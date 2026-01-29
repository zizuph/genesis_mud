/*
 * This is a temporary file to allow people that log in
 * from our guild to log in. Else they have a corrupt
 * login string
 */
inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("The dream");
    set_long("You are having a weird dream. You'd better wake up!\n");
    add_exit(HIN_DIR + "rooms/hguild", "awake", "@@fix");
}

int
fix()
{
    if (this_player()->query_default_start_location() == HIN_DIR + "hguild")
	this_player()->set_default_start_location(HIN_DIR + "rooms/hguild");

    return 0;
}
