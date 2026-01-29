inherit "/d/Rhovanion/lib/room";
inherit "/lib/shop";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

create_room()
{
	set_store_room(CULT_DIR + "t_stroom");
	set_short("Guild shop.");
	set_long("This is the guild shop, staffed by a couple of novices."
		+" Here you may buy things required for journeys abroad and sell"
		+" things gotten on such journeys."
		+" However, it is recommended that you leave items that are potentially"
		+" useful to other members in the gathering hall. There is a sign on the"
		+" wall.\n");

	add_item(({ "novices", "novice" }), "Bound to an oath of silence as they are,"
		+" none of them can or will speak to you.\n");
	
	add_exit(CULT_DIR + "t_gather", "west", 0);
	add_exit(CULT_DIR + "t_post", "north", 0);
	add_exit(CULT_DIR + "t_stroom", "east","@@wiz_check");

	add_prop(ROOM_I_LIGHT , 1);
	add_prop(ROOM_I_INSIDE, 1);
	
	config_default_trade();
}

init()
{
    ::init();
    init_shop();
}
