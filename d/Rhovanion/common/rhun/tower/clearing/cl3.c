
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("A large clearing");
set_long(break_string("You are standing in a large clearing.  Just"
    +" before you stands a tall tower of dark red stone, which you"
    +" may enter by heading north.  The clearing continues around to"
    +" the east or west, while an entrance back into the forest can"
    +" be seen south of here."
	+"\n",75));

AE(RHUN+"tower/clearing/cl2", "east", 0);
AE(RHUN+"tower/clearing/cl4", "west", 0);
AE(RHUN+"tower/clearing/cl1", "south", 0);
    add_exit(RHUN_DIR+"tower/inside/1g", "north", 0);

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

