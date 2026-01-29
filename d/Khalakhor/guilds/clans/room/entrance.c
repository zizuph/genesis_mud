/**********************************************************************
 * - entrance.c                                                     - *
 * - Entrance to Khalakhor Clans race guild                         - *
 * - Created by Damaris 05/2006                                     - *
 **********************************************************************/
#pragma strict_types

#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"

inherit GUILD_ROOM;

#include "seated.c"
#include "fireplace.c"

void
create_guild_room()
{
	set_short("An expansive hall");
	set_long("   This expansive hall is filled with large tapestries "+
	"that adorn the otherwise cold stonewalls. Directly south is an "+
	"archway leading to a more private setting that is cast in "+
	"shadow from this distance. A glimpse of a large stone stairs "+
	"can be seen just through the large archway set in the eastern "+
	"wall. The main attraction of the hall is a considerable "+
	"fireplace that accommodates a dancing fire within the western "+
	"wall. ");
	add_item(({"chair","chairs", "rug"}), seat_desc);
	add_my_desc(seat_desc, this_object());	
	add_item(({"entrance", "hall","room", "area"}), query_long);
	add_item(({"hearth"}),
	"The giant hearth is made from a bleached stone with "+
	"complex carved wooden moldings making the mantle.\n");
	add_item(({"mantle"}),
	"The mantle is made of intricate and complex carved wood "+
	"with a plaque firmly attached to it.\n");
	add_item(({"north"}),
	"An archway leading to the street is in that direction.\n");
	add_item(({"south"}),
	"An archway leading to a private room is in that direction.\n");
	add_item(({"east",}),
	"An archway leading to the stairwell is in that direction.\n");
	add_item(({"west"}),
	"A large fireplace is in that direction.\n");
	add_item(({"southeast", "southwest", "northeast", "northwest"}),
	"A wall is in that direction.\n");
	add_item(({"private room"}),
	"It is bathed in shadows from this distance.\n");
	add_item(({"stairs", "stairwell"}),
	"It is just visible enough through the arch.\n");
	add_item(({"north archway", "north arch"}),
	"The archway has carved wood moulding of trees and sptites.\n");
	add_item(({"east archway", "east arch"}),
	"The archway has carved wood moulding of various fairies in "+
	"watchful poses.\n");
	add_item(({"south archway", "south arch"}),
	"The archway has carved wood moulding of banners, and ancient "+
	"symbols.\n");
		
	add_item(({"fireplace"}),
	"The fireplace is quite large with a holder placed on one side "+
	"with tools to stoke the fire and logs on the otherside to "+
	"place on the fire.\n");
	add_item(({"tool", "tools", "poker", "fireplace poker"}),
	"There are tools in a holder next to the fireplace so one can "+
	"stoke the fire.\n");
	add_item(({"log", "logs", "stack"}),
	"Logs for the fire are piled in a neat stack next to the "+
	"fireplace.\n");
	add_item(({"tapestries", "tapestry"}),
	"Huge tapestries that start at the ceiling and end near the "+
	"floor adorn the walls. Each tapestry depicts a story and there "+
	"is a total of four.\n");
	add_item(({"first tapestry"}),
	"This first tapestry depicts a story that starts at the top and "+
	"works it's way down through the silken threads. The far upper "+
	"left corner has a young man with fiery red hair walking while "+
	"carrying a large bushel sack flung over his shoulders. Just "+
	"below to the right is a wood nymph drinking from a small "+
	"spring. The next image is of the wood nymph and man both with "+
	"an expression of surprise upon seeing each other. The next "+
	"image further down shows the man handing the wood nymph his "+
	"bushel sack. The next image is of the wood nymph handing the "+
	"man a hidden object with the final image of the man standing "+
	"in full shining armour holding a crown.\n");
	add_item(({"second tapestry"}),
	"This second tapestry is vibrant and it is a huge gathering of "+
	"different Clans all sitting at a very long table. All seem to "+
	"be quite involved with drinking and eating in great "+
	"celebration. Each corner of the tapestry has a group of female "+
	"fairies looking inward at the depiction.\n");
	add_item(({"third tapestry"}),
	"This third tapestry is filled large sailing vessels docked at "+
	"the village port of SaMorgan. Just above the docks there is a "+
	"special dock that extends to the east where ships that are "+
	"being built make up a shipyard. In the far northern background "+
	"shows multiple trees with a dragon flying over.\n");
	add_item(({"fourth tapestry"}),
	"This fourth tapestry is flamboyant with multiple colours sewn "+
	"throughout depicting a single scene of sea serpent rising from "+
	"the depths of the ocean. The sky above is filled with turbulent "+
	"grey clouds.\n");
	add_item(({"plaque"}),
	"Clans of Khalakhor.\n");
	add_cmd_item("plaque", "read", 	"Clans of Khalakhor.\n");
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	add_exit("/d/Khalakhor/sw_speir/samorgan/room/vil0707", "north");
	add_exit("join", "south");
	add_exit("stairs", "east");
	add_fail("west", "You walk right into the fireplace and get "+
	"burned!\n\nOuch! That hurts!");
	add_fail(({"southeast", "southwest", "northeast", "northwest"}),
	"A wall stops you.\n");
	
}
/**********************************************************************
 * - Give us some commands.                                         - *
 **********************************************************************/

public void
init()
{
	::init();
	init_seat();
	init_fire();
}
