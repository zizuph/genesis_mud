/*
 * /d/Gondor/ithilien/osgiliath/boatplace.c
 *
 * Original version by Elessar
 *
 * Modification log:
 *  3-Dec-1996, Olorin: General revision.
 *  June 1, 2004 Serif: Updated to add drinking from river.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/d/Gondor/ithilien/forest/room_tells";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    reset_room();
public string  exa_prints();
public string  exa_ground();
public string  long_func();

static object  Orc;

public void
create_gondor()
{
    set_short("on the eastern riverbank of the mighty Anduin river");
    set_long(long_func);
    add_item(({"bushes","shrubs"}),
	     "There are bushes and shrubs growing all around here.\n");
    add_item(({"ground","marks"}), exa_ground);
    add_item(({"footprints", "footsteps", "prints"}), exa_prints);
    add_exit(ITH_DIR + "osgiliath/bank2", "north", 0, 2);
    add_exit(ITH_DIR + "forest/edge1",    "east",  0, 2);
    BEACH;
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_drink_from( ({ "river", "anduin", "river anduin", "Anduin",
        "River Anduin", "water" }) );

    reset_room();

    add_orc_camp_tells();
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
init()
{
    ::init();
    init_drink();
}

public string
long_func()
{
    string longstr = "You are standing on the eastern riverbank of the "
      + "River Anduin. The river flows quietly past on its way south to "
      + "the sea. Looking across the river, you see nothing but flat, "
      + "grassy fields.";

    if (!objectp(present("boat", TO)))
        longstr += " There are some marks in the muddy ground.";
    else
        longstr += " There is a small wooden rowing boat here.";
    return longstr;
}

public void
reset_room()
{
    object  oars;

    if (!objectp(Orc))
    {
        Orc = clone_npc(Orc, NPC_DIR + "reorc");
        Orc->add_name("_stopping_npc");
    }
    if (!objectp(present("oars",TO)))
    {
        oars = clone_object(OBJ_DIR + "oars");
        oars->add_prop(OBJ_I_HIDE,10 + random(15));
        oars->move(TO);
    }
}

public string
exa_ground()
{
    string  desc = "The ground is muddy, with a few sparse grass halms growing here.";

    if (!present("boat",TO))
        desc += " You can see some marks in the mud. It looks as if "
          + "someone has pulled a small boat into the Anduin here. "
          + "There are some footsteps, too, but you cannot make out more.";
    else
        desc += " From the small boat, some tracks go to the Anduin, "
          + "it looks like someone recently pulled the boat from the river "
          + "up the shore. ";
    return desc + "\n";
}

public string
exa_prints()
{
    if (!present("boat", TO))
        return "You cannot make out any details since there are " +
            "too many footprints in the muddy ground and they have " +
            "been confused by the marks from the boat.\n";
    else
        return "There are some footprints going from the boat " +
            "to the Anduin as if someone recently pulled up the " +
            "boat from the river.\n";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}
