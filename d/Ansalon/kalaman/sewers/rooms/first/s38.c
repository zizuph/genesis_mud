#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit SEWER_IN;

object rat, rat2;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(FIRST + "s19", "west");
    add_exit(SECOND + "s1", "down");
    
    set_long("You are in the tunnels of the sewers of Kalaman. Surprisingly, the tunnels are lighted through several grates. Here you see the water streaming down into a large hole in the ground. Occasionally you can hear the scurrying sounds of rats nearby.\n");

    add_item(({"hole"}), break_string("You can see the water drain through the large hole in the center of the sewer. You wonder where this hole leads.\n", 70));
    
    reset_room();
}

void reset_sewer_room()
{
    if (!objectp(rat))
    {
        if(random(2))
        {
            rat = clone_object(MONSTERS + "rat");
            rat->move_living("xxx", TO);
        }
    }
    if(!objectp(rat2))
    {
        if(random(2))
        {
            rat2 = clone_object(MONSTERS + "rat");
            rat2->move_living("xxx", TO);
        }
    }
}


