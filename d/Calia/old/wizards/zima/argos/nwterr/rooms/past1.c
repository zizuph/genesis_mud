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
       "A green pasture spreads out before you to the north, where a " +
       "fence seems to enclose a lush field.  To the east there is a small " +
       "dwelling, probably belonging to a local agrarian.  A small path " +
       "leads south through the forest, while you see an entrance to the "  +
       "fenced field to the northwest.\n",70));
 
    add_item("forest", "It grows densely to the south.\n");
    add_item("path",   "It leads south through the forest.\n");
    add_item(({"pasture","field"}),
             break_string( 
             "Spreading out into fields to the north, the pasture is " +
             "covered with lush green grass.  Part of it is fenced " +
             "in.\n",70));
    add_item("fence", break_string(
             "A simple wooden fence, enclosing a field to the north.  " +
             "There is a gate through the fence to the northwest.\n",70));
    add_item("grass", break_string(
             "Lush green grass, kept short by grazing sheep, it covers " +
             "the gently rolling pasture.\n",70));
    add_item("dwelling", break_string(
             "Made of stone with a wooden roof, the small dwelling " +
             "seems a bit run down, though lived-in.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"pastd","east",0);
    add_exit(ROOM_DIR+"past2","northwest",0);
    add_exit(ROOM_DIR+"r20", "south",0);
}
