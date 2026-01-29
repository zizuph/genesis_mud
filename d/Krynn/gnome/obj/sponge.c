inherit "/std/object";
 
#include <stdproperties.h> 	/* All prop definitions */
#include <cmdparse.h>		/* The FIND_STR_IN_OBJECT macro */
#include <macros.h>		/* QCTNAME and QTNAME macro */
#include "/d/Krynn/common/defs.h"
#include "../local.h"

void
create_object()
{
    seteuid(getuid());
    set_name("sponges");
    set_short("huge heap of sponges");
    set_long("Thousands of sponges, released by the gnomeflinger" +
	" safety mechanism to break\nsomeone's fall.\n");
    add_item("sponge", "Each sponge is made out of some soft," +
	" elastic substance.\n");
    add_prop(OBJ_I_LIGHT, 0);
    add_prop(OBJ_I_WEIGHT, 700000);
    add_prop(OBJ_I_VOLUME, 30000000);
    if (IS_CLONE)
  	set_alarm(10.0, -1.0, "cleanup");
}

void
init()
{
    add_action("pickup", "get");
}

int
pickup(string str)
{
    NF("Get what?\n");
    if (!str)
	return 0;
    if (str == "sponges")
	write("All of them?  It would take dozens of you!\n");
    else if (str == "sponge")
    {
    	clone_object(OBJ + "sponge1")->move(TP);
    	write("You pick up a sponge.\n");
    	say(QCTNAME(TP) + " picks up a sponge.\n");
    }
    else
    {
    	write("Whatever you're looking for is buried under" +
	    " the sponges.\nWait until the room is cleaned up a bit...\n");
    	say(QCTNAME(TP) + " rummages around in the sponges.\n");
    }
    return 1;
}

void
cleanup()
{
    tell_room(environment(), "A gnome cleanup crew rushes in.\n");
    set_alarm(6.0, -1.0, "endit");
}

void
endit()
{
    tell_room(environment(), "The sponges are now all safely back in" +
	" their storage bins.\n");
    remove_object();
}
