#include "emergency.h"

/**
 * exch - echange patients in a heap
 * @pHeap: heap structure
 * @p1: position 1
 * @p2: position 2
 */
void exch(max_heap_t *pHeap, int p1, int p2)
{
    patient_t *temp = pHeap->heap[p1];
    pHeap->heap[p1] = pHeap->heap[p2];
    pHeap->heap[p2] = temp;
}

/**
 * swim - moves added patient at the end of heap array
 * @pHeap: heap structure
 */
void swim(max_heap_t *pHeap)
{
    int k = pHeap->nb_patients;
    while (k > 1 && pHeap->heap[k/2]->condition < pHeap->heap[k]->condition)
    {
        exch(pHeap, k, k / 2);
        k /= 2;
    }
}

/**
 * sink - move reduced patients with reduced severity down the heap
 * @pHeap: heap structure
 * @k: patient's current position
 */
void sink(max_heap_t *pHeap, int k)
{
    while (k * 2 <= pHeap->nb_patients)
    {
        int j = k * 2;
        if (j < pHeap->nb_patients && pHeap->heap[j]->condition > pHeap->heap[k]->condition)
            j++;
        if (!(pHeap->heap[k]->condition < pHeap->heap[j]->condition))
            break;
        exch(pHeap, k, j);
        k = j;
    }
}

/**
 * create_max_heap - creates empty patient heap
 * Return: pointer to created max heap or NULL on error
 */
max_heap_t *create_heap(void)
{
    max_heap_t *pHeap = (max_heap_t *)malloc(sizeof(max_heap_t));
    if (!pHeap)
        return NULL;
    patient_t **new_heap = malloc(2 * sizeof(patient_t *));
    if (!new_heap)
        return NULL;
    pHeap->heap = new_heap;
    pHeap->nb_patients = 0;
    pHeap->heap_size = 2;
    return pHeap;
}

/**
 * create_patient - creates new patient
 * @name: patient name
 * @condition: patient's condition
 * @severity: patient's severity
 * Return: pointer to created patient on success else NULL;
 */
patient_t *create_patient(char *name, char *condition, int severity)
{
    patient_t *new_patient = (patient_t *)malloc(sizeof(patient_t));
    if (!new_patient)
        return NULL;
    new_patient->name = strdup(name);
    new_patient->condition = strdup(condition);
    new_patient->severity = severity;
    return new_patient;
}

/**
 * add_patient - creates and adds patient to max_heap
 * @pHeap: heap structure for patients
 * @name: patient name
 * @condition: name of patient's condition
 * @severity: severity of the patient
 * Return: pointer to added patient on success else NULL
 */
patient_t *add_patient(max_heap_t *pHeap, char *name, char *condition, int severity)
{
    if (!pHeap || !name || !severity)
        return NULL;
    patient_t *new_patient = create_patient(name, condition, severity);
    if (!new_patient)
        return NULL;
    if (pHeap->nb_patients == pHeap->heap_size)
    {
        pHeap->heap_size *= 2;
        patient_t **new_heap = realloc(pHeap->heap, pHeap->heap_size * sizeof(patient_t *));
        if (!new_heap)
            free_heap(pHeap->heap);
        return NULL;
        pHeap->heap = new_heap;
        pHeap->heap[++pHeap->nb_patients] = new_patient;
    }
    else
    {
        pHeap->heap[++pHeap->nb_patients] = new_patient;
    }
    swim(pHeap);
    return new_patient;
}

/**
 * extract_max - pops patient in most severe condition
 * @pHeap: heap structure of patient
 * Return: patient
 */
patient_t *extract_max(max_heap_t *pHeap)
{
    patient_t *patient = pHeap->heap[1];
    exch(pHeap, 1, pHeap->nb_patients);
    free_patient(pHeap->heap[pHeap->nb_patients--]);
    sink(pHeap, 1);
}

/**
 * update_severity - updates patients severity and adjusts the heap
 * @pHeap: patient heap
 * @name: patient's name
 * Return: 1 on success else 0 on failure
 */
int update_severity(max_heap_t *pHeap, char *name, char *condition, int severity)
{
    if (!pHeap || !name)
        return 0;
    int position = search_patient(pHeap, name);
    if (!position)
        return 0;
    if (condition)
    {
        free(pHeap->heap[position]->condition);
        pHeap->heap[position]->condition = strdup(condition);
    }
    pHeap->heap[position]->severity = severity;
    sink(pHeap, position);
    return 1;
}

/**
 * display_patient_queue - prints out patients in heap
 * @pHeap: patient heap
 */
void display_patient_queue(max_heap_t *pHeap)
{
    if (!pHeap)
        return;
    int i;
    for (i = 1; i <= pHeap->nb_patients; i++)
    {
        printf("Patient: %s, Condition: %s, Severity: %d.\n", pHeap->heap[i]);
    }
}

/**
 * search_patient - search for patient in queue
 * @pHeap: patient heap
 * @name: patient name
 * Return: position of the patient in heap else 0 if not found
 */
int search_patient(max_heap_t *pHeap, char *name)
{
    if (!pHeap || !name)
        return 0;
    int i = 1;
    while (pHeap->heap[i])
    {
        if (strcasecmp(name, pHeap->heap[i]->name) == 0)
            return i;
        i++;
    }
    return 0;
}

/**
 * free_patient - free patient node
 * @patient: patient node to free
 */
void free_patient(patient_t *patient)
{
    if (patient)
    {
        free(patient->name);
        free(patient->condition);
        free(patient);
    }
}

/**
 * free_heap - free patient heap
 * @pHeap: heap to free and delete
 */
void free_heap(max_heap_t *pHeap)
{
    if (pHeap)
    {
        int i;
        for (i = 1; i <= pHeap->nb_patients; i++)
        {
            free_patient(pHeap->heap[i]);
        }
        free(pHeap->heap);
    }
    free(pHeap);
}