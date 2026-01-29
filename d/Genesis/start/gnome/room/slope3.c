#include "../gnome.h"

#pragma save_binary

inherit  LIB;
inherit  "/std/room";

void
create_room() {
    set_short("The lowest part of the Gnomehome slope");
    set_long(BS(" You are standing where the sloping spiral of the " +
		"Gnomehome climbing passage and the low levels of the " +
		"industry halls meet. The passage continues as a corridor " +
		"a little further south, where it opens up into huge " +
		"chambers lit in sparkling red and yellow from the fires.\n"));

    add_exit(ROOM_DIR + "ledge", "south", 0);
    add_exit(ROOM_DIR + "slope2", "up", 0);
    set_noshow_obvious(1);
}