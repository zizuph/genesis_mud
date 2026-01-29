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
    set_short("The western part of the merchant's area");
    set_long(BS(" This is the most colourful part of the marketplace. The " +
		"air is rich with the smell of foods of all kinds; " +
		"bakeries, barbeques, candy stands surround you. There " +
		"are exits to the east, where the marketplace continues, " +
		"and to the northwest where you see the main corridor.\n"));

    add_item(({ "bakeries", "bakery", "barbeque", "barbeques", "stands" }),
	     BS(" Happy gnomes buy, sell, and eat food. The average gnome " +
		"may have a grumpy attitude and looks to match, but they " +
		"have a passion for food only rivalled by hobbits.\n"));
    add_exit(ROOM_DIR + "merch2", "east", 0);
    add_exit(ROOM_DIR + "corr3",  "northwest", 0);

    set_noshow_obvious(1);

    guard_settings = ({ 3 }) + DEFAULT_GUARD_SETTINGS;
    reset_room();
}