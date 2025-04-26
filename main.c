#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct town {
    char townName [50];
    long population;
    struct town* nextTown;
    struct town* previousTown;
};
struct district {
    char  districtName [50];
    long totalPopulation;
    struct town * ptrToTown;
    struct district* nextDistrict;
    struct district* previousDistrict;

};

//town functions
struct town* createTown();
void addTown (char tName[50], long tPopulation, char dName [50], struct district* districtsList);
void addTownNode (struct town* myTown, struct town* townsList);
struct town* findTown(char tName [50],char dName [50], struct district* districtsList);
struct town* findLastTown (char dName [50], struct district* districtsList);
struct town* findLastCopiedTown (struct town* indexOfTownsArray);
struct town* findlastTownInDistrict (struct district* myDistrict, struct district* districtsList);//takes struct district, returns district if no towns
struct town* findMinTownInDistrict (struct district* myDistrict, struct district* districtsList);
void deleteTown(char tName [50], char dName [50],struct district* districtsList );
void deleteTownNode (struct town* myTown, struct town* townsList);
void deleteTownFromDistrict (struct town* myTown,struct district* myDistrict, struct district* districtsList);
void deleteTownsList (struct town* townsList);
void copyTownThenAdd(struct town* myTown, struct district* myDistrict,struct district* districtsList, struct town* indexOfTownsArray);
void changeTownPopulation (struct district* districtsList );
void sortTowns (struct district* districtsList);

//district functions
struct district* createDistrict ();
void addDistrict (char dName [50], struct district* districtsList);
void addDistrictNode(struct district* myDistrict, struct district* districtsList);
struct district* findDistrict (char dName [50], struct district* districtsList );
struct district* findLastDistrict(struct district* districtsList);
void deleteDistrict(char dName[50], struct district* districtsList);
void deleteDistrictNode (struct district* myDistrict, struct district* districtsList);
void deleteDistrictsList (struct district* districtsList);//not finished
struct district* copyDistrictData (struct district* myDistrict,struct district* districtsList);
void copyDistrictThenAdd(struct district* myDistrict,struct district* districtsList, struct district* indexOfDistrictsArray);
int isLastDistrict (struct district* myDistrict,struct district* districtsList);
void printDistrictsAndPopulation (struct district* districtsList);
void sortDistricts (struct district* districtsList);

//other functions
void myMenu(struct district* scannedDistrictsList,struct district* districtsList);
void loadInputs (struct district* scannedDistrictsList,struct district* districtsList);
void printLoadedInfo (struct district* scannedDistrictsList);
void printSortedInfo (struct district* districtsList);
void saveToFile (struct district* districtsList);
void palestinePopulation (struct district* districtsList);
void minPopulation (struct district* districtsList);
void minPopulation (struct district* districtsList);
int findNumberDigits (long number);

