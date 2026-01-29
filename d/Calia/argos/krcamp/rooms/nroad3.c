/* Road through Batallion Five Camp
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 8/1/96      Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include "reduce.h"
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  ORIGIN_MSG   " takes his post."
#define  KRETAN_LIST ({"soldier/soldier3","soldier/soldier3"})
#include "sentry.h"
#include "kr_reset.h"
 
/* room definition */
void create_room() {
   set_short("In a military camp");
   set_long(
      "You are standing amongst a cluster of tents in a military camp "+
      "hidden deep within the dark forest. Two of the tents stand open "+
      "from this spot, one to the north and another to the south. To "+
      "the east you see the main road of the camp, while the path "+
      "through the tents continues west.\n");
 
    add_item(({"trees","tree","pines","pine","forest"}),
       "They are tall dark pines with black bark and needles grow "+
       "sporadically around the encampment.\n");
    add_item("road",
       "The main road of the camp is to the east.\n");
    add_item("path",
        "Just a dusty path which winds through the tents in this "+
        "part of the encampment. It comes from the west and leads "+
        "onto the main road to the east.\n");
    add_item(({"cluster","tent","tents","entrance","entrance","flap",
       "flaps","camp","encampment"}),
       "Large round tents sit all around you, with their tall "+
       "cone-shaped tops rising to a point. They are made of canvas "+
       "striped vertically with various colours. There are entrances "+
       "to two of the tents open to the north and south.\n");
 
    /* exits */
    add_exit("b5tent1","north","@@check_blocked");
    add_exit("b5tent2","south","@@check_blocked");
    add_exit("mroad2", "east", 0);
    add_exit("nroad2", "west", "@@check_blocked");
 
    reset_room();
}
