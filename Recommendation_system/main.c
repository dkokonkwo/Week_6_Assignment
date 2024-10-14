#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void display_menu();
void handle_add_member(graph_t *network);
void handle_create_connection(graph_t *network);
void handle_recommend_connections(graph_t *network);

int main() {
    graph_t *network = create_network();
    if (!network) {
        printf("Error: Unable to create network.\n");
        return EXIT_FAILURE;
    }
    if (build_network(network))
        printf("Built new network.\n");
    else
    {
        printf("Error: Unable to build network.\n");
        return EXIT_FAILURE;
    }

    int choice;
    while (1) {
        display_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                handle_add_member(network);
                break;
            case 2:
                handle_create_connection(network);
                break;
            case 3:
                handle_recommend_connections(network);
                break;
            case 4:
                network_delete(network);
                printf("Exiting the program. Goodbye!\n");
                return EXIT_SUCCESS;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

/**
 * display_menu - Displays the menu options to the user.
 */
void display_menu() {
    printf("\n====== Recommendation System Menu ======\n");
    printf("1. Add a new member to the network\n");
    printf("2. Create a connection between members\n");
    printf("3. Recommend new connections\n");
    printf("4. Exit\n");
}

/**
 * handle_add_member - Handles adding a new member to the network.
 * @network: Pointer to the graph network.
 */
void handle_add_member(graph_t *network) {
    char name[100];
    printf("Enter the name of the new member: ");
    scanf(" %[^\n]s", name);
    while (getchar() != '\n');

    if (add_member(network, name)) {
        printf("Member '%s' added successfully.\n", name);
    } else {
        printf("Error: Unable to add member '%s'.\n", name);
    }
}

/**
 * handle_create_connection - Handles creating a connection between two members.
 * @network: Pointer to the graph network.
 */
void handle_create_connection(graph_t *network) {
    char src[100], dest[100];
    printf("Enter the name of the source member: ");
    scanf(" %[^\n]s", src);
    while (getchar() != '\n');
    printf("Enter the name of the destination member: ");
    scanf(" %[^\n]s", dest);
    while (getchar() != '\n');

    if (create_connection(network, src, dest)) {
        printf("Connection created between '%s' and '%s'.\n", src, dest);
    } else {
        printf("Error: Unable to create connection between '%s' and '%s'.\n", src, dest);
    }
}

/**
 * handle_recommend_connections - Handles recommending new connections for a member.
 * @network: Pointer to the graph network.
 */
void handle_recommend_connections(graph_t *network) {
    char name[100];
    printf("Enter the name of the member for recommendations: ");
    scanf(" %[^\n]s", name);
    while (getchar() != '\n');

    recommend_connections(network, name);
}