int main() {

    struct district* districtsList= createDistrict();
    struct district* scannedDistrictsList= createDistrict();

    myMenu(scannedDistrictsList,districtsList);

    return 0;
}
void myMenu(struct district* scannedDistrictsList,struct district* districtsList){
    char dName [50];
    char tName [50];
    struct district* myDistrict;

    //implement using recursion
    // wrong input case
    int myChoice=-1;
    do {
        printf("\nEnter Your Choice!\n");
        printf("1-Load the input file(Palestinian districts and their town with population)\n");
        printf ("2-Print the loaded information before sorting (as in the input file format)\n");
        printf ("3-Sort the districts alphabetically using Radix sort\n");
        printf ("4-Sort the towns for each district based on population in ascending order\n");
        printf ("5-Print the sorted information\n");
        printf ("6-Add a new district to the list of sorted districts (and sort the list)\n");
        printf ("7-Add a new town to a certain district (and sort the list)\n");
        printf ("8-Delete a town from a specific district\n");
        printf ("9-Delete a complete district\n");
        printf ("10-Calculate the population of Palestine, the max and min town population\n");
        printf ("11-Print the districts and their total population \n");
        printf ("12-Change the population of a town, after prompting the user to enter the district name\n");
        printf ("13-Save to output file\n");
        printf ("14-Exit\n\n");
        scanf("%d", &myChoice);
        getchar();//the user will have time to write the string
        switch(myChoice){
        case 1: loadInputs(scannedDistrictsList,districtsList);
        break;
        case 2: printLoadedInfo(scannedDistrictsList);
        break;
        case 3:sortDistricts(districtsList);
            printf("Districts were sorted!\n");
        break;
        case 4:sortTowns(districtsList);
                printf("Towns were sorted!\n");

        break;
        case 5:sortDistricts(districtsList);
            sortTowns(districtsList);
            printSortedInfo(districtsList);
        break;
        case 6:printf("Enter the district name: ");
            gets(dName);
            addDistrict(dName,districtsList);
            sortDistricts(districtsList);
            printf("District was added!\n");

        break;

        case 7:printf("Enter town's name: ");
            gets(tName);

            printf("Enter the district name: ");
            gets(dName);

            myDistrict=findDistrict(dName, districtsList);
            if (myDistrict==NULL){
                printf("Sorry, %s district is not existed\n", dName);
                break;
            }

            printf("Enter town's population\n");
            long tPopulation;
            scanf("%ld", &tPopulation);
            getchar();//the user will have time to write the string
            addTown(tName,tPopulation,dName,districtsList);
            sortTowns(districtsList);
            printf("Town was added!\n");

        break;

        case 8:printf("Enter town's name: ");
            gets(tName);

            printf("Enter the district name: ");
            gets(dName);

            if (myDistrict==NULL){
                printf("Sorry, %s district is not existed\n", dName);
                break;
            }
            deleteTown(tName,dName,districtsList);
            printf("Town was deleted!\n");

        break;
        case 9:printf("Enter the district name: ");
            gets(dName);
            deleteDistrict(dName,districtsList);
            printf("District was deleted!\n");
        break;
        case 10: palestinePopulation (districtsList);
            minPopulation(districtsList);
            maxPopulation (districtsList);

        break;
        case 11:printDistrictsAndPopulation(districtsList);
        break;
        case 12:changeTownPopulation(districtsList);
        break;
        case 13:saveToFile(districtsList);
        break;
        case 14:printf("You Are Welcome to use our program any time!\n");
            deleteDistrictsList(districtsList);//to free memory
        break;//exits

        //otherwise
        default: printf("Sorry, you may entered a wrong number, Try again\n");

        }
    }
    while (myChoice!=14);
}

//town functions
struct town* createTown(){
    //create the node of town (without) adding it to the list
    struct town* myTown;
    myTown= (struct town*)malloc(sizeof(struct town));
    if (myTown==NULL){
        printf("NO Free Memory");
        return;
    }
    else {
        myTown->nextTown=NULL;
        myTown->previousTown=NULL;
        return myTown;
    }
}
void addTown (char tName[50], long tPopulation, char dName [50], struct district* districtsList){
    //adds last; in order to load data as same as in the input file
    //myDistrict means a specific district, not all the list

    struct district* myDistrict= findDistrict(dName,districtsList);

    //if the district is not already existed
    if (myDistrict==NULL){
        //we create a new district
        //this usage helps while reading from file
        //bit if the user tried to add a town to not existed district, I will prevent him from mainMenu
        addDistrict(dName,districtsList);
        myDistrict= findDistrict(dName,districtsList);
    }
    //must ensure that there is a district before searching for a town
    struct town* myTown;


    //if there is a district having no towns--add the first town
    if (myDistrict->ptrToTown==NULL){
        myTown= createTown();
        strcpy(myTown->townName,tName);
        myTown->population= tPopulation;
        (myDistrict->totalPopulation)+=tPopulation;//add town population to total population of the district
        myDistrict->ptrToTown= myTown;
        myTown->nextTown=NULL;
        myTown->previousTown= myDistrict;
        return;//to exit
    }

    //if the town is already existed
    myTown= findTown(tName,myDistrict,districtsList);
    if (myTown!=NULL){
        printf("%s town is already existed\n",tName);
        return;//to exit
    }

    //means the district has towns, and the town is not already existed
    struct town* lastTown= findLastTown(myDistrict,districtsList);
    myTown= createTown();
    strcpy(myTown->townName,tName);
    myTown->population= tPopulation;
    (myDistrict->totalPopulation)+=tPopulation;//add town population to total population of the district
    myTown->nextTown=NULL;
    myTown->previousTown= lastTown;
    lastTown->nextTown= myTown;

}
void addTownNode (struct town* myTown, struct town* townsList){
    //adds last

   if (myTown==NULL || townsList==NULL){
        return;
   }

    //must add a copy of my town, imagine if the original node was deleted!!
    //see this line at addDistrict Node

    struct town* lastAddedTown= findLastCopiedTown(townsList);



    //note, findLast returns the head if no towns were added
    //else, there are towns were added
    lastAddedTown->nextTown=myTown;
    myTown->previousTown= lastAddedTown;
    myTown->nextTown=NULL;


}
struct town* findTown(char tName [50],char dName [50], struct district* districtsList){
    struct district* myDistrict= findDistrict(dName,districtsList);
    if (myDistrict==NULL){
        printf("The district is not existed\n");
        return NULL;//if district is not existed
    }
    struct town* temp=myDistrict->ptrToTown;
    while(temp!=NULL){
        if (strcmpi(temp->townName,tName)==0){//strcmpi is with ignoring case
            return temp;//town is found
        }
        temp=temp->nextTown;
    }
    return NULL;//if town is not found
}
struct town* findLastTown (char dName [50], struct district* districtsList){
    struct district* myDistrict= findDistrict(dName,districtsList);
    if (myDistrict==NULL){
        printf("%s district is not existed\n",dName);
        return NULL;//if district is not existed
    }
    if (myDistrict->ptrToTown==NULL){
        printf("%s district has no towns\n", dName);
        return NULL;//if district is existed but has no towns
    }
    //to reach here, ensures that there are towns in this district
    struct town* temp=myDistrict->ptrToTown;
    while (temp->nextTown!=NULL){
        temp=temp->nextTown;
    }
    return temp;//returns the last town
}
struct town* findLastCopiedTown (struct town* indexOfTownsArray){
    if (indexOfTownsArray == NULL) {
        printf("Your List is a NULL list\n");
        return NULL;
    }


