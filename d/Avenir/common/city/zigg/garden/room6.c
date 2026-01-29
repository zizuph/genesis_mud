// Ziggurat Garden (room6.c)
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

    add_exit("room7", "east", "@@exit_string");
    add_exit("room5", "west", "@@exit_string");
}

public string
my_long(void)
{
    string str;

    switch(season)
    {
    case 2..4: /* Tree flowers. */
	str = " and create a soft, romantic fountain of pale pink blossoms. ";
	break;
    case 5..7: /* Tree flowers/grows young fruit. */
	str = " covered with shiny green leaves that nearly brush the ground. ";
	break;
    case 8..10: /* Autumn. */
	str = " covered with striking maroon leaves that nearly brush the ground. ";
	break;
    default: /* Tree is dead. */
	str = " cascading nearly back to the ground. ";
	break;
    }

    return "Curved beds of blood-red peonies surround the weeping cherry "+
    "tree at the center of this arbor. Twisting red-black limbs turn into "+
    "arching, drooping branches"+ str +"The white-flagstone garden path meanders "+
    "east to west, curving south of the cherry tree, through the well-raked "+
    "soil and past a cast iron bench placed here for passersby wishing to "+
    "rest a moment and enjoy this enchanting grove with its scenic view.\n";
}

public string query_trees(void) {   return "cherry tree";    }

static void
garden_items(void)
{
    ::garden_items();

    add_views("From this side of the Ziggurat you can see some of the "+
      "High Lord Inquisitor's enclave to the northwest, opulent noble "+
      "houses circle the High Lord's palace on the central hill.",
      "enclave, giving it");

    add_rock("a red spiral as though painted by a bloody finger",
      ", the symbol of Aclolthayr");

    add_ground("The ground of the terrace is made of flat, rich soil, "+
      "raked so it is soft and free of debris.");

    add_item(({"tree","weeping tree","cherry tree","weeping cherry tree",}),
      "@@see_tree");

    add_item(({"cherry","cherries","fruit","fruits",}), "@@see_fruit");

    add_item(({"cherry blossom","cherrie blossoms","cherry flower",
	"cherry flowers",}), "@@see_cherryblossom");

    add_fruit("cherry");

    add_object(ZIG_RLG + "bench_r6", 1, 0 );

}

static void
garden_flowers(void)
{
    add_flower("peony", "blood red");

    ::garden_flowers();
}

public string
see_cherryblossom(void)
{
    string str;

    switch(season)
    {
    case 5..10: /* Tree flowers*/
	str = "The cherry blossoms grow in umbrels, a single blossing at the "+
	"end of a long stalk. They each have five well defined petals "+
	"and are a pale pink color.\n";
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
    case 2..4: /* Tree flowers. */
	str = "The cherry tree is covered with deep pink blossoms but you "+
	"don't see any fruit yet.\n";
	break;
    case 5..7: /* young fruit.. */
	str = "The cherries are young and many are still small. They are round, "+
	"with a depression at the apex where they hang in clusters from "+
	"long stalks. They are a bright red color with smooth, glossy "+
	"skin.\n";
	break;
    case 8..10: /* Autumn*/
	str = "The cherries are very ripe and plump. They are round, "+
	"with a depression at the apex where they hang in clusters from "+
	"long stalks. They are a dark red color, almost black, with "+
	"smooth, glossy skin.\n";
	break;
    default: /* Tree is dead. */
	str = "The glossy, red-black branches of the cherry tree are fruitless.\n";
	break;
    }

    return  str;
}

public string
see_tree(void)
{
    string str;

    switch(season)
    {
    case 2..4: /* Tree flowers. */
	str = "The branches are covered with umbrels of beautiful, light pink "+
	"blossoms that look soft and almost dreamlike on the end of of "+
	"their long stocks. A few young leaves grow near the flowers, "+
	"looking reddish as they open but will later age to a shiny "+
	"dark green.";
	break;
    case 5..7: /* Tree has leaves/grows young fruit. */
	str = "The branches are covered with long, droopy leaves that are "+
	"shiny, dark green and have a finely toothed edge. Few flowers "+
	"remain, replaced by the beginnings of small, bright red fruits "+
	"hanging in clusters by long stocks.";
	break;
    case 8..10: /* Autumn. */
	str = "The branches are covered with long, droopy leaves that have "+
	"begun to change from a dark green to a striking maroon color. "+
	"The fruit which remains clustered on the branches has changed "+
	"to a deep red, nearly black.";
	break;
    default: /* Tree is dead. */
	str = "The branches are presently bare, the dark wood a stark "+
	"contrast to the irridescent Source above.";
	break;
    }

    return "The red-black limbs of the tree twist upward in all directions, "+
    "many twisting and crossing before they arch, cascading back downward "+
    "to nearly brush the ground.  "+ str + "\n";
}
