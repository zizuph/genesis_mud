/* Marble road west of the mountains
**
** History
** Date     Coder     Activity
** -------- --------- ------------------------------------------------------
** 1994     Zima      Created
** 4/1/95   Zima      Added hidden exit to Mystic Club
** 8/15/96  Zima      removed hidden exit to Mystic Club (disabled 12/95)
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("A path through the forest");
   set_long(
       "You walk along a narrow winding path through a dense forest " +
       "of towering trees. The air is fresh with the smell of the " +
       "forest, and the breeze moves lightly through the thick " +
       "canopy of leaves which shade the path. A bee whizzes by " +
       "your head with its sweet cargo on its way to its hive which " +
       "you see high in a tall oak. The path winds its way through the "+
       "woods "+
       "to the northwest and east.\n");
 
    add_item(({"bee","bees"}),
        "You see a few darting amongst the trees in the forest, many " +
        "in and out of a hive set high in an oak.\n");
    add_item("hive",
        "A waxy cellular structure, the bees have built their colony " +
        "home in the branches of a tall oak tree. The hive looks " +
        "almost alive with the activities of its black and yellow insects. " +
        "You decide that the hive is too high in the tree to climb, " +
        "and you are not sure if you would want to deal with its " +
        "angry inhabitants if you did.\n");
    add_item("oak",
        "A towering tree, its branches and leaves woven into the " +
        "canopy above the forest floor. A bee hive sits near the " +
        "trunk in the upper branches.\n");
    add_cmd_item("oak","climb","@@climb_oak");
    add_item("path",
        "A narrow dirt path winding through the trees, somewhat muddy " +
        "from recent rains. It leads northwest and east through " +
        "the trees, walled by underbrush on the north side.\n");
    add_item(({"canopy","leaves"}),
        "The dense canopy of leaves provides a peaceful shade " +
        "as you walk along the winding path.\n");
    add_item("forest",
        "A mixture of maples, oaks and evergreens, the forest " +
        "surrounds you with its beautiful hardwoods.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r1","northwest",0);
    add_exit(ROOM_DIR+"r2a","east",0);
}
 
string climb_oak() {
    return(
        "You decide that doing so would put you in a great hurt, " +
        "and you change your mind.\n");
}
