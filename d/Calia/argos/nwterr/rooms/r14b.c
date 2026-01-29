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
       "stands guard over the waters as they make their way through "+
       "this quiet valley. You are standing on a marble road which "+
       "follows the river along its northern bank. The forest on the other "+
       "side of the river to the south looks dark and mysterious.\n");
 
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It follows the river's bank to the northwest and east.\n");
    add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "It meanders from the northwest to the east, flowing by you to "+
       "the south.\n");
    add_item(({"forest","woods","trees"}),
        "Stately oaks and maples grow densely along the north side of "+
        "the road. Across the river to the south, black pines populate "+
        "the river's edge and the valley beyond.\n");
 
    /* exits */
    add_exit("r14a","northwest",0);
    add_exit("r15","east",0);
}
