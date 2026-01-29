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
 
object corpse=0;
 
void reset_room() {
   if (corpse) corpse->reset_me();
}

void create_room() {
   set_short("A path through the forest");
   set_long(
       "A feeling of danger pervades the woods, the stench of spilled "+
       "blood filling your nostrils. The trees stand all along the path "+
       "muddied with blood, silent witnesses of the atrocities commited "+
       "in their sight. High above, you see vultures circling, their "+
       "keen eyes watching your every move.\n");
#include "r2.h"
    add_item("path",
        "A narrow dirt path winding through the woods, it winds "  +
        "towards the northwest and east. There are pools of blood muddying "+
        "the dusty trail.\n");
    add_item(({"mud","pool","pools","blood"}),
        "Large pools of fresh blood testify to the recent violence done "+
        "here, making a reddish mud out of the forest floor.\n");
    add_item(({"vulture","vultures"}),
        "They are bald, hook-beaked birds with a large wing span, circling "+
        "high in the sky above you, seeking the bodies of the dead.\n");
 
    corpse=clone_object(OBJ_DIR+"nrcorpse");
    corpse->move(this_object());
 
    /* exits */
    add_exit(ROOM_DIR+"r2e","northwest",0);
    add_exit(ROOM_DIR+"r2g","east",0);
}
