/* Argos Road
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 1993     Zima             Created
** 2/15/95  Zima             Entrance to Satyr Forest added
** 9/15/96  Zima             Cleaned up, messages added to mountain exits
** 11/18/96 Zima             Road Extension
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("A marble road in a forested valley");
   set_long(
     "You are walking along a marble road through a verdant valley heavily "+
     "forested with maples, oaks and dogwoods. To the east is an elegant "+
     "marble bridge which spans a wide, rushing river. The river flows from "+
     "the north and turns to the southeast after passing beneath the "+
     "bridge. At the foot of the bridge is a large marble block with "+
     "a tall pole set in it, a banner fluttering from its height.\n");
 
   add_item("banner",
      "It is a large blue banner made of silk, fluttering in the wind "+
      "atop a tall pole. The banner bears a regal emblem on it.\n");
   add_item("pole",
      "A tall pole made of marble, it holds aloft a large banner.\n");
   add_item("block",
      "It is a large block of marble at the foot of the bridge, serving "+
      "as a base for the banner pole and a cornerstone of the bridge. "+
      "A regal emblem is sculpted into its front face.\n");
   add_item("emblem",
      "It is the royal arms of the kingdom of Argos, a shield emblazoned "+
      "with a rampant winged horse, above which is a crown with three "+
      "jewels.\n");
   add_item("foothills",
      "Heavily forested with trees, the foothills roll along the "+
      "western horizon, bordering the mountains behind them.\n");
   add_item("bridge",
      "It is an arched bridge made of white marble, skillfully sculpted "+
      "as both a work of art and a passage across the river. It looks "+
      "fairly new.\n");
   add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "It flows from the foothills to the north, into the valley to "+
       "the southeast. A marble bridge spans its banks.\n");
   add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It leads up into the foothills to the west, and further " +
       "onto a bridge to the east.\n");
   add_item("mountains",
       "Looming along the western horizon, the mountains seem high but " +
       "passable along the marble road.\n");
   add_item(({"forest","maples","oaks","dogwoods","trees"}),
       "A mixture of maples, oaks and dogwoods, the forest grows "+
       "densly on either side of the road.\n");
 
   /* exits */
   add_exit("r13","up","@@doup");
   add_exit("mbridge","east",0);
}
int doup() {
   write("You walk west along the road up into the foothills.\n");
   return 0;
}
