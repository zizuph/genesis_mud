#include "valley.h"

create_valley() {
    set_short("Small hill.");
    set_long("You are on a small hill near the east side of greenhouse "+
	     "valley. A number of plants prevent you from going east and "+
	     "south, and north is a wild rose thicket. A path leads down "+
	     "west. ");
    add_item(({"hill","valley"}),"Oh this is such a beautiful place.\n");
    add_item(({"plant","plants","rose","roses","thicket"}),
	     "Well, even if you had a jungle machete, you wouldn't bother "+
	     "cutting yourself through this thicket.\n");
    add_item("path","It leads west into a crossing.\n");
    WEST("crossing");
}

init() {
    ::init();
    add_action("my_cut","cut");
    add_action("my_pick","pick");
    add_action("my_touch","touch");
}		    

my_cut(arg) {
    if(!arg) {
	notify_fail("Cut what?\n");
	return 0;
    }
    if (arg == "thicket" || arg == "roses" || arg == "rose" || arg == "plants"
       || arg == "plant") {
	write("You don't bother.\n");
	return 1;
    }
}

my_pick(arg) {
    if(!arg) {
	notify_fail("Pick what?\n");
	return 0;
    }
    write("Nah, they are to ugly.\n");
    return 1;
}

my_touch(arg) {
    if(!arg) {
	notify_fail("Touch what?\n");
	return 0;
    }
    write("Ok, now you have touched them as well.\n");
    return 1;
}
