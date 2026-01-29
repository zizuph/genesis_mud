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
        add_allowed(x, T_TEAMLEADER, ({ "southwest" }));
    for (x = T_GENERAL ; x <= T_RECRUIT ; x++)
        add_allowed(x, T_TEAMLEADER, ({ "southwest" }), "red");
    add_allowed(T_WIZARD, 0, ({ "southwest" }));
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
    set_short("Red Dragonarmy antechamber");
    set_long("This is the Antechamber for the Red Dragonarmy. " +
        "The floor is bare but the walls are decorated with standards " +
        "and weapons of different kinds. \n");

    add_item(({"wall", "walls"}), "They are decorated with standards " +
        "and weapons of different kinds.\n");
    add_item(({"standard", "standard of the Red Dragonarmy",
        "standards", "standard of the red dragonarmy"}),  
        "The standard is mounted on a fauchard which hangs " +      
        "horizontally above the entrance. It shows a sitting red " +
        "dragon with a scorched body clutched in its talons. " +
        "It is beautifully embroidered with silk on a cream white " +
        "velvet background. The edges are trimmed with red silk " +
        "fringes.\n");

    
    add_exit( TEMPLE + "hall8.c", "north" );
    add_exit( TEMPLE + "hall9.c", "northeast" );
    add_exit( TEMPLE + "hall7.c", "northwest" );
    add_exit( RED + "corr2.c", "southwest", "@@check_guards" );

    set_up_allowed();
    reset_temple_room();
}
