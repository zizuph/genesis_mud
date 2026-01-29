#pragma strict_types
 
#include <stdproperties.h>
#include "/d/Emerald/defs.h"
 
inherit "/std/room";
 
void
create_room()
{
    object gate;
    set_short("The garden entrance");
    set_long("   You stand at the entrance of the garden. A " +
        "gracefully arched trellis stands here. It is bedecked " +
        "with climbing roses and marks the entrance to the garden. " +
        "The roses are the best you've ever seen. They are marvel " +
        "of beauty and hint to what is beyond the trellis. An " +
        "ornamental gate is here. It is simple yet elegant in " +
        "construction. A walkway begins here and enters the garden. " +
        "Encirling the garden is a sculptured hedge.\n\n");
 
   add_item(({"hedge", "hedges"}), 
        "The hedge is scultpured in the form of green pillars. " +
        "Each pillar stands about 10 feet tall.\n");
   add_item("gate", 
        "The gate is about 3 feet tall with a circular top. It is " +
        "made of gold filigree.\n");
   add_item(({"walkway", "ground"}),
        "The walkway is made of flagstones. Growing between the " +
        "flagstones is thyme. The plant gives exhudes a sweet " +
        "fragrance as you walk through the garden.\n");
    add_item("trellis",
        "It is is sturdy, and arches over your head. Red roses " +
        "climb up and over it, filling the air with sweet " +
        "perfume.\n");
 
   gate = clone_object( TOWNSHIP_DIR + "doors/gate_gar_in");
   gate->move(this_object());
//   reset_room();
 

    add_exit(TOWNSHIP_DIR + "rd27", "north");
 
}
