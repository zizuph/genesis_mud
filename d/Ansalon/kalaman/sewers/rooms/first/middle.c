#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit SEWER_IN;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(FIRST + "s23", "north");
    add_exit(FIRST + "s8", "south");
    add_exit(FIRST + "s9", "east");
    add_exit(FIRST + "s7", "west");
   
    add_exit(SECOND + "s9", "down");
    
    
    set_short("Center of the sewers of Kalaman");
    set_long("You are in the tunnels of the sewers of Kalaman. Surprisingly, the tunnels are lighted through several grates. Here you see the water streaming down into a large hole in the ground. Occasionally you can hear the scurrying sounds of rats nearby.\n");

    add_item(({"hole"}), break_string("You can see the water drain through the large hole in the center of the sewer. You wonder where this hole leads.\n", 70));
}
