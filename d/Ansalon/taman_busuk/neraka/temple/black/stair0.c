#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/common/defs.h"

inherit TEMPLE + "std_stair.c";
inherit TEMPLE + "lib/blocking";

object *gGuards = allocate(3);

void
set_up_allowed()
{
    int x;
    
    for (x = T_LEADER ; x <= T_HIGH_PRIEST ; x++)
        add_allowed(x, T_TEAMLEADER, ({ "up" }));
    for (x = T_GENERAL ; x <= T_RECRUIT ; x++)
        add_allowed(x, T_TEAMLEADER, ({ "up" }), "black");
    add_allowed(T_WIZARD, 0, ({ "up" }));
}

void
reset_temple_room()
{
    int x, size;
    
    setuid();
    seteuid(getuid());
    
    for (x = 0, size = sizeof(gGuards) ; x < size ; x++)
    {
        if (!objectp(gGuards[x]))
        {
            gGuards[x] = clone_object(NNPC + "templeguard");
            gGuards[x]->arm_me();
            gGuards[x]->move(TO);
        }
    }
    
    if (sizeof(gGuards))
    {
        gGuards[0]->team_join(gGuards[1]);
        gGuards[0]->team_join(gGuards[2]);
    }
    
    set_guards(gGuards);
}

void
create_temple_room()
{
    ::create_temple_room();

     set_short("Bottom of a winding stairway");
    set_long("You are standing beneath ground level of the temple. " +
        "A spiraling stairway leads up and narrow corridor leads off " +
        "both northwest and west.\n");

    add_exit( DUNGONE + "corr10.c", "northwest" );
    add_exit( BLUE + "corr7.c", "west" );
    add_exit( BLACK + "stair1.c", "up", "@@check_guards" );

    set_up_allowed();
    reset_temple_room();
}
