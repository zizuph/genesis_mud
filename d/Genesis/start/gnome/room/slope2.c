#include "../gnome.h"

#pragma save_binary

inherit  LIB;
inherit  "/std/room";

void
create_room() {
    set_short("On the Gnomehome slope, second level");
    set_long(BS(" This is where the sloping passage that serves as a " +
		"staircase for the gnomes grows a extension to the south " +
		"where the second level lies. You are in a place that " +
		"connects the city-like life of the upper level with the " +
		"quiet life of this, the residential level and down below, " +
		"the smoky, hot air and metallic hammering of the Gnome " +
		"industries.\n"));

    add_exit(ROOM_DIR + "foo", "south", 0);
    add_exit(ROOM_DIR + "slope3", "down", 0);
    add_exit(ROOM_DIR + "slope1", "up", 0);
    set_noshow_obvious(1);
}