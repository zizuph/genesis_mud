#include "outpost.h"
inherit OUTPOST +"secret/tunnel_base";


void
create_room()
{
		IN_IN; // not in flux zone.
    set_short("nook along the cavern wall");

    add_exit("tunnel6", "crack", 0, 70);
    add_exit("stair_top2", "south", 0, 40);

    set_long("You are in a nook in the chasm wall, high above "+
        "the abyss. A jagged crack leads deeper into the living "+
        "stone, while south is a reddish-orange glow. A low, "+
        "grinding sound emanates from below and hot little "+
        "fingers of wind puff through here, making your eyes "+
        "water.\n");

    add_item(({"abyss", "down", "lava", "lava flow"}), 
        "You stare down into the fiery abyss. The abyss looks "+
        "back into you.\n");
    add_item("crack", "The crack leads deeper into the living stone\n");
		
    ACI(({"breeze","wind"}), "feel", "The currents of air are "
       + "suffocatingly hot.\n");

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    add_tell("The air is so hot you feel as though you are suffocating.\n");
    add_tell("Your feet are aching from the heat that seems to "+
        "pound from below.\n");
}
