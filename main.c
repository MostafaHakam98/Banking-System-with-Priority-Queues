#include <stdio.h>
#include <stdlib.h>

/*
 * Item: Each Item has a customer name and a balance.
 * and an integer order(it is used to handle the case when two items have same priority)
*/
typedef struct {
    char* cName;
    double balance;
    int order;
} Item;

 /*
  * Swap two array elements
  */
void swap(Item *arr, int a, int b) {
    Item temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

/*
 * Heapify index i in array of Items with size n
 */
void max_heapify (Item *arr, int n, int i) {
    int left = i * 2;
    int right = left + 1;
    int max = i;

    //Comparing left child node with max
    if (left <= n-1){
        if(arr[left].balance > arr[max].balance)
            max = left;
        //if left child node = max
        else if(abs(arr[left].balance - arr[max].balance) < 0.05){
            if (arr[left].order < arr[max].order)
                max = left;
        }
    }

    //Comparing right child node with max
    if (right <= n-1) {
        if(arr[right].balance > arr[max].balance)
            max = right;
        //if right child node = max
        else if(abs(arr[right].balance - arr[max].balance) < 0.05){
            if (arr[right].order < arr[max].order)
                max = right;
        }
    }

    //Swap changes
    if (max != i) {
        swap(arr, i, max);
        max_heapify(arr, n, max);
    }
}

/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
void construct_PQ (Item *arr, int n) {
    int i = n/2;
    while(i > 0)
        max_heapify(arr, n, --i);
}

/*
 * delete the item with max priority and then return it.
 */
Item extract_maximum (Item *arr, int n) {
    Item temp = arr[0];
    arr[0].balance = 0;
    max_heapify(arr, n, 0);
    return temp;
}

/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile (char* fname, Item* arr) {

    int size = 0; //Size of Array to be returned
    FILE *fptr = fopen (fname, "r");

    char *temp; //String storing name of each Item

    while (!feof(fptr)) {
        temp = (char*) malloc(sizeof(char) * 10);
        fscanf(fptr, "%[^ ] %lf\n", temp, &arr[size].balance); //Reading name and balance from file

        arr[size].cName = temp;
        arr[size].order = size+1;

        size++;
    }
    fclose(fptr);

    return size; //Returning size as arrLength
}

/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority (Item *arr, int n) {
    int i = 0;
    Item temp;
    for(i = 0; i < n; i++) {
        temp = extract_maximum(arr, n);
        printf("(%d) %s \t%.1lf\n", i+1, temp.cName, temp.balance);
    }
}

/*
 *
 */
int main(int argc, char**argv) {

	if(argc != 2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

    Item *customers = (Item*) malloc (sizeof(Item) * 1000);
    int arrLength = fillArrayFromFile (argv[1], customers);

    construct_PQ (customers, arrLength);
    printCustomersbyPriority(customers, arrLength);

    return 0;
}
