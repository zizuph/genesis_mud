/* Path through dark forest to Dephonian Temple
**
** History:
** Date        Coder       Action
** 12/14/94    Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A path through a dark forest");
   set_long(break_string(
      "The forboding caw of a large black bird perched high above you " +
      "in the branches makes you feel very uncomfortable standing here. " +
      "The path cuts to the northwest and south through the dense forest " +
      "of black pines, and you feel you should be on your way down " +
      "it.\n",70));
 
    add_item(({"forest","trees","branches"}), break_string(
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n",70));
 
    add_item("bird", break_string(
       "It is a rather large raven, though none like you have seen " +
       "before, as it seems to have a small patch of red feathers " +
       "on its breast. He seems to be watching you intently.\n",70));
 
    add_item("path",
       "It looks like it has been used for decades, as well as recently.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"tdpath2","northwest",0);
    add_exit(ROOM_DIR+"tdpath4","south",0);
}
