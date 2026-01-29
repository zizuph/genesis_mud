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
       "You are making your way through a thick forest of various " +
       "types of trees, along a path which winds its way through " +
       "the tranquil woods. The forest creatures seem a little " +
       "quiet along this stretch, even the wind is strangely calm. "+
       "The path winds to the west and northeast.\n");
 
    add_item("path",
        "A narrow dirt path winding through the woods, it winds "  +
        "towards the west and northeast.\n");
#include "r2.h"
    /* exits */
    add_exit(ROOM_DIR+"r2b","west",0);
    add_exit(ROOM_DIR+"r2d","northeast",0);
}
