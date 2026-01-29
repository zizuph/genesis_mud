#include "../gnome.h"

#pragma save_binary

inherit  LIB;
inherit  "/std/room";

object smith;

void
reset_room() {
    if (!smith) {
	smith = clone_object(OBJ_DIR + "smith");
	smith->move(this_object());
    }
    reset_guards();
}

void
create_room() {
    set_short("The eastern part of the merchants' area");
    set_long(BS(" You are in a very crowded and noisy area. People all " +
		"around you are engaged in trading - buying, selling, " +
		"haggling over prices. Little gnome kids run chase each " +
		"other back and forth and the air is filled with smells " +
		"of spices, food, and other merchandise. To the northeast " +
		"a passage lead to the main corridor. To your west, the " +
		"marketplace continues.\n"));
    add_item(({ "people", "kids" }),
	     BS(" You see mostly gnomes but here and there, people of " +
		"other races can be seen, as busy as the rest. One or two " +
		"return your curious glances.\n"));
    add_exit(ROOM_DIR + "merch2", "west", 0);
    add_exit(ROOM_DIR + "corr1",  "northeast", 0);
    add_exit(ROOM_DIR + "corr3",  "northwest", 0);

    set_noshow_obvious(1);

    guard_settings = ({ 3 }) + DEFAULT_GUARD_SETTINGS;
    reset_room();
}