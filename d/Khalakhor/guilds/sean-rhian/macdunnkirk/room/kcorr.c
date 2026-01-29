/* Kirk Abbey Cooridor Base Room
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/10/97     Zima        Created
**
*/
/* inherits/includes */
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
string  extra="";
 
void init_kcorr(string cwall, string wwall, string up, string dwn) {
   set_short("Corridor in the abbey");
   set_long(
      "   You are in a corridor which runs "+up+" and "+dwn+" through "+
      "the abbey of the kirk. Opaque windows line the "+wwall+"ern "+
      "wall of the passageway, their panes set in a lattice pattern. "+
      "Candelabrum stand along the corridor between the windows, laden "+
      "with flickering candles, dimly lighting the long stone hall. "+
      "An open doorway leads into a chamber of the abbey to the "+
      cwall+". "+extra+"\n");
 
   INSIDE;
   add_item("corridor",
      "It is a long corridor through the abbey of the kirk, linking the "+
      "myriad of chambers used by the manachs who live here. It runs "+up+
      " and " + dwn + ".\n");
   add_item("abbey",
      "It is a building attached to the kirk where the manachs who take "+
      "care of this place live and work.\n");
   add_item("windows",
      "The windows are tall and thin, their tops rising to a pointed "+
      "arch. They line the "+wwall+"ern wall of the corridor, their "+
      "opaque panes a lattice of diamond shaped panes of a cream "+
      "color.\n");
   add_item(({"candelabra","candelabrum","candelabras","candles"}),
      "The ornate candelabrum sit along the "+wwall+"ern wall, one "+
      "between each pair of windows. Each is made of gold and ornately "+
      "crafted with elegant twists and curves which flank out from "+
      "a tall central staff. Dozens of thick white candles flicker "+
      "in the holders of each, dimly lighting the corridor.\n");
   add_item(({"door","doorway","chamber"}),
      "A pointed arch marks the entrance to one of the abbey chambers "+
      "to the "+cwall+".\n");
}
 
/* room definition */
void create_khalakhor_room() {
   set_short("Kirk abbey corridor base room");
   set_long("Kirk abbey corridor base room");
}
