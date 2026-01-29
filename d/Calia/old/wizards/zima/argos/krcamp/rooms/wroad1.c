/* Road through Batallion Five Camp
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 8/1/96      Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("In a military camp");
   set_long(
      "Tall dark pines rise like the walls of a fortress to the west, "+
      "shading this small dusty path on the western side of the camp. "+
      "More tents line the path along the east side, where there is "+
      "an entrance open to one of them. A gentle breeze in the branches "+
      "of the trees is the only sound in this quiet corner of the tent "+
      "citadel.\n");
 
    add_item(({"trees","tree","pines","pine","forest"}),
       "They are tall dark pines with black bark and needles grow "+
       "thickly along the western side of the path.\n");
    add_item("path",
        "Just a dusty path which winds through the tents in this "+
        "part of the encampment. It leads north and south between "+
        "the thick forest and a line of tents.\n");
    add_item(({"cluster","tent","tents","entrance","entrance","flap",
       "flaps","camp","encampment"}),
       "Large round tents sit to the east, with their tall "+
       "cone-shaped tops rising to a point. They are made of canvas "+
       "striped vertically with various colours. There is an entrance "+
       "to one of them open to the east.\n");
 
    /* exits */
    add_exit("nroad1", "north",0);
    add_exit("wroad2",  "south",0);
    add_exit("b5tent6", "east", 0);
}
