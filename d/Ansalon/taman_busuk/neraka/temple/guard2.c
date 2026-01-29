
#pragma strict_types

#include "defs.h"
#include "/d/Ansalon/common/defs.h"

inherit TEMPLE + "std_guard.c";

object *gGuards = allocate(2);

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
        gGuards[0]->team_join(gGuards[1]);
}    

void
create_temple_room()
{
    ::create_temple_room();

     set_short("East guardroom");
    set_long("You are standing in the middle of a large guardroom. " +
        "Along the walls stand weaponracks and in the centre of this " +
        "room is a large round table with chairs around it.\n");

    add_exit( TEMPLE + "corr2.c", "west" );

    reset_temple_room();
}
