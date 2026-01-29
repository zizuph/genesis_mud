/* Inside soldiers' tent
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 8/15/96     Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  ORIGIN_MSG   " steps into the tent."
#define  KRETAN_LIST ({"soldier/soldier4","soldier/soldier4", \
                                          "soldier/soldier4"})
#include "sentry.h"
 
void reset_room() { make_kretans(); }
 
/* room definition */
void create_room() {
   set_short("Inside a tent");
   set_long(
      "Rows of x-framed cots run across the back portion of this tent, "+
      "the quarters of some of the Kretan soldiers. Stools are scattered "+
      "about the remainder, some around a small table which sits next "+
      "to the center pole.\n");
 
   add_item("stools",
      "They are old wooden stools, some are broken, most look as if they "+
      "have been repaired. They are situated around a simple table, "+
      "and gathered in small groups for conversation.\n");
   add_item(({"table","tables"}),
      "It is a simple wooden table, used by the soldiers who live here "+
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
   add_item(({"cot","cots"}),
       "They are make-shift beds, made of three sets of crossed sticks "+
       "with a piece of canvas stretched between them. They don't look "+
       "very soft, but they are better than a blanket on the floor.\n");
   add_item("floor",
       "It is just dirt, the tent covering a cleared area of the forest.\n");
 
   /* exits */
   add_exit("wroad1", "west", 0);
   reset_room();
}
