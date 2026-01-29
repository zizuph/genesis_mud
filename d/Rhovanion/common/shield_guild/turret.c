#pragma save_binary

inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "guild.h"

/*
 * Global variables
 */
int here, lit;

void
create_room()
{
    set_short("Antechamber");
    set_long("@@dependent_long");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_exit(THIS_DIR+"c2", "north");
    add_exit(THIS_DIR+"gates", "south");
    add_exit(THIS_DIR+"ac", "east");
}

public string
dependent_long()
{
    string str;

    if (lit)
	return "You stand on a high open air turret overlooking the " +
	    "surrounding grounds of the fortress.\n" +
	    "Before you, billowing in the wind, is the deep red smoke " +
	    "of the Armies beacon.\n";
    else
	return "You stand on a high open air turret overlooking the " +
	    "the surrounding grounds of the fortress.\n" +
	    "Before you is the huge metal grate of the Army's beacon.\n";
}

public void
enter_inv(object ob, object from)
{
    here++;
    ::enter_inv(ob, from);
    return;
}

public void
leave_inv(object ob, object to)
{
    here--;
    return;
}