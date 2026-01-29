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
 
void create_room() {
   set_short("A dense forest");
   set_long(
       "A dense forest surrounds you on all sides, composed of towering " +
       "maples and stately oaks. Blooming dogwoods splash pink and white " +
       "throughout the dark forest. There is a disturbing silence in " +
       "this part of the woods. To the west, you see a marble road, " +
       "while a small path leads to the northwest and east.\n");
 
   add_item("road",   "It lies to the west.\n");
   add_item("forest", "It grows densely all around you.\n");
 
   set_kretan_list(({"soldier/soldier3","soldier/soldier3"}));
   set_kretan_origin(" steps out from behind a tree");
 
   add_exit("for2","northwest",0);
   add_exit("for4","east",     0);
   add_exit("r17", "west",     0);
   reset_room();
}
