/*
 * Daenbraigh post office
 * TAPAKAH, 04/2005
 */

inherit "/d/Khalakhor/std/room";
inherit "/d/Genesis/lib/post";

#include <stdproperties.h>
#include "../../nspeir.h";
#include "../../village/village.h";

void
create_khalakhor_room()
{
    set_short("Daenbraigh Post Office");
    set_long(BS("The post office was the last institution set in Daenbraigh " +
		"as the army and the elder realized the importance of communications " +
		"with other goblin tribes of the world. It is built from thick wooden "+
		"planks. Wooden crates are scattered on the floor. " + get_std_use()));
    add_item(({"plank", "planks"}),
	     "The planks look to be collected from shipwrecks.\n");
    add_item(({"floor", "crates", "crate"}),
	     "The crates used for transporting mail are scattered all around.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(GV_OUTSIDE,0);

    add_exit("we2","north");
}
 
void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}
