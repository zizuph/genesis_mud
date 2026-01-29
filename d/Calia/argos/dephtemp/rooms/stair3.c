/*
**  Temple of Dephonia, Level three, lookout tower
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/10/95    Created
**
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 4
object *guard=allocate(NUM);
 
make_monster(int i)
{
    if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"towguard");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" walks up the steps.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++)
      make_monster(i);
}
 
create_room() {
   set_short("Tower in the Temple of Dephonia");
   set_long(
      "You are at the top of a tower on the southern end of the temple " +
      "of Dephonia, high above the roof of the shrine. This chamber "+
      "is an observation post, large windows allowing you to look "+
      "in all four directions. A set of steps leads down to a "+
      "lower level.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item(({"out to the east","east","out to east","out east",
              "to east"}),"You can look out to the east.\n");
   add_cmd_item(({"out to the east","east","out to east","out east",
              "to east"}),"look",
              "Far to the east you see the tops of marble structures in "+
              "what looks like a city, a sea of dark forest between here "+
              "and there.\n");
   add_item(({"out to the west","west","out to west","out west",
              "to west"}),"You can look out to the west.\n");
   add_cmd_item(({"out to the west","west","out to west","out west",
              "to west"}),"look",
              "Far to the west you see a range of snow capped mountains, "+
              "distanced by a sea of dark forest.\n");
   add_item(({"out to the north","north","out to north","out north",
              "to north"}),"You can look out to the north.\n");
   add_cmd_item(({"out to the north","north","out to north","out north",
              "to north"}),"look",
              "To the north you look over the roof of the temple. It is a "+
              "massive diamond-shaped structure made of glassy black "+
              "marble. You admire the crystal mosaic of the dome over "+
              "the sanctuary in the middle.\n");
   add_item(({"out to the south","south","out to south","out south",
              "to south"}),"You can look out to the south.\n");
   add_cmd_item(({"out to the south","south","out to south","out south",
              "to south"}),"look",
              "To the south all you see is a never-ending sea of the dark "+
              "trees of the surrounding forest.\n");
 
   add_item(({"windows","window"}), "There are large windows all "+
      "around the room, allowing you to look out to the east, "+
      "west, north and south.\n");
 
   add_item(({"stairwell","steps","stairs"}),
      "Made of slick black marble, the wide steps with no bannisters " +
      "lead down to a lower level.\n");
 
   add_exit(ROOM_DIR+"stair2",  "down", 0);
   reset_room();
}
 
