/* Creator: Ibun
 * Revised by: Lilith, June 2004
 * 	Lucius, Jun 2017: Misc fixes
 */
#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/room";

object rowboat;
int grapling_iron = 0;
int oars = 0;

void
create_room()
{
    set_short("Inside the boathouse");
    set_long("This is a boathouse, built in the same style as the "+
      "manor house, but in a smaller scale. Time seems to have been "+
      "kinder to this place, or perhaps it simply gets more use and "+
      "thus lacks the neglected air of the rest of the farm. You "+
      "stand on a short jetty with spaces for two small rowing " +
      "boats. The slips are separated with a thick wooden beam " +
      "that rest on a chest of stones at the end to the lake. " +
      "The lake isnt very visible from here because of the high " +
      "and thick growing reed, but you can probably escape through " +
      "the reed out on the lake if you try to row in that direction. " +
      "You cast an eye on the walls and notice they are covered with " +
      "old nets hung to dry on wooden pins and a variety of old fishing " +
      "equipment stored in a heap on the floor.\n");
    add_item(({"ceiling", "rafters", "cobweb", "cobwebs"}),
      "You look up at the ceiling but there is nothing " +
      "up there but exposed rafters draped in the occassional " +
      "cobweb.\n");
    add_item(({"nets","net","landing net"}),"You take an old net in " +
      "your hand from its pin and and realise it has been used for the last time. " +
      "There are large tears everywhere and it seems ready to fall " +
      "apart any minute now.\n");
    add_item(({"equipment","fishing equipment","old fishing equipment","heap"}),
      "The fishing equipment consists of long fishing poles, " +
      "landing nets, strings and lots of other items.\n");
    add_item(({"strings","string"}),"You take a string in your hand " +
      "and smell the mixed smell of tar and sea. Now its in a poor " +
      "state and you wouldnt use it for anything important unless " +
      "you had to.\nYou enjoy the smell again before throwing it " +
      "away.\n");
    add_item(({"pins","wooden pins"}),"@@desc_pins");
    add_item(({"poles","fishing poles"}),"You look at fishing poles " +
      "that are hung along the walls on small wooden pins. " +
      "They seem to be in a not so good shape, so if you wanted " +
      "to fish you must find a pole somewhere else.\n");
    add_item(({"beam", "wooden beam"}),
      "The wooden beam divides the moorage into two slips. " +
      "Close to the opening in the wall is a large chest of " +
      "stones in the water that the beam rest on.\n");
    add_item(({"blocks","chest","chest of stones"}),"The chest of stones " +
      "is only a pile of stone blocks put in the water to stabilize " +
      "the boat house and the wooden beam that separates the slips.\n");
    add_item(({"wall","walls"}),"Here and there light passes through " +
      "these walls. Apart from that they seem to be in a pretty good " +
      "shape. The wall towards the lake has a big opening without " +
      "any doors to allow the boats from leaving and returning to " +
      "the boat house. You feel the breeze coming through the " +
      "opening. It caresses your cheek.\n");
    add_item(({"slip", "slips"}),
      "The slips are berths for tying up small boats.\n");
    add_item("jetty", "The jetty is made of wood. One could say it is " +
      "a typical jetty inside a boathouse. But what is typical " +
      "for a jetty in these days?\n");
    add_item("opening","In the eastern wall is a big opening towards " +
      "the lake that allows boats from leaving and returning to the " +
      "boathouse. In the water right at the opening is a " +
      "chest of stones.\n");
    add_item("water","You bend down and stick a hand into the water.\n" +
      "Brrrr. Its freezing cold and you are lucky you are not one of " +
      "all the small fishes you can see swimming around in the water " +
      "inside the boathouse.\n");
    add_item(({"fish","fishes"}),"When glancing down in the water you " +
      "spot several small fishes swimming in the shadows from the " +
      "boathouse. They probably take shelter from the sun during " +
      "daytime.\n");
    add_item("boathouse","@@long");

    add_prop(OBJ_S_SEARCH_FUN, "search_eq");
    add_prop(BH, 1);
    set_terrain(TERRAIN_RESIDENCE);
    add_exit("track3","out");
    add_exit("lake4.1","lake", "@@lake");
    rowboat = clone_object(THIS_DIR + "boat");
    rowboat->move(TO, 1);

    setuid();
    seteuid(getuid());

    reset_room();
}

void
reset_room()
{
    if (sizeof(FILTER_PLAYERS(all_inventory(TO))))
	return;

    grapling_iron = 0;
    oars = 0;
    add_item("oars","@@desc_oars");
}

int
get_oars(string str)
{
    if (strlen(str) && (str == "oars"))
    {
	if (oars == 0)
	{
	    object obj = clone_object(THIS_DIR + "obj/oars");
	    obj->move(this_player(), 1);
	    write("You take the pair of oars from its wooden pins.\n");
	    say(QCTNAME(TP) + " gets a pair of oars from the wooden pins.\n");
	    oars = 1;
	    remove_item("oars");
	    return 1;
	}
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(get_oars,"get");
    add_action(get_oars,"take");
}

string
search_eq(object player, string str)
{
    object ob;


    switch (str)
    {
    case ("equipment"):
    case ("heap"):
    case ("fishing equipment"):
	if (!(grapling_iron))
	{
	    ob = clone_object(THIS_DIR + "obj/grappling");
	    ob->move(TP, 1);
	    grapling_iron = 1;
	    return "You find "+LANG_ASHORT(ob)+".\n";
	}
    default:
	return "";
    }
}

string
desc_oars()
{
    if (!(oars))
	return "Its a pair of oars lying on the wooden pins.\n";
    return "";
}

int
lake()
{
    if ((ENV(TP)) == TO)
    {
	write("You decide to take a swim into the lake. Before you " +
	  "do so, you bend down and dip your hand into the water. " +
	  "This was a wise move as the water is freezing cold and " +
	  "a swim in the water would undoubtly end up very quick, " +
	  "one way or the other.\n");
	return 1;
    }
    return 0;
}

string
desc_pins()
{
    string text = "Small wooden pins are sticking out from the wall " +
	"to hang or place various items on. ";

    if (!(oars))
	text += "There is a pair of oars lying on the pins.";

    return text + "\n";
}

string
desc_water()
{
    return "Inside the boat house are several small fishes " +
	"swimming around. Most likely they seek shelter in " +
	"here from the sun.\n";
}
