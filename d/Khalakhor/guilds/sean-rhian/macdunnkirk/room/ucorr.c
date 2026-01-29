/* Kirk Abbey Cooridor - upper level -  Base Room
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/10/98     Zima        Created
**
*/
/* inherits/includes */
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
 
void init_ucorr() {
   string long;
   set_short("Corridor in the abbey");
   set_long("   You are in a long corridor which leads north and south "+
            "through the upper level of the abbey. Two candelabras flank "+
            "a small stained-glass window which adorns the eastern wall, "+
            "their branches laden with candles dimly lighting the stone "+
            "stone hallway. "); //completed in each room
 
   INSIDE;
   add_item(({"hallway","corridor","walls","floor"}),
      "It is a long corridor in the abbey of the kirk, its walls and floor "+
      "made of stone, leading north and south through the upper level.\n");
   add_item(({"candelabra","candelabrum","candelabras","candles"}),
      "The ornate candelabras stand along the eastern wall, flanking a "+
      "small stained-glass window. Each is made of gold and ornately "+
      "crafted with elegant twists and curves which branch out from "+
      "a tall central staff. Dozens of thick white candles flicker "+
      "in the holders of each, dimly lighting the corridor.\n");
   add_item("window",
      "The window is tall and thin, its top rising to a pointed arch. Set "+
      "in the eastern wall of the cooridor, its opaque panes are crafted "+
      "in a diamond lattice pattern, made of cream colored stained glass.\n");
}
 
/* room definition */
void create_khalakhor_room() {
   set_short("Kirk upper abbey corridor base room");
   set_long("Kirk upper abbey corridor base room");
}