    struct town* myTown= indexOfTownsArray;

    while (myTown->nextTown!=NULL){
        myTown=myTown->nextTown;
    }
    return myTown;//returns header if no towns ere added

}
struct town* findlastTownInDistrict (struct district* myDistrict, struct district* districtsList){
    //takes struct district, returns district if no towns
    if (myDistrict==NULL){
        return NULL;//if district is not existed
    }

    if (myDistrict->ptrToTown==NULL){
        return myDistrict;//if district is existed but has no towns
    }

    //to reach here, ensures that there are towns in this district
    struct town* temp=myDistrict->ptrToTown;
    while (temp->nextTown!=NULL){
        temp=temp->nextTown;
    }
    return temp;//returns the last town

}
struct town* findMinTownInDistrict (struct district* myDistrict, struct district* districtsList){
    if (myDistrict==NULL || districtsList== NULL){
        return NULL;
    }
    struct town* temp=myDistrict->ptrToTown;
    if (temp==NULL){
        return NULL;
    }

    //there are towns
    char tName [50]="";

    long minNumber= 2147483647;//this is the largest signed long value
    while(temp!=NULL){
        if (temp->population<minNumber){
            minNumber=temp->population;
            strcpy(tName, temp->townName);
        }
        temp=temp->nextTown;
    }
    struct town* minTown= findTown(tName, myDistrict->districtName,districtsList);

