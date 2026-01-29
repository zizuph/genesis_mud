#include "../gnome.h"

#pragma save_binary

inherit  LIB;
inherit  "/std/room";

void
create_room() {
    set_short("On top of the ledge above the main hall");
    set_long(BS(" Before and below you lies the center of the Gnomehome " +
		"crafthalls. Deep, glowing red from the furnaces mix with " +
		"the dancing yellow flames of torches and fires. Magical " +
		"fires leap here and there where items are bestowed with " +
		"supernatural qualities. You are on top of a ledge that " +
		"runs alongside one of the walls, leading slowly but " +
		"steadily down, towards the floor. North, the corridor " +
		"starts spiralling upwards.\n"));

    add_item(({ "center", "hall" }),
	     BS(" The hall is extremely large, formed in a somewhat oval " +
		"shape with the far ends narrowing into tunnels that lead " +
		"even further into the earth.\n"));
    add_item(({ "furnace", "furnaces", "torches", "fires" }),
	     BS(" Many a weapon and armour has been forged in these halls, " +
		"in these fires, in these furnaces. Gnomes everywhere bend, " +
		"twist and shape the steel into shape.\n"));
    add_item("ledge",
	     BS(" The ledge runs downwards, clinging to the northeastern " +
		"wall as it provides the only connection to the upper " +
		"levels accessable by living things.\n"));

    add_exit(ROOM_DIR + "slope3", "north", 0);
    add_exit(ROOM_DIR + "mhall", "down", 0);
    set_noshow_obvious(1);
}