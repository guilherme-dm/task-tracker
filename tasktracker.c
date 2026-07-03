#include "libs/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* fileToString(const char *filename);
void getCurrentDateTime(char *string);

int main(int argc, char *argv[]) {

    // If the user puts no arguments, just print help text
    if (argc <= 1) {
        printf("\n\tTaskTracker helps you with daily tasks!\n");

        printf("\n\tArguments/Options:\n");
        printf("\t  add <TASKTITLE>\t\tAdds a task with the chosen title.\n");

        printf("\n\tExamples:\n");
        printf("\t  tasktracker add \"Wash clothes\"\n");

        return 0;
    }
    // If the user puts the "add" argument, execute logic 
    else if (strcmp(argv[1], "add") == 0) {

        // If the user puts no task name argument, show helper text
        if (argv[2] == NULL) {
            printf("\n\tYou must enter a task title after the \"add\" argument.\n");
            printf("\n\tExample: tasktracker add \"Your task name\"\n");
            return 0;
        }
        // If the user inputs arguments properly add task to file
        else {

            // If the file doesn't exist, creates a file with the first task
            if (fopen("tasks.json", "r") == NULL) {

                // Tries to create a object, if it fails, just print error and return
                cJSON *json = cJSON_CreateObject();
                if (json == NULL) {
                    printf("Failed to create JSON");
                    return 1;
                }

                // Composes the object by adding the first task properties to it
                cJSON_AddNumberToObject(json, "task-id", 1);        // TODO usar UUID
                cJSON_AddStringToObject(json, "title", argv[2]);
                cJSON_AddStringToObject(json, "status", "to-do");

                // Before composing next task properties, creates a string and formats current date into it according to ISO 8601 
                char datetime[22];
                getCurrentDateTime(datetime);
                cJSON_AddStringToObject(json, "createdAt", datetime);
                cJSON_AddStringToObject(json, "updatedAt", datetime);

                // Adds the task object created above into an Array for a properly formatted valid JSON 
                cJSON *json_array = cJSON_CreateArray();
                cJSON_AddItemToArray(json_array, json);

                // Creates a json file and write content on it, then return
                char *json_str = cJSON_Print(json_array);
                FILE *fptr = fopen("tasks.json", "w");
                fprintf(fptr, json_str);

                printf("\tTask added\n");
                
                return 0;
            }
            // Else if the files exists, reads and parse to JSON, check highest id used, then add tasks with higher (unique) ID
            else {

                // Parses the json file into a cjson object to be edited
                char *fptr = fileToString("tasks.json");
                cJSON *jsonString = cJSON_Parse(fptr);

                // Discover the highest used ID in the file content and saves it
                int arrSize = cJSON_GetArraySize(jsonString);
                int highestId = 0;
                for (int i = 0; i < arrSize; i++) {
                    cJSON *obj = cJSON_GetArrayItem(jsonString, i);
                    cJSON *id_key = cJSON_GetObjectItemCaseSensitive(obj, "task-id");
                    if (id_key->valueint > highestId) {
                        highestId = id_key->valueint;
                    }
                }

                // Tries to create a object, if it fails, just print error and return
                cJSON *json = cJSON_CreateObject();
                if (json == NULL) {
                    printf("Failed to create JSON");
                    return 1;
                }

                // Composes the object by adding the first task properties to it
                cJSON_AddNumberToObject(json, "task-id", highestId + 1);   // Increments the highestId to get a unique ID. TODO usar UUID
                cJSON_AddStringToObject(json, "title", argv[2]);
                cJSON_AddStringToObject(json, "status", "to-do");

                // Before composing next task properties, creates a string and formats current date into it according to ISO 8601 
                char datetime[22];
                getCurrentDateTime(datetime);
                cJSON_AddStringToObject(json, "createdAt", datetime);
                cJSON_AddStringToObject(json, "updatedAt", datetime);

                // Adds the task object created above into the existing file array 
                cJSON_AddItemToArray(jsonString, json);

                // Overwrites the json file with the added task, then return
                char *json_str = cJSON_Print(jsonString);
                FILE *fptr1 = fopen("tasks.json", "w");
                fprintf(fptr1, json_str);
                
                printf("\tTask \"%s\" added\n", argv[2]);

                return 0;
            }
        }   
    }
    
    return 0;
}



void getCurrentDateTime(char *string) {

    time_t t = time(NULL);      // Fetches current time from OS. (seconds after epoch)
    t += 10800;                 // Adds 3 hours to time to offset it to Zulu time from GMT-3 (TODO make dynamic)
    struct tm *tm;              // Declares a struct capable of containing time in distinct units. (sec, min, hou, day, etc)
    tm = localtime(&t);         // Convert time in seconds from the OS and stores it in the struct.

    // Formats the datetime from the system into ISO 8601
    snprintf(string, 21, "%.4d-%.2d-%.2dT%.2d:%.2d:%.2dZ", (tm->tm_year + 1900), (tm->tm_mon + 1), tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
}

char* fileToString(const char *filename) {

    FILE *file = fopen(filename, "rb");     // Open the file in binary mode for Windows compatibility
    if (file == NULL) {                     // If the pointer is NULL, prints the error and returns NULL
        printf("Error opening file.\n");
        return NULL;
    }

    // Seek the end of file to get its length 
    fseek(file, 0, SEEK_END);           
    long length = ftell(file);

    // Allocate memory according to file size + 1 (for \0 character) then return the file content finally converted to string  
    char *data = malloc(length + 1);
    if (data) {
        fseek(file, 0, SEEK_SET);
        fread(data, 1, length, file);
        data[length] = '\0';            
    }
    fclose(file);

    return data;
}