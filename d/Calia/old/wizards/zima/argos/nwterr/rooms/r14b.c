/* Argos Road
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 11/18/96 Zima             Created
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A marble road along a river");
   set_long(
       "The rush of the river echoes through the thick forest which "+
       "escorts it on its way through this peaceful valley. The marble "+
       "road parallels the river as it flows from the northwest to "+
       "the east.\n");
 
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It follows the river's bank to the northwest and east.\n");
 
    add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "The forest on the other side of the river seems dark and " +
       "mysterious.\n");
 
    add_item("forest",
        "Stately oaks and maples grow densely along the north side of "+
        "the road.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r14a","northwest",0);
    add_exit(ROOM_DIR+"r15","east",0);
}
