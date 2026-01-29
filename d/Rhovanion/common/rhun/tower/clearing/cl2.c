
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("A large clearing");
set_long(break_string("This is a large clearing in Rhun.  The forest"
    +" in which it lies is vast and dark.  In the center of the clearing"
    +" is a tall tower, apparently inhabited by soldiers of some sort."
	+"\n",75));

AE(RHUN+"tower/clearing/cl10", "north", 0);
AE(RHUN+"tower/clearing/cl3", "west", 0);
AE(RHUN+"tower/clearing/cl1", "southwest", 0);

add_prop(ROOM_I_LIGHT,1);

add_item(({"edge", "trees", "tree"}), break_string("The trees of the"
    +" forest in which this clearing lies are tall, made of a"
    +" dark wood, with lush, thick leaves on their tops.\n", 75));
add_item("tower", break_string("The tower is built from large blocks"
    +" of a dark red stone, perhaps the color of rust.  It rises up"
    +" into the sky, above the treetops, though you would be unable"
    +" to see it from within the trees due to the heavy canopy of"
    +" leaves on their upper branches.  Within the tower, you can"
    +" see the movement of men, the Easterlings who inhabit this"
    +" area.\n", 75));

}

