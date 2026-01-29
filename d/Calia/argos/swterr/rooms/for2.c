/*
   Evil forest in Southwestern Territory of Argos
 
   Coder:    Zima
 
   Purpose:  Area with evil NPC's.  Eventually will hide path
             to an evil temple.
 
   History:  01.12.93   Created                         Zima
 
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
   set_short("A dark forest");
   set_long(break_string(
       "You walk along a small path within the depths of a dark " +
       "forest.  Black mohagany trees loom over you, as if they are " +
       "ready to attack.  Creeper vines climb the trunks of the trees, " +
       "almost hiding the bark near the base.  The forest floor is " +
       "covered with dead leaves, which crunch loudly as you walk, " +
       "ripping the utter quiet of this forest.  The path continues " +
       "south into the forest, and another east, while you see a dirt " +
       "road to the northeast.\n",70));
 
    add_item("road", "A dirt road, in the distance to the northeast.\n");
    add_item(({"forest","trees"}),
        "You are surrounded by the trees of the forest.\n");
    add_item("vines", "They grow up the trunks of the trees.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r20","northeast",0);
    add_exit(ROOM_DIR+"for5","south",0);
    add_exit(ROOM_DIR+"for3","east",0);
}
