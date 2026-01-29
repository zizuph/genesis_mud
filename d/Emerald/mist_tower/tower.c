inherit "/d/Emerald/std/room";

#include "defs.h"
#include "/d/Emerald/common/guild/vamp/guild.h"
#include <stdproperties.h>
#include <macros.h>

public void
create_tower_room()
{
}

public nomask void
create_emerald_room()
{
    set_short("Inside a dark tower");
    set_em_long("It's a tower!\n");

    add_prop(ROOM_I_LIGHT, -10);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop("_room_i_free_vamp_dvis", ABS(query_prop(ROOM_I_LIGHT)) + 1);

    add_item(({ "wall", "walls", "dark wall", "dark walls", "tower wall",
                "tower walls", "featureless wall", "featureless walls", 
                "inside wall", "inside walls", "stone wall", "stone walls" }),
        "The inside tower wall forms a plain, smooth circle around the " +
        "room.  Its dark, perfect surface nearly gives the appearance of " +
        "empty space.\n");

    add_item(({ "ceiling", "dark ceiling", "tower ceiling",
                "featureless ceiling", "stone ceiling"}),
        "Like the surrounding wall, the dark, stone ceiling appears to be " +
        "completely flat and unblemished, giving it an almost unreal aspect, " +
        "as if one could reach through it into dark, empty space.\n");

    add_item(({ "floor", "dark floor", "tower floor", "featureless floor",
                "stone floor", "ground", }),
        "Like the surrounding wall, the dark, stone floor appears to be " +
        "perfectly smooth and unblemished, giving the strange impression " +
        "of endless, void depth.\n");

    create_tower_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (IS_MEMBER(ob))
    {
        ob->stop_thirst();
    }
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (IS_MEMBER(ob))
    {
        ob->start_thirst();
    }
}

public int
query_no_snoop()
{
    return 1;
}

public int
query_prevent_snoop()
{
    return 1;
}
