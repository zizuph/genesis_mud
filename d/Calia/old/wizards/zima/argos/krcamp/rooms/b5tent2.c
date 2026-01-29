/* inside a tent, sentries
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
#define  KRETAN_LIST ({"sentry/sentry5","sentry/sentry5","sentry/sentry5"})
#include "sentry.h"
 
void reset_room() { make_kretans(); }
 
/* room definition */
void create_room() {
   set_short("Inside a tent");
   set_long(
      "You are standing inside a large round tent, a tall pole in the "+
      "center holding up its pointed top. Small stools and bedrolls are "+
      "scattered around the floor of the tent, the living spartan living "+
      "quarters for some of the Kretan sentries.\n");
 
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
   add_item(({"bed","beds","bed roll","bed rolls","roll","rolls"}),
       "The bed rolls just seem to be a simple collection of blankets "+
       "rolled up, some with worn out pillows and cushions. They don't "+
       "look very comfortable.\n");
   add_item("floor",
       "It is just dirt, the tent covering a cleared area of the forest.\n");
   add_item(({"stool","stools"}),
       "Several short three-legged stools are scattered about, mostly "+
       "in small groups, where the soldiers have gathered for "+
       "comraderie.\n");
 
   /* exits */
   add_exit("nroad3","north",0);
   reset_room();
}
