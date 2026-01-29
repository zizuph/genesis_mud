/* Room in Argos area.

   Coded by Zima.

   History:
         11/5/95        Shale exit removed                  Maniac
*/

/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 2
object *guard=allocate(NUM);
object commander=0;
 
void
make_guard(int i)
{
     if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"guard");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" takes his post.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++) make_guard(i);
   if (commander) return;
   commander=clone_object(NPC_DIR+"tcommder");
    commander->equip_me();
   commander->move(THIS);
   tell_room(THIS, QCNAME(commander)+" salutes his men.\n");
}
 
/* room definition */
void
create_room()
{
   set_short("A marble road");
   set_long(break_string(
      "You are walking down the marble road through a thick forest.  " +
       "Far to the east on the horizon you see the summits of a chain " +
       "of mountains, rising majestically from the surrounding sea of " +
       "trees.  The road bends here leading east toward the mountains, " +
       "and northwest through the forest.\n", 70));
 
    add_item("road", break_string(
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It leads east toward the mountains and northwest through the "+
       "forest.\n",70));
 
    add_item("mountains", break_string(
       "Looming along the eastern horizon, the mountains seem high but " +
       "passable along the marble road.\n",70));
 
    add_item("forest", break_string(
        "A mixture of maples, oaks and evergreens, the forest " +
        "grows densly on either side of the road, keeping you " +
        "on your path.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r4","northwest",0);
    add_exit(ROOM_DIR+"r6","east",0);
    reset_room();
}