    return minTown;
}
void deleteTown(char tName [50], char dName [50],struct district* districtsList ){
    struct district* myDistrict= findDistrict(dName,districtsList);
    if (myDistrict==NULL){
        //the district is not already existed
        printf("%s district is not already existed\n", dName);
        return;
    }
    struct town* temp= findTown(tName,dName,districtsList);

    //if town is not existed
    if (temp==NULL){
        printf("%s town is not already existed\n",tName);
        return;
    }

    //if it is the first town
    if (temp->previousTown==myDistrict){
        myDistrict->ptrToTown=temp->nextTown;
         //we supposed that first town will direct previousTown pointer to the district
        //so, we must check before trying to access pointers
    }
    else {
        //means it is in the middle or last//in Both case, no it has a previous town
        temp->previousTown->nextTown= temp->nextTown;
    }


    //if it is NOT the last town
    if (temp->nextTown!=NULL){//to ensure that the town i delete is not the last
            //if last, then no next node having a pointer to previous
        temp->nextTown->previousTown= temp->previousTown;
    }

    (myDistrict->totalPopulation)-= (temp->population);//reduce the district's population
    free (temp);//I want to delete it
}
void deleteTownNode (struct town* myTown, struct town* townsList){
     //using while deleting in sorting,
    //I am sure that the node is existed


    struct town* myPreviousTown= myTown->previousTown;
    myPreviousTown->nextTown= myTown->nextTown;
    if (myTown->nextTown!= NULL){
        (myTown->nextTown)->previousTown= myPreviousTown;
    }
    free(myTown);

}
void deleteTownFromDistrict (struct town* myTown,struct district* myDistrict, struct district* districtsList){

    //if it is the first town
    if (myTown->previousTown==myDistrict){
        myDistrict->ptrToTown=myTown->nextTown;
         //we supposed that first town will direct previousTown pointer to the district
        //so, we must check before trying to access pointers
    }
    else {
        //means it is in the middle or last//in Both case, no it has a previous town
        myTown->previousTown->nextTown= myTown->nextTown;
    }



    //if it is NOT the last town
    if (myTown->nextTown!=NULL){//to ensure that the town i delete is not the last
            //if last, then no next node having a pointer to previous
        myTown->nextTown->previousTown= myTown->previousTown;
    }

    (myDistrict->totalPopulation)-= (myTown->population);//reduce the district's population
    free (myTown);
}
void deleteTownsList (struct town* townsList){
    //here, we delete all towns but we keep the header

    if (townsList==NULL){
        return;//no existed list
    }

    //deletes from first (the town after the header)
    struct town* temp= townsList->nextTown;//first town
    if (temp==NULL){
        return;//there are no towns
    }
    //else
    while (temp!=NULL){
        deleteTownNode(temp,townsList);//deletes first town after the header
        temp=temp->nextTown;
    }
}
void copyTownThenAdd(struct town* myTown, struct district* myDistrict,
                     struct district* districtsList, struct town* indexOfTownsArray){
    if (myTown==NULL || myDistrict==NULL ){
        printf("Sorry, town is not existed\n");
        return;
    }

    //copy name and total Population
    struct town* copiedTown= createTown();
    strcpy(copiedTown->townName, myTown->townName);
    copiedTown->population= myTown->population;

    //adds last

    /*no need to check if already existed, there will not be duplicated data: the source is my original linked list
    and there are no duplicated data in it*/

    //indexOfTownsArray: represents a linked last locates at an index of the array of linked lists to be sorted

    //adds at the last of copiedtown
    struct town* lastAddedTown= findLastCopiedTown(indexOfTownsArray);
    //if no towns were added, lastAddedTown= header= indexOfTownsArray
    lastAddedTown->nextTown=copiedTown;
    copiedTown->previousTown= lastAddedTown;
    copiedTown->nextTown=NULL;
}
void changeTownPopulation ( struct district* districtsList ){
    printf("Enter district name\n");
    char dName [50];
    gets(dName);
    struct district* myDistrict= findDistrict(dName,districtsList );
    //if district is not existed
    if (myDistrict==NULL){
        printf("%s district is not existed\n", dName);
        return;
    }

    printf("Enter town name\n");
    char tName [50];
    gets(tName);
    struct town* myTown= findTown(tName,myDistrict,districtsList);
    //if town is not existed
    if (myTown==NULL){
        printf("%s town is not existed\n", tName);
        return;
    }
    //else
    printf("Enter the new population\n");
    long newPopulation;
    scanf("%ld", &newPopulation);
    getchar();//the user will have time to write the string

    //changing district population
    myDistrict->totalPopulation -= myTown->population;//reduce the district population by (old town population)
    myTown->population=newPopulation;
    myDistrict->totalPopulation += myTown->population;//add (new town population) to the district population

}
void sortTowns (struct district* districtsList){
    if (districtsList==NULL){
        return;//no linked list
    }

    struct district* myDistrict= districtsList->nextDistrict;
    if (myDistrict==NULL){
        return;//no districts
    }

    while(myDistrict!=NULL){//there are districts

        struct town* myTown= myDistrict->ptrToTown;
        while(myTown!=NULL){//there are towns in this district

            struct town* tempTown= myTown->nextTown;

            while (tempTown!=NULL){// if ==NULL, there is unique town, do not change anything


                if (tempTown->population < myTown->population){//we will swap them
                    struct town* swap= createTown();
                    strcpy(swap->townName, myTown->townName);
                    swap->population= myTown->population;

                    strcpy(myTown->townName, tempTown->townName);
                    myTown->population= tempTown->population;

                    strcpy(tempTown->townName, swap->townName);
                    tempTown->population= swap->population;
                    free(swap);

                }
                tempTown=tempTown->nextTown;

            }
            myTown=myTown->nextTown;
        }

    myDistrict=myDistrict->nextDistrict;
    }
}

