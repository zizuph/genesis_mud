inherit "/d/Gondor/common/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define N_GUARDS	5

void    reset_room();

object *guards = allocate(N_GUARDS);

void
create_room()
{
    set_short("in a guard room at the north gate of Pelargir");
    set_long(BSN("This is the room where the guards on duty at "
      + "the north gate of Pelargir spend their time. There are "
      + "a few beds in a corner, and on the walls there are "
      + "fixtures to hold weapons and armour."));

    add_exit(PELAR_DIR + "street/n_gate_in", "east", 0, 1);
    add_prop(ROOM_I_INSIDE,1);
    reset_room();
}

void
clone_guard()
{
    int     n = 0;

    while (n < sizeof(guards))
    {
        if (!objectp(guards[n]))
        {
            if (!n)
                guards[n] = clone_object(PELAR_DIR + "npc/pelargir_officer");
            else
            {
                guards[n] = clone_object(PELAR_DIR + "npc/pelargir_soldier");
                guards[0]->team_join(guards[n]);
            }
            guards[n]->arm_me();
            guards[n]->move_living("down", TO);
            set_alarm(1.0, 0.0, clone_guard);
            return;
        }
        n++;
    }
}

void
reset_room()
{
    set_alarm(1.0, 0.0, clone_guard);
}

object *query_guards() { return guards; }

