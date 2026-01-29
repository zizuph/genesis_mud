/* Inside Statarch's tent
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 8/15/96     Zima        Created
**  1/25/97   Zima       Added object reduction
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
      "You are standing inside a large round tent, though it is obviously "+
      "not the dwelling of common soldiers. A large table and high-backed "+
      "chair sits in the center, while a simple bed sits in the back. A "+
      "red silk banner hangs above the flap which leads outside to the "+
      "north.\n");
 
   add_item("table",
      "It is a large pine table with a lamp, a quill and ink set, and "+
      "a map on it.\n");
   add_item("chair",
      "It is a high-backed chair sitting behind the table. Not something "+
      "you would find in a palace, but definitely a valuable commodity "+
      "in a temporary encampment.\n");
   add_item("lamp",
      "It is one of the oblong, bowl-shaped lamps common in this area, "+
      "with a wick on one end.\n");
   add_item(({"quill","ink","set"}),
      "There is a quill with a small bottle of in setting on the table.\n");
   add_item("map",
#include "map6.txt"
   add_item("bed",
      "It is a simple pine bed with a thin mattress, neatly made with "+
      "a pillow and blanket.\n");
   add_item("banner",
      "It is a red silk banner with a seven-headed hydra embroidered on "+
      "it with great detail. Five swords are embroidered in one corner.\n");
   add_item("tent",
      "It is a large round tent made of canvas, its top supported by "+
      "a large pole in the center. It looks a little more comfortable "+
      "than most in the camp with its furnishings and general neatness.\n");
   add_item("pole",
      "It is a tall wooden pole, set deep in the ground, holding up the "+
      "top of the tent. You imagine total chaos would ensue if that "+
      "pole were broken or pushed over.\n");
   add_cmd_item("pole","push","You push on the pole but it won't budge.\n");
   add_cmd_item("pole","break","You try to break the pole but to no avail.\n");
   add_item(({"ceiling","top"}),
       "It is cone shaped, rising from the circular sides of the tent up "+
       "to a central point supported by the pole.\n");
   add_item("floor",
       "It is just dirt, the tent covering a cleared area of the forest.\n");
 
   /* exits */
   add_exit("nroad5","north",0);
   reset_room();
}
