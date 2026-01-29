
/* Copied over from Quetzl's Esgaroth shop */

#pragma save_binary

inherit "/d/Rhovanion/lib/room";
inherit "/lib/shop";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
	set_store_room(RHUN+"stown3/storeroom");
    set_short("Town shop");
	set_long(break_string("This is the town shop."
	+"  You may buy or sell items here.  There is a sign on the wall"
	+" for you to read for instructions.  You can leave"
	+" by exiting to the northwest.\n",75));

AE(RHUN+"stown3/north_road","northwest");
    add_prop(ROOM_I_INSIDE, 1);
    config_default_trade();
}

init()
{
    ::init();
    init_shop();
}