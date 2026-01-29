inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../../../ctower.h"
#include <stdproperties.h> 

void
create_ctower_room()
{
    set_short("Mud room");
   
    set_long( "This room is a clash between the elements of "+
	"earth and water, producing a thick viscous mud.\n" );
   
    add_item(({"floor", "mud"}),  "The mud is churning "+
	"slowly and seems to change consistency constantly.\n" );
   
    add_item(({"wall", "ceiling"}),  "The walls are "+
	"made of a dark crystal that seems to absorb the light.\n" );
   
    add_exit("all", "south");
    add_exit("water", "east");
    add_exit("earth", "west");
}
