#include <stdlib.h>
#include <time.h>

unsigned char *gen_rdm_bytestream (size_t num_bytes)
{
  unsigned char *stream = malloc (num_bytes);
  size_t i;

  for (i = 0; i < num_bytes; i++)
  {
    stream[i] = rand ();
  }

  return stream;
}

int main(){
	FILE *fp;
	fp = fopen(FileName, "r");
	if(fp == NULL){
		printf("Error in opening input file\n");
		return NULL;
	}
	
	randomize( ) ;

	for (i = 0 ; i < noofr ; i++ )
	{
		j = random ( 1000 ) ;
		fwrite ( &j, sizeof ( int ), 1, fp ) ;
		printf ( "%d\t", j ) ;
	}
	
	 fclose ( fp ) ;

    printf ( "\nFile is created. \nPress any key to continue." ) ;
}
