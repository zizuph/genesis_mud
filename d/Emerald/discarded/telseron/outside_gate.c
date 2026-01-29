inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    object gate;
 
    set_short("Outside township");
    set_long( "You are standing just outside the gate leading into "+
             "a small township. To the north you can see a small forest, and "+
             "inside the township you can make out a castle.\n" );
 
    add_item("forest", "You can't see much of the forest from here.\n");
    add_item( ({ "town", "township" }), "It's a rather small township, protected "+
             "by a castle.\n");
    add_item("castle", "From here it looks like quite a grand castle.\n");
 
    add_exit(TOWNSHIP_DIR + "forest_edge", "northwest");
 
    gate = clone_object(TOWNSHIP_DIR + "doors/gate_a");
    gate->move(this_object());
}
