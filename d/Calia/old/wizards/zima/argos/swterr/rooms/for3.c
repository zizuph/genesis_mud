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
       "ripping the utter quiet of this forest.  Purple thistle grows " +
       "all around you in bunches.  The forest grows so " +
       "densely here that the only way out is back west.\n",70));
 
    add_item(({"forest","trees"}),
        "You are surrounded by the trees of the forest.\n");
    add_item("vines", "They grow up the trunks of the trees.\n");
    add_item("thistle", break_string(
             "Its purple flowers invite you place your hand upon " +
             "the sharp thorns beneath its leaves.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"for2","west",0);
}
