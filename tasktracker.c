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
        printf("\n\tTaskTracker helps you keeping track of tasks!\n");

        printf("\n\tArguments/Options:\n");
        printf("\t  list\t\t\t\tLists all tasks\n");
        printf("\t  list <TASKSTATUS>\t\tShow only tasks with the chosen status\n");
        printf("\t  add <TASKTITLE>\t\tAdds a task with the chosen title.\n");
        printf("\t  remove <TASKID>\t\tRemoves the task with the chosen ID.\n");
        printf("\t  mark-to-do <TASKID>\t\tChange task status to to-do.\n");
        printf("\t  mark-doing <TASKID>\t\tChange task status to doing.\n");
        printf("\t  mark-done <TASKID>\t\tChange task status to done.\n");

        printf("\n\tExamples:\n");
        printf("\t  tasktracker list\n");
        printf("\t  tasktracker add \"Wash clothes\"\n");
        printf("\t  tasktracker remove 1\n");
        printf("\t  tasktracker mark-to-do 1\n");
        printf("\t  tasktracker mark-doing 1\n");
        printf("\t  tasktracker mark-done 1\n");

        return 0;
    }
    else if (strcmp(argv[1], "list") == 0) {

        // If the file doesn't exist, print a warning to the user
        if (fopen("tasks.json", "r") == NULL) {
            printf("\tThere are no saved tasks.\n");
            return 0;
        }
        // If the file exists and there's additional arguments, filter by status
        else if (argc >= 3 && strcmp(argv[2], "to-do") == 0) {

            char *fptr = fileToString("tasks.json");
            cJSON *jsonString = cJSON_Parse(fptr); 

            // Prints "table headers" for the tasks to be printed below
            printf("\n\t\tID   Task                                         Status   Created\n");
            printf("\t\t-------------------------------------------------------------------------------\n");

            int arrSize = cJSON_GetArraySize(jsonString);
            for (int i = 0; i < arrSize; i++) {
                // Iterate over every array object
                cJSON *obj = cJSON_GetArrayItem(jsonString, i);
                cJSON *status = cJSON_GetObjectItem(obj, "status");

                // If this current object status is to-do, get the remaining properties, then print its contents
                if (strcmp(status->valuestring, "to-do") == 0) {
                    cJSON *id = cJSON_GetObjectItem(obj, "task-id");
                    cJSON *title = cJSON_GetObjectItem(obj, "title");
                    cJSON *createdAt = cJSON_GetObjectItem(obj, "createdAt");

                    printf("\t\t%-5d%-45.43s%-9s%s\n", id->valueint, title->valuestring, status->valuestring, createdAt->valuestring);
                }
            }
        }
        else if (argc >= 3 && strcmp(argv[2], "doing") == 0) {
            char *fptr = fileToString("tasks.json");
            cJSON *jsonString = cJSON_Parse(fptr); 

            // Prints "table headers" for the tasks to be printed below
            printf("\n\t\tID   Task                                         Status   Created\n");
            printf("\t\t-------------------------------------------------------------------------------\n");

            int arrSize = cJSON_GetArraySize(jsonString);
            for (int i = 0; i < arrSize; i++) {
                // Iterate over every array object
                cJSON *obj = cJSON_GetArrayItem(jsonString, i);
                cJSON *status = cJSON_GetObjectItem(obj, "status");

                // If this current object status is to-do, get the remaining properties, then print its contents
                if (strcmp(status->valuestring, "doing") == 0) {
                    cJSON *id = cJSON_GetObjectItem(obj, "task-id");
                    cJSON *title = cJSON_GetObjectItem(obj, "title");
                    cJSON *createdAt = cJSON_GetObjectItem(obj, "createdAt");

                    printf("\t\t%-5d%-45.43s%-9s%s\n", id->valueint, title->valuestring, status->valuestring, createdAt->valuestring);
                }
            }
        }
        else if (argc >= 3 && strcmp(argv[2], "done") == 0) {
            char *fptr = fileToString("tasks.json");
            cJSON *jsonString = cJSON_Parse(fptr); 

            // Prints "table headers" for the tasks to be printed below
            printf("\n\t\tID   Task                                         Status   Created\n");
            printf("\t\t-------------------------------------------------------------------------------\n");

            int arrSize = cJSON_GetArraySize(jsonString);
            for (int i = 0; i < arrSize; i++) {
                // Iterate over every array object
                cJSON *obj = cJSON_GetArrayItem(jsonString, i);
                cJSON *status = cJSON_GetObjectItem(obj, "status");

                // If this current object status is to-do, get the remaining properties, then print its contents
                if (strcmp(status->valuestring, "done") == 0) {
                    cJSON *id = cJSON_GetObjectItem(obj, "task-id");
                    cJSON *title = cJSON_GetObjectItem(obj, "title");
                    cJSON *createdAt = cJSON_GetObjectItem(obj, "createdAt");

                    printf("\t\t%-5d%-45.43s%-9s%s\n", id->valueint, title->valuestring, status->valuestring, createdAt->valuestring);
                }
            }
        }
        // Otherwise, just list all tasks
        else {

            if (argc >= 3) {
                printf("\n\tTask status \"%s\" doesn't exist. Listing all tasks\n", argv[2]);
            }

            // Parses the json file into a cjson object to be iterated and printed
            char *fptr = fileToString("tasks.json");
            cJSON *jsonString = cJSON_Parse(fptr);

            // Prints "table headers" for the tasks to be printed below
            printf("\n\t\tID   Task                                         Status   Created\n");
            printf("\t\t-------------------------------------------------------------------------------\n");

            // Iterate over task objects and prints them
            int arrSize = cJSON_GetArraySize(jsonString);
            for (int i = 0; i < arrSize; i++) {

                // Extracts data from JSON properties to print later
                cJSON *obj = cJSON_GetArrayItem(jsonString, i);
                cJSON *id = cJSON_GetObjectItemCaseSensitive(obj, "task-id");
                cJSON *title = cJSON_GetObjectItemCaseSensitive(obj, "title");
                cJSON *status = cJSON_GetObjectItemCaseSensitive(obj, "status");
                cJSON *createdAt = cJSON_GetObjectItemCaseSensitive(obj, "createdAt");

                // Prints this current task to terminal (formatted for alignment with table headers)
                printf("\t\t%-5d%-45.43s%-9s%s\n", id->valueint, title->valuestring, status->valuestring, createdAt->valuestring);
                
            }
            
            return 0;
        }
    }
    // If the user puts the "add" argument, execute logic 
    else if (strcmp(argv[1], "add") == 0) {

        // If the user puts no task name argument, show helper text
        if (argv[2] == NULL) {
            printf("\n\tYou must enter a task title after the \"add\" argument.\n");
            printf("\n\tExample: tasktracker add \"Your task name\"\n");
            return 0;
        }
        // If the user inputs arguments properly, add task to file
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
                cJSON_AddNumberToObject(json, "task-id", highestId + 1);   // Increments the highestId to get a unique ID. TODO use UUID?
                cJSON_AddStringToObject(json, "title", argv[2]);
                cJSON_AddStringToObject(json, "status", "to-do");

                // Before composing next task properties, creates a string and formats current date into it according to ISO 8601 
                char datetime[22];
                getCurrentDateTime(datetime);
                cJSON_AddStringToObject(json, "createdAt", datetime);
                cJSON_AddStringToObject(json, "updatedAt", datetime);

                // Adds the task object created above into the existing file array 
                cJSON_AddItemToArray(jsonString, json);

                // Overwrites the json file with the added task, print feedback to user, then return
                char *json_str = cJSON_Print(jsonString);
                FILE *fptr1 = fopen("tasks.json", "w");
                fprintf(fptr1, json_str);
                
                printf("\tTask \"%s\" added\n", argv[2]);

                return 0;
            }
        }   
    }
    // If the user puts the "remove" argument, execute logic 
    else if (strcmp(argv[1], "remove") == 0) {

        // If the user puts no task name argument, show helper text
        if (argv[2] == NULL) {
            printf("\n\tYou must enter a task id after the \"remove\" argument.\n");
            printf("\n\tExample: tasktracker remove 1\n");
            return 0;
        }
        // If the user inputs arguments properly, remove task from file
        else {

            // If the file doesn't exist, print a warn the user
            if (fopen("tasks.json", "r") == NULL) {
                printf("\tThere are no tasks to delete\n");
            }
            // If the file exists, remove task from file
            else {
                
                // Parses the json file into a cjson object to be edited
                char *fptr = fileToString("tasks.json");
                cJSON *jsonString = cJSON_Parse(fptr);

                // Go through task objects and find one with a specific ID inputed by the user
                int arrSize = cJSON_GetArraySize(jsonString);
                int deleteTarget = atoi(argv[2]);
                for (int i = 0; i < arrSize; i++) {

                    // Checks the id of the current object in the loop
                    cJSON *obj = cJSON_GetArrayItem(jsonString, i);
                    cJSON *id_key = cJSON_GetObjectItemCaseSensitive(obj, "task-id");

                    // If it matches the id the user inputted, delete the object, rewrite file and then prints feedback to user, then returns
                    if (deleteTarget == id_key->valueint) {
                        cJSON_DeleteItemFromArray(jsonString, i);

                        char *json_str = cJSON_Print(jsonString);
                        FILE *fptr = fopen("tasks.json", "w");
                        fprintf(fptr, json_str);

                        printf("\tTask with id %d deleted.\n", deleteTarget);
                        return 0;
                    } 
                }

                // If no task with given id is found, print feedback to user and quit
                printf("\tNo task found with the given ID. Try again\n");
                return 0;
            }
        }
    }
    // If the user puts the "update" argument, execute logic
    else if (strcmp(argv[1], "update") == 0) {

        if (!argv[2]) {
            printf("\n\tYou must enter a task id after the \"update\" argument, and then the new task title\n");
            printf("\n\tExample: tasktracker update 1 \"Your new task name\"\n");
            return 0;
        } else if (!argv[3]) {
            printf("\n\tYou must enter the new task name after the id argument\n");
            printf("\n\tExample: tasktracker update 1 \"Your new task name\"\n");
            return 0;
        } else {

            char *fptr = fileToString("tasks.json");
            cJSON *jsonString = cJSON_Parse(fptr);

            int arrSize = cJSON_GetArraySize(jsonString);
            for (int i = 0; i < arrSize; i++) {

                // Checks the id of the current object in the loop
                cJSON *obj = cJSON_GetArrayItem(jsonString, i);
                cJSON *id = cJSON_GetObjectItem(obj, "task-id");

                // If it matches the id the user inputted, get the object, change the title value, and then prints feedback to user, then returns
                if (id->valueint == atoi(argv[2])) {
                    // Get the task title
                    cJSON *title = cJSON_GetObjectItem(obj, "title");

                    // Create the new title from the user input 
                    cJSON *newTitle = cJSON_CreateString(argv[3]);

                    // Replaces the title with the what the user inputed
                    cJSON_ReplaceItemInObject(obj, "title", newTitle);

                    // Puts the edited task object back on the JSON array 
                    cJSON_ReplaceItemInArray(jsonString, i, obj);

                    // Rewrites the file to update its contents
                    char *json_str = cJSON_Print(jsonString);
                    FILE *fptr1 = fopen("tasks.json", "w");
                    fprintf(fptr1, json_str);
                    
                    printf("\tTask \"%s\" updated\n", argv[2]);
                    return 0;
                }

            }

        }





    } 
    // If the user puts the "mark-done" argument, execute logic 
    else if (strcmp(argv[1], "mark-done") == 0) {

        // If the user puts no task name argument, show helper text
        if (argv[2] == NULL) {
            printf("\n\tYou must enter a task id after the \"mark-done\" argument.\n");
            printf("\n\tExample: tasktracker mark-done 1\n");
            return 0;
        }
        // If the user inputs arguments properly, mark-done task from file
        else {

            // If the file doesn't exist, print a warn the user
            if (fopen("tasks.json", "r") == NULL) {
                printf("\tThere are no tasks to mark as done\n");
            }
            // If the file exists, mark as done a specific task from file
            else {
                
                // Parses the json file into a cjson object to be edited
                char *fptr = fileToString("tasks.json");
                cJSON *jsonString = cJSON_Parse(fptr);

                // Go through task objects and find one with a specific ID inputed by the user
                int arrSize = cJSON_GetArraySize(jsonString);
                int taskTarget = atoi(argv[2]);
                for (int i = 0; i < arrSize; i++) {

                    // Checks the id of the current object in the loop
                    cJSON *obj = cJSON_GetArrayItem(jsonString, i);
                    cJSON *id_key = cJSON_GetObjectItemCaseSensitive(obj, "task-id");

                    // If it matches the id the user inputted, get the object, change the status value, and then prints feedback to user, then returns
                    if (taskTarget == id_key->valueint) {
                        // Get the task object 
                        cJSON *status = cJSON_GetObjectItemCaseSensitive(obj, "status");

                        // Create the new string value with the to be saved
                        cJSON *string = cJSON_CreateString("done");

                        // Replaces the status with "done"
                        cJSON_ReplaceItemInObject(obj, "status", string);

                        // Puts the edited task object back on the JSON array
                        cJSON_ReplaceItemInArray(jsonString, i, obj);
                        
                        // Rewrites the file to update its contents 
                        char *json_str = cJSON_Print(jsonString);
                        FILE *fptr = fopen("tasks.json", "w");
                        fprintf(fptr, json_str);

                        printf("\tTask with id %d marked as done.\n", taskTarget);
                        return 0;
                    } 
                }

                // If no task with given id is found, print feedback to user and quit
                printf("\tNo task found with the given ID. Try again\n");
                return 0;
            }
        }
    }
    // If the user puts the "mark-doing" argument, execute logic 
    else if (strcmp(argv[1], "mark-doing") == 0) {

        // If the user puts no task name argument, show helper text
        if (argv[2] == NULL) {
            printf("\n\tYou must enter a task id after the \"mark-doing\" argument.\n");
            printf("\n\tExample: tasktracker mark-doing 1\n");
            return 0;
        }
        // If the user inputs arguments properly, mark-doing task from file
        else {

            // If the file doesn't exist, print a warn the user
            if (fopen("tasks.json", "r") == NULL) {
                printf("\tThere are no tasks to mark as doing\n");
            }
            // If the file exists, mark as done a specific task from file
            else {
                
                // Parses the json file into a cjson object to be edited
                char *fptr = fileToString("tasks.json");
                cJSON *jsonString = cJSON_Parse(fptr);

                // Go through task objects and find one with a specific ID inputed by the user
                int arrSize = cJSON_GetArraySize(jsonString);
                int taskTarget = atoi(argv[2]);
                for (int i = 0; i < arrSize; i++) {

                    // Checks the id of the current object in the loop
                    cJSON *obj = cJSON_GetArrayItem(jsonString, i);
                    cJSON *id_key = cJSON_GetObjectItemCaseSensitive(obj, "task-id");

                    // If it matches the id the user inputted, get the object, change the status value, and then prints feedback to user, then returns
                    if (taskTarget == id_key->valueint) {
                        // Get the task object 
                        cJSON *status = cJSON_GetObjectItemCaseSensitive(obj, "status");

                        // Create the new string value with the to be saved
                        cJSON *string = cJSON_CreateString("doing");

                        // Replaces the status with "doing"
                        cJSON_ReplaceItemInObject(obj, "status", string);

                        // Puts the edited task object back on the JSON array
                        cJSON_ReplaceItemInArray(jsonString, i, obj);
                        
                        // Rewrites the file to update its contents 
                        char *json_str = cJSON_Print(jsonString);
                        FILE *fptr = fopen("tasks.json", "w");
                        fprintf(fptr, json_str);

                        printf("\tTask with id %d marked as \"doing\".\n", taskTarget);
                        return 0;
                    } 
                }

                // If no task with given id is found, print feedback to user and quit
                printf("\tNo task found with the given ID. Try again\n");
                return 0;
            }
        }
    }
    // If the user puts the "mark-to-do" argument, execute logic 
    else if (strcmp(argv[1], "mark-to-do") == 0) {

        // If the user puts no task name argument, show helper text
        if (argv[2] == NULL) {
            printf("\n\tYou must enter a task id after the \"mark-to-do\" argument.\n");
            printf("\n\tExample: tasktracker mark-to-do 1\n");
            return 0;
        }
        // If the user inputs arguments properly, mark-to-do task from file
        else {

            // If the file doesn't exist, print a warn the user
            if (fopen("tasks.json", "r") == NULL) {
                printf("\tThere are no tasks to mark as to-do\n");
            }
            // If the file exists, mark as done a specific task from file
            else {
                
                // Parses the json file into a cjson object to be edited
                char *fptr = fileToString("tasks.json");
                cJSON *jsonString = cJSON_Parse(fptr);

                // Go through task objects and find one with a specific ID inputed by the user
                int arrSize = cJSON_GetArraySize(jsonString);
                int taskTarget = atoi(argv[2]);
                for (int i = 0; i < arrSize; i++) {

                    // Checks the id of the current object in the loop
                    cJSON *obj = cJSON_GetArrayItem(jsonString, i);
                    cJSON *id_key = cJSON_GetObjectItemCaseSensitive(obj, "task-id");

                    // If it matches the id the user inputted, get the object, change the status value, and then prints feedback to user, then returns
                    if (taskTarget == id_key->valueint) {
                        // Get the task object 
                        cJSON *status = cJSON_GetObjectItemCaseSensitive(obj, "status");

                        // Create the new string value with the to be saved
                        cJSON *string = cJSON_CreateString("to-do");

                        // Replaces the status with "doing"
                        cJSON_ReplaceItemInObject(obj, "status", string);

                        // Puts the edited task object back on the JSON array
                        cJSON_ReplaceItemInArray(jsonString, i, obj);
                        
                        // Rewrites the file to update its contents 
                        char *json_str = cJSON_Print(jsonString);
                        FILE *fptr = fopen("tasks.json", "w");
                        fprintf(fptr, json_str);

                        printf("\tTask with id %d marked as \"to-do\".\n", taskTarget);
                        return 0;
                    } 
                }

                // If no task with given id is found, print feedback to user and quit
                printf("\tNo task found with the given ID. Try again\n");
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