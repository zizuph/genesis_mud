
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void
enter_inv(object obj, object from)
{
  ::enter_inv(obj,from);
  if((obj->query_prop("_rhun_tour") == 2) &&
     (!obj->query_prop("_i_have_found_the_tower_")))
    {
      obj->add_prop("_i_have_found_the_tower_", 1);
    }
}

create_room()
{
set_short("A large clearing");
set_long("You have entered a large clearing in the"
    +" forest northeast of the Sea of Rhun.  Tall, dark trees topped"
    +" with thick green leaves ring its outer edge.  In the clearing's"
    +" center, to the south, stands a tall and menacingly-dark tower."
	+" You can see Easterlings moving around inside.\n");

add_exit(RHUN_DIR+"forest/m13", "north", 0);
add_exit(RHUN_DIR+"tower/clearing/cl9", "southeast", 0);
add_exit(RHUN_DIR+"tower/clearing/cl6", "southwest", 0);
add_exit(RHUN_DIR+"tower/clearing/cl8", "south", 0);

add_prop(ROOM_I_LIGHT,1);

add_item(({"edge", "trees", "tree"}), "The trees of the"
    +" forest in which this clearing lies are tall, made of a"
    +" dark wood, with lush, thick leaves on their tops.\n");
add_item("tower", "The tower is built from large blocks"
    +" of a dark red stone, perhaps the color of rust.  It rises up"
    +" into the sky, above the treetops, though you would be unable"
    +" to see it from within the trees due to the heavy canopy of"
    +" leaves on their upper branches.  Within the tower, you can"
    +" see the movement of men, the Easterlings who inhabit this"
    +" area.\n");

}


