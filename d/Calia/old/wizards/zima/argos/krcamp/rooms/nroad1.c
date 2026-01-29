/* North road through camp
**
** History:
** Date        Coder       Action
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
      "aroma (or is that the stench) of simmering stew. You see entrances "+
      "to two of the tents, one to the north and the other to the west. A "+
      "small red banner hangs in front of the tent to the north from a "+
      "short pole. The "+
      "dusty path leads out of the clearing to the east and south.\n");
 
    add_item(({"camp","encampment"}),
       "It is a military camp, its dusty foot-trodden paths "+
       "lined with round pointed-top tents on all about.\n");
    add_item("path","It winds through the camp to the east and south.\n");
    add_item(({"cluster","tent","tents","entrance","entrances"}),
       "They are sitting all around this clearing, their cononical tops "+
       "pointing up like large canvas helmets. There is an entrance to "+
       "the one to the north and another to the west.\n");
    add_item("pole",
       "It stuck in the ground next to the entrance of the tent to the "+
       "north, bearing a black banner.\n");
    add_item(({"banner","flag"}),
       "It is a red banner embroidered with a seven-headed hydra, its "+
       "fifth head raised high with a dark halo.\n");
 
    stewpot=clone_object(OBJ_DIR+"stewpot");
    stewpot->move(this_object());
 
    /* exits */
    add_exit(ROOM_DIR+"b5tent3", "north","@@check_blocked");
    add_exit(ROOM_DIR+"wroad1",  "south",0);
    add_exit(ROOM_DIR+"nroad2",  "east", 0);
    add_exit(ROOM_DIR+"b5tent5","west","@@check_blocked");
 
    reset_room();
}
