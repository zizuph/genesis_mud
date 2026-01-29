// Ziggurat Garden (room11.c)
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"

inherit ZIG_GARDEN;

public void
zig_room(void)
{
    /* Avtime events. */
    AVTIME->add_event(this_object());
    season = AVTIME->get_avenir_week();

    set_long("@@my_long");

    add_exit("room12", "west", "@@exit_string");
    add_exit("room10", "north", "@@exit_string");
}

public string
my_long(void)
{
    string str;

    switch(season)
    {
    case 2..10: /* Tree flowers. */
	str = "Sourcelight shines through the oak leaves as the thick branches reach "+
	"outward, ";
	break;
    default: /* Tree is dead. */
	str = "Sourcelight filters through far-reaching oak branches as they "+
	"radiate outward, ";
	break;
    }

    return "The white flagstone path passes through yellow-green grass "+
    "to curve around a small oak tree before continuing to the north and west. "+
    str +"stretching toward golden marigolds and purple petunias "+
    "nestled into little beds bordering this arbor. A sturdy wooden swing hangs "+
    "from a thick oak branch allowing someone to swing out toward the "+
    "aqueduct railing as though flying into the panorama of the City to the "+
    "southwest.\n";
}

public string query_trees(void) {   return "oak tree";    }

static void
garden_items(void)
{
    ::garden_items();

    add_views("From "+
      "this side of the Ziggurat you can see the High Lord Commisioner's "+
      "enclave to the south, opulent noble houses circle the High Lord's "+
      "palace on the central hill. Farther off to the east, you can just "+
      "see part of the High Lord Executioner's enclave and its similar "+
      "layout.", "enclaves, giving them");

    add_rock("raised etching of a baby's cradle", ", the symbol of Azauph");

    add_item(({"oak","oak tree","oaks","oak trees","small tree",
      "small trees","small oak trees","small oak tree","tree","trees",}),
      "@@see_tree");

    add_item(({"nut","nuts","acorn","acorns",}), "@@see_fruit");

    add_cmd_item(({"nut","nuts","acorn","acorns",}), ({"pluck", "pick"}),
      "@@pluck_acorns");

    add_object(ZIG_RLG + "swing_r11", 1, 0 );
}

static void
garden_flowers(void)
{
    add_flower("marigold", ({"golden", "bright yellow"}));
    add_flower("petunia", "purple");

    ::garden_flowers();
}

public string
see_fruit(void)
{
    string str;

    switch(season)
    {
    case 5..10:
	str = "The acorns contain a single seed, enclosed in a tough, leathery "+
	"shell, and borne in a cup-shaped cupule. They fall from the "+
	"branches when ripe and are probably quickly gathered by the "+
	"gardeners. The acorns hanging from the branches are unripe and "+
	"greenish.\n";
	break;
    default: /* Tree is dead. */
	str = "There are no acorns to be seen.\n";
	break;
    }

    return str;
}

public string
pluck_acorns(void)
{
    string str;

    switch(season)
    {
    case 5..10:
	str = "They are high out of reach.\n";
	break;
    default: /* Tree is dead. */
	str = "There are no acorns to be seen.\n";
	break;
    }

    return str;
}

public string
see_tree(void)
{
    string str;

    switch(season)
    {
    case 2..7: /* Tree regrows. */
	str = "The oak is tall and strong with thick branches which hold a canopy "+
	"of distinctive, bright green leaves. Many acorns hang amongst the "+
	"leaves.";
	break;
    case 8..10: /* Autumn. */
	str = "The oak is tall and strong with thick branches which hold a canopy "+
	"of distinctively shaped leaves which have turned a muted red. Many "+
	"acorns hang amongst the leaves.";
	break;
    default: /* Tree is dead. */
	str = "The oak is tall and strong with large, straight trunk and thick "+
	"branches which are currently bare of leaves. The bark is a "+
	"pretty silvery-white.";
	break;
    }

    return str +" A wooden swing hangs from one of the thick branches.\n";
}