//district functions
struct district* createDistrict (){
    struct district* myDistrict;
    myDistrict= (struct district*)malloc(sizeof(struct district));
    if (myDistrict==NULL){
        printf("NO Free Memory");
        return;
    }
    else {
        myDistrict->ptrToTown= NULL;
        myDistrict->nextDistrict=NULL;
        myDistrict->previousDistrict=NULL;
        return myDistrict;
    }
}
void addDistrict (char dName [50], struct district* districtsList){
    //adds last

    //checks if district is already existed
    struct district* myDistrict= findDistrict(dName,districtsList);
    if (myDistrict!=NULL){
        printf("%s district is already existed\n",dName);
        return;
    }
    //else
    myDistrict= createDistrict();
    strcpy(myDistrict->districtName,dName);
    myDistrict->totalPopulation=0;//will increase after adding towns
    myDistrict->ptrToTown= NULL;//it is also set in createDistrict

    //adds at the last of districtsList
    struct district* lastDistrict= findLastDistrict(districtsList);
    lastDistrict->nextDistrict=myDistrict;
    myDistrict->previousDistrict= lastDistrict;
    myDistrict->nextDistrict=NULL;
}
void addDistrictNode(struct district* myDistrict, struct district* districtsList){
    //adds last

   if (myDistrict==NULL || districtsList==NULL){
    return;
   }

   //must add a copy of my District, imagine if the original node was deleted!!
    //struct district* copiedDistrict= copyDistrictData(myDistrict, districtsList);//test commenting
    struct district* lastAddedDistrict= findLastDistrict(districtsList);

    //note, findLast returns the head if no districts were added
    //else, there are districts were added

    lastAddedDistrict->nextDistrict=myDistrict;
    myDistrict->previousDistrict= lastAddedDistrict;
}
struct district* findDistrict (char dName [50], struct district* districtsList ){
    struct district* temp= districtsList->nextDistrict;
    while (temp!=NULL ){
        //when strcmpi=0, two names are equal, district is found
        if (strcmpi(temp->districtName,dName)==0){
            return temp;//district is found
            /*this if condition must be nested,
            we have to be sure that temp!= NULL first,
            then we check the name,, if we check strcmp before the loop,,
            the string name might be to NULL if temp=NULL
            */
        }
        temp= temp->nextDistrict;
    }
    return NULL;//returns NULL if not found
}
struct district* findLastDistrict( struct district* districtsList){
    struct district* myDistrict= districtsList;
    /*
    if (myDistrict->nextDistrict==NULL){
        printf("There are no districts existed\n");
        return ;
    }
    */
    while (myDistrict->nextDistrict!=NULL){
        myDistrict=myDistrict->nextDistrict;
    }
    return myDistrict;//returns header if no districts existed
}
void deleteDistrict(char dName[50], struct district* districtsList){
    struct district* myDistrict= findDistrict(dName,districtsList);

    //check if it is not already existed
    if (myDistrict==NULL){
        printf("%s district is not already existed\n",dName);
        return;
    }
    //else if existed

    //STEP 1: delete its towns
    struct town* temp;
    struct town* p= myDistrict->ptrToTown;//access the first town in the district
    myDistrict->ptrToTown=NULL;//disconnect the district and its first town
    while (p != NULL){
        temp=p->nextTown;
        free(p);
        p=temp;
    }

    //STEP 2: delete district node
    struct district* myPreviousDistrict= myDistrict->previousDistrict;
    myPreviousDistrict->nextDistrict= myDistrict->nextDistrict;

    if (myDistrict->nextDistrict!= NULL){
        (myDistrict->nextDistrict)->previousDistrict= myPreviousDistrict;
    }
    free(myDistrict);

}
void deleteDistrictNode (struct district* myDistrict, struct district* districtsList){
    //using while deleting in sorting,
    //so we do not decrement PALESTINE_POPULATION

    //I am sure that the node is existed
    //STEP 1: delete its towns
    struct town* temp;
    struct town* p= myDistrict->ptrToTown;//access the first town in the district
    myDistrict->ptrToTown=NULL;//disconnect the district and its first town
    while (p != NULL){
        temp=p->nextTown;
        free(p);
        p=temp;
    }

    //STEP 2: delete district node
    struct district* myPreviousDistrict= myDistrict->previousDistrict;
    myPreviousDistrict->nextDistrict= myDistrict->nextDistrict;
    if (myDistrict->nextDistrict!= NULL){
        (myDistrict->nextDistrict)->previousDistrict= myPreviousDistrict;
    }
    free(myDistrict);
}
void deleteDistrictsList (struct district* districtsList){

    //here, we delete all districts but we keep the header

    if (districtsList==NULL){
        return;//no existed list
    }

    //deletes from first (the district after the header)
    struct district* temp= districtsList->nextDistrict;//first district
    if (temp==NULL){
        return;//there are no districts
    }
    //else
    while (temp!=NULL){
        deleteDistrictNode(temp,districtsList);
        temp=districtsList->nextDistrict;
    }
}
struct district* copyDistrictData (struct district* myDistrict,struct district* districtsList){
    if (myDistrict==NULL || districtsList==NULL){
        printf("Sorry, district is not existed\n");
        return NULL;
    }

