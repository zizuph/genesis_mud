#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../lib/repair_dock.h"

#define WEAPONS ({ WEP_DIR + "knife", WEP_DIR + "stick" })
#define MIN_AWARE  20

void    reset_room();

int     rat_alarm,
        iplank;
object *rats;

void
create_warehouse()
{
}

nomask void
create_room()
{
    add_prop(ROOM_I_INSIDE,1);
 
    create_warehouse();

    if (item_id("crates"))
    {
        add_prop(OBJ_S_SEARCH_FUN, "search_crates");
        add_prop(OBJ_I_SEARCH_TIME, 0);
    }

    reset_room();
}

void
make_rats()
{
    int     i;

    for (i = 0; i < sizeof(rats); i++)
    {
        if (!objectp(rats[i]))
        {
            rats[i] = clone_object(NPC_DIR+"rat");
            rats[i]->set_restrain_path(PELAR_DIR + "docks");
            rats[i]->set_random_move(15);
            rats[i]->move_living("down", TO);
            if (!(rat_alarm && sizeof(get_alarm(rat_alarm))))
                rat_alarm = set_alarm(60.0 + 120.0 * rnd(), 0.0, make_rats);
            return;
        }
    }
}

void
reset_room()
{
    object weapon;

    make_rats();

    if (!present("_hidden_weapon",TO) && !random(3))
    {
        weapon = clone_object(ONE_OF_LIST(WEAPONS));
        weapon->add_name("_hidden_weapon");
        weapon->add_prop(OBJ_I_HIDE, 10 + random(10));
        weapon->move(TO);
    }

    if (!present("crowbar", TO))
    {
        weapon = clone_object(PELAR_DIR + "obj/crowbar");
        weapon->add_name("_hidden_weapon");
        weapon->add_prop(OBJ_I_HIDE, 10 + random(10));
        weapon->move(TO);
    }

    iplank = 0;
}


public string
search_crates(object tp, string str)
{
    object  plank;

    if (!strlen(str) || ((str != "crate") && (str != "crates")))
        return 0;

    if (iplank)
        return 0;

    if (!(tp->query_prop(PELARGIR_I_REPAIR_DOCK) && REPAIR_TASK) ||
    ((tp->query_skill(SS_AWARENESS) + random(11)) < MIN_AWARE))
        return 0;

    iplank = 1;
    plank = clone_object(PELAR_DIR + "obj/plank");
    plank->set_length(136 + random(30));
    plank->move(TO);
    SET_STAGE(tp, REPAIR_PLANK);

    return "Among the crates, you find " + LANG_ADDART(plank->short())
        + ".\n";
}
