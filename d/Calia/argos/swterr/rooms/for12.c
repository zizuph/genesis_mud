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
 
object wolf=0;
 
void
reset_room()
{
    if (wolf) return;
    wolf=clone_object(NPC_DIR+"wolf");
    wolf->move(THIS);
    tell_room(THIS, QCNAME(wolf)+" trots through the woods.\n");
}
 
/* room definition */
void
create_room()
{
   set_short("A dark forest");
   set_long(break_string(
       "You walk to the end of a path through a dark forest.  Tall pines " +
       "surround you on all sides, the wind swiping their sharp needles " +
       "at your skin.  You see a shallow pit in the ground here, filled " +
       "with leaves and small bones, obviously the den of some creature.  " +
       "The forest grows so thick here that your only way out is back " +
       "west.\n",70));
 
    add_item("pit","It seems dug out by an animal.\n");
    add_item("leaves","The leaves in the pit seem very crumpled.\n");
    add_item("bones","They are scattered about, some still red with meat.\n");
    add_item(({"forest","trees"}), break_string(
        "Towering pine trees, their bark as black as night and their " +
        "dark-green needles sharp enough to cut.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"for11","west",0);
    reset_room();
}
