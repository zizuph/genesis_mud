/* updated by Amelia for Earthsea exits etc. 6-1-98 */


#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";

#include <stdproperties.h>
#include <macros.h>

void
create_traveller_room()
{
    string sign;

    set_short("Front room");

    set_long("This is a luxurious room where you may relax "+
      "from your travels in peace and comfort. There is a beautiful "+
      "seascape on the north wall, which depicts a scene on the beaches "+
      "of Earthsea. You see dark blue waves crashing onto a white sandy "+
      "beach with sea birds in the background. The walls of this mansion "+
      "are formed of the same dark granite as the walls of Gont Port, "+
      "which makes it seem impregnable from intruders. The floor is "+
      "covered with rich thick red carpets. You notice a sign that "+
      "hangs above a magnificent fireplace set into the east wall.\n");

    add_item((({"floor","carpets", "red carpets", "rich thick red carpets"})),
      "Your feet sink into the luxuriant carpets, perhaps the "+
      "gift of a traveller from one of many voyages.\n");

    add_item("seascape", "The seascape depicts the beaches of "+
      "Earthsea, known for their beauty.\n");
    add_item((({"walls", "granite"})),
      "The granite walls are made of huge grey stones and appear very "+
      "thick.\n");
    add_item((({"fireplace", "magnificent fireplace"})),
      "The fireplace in the east wall is very large, and "+
      "the fire burns merrily in it, welcoming you.\n");

    sign = "If you are a member you may type 'start here'\n" +
    "to start here when you enter the game.\n";

    add_item("sign", sign);
    add_cmd_item("sign", "read", sign);

    add_exit("stairs", "south");

    add_prop(ROOM_I_INSIDE, 1);
}

int
start(string str)
{
    if (str == "here")
    {
	if (IS_MEMBER(this_player()))
	{
	    this_player()->set_default_start_location(MASTER);
	    write("Ok.\n");
	    return 1;
	}

	write("But you aren't a member!\n");
	return 1;
    }

    notify_fail("Start here perhaps?\n");
    return 0;
}

void
init()
{
    ::init();

    add_action(start,"start");
}


