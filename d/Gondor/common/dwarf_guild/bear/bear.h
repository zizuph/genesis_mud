/*
 * /d/Gondor/common/dwarf_guild/bear/bear.h
 * 
 * Mercade @ Genesis - April 24 2000
 *
 * Header file for the bear distribution system.
 */

#ifndef BEAR_DEFINITIONS
#define BEAR_DEFINITIONS

#define BEAR_DIR     "/d/Gondor/common/dwarf_guild/bear/"

#define BEAR_OBJECT  (BEAR_DIR + "bear")
#define BEAR_CABINET (BEAR_DIR + "cabinet")
#define BEAR_HOME    (BEAR_DIR + "home")

#define BEAR_SAVE    (BEAR_DIR + "bears")

#define SHOWCASE_ID  "_bear_showcase"

#define DEFAULT_BEAR_NAME "Bear"

#define BEAR_SIZE_MALE_NAMES 6
#define BEAR_MALE_NAMES ({ "Bamboo", "Bob", "Edward", "Polar", "Pooh", \
    "Teddy" })

#define BEAR_SIZE_FEMALE_NAMES 5
#define BEAR_FEMALE_NAMES ({ "Belinda", "Bella", "Cheeky", "Joyce", "Teddy" })

#define BEAR_SIZE_ALL_NAMES (BEAR_SIZE_MALE_NAMES + BEAR_SIZE_FEMALE_NAMES)

/* Indices in the bear configuration array. */
#define BEAR_NAME     0
#define BEAR_GENDER   1
#define BEAR_OWNER    2
#define BEAR_LOCATION 3

#define GOOD_EMOTES  ({ "kiss", "admire", "approve", "compliment", \
                     "caress","pat", "pet", "lick", "nibble",      \
                     "ruffle", "thank", "applaud", "comfort",      \
                     "smile", "shake", "congratulate", "wink",     \
                     "squeeze", "hold", "hug", "bow", "grovel",    \
                     "thumb"})
#define NEUTRAL_EMOTES ({ "nuzzle", "cuddle", "melt", "flirt",     \
                     "nudge", "poke", "glare", "pounce" })
#define BAD_EMOTES ({ "finger", "tackle", "knee", "slap", "kick", "spank", \
                     "puke", "spit","curse", "scowl", "scold", "snarl" })

/* No definitions beyond this line. */
#endif BEAR_DEFINITIONS
