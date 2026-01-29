// Bottle        (/d/Avenir/common/bazaar/NPC/waiter.c)
// creator(s):    Glinda may -95
// last update:   Lilith Oct 2021: modified the fishing function. 
//                    got a couple of complaints about being unable
//                    to get the bottle.
// purpose:       A net. U can fish with it.
//
// note:
// bug(s):
// to-do:

inherit "/std/container";


#include <stdproperties.h>
#include "/d/Avenir/common/common.h"

object bottle;
object boot;

void
create_container()
{
    if (!IS_CLONE)
	return;

    set_name ("net");
    set_short ("fishing net");
    set_adj("fishing");
    set_long("A long pole with a circular frame at one end. A net is " +
      "attached to the pole making it a good device for fishing "+
      "from the deck of a boat.\n");
    add_prop (CONT_I_WEIGHT, 4500);
    add_prop (CONT_I_VOLUME, 6000);
    add_prop (OBJ_I_VALUE, 250);
    add_prop (CONT_I_MAX_WEIGHT, 10000);
    add_prop (CONT_I_MAX_VOLUME, 11000);
    add_prop (CONT_I_TRANSP, 1);
    add_prop (CONT_I_RIGID, 0);
    seteuid(getuid());
}

init()
{
    add_action("do_fish","fish");
    ::init();
}

do_fish(string str)
{
    object ob;

    if(!(str == "with net"))
    {
	NF("Fish with what?\n");
	return 0;
    }
    if(!( function_exists("create_deck",ENV(TP)) ))
    {
	NF("Maybe you should try that somewhere else?\n");
	return 0;
    }
    if(!(sizeof(all_inventory(TO))==0))
    {
	NF("Maybe you should empty it first?\n");
	return 0;
    }
    if(!(ENV(TO)==TP))
    {
	NF("But you don't have the net.\n");
	return 0;
    }
    if(TP->query_fatigue()<6)
    {
	NF("You are too tired to do that.\n");
	return 0;
    }
    if (str == "with net")
    {
	TP->add_fatigue(-6);
	say(QCTNAME(TP) + " bends over the railing and tries to catch " +
	  "something with " + TP->query_possessive() + " net.\n");
	write("You lean over the side and try to fish with the net.\n");
	TP->add_prop("_has_fished_with_avenir_net",1);
    }
    switch(random(10))
    {
    case 0..4:
	{	
	    write("Your net comes up empty. No luck this time.\n"); 
	    return 1;
	}
    case 5..7:
	{
	    write("You've caught something!\n");
	    ob=clone_object(BAZAAR + "Obj/food/net_fish");
	    ob->move(TO);
	    return 1;
	}
    case 8:
	if(!TP->query_prop("_glinda_fished_boot"))
	{
	    write("You've fished something up out of the water...\n");
	    boot=clone_object(BAZAAR + "Obj/worn/net_boot");
	    boot->move(TO);
	    TP->add_prop("_glinda_fished_boot", 1);
	    return 1;
	}
    case 9:
	if (!TP->query_prop("_glinda_fished_bottle"))
	{
	    write("Something different snags in the net.\n");			 
	    bottle=clone_object(BAZAAR + "Obj/misc/net_bottle");
	    bottle->move(TO);
	    TP->add_prop("_glinda_fished_bottle", 1);
	    return 1;
	}
    default: write("Your net comes up empty.\n"); 
	return 1;			
    }		
    return 1;
}

