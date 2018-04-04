#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>

/// Υπολογισμός θερμοκρασιών πλάκας version 2

#define ROWS 10 //Εδώ προσδιορίζονται ο αριθμός των γραμμών και στηλών του πίνακα καθώς και οι θερμοκρασίες της πλάκας σε global μορφή.
#define COLS 20
float TEMPERATURE_LEFT;
float TEMPERATURE_RIGHT;
float TEMPERATURE_UP;
float TEMPERATURE_DOWN;
float TEMPERATURE_REST;
#define DIFF 10

//Η συνάρτηση αυτή παίρνει απο το πληκτρολόγιο τις αρχικές τιμές σε float μορφή.
void SetValues()
{
    printf("Give up side temperature:\n");
    scanf("%f", &TEMPERATURE_UP);
    printf("Give down side temperature:\n");
    scanf("%f", &TEMPERATURE_DOWN);
    printf("Give left side temperature:\n");
    scanf("%f", &TEMPERATURE_LEFT);
    printf("Give right side temperature:\n");
    scanf("%f", &TEMPERATURE_RIGHT);
    printf("Give rest temperature:\n");
    scanf("%f", &TEMPERATURE_REST);

}
// MATRIXES

float m0[ROWS][COLS];
float m1[ROWS][COLS];
int m2[ROWS][COLS]; //ο κανονικοποιημένος πίνακας tου m0
float m_x_secs[ROWS][COLS];// function copy of m0 and change in x secods

//αρχικοποίση της m0
void init_m0()
{
    int i,j;
    for(i=1; i<ROWS-1; i++)
    {
        m0[i][0]=TEMPERATURE_LEFT;
        m0[i][COLS-1]=TEMPERATURE_RIGHT;
    }

    for(j=1; j<COLS-1; j++)
    {
        m0[0][j]=TEMPERATURE_UP;
        m0[ROWS-1][j]=TEMPERATURE_DOWN;
    }
//διόρθωση των γωνιακών στοιχείων στο μέσο όρο, επειδή ενδέχεται να έχουμε διαφορετικές θερμοκρασίες σε κάθε πλευρά.
    m0[0][0]=(float)(m0[0][1]+m0[1][0])/2.0;
    m0[0][COLS-1]=(float)(m0[0][18]+m0[1][19])/2.0;
    m0[ROWS-1][0]=(float)(m0[8][0]+m0[9][2])/2.0;
    m0[ROWS-1][COLS-1]=(float)(m0[8][19]+m0[9][18])/2.0;
    for(i=1; i<ROWS-1; i++)
        for(j=1; j<COLS-1; j++)
        {
            m0[i][j]=TEMPERATURE_REST;
        }
}
//Η συνάρτηση αυτή εκτυπώνει τον αρχικό πίνακα
void printmatrix(float m[ROWS][COLS])
{
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
            printf("%.2f ", m[i][j]);
        printf("\n");
    }
}
//Η συναρτηση αυτή εκτυπώνει τον κανονικοποιημένο πίνακα
void print_matrix_of_integers(int m[ROWS][COLS])
{
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
            printf("%i ", m[i][j]);
        printf("\n");
    }
}


//Αντιγράφει ένα μητρώο σε ένα άλλο.
void copy(float from[ROWS][COLS],float to[ROWS][COLS])
{
    for(int i=0; i<ROWS; i++)
        for(int j=0; j<COLS; j++)
            to[i][j]=from[i][j];
}

//Αλλάζει το μητρώο σύμφωνα με τον τύπο χωρίς να πειράζει τις ακριανές τιμές.
void change(float New[ROWS][COLS], float Old[ROWS][COLS])
{
    for(int i=1; i<ROWS-1; i++)
        for(int j=1; j<COLS-1; j++)
            New[i][j]=0.1*(Old[i-1][j-1]+Old[i-1][j]+Old[i-1][j+1]+Old[i][j-1]+2.0*Old[i][j]+Old[i][j+1]+Old[i+1][j-1]+Old[i+1][j]+Old[i+1][j+1]);
}
//Η συνάρτηση βρίσκει τη μέγιστη και ελάχιστη θερμοκρασία ενός πίνακα
//void minmax(float m[ROWS][COLS], float*min, float* max)
//{
//    *min=1000000000.0;
//    *max=0.0;
//
//    for(int i=0; i<ROWS; i++)
//        for(int j=0; j<COLS; j++)
//        {
//            if(*min>m[i][j])
//                *min=m[i][j];
//            if(*max<m[i][j])
//                *max=m[i][j];
//        }
//}

//Η συνάρτηση επιστρέφει σε ποιά τάξη ανήκει η θερμοκρασία
//int return_class_of_int(float mij, int min, int max, float du)
//{
//    float f=mij-min;
//    int i=f/du;
//    if(i==DIFF)
//        i=DIFF-1;
//    return i;
//}
//Η normalize κανονικοποιεί τον πίνακα που δίνεις
//void normalize(float m[ROWS][COLS],int norm[ROWS][COLS])
//{
//    float min,max;
//    minmax(m,&min,&max);
//    // διαφορική θερμοκρασία
//    float du=(max-min+0.1)/10;
//    for(int i=0; i<ROWS; i++)
//        for(int j=0; j<COLS; j++)
//            norm[i][j]=return_class_of_int(m[i][j],min,max,du);
//}
//

//αθροιστική μεταβολή στοιχείων
float abs_matrix_du(float before[ROWS][COLS],float after[ROWS][COLS]){
    float d1;
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
            d1+=abs(abs(after[i][j])-abs(before[i][j]));
        }
    }
    return d1;
}

void change_matrix_in_x_seconds(float m[ROWS][COLS],int t){
    float mt[ROWS][COLS];
    copy(mt,m0);
    for (int i=0; i<t; i++)
    {
        change(mt,m);
        copy(mt,m);
    }
}

//count θερμοκρασιες στον πινακα
int count_occur(int m_x_secs[ROWS][COLS], int value)
/* checks array a for number of occurrances of value */
{
    int i,j, count=0;
    for (i=0; i<ROWS; i++)
    {
        for(j=0; j<COLS; j++)
        {
            if (m_x_secs[i][j] == value)
            {
                ++count; /* it was found */
            }
        }
    }
    return(count);

}
//κατασκευη ιστογραμματος

int main()
{
//αρχικοποίση της m0 με διόρθωση των γωνιακών.
    SetValues();
    init_m0();

    int t;
    printf("Give me the second:");

    scanf("%d",&t);

    copy(m0,m_x_secs);

    printmatrix(m_x_secs);

    change_matrix_in_x_seconds(m_x_secs,t);

    printmatrix(m_x_secs);

    return 0;
}