    //copy name and total Population
    struct district* copiedDistrict= createDistrict();
    strcpy(copiedDistrict->districtName, myDistrict->districtName);
    copiedDistrict->totalPopulation= myDistrict->totalPopulation;

    //copying towns to my copied district
    struct town* tempTown= myDistrict->ptrToTown;
    if (tempTown==NULL){
        return copiedDistrict;//returns the copied district which has no towns
    }
    struct town* copiedTown;//the town block that we will connect with copied district
    struct town* ptrToLastTownAdded=createTown();

    //here we add the first town to copied district
    copiedTown=createTown();
    strcpy(copiedTown->townName,tempTown->townName);
    copiedTown->population= tempTown->population;
    copiedDistrict->ptrToTown= copiedTown;
    copiedTown->previousTown=copiedDistrict;
    ptrToLastTownAdded->nextTown=copiedTown;

    //here we will connect other towns
    tempTown= myDistrict->ptrToTown;
    if (tempTown->nextTown==NULL){//check the second town
        return copiedDistrict;//returns if  there is just one town
    }
    //else
    //means that there are towns (or town) after the first town
    tempTown= tempTown->nextTown;//accessing the next town
    while (tempTown!=NULL){
        copiedTown=createTown();
        strcpy(copiedTown->townName,tempTown->townName);
        copiedTown->population= tempTown->population;

        (ptrToLastTownAdded->nextTown)->nextTown=copiedTown;//last town directs its next- town pointer to new copied town
        //ptrToLastTownAdded->nextTown : this is last town
        copiedTown->previousTown=ptrToLastTownAdded->nextTown;

        ptrToLastTownAdded->nextTown= (ptrToLastTownAdded->nextTown)->nextTown;//increment position to reach new last town

        //finally, loop increment position, to add other towns
        tempTown=tempTown->nextTown;
    }

