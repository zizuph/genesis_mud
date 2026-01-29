/*
 * /d/Gondor/rohan/isengard/defs.h
 *
 * Definitions for Isengard.
 *
 */
#ifndef ISENGARD_DEFINITIONS
#define ISENGARD_DEFINITIONS
/*
 * Nothing before this line!
 */
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/rohan_clock.h"

/*
 * Definitions specific to Isengard:
 */
#define ISEN_STD           (ISEN_DIR + "std/")
/*
 * Since we use 'inherit ISEN_ROOM;', do not change this definition,
 * unless you _KNOW_ what you are doing and you _KNOW_ that the gd bug
 * has been fixed.  If you do not know what I am talking about, don't
 * even think about changing it!
 *                                            Olorin
 */
#define ISEN_ROOM          "/d/Gondor/rohan/isengard/std/room"


/*
 * Players wearing Isengard armour are disguised.
 * We mark Isengard armour using this prop:
 */
#define ISEN_I_ARMOUR	"_Isen_i_armour"


/*
 * This prop lets us designate players as enemies of Isengard.
 */
#define ISEN_I_ENEMY       "_isen_i_enemy"

/*
 * At what alignment do we want our npcs to consider players to be
 * enemies?
 */
#define ENEMY_ALIGNMENT    200

/* logging macros. comment out the first DEBUG_LOG (or TMP_LOG)
 * and uncomment the second to turn off debugging (or tmp logging)
 */
#define ERR_LOG(x)      log_file("isen", \
        "ERR "+ctime(time())+" "+file_name(this_object())+"\nERR\t"+x);
#define DEBUG_LOG(x)    log_file("isen", \
        "DBG "+ctime(time())+" "+file_name(this_object())+"\nDBG\t"+x);

/*
 * Nothing beyond this line!
 */
#endif
