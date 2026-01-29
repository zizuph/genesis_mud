/* Kirk of Port City - Corridor
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 5/25/97     Zima        Created
**
*/
/* inherits/includes */
#include "defs.h"
inherit  ROOM+"kcorr";
int      do_step_out();
 
/* room definition */
void create_khalakhor_room() {
   init_kcorr("west","east","north","south");
   set_long(
      "   You are at the main entrance of the abbey of the kirk, the place "+
      "where the manachs who care for this place live and work. Opaque "+
      "windows line the eastern wall of the passageway, their panes "+
      "set in a lattice pattern. Candelabrum stand along the corridor "+
      "between the windows, laden with flickering candles, dimly lighting "+
      "the long stone hall. There is a doorway leading into a chamber "+
      "of the abbey to the west, while the main entrance leads out to "+
      "the east. The corridor runs north and south.\n");
   add_item("entrance",
      "The main entrance of the abbey is to the east. It leads out "+
      "into the garden.\n");
   add_exit("kcorr4",  "north");
   add_exit("kcorr6",  "south");
   add_exit("kgarden5","east",&do_step_out());
   add_exit("klibrary","west");
}
 
int do_step_out() {
   write("You step out of the abbey into the garden.\n");
   return 0;
}
