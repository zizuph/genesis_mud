/*
 *      /d/Gondor/anorien/osgiliath/underbridge
 *      Updated June 1, 2004 to allow drinking from the river.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object *Ranger = allocate(2),
               Ferry;

public int	log_actions(string arg);

public void
create_gondor()
{
    set_short("under the bridge in Western Osgiliath");
    set_long(BSN(
        "You are standing on a small platform under the ruins of the "
      + "bridge in West Osgiliath. The platform is wet, as occasional "
      + "splashes from the river Anduin spray over it. The water "
      + "surface is only a foot lower than the stone constructed "
      + "platform. A rickety ladder leads up to the bridge from here."));
    add_item("ladder",BSN(
        "The wooden ladder is rickety and old, but will probably "
      + "hold your weight if you climb it."));
    add_item("bridge",BSN(
        "Just a few feet above your head is the ruined bridge, "
      + "which once connected the west part of Osgiliath with the "
      + "central part, which you can see further out in the river."));
    add_item(({"river","river anduin","anduin","anduin river"}), BSN(
        "The river Anduin spreads out for a great distance under the"
      + " bridge of Osgiliath as it runs past the stone platform"
      + " here. Its clear waters flow steadily, yet not more rapidly"
      + " than might be expected for such a great waterway."));
    add_item(({"surface", "water"}), BSN(
        "The surface of the water is even and clear near to the"
      + " platform, and grows ever more turgid as you gaze out"
      + " towards the river's center."));
    add_item(({"platform", "stone platform"}), BSN(
        "The stone platform juts out from the base of the"
      + " bridge of Osgiliath and forms a sturdy walkway along"
      + " the edge of the great river. A rickety ladder runs"
      + " up from one corner of the platform to the top of the"
      + " embankment."));
    add_exit(OSG_DIR + "wbridge1","up",0,4);
    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_drink_from( ({ "river", "anduin", "river anduin", "Anduin",
        "River Anduin", "water" }) );

    reset_room();
}

public void
reset_room()
{
    if (!objectp(Ferry))
    {
        Ferry = clone_object(OSG_DIR + "ferry/ferry");
        Ferry->move(TO);
        Ferry->start_ship();
    }
    clone_npcs(Ranger, NPC_DIR + "random_ranger", -1.0);
}

public int
climb_up(string str)
{
    if (!strlen(str) || ((str != "ladder") && (str != "up")))
    {
        NF("Climb what?\n");
        return 0;
    }
    write("You climb up the rickety ladder.\n");
    set_dircmd(str);
    TP->move_living("up the rickety ladder", OSG_DIR+"wbridge1");
    return 1;
}

public void
drink_message(string from)
{
    write("You reach down from the pier and scoop up some water from "
        + "the River Anduin, drinking it quickly before it trickles away.\n"
        + "It tastes cool and delicious, and you feel refreshed.\n");
    say(QCTNAME(TP) + " scoops some  water from the river and "
        + "drinks it.\n");
}

string
query_river_file()
{
    return (ANDUIN_DIR + "subridge");
}

public void
init()
{
    ::init();
    add_action(climb_up, "climb");
    init_drink();
}

public int
log_actions(string arg)
{
    if ( strlen(arg) )
	log_file("ferryman", QVB+" "+arg+"\n");
    else
	log_file("ferryman", QVB+"\n");
    return 0;
}

