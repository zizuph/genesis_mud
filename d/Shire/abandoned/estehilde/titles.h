/*
 *  /d/Shire/guild/estehilde/estehilde.h
 *
 *  This file contains the defines with the titles of the Estehilde.
 *  Jaypeg, June 1999
 * 
 */

/* NUM_TITLES should define the number of titles possible.
 * These defines should contain exactly that number of titles.
 */
#define NUM_TITLES    20

/* Everyone with SS_OCCUP >= MAX_SS_OCCUP will get the maximum title.
 */
#define MAX_SS_OCCUP  180 


/* This define contains the strlen() of the longest title in the TITLES
 * define.
 */
#define LONGEST_TITLE 17

/* The possible titles for the members of the Trickster guild. The number
 * of titles must equal the number of descriptions possible for beards and
 * it must also equal the number set in NUM_TITLES.
 */
#define TITLES          \
    ({ "Altar Servant",       \
       "Acolyte",      \
       "Seeker",      \
       "Inquirer", \
       "Lover",        \
       "Student",        \
       "Auspicer",       \
       "Diviner",        \
       "Devout Follower",    \
       "Messenger",      \
       "Scholar",    \
       "Faithful Follower",       \
       "Agent",      \
       "Voice",       \
       "Cantor",  \
       "Speaker",     \
       "Herald",     \
       "Jewel",    \
       "Farseer",     \
       "High Speaker"       \
       })
