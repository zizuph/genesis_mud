/* Forest along marble road - kretan infested
**
** History:
** Date      Coder          Action
** --------  -------------  ---------------------------------
** 1993      Zima           Created
** 1/25/97   Zima           Re-coded
**
*/
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
inherit  "/std/room";
inherit  KRETAN_SENTRY_MOD;
inherit  REDUCE_OBJ_MOD;
 
void reset_room() {
   reduce_objects();
   make_kretans();
}
 
/* room definition */
void create_room() {
   set_short("A dense forest");
   set_long(
       "A dense forest surrounds you on all sides, composed of towering " +
       "maples and stately oaks. Blooming dogwoods splash pink and white " +
       "throughout the dark forest. To the west, you can see the back "+
       "of a dwelling, but the forest is too thick to walk that way. You "  +
       "see a marble road to the south, while a small path leads east " +
       "into the forest.\n");
 
   add_item("road",    "It lies to the south.\n");
   add_item("forest",  "It grows densely all around you.\n");
   add_item("dwelling","You can barely see it through the trees.\n");
   set_kretan_list(({"soldier/soldier3","soldier/soldier3",
                     "warrior/warrior4"}));
   set_kretan_origin(" jumps out of the forest");
 
   add_exit("for6","east", 0);
   add_exit("r21", "south",0);
   reset_room();
}
