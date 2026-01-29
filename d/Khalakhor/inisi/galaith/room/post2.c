/**********************************************************************
 * - post.c                                                         - *
 * - Postoffice added to tree.                                      - *
 * - Created by Damaris@Genesis 01/2006                             - *
 **********************************************************************/
#pragma strict_types
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/basic.h"
inherit "/d/Khalakhor/std/room";
inherit "/d/Genesis/lib/post";
public void
create_khalakhor_room()
{
	set_short("Postal service");
	set_long("   This strange little corner inside the tree is "+
	"where the postal service is. The walls are made of bark and "+
	"there is what looks like a stairway made of vines and limbs "+
	"spiraling upward to a small opening. The atmosphere is cozy "+
	"and welcoming with warm lit lanterns upon the walls that give "+
	"off just enough light to cast a nice glow on a small counter. "+
	"Just behind the counter is a very pleasant looking postal "+
	"worker who is sorting mail. She is quite busy with her tasks "+
	"so it would be wise to let her continue her work. So please "+
	"'examine mail reader' for further information.\n");
	add_item(({"room", "area"}), query_long);
	add_item(({"painting", "paintings"}),
	"You look closer at the posters that adorn the walls here.\n"+
	"They depict far off lands you have yet to see. There are "+
	"beautiful castles and green grass, also majestic mountains and "+
	"cliffs with stunning waterfalls. Each painting makes you wonder "+
	"what lies ahead in the distant lands.\n");
	
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 2);
	add_exit("tree", "northwest");
	add_fail("auto", "You walked into a wall!\n"+
	"Ouch! That's gotta hurt!\n");
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
	write("\nThere is"+ new +" mail for you in the post office.\n");
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
