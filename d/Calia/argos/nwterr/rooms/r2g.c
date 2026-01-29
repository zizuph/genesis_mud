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
       "You are walking along a path through a thick forest, the site of "+
       "a recent skirmish, or perhaps a murder. Blood is spattered along "+
       "the dusty trail, testifying to the recent gruesome events. The trees "+
       "of the forest tower above you, their branches waving gently in the "+
       "slight breeze, as if warning you of impending danger.\n");
#include "r2.h"
    add_item("path",
        "A narrow dirt path winding through the woods, it winds "  +
        "towards the west and southeast. There are pools of blood muddying "+
        "the dusty trail.\n");
    add_item(({"mud","pool","pools","blood"}),
        "Large pools of fresh blood testify to the recent violence done "+
        "here, making a reddish mud out of the forest floor.\n");
 
    corpse=clone_object(OBJ_DIR+"nrcorpse");
    corpse->move(this_object());
 
    /* exits */
    add_exit(ROOM_DIR+"r2f","west",0);
    add_exit(ROOM_DIR+"r2h","southeast",0);
}
