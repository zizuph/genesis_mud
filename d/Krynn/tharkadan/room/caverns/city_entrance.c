#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit CAVERNS_BASE;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"cave",}));
object dwarf1, dwarf2, dwarf3, dwarf4, leader, magi;

void
reset_tharkadan_room()
{

    if(!objectp(leader) && !objectp(magi))
    {
        if(random(3) == 1)
        {
           magi = clone_object(LIVING + "theiwar_magi");
           magi->arm_me();
           magi->move(TO, 1);
        }
        else
        {
           leader = clone_object(LIVING + "theiwar_chieftain");
           leader->arm_me();
           leader->move(TO, 1);
        }
    }

    if(!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIVING + "theiwar_savant");
        dwarf1->move(TO, 1);
    }

    if(!objectp(dwarf2))
    {
        dwarf2 = clone_object(LIVING + "theiwar_axeman");
        dwarf2->move(TO, 1);
    }

    if(!objectp(dwarf3))
    {
        dwarf3 = clone_object(LIVING + "theiwar_savant");
        dwarf3->move(TO, 1);
    }

    if(!objectp(dwarf4))
    {
        dwarf4 = clone_object(LIVING + "theiwar_axeman");
        dwarf4->move(TO, 1);
    }

    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(CAVERNS + "upper_mines13","west", 0);
    add_exit(CAVERNS + "upper_mines20","south", 0);
    add_invis_exit(CAVERNS + "xx","northeast", "@@no_go");

    add_prop(ROOM_S_DARK_LONG, "A lightless tunnel. Without a light " +
          "source it is too dark to see in here.\n"); 
    add_prop(ROOM_S_DARK_MSG, "It is too dark to"); 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    add_item(({"tunnels"}),
        "Tunnels lead away from the ledge here to your west and south.\n");
    add_item(({"reinforced ledge","ledge", "balustrade", 
        "stone balustrade", "break"}), "You stand on a ledge that has " +
        "been reinforced with a stone balustrade to stop careless " +
        "dwarves from falling into the chamber below. To the northeast " +
        "of the ledge there is a break in the balustrade to allow " +
        "access to a retractable bridge extended from the other side " +
        "of the chamber. At the edge of the balustrade near the break " +
        "you notice a signal mechanism.\n");
    add_item(({"signal mechanism","mechanism"}), "A curious dwarven " +
        "mechanism sits on the edge of the stone balustrade, " +
        "used to signal the dark dwarves on the other side of the " +
        "chamber to extend the bridge. It looks like it needs a key " +
        "to activate.\n");
    add_item(({"chamber","massive chamber","magma bowl","bowl","volcano"}),
        "You stand on a ledge at the very top of a massive chamber that " +
        "was once the magma bowl for a volcano that is now long " +
        "dormant. You would have had no idea of the size of the " +
        "chamber if it wasn't for the darkness being broken by " +
        "thousands of tiny pin pricks of light far below, the forge " +
        "fires of the dark dwarf Kingdom of the Theiwar.\n");
    add_item(({"forge fires","fires"}), "Far beneath you burn " +
        "thousands of forge fires, outlining a great city of " +
        "dark dwarves - a kingdom of the Theiwar clan.\n");
    add_item(({"kingdom","city"}), "You stand on a ledge overlooking " +
        "a great dwarven city, a kingdom of the Theiwar clan. You can't " +
        "see much - dark dwarves hate the light. However they love to " +
        "forge, and the thousands of forge fires burning far beneath " +
        "you indicate it is an impressive city!\n");
    add_item(({"second ledge","northeast","other ledge","another ledge",
        "bridge","another reinforced ledge","second reinforced ledge",
        "retracted bridge"}), "To your northeast across the chamber " +
        "is another reinforced ledge similar to this one, however it " +
        "has a large retracted bridge stationed there. You imagine that " +
        "bridge is how you would access the city below if you could " +
        "get it to extend.\n");

    add_cmd_item(({"mechanism","signal mechanism"}), ({"activate","use"}),
        "You need a specific key to activate the signal mechanism.\n");
    add_cmd_item(({"mechanism","signal mechanism"}), ({"pick","unlock"}),
        "You attempt to pick the mechanism, but it fails to activate.\n");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "vent","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "a ledge overlooking a massive chamber, the kingdom of the " +
        "Theiwar clan";
}

string
long_descr()
{
    return "The tunnels end here at a reinforced ledge overlooking a " +
        "massive chamber that was once the magma bowl of the volcano. " +
        "Far below you can make out thousands of forge fires burning " +
        "in the darkness like tiny red stars, the only indication that " +
        "a city of dark dwarves has made their home beneath you. Far " +
        "across to your northeast you can make out another reinforced " +
        "ledge with a retracted bridge - likely the entrance to the " +
        "city.\n";
}

int
no_go()
{
    write("You walk to the edge of the ledge where the break in the " +
        "stone balustrade is and look down. You don't feel you should " +
        "go any further without the bridge extended and firmly in " +
        "place!\n");
    say(QCTNAME(TP)+ " walks to the ledge where the break in the stone " +
        "balustrade is, looks down, and returns.\n");
    return 1;
}
