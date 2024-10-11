#ifndef BST_H
#define BST_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct product_s - structure for a product
 * @name: product name
 * @ID: product ID
 * @price: price of one unit of product
 * @quantity: number of units in stock
 */
typedef struct product_s
{
    char *name;
    char *ID;
    double price;
    int quantity;
} product_t;

/**
 * struct node_s node structure that stores a product
 * @product: a product
 * @left: pointer to left child of node
 * @right: pointer to right child of node
 */
typedef struct node_s
{
    product_t *product;
    size_t index;
    struct node_s *left;
    struct node_s *right;
} node_t;

/**
 * struct database_s - database to store nodes of products
 * @nb_products: number of products
 * @head: pointer to first node of product in database
 */
typedef struct database_s
{
    size_t nb_products;
    node_t *head;
} database_t;

database_t *create_database(void);
product_t *create_product(char *name, char *ID, double price, int quantity);
node_t *create_node(product_t *product);
int add_product(database_t *database, char *name, char *ID, double price, int quantity);
int update_details(database_t *database, char *name, char *new_name, char *new_ID, double new_price, int new_quantity);
void database_inorder(node_t *head);
void out_of_stock(node_t *head);
void delete_database(node_t *head);
#endif