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
    set_long(BS("This is the end of the main corridor running through " +
		"the top level of Gnomehome. To the northeast it continues " +
		"and to the southeast you can enter the merchantry area.\n"));

    add_exit(ROOM_DIR + "corr2",  "northeast", 0);
    add_exit(ROOM_DIR + "merch3", "southeast", 0);

    guard_settings = ({ 2 }) + DEFAULT_GUARD_SETTINGS;
    reset_room();
    set_noshow_obvious(1);
}
