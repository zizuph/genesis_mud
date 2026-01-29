#include "outroom.h"

create_outroom() {
    set_short("A mountain path enters a cleft.");
    set_long("A mountain path enters a cleft. To the south is the plain, "+
	     "and a precipitous passage between the stones climbs upwards.");
    add_item(({"path","cleft","passage"}),
	     "It is a somewhat dangerous track, so keep your tongue "+
	     "straight.\n");
    add_item(({"stone","stones"}),
	     "They seem somewhat dangerous.\n");
    add_item("plain",
	     "It lies between a steep rocky wall and the lake, the Sirannon "+
	     "Lake.\n");
    SOUTH("n_of_plain");
    UP("steep_path");
}

init() {
    ::init();
    add_action("my_jump","jump");
    add_action("my_climb","climb");
    add_action("my_yodl","yodl");
    add_action("my_move","move");
}

my_jump(arg) {
    if(!arg) {
	notify_fail("Jump where?\n");
	return 0;
    }
    write("Are you kidding?\n");
    return 1;
}

my_climb(arg) {
    if(!arg) {
	notify_fail("Climb where?\n");
	return 0;
    }
    if(arg == "up" || arg == "passage") {
	TP->command("up");
	return 1;
    }
}
    
my_yodl() {
    write("Yodlitatitoooo!\n");
    return 1;
}

my_move(arg) {
    if(!arg) {
	notify_fail("Move what?\n");
	return 0;
    }
    if(arg == "stone" || arg == "stones" || arg == "rocks" || arg == "rock") {
	write("Thought of killing yourself?\n");
    return 1;
    }
}
