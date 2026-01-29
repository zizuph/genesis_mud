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
       "The chirp of a solitary songbird comes from deep within the forest "+
       "as you walk along a dusty path through the myriad of maples, oaks "+
       "and evergreens. You can make out the tops of some mountains far "+
       "to the east, looming along the border of the forest.\n");
 
    add_item("path",
        "A narrow dirt path winding through the woods, it winds "  +
        "towards the southwest and east.\n");
    add_item(({"bird","songbird"}),
        "You can't see him anywhere, but his cheery song drifts along "+
        "the breeze from somewhere deep in the woods.\n");
    add_item("mountains",
        "You can barely see the peaks of some mountains far to the east "+
        "over the tops of the trees.\n");
#include "r2.h"
 
    /* exits */
    add_exit(ROOM_DIR+"r2i","southwest",0);
    add_exit(ROOM_DIR+"r3","east",0);
}
