inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

create_room()
{
	set_short("Corridor in the home.\n");
	set_long("This corridor is cut from the bedrock itself. You can see"
		+" veins of differing material crossing the polished surface of the"
		+" walls. A foggy luminescence hangs in the air, giving off enough"
		+" light to see by.\nTo the north you can see a gathering room of"
		+" sorts, and to the southwest you see the entrance hall.\n");
	
	add_item(({"vein", "veins"}), "You cannot tell what the material in the"
		+" crossing veins is.\n");
	add_item("luminescence", "It swirls and moves around you, casting no shadows"
		+" and adding a pressing silence to this corridor.\n");
	add_item(({"wall", "walls", "surface"}), "The walls are polished to the point"
		+" where they would be slippery if you stood on them.\n");
	add_item("gathering hall", "It seems quite large with a"
		+" comfortable atmosphere. You can hear the sound of running"
		+" water from it.\n");
	add_item("entrance hall", "You can make out the imposing figure of Melkor"
		+" in the midst of it.\n");
	add_item("hall", "There are two halls visible from here, the entrance hall"
		+" and the gathering hall.\n");
	
	add_exit(CULT_DIR + "t_entr", "southwest", 0);
	add_exit(CULT_DIR + "t_gather", "north", 0);
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
}