    return copiedDistrict;//which has all towns
}
void copyDistrictThenAdd (struct district* myDistrict,struct district* districtsList, struct district* indexOfDistrictsArray){

    //no increment for PALESTINE_POPULATION here
    if (myDistrict==NULL || districtsList==NULL){
        printf("Sorry, district is not existed\n");
        return;
    }

    //copy name and total Population
    struct district* copiedDistrict= createDistrict();
    strcpy(copiedDistrict->districtName, myDistrict->districtName);
    copiedDistrict->totalPopulation= myDistrict->totalPopulation;

    //copying towns to my copied district
    struct town* tempTown= myDistrict->ptrToTown;
    if (tempTown!=NULL){

        struct town* copiedTown;//the town block that we will connect with copied district
        struct town* ptrToLastTownAdded=createTown();

        //here we add the first town to copied district
        copiedTown=createTown();
        strcpy(copiedTown->townName,tempTown->townName);
        copiedTown->population= tempTown->population;
        copiedDistrict->ptrToTown= copiedTown;
        copiedTown->previousTown=copiedDistrict;
        ptrToLastTownAdded->nextTown=copiedTown;

        //here we will connect other towns
        tempTown= myDistrict->ptrToTown;
        if (tempTown->nextTown!=NULL){//check the second town

            //means that there are towns (or town) after the first town
            tempTown= tempTown->nextTown;//accessing the next town
            while (tempTown!=NULL){
                copiedTown=createTown();
                strcpy(copiedTown->townName,tempTown->townName);
                copiedTown->population= tempTown->population;

                (ptrToLastTownAdded->nextTown)->nextTown=copiedTown;//last town directs its next- town pointer to new copied town
                //ptrToLastTownAdded->nextTown : this is last town
                copiedTown->previousTown=ptrToLastTownAdded->nextTown;

                ptrToLastTownAdded->nextTown= (ptrToLastTownAdded->nextTown)->nextTown;//increment position to reach new last town

                //finally, loop increment position, to add other towns
                tempTown=tempTown->nextTown;
            }
        }
    }

    //adds last

    /*no need to check if already existed, there will not be duplicated data: the source is my original linked list
    and there are no duplicated data in it*/

    //indexOfDistrictsArray: represents a linked last locates at an index of the array of linked lists to be sorted

    //adds at the last of copiedDistrict

    struct district* lastAddedDistrict= findLastDistrict(indexOfDistrictsArray);

    //if no towns were added, lastAddedTown= header= indexOfTownsArray


    //else, there are districts were added
    lastAddedDistrict->nextDistrict=copiedDistrict;
    copiedDistrict->previousDistrict= lastAddedDistrict;
    //copiedDistrict->nextDistrict=NULL;//edited, no need
}
int isLastDistrict (struct district* myDistrict,struct district* districtsList){
    return myDistrict->nextDistrict==NULL;
}
void printDistrictsAndPopulation (struct district* districtsList){
    if (districtsList==NULL||districtsList->nextDistrict==NULL){
        printf("There are no districts!\n");
        return;
    }
    struct district* myDistrict= districtsList->nextDistrict;

    while (myDistrict!=NULL){

        printf("%s District, Total District Population= %ld\n", myDistrict->districtName,myDistrict->totalPopulation);
        myDistrict=myDistrict->nextDistrict;
    }
    printf("\n");
}
void sortDistricts (struct district* districtsList){
    struct district* districtsArray [53]= {NULL};

    int max_digits=0;

    struct district* myDistrict= districtsList->nextDistrict;
    if (myDistrict==NULL) {
        printf("There are no districts to sort\n");
        return;
    }

    //find Max string length
    while (myDistrict!=NULL){
        int length= strlen(myDistrict->districtName);
        if (length>max_digits){
            max_digits= length;
        }
        myDistrict= myDistrict->nextDistrict;
    }

    int counter= max_digits;//counter means that i will compare the JTh char

    for (int i=0; i<max_digits; i++) {//outer loop

        // Reset the districtsArray
        for (int j=0;j<53;j++){
            districtsArray[j]= createDistrict();
        }
        //the 53Th row is for adding the short strings that we will not compare at JTh loop turn

        // for (max digits) times, we start from the first district
        myDistrict= districtsList->nextDistrict;
        while (myDistrict!=NULL){

            int str_length= strlen (myDistrict->districtName);
            if (str_length<counter){//ex: i will not compare the 5th char of 3-digit string
                // add to 53Th row
                copyDistrictThenAdd(myDistrict,districtsList, districtsArray[52]);//52 is the 53Th row
            }

            else {//else means that i have a char to compare

                    char checker= (myDistrict->districtName)[counter-1];//access the needed char (counterTh char= counter -1)
                    int index;
                    if (checker >= 'A' && checker <= 'Z'){//Capital Letter
                        index= checker - 'A';// A=65, starts from A
                        copyDistrictThenAdd(myDistrict,districtsList, districtsArray[index]);
                    }

                    else if (checker >= 'a' && checker <= 'z') {//Small Letters
                        index= checker - 'A' - (6);// a=97// 27Th row// [26] = (checker ASCII) - 'A' - 6
                        copyDistrictThenAdd(myDistrict,districtsList, districtsArray[index]);
                    }
                    else {
                        copyDistrictThenAdd(myDistrict,districtsList, districtsArray[52]);//52 is the 53Th row
                    }
            }

            myDistrict= myDistrict->nextDistrict;//incrementing the loop
        }


        //delete the list then store the partially- sorted data in the linked List
        deleteDistrictsList(districtsList);//deleting the original district list

        for (int j=0;j<53; j++){//constructing the partially- sorted linked list
            addDistrictNode( (districtsArray[j]->nextDistrict),districtsList);
        }

        //freeing each index of the array without deleting districts were added to it
        for (int k=0; k<53; k++){
            free(districtsArray[k]);
        }

        //decrement to check more letters
        counter--;
    }

}


