/**********************************************************************
 * - post.c                                                         - *
 * - Post Office for Gladiators                                     - *
 * - Created by Damaris 09/2005                                     - *
 **********************************************************************/
#pragma strict_types
#pragma save_binary
inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";

#include "defs.h"
inherit "/d/Genesis/lib/post";

#include <macros.h> /* For the Q macros in messages.. */
#include <stdproperties.h> /* for room props */

public void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 2);
	set_short("Message center");
        set_long("This is a small message center for Gladiators. " +
	"It is by order of King Kalak that such a luxury has been "+
	"provided, as he has been pleased with the entertainment in "+
	"the Arena lately. Although it is considered a luxury the "+
	"room is quite bare with little atmosphere other than a "+
	"feeble counter with meager writing materials, 'examine mail "+
	"reader' for further information.\n");
	add_item(({"room", "area"}), query_long);
	add_prop(ROOM_I_INSIDE, 1);
	add_exit("startspt", "east");
	
}
/*
 * Function name:   leave_inv
 * Description:     remove mailreader from players exiting the room
 */
public void
leave_inv(object ob, object to)
{
	::leave_inv(ob, to);
	post_leave_inv(ob, to);
}

public void
mail_message(string new)
{
write("\n* - - - - - - - - - - - - - - Glory to Kalak! - - - - - - - - - - - - - - - *\n\n"+
"      There is"+ new +" mail for you in the Gladiator message center.         \n\n"+
"* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *\n");
}

/*
 * Function name:   init
 * Description:     add a mailreader to players who enter the room
 */
public void
init()
{
	::init();
	post_init();

}
