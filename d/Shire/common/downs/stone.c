inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

create_room() {
    set_short("Atop a barrow");
    set_long(break_string(
	  "You have arrived at the top of a hill, facing a barrow. "
	+ "The wind is blowing icy from the east. The black rock "
        + "is pointing to the sky like a finger of ancient anger.\n",70));

    add_exit(DOWNS_DIR + "slope", "north");

    clone_object(DOWNS_DIR + "barrow")->move(this_object());
}

init() {
    ::init();
    add_action( "do_dig", "dig");
}

do_dig(str)
{
    write("You start to dig in the ground with your hands. Suddenly the "
	+ "ground below gives away! You slip, and fall into a dark pit.\n");
    this_player()->move_living("into the ground.", DOWNS_DIR + "stone1");
    return 1;
}
