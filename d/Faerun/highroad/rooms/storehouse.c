/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
//#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_KEEP;

void
create_house()
{
    set_short("A packed storehouse");
    set_long("You can hardly squeeze in to this crapped storehouse. Goods " +
             "are stacked floor to ceiling, and you can hardly move. Only " +
             "a single brass lantern is set on a crate here, emitting just " +
             "enough light to allow the provisioner to identify needed " +
             "times. He must have a system for identifying which items are " +
             "stored where, but you cannot discern what it is. Everything " +
             "is unlabelled and tightly packed. There is no " +
             "place to go but west, back into the provisions shop.\n");
	
    add_exit(ROOM_DIR + "provisions",  "west");

    reset_room();
}

void
reset_room()
{
   ::reset_room();
}
