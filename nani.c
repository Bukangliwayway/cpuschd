#include<stdlib.h>
#include<stdio.h>

typedef struct Process{
  int name;
  int arrTime;
  int burTime;
  int priority;
  struct Process *next;
} Process;

int processNum = 0;

int inputNum(int type){
  int num;
  system("clear");
  printf("Process %d:\n", processNum);
  printf("Input 0 if None\n\n\n");
  switch(type){
    case 1: printf("Burst Time\n"); break;
    case 2: printf("Arrival Time\n"); break;
    case 3: printf("Priority\n"); break;
  }

  printf("Input Value: ");
  scanf("%d", &num);
  return num;
}

Process *createNode(Process *curr){
  processNum++;
  Process* newNode =  (Process*)malloc(sizeof(Process));
  if(curr != NULL){
    while(curr->next != NULL) curr = curr->next; //traverse to the end link  
    curr->next = newNode;
  } 
  newNode->name = processNum;
  newNode->next = NULL;
  newNode->burTime = inputNum(1);
  newNode->arrTime = inputNum(2);
  newNode->priority = inputNum(3);
  return newNode;
}

void displayItem(Process* head){
  while(head != NULL){
    printf("%d\t", head->name);
    printf("%d\t", head->burTime);
    printf("%d\t", head->arrTime);
    printf("%d\t\n", head->priority);
    head = head->next;
  }
}

void fcfs(Process *temp){
  int processCount = 0;
  float waitTime = 0, avg = 0;

  system("clear");
  printf("Waiting Time:\n\n");
  while(temp != NULL){
    printf("P%d: %0.2f\n", temp->name, waitTime);
    processCount++;
    waitTime += (float)temp->burTime;
    avg += waitTime;
    temp = temp->next;
  }
  avg -= waitTime;
  printf("\nAverage Waiting Time: %0.2f\n", (float)avg/((float)processCount));
}

// void swapNode(Process **a, Process **b){
//   // Process *temp =  *a;
//   // *a = *b;
//   // *b = temp;
// }

void swapNode(Process *a, Process *b){
  a->arrTime += b->arrTime ;
  a->burTime += b->burTime;
  a->priority += b->priority;
  a->name += b->name;
 
  b->arrTime = a->arrTime - b->arrTime;
  b->burTime = a->burTime - b->burTime;
  b->priority = a->priority - b->priority;
  b->name = a->name - b->name;

  a->arrTime -= b->arrTime;
  a->burTime -= b->burTime;
  a->priority -= b->priority;
  a->name -= b->name;
}

void sjf(Process *temp){
  Process *head = temp, *compare = head; 

  while(temp != NULL){
    while(compare != NULL){
      if(temp->burTime < compare->burTime) swapNode(temp, compare);
      compare = compare->next;
    }
    temp = temp->next;
    compare = head;
  }
  fcfs(head);
}

// void sjfPreemptive(Process *temp){
//   Process *head = temp, *compare = head; 
//   int waitTime = 0;

//   while(temp != NULL){
//     while(compare != NULL){
//       if(temp->arrTime < compare->arrTime) swapNode(temp, compare);
//       compare = compare->next;
//     }
//     temp = temp->next;
//     compare = head;
//   }
  
//   while(!rrCheck(head)){
//     compare = head;
//     printf("p%d: %d", temp->name, waitTime);
//     // Code to search for the lowest burTime and compare it to temp->burTime
//     // if true temp->burTime -= compare->arrTime; waitTime += arrTime; temp = compare; break;
//     // else waitTime += temp->burTime; temp-burtime = 0; temp = lowest burtime

//     //if rrcehck or everything is alreaedy 0 then finish it with average time

//   }


// }

void prioritySched(Process *temp){
  Process *head = temp, *compare = head; 

  while(temp != NULL){
    while(compare != NULL){
      if(temp->priority < compare->priority) swapNode(temp, compare);
      compare = compare->next;
    }
    temp = temp->next;
    compare = head;
  }
  fcfs(head);
}

int rrCheck(Process *head){
  while(head != NULL){
    if(head->burTime > 0) return 0;
    head = head->next;
  }
  return 1;
}

void roundRobin(Process *temp){
  system("clear");
  Process *head = temp;
  int quantum, countProcess = 1, waitTime = 0;
  printf("Input Quantum Time: ");
  scanf("%d", &quantum);
  
  while(!rrCheck(head)){
    while(temp != NULL){
      if(temp->burTime > quantum){
        printf("p%d: %d\n", countProcess, waitTime);
        waitTime += quantum;
        temp->burTime -= quantum;
      }else if(temp->burTime <= quantum && temp->burTime > 0){
        printf("p%d: %d\n", countProcess, waitTime);
        waitTime += temp->burTime;
        temp->burTime = 0;
      }
      countProcess++;
      temp = temp->next;
    }
    temp = head;
    countProcess = 1;
  }
}

int main(){
  Process *head = createNode(NULL);
  createNode(head);
  createNode(head);
  createNode(head);
  sjf(head);
  return 0;
}