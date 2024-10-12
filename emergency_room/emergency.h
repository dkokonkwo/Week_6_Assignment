#ifndef EMERGENCY_H
#define EMERGENCY_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/**
 * struct patient_s - patient node in max heap
 * @name: Patient name
 * @condition: patient condition
 * @severity: condition severity
 * @left: node's left child
 * @right: node's right child
 */
typedef struct patient_s
{
    char *name;
    char *condition;
    int severity;
    size_t index;
} patient_t;

/**
 * struct max_heap_s - emergency room queue (max heap)
 * @nb_patients: number of patients for treatment
 * @first: pointer to most severe/first patient
 */
typedef struct max_heap_s
{
    int nb_patients;
    patient_t **heap;
    int heap_size;
} max_heap_t;

#endif

