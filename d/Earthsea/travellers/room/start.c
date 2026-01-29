/* updated by Amelia for Earthsea exits etc. 6-1-98 */

#pragma strict_types
#pragma save_binary

#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>

inherit TRAVELLERS_STD_DIR + "room_base";

public void
create_traveller_room()
{
    add_prop(ROOM_S_MAP_FILE, "trav_map.txt");
    string sign;
    set_short("Front Room");
    set_long("This is a luxurious room where you may relax " +
      "from your travels in peace and comfort. There is a beautiful " +
      "seascape on the north wall, which depicts a scene on the " +
      "beaches of Earthsea. You see dark blue waves crashing onto " +
      "a white sandy beach with sea birds in the background. The " +
      "walls of this mansion are formed of the same dark granite " +
      "as the walls of Gont Port, which makes it seem impregnable " +
      "from intruders. The floor is covered with rich thick red " +
      "carpets. You notice a sign that hangs above a magnificent " +
      "fireplace set into the east wall.\n");
    add_item((({ "floor","carpets", "red carpets",
        "rich thick red carpets"})),
        "Your feet sink into the luxuriant carpets, perhaps the " +
        "gift of a traveller from one of many voyages.\n");
    add_item("seascape", "The seascape depicts the beaches of " +
        "Earthsea, known for their beauty.\n");
    add_item((({ "walls", "granite" })),
        "The granite walls are made of huge grey stones and appear very " +
        "thick.\n");
    add_item((({ "fireplace", "magnificent fireplace" })),
        "The fireplace in the east wall is very large, and " +
        "the fire burns merrily in it, welcoming you.\n");
    sign = "If you are a member you may type 'start here'\n" +
        "to start here when you enter the game.\n";
    add_item("sign", sign);
    add_cmd_item("sign", "read", sign);
    add_exit("stairs", "south");
}

public int
start(string str)
{
    object tp;

    if(str == "here")
    {
        tp = this_player();

        if(IS_MEMBER(tp))
        {
            tp->set_default_start_location(MASTER);
            write("Ok.\n");
            return 1;
        }

        return notify_fail("But you aren't a member!\n");
    }

    return notify_fail("Start here perhaps?\n");
}

public void
init()
{
    ::init();
    add_action(start, "start");
}
