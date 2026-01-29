inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  thief;

void
reset_room()
{
    thief = add_citizen(thief, PELAR_DIR + "npc/yngthief");
}

void
create_room()
{
    set_short("amid the vast docks of Pelargir");
    set_long(BSN("This dock appears to be one of the military berths "
      + "of Pelargir. On the end of the sturdy wharf is a pole bearing "
      + "the standard of Pelargir. There are several docks on either "
      + "side of this one, creating a busy port. South of the dock is "
      + "a large warehouse. The Anduin flows by to the east and to "
      + "the west spreads the city of Pelargir.")
      + "There is a military ship here.\n");
    add_item("standard", BSN("This large blue standard flaps loudly in "
      + "the wind off the river. At a glance you can see the three "
      + "ships and crown, proud symbols of Pelargir."));
    add_item(({"military ship","ship"}), BSN("This ship has been "
      + "obviously built with the sole purpose of winning battles. "
      + "With its size it could carry an army, yet it rides high "
      + "enough in the water to avoid some of the sandbars found in "
      + "the Anduin."));
    add_item(({"house", "warehouse", }), BSN(
        "A large warehouse, probably used by the Gondorian navy to "
      + "store arms and provisions for the fleet."));
    add_dockships();
    add_anduin("socks");
    add_exit(PELAR_DIR + "docks/dock5","north",0);
    add_exit(PELAR_DIR + "docks/dock7","southeast",0);
    add_exit(PELAR_DIR + "docks/warehouse6","south",0);
    add_exit(PELAR_DIR + "streets/market04", "west", 0);

    reset_room();
}

int
enter_ship(string str)
{
    string  vb = query_verb();

    NFN(CAP(vb) + " what?");
    if (vb == "enter")
    {
        if (!strlen(str) || str != "ship")
            return 0;
    }
    else
    {
        if (!strlen(str) && str != "ship")
            return 0;
    }

    set_dircmd("ship");
    TP->move_living("boarding the ship", PELAR_DIR + "docks/ship2");
    return 1;
}

void
init()
{
    ::init();

    add_action(enter_ship, "board");
    add_action(enter_ship, "enter");
}

