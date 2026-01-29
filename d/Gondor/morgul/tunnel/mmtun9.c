#pragma strict_types

inherit "/d/Gondor/morgul/tunnel/std_tunnel";
inherit "/d/Gondor/morgul/feeling.c";

#include <macros.h>
#include <stdproperties.h>

#include "tunnel_door.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

public void    reset_room();

static object *wguard = allocate(2 + random(2));

void
create_room()
{
    add_exit(MORGUL_DIR + "city/tunnels/base_ne1", "up", "@@check_entry@@", 4);
    add_exit(MORGUL_DIR + "tunnel/mmtun8", "down", 0, 4);

    make_the_room("You must be far below the surface here. But the tunnel " +
        "still continues to descend steeply towards the southwest, " +
        "while it is leading upwards to the northeast. ");

    reset_room();
}

void reward_quest(object player)
{
    int    reward;

    write("\nYou feel more experienced!\n\n");

    seteuid(getuid());
    player->set_bit(MORGUL_GROUP,MORGUL_ENTRY_BIT);
    reward = MIN(player->query_exp(), MORGUL_ENTRY_QUEST_EXP);
    player->add_exp_quest(reward);
    LOG_QUEST(player, reward, "MORGUL ENTRY");
}

int check_entry()
{
    int     prop;
    object stopper;
    if (stopper = TP->query_attack())
    {
        write(CAP(LANG_ADDART(stopper->query_nonmet_name())) +
            " stops you from going there!\n");
        return 1;
    }

    if ((stopper = present("_morgul_monster",TO)))
    {
        // let friends pass if they already solved the quest
        if (TP->test_bit("Gondor",MORGUL_GROUP,MORGUL_ENTRY_BIT)
            && (query_friend_or_foe(TP) == -1))
            return 0;
        if (CAN_SEE_IN_ROOM(stopper) && CAN_SEE(stopper, TP))
        {
            write(CAP(LANG_ADDART(stopper->query_nonmet_name())) +
                " stops you from going there!\n");
            stopper->init_attack();
            return 1;
        }
    }

    if (!(prop = TP->query_prop(MORGUL_ENTRY_HATCH)) ||
        (TP->test_bit("Gondor",MORGUL_GROUP,MORGUL_ENTRY_BIT)))
        return 0;
    write("\nYou managed to enter Minas Morgul through this secret tunnel!\n");
    TP->remove_prop(MORGUL_ENTRY_HATCH);
    if (prop == 3)
        reward_quest(TP);
    else
        write("\n" + BSN("Probably you would feel more satisfied if you hadn't relied "+
            "so much on help from others.\n"));
    return 0;
}

void
clone_orc()
{
    int     rs = random(30),
            i,
            s = sizeof(wguard);

    for (i = 0; i < s; i++)
    {
        if (!objectp(wguard[i]))
        {
            wguard[i] = clone_object(MORGUL_DIR + "npc/ithil_soldier");
            wguard[i]->default_config_npc(30 + rs);
            wguard[i]->arm_me();
            wguard[i]->move_living("down", TO);
            set_alarm(1.0, 0.0, clone_orc);
            break;
        }
    }
}

public void
reset_room()
{
    set_alarm(0.0, 0.0, clone_orc);
}
