/* Olive grove - olives can be picked here
**
** Date      Coder    Action
** -------   -------- ----------------------
** 11/16/95  Zima     Created
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "ogrove.h" /* allows picking of olives */
 
void reset_room() { NumOlives=MAX_OLIVES; }
 
void create_room() {
   set_short("An olive grove");
   set_long(
       "You are standing on a narrow path through an olive grove, the trees "+
       "set in neat rows all around you laden with fruit. A fence borders "+
       "the grove to the east, over which you see a dirt "+
       "road. In the distance from across the road you hear the rush "+
       "of the river. A dilapidated old shed sits to the south amongst "+
       "the trees.\n");
 
   add_item("trees",
            "Olive trees, set neatly in rows, laden with olives.\n");
   add_item("olives",
            "Clustered on the limbs of the trees, they seem ready to pick.\n");
   add_item("fence",
            "It is a crude wooden fence which separates the grove of olive "+
            "trees from the road.\n");
   add_item("river",
            "You can't see it from here, but you hear its flowing torrents "+
            "from the other side of the road.\n");
   add_item("road",
            "It is just an old dirt road. The fence prevents you from "+
            "reaching it from here.\n");
   add_item("shed",
            "It is an old wooden shed, years of torment by the weather has "+
            "almost eroded it away. Its broken door stands open to the "+
            "south.\n");
   add_item("door",
            "The old shed door stands open, but looks broken anyway.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"ogrove6","west",0);
   add_exit(ROOM_DIR+"ogrove9","south",0);
   reset_room();
}
