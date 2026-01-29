/* North road through camp
**
** Histo** Date        Coder       Action
**----------   ----------- ----------------------------------
** 8/1/96      Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  ORIGIN_MSG   " takes his post."
#define KRETAN_LIST ({"boycook","sentry/sentry4"})
#include "sentry.h"
object   stewpot;
 
void reset_room() { make_kretans(); stewpot->reset_stew(); }
 
/* room definition */
void create_room() {
   set_short("In a military camp");
   set_long(
      "Several tents surround this small clearing, from which you hear the "+
      "voices of soldiers and the clanking of weapons, mingled with the "+
      "aroma, or stench, of simmering stew. You see entrances "+
      "to three of the tents, to the north, west and east, while "+
      "a dusty path leads out of the clearing to the south.\n");
 
    add_item(({"camp","encampment"}),
       "It is a military camp, its dusty foot-trodden paths "+
       "lined with round pointed-top tents on all about.\n");
    add_item("path","It leads south out of the clearing.\n");
    add_item(({"cluster","tent","tents","entrance","entrances"}),
       "They are sitting all around this clearing, their cononical tops "+
       "pointing up like large canvas helmets. There are entrances to "+
       "three to the north, east and west.\n");
    add_item("pole",
       "It stuck in the ground next to the entrance of the tent to the "+
       "north, bearing a black banner.\n");
    add_item(({"banner","flag"}),
       "It is a red banner embroidered with a seven-headed hydra, its "+
       "sixth head raised high with a dark halo.\n");
 
    stewpot=clone_object(OBJ_DIR+"stewpot");
    stewpot->move(this_object());
 
    /* exits */
    add_exit(ROOM_DIR+"b6tent6", "north","@@check_blocked");
    add_exit(ROOM_DIR+"nroad6",  "south",0);
    add_exit(ROOM_DIR+"b6tent7", "east", "@@check_blocked");
    add_exit(ROOM_DIR+"b6tent5", "west", "@@check_blocked");
 
    reset_room();
}
