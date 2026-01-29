/*
 *	/d/Gondor/ithilien/osgiliath/underbridge.c
 *
 *	Original version by Elessar
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	General revision.
 *  June 1, 2004 Serif: Updated to add drinking from river.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    reset_room();

static object *Ranger = allocate(2);

public int	log_actions(string arg);

public void
create_gondor()
{
    set_short("under the bridge in Eastern Osgiliath");
    set_long(BSN("You are standing on a small platform under the ruins " +
        "of the bridge in East Osgiliath. The platform is wet, as " +
        "occasional splashes from the river Anduin spray over it. The " +
        "water surface is only a foot lower than the stone constructed " +
        "platform. A rickety ladder leads up to the bridge from here."));
    add_item("ladder", BSN("The wooden ladder is rickety and old, but " +
        "will probably hold your weight if you climb it."));
    add_item("bridge", BSN("Just a few feet above your head is the " +
        "ruined bridge, which once connected the east part of " +
        "Osgiliath with the central part, which you can see further " +
        "out in the river."));
    add_item(({"river", "anduin", "river anduin", "Anduin", "water"}),
        BSN("The great river Anduin flows by right next to you, its " +
        "surface rippled by a calm breeze. Out in the river to the west " +
        "is the central part of Osgiliath, with the ruined Royal Palace " +
        "and the Hall of Stars."));
    add_item(({"platform", "small platform"}), BSN("The platform is wet, " + 
        "as occasional splashes from the river Anduin spray over it."));

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_drink_from( ({ "river", "anduin", "river anduin", "Anduin",
        "River Anduin", "water" }) );

    add_exit(ITH_DIR + "osgiliath/eosgbridge", "up", 0, 2);

    (OSG_DIR + "underbridge")->load_me();

    reset_room();
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

public void
reset_room()
{
    int     flag;
    flag = clone_npcs(Ranger, NPC_DIR + "random_ranger", -1.0);

    if (flag)
	Ranger->set_company("Ithilien");

/* were getting bug reports on this -- someone left debugging in ??
    TI->catch_tell("Flag = " + flag + "\n");
 * commented it out for now -- gnadnar */
}

public int
climb_up(string str)
{
    if (!strlen(str) || ((str != "up") && (str != "ladder")))
    {
	NFN("Climb what?");
	return 0;
    }
    set_dircmd(str);
    write("You climb up the rickety ladder.\n");
    TP->move_living("up the rickety ladder", ITH_DIR + "osgiliath/eosgbridge");
    return 1;
}

public string
query_river_file()
{
    return (ANDUIN_DIR + "suebridge");
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
