/* inside soldiers tent
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 8/15/96     Zima        Created
** 1/25/97     Zima        Added object reduction
**
*/
/* inherits/includes */
inherit "/std/room";
#include "reduce.h"
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  ORIGIN_MSG   " steps into the tent."
#define  KRETAN_LIST ({"warrior/warrior4","warrior/warrior4", \
                       "tcomder/tcomder5"})
#include "sentry.h"
#include "kr_reset.h"
 
/* room definition */
void create_room() {
   set_short("Inside a tent");
   set_long(
      "A ring of beds encircles the perimeter of this tent, used for "+
      "the sleeping quarters of some of the more fortunate titans loyal "+
      "to Kretos. There are a couple of tables and some old chairs "+
      "scattered around the pole which holds up the top of the tent. "+
      "A flap is open to the east leading outside to the east.\n");
 
   add_item("chairs",
      "They are old wooden chairs, some are broken, most look as if they "+
      "have been repaired. They are situated around a simple table, "+
      "and gathered in small groups for conversation.\n");
   add_item(({"table","tables"}),
      "They are simple wooden tables, used by the soldiers who live here "+
      "for every day necessities, like arm-wrestling and gambling.\n");
   add_item("tent",
      "It is a large round tent made of canvas, its top supported by "+
      "a large pole in the center. You wouldn't call it home, but it "+
      "seems to provide decent shelter for the soldiers who live here.\n");
   add_item("pole",
      "It is a tall wooden pole, set deep in the ground, holding up the "+
      "top of the tent. You imagine total chaos would ensue if that "+
      "pole were broken or pushed over.\n");
   add_cmd_item("pole","push","You push on the pole but it won't budge.\n");
   add_cmd_item("pole","break","You try to break the pole but to no avail.\n");
   add_item(({"ceiling","top"}),
       "It is cone shaped, rising from the circular sides of the tent up "+
       "to a central point supported by the pole.\n");
   add_item(({"bed","beds"}),
       "They are simple wooden beds with flat matresses, probably filled "+
       "with straw, but neatly made. They circle the perimeter of the round "+
       "tent.\n");
   add_item("floor",
       "It is just dirt, the tent covering a cleared area of the forest.\n");
 
   /* exits */
   add_exit("nroad8", "east", 0);
   reset_room();
}
