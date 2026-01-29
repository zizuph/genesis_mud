/*
* Inn created on the 1.5.94 for the City of Telberin in the
* expansion phase of the City, Mylos.
*/

inherit "/std/room";
inherit "/lib/pub";
inherit "/d/Emerald/lib/room_tell";

#include "/d/Emerald/defs.h"
#include <stdproperties.h>

void
create_room()
{
    set_short("The Vulgar Unicorn");
    
    set_long("   Shadows hover all around you as you enter this dark and dank " +
        "tavern. The gloom is hardly alleviated by the dozens of oil " +
        "lamps that hang from the overhead beams. Low, rough-hewn tables " +
        "are scattered throughout the tavern. The bartender glances in " +
        "your direction with an air of watchfulness and suspicion, then " +
        "quickly looks away, ignoring you. Harried barmaids try " +
        "desperately to keep up with the shouts for more beer. \n\n");
    
    add_exit("c31", "out", 0);
    
    add_prop(ROOM_I_INSIDE, 1);
    
    add_prop(ROOM_M_NO_ATTACK, 1);
    
    add_cmd_item("menu", "read", "@@menu_desc@@");
    
    add_item("menu", "A short, hand-painted wood sign.\n");
    
    add_item(({"lamps","oil lamps","lamp"}), "These smokey oil lamps, " +
        "which hang from the beams above, are tarnished with rust and " +
        "the glass is cracked and encrusted with dirt and soot.\n");
    
    add_item(({"tables","rough-hewn tables"}), "The tables, made of old " +
        "timbers, offer nothing but a place to set your drink and plenty " +
        "of splinters.\n");
    
    add_item("bartender","A huge burly man whose fearsome gaze is " +
        "enough to make many people think twice before causing any " +
        "trouble in his place of business.\n");
    
    add_item(({"barmaid","barmaids"}), "Young girls, barely old enough " +
        "to be drinking themselves, run hurriedly back and forth between " +
        "the bar and the patrons they serve.\n");
    
    set_tell_time(30);
    add_tell("Some Telberin elven warriors whisper secretively " +
        "in the corner.\n");
    add_tell("As a loud conversation erupts at a table in the " +
        "back of the tavern, two strange mercenaries draw their " +
        "swords in a flash of metal. A fierce yell from the " +
        "bartender immediately silences the room, and the " +
        "two mercenaries sit down quickly.\n"); 
    add_tell("Boisterous voices and the clinking of glasses " +
        "fill the room.\n");
    
    add_drink(({ "beer", "watery beer" }), "beer", "watery", 500, 3, 8,
        "mug of beer", 0, "A watered down beer, rather bland.\n", 0);
    
    add_drink(({ "ale", "dark ale" }), "ale", "dark", 100, 20, 22,
        "tankard of dark ale", 0, "A dark refreshing ale.\n", 0);
    
    add_drink( ({"wine", "red wine"}), "wine", "red",
        62, 35, 72, "glass of imported Elven wine", 0, "A " +
        "beautifully rich Elven wine, imported from Telberin.\n", 0);
    
    add_drink(({ "special", "unicorn special" }), "special", "unicorn",
        40, 60, 280, "frothing, bubbling shot", 0, "It looks as " +
        "nasty and as mean as the unicorn outside.\n", 0);
    
}

void
init()
{
    ::init();
    init_pub();
}

string
menu_desc()
{
    return "       The menu reads:\n\n"+
    "  Beer               -   8 cc\n"+
    "  Dark ale           -  22 cc\n"+
    "  Red wine           -  72 cc\n"+
    "  Unicorn Special    - 280 cc\n";
    
}

void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}

