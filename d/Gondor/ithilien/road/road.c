/*
 *	/d/Gondor/ithilien/road/road.c
 *
 *	Olorin, 1997
 *
 *	Copyright (c) 1997 by Christian Markus
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define LOOKOUT		(ITH_DIR + "nforest/lookout")

static int     move_alarm;
static string  patrol_dir = "north";

public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
move_patrol(object ob)
{
    move_alarm = 0;
    ob->command(query_patrol_dir(ob));
}

public void
enter_inv(object ob, object from)
{
    string  npc_name = ob->query_real_name();
    ::enter_inv(ob, from);

    if (TO->query_lookout_message())
    {
        if (living(ob))
            LOOKOUT->enter_road(ob,from);
    }
    if ((npc_name == "haradrim captain") &&
        (!move_alarm || !sizeof(get_alarm(move_alarm))))
        move_alarm = set_alarm(20.0 + rnd() * 40.0, 0.0, &move_patrol(ob));
}

void
stand_to_fight()
{
    if (move_alarm)
        remove_alarm(move_alarm);
}

void
continue_patrol(object ob)
{
    if (move_alarm && sizeof(get_alarm(move_alarm)))
        return;

    move_alarm = set_alarm(10.0 + rnd() * 20.0, 0.0, &move_patrol(ob));
}

public int
test_exit()
{
    int     stopped;
    object  attacker = TP->query_attack();

    if (present(attacker) && attacker->query_npc())
    {
        stopped = TP->query_stat(SS_DEX) - attacker->query_stat(SS_DEX) + 85;
        if (stopped < 0)
            stopped = 0;
        stopped = 12 - stopped / 10;
        if (stopped < 1)
            stopped = 1;
        if (stopped > 10)
            stopped = 10;
        if (random(stopped)) 
        {
            write("The " + attacker->query_nonmet_name() + " stops you!\n");
            return 1;
        }
    }
    return 0;
}

static void
add_forest(int stage, string extra = 0, string *names =
	   ({ "forest", "wood", "woods", "trees", }) )
{
    string  desc = "";

    switch (stage)
    {
    case 1:
	desc = "A great open forest, with large ilexes of huge girth " 
	     + "standing dark and solemn in wide glades. Here and there "
	     + "among them hoary ash-trees, and giant oaks are putting " 
	     + "out their brown-green buds. About them, long launds of "
	     + "green grass lie dappled with celandine and anemones.";
	break;
    case 2:
	desc = "In the forests to the west of the road many great trees "
	     + "are growing, planted long ago, falling into untended "
	     + "age amid a riot of careless descendants; and groves and "
             + "thickets there are of tamarisk and pungent terebinth, "
	     + "of olive and bay. There are junipers and myrtles; and "
	     + "thymes that grow in bushes, or with their woody creeping "
	     + "stems mantle in deep tapestries the hidden stones.";
	break;
    case 3:
	desc = "Small woods of resinous trees, fir and cedar and cypress "
	     + "and other kinds cover the gentle slopes west of the "
	     + "road. Wide glades are among them, and groves and "
	     + "thickets there are of tamarisk and pungent terebinth, of "
	     + "olive and bay. There are junipers and myrtles; and "
	     + "thymes that grow in bushes, or with their woody creeping "
	     + "stems mantle in deep tapestries the hidden stones.";
	break;
    case 4:
	desc = "Small woods of resinous trees, fir and cedar and cypress "
	     + "and other kinds cover the gentle slopes west of the "
	     + "road. Wide glades are among them, and everywhere there "
             + "is a wealth of sweet-smelling herbs and shrubs.";
	break;
    case 5:
	desc = "All about you lies a tumbled heathland, grown with ling "
	     + "and broom and cornel, and other shrubs you do not know. "
	     + "Here and there knots of tall pine-trees can be seen.";
	if (strlen(extra))
	    desc += " " + extra;
	add_item( ({ "heath", "heathland", "heath land"}), desc + "\n");
	extra = "";

	desc = "On the heathland west of the road one can see knots of "
             + "pine-trees, that are growing more numerous and denser "
             + "towards the south. There fir, cedar, cypress, and "
             + "other resinous trees join the pines.";
	break;
    case -1:
	desc = "West of the road, scattered groups of large trees form " 
	     + "the southern fringes of the forest visible to the north. "
	     + "There are acres populous with woodland hyacinths; and hoary "
	     + "ash-trees and giant oaks stand in wide glades. Close to the "
             + "road, the land is covered with a thick growth of gorse and "
	     + "whortleberry, and low tough thorns. But here and there "
	     + "clearings open, scars of recent fires.";
	add_item(({"clearing","clearings","fire"}), 
            "Thick growth blocks the west of the road blocks your " +
            "passage in that direction in most places, but here and " +
            "there, recent fires tore scars into the vegetation, " +
            "creating clearings that allow you to leave the road.");
	break;
    case -2:
	desc = "West of the road, scattered groups of large trees form " 
	     + "the southern fringes of the forest visible to the north. "
	     + "There are acres populous with woodland hyacinths; and hoary "
	     + "ash-trees and giant oaks stand in wide glades.";
	break;
    }

    if (strlen(extra))
	desc += " " + extra;
    
    if (strlen(desc))
	add_item( names, desc + "\n");
}

static void
add_mountains(int stage, string dist = "only about half a mile", 
	      string extra = 0)
{
    string  desc;

    switch (stage)
    {
    case 1:
	desc = "The mountains named Ephel Duath appear to be dark "
	     + "grey from here. You judge the mountains to be between "
	     + "5000 to 7000 feet tall, and you guess they are "
	     + dist + " away now.";
	break;
    case 2:
	desc = "The southern ranges of the Ephel Duath, the Mountains "
	     + "of Shadow that are the western border of the land of "
	     + "Mordor, are rising in the east.";
    }

    if (strlen(extra))
	desc += " " + extra;
    
    add_item( ({ "mountains", "mountain-range", "mountain",
		 "ephel duath", "east",  }), desc + "\n");
}

static void
add_road(int stage, string extra = 0)
{
    string  desc = "The long straight road runs north towards the Morannon, "
	     + "the Black Gates of Mordor, while in the other direction "
	     + "it goes to the crossroads where it meets the road from "
             + "Osgiliath to Minas Morgul.";

    switch (stage)
    {
    case 1:
	desc = "The long straight road runs north towards the Morannon, "
	     + "the Black Gates of Mordor, while in the other direction "
             + "it goes to a belt of dark trees, where the road from "
	     + "Osgiliath to Minas Morgul crosses this one. From the "
             + "crossroads, this road continues south through South "
	     + "Ithilien to the land of Harad. The road is well "
             + "crafted, cobbled with stones and lined with high banks, "
	     + "but it is not in good repair and overgrown in patches.";
	break;
    case 2:
	desc += " From there, it then " 
             +  "continues through South Ithilien towards the land of "
             +  "Harad. The road is well crafted, cobbled with stones "
             +  "and lined with high banks, but it is not in good repair "
             +  "and overgrown in patches.";
	break;
    case 3:
	desc += " From there, it then " 
             +  "continues through South Ithilien towards the land of "
             +  "Harad. The road is well crafted, cobbled with stones and "
             +  "lined with high banks, but it is in bad repair and almost "
	     +  "completely overgrown.";
	break;
    case 4:
	desc += " The road is well crafted, cobbled with stones and lined "
	     +  "with high banks. To the north, it seems to have been "
             +  "newly repaired, but as it goes south, the wild encroaches "
             +  "on it.";
	break;
    case 5:
	desc += " The handiwork of the Men of old can still be seen in "
             +  "its straight sure flight and level course. The road is "
             +  "well crafted, cobbled with stones and lined with high "
             +  "banks, and has been newly repaired.";
	break;
    case 6:
	desc = "The long road runs south in a straight line to the crossroads "
	     + "where it meets the road from Osgiliath to Minas Morgul, while "
             + "in the other direction, following the mountains which are "
             + "receding eastward here, it leads to the Morannon, the Black "
             + "Gates of Mordor. The road is well crafted, cobbled with "
             + "stones and lined with high banks, and has been newly repaired.";
	break;
    case -1:
	desc = "The long straight road runs north towards the Morannon, " 
	     + "the Black Gates of Mordor. From the crossroads to the north, "
	     + "it continues south through South Ithilien to the land of "
	     + "Harad. The road is well crafted, cobbled with stones and "
             + "lined with high banks, but it is not in good repair and "
	     + "overgrown in patches.";
	break;
    case -2:
	desc = "The long straight road runs north towards the Morannon, the "
	     + "Black Gates of Mordor. Somewhere north of the bridge must be "
	     + "the crossroads with the road from Minas Morgul to Osgiliath. "
	     + "To the south, the road continues through Southern Ithilien "
	     + "to the Crossings of Poros and from there to the land of Harad. "
	     + "The road is well crafted, cobbled with stones and lined with "
             + "high banks, but it is not in good repair and overgrown in "
	     + "patches.";
	break;
    case -3:
	desc = "The long straight road runs north towards the Morannon, the "
	     + "Black Gates of Mordor. Several leagues north of here must be "
	     + "the crossroads with the road from Minas Morgul to Osgiliath. "
	     + "To the south, the road continues through Southern Ithilien to "
	     + "the Crossings of Poros and from there to the land of Harad. " 
	     + "The road is well crafted, cobbled with stones and lined with " 
	     + "high banks, but it is in poor repair and overgrown in patches.";
	break;
    }

    if (strlen(extra))
	desc += " " + extra;

    if (strlen(desc))
	add_item( ({ "road" }), desc + "\n");
}

static void
add_tree_ring(string dir = "south")
{
    string  desc = 
        "To the "+dir+", looming up like a black wall, you can make out a great " +
        "belt of trees. The trees are vast of size, very ancient it seems, and " +
        "still towering high, though their tops are gaunt and broken, as if " +
        "tempest and lightning-blast had swept across them, but had failed to " +
        "kill them or to shake their fathomless roots.";
    add_item(({"trees","ring of trees","belt of trees"}), desc + "\n");
}

static void
add_emyn_arnen(string extra = 0)
{
    string  desc =
    "The green hills west of the road are the hills of Emyn Arnen, the " +
    "land in southern Ithilien that was the home of the House of Hurin, " +
    "the house of the Stewards of Gondor. It rises between the road and " +
    "the Anduin, and was said to be the most beautiful part of Ithilien " +
    "before it fell under the Shadow.";

    if (strlen(extra))
	desc += " " + extra;
    add_item(({"hill", "hills", "emyn arnen"}), desc + "\n");
}
