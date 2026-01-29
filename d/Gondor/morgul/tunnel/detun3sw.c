#pragma strict_types

inherit "/d/Gondor/morgul/tunnel/std_tunnel";

#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

public void    reset_room();
static object *wguard = allocate(2 + random(2));

void
create_room()
{
    add_exit(MORGUL_DIR + "tunnel/mmtun2", "northeast", 0, 5);
    add_exit(MORGUL_DIR + "tunnel/detun3sw2", "down", 0, 3);

    make_the_room("The tunnel continues to descend steeply towards " +
        "the southwest, leading upwards to the northeast. It looks " +
        "like some orcs rested here, the floor " +
        "is covered by filth and garbage. ");

    remove_item("floor");
    add_item(({"floor", "ground"}), BSN(
        "The floor is covered with filth and garbage lying around between " +
        "rocks of all sizes. "));
    add_item(({"filth", "garbage"}), BSN(
        "You do not want to know what exactly is lying on the ground here. " +
        "It looks like some decayed morsels of food, excrements, pieces of " +
        "clothes, broken wood, some ashes and bones. "));
    add_item(({"food", "morsels", "excrements", "clothes", "wood", "ashes", "bones"}), BSN(
        "It's almost beyond recognition and of no interest to you. "));

    reset_room();

    (MORGUL_DIR + "tunnel/detun3sw2")->load_me();
}

void
clone_orc()
{
    int     rs = random(31),
            s = sizeof(wguard),
            n;

    for (n = 0; n < s; n++)
    {
        if (!objectp(wguard[n]))
        {
            wguard[n] = clone_object(MORGUL_DIR + "npc/ithil_soldier");
            wguard[n]->set_restrain_path(MORGUL_DIR + "tunnel/");
            wguard[n]->set_random_move(25);
            wguard[n]->default_config_npc(30 + rs);
            wguard[n]->set_base_stat(SS_INT, 25 + random(15));
            wguard[n]->set_base_stat(SS_WIS, 25 + random(15));
            wguard[n]->set_base_stat(SS_DIS, 35 + rs);
            wguard[n]->arm_me();
            wguard[n]->move_living("down", TO);
            set_alarm(1.0, 0.0, clone_orc);
            break;
        }
    }
}

void
reset_room()
{
    set_alarm(0.0, 0.0, clone_orc);
}
