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
       "You come to a small clearing in the forest, paths leading out " +
       "to the west, east, northwest and northeast.  You are surrounded " +
       "by dark pine trees, their limbs seeming to reach out with the " +
       "wind to cut you with their sharp needles.  Dead pine needles " +
       "carpet the floor of the forest, softening your footsteps, and " +
       "you think you hear a growl in the distance.\n",70));
 
    add_item(({"forest","trees"}), break_string(
        "Towering pine trees, their bark as black as night and their " +
        "dark-green needles sharp enough to cut.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"for9","west",0);
    add_exit(ROOM_DIR+"for11","east",0);
    add_exit(ROOM_DIR+"for4","northwest",0);
    add_exit(ROOM_DIR+"for6","northeast",0);
}
