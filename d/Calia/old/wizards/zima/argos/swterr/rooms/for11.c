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
       "You walk along a path in a dark forest, surrounded by tall pines, " +
       "their needles able to draw blood.  Dead pine needles carpet the " +
       "forest floor, softening your footsteps.  You think you feel "   +
       "eyes watching you from the dense forest.  The path continues " +
       "to the east and west between the towering pines.\n",70));
 
    add_item(({"forest","trees"}), break_string(
        "Towering pine trees, their bark as black as night and their " +
        "dark-green needles sharp enough to cut.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"for10","west",0);
    add_exit(ROOM_DIR+"for12","east",0);
}
