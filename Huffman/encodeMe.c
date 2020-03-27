#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
	char symbol ;
	int frequency ;
	struct Node* left ;
	struct Node* right ;
	
} TreeNode ;

int main( int argc , char* argv[] )
{
	FILE* fin = fopen( "encodeME.txt" , "r" ) ;
	char ch ;
	int n = 0 ;
	int numbytes ;


	while( 1 )
	{
		numbytes = fread( &ch , sizeof(char) , 1 , fin ) ;
	}

	fclose( fin ) ;
	printf( "\n" ) ;
	printf( "%d\n" , n ) ;
	printf( "\n" ) ;

	TreeNode* t = NULL ;
		t = (TreeNode*)malloc( sizeof(TreeNode) );
		(*t).symbol = '\0' ;
	t -> frequency = 7 ;
	t -> left = NULL ;
	t -> right = NULL ;
		printf( "%c\n" , t->symbol ) ;
	printf( "%d\n" , t->frequency ) ;
		return 0 ;
}
