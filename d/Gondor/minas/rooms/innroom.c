/*
 *  The common sleeping room of the Old Guesthouse
 *  
 *  copied from the hotel room in Re Albi 
 *
 *  created by unknown 
 *  modified for The Old Guesthouse by Olorin on 6-jan-93
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/common/lib/gs_include.c"
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_gondor()
{
    set_short("small room in the Old Guesthouse in Minas Tirith");
    set_long(BS("This is a small room on the first floor of "
  	+ "the Old Guesthouse in Minas Tirith. If you have bought a key from the "
    + "innkeeper downstairs, you can spend the night here by typing "
    + "'start here'. You will then start here the next time you enter "
    + "the game.\n"));

    add_exit(MINAS_DIR + "rooms/old_guesthouse", "down", 0, 2);

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
}

public int 
start(string s)
{
    object ob;

    if (!objectp(ob = present("_the_key_to_the_old_guesthouse_", TP)))
    {
	write("You don't have the key you need!\n");
	return 1;
    }
    NFN("Start where?");
    if (s != "here") 
	return 0;

    ob->remove_object();

    TP->set_temp_start_location(MINAS_DIR + "rooms/innroom");

    write(BS("You notice that the small wooden key fits well for the situation at "
	     + "hand. You are confident that you will wake up here the next "
	     + "time you enter the game.\n"));
    return 1;
}

public void
init()
{
    ::init();

    add_action(start, "start");
}
