/* Path through dark forest to Dephonian Temple
**
** History:
** Date        Coder       Action
** 12/14/94    Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A path through a dark forest");
   set_long(break_string(
      "You walk into a clearing and are surprised to find a large " +
      "temple of black marble sitting in the middle of this isolated " +
      "forest. The temple seems to be diamond-shaped, though you can " +
      "barely see more than the front, the black pines surrounding " +
      "it on all sides. Judging from the close growth around the " +
      "walls of the structure, you guess it is probably a deserted " +
      "and forgotten edifice, though you get a strange sense of " +
      "darkness from its black walls. A set of steps leads up " +
      "to the portico of the temple, while a path leads north " +
      "through the forest.\n",70));
 
    add_item("temple", break_string(
      "It is an enromous ancient structure with a rows of pillars " +
      "lining its outer walls. A rectangular portico has been built " +
      "on this northern end of the diamond-shaped monolith, a set " +
      "of steps leading up into it. The darkness of the temple walls " +
      "seem to absorb even the sunlight.\n",70));
 
    add_item("portico", break_string(
      "It is a rectangular appendage built onto the northern corner " +
      "of the temple, tall pillars supporting its roof. It seems " +
      "to be the entrance to the mysterious black structure.\n",70));
 
    add_item("pillars", break_string(
      "Massive columns of black marble, topped with elaborate capitals " +
      "which are hewn into the image of writhing snakes, they line " +
      "the outer walls of the temple on all sides and support the " +
      "roof of the portico above the entrance.\n",70));
 
    add_item("steps", break_string(
      "A steep set of short steps rise above your head to the " +
      "floor of the temple's portico, made of the same black " +
      "marble as the rest of the structure. They are so polished " +
      "that they seem to be coated with glass.\n",70));
 
    add_item("entrance", break_string(
      "You can't see it from here, but you guess it is hidden behind " +
      "the shadows of the temple's portico.\n",70));
 
    add_item(({"forest","trees","branches"}), break_string(
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n",70));
 
    add_item("path",
       "It leads north back into the forest.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"tdpath5","north",0);
    add_exit(ROOM_DIR+"portico","steps","@@steps");
}
 
steps()
{
    write(break_string(
          "You walk up the steep steps of the temple, almost " +
          "slipping on the glassy black marble.\n",70));
   return 0;
}
