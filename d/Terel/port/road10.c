/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * road10.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit PORT_DIR + "port_room";

static object boy;

public void
reset_room()
{
    object shovel;

    if (!boy) {
	seteuid(getuid());
	boy = clone_object(PORT_DIR + "monster/boy");
	boy->move_living("arrives", TO);
	shovel = clone_object(PORT_DIR + "obj/shovel");
	shovel->move(boy);
	boy->command("wield shovel");
    }
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Village road");
    set_long("You are standing on the eastern village road. " +
	     "It continues to the south and to the northwest. " +
	     "Some distance to the south you make out a pier. " +
	     "To the east a small muddy path opens up and " +
	     "to the west is a house which you hear some noise from. " +
	     "There is a distinct smell in the air.\n");
    
    add_item(({"pier"}), 
	     "It seems to be some kind of wooden pier, but you " +
	     "must go further south to be sure.\n");
    
    add_exit(PORT_DIR + "road9",  "northwest", 0);
    add_exit(PORT_DIR + "road11", "south",     0);
    add_exit(PORT_DIR + "inn",    "west",      0);
    add_exit(PORT_DIR + "path5",  "east",      0);

    set_alarm(1.0, -1.0, "reset_room");
}
