#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

#define PERSON_SIZE  100

typedef struct person{
	char firstname[100];
	char lastname[100];
	char phonenumber[100];
} Person;

int count = 0;
Person * people[PERSON_SIZE];

void insertToStruct();
void display();
void createPhonebook(char[]);
void doSort();
void randomizedQuickSort(int,int);
void swap(int,int);
int partitionStruct(int,int);
int comparePeople(Person*,Person*);
void searchPerson();
int binarySearch(int,int,char[]);
void deletePerson();
void freeMemory();

int main(int argc, char *argv[]){
	int choice = 0;
	createPhonebook(argv[1]);
	do{
		choice = 0;
		printf("\nEnter Choice \n");
		printf("1) sort_contact \n");
		printf("2) search \n");
		printf("3) delete \n");
		printf("4) insert \n");
		printf("Enter Choice more than 4 to Exit. Your choice now Please: \n");
		scanf(" %d",&choice);
		switch(choice){
			case 1 :
				printf("\nContent after Sorting:\n");
				doSort();
				display();
				break;
			case 2 :
				searchPerson();
				break;
			case 3 :
				deletePerson();
				break;
			case 4 : 
				insertToStruct();
				break;
			default:
				printf("Please enter value between 1 and 4.Exiting now...\n");
				freeMemory();
				return -1;
		}
	}while(choice > 0 && choice < 5);
	return 0;
}

//Function to free the used Memory
void freeMemory(){
	for(int i=0;i<count;i++){
		free(people[i]);
	}
	while(count == 0){
		count--;
	}
}

//Function to delete an entry
void deletePerson(){
	char toDelete[100]="",fname[100],lname[100];
	int check = 0;
	printf("Enter the Full Name ->\n");
	scanf("%s%s",fname,lname);
	strcat(toDelete,fname);
	strcat(toDelete, " ");
	strcat(toDelete,lname);
	strcat(toDelete,",");
	doSort();	
	int result = binarySearch(0,count-1,toDelete);
	printf("\n");
	printf("Content after deletion: \n");
	if(result == -1){
		printf("Name not Found\n");
		toDelete[0] = 0;
	}else{
		swap(result,count-1);
		free(people[count-1]);
		count--;
		toDelete[0] = 0;
		doSort();
		display();
	}
}

//Function to search an entry
void searchPerson(){
	char toSearch[100] = "",fname[100],lname[100];
	printf("Enter the Full Name ->\n");
	scanf("%s%s",fname,lname);
	strcat(toSearch,fname);
	strcat(toSearch, " ");
	strcat(toSearch,lname);
	strcat(toSearch,",");
	int result = binarySearch(0,count-1,toSearch);
	printf("\n");
	printf("Searched Content: \n");
	if(result == -1){
		printf("Name not Found\n");
		toSearch[0] = 0;	
	}else{
		printf("%s %s %s found at the location %d\n", people[result]->firstname,people[result]->lastname,people[result]->phonenumber,result+1);
		toSearch[0] = 0;
	}
}

//Function which does Binary Search logic
int binarySearch(int low,int high, char toSearch[]){
	char fullname[100] = "";
	if(low <= high){
		int mid =  low + (high - low)/2;
		strcat(fullname,people[mid]->firstname);
		strcat(fullname, " ");
		strcat(fullname,people[mid]->lastname);
		if(strcmp(toSearch,fullname) == 0){
			fullname[0] = 0;
			return mid;	
		}else{
			if(strcmp(fullname,toSearch)<0){
				return binarySearch(mid+1,high,toSearch);
			}else{
				return binarySearch(low,mid-1,toSearch);
			}
		}
	}
	return -1;
}

//Function to sort all the entries
void doSort(){
	randomizedQuickSort(0,count-1);
}


//Function which does Randomised quick sort
void randomizedQuickSort(int start,int end){
	if(start < end){
                srand(time(NULL));
                int random = start + rand()%(end + 1 -start);
                swap(random,end);
               	int pIndex = partitionStruct(start,end);
		randomizedQuickSort(start,pIndex-1);
                randomizedQuickSort(pIndex+1,end);
        }
}

//Function to find partition to perform quick sort in that partition
int partitionStruct(int start, int end){
	Person *pivot = people[end];
	int pIndex = start;
	
	for(int i=start;i<=end-1;i++){
                if(comparePeople(people[i],pivot) < 0){
                        swap(i,pIndex);
                        pIndex = pIndex + 1;
                }
        }
        swap(pIndex,end);
        return pIndex;
}

//Function to compare the equalness of 2 entries
int comparePeople(Person*  person1, Person*  person2){
	if(strcmp(person1->firstname,person2->firstname) == 0){
		if(strcmp(person1->lastname,person2->lastname) == 0){
			return strcmp(person1->phonenumber,person2->phonenumber);
		}else{
			return strcmp(person1->lastname,person2->lastname);
		}
	}else{
		return strcmp(person1->firstname,person2->firstname);
	}
}

//Function to swap 2 records
void swap(int record1,int record2){
	Person * temp = people[record1];
	people[record1] = people[record2];
	people[record2] = temp; 
}

//Function to read from file and create the struct to work upon
void createPhonebook(char fileName[]){
	char line[500];
	
	FILE *file = fopen(fileName,"r");
	if(file == NULL){
		printf("Error! Could not find the phonebook\n");
		exit(-1);
	}
	while(fgets(line, sizeof line,file)!=NULL){
		people[count] = malloc(sizeof(Person));
		sscanf(line,"%s%s%s", people[count]->firstname,people[count]->lastname,people[count]->phonenumber);
		count++;
	}
	fclose(file);
}

//Function to insert a new entry
void insertToStruct(){
	printf("Enter the Full Name and Phone Number->\n");
	people[count] = malloc(sizeof(Person));
	scanf("%s%s%s", people[count]->firstname,people[count]->lastname,people[count]->phonenumber);
	count++;
	doSort();
	printf("\n");
	printf("Content after insertion\n");
	display();
}

//Function to display all the entries
void display(){
	printf("\n");
	for(int i = 0;i < count;i++){
		printf("%s %s %s\n",people[i]->firstname,people[i]->lastname,people[i]->phonenumber);	
	}
}
