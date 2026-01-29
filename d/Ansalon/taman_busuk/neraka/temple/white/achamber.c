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
        add_allowed(x, T_TEAMLEADER, ({ "northwest" }));
    for (x = T_GENERAL ; x <= T_RECRUIT ; x++)
        add_allowed(x, T_TEAMLEADER, ({ "northwest" }), "white");
    add_allowed(T_WIZARD, 0, ({ "northwest" }));
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
    set_short("White Dragonarmy antechamber");
    set_long("This is the Antechamber for the White Dragonarmy. " +
        "The floor is bare but the walls are decorated with standards " +
        "and weapons of different kinds. \n");

    add_item(({"wall", "walls"}), "They are decorated with standards " +
        "and weapons of different kinds.\n");
    add_item(({"standard", "standard of the white dragonarmy",
        "standards", "standard of the White Dragonarmy"}),
        "The standard is mounted on a large halberd which hangs " +
        "horizontally above the entrance. It shows an ancient white " +
        "dragon in flight above three spiked maces. All embroidered " +
        "with white silk upon bright blue velvet. The edges are " +    
        "trimmed with silver fringes.\n");
    
    add_exit( TEMPLE + "hall2.c", "east" );
    add_exit( WHITE + "corr2.c", "northwest", "@@check_guards" );
    add_exit( TEMPLE + "hall5.c", "southeast" );

    set_up_allowed();
    reset_temple_room();
}
