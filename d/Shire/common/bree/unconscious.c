#include "defs.h"
#include "/sys/ss_types.h"

inherit "/std/room";

create_room() {
    set_short("You are unconscious.");
    set_long(break_string(
	  "The fall from the tree has knocked you unconscious. "
        + "You see all kinds of weird stars, gray planets, orcs, ogres, "
        + "rifts of space, nothing, and yet everything, and all of that "
        + "in multicolour! Isn't the mind a mindboggling thing?\n",70));

    add_exit(STAND_DIR + "tom","awake");
}
