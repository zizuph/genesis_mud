/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A green pasture");
   set_long(break_string(
       "You are standing near a gate inside a fenced-in pasture. " +
       "The lush grass grows green here, though it seems to be kept very " +
       "short, probably by some grazing animals.  " +
       "A small path leads out of the pasture to the southeast, " +
       "while the pasture opens up to the north and east.\n",70));
 
    add_item("gate", "A simple wooden gate in the fence.\n");
    add_item("path",   "It leads southeast out of the pasture.\n");
    add_item(({"pasture","field"}), break_string(
             "The pasture is covered with short green grass within " +
             "the fence, and stretches to the north and east.\n",70));
    add_item("grass", break_string(
             "Lush green grass, kept short by grazing sheep, it covers " +
             "the gently rolling pasture.\n",70));
    add_item("fence", break_string(
             "A simple wooden fence, enclosing the field you are standing " +
             "in.  It borders the pasture to the west and south here, " +
             "while a gate leads out to the southeast.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"past3","east",0);
    add_exit(ROOM_DIR+"past5","north",0);
    add_exit(ROOM_DIR+"past1","southeast",0);
}
