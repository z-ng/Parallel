//
// Torbert, 4 Sept 2015
//
#include <stdio.h>
#include <math.h>
//
//  


int main()
{
    FILE* fin = fopen( "decodeME.txt" , "r" ) ;
    char ch ;
    int n = 0 ;
    int numbytes ;
    char tree[1001000] = {'\0'};
    int m = 0;
    char element = '\0';
    int counter = 1;
    int frequency[256] = {0};
    
    while (1)
    {
        numbytes = fread( &ch , sizeof(char) , 1 , fin ) ;
        if (ch == '\n')
            break;
        m = (m*10) + (ch - 48);
    }
    
    printf("%i is the num characters\n", m);
    for (int x = 0; x < m; x = x+1)
    {
        while(1)
        {
            numbytes = fread( &ch , sizeof(char) , 1 , fin ) ;
            if (ch == '\n')
            {
                break;
            }
            
            if (ch != '0' && ch != '1')
            {
                element = ch;
            }
            else
            {
                if (ch == '0')
                    counter = counter*2;
                else
                    counter = (counter*2) + 1;
                //printf("%i\n", counter);
                //printf("%c", element);
            }
        }
        tree[counter] = element;
        printf("%i ", counter);
        printf("%c ", element); 
        printf("%c", '\n');
        counter = 1;
    }
    
    printf("%c", '\n');
    double encodedBits = 0;
    double decodedBits = 0;
    counter = 1;
    int totalCharacters = 0;
    
    while (1)
    {
        numbytes = fread( &ch , sizeof(char) , 1 , fin ) ;
        if (ch == '\n')
        {
            break;
        }
        
        if (ch == '1')
            counter = (counter*2)+1;
        else
            counter = (counter*2);
        
        encodedBits = encodedBits + 1.0;
        
        if (tree[counter] != '\0')
        {
            printf("%c", tree[counter]);

            decodedBits = decodedBits + 8.0;
            frequency[(int)tree[counter]] = frequency[(int)tree[counter]] + 1;
            counter = 1;
            totalCharacters += 1;
        }
    }
    
    printf("%c", '\n');
    printf("%c", '\n');
    printf("%f\n", (decodedBits-encodedBits)/decodedBits); 
    double minimumNumberBits = 0;
    
    for(int x = 0; x < 256; x++)
    {
        if(frequency[x] != 0)
        {
            minimumNumberBits = minimumNumberBits + (frequency[x] * -log2((double)frequency[x]/(double)totalCharacters));
        }
		//printf("%d", x);
    }
    
    printf("%f\n", minimumNumberBits); 
    
    
    //goto website
    // shannon = frequency - log2 prob
    //then write own encoder
}
