#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit SEWER_IN;

object rat, rat2;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(FIRST + "s22", "north");
    add_exit(FIRST + "middle", "south");
    
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
