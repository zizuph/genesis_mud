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
        add_allowed(x, T_TEAMLEADER, ({ "east" }));
    for (x = T_GENERAL ; x <= T_RECRUIT ; x++)
        add_allowed(x, T_TEAMLEADER, ({ "east" }), "blue");
    add_allowed(T_WIZARD, 0, ({ "east" }));
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
    set_short("Blue Dragonarmy antechamber");
    set_long("This is the Antechamber for the Blue Dragonarmy. " +
        "The floor is bare but the walls are decorated with standards " +
        "and weapons of different kinds. \n");

    add_item(({"wall", "walls"}), "They are decorated with standards " +
        "and weapons of different kinds.\n");
    add_item(({"standard", "standard of the Blue Dragonarmy",
        "standards", "standard of the blue dragonarmy"}),
        "Two crossed two-handed swords hold up the standard of the " +
        "Blue Dragonarmy. It shows a blue dragon sitting with its " +
        "wings spread wide. Beneath the dragon are two crossed " +  
        "lightning bolts. The dragon is embroided with rich dark " +
        "blue silk and the bolts are of the finest silver. The " +
        "background is made of pale dark green velvet. The edges are " +
        "trimmed with blue silk fringes.\n");

    
    add_exit( TEMPLE + "hall9.c", "west" );
    add_exit( TEMPLE + "hall6.c", "northwest" );
    add_exit( BLUE + "corr3.c", "east", "@@check_guards" );

    set_up_allowed();
    reset_temple_room();
}
