/* North road through camp
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 8/1/96      Zima        Created
** 1/25/97     Zima        Object reduction added
*/
/* inherits/includes */
inherit "/std/room";
#include "reduce.h";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  ORIGIN_MSG   " takes his post."
#define KRETAN_LIST ({"boycook","soldier/soldier3"})
#include "sentry.h"

object   stewpot;

/*
 * Function:    alarmed_reset_room
 * Description: This will execute all the actions that are needed
 *              inside a reset room. It will be called from within
 *              an alarm, so no assumptions can be made about the
 *              context.
 */
public void
alarmed_reset_room()
{
    set_alarm(0.0, 0.0, make_kretans);
    stewpot->reset_stew();
    set_alarm(0.0, 0.0, reduce_objects);
}

/*
 * Function:    reset_room
 * Description: This reset_room will call the meat of its functionality
 *              in an alarm. The reason is that without an alarm, it can
 *              cause runtime or eval-cost errors, leading to the room
 *              not properly being created.
 */
public nomask void
reset_room()
{
    set_alarm(0.0, 0.0, alarmed_reset_room);
}

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
    /* exits */
    add_exit(ROOM_DIR+"b5tent3", "north","@@check_blocked");
    add_exit(ROOM_DIR+"wroad1",  "south","@@check_blocked");
    add_exit(ROOM_DIR+"nroad2",  "east", 0);
    add_exit(ROOM_DIR+"b5tent5","west","@@check_blocked");
 
    stewpot=clone_object(OBJ_DIR+"stewpot");
    stewpot->move(this_object());
    stewpot->add_prop(ARGOS_NO_CLEANME,1);

    reset_room();
}
