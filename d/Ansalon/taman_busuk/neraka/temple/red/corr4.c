#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/common/defs.h"

inherit TEMPLE + "std_dung.c";

object *gPatrolteam = allocate(3);

void
reset_temple_room()
{
    int x, size = sizeof(gPatrolteam);
    
    setuid();
    seteuid(getuid());

    for (x = 0 ; x < size ; x++)
    {
        if (!objectp(gPatrolteam[x]))
        {
            if (x == (size - 1))
            {
                gPatrolteam[x] = clone_object(NNPC + "priest");
                gPatrolteam[x]->arm_me();
                gPatrolteam[x]->move(TO);
                gPatrolteam[x]->set_patrol_time(20);
                gPatrolteam[x]->set_patrol_path(({"se", "e", "e", "e",
                    "n", "ne", "ne", "e", "nw", "nw", "n", "ne", "n", "w",
                    "w", "w", "w", "w", "w", "w", "s", "sw", "se", "s",
                    "s", "s", "se"}));
                gPatrolteam[x]->set_patrol_loop();
                gPatrolteam[x]->start_patrol();
            }
            else
            {
                gPatrolteam[x] = clone_object(NNPC + "templeguard");
                gPatrolteam[x]->arm_me();
                gPatrolteam[x]->move(TO);
            }
        }
    }
}

void
create_temple_room()
{
    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which continues to the southeast and leads off to a stairway " +
        "to the northwest.\n");

    add_exit( RED + "stair0.c", "northwest" );
    add_exit( RED + "corr5.c", "southeast" );

    reset_temple_room();
    (DUNGONE + "corr6")->load_me();
}
