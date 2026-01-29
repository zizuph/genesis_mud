/* This room should be _extremely_ well guarded. */

#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_guard.c";
inherit TEMPLE + "lib/blocking";

#define NUM 5

object *dracs = allocate(NUM);

void
set_up_allowed()
{
    int x;
    
    for (x = T_LEADER ; x <= T_HIGH_PRIEST ; x++)
        add_allowed(x, T_TEAMMEMBER, ({ "west" }));
    add_allowed(T_WIZARD, 0, ({ "west" }));
}

void
reset_temple_room()
{
    int x;
    
    setuid();
    seteuid(getuid());
    
    for (x = 0 ; x < NUM ; x++)
    {
        if (!objectp(dracs[x]))
        {
            switch (x)
            {
                case 0..1:
                    dracs[x] = clone_object(NNPC + "sivak");
                    break;
                case 2..3:
                    dracs[x] = clone_object(NNPC + "kapak");
                    break;
                default:
                    dracs[x] = clone_object(NNPC + "bozak");
                    break;
            }
    
            dracs[x]->set_act_time(19 + random(5));
            dracs[x]->set_chat_time(25 + random(5));
            dracs[x]->move(this_object());
        }
    }
    
    set_guards(dracs);
}

void
create_temple_room()
{
    object door;
    
    ::create_temple_room();

     set_short("West guardroom");
    set_long("You are standing in the middle of a large guardroom. " +
        "Along the walls stand weaponracks and in the centre of this " +
        "room is a large round table with chairs around it.\n");

    add_exit( DUNGTHREE + "spiral5.c", "north" );

    /* The call to check_guards is done in the door */
    door = clone_object( DOOR + "cavern1.c" );
    door->move(this_object());

    set_up_allowed();
    reset_temple_room();
}
