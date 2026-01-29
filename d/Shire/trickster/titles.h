/*
 * /d/Shire/trickster/titles.h
 *
 * This file contains the defines with the titles and beard descriptions
 * possible for members of the Trickster guild.
 * 
 * /Mercade, 28 October 1994
 * From Mercade's Dwarf Titles
 * Dunstable March 23, 1995
 * Revision history:
 */

/* NUM_TITLES should define the number of titles possible, as they are
 * defined in BEARD_DESCRIPTIONS and TITLES. Those defines should contain
 * exactly that much descriptions and titles.
 */
#define NUM_TITLES    23

/* Everyone with SS_LAYMAN >= MAX_SS_LAYMAN will get the maximum title.
 */
#define MAX_SS_LAYMAN  136 


/* This define contains the strlen() of the longest title in the TITLES
 * define.
 */
#define LONGEST_TITLE 13

/* The possible titles for the members of the Trickster guild. The number
 * of titles must equal the number of descriptions possible for beards and
 * it must also equal the number set in NUM_TITLES.
 */
#define TITLES          \
    ({ "Naughty",       \
       "Sly",      \
       "Wily",      \
       "Furtive", \
       "Tricky",        \
       "Cagey",        \
       "Shrewd",     \
       "Unruly",       \
       "Shifty",        \
       "Recalcitrant",    \
       "Skulking",      \
       "Insubordinate",    \
       "Underhanded",      \
       "Cunning",       \
       "Mischievous",      \
       "Lawless",       \
       "Spiteful",  \
       "Deceitful",     \
       "Villainous",     \
       "Insidious",      \
       "Treacherous",    \
       "Malicious",     \
       "Infamous",        \
       "Wizardly"         \
       })
