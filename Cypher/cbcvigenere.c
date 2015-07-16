
//------------------------------------------------------------------

// University of Central Florida

// CIS3360 - Summer 2015

// Program Author: Angelo Contreras-Montagner

//------------------------------------------------------------------

#include<stdio.h>
#include <ctype.h>
#include <string.h>



int convertChartoInt(char c);
char convertInttoChar (int i);

int main(int argc, char *argv[]) {

    char fileArray[10000];
    char FinalEncryption[10000];

    char* Keywordtemp = argv[ 2 ];

    int blockSize = strlen(Keywordtemp);

    char XORblock[blockSize];
    char Viegeblock[blockSize];

    char* Keyword = argv[ 2 ];
    char* IV =argv[ 3 ];

    int end=0;
    int tokenCounter=0;
    FILE *input;
    int ArrayPosition = 0;
    int Words=0;
    int i=0, finished = 0, TotalcharacterCount=0, loopArray=0;
    char c, nextChar;
    int tempblockSize = blockSize;
    int XORSum=0;
    int ViegeSum=0;
    int tempTotalcharacterCount=0;
    int Upcounter=0;
    int FinalUpcounter=0;
    int InitialBlock = 1;
    int A,B;
    int Padnumber = 0;
    int TotalCleanChars;
    int Linecounter=0;

    char* fname = argv[ 1 ];

    input = fopen( fname, "r" );

    while (!feof(input))
    {
        c = fgetc (input);

        if(isalpha(c))
        {
            fileArray[i] = tolower(c);
            TotalcharacterCount++;
            i++;
        }

    }

    TotalCleanChars = strlen(fileArray);

    printf("PlainText file name: %s\n", fname);
    printf("Vigenere Keyword: %s\n", Keyword);
    printf("Initialization Vector: %s\n", IV);
    printf("\n");
    printf("Clean Plaintext:\n");

    printf("\n");


    for (i=0;i<TotalcharacterCount;i++)
    {
        printf("%c", fileArray[i]);

        Linecounter++;
        if(Linecounter == 80)
        {
            Linecounter = 0;
            printf("\n");
        }

    }
    printf("\n");


    Padnumber = (strlen(fileArray)) % blockSize;
    Padnumber = blockSize - Padnumber;


    if(Padnumber != 0)
    {

        for(i=0;i<Padnumber;i++)
        {
            fileArray[TotalcharacterCount] = 'x';
            TotalcharacterCount++;
        }
    }


    while (tempTotalcharacterCount < TotalcharacterCount)
    {
        tempblockSize = blockSize;

        if(InitialBlock == 1)
        {


            for (i=0;i<blockSize;i++)
            {
                A= convertChartoInt(fileArray[Upcounter]);
                B= convertChartoInt(IV[i]);

                XORSum= ((A + B) % 26);

                XORblock[i]=  convertInttoChar(XORSum);

                Upcounter++;

            }


            InitialBlock=0;

        }else{



            for (i=0;i<blockSize;i++)
            {

                A= convertChartoInt(fileArray[Upcounter]);

                B= convertChartoInt(Viegeblock[i]);


                XORSum= ((A+B) % 26);

                XORblock[i]=  convertInttoChar(XORSum);

                Upcounter++;

            }



        }


        tempTotalcharacterCount = tempTotalcharacterCount + blockSize;



        for (i=0;i<blockSize;i++)
        {

            A= convertChartoInt(XORblock[i]);
            B= convertChartoInt(Keyword[i]);

            ViegeSum= (A+B) % 26;
            Viegeblock[i]=   convertInttoChar (ViegeSum);

        }

        for (i=0;i<blockSize;i++)
        {
        FinalEncryption[FinalUpcounter]= Viegeblock[i];

        FinalUpcounter++;
        }

    }

        printf("\n");

        printf("Ciphertext:\n");

        printf("\n");


        Linecounter=0;

        for(i=0;i<TotalcharacterCount;i++)
        {
            printf("%c",   FinalEncryption[i]);

            Linecounter++;
            if(Linecounter == 80)
            {
                Linecounter = 0;
                printf("\n");
            }
        }

         printf("\n\n");

        printf("Number of characters in clean plaintext file: %i\n", TotalCleanChars);
        printf("Block size =  %i\n", blockSize);
        printf("Number of pad characters added: %i\n", Padnumber);

        printf("\n");

}


int convertChartoInt (char c)
{

return c - 'a';

}


char convertInttoChar (int i)
{
   return (char) i + 'a';


}
