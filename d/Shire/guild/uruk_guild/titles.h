/*
 * /d/Shire/guild/uruk_guild/titles.h
 * This file contains the titles
 
 */

/* NUM_TITLES should define the number of titles possible
 */
#define NUM_TITLES    12

/* Everyone with SS_RACE >= MAX_SS_RACE will get the maximum title.
 */
#define MAX_SS_RACE  120 


/* This define contains the strlen() of the longest title in the TITLES
 * define.
 */
#define LONGEST_TITLE 21

/* The possible titles for the members of the Mordor uruk guild.
 *Must match NUM_TITLES. 
 */
#define M_TITLES          \
    ({ "Mindless Drone",       \
       "Mewling Drone",      \
       "Weak Slave",      \
       "Adaquate Slave", \
       "Docile Thrall",        \
       "Willing Thrall",        \
       "Subservient Minion",       \
       "Obedient Minion",        \
       "Brutal Slavedriver",    \
       "Sadistic Slavedriver",      \
       "Cruel Taskmaster",    \
       "Merciless Taskmaster"       \
       })



/* The possible titles for the members of the Isengard uruk guild.
 *Must match NUM_TITLES. 
 */
#define I_TITLES          \
    ({ "Snivelling Maggot",	\
	"Putrid Maggot",	\
	"Inept Grunt",	\
	"Reliable Grunt",	\
	"Petty Thug",	\
	"Brutish Thug",	\
	"Competent Soldier",	\
	"Frontline Soldier",	\
	"Blooded Warrior",	\
	"Skilled Warrior",	\
	"Raging Berserker",	\
	"Indomitable Berserker"       \
       })