/* Main Road through the Kretan Camp - just inside the gate
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
   set_short("On a road in a military camp");
   set_long(
      "You are standing just south of the gate of a military camp, composed "+
      "of round pointed-top tents hidden in the depths of the dark forest. "+
      "A banner hangs from the top of the gate, dancing gently in the breeze. "+
      "A small path crosses the road here, running "+
      "east and west, while the road leads further south.\n");
 
    add_item(({"forest","trees","branches"}),
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n");
    add_item("camp",
       "It seems to be a military camp, its dusty foot-trodden roads "+
       "lined with round pointed-top tents on all sides.\n");
    add_item(({"tent","tents"}),
       "Round tents made of canvas with large stripes of various colors "+
       "occupy spots all along the road. Each seems to have a central "+
       "pole which supports its roof, giving the temporary shelters "+
       "pointy funnel-shaped tops. You don't see an entrance to any of "+
       "the tents here.\n");
    add_item("road",
       "It is a dusty road, trodden flat by the feet of soldiers, which "+
       "leads north beneath the gate and south into the encampment.\n");
    add_item(({"gate","arch","structure"}),
       "It is a large rectangular-shaped arch, a gateway which guards "+
       "the entrance of the camp. It is made from some of the thick pines "+
       "which populate the forest. A banner hangs from the crossbar at "+
       "the top of the gate.\n");
    add_cmd_item("gate",({"close","open","lock"}),
       "The gate seems to have no doors on it. It just marks an entrance.\n");
    add_item(({"crossbar","banner"}),
       "A banner hangs from the crossbar of the gate high above the path. "+
       "It is made of black silk and embroidered with a seven-headed "+
       "hydra of crimson thread. It flutters gently with the breeze.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"mroad1","north", 0);
    add_exit(ROOM_DIR+"mroad3","south","@@blocked");
    add_exit(ROOM_DIR+"nroad4","east","@@check_blocked");
    add_exit(ROOM_DIR+"nroad3","west","@@check_blocked");
    reset_room();
}
 
int blocked() {
   write("A mysterious force prevents you from going south.\n");
   return 1;
}
