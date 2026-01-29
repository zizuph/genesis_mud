#pragma strict_types

#include "defs.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/pot/guild.h"

inherit TEMPLE + "std_temple.c";
inherit TEMPLE + "lib/blocking";

object *gGuards = allocate(3);

void
set_up_allowed()
{
    int x;
    
    /* Members of the guild are allowed east and their teammates */
    for (x = T_LEADER ; x <= T_INITIATE ; x++)
        add_allowed(x, T_TEAMMEMBER, ({ "east", "south" }));
    /* Pilgrims are allowed east but not their teammates */
    add_allowed(T_PILGRIM, 0, ({ "east" }));
    add_allowed(T_WIZARD, 0, ({ "east", "south" }));
}

void
reset_temple_room()
{
    int x, size, tmp;
    
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

     set_short("In a corridor in the temple");
    set_long("You are standing in a wide corridor which leads pilgrims " +
        "into the Temple of Darkness. It continues south to the Great " +
        "Hall of Audience and north leads out of the temple. The " +
        "corridor is wide and the ceiling is 20 feet high and vaulted. " +
        "The black walls are lined with torches and another corridor " +
        "branches off to the east.\n");

    add_item(({"city", "neraka"}),
        "It is impossible for you to see the city from here.\n");

    add_item(({"corridor", "corridors"}),
        "This part of the corridor is wide and seemingly straight, leading " +
        "towards the Great Hall of Audience. The corridor branching off " +
        "to the east is not quite as wide.\n");

    add_exit( TEMPLE +"corr2.c", "north" );
    add_exit( TEMPLE +"hall1.c", "south", "@@check_guards" );
    add_exit( TEMPLE +"corr4.c", "east", "@@check_guards" );

    set_up_allowed();
    reset_temple_room();
}
