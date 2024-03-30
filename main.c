#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 200

struct poly_node;
typedef struct poly_node *PTR;
typedef PTR List;
typedef PTR position;
void inseret_poly_node(List L,position p,float factor, int power);
int Numberofequations=0;
char string[1000];
char factor[1000];
char deg[1000];
float storeCoff;
int storeDeg;
struct poly_node
{
    float X_factor;
    int power;
    PTR next;
    PTR prevous;
};
struct poly_node *ArrayofLinkedLists[200] ;
struct poly_node result,p ;
///-------------------------------------------------
void remove_space(char* string)
{
    int j=0;

    for(int i=0; i< string[i]; i++)
    {
        string[i]=string[i+j];

        if(string[i]== ' ')
        {
            j++;
            i--;
        }
    }
}
///-----------------------------------------------

int read(FILE *polynomials)
{

    if (polynomials == NULL)
    {
        printf("File does not exist..!!\n");
    }
    else
    {
        while(fgets(string, MAX, polynomials) !=NULL)
        {
            int i=0;
            //fgets(string, MAX, polynomials);
            // remove all space from lines
            remove_space(string);
            // printf("%s \n", string);
            //Since the line has not reached its end
            while(string[i] != '\n')
            {
                ///------------------------------------------------------------------------------------------------
                /// The main idea is to divide the equation into terms based on the positive, negative or number (x factor)

                //If the first character equal (+) or numbers..
                if ( strncmp(&(string[i]),"+",1)==0  || (  strncmp(&(string[i]),"0",1)>=0 && strncmp(&(string[i]),"9",1)<=0 ))
                {
                    //If the first character equal (+)
                    if(strncmp(&(string[i]),"+",1)==0)
                    {
                        //Move on to the next character.
                        i++;
                    }
                    //If the next character is number [0,9]
                    if(((strncmp(&(string[i]),"0",1)>=0 && (strncmp(&(string[i]),"9",1)<=0))))
                    {
                        int j=0;
                        while (((strncmp(&(string[i]),"0",1)>=0&&(strncmp(&(string[i]),"9",1)<=0))))
                        {
                            //store the character (number) in factor
                            factor[j]=string[i];
                            //Move to the next number
                            j++;
                            //Move on to the next character.
                            i++;
                        }
                        factor[j] ='r';
                        //Convert the numbers stored in the factor to integer numbers by using atoi.
                        storeCoff=atof(factor);

                    }
                    else
                    {
                        //ex : x -->factor =1
                        storeCoff = 1;
                    }
                    //If the first character equal (x)
                    if (string[i]=='x')
                    {
                        //Move on to the next character.
                        i++;
                        if(string[i]=='^')
                        {
                            //Move on to the next character.
                            i++;
                            //If the next character is number [0,9]
                            if(((strncmp(&(string[i]),"0",1)>=0&&(strncmp(&(string[i]),"9",1)<=0))))
                            {

                                int k=0;
                                while (((strncmp(&(string[i]),"0",1)>=0&&(strncmp(&(string[i]),"9",1)<=0))))
                                {
                                    //store the character (number) in deg
                                    deg[k]=string[i];
                                    //Move to the next number
                                    k++;
                                    //Move on to the next character.
                                    i++;
                                }
                                deg[k]='r';
                                //Convert the numbers stored in the factor to integer numbers by using atoi.
                                storeDeg=atoi(deg);
                            }
                        }
                        else
                        {
                            storeDeg=1;
                        }
                    }
                    //-----------
                    else
                    {
                        storeDeg=0;
                    }
                    inseret_poly_node(ArrayofLinkedLists[Numberofequations],ArrayofLinkedLists[Numberofequations], storeCoff,storeDeg);
                }
                ///------------------------------------------------------------------------------------------
                else if (string[i]=='-') //If the first character equal (-)
                {
                    //Move on to the next character.
                    i++;
                    //If the next character is number [0,9]
                    if((strncmp(&(string[i]),"0",1)>=0&&(strncmp(&(string[i]),"9",1)<=0)))
                    {

                        int j = 0;
                        while ((strncmp(&(string[i]), "0", 1) >= 0 && (strncmp(&(string[i]), "9", 1) <= 0)))
                        {
                            //store the character (number) in factor
                            factor[j] = string[i];
                            //Move to the next number
                            j++;
                            //Move on to the next character.
                            i++;

                        }
                        factor[j] = 'r';
                        //Convert the numbers stored in the factor to float numbers by using atof.
                        storeCoff = atof(factor);
                        //Since the first character is negative, multiply the storeCoffber by -1
                        storeCoff =storeCoff*-1;
                    }
                    else
                    {
                        //-x --> print -1
                        storeCoff = -1;
                    }
                    //If the first character equal (x)

                    if ((string[i])=='x')
                    {
                        //Move on to the next character.
                        i++;
                    }
                    else
                    {
                        //deg=0
                        storeDeg = 0;
                    }
                    //If the first character equal (^)
                    if((string[i])=='^')
                    {
                        //Move on to the next character.
                        i++;
                        //If the next character is number [0,9]
                        if((strncmp(&(string[i]),"0",1)>=0&&(strncmp(&(string[i]),"9",1)<=0)))
                        {
                            int k=0;
                            while ((strncmp(&(string[i]),"0",1)>=0&&(strncmp(&(string[i]),"9",1)<=0)))
                            {
                                //store the character (number) in deg
                                deg[k]=string[i];
                                //Move to the next number
                                k++;
                                //Move on to the next character
                                i++;
                            }
                            deg[k]='r';
                            //Convert the numbers stored in the deg to integer numbers by using atoi.
                            storeDeg=atoi(deg);
                        }
                    }
                    else
                    {
                        //ex : -3 --> the deg = 0
                        storeDeg = 0;
                    }
                    inseret_poly_node(ArrayofLinkedLists[Numberofequations],ArrayofLinkedLists[Numberofequations], storeCoff,storeDeg);

                }
                ///--------------------------------------------------------------------------------------------------

                //If the first character equal (x)
                else  if (string[i]=='x')
                {
                    //factor =1 --> ex : x^3
                    storeCoff =1;
                    //Move on to the next character.
                    i++;
                    //If the first character equal (^)
                    if(string[i]=='^')
                    {
                        //Move on to the next character.
                        i++;
                        //If the next character is number [0,9]
                        if(((strncmp(&(string[i]),"0",1)>=0&&(strncmp(&(string[i]),"9",1)<=0))))
                        {

                            int k=0;
                            while (((strncmp(&(string[i]),"0",1)>=0&&(strncmp(&(string[i]),"9",1)<=0))))
                            {
                                //store the character (number) in deg
                                deg[k]=string[i];
                                //Move to the next number
                                k++;
                                //Move on to the next character.
                                i++;
                            }
                            deg[k]='r';
                            //Convert the numbers stored in the factor to integer numbers by using atoi.
                            storeDeg=atoi(deg);
                        }
                    }
                    else
                    {
                        // ex : x --> x^1
                        storeDeg=1;

                    }
                    inseret_poly_node(ArrayofLinkedLists[Numberofequations],ArrayofLinkedLists[Numberofequations], storeCoff,storeDeg);
                }
                ///-------------------------------------------------------------
            }
            Numberofequations++;

        }
    }
}
///-------------------------------------------------------------
void inseret_poly_node(List L, position p,float factor, int power)
{
    position temp= (position)malloc(sizeof(struct poly_node));
    temp->X_factor=factor;
    temp->power=power;
    position d;
    d=p;
    if (temp!= NULL)
    {
        while(d->next != NULL)
        {
            d = d->next ;
        }
        temp ->next = d ->next;
        d ->next = temp;
        temp ->prevous = d;
    }
    else
    {
        printf("Out of Memory!\n");
        exit(0);
    }
}
///-------------------------------------------------------------
List printList (List L )
{
    position pos ;
    pos=L;
    while(pos->next!=NULL)
    {
        pos =pos->next;
        // if coefficient (+) and power (+)
        if (pos->X_factor >=0 && pos->power >=0)
        {
            printf(" + %.1f x^ %d ", pos->X_factor,pos->power);
        }
        // if coefficient (-) and power (+)
        else if (pos->X_factor <=0 && pos->power >=0)
        {
            printf(" %.1f  x^ %d ", pos->X_factor,pos->power);
        }
    }
    printf("\n");
}
///----------------------------------------------
List Addition( List L1, List L2)
{
    List p_L1 = L1->next ;
    List q_L2 = L2->next ;
    List sum = (List)malloc (sizeof(struct poly_node));
    sum->next= NULL;
    sum ->prevous = NULL;
    int a, b;
    while(p_L1 != NULL && q_L2 != NULL)
    {
        // If the power of the first term of the first equation is equal
        //to the power of the second term of the second equation
        if(p_L1->power == q_L2->power )
        {
            a =  p_L1->X_factor + q_L2->X_factor;
            b =  p_L1->power;
            inseret_poly_node(sum, sum,a, b);
            p_L1 = p_L1->next;
            q_L2 = q_L2->next;
        }
        // If the power of the first term of the first equation is larger than
        // the power of the second term of the second equation
        else if(p_L1->power > q_L2->power )
        {
            a =  p_L1->X_factor ;
            b =  p_L1->power;
            inseret_poly_node(sum, sum,a, b);
            p_L1 = p_L1->next;
        }
        else
            // If the power of the first term of the first equation is smaller than
            // the power of the second term of the second equation
        {
            a =  q_L2->X_factor ;
            b=  q_L2->power;
            inseret_poly_node(sum, sum,a, b);
            q_L2 = q_L2->next;
        }
    }
    return sum;
}
///----------------------------------------------
List add()
{
    List resultt ;
    resultt = ArrayofLinkedLists[0];
    for(int i=1; i< Numberofequations; i++)
    {
        resultt= Addition(resultt, ArrayofLinkedLists[i]);
    }
    return resultt;
}
///----------------------------------------------
List Subtraction(List L1, List L2)
{
    List p_L1 = L1->next ;
    List q_L2 = L2->next ;
    List sub = (List)malloc (sizeof(struct poly_node));
    sub->next= NULL;
    sub ->prevous = NULL;
    int a, b;
    while(p_L1 != NULL && q_L2 != NULL)
    {
        // If the power of the first term of the first equation is equal
        //to the power of the second term of the second equation
        if(p_L1->power == q_L2->power )
        {
            a =  p_L1->X_factor - q_L2->X_factor;
            b =  p_L1->power;
            inseret_poly_node(sub, sub,a, b);
            p_L1 = p_L1->next;
            q_L2 = q_L2->next;
        }
        // If the power of the first term of the first equation is larger than
        // the power of the second term of the second equation
        else if(p_L1->power > q_L2->power )
        {
            a =  p_L1->X_factor ;
            b =  p_L1->power;
            inseret_poly_node(sub, sub,a, b);
            p_L1 = p_L1->next;
        }
        // If the power of the first term of the first equation is smaller than
        // the power of the second term of the second equation
        else
        {
            a =  q_L2->X_factor ;
            b=  q_L2->power;
            inseret_poly_node(sub, sub,a, b);
            q_L2 = q_L2->next;
        }
    }

    return sub;
}
///----------------------------------------------
List subb()
{
    List resultt ;
    resultt = ArrayofLinkedLists[0];
    for(int i=1; i< Numberofequations; i++)
    {
        resultt= Subtraction(resultt, ArrayofLinkedLists[i]);
    }
    return resultt;
}
///-------------------------------------------------
List Multiplication(List L1, List L2)
{
    ///Sorry .. I was not able to do the multiplication and save and substitute fenction :(
    List p_L1 = L1->next ;
    List q_L2 = L2->next ;
    List Product = (List)malloc (sizeof(struct poly_node));
    Product->next= NULL;
    Product ->prevous = NULL;
    List p ;
    int a, b ;
    while(p_L1 != NULL )
    {
        q_L2 = L2;
        while(q_L2 !=NULL)
        {
            a =  p_L1->X_factor * q_L2->X_factor;
            b =  p_L1->power + q_L2->power;
            inseret_poly_node(p,p,a, b);
        }
        Product = Addition(Product, p);
        delete_1(p);
        p_L1 = p_L1->next;
    }
    return Product;
}
///----------------------------------------------
List MULL()
{
    List resultt ;
    resultt = ArrayofLinkedLists[0];
    for(int i=1; i< Numberofequations; i++)
    {
        resultt= Multiplication(resultt, ArrayofLinkedLists[i]);
    }
    return resultt;

}
///----------------------------------------------
void delete_1(List d)
{
    position p = d -> next;
    while (d -> next != NULL)
    {
        d -> next = d -> next;
        free(p);
        p = d -> next;
    }
}
///----------------------------------------------
void Save()
{
    FILE *out;  /// creat output file
    out = fopen("results.txt","w");
    position pos ;
    while(pos->next!=NULL)
    {
        pos =pos->next;
        // if coefficient (+) and power (+)
        if (pos->X_factor >=0 && pos->power >=0)
        {
            fprintf(out," + %.1f x^ %d ", pos->X_factor,pos->power);
        }
        // if coefficient (-) and power (+)
        else if (pos->X_factor <=0 && pos->power >=0)
        {
            fprintf(out," %.1f  x^ %d ", pos->X_factor,pos->power);
        }
    }
    fprintf(out, "\n");
    fclose(out);
}
///----------------------------------------------
double substitute(List d)
{
    printf("\nDo you want to substitute a number into the equation? \n");
    int v;
    printf("\n 1. yes \n");
    printf("\n 2. No \n");
    scanf("%d",& v);
    double Finalresult = 0, x ;
    if (v == 1)
    {
        printf("\nPlease enter the number that you want to substitute in the equation \n");
        scanf("%d", &x);
        List z = d->next;
        while (z != NULL)
        {
            Finalresult += (z -> X_factor) * pow(x, z -> power);
            z = z -> next;
        }
        printf("F(%d) =  %.1f", x, Finalresult );
    }
    else
    {
        // Do nothing
    }
    return Finalresult;
}
///----------------------------------------------
int main()
{
    FILE *polynomials;   // creat input file
    polynomials = fopen("equations.txt", "r");
    for(int i=0; i< MAX ; i++)
    {
        ArrayofLinkedLists[i]=(List)malloc(sizeof(struct poly_node));// allocate memory for List
        ArrayofLinkedLists[i]->next=NULL;
        ArrayofLinkedLists[i]->prevous=NULL;
    }
    int x ;
    while(x!=6)
    {
        printf("\nEnter Your choice please.. \n");
        printf("----------------------------\n");
        printf("1.Read File and Show equations\n");
        printf("2.Addition equations\n");
        printf("3.Subtraction equations\n");
        printf("4.Multiplication equations\n");
        printf("5.Save the result \n");
        printf("6.Exit \n");
        scanf("%d",&x);
        switch (x)

        {

        case 1:
            ///Read File
            read(polynomials);
            printf("Equations stored in file: \n");
            for(int i=0; i< Numberofequations; i++)
            {
                // print equations
                printList(ArrayofLinkedLists[i]);
            }
            break;
        ///Addition equations
        case 2:
            printf("The result of the addition process : \n");
            printList(add());
            substitute(add());

            break;
        case 3:
            ///Subtraction equations
            printf("The result of the Subtraction process : \n");
            printList(subb());
            substitute(subb());

            break;
        case 4:
            ///Multiplication equations
            printf("The result of the Multiplication process : \n");
            // printList(MULL());
            // substitute(MULL());

            break;

        case 5:

            ///Save the result in output file
            // Save();
            printf("Saved successfully .. ");
            break;
        case 6:
            printf("GOOD BYE ..");
            ///Exit the program
            exit(0);
            break;
        default:
            printf("Error .. !");

        }
    }

    return 0;
}*/


