/*
 * Definitions used in the gwaedhil.
 */

/*
 * Racial guilds
 */
#define DROW       "Drow race guild"
#define DUNEDAIN   "Dunedain"
#define HOBBIT     "Adventuresome Hobbits Guild"
#define NOLDOR     "Noldor High Elves"
#define ROCKFRIEND "Rockfriend guild"
/*
 * Layman guilds
 */
#define HERALD     "Heralds of the Valar"
/*
 * Occupational guilds
 */
#define MM         "Morgul Mages"
#define RANGER     "Gondorian Rangers Guild"

/*
 * Damage fear, explotions etc.
 */
#define EXPLODING_SPEAR      800
#define ERECH_PHURT_MED      10
#define ERECH_PHURT_GOOD     25
#define ERECH_PHURT_XDAM     20
#define ERECH_TROUBLED       2
#define ERECH_SCARED         10

/*
 * Dreaming, visions etc.
 */
#define DREAM_MIN_DELAY      120
#define DREAM_MAX_DELAY      900
#define DREAM_FLOAT_REPEAT   0.0   /* DO NOT CHANGE THIS */
#define DREAMER_RANDOM_TEST  10

/*
 * The Dreams:
 */
#define W_DREAMS    ({ \
    "An apparition of Isildur apears to you.\nHe tells you: Remember these " +\
    "words, for you are bound to them.\nThe apparition then disapears.\n", \
    "A vision of a ghostly shade with a black banner apears before you.\n", \
    "A vision of a people ill with plague traveling up a mountain path " +\
    "apears before you.\n", \
    "Suddenly you see before you the city of Minas Tirith. You find " +\
    "yourself on a ledge above the sity, and infront of you there is " +\
    "a small white tree.\n", \
    "Morthec rises before you ands says: No, I will not do as you command, " +\
    "even if that means you will curse me and my people. I will not do " +\
    "it.\n", \
                    })
#define I_DREAMS    ({ \
    "A vision of Isildur cutting of a finger from Sauron's hand apears " + \
    "before you.\n", \
    "A vision of a large army on march apears before you.\n", \
    "A vision of a horde of shadows apears before you.\n", \
    "A vision of a distant battle apears before you.\n", \
                    })
#define A_DREAMS    ({ \
    "A battle is seen in the distance.\n", \
    "In the distance you can see a fleet anchor up in a large bay.\n", \
    "You feel sorrow and suddenly you miss Numenor.\n" \
                    })


