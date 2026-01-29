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
       "throughout the dark forest, and you can hear the hoot of an owl " +
       "from the canopy of leaves. To the west, you see a marble road, " +
       "while a small path leads to the northwest and southeast.\n");
 
   add_item("road",   "It lies to the west.\n");
   add_item("forest", "It grows densely all around you.\n");
 
   set_kretan_list(({"sentry/sentry3","sentry/sentry3"}));
   set_kretan_origin(" steps out from behind a tree");
 
   add_exit("for1","northwest",0);
   add_exit("for3","southeast",0);
   add_exit("r16", "west",     0);
   reset_room();
}
