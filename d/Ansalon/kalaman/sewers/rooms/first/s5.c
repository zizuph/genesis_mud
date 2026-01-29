#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit SEWER_IN;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(FIRST + "s4", "southwest");
    add_exit(FIRST + "s6", "southeast");
    add_exit(FIRST + "s3", "northwest");
    add_exit(FIRST + "s21", "northeast");
    
    add_exit(SECOND + "s26", "down");
    
    set_long("You are in the tunnels of the sewers of Kalaman. Surprisingly, the tunnels are lighted through several grates. Here you see the water streaming down into a large hole in the ground. Occasionally you can hear the scurrying sounds of rats nearby.\n");

    add_item(({"hole"}), break_string("You can see the water drain through the large hole in the center of the sewer. You wonder where this hole leads.\n", 70));

}
