#include <stdio.h>
#include <stdlib.h>

void OneDMath(int);
void fillArray(char*, int);
void OneDChar(int);
void TwoDChar(int, int);
void Swap(int*, int*);
int  ArrayDivider(int arr[], int, int);
void QuickSort(int arr[], int, int);
void SwapChar(char*, char*);
int  ArrayDividerChar(char arr[], int, int);
void QuickSortChar(char arr[], int, int);


int main(int argc, char** argv) {
  int choice, size, numberOfStrings, sizeOfStrings;
  do {
    printf("Welcome to Assignment3!\n");
    printf("Menu:\n");
    printf("1 - 1D Math\n");
    printf("2 - Single Dimension Character Processing\n");
    printf("3 - Two-D Character Processing\n");
    printf("4 - Exit\n");
    printf("Choose an option: ");

    scanf("%d", &choice);

    switch(choice) {
    case 1 :
      printf("\n\nWelcome to 1D Math!\n");
      printf("Please enter the size of the array you would like to create: ");
      
      scanf("%d", &size);
      OneDMath(size);
      break;

    case 2 : 
      printf("\n\nWelcome to Single Dimension Character Processing!\n");
      printf("Please enter the number of characters you would like to generate: ");
      
      scanf("%d", &size);
      OneDChar(size);
      break;

    case 3 :
      printf("\n\nWelcome to Two-D Character Processing!\n");
      printf("How many strings do you want to enter? ");
      scanf("%d", &numberOfStrings);
      printf("\nWhat is the max size of the strings? ");
      scanf("%d", &sizeOfStrings);

      TwoDChar(numberOfStrings, sizeOfStrings);
      break;
    
    case 4 :
      printf("Goodbye!\n");
      break;

    default :
      printf("\nNot a valid input. Please try again!\n\n");
      break;
    }
  }

  while(choice != 4);

  return (0);
}

void OneDMath(int size) {
  int minimum, maximum, sum = 0, count = 0, uniques = 0, duplicates, i, j;
  double average, median;
  int* myArray;
  myArray = (int*)malloc(size * sizeof(int));

  printf("\nEnter the minimum number for the array: ");
  scanf("%d", &minimum);

  printf("\nEnter the maximum number for the array: ");
  scanf("%d", &maximum);

  for(i = 0; i < size; i++) {
    myArray[i] = (rand() % (maximum - minimum + 1)) + minimum;
    //using a for loop, this will fill the array with numbers within the
    //minimum and maximum numbers requested
  }
 
  //SORTING AND PRINTING THE ARRAY 
  QuickSort(myArray, 0, size);
  
  printf("[");
  for(i = 0; i < size - 1; i++) {
    //in order to format correctly, this for loop goes to the second to the
    //last value
    printf("%d - ", myArray[i]);
  }
  printf("%d]\n", myArray[size -1]);//the final value is added here

  //COMPUTING THE AVERAGE
  for(i = 0; i < size; i++) {
    sum += myArray[i];
  }
  
  average = (double)sum / size;
  //in order to complete this operation with decimal values, sum must be cast
  //as a double
  printf("The average of the array is: %.4f\n", average);

  //COMPUTING THE MEDIAN
  if(size % 2 != 0) { //checks if there is an even or odd number of elements
    median = myArray[size/2];;
    //Since my array is sorted, I am able to do this operation
    printf("The median of the array is: %.0f\n", median);
  }
  else {
    median = ((double)myArray[(size/2 - 1)] + (double)myArray[size/2])/2;
    //If there is an even number of elements, the median is the average of the 
    //two middle elements (cast as doubles to return a double)
    printf("The median of the array is: %.1f\n", median);
  }

  //COUNTING THE NUMBER OF UNIQUE ELEMENTS
  for(i = 0; i < size; i++) {
    count = 0;

    for(j = 0; j < size; j++) {
      if(i != j && myArray[i] == myArray[j]) {
	count++;//counts the number of duplicate elements after the original
      }
    }

    uniques++;
    i += count;
    //by incrementing i by count, the for loop skips over all duplicates to 
    //avoid double counting and allows uniques to simply be incremented each 
    //time i runs. This is only possible because the array is sorted
  }
  printf("The number of unique elements is: %d\n", uniques);

  //COUNTING HOW MANY ELEMENTS WERE DUPLICATED 
  duplicates = size - uniques;//all the uniques and duplicates must equal size
  printf("The number of elements that were duplicated is: %d\n\n", duplicates);
}

void OneDChar(int size) {
  char* myArray;
  int i, choice, count = 0, instance, finalSize = size;
  char letter;
  myArray = (char*)malloc(size);
  for(i = 0; i < size; i++) {
    myArray[i] = '\0';
  }
  fillArray(myArray, size);
  printf("%s\n", myArray);
  
  do {
    printf("What would you like to do?\n");
    printf("1.\tCheck frequency of a letter\n");
    printf("2.\tRemove a letter\n");
    printf("3.\tSort\n");
    printf("4.\tReturn to Main Menu\n");
    printf(">>? ");

    scanf("%d", &choice);

    switch(choice) {
    case 1 :
      count = 0;
      printf("\n\nWhat letter would you like to count? ");
      scanf(" %c", &letter);

      for(i = 0; i < size; i++) {
	if(myArray[i] == letter) {
	  count++;
	}
      }

      printf("There are %d of the letter %c\n\n", count, letter);
      break;

    case 2 :
      printf("\n\nWhat letter would you like to remove? ");
      scanf(" %c", &letter);

      for(i = 0; i < size; i++) {
	if(myArray[i] == letter) {
	  instance = i;
	  if(instance == (size - 1)) {//we are at the last element of the array
	      myArray[instance] = '\0';
	  }
	  else {
	    for(instance = i; instance < size - 1; instance++) {
	      myArray[instance] = myArray[instance + 1];
	    }
	    finalSize--;//keeps track of what size the final array should be
	    i--; //i must be decremented incase letters are sequential
	  }
	}
      }
      myArray[finalSize] = '\0';//clears all other chars after finalSize
      printf("%s\n\n", myArray);
      break;

    case 3 :
      printf("Sorting!\n");
      QuickSortChar(myArray, 0, finalSize - 1);
      printf("%s\n\n", myArray);
      break;

    case 4 :
      printf("Returning to the Main Menu!\n\n");
      break;

    default : 
      printf("\nPlease enter a valid input.\n");
      break;
    }
  }
  while(choice != 4);
}

