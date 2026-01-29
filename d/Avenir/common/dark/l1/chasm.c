/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public int
jump(string str)
{
    if (str != "chasm")
	return 0;

    write("A suicide attempt at best.\n");
    return 1;
}

public void
init(void)
{
    ::init();
    add_action(jump, "jump");
}

public void
create_room(void)
{
    set_short("Chasm");
    set_long("An abyssal chasm reaches out across the cavern, like " +
	"the mouth of some great demon. A wind rises up from its depths, " +
	"upon which rides the smell of death. On the north side of the " +
	"chasm is a tall towered fort, from which rays of light flicker " +
	"deep into the chasm.\n");

    add_item("walls", "Worn smooth, but not natural tunnels.\n");
    add_item("fungi", "Foul smelling fungus that decays all matter.\n");
    add_item("moss", "Its is a foul blackish green moss.\n");
    add_item("water", "Fetid and contaminated with dirt and minerals.\n");
    add_item(({ "fort", "outpost", "keep"}),
	"It is a small fortress made of deep black stone. It looks to be "+
	"heavily guarded. Lights from within it shine out across the chasm.\n");
    add_item(({"chasm", "pit"}),
	"This abyssal chasm must be bottomless or else is the entry to "+
	"the netherworld. Shadows seems to dance within it.\n");

    IN; LIGHT;

    add_exit(L1 + "n5", "south");
    add_exit(OUTPOST + "chasm_south", "east");
}
