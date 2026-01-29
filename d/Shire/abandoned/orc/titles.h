/*
 *  /d/Shire/guild/estehilde/estehilde.h
 *
 *  This file contains the defines with the titles of the Estehilde.
 *  Jaypeg, June 1999
 * 
 */
/*
 * In LONGEST_NAME you will find the value of the longest family name.
 */
#define LONGEST_NAME 5


/* NUM_TITLES should define the number of titles possible.
 * These defines should contain exactly that number of titles.
 */
#define NUM_TITLES    7

/* Everyone with SS_OCCUP >= MAX_SS_OCCUP will get the maximum title.
 */
#define MAX_SS_OCCUP  100 


/* This define contains the strlen() of the longest title in the TITLES
 * define.
 */
#define LONGEST_TITLE 22

/* The possible titles for the members of the Dunlinde guild. The number
 * of titles must equal the number of descriptions possible for beards and
 * it must also equal the number set in NUM_TITLES.
 */
#define TITLES  \
    ({ "of the Great Eye", \
       "of the Mines", \
       "of the White Hand",  \
       "of the Red Eye", \
       "of the Disfigured Moon", \
       "of the Mountains", \
       "of the Dark Tower" \
       })
