#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_base.c";
inherit TEMPLE + "lib/blocking";

object *gGuards = allocate(3);

void
set_up_allowed()
{
    int x;
    
    for (x = T_LEADER ; x <= T_HIGH_PRIEST ; x++)
        add_allowed(x, T_TEAMLEADER, ({ "west" }));
    for (x = T_GENERAL ; x <= T_RECRUIT ; x++)
        add_allowed(x, T_TEAMLEADER, ({ "west" }), "green");
    add_allowed(T_WIZARD, 0, ({ "west" }));
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
            gGuards[x]->move(this_object());
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
    set_short("Green Dragonarmy antechamber");
    set_long("This is the Antechamber for the Green Dragonarmy. " +
        "The floor is bare but the walls are decorated with standards " +
        "and weapons of different kinds. \n");

    add_item(({"wall", "walls"}), "They are decorated with standards " +
        "and weapons of different kinds.\n");
    add_item(({"standard", "standard of the Green Dragonarmy",
        "standards", "standard of the green dragonarmy"}),
        "The standard hangs from two spears pointing in opposite " +
        "directions. It shows the head of a green dragon in profile " +
        "set on a mustard yellow background. It is embroidered with " +
        "silk thread on velvet and the edges are trimmed with darker " +
        "yellow silk fringes.\n");


    add_exit( TEMPLE + "hall7.c", "east" );
    add_exit( GREEN + "corr2.c", "west", "@@check_guards" );
    add_exit( TEMPLE + "hall5.c", "northeast" );

    set_up_allowed();
    reset_temple_room();
}

