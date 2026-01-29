/* Kirk of Port City - Dining Hall of the Abbey
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 5/25/97     Zima        Created
**
*/
/* inherits/includes */
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include <stdproperties.h>
 
/* room definition */
void create_khalakhor_room() {
   set_short("the abbey dining hall");
   set_long(
      "   This chamber serves as the dining hall of the abbey. A long "+
      "table surrounded by dozens of neatly placed chairs sits in the "+
      "center of the chamber. A large tapestry adorns the eastern wall, "+
      "while a window is set in the northern. Chandeliers filled with "+
      "candles hang from the ceiling, filling the chamber with bright "+
      "light. The entrance of the hall from the corridor is to the "+
      "south, while a doorway leads out of the hall to the west.\n");
   INSIDE;
 
   add_item("table",
      "It is a very long oak table, polished to a high shine, mirroring "+
      "the light of the chandeliers above. It is surrounded by dozens "+
      "of evenly placed chairs, fit for an elegant banquet of any king. "+
      "The manachs obviously gather here to share their meals, a binding "+
      "activity for any community.\n");
   add_item("chairs",
      "Comfortable oak chairs are pushed under the table on all sides. "+
      "At the north end a larger chair is set for some person of honor.\n");
   add_item("tapestry",
      "Woven of fine wool, the tapestry runs the long length of the "+
      "eastern wall. It portrays a group of elves reclining on "+
      "blankets near a stream in the shade of nearby trees. Baskets "+
      "of bread, pots of honey and pitchers of drink abound at the "+
      "feast.\n");
   add_item(({"chandelier","chandeliers","candles"}),
      "Four large chandeliers made of gold, each with dozens of branches "+
      "filled with flickering candles, hang from the ceiling of the "+
      "chamber.\n");
   add_item("window",
      "The window is a mosaic of colored glass which portrays a circle "+
      "of nine elders and a great angel standing around a blazing fire "+
      "with hands joined. An inscription is written along the arched "+
      "top of the window.\n");
   add_item("inscription",
      "Set in the mosaic of the colored glass of the window, the "+
      "inscription crawls along the upper arched part of the window.\n");
   add_cmd_item("inscription","read",
      "Invoke the Cleansing Fires of Ardaugh\n");
   add_item(({"entrance","cooridor"}),
      "The entrance leads into the cooridor to the south.\n");
   add_item("doorway",
      "It leads west out of the hall, the scent of cooking food wafting "+
      "from it.\n");
 
   add_exit("kcorr2",    "south");
   add_exit("kkitchen",  "west");
}
