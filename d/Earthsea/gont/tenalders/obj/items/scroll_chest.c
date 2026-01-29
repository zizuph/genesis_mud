#pragma strict_types

inherit "/std/container";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "defs.h"

private int scroll_in = 0;

public void
create_container()
{
    set_name("chest");
    set_adj(({"large", "cedar"}));
    set_short("@@open_shut");
    set_long("The chest, which is probably used as a " +
        "foot locker, is fashioned from old cedar which gives off " +
        "a pleasant scent. This is the only nice piece of " +
        "furniture in the room, as though it did not really belong " +
        "here. There is a brass lock on it, and it seems to " +
        "be bolted to the floor. "+ "@@open_long");
    add_item("lock", "The chest has a brass lock.\n");
    add_cmd_item("lock", "pick", "@@pick_lock");
    add_cmd_item("chest", "open", "@@open_chest");
    add_cmd_item("chest", "close", "@@close_chest");
    add_cmd_item("lock", "unlock", "@@unlock_chest");
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);
    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_WEIGHT, 1800);
    add_prop(OBJ_M_NO_GET, "The chest is bolted down.\n");
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
}

public int
pick_lock()
{
    object tp = this_player(), to = this_object();

    if(tp->query_skill(SS_OPEN_LOCK) > 18)
    {
        tp->add_prop(PLAYER_I_FOUND_PARCHMENT, 1);
        write("After fumbling a bit, you manage to pick the lock!\n");
        tell_room(to, QCTNAME(tp) + " fumbles with the lock on " +
            "the chest.\n", ({ tp }));
        tell_room(to, "You hear a soft click.\n");
        change_prop(CONT_I_LOCK, 0);
        return 1;
    }

    write("You don't have the necessary skill to pick " +
        "the lock.\n");
    return 1;
}

public int
open_chest()
{
    object to = this_object(), scroll;

    if(query_prop(CONT_I_LOCK))
    {
        write("The chest is locked.\n");
        return 1;
    }

    write("You open the chest.\n");
    change_prop(CONT_I_CLOSED, 0);

    if(!scroll_in)
    {
        scroll_in = 1;
        seteuid(getuid(to));
        scroll = clone_object("/d/Earthsea/gont/tenalders/obj/items/ea_scroll");
        scroll->move(to);
    }

    return 1;
}

public int
close_chest()
{
    if(query_prop(CONT_I_CLOSED))
    {
        write("The chest is already closed.\n");
        return 1;
    }

    change_prop(CONT_I_CLOSED, 1);
    write("You close the chest.\n");
    return 1;
}

public string
open_long()
{
    if(query_prop(CONT_I_CLOSED))
    {
        return "The chest is closed.\n";
    }

    return "The chest is open.\n";
}

public string
open_shut()
{
    if(!query_prop(CONT_I_CLOSED))
    {
        return "large cedar chest";
    }

    return "large cedar chest";
}

public int
unlock_chest()
{
    write("Unlock lock with what?\n");
    return 1;
}
