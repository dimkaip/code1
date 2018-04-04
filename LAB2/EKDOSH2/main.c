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
int m3[ROWS][COLS]; //ο κανονικοποιημένος πίνακας tου m1

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
void minmax(float m[ROWS][COLS], float*min, float* max)
{
    *min=1000000000.0;
    *max=0.0;

    for(int i=0; i<ROWS; i++)
        for(int j=0; j<COLS; j++)
        {
            if(*min>m[i][j])
                *min=m[i][j];
            if(*max<m[i][j])
                *max=m[i][j];
        }
}
//Η συνάρτηση επιστρέφει σε ποιά τάξη ανήκει η θερμοκρασία
int return_class_of_int(float mij, int min, int max, float du)
{
    float f=mij-min;
    int i=f/du;
    if(i==DIFF)
        i=DIFF-1;
    return i;
}
//Η normalize κανονικοποιεί τον πίνακα που δίνεις
void normalize(float m[ROWS][COLS],int norm[ROWS][COLS])
{
    float min,max;
    minmax(m,&min,&max);
    // διαφορική θερμοκρασία
    float du=(max-min+0.1)/10;
    for(int i=0; i<ROWS; i++)
        for(int j=0; j<COLS; j++)
            norm[i][j]=return_class_of_int(m[i][j],min,max,du);
}

int main()
{
//αρχικοποίησε τον m0 με διόρθωση των γωνιακών θερμοκρασιών.
    SetValues();
    init_m0();

//    printf("Εκτύπωση min και max του μητρώου m1\n");
//
//    float min,max;
//    //βρες τις μέγιστες και ελάχιστες θερμοκρασίες του αρχικού πίνακα
//    minmax(m0,&min,&max);
//
//    printf("min is:%.2f max is:%.2f \n", min,max);

    printf("For t=0\n");
    printmatrix(m0);
//αντιγραφή στon m1
    copy(m0,m1);
//Αλλαγή της m1 σύμφωνα με τον τύπο
    printf("For t=1\n");
    change(m1,m0);
//Εκτύπωση της m1
    printmatrix(m1);
    normalize(m0,m2);

    printf("Κανονικοποίηση για t=0\n");
    //εκτύπωσε τον κανονικοποιημένο πίνακα m2
    print_matrix_of_integers(m2);
    //αντιγραφή του αρχικού πίνακα-μητρώου m0 στον δεύτερο m1
    copy(m0,m1);

//Άλλαξε της m1 σύμφωνα με τον δοθέντα τύπο
    change(m1,m0);
    printf("Κανονικοποίηση για t=1\n");
    normalize(m1,m2);
    print_matrix_of_integers(m2);

    return 0;
}









