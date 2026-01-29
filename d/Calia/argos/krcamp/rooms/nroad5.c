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
#define  KRETAN_LIST ({"soldier/soldier3","soldier/soldier3", \
                       "soldier/soldier3"})
#include "sentry.h"
#include "kr_reset.h"

/* room definition */
void create_room() {
   set_short("In a military camp");
   set_long(
      "The clatter of men's voices and weapons chime from the tents all "+
      "around you, the sound of an army preparing to march. A yellow-striped "+
      "tent sits to the south, its flap opened to let the air in. A small "+
      "red banner hangs from a pole just outside its entrance. The dusty "+
      "path winds to the east and west between the crowed tents.\n");
 
    add_item("pole",
       "It stuck in the ground next to the entrance of the tent to the "+
       "north, bearing a red banner.\n");
    add_item(({"banner","flag"}),
       "It is a red banner embroidered with a seven-headed hydra, its "+
       "sixth head raised high with a dark halo.\n");
    add_item(({"trees","tree","pines","pine","forest"}),
       "They are tall dark pines with black bark and needles grow "+
       "sporadically around the encampment.\n");
    add_item("path",
        "Just a dusty path which winds through the tents in this "+
        "part of the encampment. It leads east and west.\n");
    add_item(({"cluster","tent","tents","entrance","entrance","flap",
       "flaps","camp","encampment"}),
       "Large round tents sit all around you, with their tall "+
       "cone-shaped tops rising to a point. They are made of canvas "+
       "striped vertically with various colours. The flap of the yellow-"+
       "striped tent to the south is open.\n");
 
    /* exits */
    add_exit("b6tent3","south","@@check_blocked");
    add_exit("nroad6", "east","@@check_blocked");
    add_exit("nroad4", "west", 0);
 
    reset_room();
}
