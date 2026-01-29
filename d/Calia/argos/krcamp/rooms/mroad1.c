/* Main Road through the Kretan Camp - outside the gate
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 8/1/96      Zima        Created
**  1/25/97   Zima     Added object reduction
**
*/
/* inherits/includes */
inherit "/std/room";
#include "reduce.h"
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  ORIGIN_MSG   " steps through the gate"
#define  KRETAN_LIST ({"soldier/soldier3","soldier/soldier3", \
                       "soldier/soldier3"})
#include "sentry.h"
#include "kr_reset.h"
 
/* room definition */
void create_room() {
   set_short("Before a gate in the forest");
   set_long(
      "A large gate, more of an arch, stands above the pathway as it leads "+
      "further south. The massive wooden structure is an oddity, a man-made "+
      "interloper in the natural beauty of the surrounding forest. The path "+
      "trails off to the north and widens beneath the gate into a road to the "+
      "south.\n");
 
    add_item(({"forest","trees","branches"}),
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n");
    add_item(({"path","road"}),
       "The path leads to the north and widens into a road beneath the "+
       "gate.\n");
    add_item(({"gate","arch","structure"}),
       "It is a large rectangular-shaped arch, a gateway which guards "+
       "the road to the south. It is made from some of the thick pines "+
       "which populate the forest. A banner hangs from the crossbar at "+
       "the top of the gate.\n");
    add_cmd_item("gate",({"close","open","lock"}),
       "The gate seems to have no doors on it. It just marks an entrance.\n");
    add_item(({"crossbar","banner"}),
       "A banner hangs from the crossbar of the gate high above the path. "+
       "It is made of black silk and embroidered with a seven-headed "+
       "hydra of crimson thread. It flutters gently with the breeze.\n");
 
 
    /* exits */
    add_exit("npath3","north",0);
    add_exit("mroad2","south","@@check_blocked");
    reset_room();
}
