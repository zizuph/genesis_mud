/*
 * This file contains the number of signatures (eg colours) of
 * the buttons to the secret door
 *
 *
 *  Modified: 13 June 2003, by Bleys
 *      - Added FAIL_LOG define, which tells where to log
 *          failed attempts to open the Zodiac door.
 *
 */

#include <math.h>

#define FAIL_LOG "/d/Terel/log/zodiac_failures"

/*
 * the quest consists of NBR_SIGS possible buttons; the right
 * sequence has the length of SEQ_LEN. For the buttons we need
 * the following fields:
 * - SIGS: name of buttons as they appear at the questroom
 * - SIGEQ: equivalent names as they appear in the hintrooms
 * - SIGPR: right article in the hint rooms
 * HINT contains the adjectives for SIGEQ in an easy to guess
 * order (here rainbow colours) for teh hint-rooms. A hint
 * in the hint-room consists of SIGPR, HINT and SIGEQ
 * concatenated together.
 */
#define NBR_SIGS 12
#define SIGS ({	"aries", "taurus", "gemini", "cancer", "leo",\
		"virgo", "libra", "scorpio", "sagittarius",\
		"capricorn", "aquarius", "pisces" })
#define SIGEQ ({"ram", "bull", "twins", "crab", "lion",\
		"maid", "balance", "scorpion", "archer",\
		"ibex", "water bearer", "fishes" })
#define SIGPR ({"a ","a ","","a ","a ","a ","a ","a ","an ","an ","a ","" })

/* The length of the sequence to be guessed */
#define SEQ_LEN 6
/* We need a hint (right order) for each element to be guessed */
#define	HINT ({"red ","orange ","yellow ","green ","blue ","violet "})
#define ZNAMES ({ "red death", "cave fire", "portia", "balance", "mirror", "maze" }) 
/* Six random seeds for each of the parts. */
#define ZODIAC_SEED 155625

/* for each button to press, we need a room with a hint */
#define HINT_ROOMS ({DUST_DIR + "hint_room0",\
                  "/d/Terel/mountains/goblincave/cave11",\
		     "/d/Terel/common/town/mansion/porcia/riddle_room",\
		     "/d/Terel/common/town/mansion/obj/balance",\
		     "/d/Terel/common/town/mansion/obj/mirror",\
		     "/d/Terel/common/town/mansion/colors/maze_end"})
/* And we need the room that contains the door */
#define DOOR_ROOM DUST_DIR + "door_room"



/*
 * Function name: name_to_sign
 * Description  : Algorithm to figure out the zodiac hint for each combination
 *                of name and valid zodiac part index.
 * Arguments    : string name - the name of a player.
 *                int index - the Zodiac part (0-5)
 * Returns      : int - the corresponding zodiac sign (0-11)
 */
int
name_to_sign(string name, int index)
{
    int *signs = ({ }), *sort = ({ }), i;   
  
    /* Access failure. */
    if (index >= SEQ_LEN) return 0;

    
    /* Extremely ugly and inneficient but builds the same array always 
     * for the same player name */
    i = -1;
    while (++i < NBR_SIGS)
    {
	signs += ({ i });
    }

    while (sizeof(signs))
    {
	i = signs[NAME_TO_RANDOM(name, ZODIAC_SEED, sizeof(signs))];
	signs -= ({ i });
	sort += ({ i });
    }
 
    return sort[index];
}

/*
 * Function name: calc_hint
 * Description  : Calculates the hint for any of the Zodiac parts for the
 *                current player. The index represents the part of the Zodiac
 *                quest to test. This function operates on this_player().
 * Arguments    : int index - the Zodiac part (0-5)
 * Returns      : int - the zodiac sign (0-11) corresponding to the index.
 */
int
calc_hint(int index)
{
    return name_to_sign(TP->query_real_name(), index);
}

/*
 * Function name: wiz_hint
 * Description  : Support function find out the hints for a certain player.
 * Arguments    : string name - the name of the player to test.
 */
void
wiz_hint(string name)
{
    int index, sign;

    for (index = 0; index < SEQ_LEN; index++)
    {
        sign = name_to_sign(name, index);
        write(sprintf("%-7s (%-10s : %-7s (%s\n", HINT[index],
            ZNAMES[index] + ")",
            SIGEQ[sign],
            SIGS[sign] + ")"));
    }
}
