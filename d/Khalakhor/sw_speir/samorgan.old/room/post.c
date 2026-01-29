/**********************************************************************
 * - post.c                                                         - *
 * - Post Office in SaMorgan                                        - *
 * - Created by Damaris@Genesis 09/2000                             - *
 **********************************************************************/

#pragma strict_types
#pragma save_binary
#include "../defs.h"

inherit "/d/Genesis/lib/post";
inherit "/d/Khalakhor/std/room";

#include <macros.h> /* For the Q macros in messages.. */
#include <stdproperties.h> /* for room props */
/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/
public int *
query_local_coords()
{
	return ({6, 5});
}
public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}

string
query_sign()
{
    return(      "          +------------------------------+\n"+
      "          |                              |\n"+
      "          |      Examine Mailreader      |\n"+
      "          |                              |\n"+
      "          +------------------------------+\n"); 
}
void
create_khalakhor_room()
{
	set_short("SaMorgan postal area");
	set_long("   Dust covers packages of all different shapes and "+
	"sizes that are piled up in the far corner of this postal area. "+
	"Through the small window within the western wall a small amount "+
	"of light peeks through the dingy cloth place upon it, that "+
	"seems to flicker now and again when a slight breeze filters in. "+
	"Far towards the back in the shadows is a postal worker sorting "+
	"through many different postal items ranging from letters to "+
	"packages. The walls are a bit drab as they remain without any "+
	"ornaments save a couple of lanterns. The center of the room has "+
	"a fairly good-sized counter that holds paper, quills and ink. A "+
	"small sign is placed upon the counter that states <examine "+
	"mailreader> to understand how this post works.\n");
	add_item(({"room", "post", "postal office", "post office", "postal area", "area"}), query_long);
	add_item(({"packages", "package", "pile", "corner", "far coerner"}),
	"There is a pile of packages covered with dust in the far "+
	"corner.\n");
	add_item(({"postal worker", "worker"}),
	"The postal worker is busy.\n");
	add_item(({"dingy cloth", "cloth"}),
	"The dingy cloth has been placed on the window and it moves "+
	"back and forth dependent upon the breeze.\n");
	add_item(({"window"}),
	"The window is small and has a cdingy cloth covering it.\n");
	add_item(({"shadow", "shadows"}),
	"The back of the room seem to dance with shadows.\n");
	add_item(({"letters"}),
	"The postal worker seems quite busy sorting letters and "+
	"packages.\n");
	
	add_item(({"west", "south"}),
	"That direction leads back out into the village street.\n");
	add_item(({"north", "east", "southeast", "southwest", "northwest", "northeast"}),
	"There is a wall in that direction.\n");    
	add_item(({"walls","wall"}),
	"The walls are pretty bare save two lanterns one fixed on two "+
	"walls.\n");
	add_item(({"floor","ground"}),
	"The floor on which you are standing seems very firm, and is "+
	"made of a clay and rock formation.\n");
	add_item(({"lantern","lanterns"}),
	"The lanterns are fixed firmly to the wall, and cannot be "+
	"taken.\n");
	add_item(({"sign", "small sign"}), query_sign);
	add_item(({"paper", "papers", "stack of paper", "stack of papers"}),
	"There is a stack of paper on the counter.\n");
	add_item(({"quill", "quills"}),
	"There are quills laying upon the counter ready to be used.\n");
	add_item(({"ink", "inkwell", "black ink", "black inkwell"}),
	"There is an inkwell filled with black ink placed on the "+
	"counter.\n");
	add_item(({"counter", "good-sized counter", "large counter"}),
	"There is a good-sized counter in the center of this room\n");
	
	add_exit("vil0905", "west");
	add_exit("vil1006", "south");
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
}
int
do_read(string str)
{
	if (str != "sign")
	{
		notify_fail("Read what?\n");
		return 0;
	}
	write(query_sign());
	return 1;
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

/*
 * Function name:   init
 * Description:     add a mailreader to players who enter the room
 */
public void
init()
{
	::init();
	post_init();
	add_action("do_read",   "read");

}
