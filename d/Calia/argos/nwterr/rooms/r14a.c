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
void create_room()
{
   set_short("A marble road along a river");
   set_long(
       "You are walking along the northern bank of a wide river on a "+
       "marble road through a thickly forested valley. The river "+
       "lies to the west and southwest of you, flowing from the foothills "+
       "of the north and turning southeast as it makes its way further "+
       "into the valley. The road leads west onto an elegant marble "+
       "bridge which spans the river, and follows the northern bank "+
       "of the river to the southeast.\n");
 
 
   add_item("road",
      "Made of long slabs of white marble, this road seems fairly " +
      "new. It leads southeast along the river's bank and west onto "+
      "a bridge.\n");
   add_item("river",
      "The river is very wide, and seems deep with its rushing torrents. " +
      "It lies to the west and southwest of you, flowing out of the "+
      "foothills to the north and turning southeast on its journey "+
      "deeper into the valley.\n");
   add_item("forest",
       "Stately oaks and maples grow densely along the north side of "+
       "the road.\n");
   add_item("foothills",
      "Heavily forested with trees, the foothills roll along the "+
      "western horizon, bordering the mountains behind them.\n");
   add_item("bridge",
      "It is an arched bridge made of white marble, skillfully sculpted "+
      "as both a work of art and a passage across the river. It looks "+
      "fairly new.\n");
 
    /* exits */
    add_exit("mbridge","west",0);
    add_exit("r14b","southeast",0);
    add_exit("sfor1","north",0);
}
