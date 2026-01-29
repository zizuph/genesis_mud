#include "../gnome.h"

#pragma save_binary

inherit  LIB;
inherit  "/std/room";

void
create_room() {
    set_short("On top of the Gnomehome slope");
    set_long(BS(" You are on the very top of the sloping tunnel that " +
		"connects the levels of Gnomehome. To the south lies the " +
		"main corridor of the first level. The air up here is fresh " +
		"and cool. Downwards lies heat and worn air.\n"));
    add_exit(ROOM_DIR + "corr2", "south", 0);
    add_exit(ROOM_DIR + "slope2", "down", 0);
    set_noshow_obvious(1);
}