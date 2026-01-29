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
       "You come to a turn in the path through a dark forest, dead leaves " +
       "crunching under your feet.  You are surrounded by ominous black-" +
       "barked oaks which seem almost dead with their brown leaves.  " +
       "The narrow path leads west, and turns here to the south.\n",70));
 
    add_item(({"forest","trees"}),
        "Black-barked oak trees with brown leaves.  They look almost dead.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"for7","west",0);
    add_exit(ROOM_DIR+"for13","south",0);
}
