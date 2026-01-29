/* Argos Road
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 10/1/96  Zima             Argos road extened
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("A path through the forest");
   set_long(
       "The trees of the forest shade the remnants of a murder scene "+
       "which seems to have recently disturbed the tranquility of the "+
       "woods. Pools of blood muddy the dusty path, evidence of the horror "+
       "which has befallen this place. Your spine tingles as you take in "+
       "the monstrous scene.\n");
#include "r2.h"
    add_item("path",
        "A narrow dirt path winding through the woods, it winds "  +
        "towards the west and southeast. There are pools of blood muddying "+
        "the dusty trail.\n");
    add_item(({"mud","pool","pools","blood"}),
        "Large pools of fresh blood testify to the recent violence done "+
        "here, making a reddish mud out of the forest floor.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r2d","west",0);
    add_exit(ROOM_DIR+"r2f","southeast",0);
}
