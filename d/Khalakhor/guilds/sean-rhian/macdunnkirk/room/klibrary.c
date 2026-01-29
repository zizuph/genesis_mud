/* Kirk of Port City - Priory Library
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/5/97      Zima        Created
** 4/10/97     Zima        Recoded to use library base room
**
*/
#include "defs.h"
inherit  SR_ROOM+"libbase";
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"
 
void create_khalakhor_room() {
   set_short("Library of the abbey");
   set_long(
      "   This is the library of the abbey, filled with tall shelves lined "+
      "with books chained to their shelf. Light from the candles of a "+
      "chandelier above blends with dim sunlight from a window on the "+
      "west wall. The musty smell of old parchment and the wood and "+
      "leather covers of the books mix with the scent of the "+
      "candles.\n");
 
   INSIDE;
   add_item(({"room","chamber","library"}),
      "It is one of the chambers of the abbey, with smooth stone walls, "+
      "lined with tall shelves housing many books.\n");
   add_item("shelves",
      "They are heavy, antique oak shelves, beautifully carved, set around "+
      "the walls housing a great collection of books.\n");
   add_item("books",
      "The books are chained to the shelves, so they can not be taken out. "+
      "They look very old, with covers of wood, leather and cloth. Most "+
      "have titles in languages that you can not read, but there are a few "+
      "titles you can.\n");
   add_item(({"chandelier","chain","candles","light"}),
      "Suspended by a thick gold chain from the central point of the "+
      "vaulted ceiling high above you is an ornate chandelier filled with "+
      "dozens of burning candles, their graceful flickering flames filling "+
      "the chamber with a subtle light.\n");
   add_item("window",
      "It is a tall, thin window with a pointed arch top, like those "+
      "of the corridor. Its opaque panes are set in a lattice of "+
      "diamond-shaped cream colored glass.\n");
   add_item("titles",
      "You might be able to read the titles of some of the books.\n");
 
   add_exit("kcorr5","east");
   init_library(
      ({ "'titles'",
         "[the] 'prologue'",
         "[the] [age] [of] 'rebirth'",
         "[the] [age] [of] 'legend'",
         "[the] [age] [of] 'wisdom'",
         "[the] [age] [of] 'might'",
         "[the] [age] [of] 'clans'",
         "[the] [scroll] [of] 'vestments'"
      }),
      ({"titles","hist0","hist1","hist2","hist3","hist4","hist5","vestments"}),
      29,0);
}

