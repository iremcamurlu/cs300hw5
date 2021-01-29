#include <iostream>

#include <pthread.h>

#include <stdlib.h>

#include <cmath>

#include <limits.h>

//created by nazli irem camurlu 11/08/2020



class RandGen//random generator class to generate random numbers for the agencies

{

public:

    RandGen()

    {



        if (0 == ourInitialized)

        {   ourInitialized = 1;





            time_t now;

            time (&now);

            srand(int((sin(double(now))*1000000)));



        }

    }

    int RandInt(int max = INT_MAX)

    {

        return int(RandReal() * max);

    }

    double RandReal()

    {

        return rand() / (double(RAND_MAX) + 1);

    }

    double RandReal(double low, double high)

    {

        double width = fabs(high-low);

        double thelow = low < high ? low : high;

        return RandReal()*width + thelow;

    }



    static void SetSeed(int seed)

    {

        if (0 == ourInitialized)

        {   ourInitialized = 1;

            srand(seed);

        }

    }

private:

    static int ourInitialized;

};



int RandGen::ourInitialized = 0;









using namespace std;

int matrix[2][50] = {0};//matrix array to represent the plane seating



int matrixCounter = 1; //shows the element number in matrix

bool matrixIsFull = false;//to be able to see if the plane is all reserved

int random(int m)//to get random numbers through randgen class

{

    RandGen randomGenerator;

    return randomGenerator.RandInt(m+1);

}

bool tturn = true;//to implement busy-waiting



bool thread1_finished = false;





void *rezerv1(void *param)//function for thread 1

{



    while (!matrixIsFull) {

        

        while(!tturn)

        {

            //busy waiting

        }





        int * id = (int*) param;

        int random_row = random(1);//random row number

        int ran_column = random(49);//random column number



        cout<<"Agency "<<*id<<" Entered Critical Region with "<<random_row+1 * ran_column+1<<endl;



        if (matrix[random_row][ran_column]== 0) {//if the random cell is not reserved before

            cout<<"Seat Number "<<random_row+1 * ran_column+1<< " is reserved by Agency "<<*id <<endl;

            matrix[random_row][ran_column]=*id;

            matrixCounter++;



        }

        cout<<"Agency "<< *id<<" Exit Critical Region"<<endl<<endl;





        tturn = false;



        if(matrixCounter>100)

        {

            matrixIsFull=true;//if all the seats are reserved the boolean changes to true to exit the function





        }









    }

    thread1_finished = true;//boolean to represent that the thread has finished its job

    return NULL;

}

bool thread2_finished = false;

void *rezerv2(void *param)

{



    while (!matrixIsFull) {

        while (tturn)

        {

        }

        

        int * id = (int*) param;

        int random_row = random(1);

        int ran_column = random(49);



        cout<<"Agency "<<*id<<" Entered Critical Region with "<<random_row+1 * ran_column+1<<endl;



        if (matrix[random_row][ran_column]== 0) {

            cout<<"Seat Number "<<random_row+1 * ran_column+1<< " is reserved by Agency "<<*id <<endl;

            matrix[random_row][ran_column]=*id;

            matrixCounter++;



        }

        cout<<"Agency "<< *id<<" Exit Critical Region"<<endl<<endl;









        tturn = true;

        if(matrixCounter>100)

        {

            matrixIsFull=true;





        }



    }

    thread2_finished = true;

    return NULL;

}



void print_2d_matrix()

{

    for (int i =0; i<2; i++) {

        for (int k = 0; k<50; k++) {

            cout<<matrix[i][k]<<" ";

        }

        cout<<endl;

    }

}



int main() {



    pthread_t thread1; //initialization of threads

    pthread_t thread2;





    int agency1_id = 1;

    int agency2_id = 2;





    pthread_create(&thread1, NULL, &rezerv1, (void*)&agency1_id);//sending the threads to their functions individually



    pthread_create(&thread2, NULL, &rezerv2, (void*)&agency2_id);

    

    while (!thread1_finished) {


		//join implemented manually
    }

    

    while (!thread2_finished) {

        //join implemented manually

    }



    



    cout<<"No Seats Left"<<endl<<endl;



    print_2d_matrix();



}