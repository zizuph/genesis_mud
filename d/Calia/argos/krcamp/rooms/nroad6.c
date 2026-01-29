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
      "You are standing on a dusty path through a cluster of round tents, "+
      "where the path splits from the west to the east and north. One of "+
      "the tents is open to the south, is flap folded back allowing "+
      "entrance. There is a nervous tension in the air, as if this "+
      "camp is ready to explode like a fallen beehive.\n");
 
    add_item(({"trees","tree","pines","pine","forest"}),
       "They are tall dark pines with black bark and needles grow "+
       "sporadically around the encampment.\n");
    add_item("path",
        "Just a dusty path which winds through the tents in this "+
        "part of the encampment. It leads east and west, and splits off "+
        "to the north.\n");
    add_item(({"cluster","tent","tents","entrance","entrance","flap",
       "flaps","camp","encampment"}),
       "Large round tents sit all around you, with their tall "+
       "cone-shaped tops rising to a point. They are made of canvas "+
       "striped vertically with various colours. The flap of the green-"+
       "striped tent to the south is open.\n");
 
    /* exits */
    add_exit("nroad8", "north","@@check_blocked");
    add_exit("b6tent4","south","@@check_blocked");
    add_exit("nroad7","east","@@check_blocked");
    add_exit("nroad5","west",0);
 
    reset_room();
}
