/* Kirk of Port City - Apothecary - where potions/mixtures will be made
**                     when needed.
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/18/98     Zima        Created
*/
/* inherits/includes */
#include "defs.h"
inherit   "/d/Khalakhor/std/room";
#include <stdproperties.h>
object bench;
 
int chk(string id, string fname) {
   if (!objectp(present(id,bench))) {
      (clone_object(SR_TOOL+fname))->move(bench);
      return 1;
   }
   return 0;
}
 
void check_bench() {
   if ((chk("mortar","cmortar") + chk("pestle","pestle"))<0)
      tell_room(TO,"A young novishagh rushes in, places something on the "+
                   "bench and rushes back out.\n");
}
 
void reset_room() {
   check_bench();
}
 
/* room definition */
void create_khalakhor_room() {
   set_short("Apothecary of the abbey");
   set_long(
      "   The pungent smells of dried herbs permeate the air in this "+
      "chamber, tickling your nose with various aromas. There is a large "+
      "set of shelves along the north wall, filled with vials, jars and "+
      "pots of various sizes. A long cabinet sits along the south "+
      "wall, its shelves filled with a variety of leaves, berries, sticks "+
      "and powders neatly labeled or held in jars, along with sets of "+
      "of mortars and pestles of various sizes. There is a long "+
      "workbench in the center of the room, its top stained with various "+
      "dark colors. A somber stained glass window is the only adornment of "+
      "the chamber, set in an arch in the west wall.\n");
 
   INSIDE;
   add_item(({"herbs","berries","leaves","sticks","powders"}),
      "A wide variety of herbs, berries, leaves, sticks and powders "+
      "are stored in the cabinet, each neatly placed and labeled or "+
      "stored in jars. Their aromatic scents fill the room with a "+
      "strong smell.\n");
   add_item("cabinet",
      "It is long cabinet made of wood with no special design. Inside "+
      "its glass doors is a wide variety of labeled herbs and jars, "+
      "along with various mortars and pestles.\n");
   add_item(({"mortar","pestle","mortars","pestles"}),
      "Ceramic bowls and grinding tools used to crush herbs. They are "+
      "set neatly inside the cabinet.\n");
   add_cmd_item("cabinet",({"open","unlock"}),
      "The cabinet is locked and cannot be opened.\n");
   add_item(({"vials","jars","pots"}),
      "Vials, jars and pots of ceramic and glass are placed along "+
      "the shelves, cleaned and empty.\n");
   add_item("shelves",
      "Inornate shelves along the north wall house vials, jars and "+
      "pots neatly placed according to size.\n");
   add_item("window",
      "It is a tall, thin window with a pointed arch top, like those "+
      "of the corridor. Its opaque panes are set in a lattice of "+
      "diamond-shaped cream colored glass.\n");
 
   add_exit("kclassrm","north");
   bench=clone_object(SR_OBJ+"workbench");
   bench->move(TO);
   reset_room();
}

