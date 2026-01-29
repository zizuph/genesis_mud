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
    
    /* Members of the guild are allowed east and their teammates */
    for (x = T_LEADER ; x <= T_INITIATE ; x++)
        add_allowed(x, T_TEAMMEMBER, ({ "up" }));
    /* Pilgrims are allowed east but not their teammates */
    add_allowed(T_PILGRIM, 0, ({ "up" }));
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

     set_short("On a winding stairway");
    set_long("You are standing on the first dungeon level landing on a " +
        "spiraling stone stairway in the Temple of Darkness. A dark " +
        "narrow corridor leads off west and south, and the stairway " +
        "leads both up and down.\n");

    add_exit( DUNGONE  + "corr7.c", "south" );
    add_exit( DUNGONE  + "corr6.c", "west" );
    add_exit( TEMPLE + "stair1.c", "up", "@@check_guards" );
    add_exit( DUNGTWO  + "guard.c", "down" );

    set_up_allowed();
    reset_temple_room();
}
