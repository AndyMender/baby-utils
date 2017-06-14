/* This is a simple dictionary program that uses a text file to store 
 * records of keywords and definitions and allows their lookup. */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* simple dictionary entry structure */
struct entry
{
	char name[20];
	char definition[80];
};

struct entry dictionary[100];

/* takes an open FILE object, loads the dictionary records into an array
 * and returns a pointer to that array */
struct entry *dictLoader (FILE *dictFile)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	
	/* read lines into colon-separated name and definition of dictionary 
	 * as entries until end of file */
	while ( ( read = getline (&line, &len, dictFile) ) != -1 )
	{
		static int i = 0;
		sscanf (line, "%[^:]: %[^\n]", dictionary[i].name, dictionary[i].definition);
		i++;
	}
	
	return dictionary;
}

/* takes a pointer to a dictionary array, looks for a matching word and returns
 * a pointer pointing to it */ 
struct entry *dictLookup (struct entry *dictPtr, const char *keyword)
{
	for ( ; *dictPtr->name != 0; dictPtr++ )
		if ( strcmp (dictPtr->name, keyword) == 0 )
			return dictPtr;
			
	/* Fall through - no matching entry found in dictionary */
	return NULL;
}

int main (const int argc, const char *argv[])
{
	/* function prototypes */
	struct entry *dictLoader (FILE *dictFile);
	struct entry *dictLookup (struct entry *dictPtr, const char *keyword);
	
	/* variable definitions */
	FILE *dictFile;
	struct entry *matchPtr;
	char choice;
	char newDefinition[80];
	
	/* if no arguments are given, print a short help message */
	if ( argc == 1 )
	{
		printf ("No arguments were specified.\n"
				"Use: dictlook <word> [dictionary file]\n");
		exit (EXIT_SUCCESS);
	}
	
	/* exit with error if too many arguments were given */
	if ( argc > 3 )
	{
		fprintf (stderr, "Too many arguments were specified: %i\n"
				 "Use: dictlook <word> [dictionary file]\n", argc);
		exit (EXIT_FAILURE);
	}
	
	if ( argc == 2 )
	{
		dictFile = fopen (argv[2], "r+");
		/* if dictionary file doesn't exist, fall back to default */
		if ( dictFile == NULL )
				dictFile = fopen ("words.txt", "r+");
	}
	
	/* can be separated into 2 calls for better clarity */
	matchPtr = dictLookup (dictLoader (dictFile), argv[1]);
	
	/* was the record found? */
	if ( matchPtr != NULL )
		printf ("%s: %s\n", matchPtr->name, matchPtr->definition);
	else
	{
		printf ("Word %s not found in dictionary.\n", argv[1]);
		printf ("Would you like to add it?(y/n) ");
		scanf ("%c", &choice);
		
		switch ( choice )
		{
			case 'y':
				printf ("What is the definition of the keyword? ");
				scanf (" %[^\n]", newDefinition);
				fprintf (dictFile, "%s: %s\n", argv[1], newDefinition);
				exit (EXIT_SUCCESS);
				break;
			case 'n':
				printf ("Oh well, too bad!\n");
				exit (EXIT_SUCCESS);
				break;
			default:
				printf ("Well now, something went wrong...\n");
				exit (EXIT_FAILURE);
		}
	}
		
	return 0;
}
