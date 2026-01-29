#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../ship.h"

static object *Rower = allocate(5 + random(3));

public void
reset_room()
{
    object ob;

    clone_npcs(Rower, SLAVE, 5.0);

    while (ob = present("oar")) 
    {
        ob->remove_object();
        say("A rowing oar suddenly breaks, and the rower picks up a new one.\n");
    }
}

int
do_beat(string str)
{
    if (str == "drum")
    {
        write("You hit the drum.\n");
        say(QCTNAME(TP) + " hits the drum.\n");
        tell_room(TP, "You hear a deep booming sound from the drum.\n");
        return 1;
    }
    NF("What do you want to hit? The drum?\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(do_beat, "hit");
    add_action(do_beat, "beat");
}

public void
create_gondor()
{
    set_short("the slavedeck");
    set_long(BSN("This is the oar deck of the merchant ship. There are "+
	     "a number of benches on each side where the rowers sit when they "+
	     "are rowing, and there is a large beating drum at the far end of "+
	     "the deck, used to keep the rowers in pace, thus enforcing "+
	     "fair speeds. A rugged brass lantern hangs in the ceiling, "+
	     "shedding a dim light so that you can barely see the room."));
    add_item("drum", "This is a large drum giving a deep booming sound.\n");
    add_item("benches", "The old, wooden benches look really uncomfortable.\n");
    add_item("lantern", "It's an old brass lantern, secured in the ceiling.\n");

    add_exit(CABIN, "up", 0);

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}
