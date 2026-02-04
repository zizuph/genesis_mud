/*
 * Farm2h.c   Tomas  -- Jan 2000
 *
 * Lucius - Feb 2021
 *    Cleaned and modernized.
 */
#include "farm.h"
inherit FARMRM;

public string
check_see()
{
    string str;

    if (!TP->query_prop("_terel_i_found_it"))
	str = "You find no trapdoor.";
    else
	str = "It is a very cleverly made trapdoor, hidden under the strewn hay "+
            "and mess of chicken feathers and waste.";

    return str +"\n";
}

public void
create_terel_room()
{
    INSIDE;
    set_short("chicken coop");
    set_long("You stand inside a filthy chicken coop. A tarp has been " +
      "pulled over the top of the coop creating a makeshift roof. The " +
      "ground is covered in hay and down feathers. A gated exit leads " +
      "outside.\n");

    add_item(({"gate","fence","coop"}),
      "The coop is made from wire woven together to create a strong " +
      "barrier keeping unfriendly animals out and the chickens in. " +
      "There is a small meshed gate before you.\n");

    add_item(({"tarp", "canvas tarp", "roof"}),
      "The canvas tarp provides shelter for the " +
      "chickens.\n");

    add_item(({"floor","ground","feathers","hay","down feathers"}),
      "Someone spread out a thick layer of hay for the chickens " +
      "to lay down on. The hay is mixed with various sized " +
      "feathers.\n");

    add_item("trapdoor", "@@check_see");

    add_cmd_item(({"door","trapdoor","trap door"}),
      ({"lift","open"}),"@@trapdoor");

    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "search_ground");

    room_add_object(CFARMS + "obj/farm2g_gate1");
    add_npc(CFARMS + "monsters/chicken", 8);
}

string
search_ground(object player, string str)
{
    switch (str)
    {
    case "floor":
    case "ground":
    case "feathers": 
    case "hay":
    case "down feathers":
    case "chicken feathers":
    case "waste":
	{
	    player->add_prop("_terel_i_found_it", 1);
	    /* I get some general experience for succeeeding */
	    player->add_exp_general(100 + random(50));
	    say(({METNAME + " begins methodically searching the ground "+
                     "of the chicken coop.\n",
                  TART_NONMETNAME + " begins methodically searching the "+
                     "ground of the chicken coop.\n"}), TP);
	    return "Your methodical search through the hay, feathers "+
                "and waste on the ground pays off when your fingertips "+
                "brush what appears to be a trapdoor.\n";
	}
    default:
	return "";
    }
}

public mixed
trapdoor()
{
    if (!TP->query_prop("_terel_i_found_it"))
    {
	write("Where is it, exactly, in this mess?\n");
	return 1;
    }

    write("You lift open the trapdoor and climb down.\n");
    say(QCTNAME(TP) + " rustles around in the hay and then suddenly disappears.\n");
    tell_room(CALATHIN_DIR + "tunnel/tunnel_11b", QCTNAME(TP) +
        " climbs through a trapdoor in the ceiling. "+
        "Then closes it behind "+ HIM_HER +".\n");
    TP->move_living("M",CALATHIN_DIR + "tunnel/tunnel_11b",1,0);
    return 1;
}