//other functions
void loadInputs (struct district* scannedDistrictsList,struct district* districtsList){
    FILE *input;
    input= fopen("districts.txt","r");
    char scannedLine [150];
    char *valid= fgets(scannedLine,50,input);
    //fgets returns NULL when the file is over

    char scannedInputs [3][50];
    //[0]=district name // 1]=town name // [2]=town population

    while (valid!= NULL) {//as long as lines are not over

        char *p= strtok(scannedLine, "|");
        int counter =0;
        while (p!=NULL){
            strcpy(scannedInputs[counter],p);
            counter++;
            p=strtok(NULL,"|");//NULL is set where "|" is found

        }
        long scannedPopulation= strtol(scannedInputs[2], NULL, 10);//strtol converts from string to long
        addTown(scannedInputs[1], scannedPopulation,scannedInputs[0],districtsList);
        addTown(scannedInputs[1], scannedPopulation,scannedInputs[0],scannedDistrictsList);

        //once for districtsList & once for scannedDistrictsList
        //so to avoid adding the same town's population twice
        valid= fgets(scannedLine,50,input);//for the next line
    }
    fclose(input);
    printf("Data was loaded from input file\n");

}
void printLoadedInfo (struct district* scannedDistrictsList){
    if (scannedDistrictsList==NULL){
        printf("Data was not loaded from the input file!!\n");
        return;
    }
    struct district* myDistrict= scannedDistrictsList->nextDistrict;
    struct town* myTown;
    while (myDistrict!=NULL){
        myTown= myDistrict->ptrToTown;
        while(myTown!=NULL){
            printf("%s|%s|%ld\n", myDistrict->districtName,myTown->townName,myTown->population);
            myTown=myTown->nextTown;
        }
        myDistrict=myDistrict->nextDistrict;

    }
    printf("\n");
}
void printSortedInfo (struct district* districtsList){
    if (districtsList==NULL){
        printf("Data was not loaded from the input file!!\n");
        return;
    }
    struct district* myDistrict= districtsList->nextDistrict;
    struct town* myTown;
    while (myDistrict!=NULL){
        myTown= myDistrict->ptrToTown;
        if (myTown!=NULL){//has towns
        while(myTown!=NULL){
            printf("%s|%s|%ld\n", myDistrict->districtName,myTown->townName,myTown->population);
            myTown=myTown->nextTown;
        }
        }
        else {//print District name which has no towns
            printf("%s| |%ld\n", myDistrict->districtName,myDistrict->totalPopulation );
        }
        myDistrict=myDistrict->nextDistrict;

    }
    printf("\n");

}
void saveToFile (struct district* districtsList){
    FILE *output;
    output= fopen("sorted_districts.txt", "w");
    struct district* myDistrict= districtsList->nextDistrict;
    while (myDistrict!=NULL){//while there are districts
        fprintf(output,"%s District, Population= %ld\n",myDistrict->districtName,myDistrict->totalPopulation);

        struct town* myTown= myDistrict->ptrToTown;
        while (myTown!=NULL){//while there are towns
            fprintf(output,"%s, %ld\n",myTown->townName, myTown->population);
            myTown=myTown->nextTown;
        }
        fprintf(output,"\n");
        myDistrict=myDistrict->nextDistrict;
    }
}
void palestinePopulation (struct district* districtsList){
    long population=0;
    struct district* myDistrict= districtsList->nextDistrict;
    while( myDistrict!=NULL){
        population += myDistrict->totalPopulation;
        myDistrict= myDistrict->nextDistrict;
    }
    printf("Palestine's Total Population = %ld\n",population );
}
void minPopulation (struct district* districtsList){
    struct district* myDistrict= districtsList->nextDistrict;
    if (myDistrict==NULL){
        printf("There are no towns\n");
        return;
    }

    struct town* minTown= createTown();
    minTown->population=2147483647;//this is the largest signed long value

    int checker=0;//to check if there are towns

    while (myDistrict!=NULL){
        struct town* myTown= myDistrict->ptrToTown;
        if (myTown!=NULL){
            checker++;
        }
        while(myTown!=NULL){

            if (myTown->population < minTown->population){
                strcpy(minTown->townName, myTown->townName);
                minTown->population= myTown->population;
            }
            myTown=myTown->nextTown;
        }
        myDistrict= myDistrict->nextDistrict;
    }

    if (checker==0){
        printf("There are no towns\n");
        free(minTown);
        return;

    }

    printf("Minimum town is %s , Town Population = %ld\n", minTown->townName, minTown->population);
    free(minTown);
}
void maxPopulation (struct district* districtsList){
    struct district* myDistrict= districtsList->nextDistrict;
    if (myDistrict==NULL){
        printf("There are no towns\n");
        return;
    }

    struct town* maxTown= createTown();
    maxTown->population= -1;//there will not be negative population

    int checker=0;//to check if there are towns

    while (myDistrict!=NULL){
        struct town* myTown= myDistrict->ptrToTown;
        if (myTown!=NULL){
            checker++;
        }
        while(myTown!=NULL){

            if (myTown->population > maxTown->population){
                strcpy(maxTown->townName, myTown->townName);
                maxTown->population= myTown->population;
            }
            myTown=myTown->nextTown;
        }
        myDistrict= myDistrict->nextDistrict;
    }

    if (checker==0){
        printf("There are no towns\n");
        free(maxTown);
        return;

    }

    printf("Maximum town is %s , Town Population %ld\n", maxTown->townName, maxTown->population);
    free(maxTown);
}
int findNumberDigits (long number){
    int digits=0;

    if (number==0){
        return 1;//handling the cae
    }

    //if number is negaive
    if (number<0){
        number= -number;
    }

    while (number>0){
        number/=10;
        digits++;
    }
    return digits;
}












