// Ziggurat galleria (room8.c)
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"
#include <macros.h>

inherit ZIG_GARDEN;

public void
zig_room(void)
{
    /* Avtime events. */
    AVTIME->add_event(this_object());
    season = AVTIME->get_avenir_week();

    set_long("Pink and cream star-shaped lilies spring from beds against the "+
      "corner railing of this arbor. The soothing melody of trickling water "+
      "drifts from the narrow aqueduct. A large peach tree stands near the "+
      "flagstone path next to a thick patch of grass that looks as though "+
      "it would be a favored spot to sit and enjoy the fragrant flowers "+
      "and perhaps even a ripe peach.\n");

    add_exit("room9", "south", "@@exit_string");
    add_exit("room7", "west", "@@exit_string");
}

static void
garden_items(void)
{
    ::garden_items();

    add_views("From this side of the "+
      "Ziggurat you can see some of the High Lord Executioner's enclave "+
      "to the north and east, opulent noble houses circle the High Lord's "+
      "palace on the central hill.", "enclave, giving it");

    add_rock("carved an odd rectangular shape reminiscent of a loaf of "+
      "bread", ", the symbol of Sabrus");

    add_item(({"tree","peach tree","large tree","large peach tree",}),
      "@@see_tree");

    add_item(({"peach","peaches","fruit","fruits",}), "@@see_fruit");

    add_item(({"peach blossom","peach blossoms","peach flower",
	"peach flowers",}), "@@see_peachblossom");

    add_fruit("peach");

    add_object(ZIG_RLG + "grass_r8", 1, 0 );

    remove_item("grass");

}

public string query_trees(void) {   return "peach tree";    }

static void
garden_flowers(void)
{
    add_flower("lily", ({"pink", "cream"}));

    ::garden_flowers();
}

public string
see_peachblossom(void)
{
    string str;

    switch(season)
    {
    case 5..10: /* Tree flowers*/
	str = "The peach blossoms grow in pairs. They each have five well "+
	"defined petals which curve toward a bowl-like shape. Their "+
	"centers are a deeper pink than the outer part of the petals, "+
	"with many pink tipped filiaments.\n";
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
	str = "The peaches are tiny, hard and green. They are just beginning "+
	"to grow and don't look at all appetizing.";
	break;
    case 8..10: /* Autumn. */
	str = "The peaches are full and heavy with velvety rose-kissed, peach "+
	"skin. They look like they would be sweet and juicy.";
	break;
    default: /* Tree is dead. */
	str = "The branches of the peach tree are fruitless.";
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
    case 2..4: /* Tree flowers. */
	str = "The branches are covered with hundreds of deep pink blossoms "+
	"adorned sparsely by fresh, young leaves which have just begun "+
	"to grow.";
	break;
    case 5..7: /* Tree grows leaves/young fruit. */
	str = "The tree branches are covered by long, glossy green leaves and "+
	"and a few remaining pink flowers. Looking closer you notice some "+
	"tiny, round, fuzzy, greenish fruits just beginning to grow.";
	break;
    case 8..10: /* Autumn. */
	str = "Thick green leaves seem heavy on its branches, almost drooping "+
	"from their numbers but still glossy beneath the sourcelight. "+
	"Large, round peaches peek out from clusters of the leaves.";
	break;
    default: /* Tree is dead. */
	str = "The branches are presently bare, reaching like skeletal fingers "+
	"toward the source.";
	break;
    }

    return "A large peach tree stands near the flagstone path next to a "+
    "thick patch of grass. "+ str + "\n";
}
