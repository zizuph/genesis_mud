/* Northern road through camp
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
      "You are walking down a small dusty path amongst a group of round, "+
      "pointed-topped tents. There are entrances to two of the tents, "+
      "one to the north and another to the south. The path continues "+
      "east between the canvas dwellings, and west to the main road.\n");
 
    add_item(({"trees","tree","pines","pine","forest"}),
       "They are tall dark pines with black bark and needles grow "+
       "sporadically around the encampment.\n");
    add_item("road",
       "The main road of the camp is to the west.\n");
    add_item("path",
        "Just a dusty path which winds through the tents in this "+
        "part of the encampment. It comes from the east and leads "+
        "onto the main road to the west.\n");
    add_item(({"cluster","tent","tents","entrance","entrance","flap",
       "flaps","camp","encampment"}),
       "Large round tents sit all around you, with their tall "+
       "cone-shaped tops rising to a point. They are made of canvas "+
       "striped vertically with various colours. There are entrances "+
       "to two of the tents open to the north and south.\n");
 
    /* exits */
    add_exit("b6tent1","north","@@check_blocked");
    add_exit("b6tent2","south","@@check_blocked");
    add_exit("nroad5", "east", "@@check_blocked");
    add_exit("mroad2", "west", 0);
 
    reset_room();
}
