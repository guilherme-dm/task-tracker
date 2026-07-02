#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        printf("\n\tTaskTracker helps you with daily tasks!\n");

        printf("\n\tArguments/Options:\n");
        printf("\t  add <TASKTITLE>\t\tAdds a task with the chosen title.\n");

        printf("\n\tExamples:\n");
        printf("\t  tasktracker add \"Wash clothes\"\n");

        return 0;
    }

    return 0;
}