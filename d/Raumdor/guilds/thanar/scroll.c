/*
 * - scroll.c
 *
 * This file contains support functions for use in printing pseudo
 * scrolls to a players screen.  It is still rather experimental.
 *
 * To use:
 *  - Inherit this file, then call 'print_scroll' where needed.
 *
 * Yes, I am well aware the two defines look like cryptic scrambled
 * pieces of goo that have been splattered against a wall, but trust
 * me, they look pretty when printed ;)
 *
 * If you alter them at all, you will probably ruin the scroll, be warned.
 * Only change them if you wish to alter how the scroll looks and you
 * at least have some idea of what your doing.
 *
 * 						--= Lucius Kane
 */

/*
 * The top of the scroll, this should remain static.
 */
#define HEAD \
"  __________________________________________________________________________\n"    + \
" / \\                                                                        \\\n" + \
"|\\_/___-____________-______/|________--___|\\______-______-___-_/|_____/\\____/|\n"+"|                                                                            |\n"    
    


/*
 * The bottom portion of the scroll, this should remain static.
 */
#define TAIL \
"\n| ___ ____  ________ ___________________  __________________ __________ _____|\n"  + \
"|/\\  -    |/        -                   |/                    -       -      \\\n" + \
"\\\\_|_________________________________________________________________________/\n"

/*
 * Function name: print_scroll
 * Description	: Print out a pseudo-scroll to a player.
 * Arguments	: string *arr - The data of the scroll, it should
 * 			be an array of strings that can be formed
 * 			into a table without difficulty.
 * 		  string title - Optional title string to place at
 * 		  	the top of the scroll.
 * 		  object who - (Default: this_player()) This is who
 * 		  	the scroll will be printed out to if set.
 * Returns	: 1/0 - Success/Failure.
 */
public varargs int
print_scroll(string *arr, string title, object who)
{
    int sz;
    mixed tmp;
    object old;

    if (!pointerp(arr) || !sizeof(arr))
	return 0;

    if (objectp(who) && who != this_player())
    {
	old = this_player();
	set_this_player(who);
    }

    tmp = sprintf("%#-*s", 77, implode(arr, "\n"));
    arr  = explode(tmp, "\n");
    sz = sizeof(arr);

    while(sz--)
    {
	arr[sz] = sprintf("|  %*-s |", 73, arr[sz]); 
    }
	
    write(HEAD);
    if (strlen(title))
    {
	write(sprintf("| %|74s |\n|%' '76s|\n", title, ""));
    }
    write(implode(arr, "\n"));
    write(TAIL);

    if (objectp(old))
    {
	set_this_player(old);
    }
    return 1;
}

