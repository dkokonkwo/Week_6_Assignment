#include "bst.h"

/**
 * create_database - create empty database structure
 * Return: pointer to created database or NULL on error
 */
database_t *create_database(void)
{
    database_t *new_database = (database_t *)malloc(sizeof(database_t));
    if (!new_database)
        return NULL;
    new_database->nb_products = 0;
    new_database->head = NULL;
    return new_database;
}

/**
 * create_product - creates new product
 * @name: product name
 * @ID: product ID
 * @price: product price per unit
 * @quantity: number of available units
 * Return: pointer to new product or NULL on error
 */
product_t *create_product(char *name, char *ID, double price, int quantity)
{
    product_t *new_product;
    if (!name || price <= 0 || !ID)
        return NULL;
    new_product = (product_t *)malloc(sizeof(product_t));
    if (!new_product)
        return NULL;
    new_product->name = strdup(name);
    if (!new_product->name)
    {
        free(new_product);
        return NULL;
    }
    new_product->ID = strdup(ID);
    if (!new_product->ID)
    {
        free(new_product);
        return NULL;
    }
    new_product->price = price;
    new_product->quantity = quantity;
    return new_product;
}

/**
 * create_node - create new node
 * @product: product to add to node
 * Return: pointer to created node or NULL on error
 */
node_t *create_node(product_t *product)
{
    node_t *new_node;
    if (!product)
        return NULL;
    new_node = (node_t *)malloc(sizeof(node_t));
    if (!new_node)
        return NULL;
    new_node->product = product;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->index = 0;
    return new_node;
}

/**
 * add_product - adds new product to database
 * @database: database to store new product
 * @name: product name
 * @ID: product ID
 * @price: product price per unit
 * @quantity: number of available units
 * Return: 1 on succes, or 0 on failure
 */
int add_product(database_t *database, char *name, char *ID, double price, int quantity)
{
    node_t *node;
    product_t *product;
    if (!database)
    {
        fprintf(stderr, "Error: No database available to add the product.\n");
        return 0;
    }
    product = create_product(name, ID, price, quantity);
    if (!product)
    {
        fprintf(stderr, "Error: Failed to create the product.\n");
        return 0;
    }
    node = create_node(product);
    if (!node)
    {
        fprintf(stderr, "Error: Failed to create the product node.\n");
        free(product->name);
        free(product->ID);
        free(product);
        return 0;
    }
    if (database->nb_products == 0)
    {
        database->head = node;
    }
    else
    {
        node_t *curr = database->head;
        while (curr)
        {
            if (strcasecmp(name, curr->product->name) > 0)
            {
                if (curr->right)
                    curr = curr->right;
                else
                {
                    curr->right = node;
                    break;
                }
            }
            else
            {
                if (curr->left)
                    curr = curr->left;
                else
                {
                    curr->left = node;
                    break;
                }
            }       
        }
    }
    node->index = database->nb_products++;
    return 1;
}
/**
 * search_product - searches for product in database
 * @database: database to search through
 * @name: product name
 * Return: pointer to product node if found else NULL
 */
node_t *search_product(database_t *database, char *name)
{
    node_t *curr;
    if (!database || !name)
        return NULL;
    curr = database->head;
    while (curr)
    {
        if (strcasecmp(name, curr->product->name) < 0)
            curr = curr->left;
        else if (strcasecmp(name, curr->product->name) > 0)
            curr = curr->right;
        else
        {
            printf("Found!\n");
            return curr;
        }
    }
    return NULL;
}

/**
 * update_details - update details of product
 * @database: product database
 * @name: current product name
 * @new_name: new product name
 * @new_ID: new product id
 * @new_price: new product price
 * @new_quantity: new unit quantity
 * Return: 1 on success else 0 on failure
 */
int update_details(database_t *database, char *name, char *new_name, char *new_ID, double new_price, int new_quantity)
{
    node_t *product_node;
    if (!database || !name)
        return 0;
    product_node = search_product(database, name);
    if (!product_node)
        return 0;
    if (new_name)
    {
        free(product_node->product->name);
        product_node->product->name = strdup(new_name);
    }
    if (new_ID)
    {
        free(product_node->product->ID);
        product_node->product->ID = strdup(new_ID);
    }
    if (new_price)
        product_node->product->price = new_price;
    if (new_quantity)
        product_node->product->quantity = new_quantity;

    printf("Product details updated!\n");
    return 1;
}

/**
 * database_inorder - inorder traversal displays product in ascending order of name
 * @head:  database head
 */
void database_inorder(node_t *head)
{
    product_t *c_product;
    if (!head)
        return;
    c_product = head->product;
    database_inorder(head->left);
    printf("%s ID: %s price: %.2f units in stock: %d\n", c_product->name, c_product->ID, c_product->price, c_product->quantity);
    database_inorder(head->right);
}

/**
 * out_of_stock - inorder traversal displays out of stock products
 * @head:  database head
 */
void out_of_stock(node_t *head)
{
    product_t *c_product;
    if (!head)
        return;
    c_product = head->product;
    out_of_stock(head->left);
    if (c_product->quantity == 0)
        printf("%s ID: %s is currently out of stock.\n", c_product->name, c_product->ID);
    out_of_stock(head->right);
}

/**
 * delete_database - free node and its content
 * @head: head node of database
 */
void delete_database(node_t *head)
{
    if (head)
    {
        delete_database(head->left);
        delete_database(head->right);
        free(head->product->name);
        free(head->product->ID);
        free(head->product);
        free(head);
        
    }
}