/* Kirk of Port City - Living quarters of the manachs
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 8/10/97     Zima        Created
** 3/7/98      Zima        Added support for Cimbaeth to make saltpeter
**
*/
/* inherits/includes */
inherit  "/d/Khalakhor/std/room";
#include "defs.h"
#include "kkitchen.h"
#include <macros.h>
#include <stdproperties.h>
#define  FIRST_STEP 1
#define  LAST_STEP  19
#define  SHORTTIME 3.0
#define  LONGTIME  20.0
#define  POTC    "The contents of the small copper pot in the hearth "
#define  POTDESC "There is a small copper pot hanging over the fire "+ \
                 "in the hearth. "
 
object monk=0;
int    step=0;
int    pothere=0;
 
#include "kkitchen.inc"
 
/*
** reset_room - get cimbaeth in here!
*/
void reset_room() {
   int i;
   if (!objectp(monk)) { /* he's not alive, create him */
      monk=clone_object(SR_NPC+"cimbaeth");
      monk->equip_me();
      monk->move(TO);
      tell_room(TO,QCTNAME(monk)+" meanders into the kitchen.\n");
   }
   else if (!objectp((present(monk,TO)))) { /* not here, call him home */
      tell_room(environment(monk),QCTNAME(monk)+" runs out in a hurry.\n");
      monk->move(TO);
      tell_room(TO,QCTNAME(monk)+" meanders into the kitchen.\n");
   }
}
 
/*
** create_khalakhor_room
*/
void create_khalakhor_room() {
   set_short("Kitchen of the abbey");
   set_long(
      "   A large stone hearth along the north wall dominates this steamy "+
      "chamber where several fires burn beneath stewing pots. A long "+
      "wooden table with a nicked and food-stained top sits in the "+
      "center of the room, while various pots and pans hang on the "+
      "west wall. The aroma of a large, hearty meal permeates the air, "+
      "making your stomach grumble a bit.\n");
   INSIDE;
 
   add_item("hearth",
      "It is a long stone hearth built along the north wall of the "+
      "chamber. Several fires burn in its charred pit at the bottom, "+
      "while pots hang above the flames. It makes the kitchen seem "+
      "more like a large oven.\n");
   add_item(({"fire","fires","flames"}),
      "Several fires burn in the pit of the hearth, cooking the contents "+
      "of the pots hanging above.\n");
   add_item(({"pots","pans"}),
      "A few pots are hung in the hearth over the flames, the smell of "+
      "a hearty stew filling the room. Others hang neatly along the "+
      "south wall, spotless and clean.\n");
   add_item("stew",
      "You can smell the stew in the pots, but they are covered with "+
      "large lids.\n");
   add_item("table",
      "It is a long wooden table, its top chipped and nicked from all "+
      "the chopping which it must endure. Scraps of vegetables are "+
      "scattered across its heavily stained surface.\n");
 
   add_exit("kdining","east");
   reset_room();
}
