#include "../gnome.h"
#pragma save_binary

inherit "/std/room";
inherit LIB;

void
reset_room() {
    reset_guards();
}

void
create_room() {
  set_short("Gnomehome main tunnel");
    set_long(BS(" Here, the main tunnel of Gnomehome reaches the gate to " +
                "the southeast and continues further into the hill to the " +
                "northwest. Occasional side exits lead to private areas, " +
                "and you stay away from them. Southwest, on the other hand, " +
                "you hear the unmistakable sounds of crowds and commerce.\n"));
    add_item(({ "tunnel", "wall" }),
             BS("The tunnel is dug out of the hillside, approximately three " +
                "meters high and eight meters wide, and the walls and roof " +
                "are crisscrossed with supporting oak beams.\n"));
    add_exit(ROOM_DIR + "gate", "southeast", 0);
    add_exit(ROOM_DIR + "corr2", "northwest", 0);
    add_exit(ROOM_DIR + "merch1", "southwest", 0);
    guard_settings = ({ 1 }) + DEFAULT_GUARD_SETTINGS;
    reset_guards();
    set_noshow_obvious(1);
}
