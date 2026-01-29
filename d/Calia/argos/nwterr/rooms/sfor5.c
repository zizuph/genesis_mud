/* Satyr Forest, a Newbie area
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/18/95   Zima          Created
**/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NumSatyrs 3
#include "sfornpcs.h"
 
/* room definition */
void create_room() {
   set_short("A dense forest");
   set_long(
       "The underbrush of the floor of the forest continues to crunch "+
       "and crackle as you stomp through its deep matting of dead leaves "+
       "and twigs. You hear the hoot of an owl from somewhere in the "+
       "branches of the trees, but you can not spot it. A newly broken "+
       "branch of a dogwood lies at your feet, its flowers still vibrant "+
       "with pink blooms.\n");
 
#include "sfordesc.ext"
   add_item("branch",
            "It is a branch recently broken off from a dogwood tree. "+
            "The four-petaled blooms are still full of their pink color.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"sfor4","northwest",0);
   add_exit(ROOM_DIR+"sfor6","northeast",0);
   set_alarm(5.0,0.0,"reset_room");
}
