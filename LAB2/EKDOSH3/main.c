#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>

#define test


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

#ifdef test
    TEMPERATURE_UP=2.0;
    TEMPERATURE_DOWN=2.0;
    TEMPERATURE_LEFT=3.0;
    TEMPERATURE_RIGHT=1.0;
    TEMPERATURE_REST=1.0;
#else // test
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
#endif
}
// MATRIXES

float m0[ROWS][COLS];
float m1[ROWS][COLS];
float m2[ROWS][COLS];
float m_x_secs[ROWS][COLS];// function copy of m0 and change in x secods
float diafores[ROWS][COLS];//

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
    for(i=0; i<ROWS; i++)
        for(j=0; j<COLS; j++)
        {
            diafores[i][j]=0;
        }

}
//Η συνάρτηση αυτή εκτυπώνει τον αρχικό πίνακα
void printmatrix(float m[ROWS][COLS])
{
    printf("--------------------------------\n");
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
            printf("%.2f ", m[i][j]);
        printf("\n");
    }
    printf("--------------------------------\n");
}
////Η συναρτηση αυτή εκτυπώνει τον κανονικοποιημένο πίνακα
//void print_matrix_of_integers(int m[ROWS][COLS])
//{
//    for(int i=0; i<ROWS; i++)
//    {
//        for(int j=0; j<COLS; j++)
//            printf("%i ", m[i][j]);
//        printf("\n");
//    }
//}


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
float minmax(float m[ROWS][COLS])
{
    float max=-1000000000.0;

    for(int i=0; i<ROWS; i++)
        for(int j=0; j<COLS; j++)
        {
            if(max<m[i][j])
                max=m[i][j];
        }
    return max;
}

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
void diafora(float before[ROWS][COLS],float after[ROWS][COLS])
{
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
            diafores[i][j]=abs(after[i][j]-before[i][j]);
//        printf("%d %d %f %f %f\n",i,j,after[i][j],before[i][j],diafores[i][j]);
        }
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

//    int t;
//    printf("Give me the second:");

//scanf("%d",&t);

    copy(m0,m1);
    copy(m1,m2);
    while(minmax(diafores)<1.0)
    {
//        printmatrix(m1);
//        printmatrix(m2);
        change(m2,m1);
//        printmatrix(m1);
//        printmatrix(m2);
        diafora(m1,m2);
//        printmatrix(diafores);
//        exit(1);
        copy(m2,m1);
    }
    printmatrix(m2);

    return 0;
}
