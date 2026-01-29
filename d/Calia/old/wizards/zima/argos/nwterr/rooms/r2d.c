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
       "The woods are strangely quiet here, as if something has " +
       "scared off all the woodland creatures. You look up and notice "+
       "a pair of vultures circling the sky, their keen eyes watching "+
       "your every move. You look down and see a small puddle on the path, "+
       "which meanders along to the southwest and east.\n");
#include "r2.h"
    add_item("path",
        "A narrow dirt path winding through the woods, it winds "  +
        "towards the southwest and east. There is a small puddle " +
        "in the middle of the path.\n");
    add_item(({"mud","puddle","blood"}),
        "You look closely at the small puddle in the path, and discover "+
        "that it red blood which has been spilled on the forest floor!\n");
    add_item(({"vulture","vultures"}),
        "They are bald, hook-beaked birds with a large wing span, circling "+
        "high in the sky above you, seeking the bodies of the dead.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r2c","southwest",0);
    add_exit(ROOM_DIR+"r2e","east",0);
}
