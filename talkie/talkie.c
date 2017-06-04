/* This is a simple AI algorithm that tries to establish a conversation
 * with the user to finally decide whether to like or dislike him/her. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
	char *name = (char *) calloc (25, sizeof (char));
	char *favColor = (char *) calloc (20, sizeof (char));
	char *favAnimal = (char *) calloc (25, sizeof (char));
	int GOOD = 0, NEUTRAL = 0, BAD = 0;
	char choice[10];

	/* get user name */
	printf ("Hello, my name is Talkie Z-81A, but people call me Jenny.\n"
			"What is your name? ");
	scanf ("%24s", name);
	name = (char *) realloc (name, (strlen (name) + 1) * sizeof (char));
	printf ("Hello, %s. Pleased to meet you.\n", name);
	
	/* get user's favorite color; does it match Jenny's favorite colors? */
	printf ("I like blue and green, but not so much orange and pink.\n"
			"What is your favorite color? ");
	scanf ("%19s", favColor);
	favColor = (char *) realloc (favColor, (strlen (favColor) + 1) * sizeof (char));
	
	if ( strcmp (favColor, "blue") == 0 || strcmp (favColor, "green") == 0 )
		GOOD++;
	else if ( strcmp (favColor, "orange") == 0 || strcmp (favColor, "pink" ) == 0 )
		BAD++;
	else
		NEUTRAL++;
	
	/* get user's favorite animal; does it match Jenny's favorite animal? */
	printf ("You know, I really like cats and dogs, but just detest sharks"
			" and squidds.\nWhat is your favorite animal? ");
	scanf ("%24s", favAnimal);
	favAnimal = (char *) realloc (favAnimal, (strlen (favAnimal) + 1) * sizeof (char));
	
	if ( strcmp (favAnimal, "cat") == 0 || strcmp (favAnimal, "dog") == 0 )
		GOOD++;
	else if ( strcmp (favAnimal, "squid") == 0 || strcmp (favAnimal, "shark") == 0 )
		BAD++;
	else
		NEUTRAL++;
	
	/* clean-up - we don't need those pointers anymore */
	free (name);
	free (favColor);
	free (favAnimal);
	
	/* does the user and Jenny have anything in common? */
	if ( GOOD > BAD && GOOD > NEUTRAL ) {
		printf ("It seems to me we have quite some things in common.\nWould you like"
				" to be friends? ");
		scanf ("%9s", choice);
		
		switch ( choice[0] ) {
			case 'y':
				printf ("Call me? ;)\n");
				exit (EXIT_SUCCESS);
			case 'n':
				printf ("Ouch, too bad. Maybe some other time?\n");
				exit (EXIT_SUCCESS);
			default:
				printf ("Erm, not sure I understood that...\nHow about we start from"
						" the very beginning?\n");
				exit (EXIT_SUCCESS);
		}
	} else if ( BAD > GOOD && BAD > NEUTRAL ) {
		printf ("I don't think we would get along at all. Sorry! :(\n");
		exit (EXIT_SUCCESS);
	} else {
		printf ("We don't really have anything in common, but maybe we could still get"
				" along?\nWhat do you think?\n");
		exit (EXIT_SUCCESS);
	}
	
		
	return 0;
}
