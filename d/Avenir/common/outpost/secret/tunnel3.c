#include "outpost.h"
inherit OUTPOST +"secret/tunnel_base";

void
create_room()
{
		IN_IN; // not in flux zone.
    set_short("ledge along the cavern wall");

    western("tunnel2");
    add_exit("stair_bottom2", "east", 0, 60);

    set_long("You are on a tiny little ledge, dangling over the "+
        "abyss, which glows red-orange below you. You can pick "+
        "out cracks and gaps in the wall that will make it "+
        "possible for you move along the wall east and "+
        get_west() +". A low, grinding sound emanates from the "+
        "lava flowing below, and hot dry winds buffet you, beading "+
        "your skin with sweat and making every breath agony.\n");

    add_item(({"abyss", "down", "lava", "lava flow"}), 
        "You stare down into the fiery abyss. The abyss looks "+
        "back into you.\n");

    ACI(({"breeze","wind"}), "feel", "The currents of air are "
       + "suffocatingly hot.\n");

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    add_tell("The air is so hot you feel as though you are suffocating.\n");
    add_tell("Your feet are aching from the heat that seems to "+
        "pound at you from below.\n");
}
