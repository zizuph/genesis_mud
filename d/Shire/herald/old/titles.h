/*
 * /d/Shire/herald/titles.h
 *
 * This file contains the defines with the titles and beard descriptions
 * possible for members of the Heralds of the Valar.
 * 
 * /Mercade, 28 October 1994
 * From Mercade's Dwarf Titles
 * Dunstable March 26, 1995
 * Revision history:
 */

/* NUM_TITLES should define the number of titles possible, as they are
 * defined in BEARD_DESCRIPTIONS and TITLES. Those defines should contain
 * exactly that much descriptions and titles.
 */
#define NUM_TITLES    20

/* Everyone with SS_LAYMAN >= MAX_SS_LAYMAN will get the maximum title.
 */
#define MAX_SS_LAYMAN  150 


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
