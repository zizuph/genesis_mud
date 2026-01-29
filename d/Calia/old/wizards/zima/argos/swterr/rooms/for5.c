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
       "You continue through the dark forest, surrounded by black-barked " +
       "oak trees.  You would believe they were dead, if the brown leaves " +
       "did not cling to their branches. The forest floor is " +
       "covered with dead leaves, which crunch loudly as you walk, " +
       "echoing through the forest.  The path leads to the north and " +
       "east.\n",70));
 
    add_item(({"forest","trees"}),
        "Black-barked oak trees with brown leaves.  They look almost dead.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"for2","north",0);
    add_exit(ROOM_DIR+"for6","east",0);
    reset_room();
}
