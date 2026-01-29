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
        add_allowed(x, T_TEAMLEADER, ({ "east" }), "black");
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
    set_short("Black Dragonarmy antechamber");
    set_long("This is the Antechamber for the Black Dragonarmy. " +
        "The floor is bare but the walls are decorated with standards " +
        "and weapons of different kinds.\n");

    add_item(({"wall", "walls"}), "They are decorated with standards " +
        "and weapons of different kinds.\n");
    add_item(({"standard", "standard of the black dragonarmy",
        "standards", "standard of the Black Dragonarmy"}),
        "This standard shows the silhouette of a dragon in profile, " +
        "rearing up and clawing in the air. It is embroided with " +
        "thick silver thread on a deep-black velvet background. " +
        "The edges are trimmed with silver fringes and the standard " +
        "hangs from a large two-handed battleaxe.\n");
    
    add_exit( BLACK + "corr3.c", "east", "@@check_guards" );
    add_exit( TEMPLE + "hall4.c", "west" );
    add_exit( TEMPLE + "hall6.c", "southwest" );

    set_up_allowed();
    reset_temple_room();
}
