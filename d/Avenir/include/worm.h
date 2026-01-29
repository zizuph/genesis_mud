// Constants used in defferent parts of The Worm of Avenir (tm) code.
// Made by Boriska@Genesis, Sept 1994

#define LEFT_OBJ "/d/Avenir/common/dark/obj/worm_leftover"
// leftover code, cloned by all body parts

#define ARMOR_OBJ "/d/Avenir/common/dark/obj/worm_armor"
#define TOOTH_KNIFE "/d/Avenir/common/dark/obj/tooth_knife"


#define HEAD 0
#define BODY 1
#define TAIL 2
#define TOOTH 3

#define HEAD_LEFTOVER "skin"
#define BODY_LEFTOVER "hide"
#define TAIL_LEFTOVER "scale"
// make sure above 3 are different
#define TOOTH_LEFTOVER "tooth"

#define WORM_LEFTOVER_ID "avenir_worm_leftover"

#define WORM_LEFTOVERS ({ HEAD_LEFTOVER, BODY_LEFTOVER, \
			    TAIL_LEFTOVER, TOOTH_LEFTOVER })

#define WORM_LAIR ("/d/Avenir/common/dark/lair/lair")

#define LOG_FILE ("/d/Avenir/log/lair")
#define WRITE_LOG(x) (write_file(LOG_FILE, ctime(time())+" "+(x)))






