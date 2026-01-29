/*
 * /d/Shire/guild/heralds/titles.h
 *
 * This file contains the defines with the titles possible for members 
 * of the Heralds of the Valar.
 */

/* NUM_TITLES should define the number of titles possible.
 */
#define NUM_TITLES    20

/* Everyone with SS_LAYMAN >= MAX_SS_LAYMAN will get the maximum title.
 */
#define MAX_SS_LAYMAN  150 

/* This define contains the strlen() of the longest title in the TITLES
 * define.
 */
#define LONGEST_TITLE 17

/* The possible titles for the members of the Heralds guild. The number
 * of titles must equal the number set in NUM_TITLES.
 */
#define TITLES             \
    ({ "Altar Servant",    \
       "Acolyte",          \
       "Seeker",           \
       "Inquirer",         \
       "Lover",            \
       "Student",          \
       "Auspicer",         \
       "Diviner",          \
       "Devout Follower",  \
       "Messenger",        \
       "Scholar",          \
       "Faithful Follower",\
       "Agent",            \
       "Voice",            \
       "Cantor",           \
       "Speaker",          \
       "Herald",           \
       "Jewel",            \
       "Farseer",          \
       "High Speaker"      \
       })
