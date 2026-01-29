// Ziggurat Garden (room5.c)
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

    set_long("Cheerful yellow daffodils and striking red tulips stretch "+
      "toward the Source in their well-manicured beds. Three small pear "+
      "trees form an angle, mirroring the white flagstone path as it curves "+
      "its way around the Ziggurat, turning near the center tree to run east "+
      "and south. Behind the trees sits a sturdy wooden bench, nestled away "+
      "near the ever trickling aqueduct railing.\n");

    add_exit("room6", "east", "@@exit_string");
    add_exit("room4", "south", "@@exit_string");
}

public string query_trees(void) {   return "pear tree";    }

static void
garden_items(void)
{
    ::garden_items();

    add_views("From this side of the Ziggurat you can see the High Lord "+
      "Inquisitor's enclave to the north and west, opulent noble houses "+
      "circle the High Lord's palace on the central hill.",
      "enclave, giving it");

    add_rock("a gold coin set within a depression to be flush with the "+
      "rock surrounding it", ", the symbol of Nitikas");

    add_item(({"trees","small trees","pear trees","small pear trees",
	"tree","small tree","pear tree","small pear tree",}), "@@see_tree");

    add_item(({"pear","pears","fruit","fruits",}), "@@see_fruit");

    add_item(({"pear blossom","pear blossoms","pear flower",
	"pear flowers",}), "@@see_pearblossom");

    add_fruit("pear");

    add_object(ZIG_RLG + "bench_r5", 1, 0 );

}

static void
garden_flowers(void)
{
    add_flower("tulip", ({"scarlet", "red", "crimson",}));
    add_flower("daffodil", "yellow");

    ::garden_flowers();
}

public string
see_pearblossom(void)
{
    string str;

    switch(season)
    {
    case 5..10: /* Tree flowers*/
	str = "The pear blossoms grow individually. They each have five slightly "+
	"spaced, bright white petals with slightly yellow star shape at "+
	"their centers where they also have many thin stamen.\n";
	break;
    default: /* No flowers. */
	str = "The tree is currently blossomless.";
	break;
    }

    return str;
}

public string
see_fruit(void)
{
    string str;

    switch(season)
    {
    case 5..7: /* Tree flowers/grows young fruit. */
	str = "The pears are tiny, hard and green. They are just beginning "+
	"to grow and don't look at all appetizing.";
	break;
    case 8..10: /* Autumn. */
	str = "The pears are full and heavy with a faint gloss to their "+
	"honey-colored skin. They look like they would be deliciously "+
	"sweet.";
	break;
    default: /* Tree is dead. */
	str = "The smooth white branches of the pear trees are fruitless.";
	break;
    }

    return str + "\n";
}

public string
see_tree(void)
{
    string str;

    switch(season)
    {
    case 2..4: /* Tree regrows. */
	str = "Their smooth white branches are covered with fluffy looking "+
	"clusters of beautiful white flowers and new leaves have just "+
	"begun to grow.";
	break;
    case 5..7: /* Tree flowers/grows young fruit. */
	str = "The trees each have a narrow crown of glossy green leaves and "+
	"some of their white flowers still remain. Looking closer "+
	"you notice some tiny hard green fruits beginning to grow here "+
	"and there.";
	break;
    case 8..10: /* Autumn. */
	str = "Stunning bronze foliage adorns their branches, almost shining "+
	"in the Sourcelight and heavy, honey-colored pears peak out.";
	break;
    default: /* Tree is dead. */
	str = "The branches are presently bare, focusing attention on their "+
	"lovely, smooth, white bark.";
	break;
    }

    return "Three small pear trees form an angle, mirroring the white "+
    "flagstone path as it curves its way around the Ziggurat. "+ str + "\n";
}