// Eman Shaher Maraita, 1190768, section 1.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 15           // the size of the array of linked list, assume that it is [15].
// define a pointer of structure as an new data type.
typedef struct Node*ptr;
// define the Doubly linked list structure.
typedef struct Node
{
    float coefficient;
    int exponent;
    ptr next;            // pointer to point to the next node.
    ptr previous;        // pointer to point to the previous node.
} Node;
// define an array of linked list to store equations inside it ( i assume that the maximum number of equations is 15).
ptr Array[MAX_SIZE];
// define a pointer with name (start) and initialize it to NULL.
ptr start = NULL;
// define a global variable to count the number of equation that exist in the file.
int numOfEquation = 0;
int numWithMulOperation = 0;
/* define an array of integers to store the number of terms in each equation
(assuming that the maximum number of terms in each equation is 15).*/
int terms[MAX_SIZE];
// define two arrays of integers to store the values of coefficients and exponents before load them in the Doubly linked list.
float coeff[100];
int expo[100];
// define a function to remove spaces from each equation.
void removeSpacesFromEquation(char equation[100])
{

    int i = 0, j = 0;        // define two local variables and initialize them to 0.
    while (equation[i] != NULL)
    {
        if (equation[i] != ' ' )        // if there is a space, then
            equation[j++] = equation[i];
        i++;
    }
    equation[j] = '\0';
}
// define readFile()Function to read equations from file and store the values of coefficients and exponents in arrays.
void readFile(FILE* infile)
{
    // opening the file.
    if (infile != NULL)                        // check if the file is successfully opened.
    {
        char status;
        int counter = 0,k = 0,count = 0,numOfTerms[10];
        char str[2] = "-";
        char line[100], linesInFile[100][100], *token, allEquations[100][100], divided_Equations1[100][100], divided_Equations2[100][100];
        // First Step //
        status = fgets(line,100,infile);
        // read the equations from the file and store it line by line.
        while(status != NULL)
        {
            removeSpacesFromEquation(line);                  // remove space from the equation.
            strcpy(linesInFile[numOfEquation],line);         // store the equation in the array linesInFile[].
            numOfEquation++;                                 // increase the number of equations that exist in the input file.
            status = fgets(line,100,infile);                 // take the next equation until NULL value.
        }
        // copy the contents of linesInFile[] array in to allEquations[] array.
        for(int i = 0; i < numOfEquation; i++)
        {
            // after this step we will have two arrays with the same contents, each one of them we will use it to different purpose.
            strcpy(allEquations[i],linesInFile[i]);
        }
        // use the array that contains all equations =>(allEquations[]), and divide it according (+-), to count the number of terms in each equation.
        int t = 0;                    // local variable.
        while (t < numOfEquation)
        {
            counter = 0;
            token = strtok(allEquations[t],"+-");
            while(token != NULL)
            {
                counter ++;          // increase counter by 1.
                token = strtok(NULL,"+-");
            }
            numOfTerms[t] = counter; // store the number of terms in each equation in the array numOfTerms[].
            t++;                     // increase t by 1.
        }
        for(int j = 0; j < t; j++)
        {
            terms[j] = numOfTerms[j];              // copy the contents of the array numOfTerms[] to the array terms[].
        }
        /* after the above step, we Know the number of equation that exist in the file, and the number of terms in each equation.*/
        // Second Step //
        // first, i divide each equation according to (+) character, and store the results in an array divided_Equations1[].
        int numOfTermsWithPlus = 0;
        for (int  i = 0; i < numOfEquation; i++ )
        {
            token = strtok(linesInFile[i],"+");
            while(token != NULL)
            {
                strcpy(divided_Equations1[numOfTermsWithPlus],token);
                numOfTermsWithPlus++;
                token = strtok(NULL,"+");
            }
        }
        // now, i check each element in the array divided_Equation1[] if it has a (-) character or not.
        // declare two local variables we use them in the step below.
        float flo;
        char temp[5];
        for(int y = 0; y < numOfTermsWithPlus; y++)
        {
            counter = 0;
            if(strchr(divided_Equations1[y],'-') != NULL)         // if the term has (-) character, then there are two cases.
            {
                if(strncmp(divided_Equations1[y],"-",1) == 0)     // the first case if the (-) character is at the first position.
                {
                    token = strtok(divided_Equations1[y],"-");    // then divide according to (-) char.
                    while(token != NULL)
                    {
                        strcpy(str,"-");
                        strcpy(temp,"");
                        // if the term is as => (-x ,-2x,-7x...) with out (^).
                        if(strchr(token,'x') != NULL && strchr(token,'^') == NULL )
                        {
                            flo = atof(token);          // take the float value of the term.
                            if (flo == 0)               // check if the float value is 0, then the float value must be (-1).
                            {
                                flo = -1;               // set float to -1.
                                gcvt(flo,3,temp);       // convert the float value to string (Array of char[]).
                                strcat(temp,"x");        // concatenate the float value with (x) then the term is => (-1.0x).
                                strcpy(divided_Equations2[k],temp);   // copy the term in the Array divided_Equations2[].
                            }
                            else          // if the float value doesn't 0.
                            {
                                gcvt(flo,3,temp);     // convert the float value to string (Array of char[]).
                                strcat(str,temp);
                                strcat(str,"x");
                                strcpy(divided_Equations2[k],str);
                            }
                        }
                        else
                        {
                            strcat(str,token);
                            strcpy(divided_Equations2[k],str);
                        }
                        k++;
                        token = strtok(NULL,"-");
                    }
                }
                else
                {
                    token = strtok(divided_Equations1[y],"-");  // the second case if it has a (-) character at other positions.
                    while(token != NULL)
                    {
                        counter++;
                        if(counter >1)
                        {
                            strcpy(str,"-");
                            strcpy(temp,"");
                            if(strchr(token,'x') != NULL && strchr(token,'^') == NULL )
                            {
                                flo = atof(token);
                                if (flo ==0)
                                {
                                    flo =-1;
                                    gcvt(flo,3,temp);
                                    strcat(temp,"x");
                                    strcpy(divided_Equations2[k],temp);
                                }
                                else
                                {
                                    gcvt(flo,3,temp);
                                    strcat(str,temp);
                                    strcat(str,"x");
                                    strcpy(divided_Equations2[k],str);
                                }
                                k++;
                            }
                            else
                            {
                                strcat(str,token);
                                strcpy(divided_Equations2[k],str);
                                k++;
                            }
                        }
                        else
                        {
                            strcpy(divided_Equations2[k],token);
                            k++;
                        }
                        token = strtok(NULL,"-");
                    }
                }
            }
            else        // if the term doesn't have (-) character, them we add it as it is to the Array divided_equation2[].
            {
                strcpy(divided_Equations2[k],divided_Equations1[y]);
                k++;
            }
        }
        // stores the coefficients and exponents in arrays.
        int flip = 0;
        for(int j = 0; j<k; j++)
        {
            if(strchr(divided_Equations2[j],'^') != NULL)
            {
                count = 0;
                if (strchr(divided_Equations2[j],'-') != NULL)
                {
                    if(atof(divided_Equations2[j]) == 0)
                        coeff[flip] = -1;
                    else
                        coeff[flip] = atof(divided_Equations2[j]);
                }
                else
                {
                    if(atof(divided_Equations2[j]) == 0)
                        coeff[flip] = 1;
                    else
                        coeff[flip] = atof(divided_Equations2[j]);
                }
                token = strtok(divided_Equations2[j],"^");
                while (token != NULL)
                {
                    count ++;
                    if(count >1)
                    {
                        expo[flip] = (int)atoi(token);
                    }
                    token = strtok(NULL,"^");
                }

            }
            else if (strchr(divided_Equations2[j],'^') == NULL)
            {
                if(atof(divided_Equations2[j]) == 0)
                {
                    if (strchr(divided_Equations2[j],'-') != NULL)
                        coeff[flip] = -1;
                    else
                        coeff[flip] = 1;
                    expo[flip] = 1;
                }
                else
                {
                    coeff[flip] = atof(divided_Equations2[j]);
                    if(strchr(divided_Equations2[j],'x'))
                        expo[flip] = 1;
                    else
                        expo[flip] = 0;
                }
            }
            flip++;
        }
    }
    else
    {
        // if the opening file operation is fail.
        puts("Can't open the file to read data from it ! check the file name.");

    }
    // fclose(infile);          // closing the file.
}
// the function storeFile() used to fill the array of linked list by data .
int l = 0;
int i = 0;
ptr storeFile(ptr start)
{
    int count = 0;           /* declare a local variable (count) to count the nodes in each linked list,
                        the number of nodes in each linked list must equal the number of term in each equation.*/
    // declare two node pointers, the first one for the new node, the second to point to the first node in linked list.
    ptr new_node, P;
    while(count != terms[i])        // check if the counter (count) is equal to the number of terms in equation 1,2,3...
    {
        if(start == NULL)             // check if the start node is NULL, then the new_node must be the first node.
        {
            new_node = (ptr) malloc(sizeof(struct Node));
            if (new_node != NULL)
            {
                new_node -> previous = new_node -> next = NULL;
                new_node -> coefficient = coeff[l];
                new_node -> exponent = expo[l];
                P = start = new_node;
            }
            else
            {
                puts("Sorry ! There is no out space in memory !");
            }
        }
        else
        {
            new_node = (ptr) malloc(sizeof(struct Node));
            if (new_node != NULL)
            {
                P = start;
                while(P->next != NULL)
                {
                    P = P->next;
                }
                new_node -> coefficient = coeff[l];
                new_node -> exponent = expo[l];
                new_node-> next = NULL;
                P -> next = new_node;
                new_node -> previous = P;
                P = new_node;
            }
            else
            {
                puts("Sorry ! There is no out space in memory !");
            }
        }
        count++;
        l++;
    }
    i++;
    return start;
    l = count;
}
// define the function max to find the maximum exponent that exists in the doubly linked list.
int maxExp(ptr start)
{
    ptr p = start;
    int max = p -> exponent;       // declare local variable (max) and initialize it to the exponent in the first node.
    while (p != NULL)
    {
        if ((p->exponent) > max)
            max = p->exponent;
        p = p ->next;
    }
    return max;      // return the value of the maximum exponent.
}
// define the function addPolynomials() to add the polynomials that stored in the array of linked list.
ptr addPolynomials(ptr Array[MAX_SIZE],ptr sum)
{
    ptr Array2[MAX_SIZE];
    for (int j = 0; j < numOfEquation; j++)
    {
        // declare another array and copy the contents of Array[] to it, to use it to find the maximum exponent in all equations.
        Array2[j] = Array[j];
    }
    int max = maxExp(Array2[0]);  // declare local variable max and initialize it the maximum exponent in the first equation.
    for(int j = 0; j<numOfEquation; j++)
    {
        while(Array2[j] != NULL)
        {
            if ((Array2[j] ->exponent) > max)
            {
                max = Array2[j]->exponent;
            }
            Array2[j] = Array2[j]->next;
        }
    }
    // now we know the maximum value of exponent in all equations.
    ptr Array3[MAX_SIZE];
    float s = 0;
    ptr new_node;
    ptr p;
    i = max;
    while(i >= 0)
    {
        for (int j = 0; j < numOfEquation; j++)
        {
            Array3[j] = Array[j];
        }
        if(sum == NULL)
        {
            new_node = (ptr) malloc(sizeof(struct Node));
            if (new_node != NULL)
            {
                new_node -> previous = new_node -> next = NULL;
                for(int j = 0; j < numOfEquation; j++)
                {
                    while(Array3[j] != NULL)
                    {
                        if (Array3[j]->exponent == i)
                        {
                            s += Array3[j]->coefficient;
                        }
                        Array3[j] = Array3[j]->next;
                    }
                }
                new_node->coefficient = s;
                new_node -> exponent = i;
            }
            sum = new_node;
        }
        else
        {
            s = 0;
            new_node = (ptr) malloc(sizeof(struct Node));
            if (new_node != NULL)
            {
                p = sum;
                while(p->next != NULL)
                {
                    p = p->next;
                }
                new_node-> next = NULL;
                p -> next = new_node;
                new_node -> previous = p;
                for(int j =0; j < numOfEquation; j++)
                {
                    while(Array3[j] != NULL)
                    {
                        if (Array3[j]->exponent == i)
                        {
                            s += Array3[j]->coefficient;
                        }
                        Array3[j] = Array3[j]->next;

                    }
                }
                new_node->coefficient = s;
                new_node -> exponent = i;
                p = new_node;
            }
        }
        i--;

    }
    return sum;           // return the node.
}
// define a function to subtract polynomials.
ptr subPolynomials(ptr Array[MAX_SIZE],ptr sub)
{
    ptr Array2[MAX_SIZE];
    for (int j = 0; j < numOfEquation; j++)
    {
        Array2[j] = Array[j];
    }
    int max = maxExp(Array2[0]);
    for(int j =0; j<numOfEquation; j++)
    {
        while(Array2[j] != NULL)
        {
            if (Array2[j] ->exponent > max)
                max = Array2[j]->exponent;       // the maximum power.
            Array2[j] = Array2[j]->next;
        }
    }
    // now we know the maximum value of exponent in all equations.
    ptr Array3[MAX_SIZE];
    float s = 0;
    ptr new_node;
    ptr p;
    i = max;
    int counter =0;
    while(i >= 0)
    {
        counter = 0;
        s = 0;
        for (int j = 0; j < numOfEquation; j++)
        {
            Array3[j] = Array[j];
        }
        if(sub == NULL)
        {
            new_node = (ptr) malloc(sizeof(struct Node));
            if (new_node != NULL)
            {
                new_node -> previous = new_node -> next = NULL;
                for(int j = 0; j < numOfEquation; j++)
                {
                    while(Array3[j] != NULL)
                    {
                        if (Array3[j]->exponent == i)
                        {
                            counter++;
                            if (counter>1)
                            {
                                s -= Array3[j]->coefficient;
                            }
                            else
                            {
                                s = Array3[j]->coefficient - s;
                            }
                        }
                        Array3[j] = Array3[j]->next;
                    }
                }
                new_node->coefficient = s;
                new_node -> exponent = i;
            }
            sub = new_node;
        }
        else
        {
            new_node = (ptr) malloc(sizeof(struct Node));
            if (new_node != NULL)
            {
                p = sub;
                while(p->next != NULL)
                {
                    p = p->next;
                }
                new_node-> next = NULL;
                p -> next = new_node;
                new_node -> previous = p;
                for(int j =0; j < numOfEquation; j++)
                {
                    while(Array3[j] != NULL)
                    {
                        if (Array3[j]->exponent == i)
                        {
                            counter++;
                            if (counter>1)
                            {
                                s -= Array3[j]->coefficient;
                            }
                            else
                            {
                                s = Array3[j]->coefficient - s;
                            }

                        }
                        Array3[j] = Array3[j]->next;
                    }
                }
                new_node->coefficient = s;
                new_node -> exponent = i;
                p = new_node;
            }
        }
        i--;
    }
    return sub;
}
// define a function to multiply two polynomials, then we can call it many times.
ptr multiplayPolynomials(ptr arr1,ptr arr2,ptr mul)
{
    ptr new_node,p,arr3;
    float co,co1,co2;
    int ex,ex1,ex2;
    while(arr1 != NULL)
    {
        arr3 = arr2;
        while(arr3 != NULL)
        {
            co1 = arr1->coefficient;
            ex1 = arr1->exponent;
            if (mul == NULL)
            {
                new_node = (ptr) malloc (sizeof(struct Node));
                new_node->next = new_node->previous = NULL;
                if (new_node != NULL)
                {
                    if(arr3 != NULL)
                    {
                        co1 = arr1->coefficient;
                        ex1 = arr1->exponent;
                        co2 = arr3->coefficient;
                        ex2 = arr3->exponent;
                        co = co1 * co2;
                        ex = ex1 + ex2;
                        new_node->coefficient = co;
                        new_node->exponent = ex;
                        mul = new_node;
                    }
                }
            }
            else
            {
                new_node = (ptr) malloc (sizeof(struct Node));
                if (new_node != NULL)
                {
                    p = mul;
                    while(p->next != NULL)
                    {
                        p = p->next;
                    }
                    if(arr3 != NULL)
                    {
                        co1 = arr1->coefficient;
                        ex1 = arr1->exponent;
                        co2 = arr3->coefficient;
                        ex2 = arr3->exponent;
                        co = co1 * co2;
                        ex = ex1 + ex2;
                        new_node->next = NULL;
                        new_node->previous = p;
                        p->next = new_node;
                        new_node->coefficient = co;
                        new_node->exponent = ex;
                        p = new_node;
                    }
                }
            }
            arr3 = arr3->next;
        }
        arr1 = arr1->next;
    }
    return mul;
}
// define function to display the equations to user after reading it from file.
void display(ptr start)
{
    ptr p;
    p = start;
    while(p != NULL)
    {
        if (p->coefficient != 0)
        {
            if(p->exponent == 0)
            {
                if(p->coefficient > 0)
                    printf("+%0.1f",p->coefficient);
                else
                    printf("%0.1f",p->coefficient);
            }
            else if(p->exponent == 1)
            {
                if(p->coefficient > 0)
                    printf("+%0.1fx",p->coefficient);
                else
                    printf("%0.1fx",p->coefficient);
            }
            else
            {
                if(p->coefficient > 0)
                    printf("+%0.1fx^%d", p ->coefficient,p->exponent);
                else
                    printf("%0.1fx^%d", p ->coefficient,p->exponent);
            }
        }
        p = p -> next;
    }

}
// define a function to store the result equations from the operations (addition, subtraction, multiplication) in an output file.
void displayInOutfile(ptr start,FILE *outfile)
{
    ptr p;
    p = start;
    while(p != NULL)
    {
        if (p->coefficient != 0)
        {
            if(p->exponent == 0)
            {
                if(p->coefficient > 0)
                    fprintf(outfile,"+%0.1f",p->coefficient);
                else
                    fprintf(outfile,"%0.1f",p->coefficient);
            }
            else if(p->exponent == 1)
            {
                if(p->coefficient > 0)
                    fprintf(outfile,"+%0.1fx",p->coefficient);
                else
                    fprintf(outfile,"%0.1fx",p->coefficient);
            }
            else
            {
                if(p->coefficient > 0)
                    fprintf(outfile,"+%0.1fx^%d", p ->coefficient,p->exponent);
                else
                    fprintf(outfile,"%0.1fx^%d", p ->coefficient,p->exponent);
            }
        }
        p = p -> next;
    }
    fprintf(outfile,"\n");
}
// define a function to re-arrange the equation, =>(add the terms with the same exponent with each other).
ptr rearrangeEquation(ptr equation,ptr result)
{
    ptr new_node,p,temp;
    temp = NULL;
    float s;
    int max = maxExp(equation);
    i = max;
    while(i >= 0)
    {
        s = 0;
        temp = equation;
        if(result == NULL)
        {
            new_node = (ptr) malloc(sizeof(struct Node));
            if (new_node != NULL)
            {
                new_node -> previous = new_node -> next = NULL;

                while(temp != NULL)
                {
                    if (temp->exponent == i)
                    {
                        s += temp->coefficient;
                    }
                    temp = temp->next;
                }
                new_node->coefficient = s;
                new_node -> exponent = i;
            }
            result = new_node;
        }
        else
        {
            s = 0;
            new_node = (ptr) malloc(sizeof(struct Node));
            if (new_node != NULL)
            {
                p = result;
                while(p->next != NULL)
                {
                    p = p->next;
                }
                new_node-> next = NULL;
                p -> next = new_node;
                new_node -> previous = p;
                while(temp != NULL)
                {
                    if (temp->exponent == i)
                    {
                        s += temp->coefficient;
                    }
                    temp = temp->next;

                }

                new_node->coefficient = s;
                new_node -> exponent = i;
                p = new_node;
            }
        }
        i--;
    }
    return result;
}
// define a function to allow user to substitute any value in the result equations from operations.
float substituteInResult(ptr equation,float number)
{
    float res = 0.0;
    while (equation != NULL)
    {
        res += equation->coefficient * (pow(number, equation->exponent));
        equation = equation ->next;
    }
    return res;
}
// system menu.
void showMenu()
{
    printf("\n<<< Menu >>>\n1. Read the File that contains the equations.\n2. Show the equations.");
    printf("\n3. Perform Addition operation for the polynomials.\n4. Perform Subtraction operation for the polynomials.\n");
    printf("5. Perform Multiplication operation for the polynomials.\n6. Save results.\n7. Exit the system.\n");
}
// main function.
int main()
{
    puts("Welcome to our system...");
    puts("This system helps you on reading polynomials from a file, and applying different operations on them, such as \n=> (Addition, Subtraction and Multiplication).");
    puts("***The below menu show you what you can do using this system, please select what the choice you want :).***");
    FILE* infile,*outfile;
    infile = fopen("equations.txt","r");
    outfile = fopen("results.txt","w");
    ptr mul = NULL;
    ptr add = NULL;
    ptr sub = NULL;
    int selection = 0;
    char answer[100];
    for (int j = 0; j < sizeof(Array); j++)
    {
        Array[j] = NULL;
    }
    int num = numOfEquation;
    showMenu();
    printf("\nPlease select an option from the menu : ");
    scanf("%d",&selection);
    while (selection)
    {
        switch (selection)
        {
        case 1:
            readFile(infile);
            for(int i = 0 ; i<numOfEquation; i++)
            {
                Array[i] = storeFile(Array[i]);
            }
            puts("The equations have been read successfully from the file !\n");
            showMenu();
            puts("\nEnter your selection : ");
            scanf("%d",&selection);
            break;
        case 2 :
            if (Array[0] != NULL)
            {
                puts("The equations : ");
                for(int i=0 ; i<numOfEquation; i++)
                {
                    printf("Equation[%d] => ",i+1);
                    display(Array[i]);
                    printf("\n");
                }
            }
            else
            {
                printf(" > Please select the first option to read the file then select 2 to display the equations to you :)\n");
            }
            showMenu();
            puts("\nEnter your selection : ");
            scanf("%d",&selection);
            break;
        case 3:
            if (Array[0] != NULL)
            {
                add = NULL;
                printf("The result from adding all polynomials >> ");
                add = addPolynomials(Array,add);
                display(add);
                printf("\n > Do you want to substitute any value in the result equation ? (Answer => yes or no )\nAnswer >> ");
                strcpy(answer,"");
                scanf("%s",&answer);
                float number = 0;
                if (strcmp(answer,"yes") == 0)
                {
                    printf("Enter the floating point or integer number you want to substitute : ");
                    scanf("%f",&number);
                    float result = (float)substituteInResult(add,number);
                    printf("The result from substitute %.2f in the equation = %.3f\n",number,result);
                }
                else if (strcmp(answer,"no") == 0)
                {
                    puts("Ok :)");
                }
            }
            else
            {
                printf(" > Please select the first option to read and store the equation then you can choose this option to add them :)\n");
            }
            showMenu();
            puts("\nEnter your selection : ");
            scanf("%d",&selection);
            break;
        case 4:
            if (Array[0] != NULL)
            {
                sub = NULL;
                printf("The result from Subtracting all polynomials >> ");
                sub = subPolynomials(Array,sub);
                display(sub);
                printf("\n > Do you want to substitute any value in the result equation ? (Answer => yes or no )\nAnswer >> ");
                strcpy(answer,"");
                scanf("%s",&answer);
                float number = 0;
                if (strcmp(answer,"yes") == 0)
                {
                    printf("Enter the floating point or integer number you want to substitute : ");
                    scanf("%f",&number);
                    float result = (float)substituteInResult(sub,number);
                    printf("The result from substitute %.2f in the equation = %.3f\n",number,result);
                }
                else if (strcmp(answer,"no") == 0)
                {
                    puts("Ok :)");
                }
            }
            else
            {
                printf(" > Please select the first option to read and store the equation then you can choose this option to subtract them :)\n");
            }
            showMenu();
            puts("\nEnter your selection : ");
            scanf("%d",&selection);
            break;
        case 5:
            if (Array[0] != NULL)
            {
                num = numOfEquation;
                if (num >= 1 && num <=5)
                {
                    puts("\nThe result from multiplying all polynomials :\n");
                    mul = NULL;
                    if (num == 1)
                    {
                        mul = Array[0];
                    }
                    else if (num == 2)
                    {
                        ptr mul_1 = NULL;
                        int i = 0;
                        mul_1 = multiplayPolynomials(Array[i],Array[i+1],mul_1);
                        mul = rearrangeEquation(mul_1,mul);
                        display(mul);
                    }
                    else if(num == 3)
                    {
                        ptr mul_1 = NULL;
                        int i =0;
                        mul_1 = multiplayPolynomials(Array[i],Array[i+1],mul_1);
                        i+=2;
                        ptr mul_2 = NULL;
                        mul_2 = multiplayPolynomials(mul_1,Array[i],mul_2);
                        mul = rearrangeEquation(mul_2,mul);
                        display(mul);
                    }
                    else if (num == 4)
                    {
                        ptr mul_1 = NULL;
                        mul_1 = multiplayPolynomials(Array[0],Array[1],mul_1);
                        ptr mul_2 = NULL;
                        mul_2 = multiplayPolynomials(Array[2],Array[3],mul_2);
                        ptr mul_3 = NULL;
                        mul_3 = multiplayPolynomials(mul_1,mul_2,mul_3);
                        mul = rearrangeEquation(mul_3,mul);
                        display(mul);
                    }
                    else if (num == 5)
                    {
                        ptr mul_1 = NULL;
                        mul_1 = multiplayPolynomials(Array[0],Array[1],mul_1);
                        ptr mul_2 = NULL;
                        mul_2 = multiplayPolynomials(Array[2],Array[3],mul_2);
                        ptr mul_3 = NULL;
                        mul_3 = multiplayPolynomials(mul_1,mul_2,mul_3);
                        ptr mul_4 = NULL;
                        mul_4 = multiplayPolynomials(mul_3,Array[4],mul_4);
                        mul = rearrangeEquation(mul_4,mul);
                        display(mul);
                    }
                    printf("\n > Do you want to substitute any value in the result equation ? (Answer => yes or no )\nAnswer >> ");
                    strcpy(answer,"");
                    scanf("%s",&answer);
                    float number = 0;
                    if (strcmp(answer,"yes") == 0)
                    {
                        printf("Enter the floating point or integer number you want to substitute : ");
                        scanf("%f",&number);
                        float result = (float)substituteInResult(mul,number);
                        printf("The result from substitute %.2f in the equation = %.3f\n",number,result);
                    }
                    else if (strcmp(answer,"no") == 0)
                    {
                        puts("Ok :)");
                    }
                }
                else
                {
                    puts("This system can only multiply at most 5 equation !");
                }
            }
            else
            {
                printf(" > Please select the first option to read and store the equation then you can choose this option to multiply them :)\n");
            }
            showMenu();
            puts("\nEnter your selection : ");
            scanf("%d",&selection);
            break;
        case 6:
            if (Array[0] != NULL)
            {
                if(add == NULL && sub == NULL && mul == NULL)
                {
                    printf(" > There is no result from applying operations to save it !!\n>>Make sure you select one or more operation from the menu\n> (operations => 3, 4 or 5).");
                }
                else
                {
                    fprintf(outfile,">>The result from addition operation :\n");
                    displayInOutfile(add,outfile);
                    fprintf(outfile,">>The result from subtraction operation :\n");
                    displayInOutfile(sub,outfile);
                    fprintf(outfile,">>The result from multiplication operation :\n");
                    displayInOutfile(mul,outfile);
                    printf("The results are saved successfully in the output file.\n");
                    fclose(outfile);

                }
            }
            else
            {
                printf(" > Please select the first option to read and store the equations then select any operation you want to do, then select save option :) !\n\n");
            }
            showMenu();
            puts("\nEnter your selection : ");
            scanf("%d",&selection);
            break;
        case 7:
            printf("> Good Bye ! ");
            exit(0);
            break;
        default:
            printf(" > Please select one of the options that appears in the menu :).\n");
            showMenu();
            puts("\nEnter your selection : ");
            scanf("%d",&selection);
            break;
        }
    }
    fclose(infile);
}



