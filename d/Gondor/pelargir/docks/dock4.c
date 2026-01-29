inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/pelargir/city_items.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object *Grub = allocate(1);

void
create_gondor()
{
    set_short("amid the vast docks of Pelargir");
    set_long(BSN("This is a military dock. It has been swept, "
      + "polished, and the standard of Pelargir hangs from every post. "
      + "Of all the docks, this one is built with the thickest boards "
      + "and seems the most sturdy. To the west the rest of Pelargir "
      + "expands, while to the east the River Anduin dominates the "
      + "landscape. To the north and south you can visit other docks.")
      + "There is a large military ship here.\n");
    add_item(({"standard","standards"}), BSN("These standards flutter "
      + "in the river wind with a display of pride and elegance. "
      + "Close inspection reveals the three ships surmounted by a "
      + "silver crown, as is commonly known to be the herald of "
      + "Pelargir."));
    add_item(({"military ship","ship"}), BSN("The large ship has a "
      + "sleek design well suited to the river currents, yet its "
      + "size indicates it would be a strong force to reckon with "
      + "even on the open sea. This clean, well kept vessel is "
      + "definitely worthy of Pelargir's standard it bears on its "
      + "top mast."));

    add_dockships();
    add_anduin("docks");
    add_exit(PELAR_DIR + "docks/dock3","north",0);
    add_exit(PELAR_DIR + "docks/dock5","south",0);
    add_exit(PELAR_DIR + "streets/shipwright02", "west", 0);
    
    reset_room();

}

void
reset_room()
{
    clone_npcs(Grub, "/d/Gondor/pelargir/riverstead/npc/grub", -1.0);
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
    TP->move_living("boarding the ship", PELAR_DIR + "docks/ship1");
    return 1;
}

void
init()
{
    ::init();

    add_action(enter_ship, "board");
    add_action(enter_ship, "enter");
}

