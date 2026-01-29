/*
 *  /d/Gondor/guilds/rangers/ithilien/tunnel/osg_cellar.c
 *
 *  A secret tunnel in Ithilien hideout
 *
 *  Coded by Tigerlily, March 25, 2004
 *
 *
 */
inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#include "../../rangers.h"
#include "../exit.c"

int push_trapdoor(string str);
string exa_ceiling();


void
create_gondor()
{
    set_short("a cellar beneath the ruins of Osgiliath");
    set_long("This is a dark cellar somewhere below the ruins " +
        "of Osgiliath.  An iron grate in the floor is open and " +
        "exposes the entrance to a tunnel leading down.\n");
    add_item(({"tunnel", "down"}), "The tunnel is dark. It looks " +
        "like the entrance to an ancient sewer.\n");
    add_item(({"walls"}), "Solid rock walls surround the cellar.\n");
    add_item(({"grate", "iron grate"}), "A rusty iron grate is open " +
        "and exposes a dark entrance to a tunnel below.\n");
    add_item("cellar", "The cellar might once have been a storeroom " +
        "for the house above; however, now it is empty.\n");
    add_item(({"tiles", "ceiling", "tile"}), &exa_ceiling());
    add_exit(RANGERS_ITH_TUNNEL + "tunnel14","down",&check_ranger());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_M_NO_SCRY, 1);
}
void
init()
{
    ::init();
    add_action(&push_trapdoor(), "push");
}

int
push_trapdoor(string str)
{
    object tp = this_player();

    if (!RANGERS_MEMBER(tp))
    {
        notify_fail("What?\n");
        return 0;
    }

    if (str != "trapdoor" && str != "tile" && str != "handle")
    {
        notify_fail("Push trapdoor?\n");
        return 0;
    }
    write("You push the tile that is actually a trapdoor, " +
        "and suddenly it opens.\nYou climb up.\n");
    tell_room(environment(tp), QCTNAME(tp) + " pushes " +
        "up a tile in the ceiling, and it suddenly swings open.\n", tp);
    tp->move_living("through the trapdoor", 
        RANGERS_ITH_TUNNEL + "ruins_wosg3", 1, 0);
    return 1;
}

string
exa_ceiling()
{
    if (RANGERS_MEMBER(TP))
    {
        return "The ceiling is made of tiles. You notice " +
            "that one of the has a handle that you can " +
            "push. It is a trapdoor!\n";
    }
//else
    return "The ceiling is made of large stone tiles.\n";
}

