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
    set_short("An open air turret");
    set_long("@@dependent_long");

    add_prop(ROOM_I_INSIDE, 0); 

    add_item(("beacon"), "@@my_beacon");

    add_exit(THIS_DIR+"ac", "down");
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
	return "You stand on a high open air turret overlooking the " +
	    "the surrounding grounds of the fortress.\n" +
	    "Before you is the huge metal grate of the Army's beacon.\n";
}

public string
my_beacon()
{
    if (lit)
	 return "You gaze at the billowing, blood red smoke as it rises " +
	    "high into the sky\n.";
    return "The metal grates are blackened by soot and stained with " +
	"the fibres of leaves.\n";
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