/*
 *
 * This is an alley behind the bladesmith forge in Port Macdunn.
 *
 * Khail - May 16/97
 */
#pragma strict_types

#include "room.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>

inherit "/d/Khalakhor/std/room";

int scraps;

public int *
query_local_coords()
{
    return ({7,8});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public void
reset_room()
{
    scraps = 0;
}

public void
create_khalakhor_room()
{
    set_short("narrow alley");
    set_long("   You are in a narrow, shadowed alley between two " +
        "windowless stone buildings. It doesn't seem very " +
        "heavily used, the ground is still lightly matted " +
        "grass. The only evidence of use is that the grass " +
        "is strewn with a few scraps of " +
        "rusted iron. To the north and south, the alley " +
        "emerges onto larger dirt roads.\n");

    add_item(({"sky"}),
        "Looking up, you see the sky is partially overcast, " +
        "with thick grey clouds drifting through an " +
        "otherwise blue sky.\n");
    add_item(({"clouds","thick clouds", "white clouds",
        "thick white clouds"}),
        "Thick clouds drift lazily across the sky high above " +
        "your head.\n");
    add_item(({"ground"}),
        "The ground of the alley is grass covered, slightly " +
        "matted but otherwise showing little indication of " +
        "traffic.\n");
    add_item(({"iron","scraps","rusted iron"}),
        "Small scraps of rusted iron lie here and there " +
        "in the grass, discarded by someone quite some " +
        "time ago and left forgotten.\n");
    add_item(({"buildings"}),
        "Both buildings look pretty much identical, with " +
        "little to see from here except their bare stone " +
        "walls.\n");
    add_item(({"walls","wall","building walls"}),
        "The walls of the buildings are unadorned, made " +
        "simply from large stones and mortared with clay.\n");
    add_item(({"stones","large stones"}),
        "The stones of building walls are large and grey, " +
        "and fairly well-dressed, probably hewn from a " +
        "granite quarry somewhere.\n");
    add_item(({"clay"}),
        "Thick grey clay has been tightly packed into the " +
        "crevices where the stones didn't quite fight in an " +
        "effort to make the walls more weather-resistant.\n");

    add_exit(ROOM + "road_7_7", "north");
    add_exit(ROOM + "road_7_9", "south");
}

public int
do_get(string what)
{
    object scrap;

    if (!what || !strlen(what))
        return 0;

    if (what != "scrap" &&
        what != "iron" &&
        what != "iron scrap" &&
        what != "scrap of iron")
        return 0;

    if (scraps >= 2)
    {
        write("You don't see any scraps of iron worth gathering " +
            "on the ground.\n");
        return 1;
    }

    scraps++;
    write("You poke about the various bits of scrap iron on " +
        "the ground until you find one worth taking, and " +
        "quickly gather it up.\n");
    say(QCTNAME(TP) + " pokes about the various bits of scrap " +
        "iron on the ground until " + HE_SHE(TP) +
        " finds one worth taking, and quickly gathers it up.\n");
    reset_euid();
    scrap = clone_object("/d/Khalakhor/common/obj/rust_iron_scrap");
    if (scrap->move(TP))
    {
        write("Unfortunately, you can't manage to hold onto " +
            "it and clumsily drop the iron again.\n");
        say("Unfortunately, " + QTNAME(TP) + " can't seem to " +
            "keep " + HIS_HER(TP) + " grasp on it and " +
            "clumsily drops it again.\n");
        scrap->move(TO);
    }
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_get, "get");
    add_action(do_get, "take");
}
