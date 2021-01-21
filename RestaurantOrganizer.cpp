/*
Student Name:Salih Bedirhan EKER
Student Number:2017400030
Project Number: 2
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "RestaurantOrganizer.h"

using namespace std;


static int myHeap[100042];
static int myTableCapacity[100042];

RestaurantOrganizer::RestaurantOrganizer(const vector<int>& tableCapacityInput){    // prepares initial heap and table capacities
    numberOfTables = tableCapacityInput.size();
    for(int i=0;i<numberOfTables;i++){
        myTableCapacity[i + 1] = tableCapacityInput[i];
        myHeap[i + 1] = i + 1;
        heapUp(i+1);
    }

}

void RestaurantOrganizer::addNewGroup(int groupSize, ofstream& outFile){        // when a group comes it assign them a table and decreases the tables capacity
    // IMPLEMENT ME!
    if(groupSize > myTableCapacity[myHeap[1]]){
        outFile<<-1<<endl;
    }else{
        outFile << myHeap[1] - 1 << endl;
        myTableCapacity[myHeap[1]] = myTableCapacity[myHeap[1]] - groupSize;
        heapDown(1);
    }
}

void RestaurantOrganizer::heapUp(int index){                                    // it keep the heap with proper order
    // IMPLEMENT ME!
    while((myTableCapacity[myHeap[index]] > myTableCapacity[myHeap[index / 2]]) && index > 1){
        int temp = myHeap[index / 2];
        myHeap[index / 2] = myHeap[index];
        myHeap[index] = temp;

        index = index/2;
    }
}

void RestaurantOrganizer::heapDown(int index){                                  // when a tables capacity decreased it finds and assigns a suitable place in the heap for the table
    // IMPLEMENT ME!
    int max = myTableCapacity[myHeap[index]];
    int control = 0;                                                           // it is used when table capacities are equal

    if(numberOfTables < index*2){                                               // base case. When it is last table to check returns
        return;
    }else if (numberOfTables == index*2){                                       // another base case. When last element of the heap it make the necessary changes and returns
            if(myTableCapacity[myHeap[index*2]] > myTableCapacity[myHeap[index]]){
                int temp = myHeap[index];
                myHeap[index] = myHeap[index * 2];
                myHeap[index * 2] = temp;
            }else if(myTableCapacity[myHeap[index*2]] == myTableCapacity[myHeap[index]]){
                if(myHeap[index*2] < myHeap[index]){
                    int temp = myHeap[index];
                    myHeap[index] = myHeap[index * 2];
                    myHeap[index * 2] = temp;
                }
            }
            return;
    }

    if(myTableCapacity[myHeap[index * 2]] > max) {
        max = myTableCapacity[myHeap[index * 2]];
    }else{
        if(myTableCapacity[myHeap[index * 2]] == max){
            control ++;
        }
    }
    if(myTableCapacity[myHeap[(index * 2) + 1]] > max) {
        max = myTableCapacity[myHeap[(index * 2) + 1]];
    }else{
        if(myTableCapacity[myHeap[(index * 2) + 1]] == max){
            control += 2;
        }
    }



    if(max != myTableCapacity[myHeap[index]]) {
        if(myTableCapacity[myHeap[index * 2]] == myTableCapacity[myHeap[(index * 2)+1]]){
            if(myHeap[index*2] > myHeap[(index*2)+1]){
                int temp = myHeap[index];
                myHeap[index] = myHeap[(index * 2) + 1];
                myHeap[(index * 2) + 1] = temp;
                heapDown((index * 2) + 1);
            }else{
                int temp = myHeap[index];
                myHeap[index] = myHeap[index * 2];
                myHeap[index * 2] = temp;
                heapDown(index * 2);
            }
        }else if (max == myTableCapacity[myHeap[index * 2]]) {
            int temp = myHeap[index];
            myHeap[index] = myHeap[index * 2];
            myHeap[index * 2] = temp;
            heapDown(index * 2);
        } else if (max == myTableCapacity[myHeap[(index * 2) + 1]]) {
            int temp = myHeap[index];
            myHeap[index] = myHeap[(index * 2) + 1];
            myHeap[(index * 2) + 1] = temp;
            heapDown((index * 2) + 1);
        }
    }else{

        if(control == 1){
            if(myHeap[index*2] < myHeap[index]){
                int temp = myHeap[index*2];
                myHeap[index*2] = myHeap[index];
                myHeap[index] = temp;
            }
        }else if (control == 2){
            if(myHeap[(index*2)+1] < myHeap[index]){
                int temp = myHeap[(index*2)+1];
                myHeap[(index*2)+1] = myHeap[index];
                myHeap[index] = temp;
            }
        }else if (control == 3){

            int min_index_table = myHeap[index];

            if(myHeap[index*2] < min_index_table){
                min_index_table = myHeap[index*2];
            }if(myHeap[(index*2)+1] < min_index_table){
                min_index_table = myHeap[(index*2)+1];
            }

            if(min_index_table != myHeap[index]) {
                if (min_index_table == myHeap[index * 2]) {
                    int temp = myHeap[index];
                    myHeap[index] = myHeap[index * 2];
                    myHeap[index * 2] = temp;
                    heapDown(index * 2);
                } else if (min_index_table == myHeap[(index * 2) + 1]) {
                    int temp = myHeap[index];
                    myHeap[index] = myHeap[(index * 2) + 1];
                    myHeap[(index * 2) + 1] = temp;
                    heapDown((index * 2) + 1);
                }
            }



        }

    }

}

void RestaurantOrganizer::printSorted(ofstream& outFile){                   // prints the first element of the heap and sets its table capacity to zero and pushes it down
    // IMPLEMENT ME!
    for(int i=0; i<numberOfTables;i++){
        outFile << myTableCapacity[myHeap[1]] << " ";
        myTableCapacity[myHeap[1]] = 0;
        heapDown(1);
    }
}

// YOU CAN ADD YOUR HELPER FUNCTIONS

