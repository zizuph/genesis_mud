/* Argos Road
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 10/1/96  Zima             Argos road extened
** 1997/1/26  ?              Previous update?
** 2010/9/2 Lavellan         Typo
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("A path through the forest");
   set_long(
       "You are walking along a dusty path through a thick forest. The "+
       "woods are quiet here, a gentle breeze cooling your face and easing "+
       "your mind. Colorful wildflowers grow along the path's edge as it "+
       "meanders through the trees to the west and northeast.\n");
 
    add_item("path",
        "A narrow dirt path winding through the woods, it winds "  +
        "towards the west and northeast.\n");
#include "r2.h"
    /* exits */
    add_exit(ROOM_DIR+"r2h","west",0);
    add_exit(ROOM_DIR+"r2j","northeast",0);
}
