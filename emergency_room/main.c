#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emergency.h"

void display_menu()
{
    printf("\nEmergency Room Patient Management System(ERPMS)\n");
    printf("1. Add a new patient\n");
    printf("2. Extract the patient with the highest severity\n");
    printf("3. Update a patient's severity\n");
    printf("4. Display the patient queue\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    max_heap_t *pHeap = create_heap();
    if (!pHeap)
    {
        printf("Error: Could not create patient heap.\n");
        return 1;
    }

    int choice;
    char name[100];
    char condition[100];
    int severity;

    while (1)
    {
        display_menu();
        scanf("%d", &choice);
        getchar(); // Clear newline from input buffer

        switch (choice)
        {
            case 1:
                printf("Enter patient's name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character

                printf("Enter patient's condition: ");
                fgets(condition, sizeof(condition), stdin);
                condition[strcspn(condition, "\n")] = '\0'; // Remove newline character

                printf("Enter severity of the condition (higher number indicates more severe): ");
                scanf("%d", &severity);

                if (add_patient(pHeap, name, condition, severity))
                {
                    printf("Patient added successfully.\n");
                }
                else
                {
                    printf("Error: Could not add patient.\n");
                }
                break;

            case 2:
            {
                patient_t *severe_patient = extract_max(pHeap);
                if (severe_patient)
                {
                    printf("Patient with highest severity treated: %s, Condition: %s, Severity: %d\n",
                           severe_patient->name, severe_patient->condition, severe_patient->severity);
                    free_patient(severe_patient); // Free the extracted patient after treatment
                }
                else
                {
                    printf("No patients are waiting for treatment.\n");
                }
                break;
            }

            case 3:
                printf("Enter the patient's name to update severity: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character

                printf("Enter new condition (leave blank to keep current condition): ");
                fgets(condition, sizeof(condition), stdin);
                condition[strcspn(condition, "\n")] = '\0'; // Remove newline character

                printf("Enter new severity: ");
                scanf("%d", &severity);

                if (update_severity(pHeap, name, strlen(condition) > 0 ? condition : NULL, severity))
                {
                    printf("Patient severity updated successfully.\n");
                }
                else
                {
                    printf("Error: Patient not found or could not update severity.\n");
                }
                break;

            case 4:
                display_patient_queue(pHeap);
                break;

            case 5:
                printf("Exiting the program...\n");
                free_heap(pHeap);
                return 0;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
