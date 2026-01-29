#include "../gnome.h"

#pragma save_binary

inherit  LIB;
inherit  "/std/room";

void
reset_room() {
    reset_guards();
}

void
create_room() {
    set_short("The middle part of the merchant's area");
    set_long(BS(" Here, the marketplace is a little quieter. To the west " +
		"the smell of edibles is stronger and south lies the square " +
		"where the Elder Gnomes gather monthly to discuss the " +
		"administration of Gnomehome. East the markets continue.\n"));
    add_item("square",
	     "You don't see much from here except from a large statue.\n");
    add_exit(ROOM_DIR + "square", "south", 0);
    add_exit(ROOM_DIR + "merch1", "east", 0);
    add_exit(ROOM_DIR + "merch3", "west", 0);

    set_noshow_obvious(1);

    guard_settings = ({ 3 }) + DEFAULT_GUARD_SETTINGS;
    reset_room();
}