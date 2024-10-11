#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

void display_menu()
{
    printf("\n===== Product Database Menu =====\n");
    printf("1. Insert a new product\n");
    printf("2. Search for a product by name\n");
    printf("3. Update product details\n");
    printf("4. Display all products in sorted order\n");
    printf("5. Display out-of-stock products\n");
    printf("6. Exit\n");
    printf("=================================\n");
    printf("Enter your choice: ");
}

int main()
{
    database_t *database = create_database();
    int choice;
    char name[100], ID[100], new_name[100], new_ID[100];
    double price;
    int quantity, new_quantity;

    if (!database)
    {
        fprintf(stderr, "Error: Unable to create the database.\n");
        return EXIT_FAILURE;
    }

    while (1)
    {
        display_menu();
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                printf("Enter product name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Enter product ID: ");
                fgets(ID, sizeof(ID), stdin);
                ID[strcspn(ID, "\n")] = '\0';

                printf("Enter product price: ");
                scanf("%lf", &price);
                printf("Enter product quantity: ");
                scanf("%d", &quantity);

                if (add_product(database, name, ID, price, quantity))
                    printf("Product added successfully!\n");
                else
                    fprintf(stderr, "Error: Failed to add the product.\n");
                break;

            case 2:
                printf("Enter the name of the product to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                node_t *product_node = search_product(database, name);
                if (product_node)
                    printf("Product found: %s, ID: %s, Price: %.2f, Quantity: %d\n",
                           product_node->product->name, product_node->product->ID,
                           product_node->product->price, product_node->product->quantity);
                else
                    printf("Product not found.\n");
                break;

            case 3:
                printf("Enter the name of the product to update: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Enter new product name (or press Enter to skip): ");
                fgets(new_name, sizeof(new_name), stdin);
                new_name[strcspn(new_name, "\n")] = '\0';

                printf("Enter new product ID (or press Enter to skip): ");
                fgets(new_ID, sizeof(new_ID), stdin);
                new_ID[strcspn(new_ID, "\n")] = '\0';

                printf("Enter new price (or 0 to skip): ");
                scanf("%lf", &price);
                printf("Enter new quantity (or -1 to skip): ");
                scanf("%d", &new_quantity);

                if (update_details(database, name, 
                    strlen(new_name) > 0 ? new_name : NULL, 
                    strlen(new_ID) > 0 ? new_ID : NULL, 
                    price != 0 ? price : -1, 
                    new_quantity != -1 ? new_quantity : -1))
                    printf("Product details updated successfully!\n");
                else
                    fprintf(stderr, "Error: Failed to update product details.\n");
                break;

            case 4:
                printf("Displaying all products in sorted order:\n");
                database_inorder(database->head);
                break;

            case 5:
                printf("Displaying out-of-stock products:\n");
                out_of_stock(database->head);
                break;

            case 6:
                delete_database(database->head);
                free(database);
                printf("Exiting the program. Goodbye!\n");
                return EXIT_SUCCESS;

            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    }
    return EXIT_SUCCESS;
}
