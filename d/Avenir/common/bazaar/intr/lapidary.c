// file name:   /d/Avenir/common/bazaar/intr/lapidary.c
// creator(s):  Lilith, 20 Sep 1997
// revised:     Lilith, 27 Dec 1997
//              Manat, 18 Sep 2000 - removed buy_it in favor for the
//              standard /std/shop version
//              Lucius, Mar, 2007: Removed useless code and cruft.
//                 Cleaned up; added new bits.
//              Lucius, Aug, 2011: Updated for modified shop_list.
// purpose:     Buy and sell gems
// note:
// bug(s):
// to-do:

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/d/Avenir/inherit/shop";

#include "../bazaar.h"
#include "/d/Avenir/include/relation.h"

#define STRM   (INTR + "lapstore")

public void
reset_room(void)
{
    fix_keeper();
}

public void
create_room(void)
{
    setuid();
    seteuid(getuid(TO));    

    set_maxlist(50);
    set_store_room(STRM);
    set_keeper_file(NPC + "imlis");

    set_short("Sybarus Bazaar Lapidary Shop");
    set_long("This room has been carved into solid basaltic stone "+
      "that gleams a dull reddish black. There is a worktable here, "+
      "with lamps and mirrors that focus light into a lens. Tools "+
      "designed for cutting facets into minerals of varying hardness "+
      "are laid out on the table, alongside calipers and a fine scale. "+
      "A banner hangs from the wall above a modest glass-topped case "+
      "which displays those gems and jewels available for sale. The "+
      "banner appears to have had some newly stitched text added to it.\n");
    add_item(({"sign", "banner"}), "@@exa_sign");
    add_cmd_item(({"sign", "script", "banner", "wall"}), "read", 
      "@@exa_sign"); 
    add_item(({"case", "display case", "modest case", "glass case" }),
      "@@do_case");
    add_item(({"lamps", "mirrors", "lens", "source"}), 
      "The lamps hold glowing bits of crystal whose light is captured "+
      "and intensified by the mirrors. The light falls in a pool on the "+
      "workbench, where the gemcutter's lens lies.\n");
    add_item(({"tools", "calipers", "scale"}), 
      "These are the tools of a gemcutter's trade, finely and precisely "+
      "crafted.\n");
    add_item(({"table","work table","worktable","work bench","workbench"}), 
      "A high, matte-finish stone table that the gemcutter works at.\n");
    add_item(({"floor","stone","basalt","ground","walls"}),
      "It has been quarried from a cubic formation of basalt, a dark "+
      "stone with a rusty-red tint.\n");         

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


    add_exit(EXTR + "str21", "north", 0);
    add_exit(STRM, "storeroom", "@@check_store@@", 1, 1);

    config_shop();
    fix_keeper();

    /* Taken from /d/Genesis/gems/gem_shop.c */
    set_money_give_max(100000);
    set_money_give_out(   ({  100,  100,  1000, 100 }));
    set_money_give_reduce(({    0,     2,    4,  50 }));
}

public int
check_store(void)
{
    if (TP == keeper)
	return 0;

    return !(TP->query_wiz_level());
}

public void
init(void)
{
    ::init();
    init_shop();
}

public string
exa_sign(void)
{
    return "\nWelcome to Sybarus Bazaar Lapidary Shop!\n"+
    "\n          Highest Quality        \n"+
    "\n        Gemstones and Jewels     \n"+
    "\n        Bought and Sold Here.    \n"+
    "\n        ~~~~~~~~~~~~~~~~~~~~~      "+
    "\n      Now selling money-purses!  \n"+
    "\n        ~~~~~~~~~~~~~~~~~~~~~    \n";
}

public string
do_case(void)
{    
    write("You stare through the thick glass.\n");
    do_list("all");
    return "";
}

private void
shop_filter(object ob)
{
    return ob->query_gem();
}

public int
shop_hook_allow_sell(object ob)  
{
    if (IS_INFIDEL(TP))
    {
	keeper_speak("I do not trade with criminals.");
	return 0;
    }

    if (!shop_filter(ob))
    {
	if (ob->id("gem") || ob->id("jewel"))
	    keeper_speak("I don't traffic in phony jewels.");
	else
	    keeper_speak("I'm sorry, I do not trade in anything but jewels.");

	return 0;
    }

    if (ob->query_value() > money_give_max)
    {
	if (ob->num_heap() > 1)
	{
	    keeper_speak("I'm afraid I cannot afford to pay that much.");
	    keeper_speak("Perhaps you could try selling the "+
		ob->short() +" individually.");

	    return 0;
	}

	keeper_speak("I'm afraid I cannot afford to pay the full value.");
    }

    return 1;
}

public void
shop_hook_value_not_interesting(object ob)
{
    /* Kept gems have the NO_SELL prop... */
    if (shop_filter(ob) && ob->query_keep())
    {
	keeper_speak("I cannot value that item, "+
	    "try 'unkeeping' it first."); 
    }
}

public string
categorize(object ob)
{
    return "Gems";
}

public varargs string
query_object_desc(object obj, int phase)
{
    if (phase)
	return obj->singular_short();
    else
	return obj->query_name();
}
