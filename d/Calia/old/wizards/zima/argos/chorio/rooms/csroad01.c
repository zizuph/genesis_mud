/* Road to Argos
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/30/97     Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A cobblestone road along a river");
   set_long(
      "You are standing at the end of an old cobblestone road which runs "+
      "along the edge of a rushing river. There is a street which leads "+
      "to the northeast, toward a small village built on the gentle "+
      "slope of a large hill. A banner flies from atop a tall pole at "+
      "the edge of the road. To the south you see a dock and a small "+
      "house set in the bend of the river, while the old road leads back "+
      "along the river to the northwest.\n");
 
#include "csroad.h"

   add_item("street",
      "It leads to the northeast toward the village.\n");
   add_item("banner",
      "It is a white banner with the emblem of a sun burst in red and "+
      "gold, with the words 'Chorio Hagios' embroidered beneath.\n");
   add_item("pole",
      "It is a tall metal pole set in the ground next to the street. "+
      "A white banner flies from its top.\n");
   add_item("dock",
      "It is a small wooden dock built along the bank of the river "+
      "to the south, probably a landing place for boats which "+
      "travel up and down the river.\n");
   add_item("house",
      "It is a small wooden house next to the dock.\n");
 
   add_exit("csroad02","northwest",0);
   add_exit("street01","northeast",0);
   add_exit("dock",    "south",    0);
}
