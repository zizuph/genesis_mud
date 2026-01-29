/*
 * This file contains the number of signatures (eg colours) of
 * the buttons to the secret door
 */

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
/* for each button to press, we need a room with a hint */
#define HINT_ROOMS ({DUSTDIR + "hint_room0",\
		     "/d/Terel/common/forest/caves/c11",\
		     "/d/Terel/common/town/mansion/porcia/riddle_room",\
		     "/d/Terel/common/town/mansion/obj/balance",\
		     "/d/Terel/common/twon/mansion/obj/mirror",\
		     "/d/Terel/common/town/mansion/colors/maze_end"})
/* And we need the room that contains the door */
#define DOOR_ROOM DUSTDIR + "door_room"

/*
 * calc_hint: based on the players name and the index, a fix number
 * from 0..11 is returned
 */
int
calc_hint(int index) {
    string *nam;
    int seed,i;

    nam = explode(this_player()->query_name(),"");
    seed = 3;
    for (i=0; i<sizeof(nam); i++)
	seed += i*97*(nam[i][0]-32);
    for (i=0; i<(17+index); i++) seed = random(32760,seed);
    return(random(12,seed));
}

/* next function is just for debug purposes */

int
wiz_hint(string name) {
    string *nam;
    int seed,i,index;

  nam = explode(name,"");
  for (index=0; index<6; index++) {
    seed = 3;
    for (i=0; i<sizeof(nam); i++)
	seed += i*97*(nam[i][0]-32);
    for (i=0; i<(17+index); i++) seed = random(32760,seed);
    write(HINT[index] + "\t: " + SIGEQ[random(12,seed)] + 
	"(" + SIGS[random(12,seed)] + ")\n");
  }
}
