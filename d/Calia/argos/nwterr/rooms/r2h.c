/* Argos Road
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 10/1/96  Zima             Argos road extened
** 1997/1/26  ?              Previous update?
** 2010/9/2 Lavellan         Typo
** 2016/5/12 Jaacar          Typo
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("A path through the forest");
   set_long(
       "The forest is eerily quiet here, only a slight breeze dancing "+
       "through the branches of the trees of the surrounding woods. High "+
       "above you, vultures circle with the elegance of death, a forboding "+
       "sign of the dangers of an unknown forest. The path winds between "+
       "the thick trees to the northwest and east.\n");
#include "r2.h"
    add_item("path",
        "A narrow dirt path winding through the woods, it winds "  +
        "towards the northwest and east.\n");
    add_item(({"vulture","vultures"}),
        "They are bald, hook-beaked birds with a large wing span, circling "+
        "high in the sky above you, seeking the bodies of the dead.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r2g","northwest",0);
    add_exit(ROOM_DIR+"r2i","east",0);
}
