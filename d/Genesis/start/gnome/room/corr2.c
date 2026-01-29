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
    set_short("Gnomehome main corridor");
    set_long(BS(" The main corridor curves from southeast to southwest " +
		"here. To the north, the corridor opens up to the downwards " +
		"spiraling slope that will take you to the lower levels of " +
		"Gnomehome.\n"));
    add_item("slope",
	     BS(" There are no stairs cut out in the sloping tunnel. For " +
		"some reason Gnomes prefer to drag their feet along dusty " +
		"slopes to tapping down stairs.\n"));

    add_exit(ROOM_DIR + "slope1", "north", 0);
    add_exit(ROOM_DIR + "corr1",  "southeast", 0);
    add_exit(ROOM_DIR + "corr3",  "southwest", 0);
    guard_settings = ({ 2 }) + DEFAULT_GUARD_SETTINGS;
    reset_room();
    set_noshow_obvious(1);
}