void fillArray(char* letters, int size) {
  int i;
  printf("Filling the array!\n");
  for(i = 0; i < size; i++) {
    letters[i] = (rand() % 26) + 'a';
    //fills this array with the ASCII code of a + (a random number from 0 to
    //26)--this is because there are 26 letters in the alphabet (%26 gives a 
    //number from 0 to 25)
  }
}

void Swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int ArrayDivider(int arr[], int low, int high) {
  //this function takes the last element as the pivot, places the pivot in its
  //correct position in a sorted array, and places all elements smaller than 
  //pivot to the left and greater than pivot to the right
  int j;
  int pivot = arr[high];
  int i = (low - 1);//index of smaller element

  for(j = low; j < high; j++) {
    if(arr[j] <= pivot) {
      i++;//increment index of smaller element
      Swap(&arr[i], &arr[j]);
    }
  }
  Swap(&arr[i + 1], &arr[j]);
  return(i + 1);
}

void QuickSort(int arr[], int low, int high) {
  //low and high will originally be the starting and ending indexes
  if(low < high) {
    int pivot = ArrayDivider(arr, low, high);
    //pivot will now be in its correct position
    
    QuickSort(arr, low, pivot - 1);
    QuickSort(arr, pivot + 1, high);
    //Recursively calls this function to continue sorting elements until we are
    //at the beginning and end of the index respectively
  }
}

void SwapChar(char* a, char* b) {
  char temp = *a;
  *a = *b;
  *b = temp;
}

int ArrayDividerChar(char arr[], int low, int high) {
  //this function takes the last element as the pivot, places the pivot in its
  //correct position in a sorted array, and places all elements smaller than 
  //pivot to the left and greater than pivot to the right
  int j;
  char pivot = arr[high];
  int i = (low - 1);//index of smaller element

  for(j = low; j < high; j++) {
    if(arr[j] <= pivot) {
      i++;//increment index of smaller element
      SwapChar(&arr[i], &arr[j]);
    }
  }
  SwapChar(&arr[i + 1], &arr[j]);
  return(i + 1);
}

void QuickSortChar(char arr[], int low, int high) {
  //low and high will originally be the starting and ending indexes
  if(low < high) {
    int pivot = ArrayDividerChar(arr, low, high);
    //pivot will now be in its correct position
    
    QuickSortChar(arr, low, pivot - 1);
    QuickSortChar(arr, pivot + 1, high);
    //Recursively calls this function to continue sorting elements until we are
    //at the beginning and end of the index respectively
  }
}

void TwoDChar(int number, int size) {
  int i, j, choice, count = 0, instance;
  char letter;

  char myArray[number][size + 1];//+1 to include '\0' character
  for(i = 0; i < number; i++) {
    __fpurge(stdin);//this clears the input buffer of everything
    printf("\nEnter string %d: ", i + 1);
    fgets(myArray[i],size + 1, stdin);
    for(j = 0; j < size; j++) {
      if(myArray[i][j] == '\n') {
	myArray[i][j] = '\0';
      }//this for loop gets rid of the newline character from the strings
    }
  }

  printf("You have entered:\n");
  for(i = 0; i < number; i++) {
    printf("%s\n", myArray[i]);
  }

  do {
    printf("\n\nWhat would you like to do?\n");
    printf("1.\tCheck frequency of a letter\n");
    printf("2.\tRemove a letter\n");
    printf("3.\tReturn to Main Menu\n");
    printf(">>? ");

    scanf("%d", &choice);
    switch(choice) {
    case 1 :
      printf("\n\nWhat letter would you like to search for? ");
      scanf(" %c", &letter);
      printf("\n");

      for(i = 0; i < number; i++) {
	count = 0;
	for(j = 0; j < size; j++) {
	  if(myArray[i][j] == letter) {
	    count++;
	  }
	}
	printf("%s - %d\n", myArray[i], count);
      }
      break;
      
    case 2 :
      printf("What letter would you like to remove? ");
      scanf(" %c", &letter);
      printf("\n");

      for(i = 0; i < number; i++) {
	for(j = 0; j <= size; j++) {
	  if(myArray[i][j] == letter) {
	    instance = j;
	    if(instance == size) {//we are at the last element of the array
	      myArray[i][instance] = '\0';
	    }
	    else {
	      for(instance = j; instance < size; instance++) {
		myArray[i][instance] = myArray[i][instance + 1];
	      }
	      j--; //j must be decremented incase letters are sequential
	    }
	  }
	}
      }
      for(i = 0; i < number; i++) {
	printf("%s\n", myArray[i]);
      }
    break;

    case 3 :
      printf("Returning to the Main Menu!\n\n");
      break;

    default :
      printf("\nInvalid input, please try again.\n");
      break;
    }
  }
  while(choice != 3);

}

