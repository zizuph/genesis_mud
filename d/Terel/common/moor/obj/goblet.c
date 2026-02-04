/* Lilith, Jan 2022
 * This goblet is a treasure item in the safe/chest,
 * Its basically a red-herring, for now anyway.
 * The code for this comes from the waterskin in Avenir.
 */
#pragma strict_types
inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

#define TP	this_player()
#define TO	this_object()
#define ENV	environment

private static int level = 0;

private int
query_water(void)	{ return (level ? 1 : 0); }

public void
create_object()
{
    set_name("goblet");
    add_name("_terel_safe_goblet");
    add_name(({"cup"}));
    set_adj(({"golden", "bronze", "orichalcum", "ancient", "dragon"}));
	set_short("orichalcum goblet");
    set_long("This is an ancient goblet made from orichalcum, an alloy of "+
        "copper and gold. It is a tarnished golden color. The soft metal is "+
        "dented in a few spots, but overall in good condition, given its "+
        "age. The stem of the goblet is thick but obviously hollow. The "+
		"bowl of the goblet is large enough to hold half a litre or so. "+
        "Around the rim of the goblet is embossed a series of dragons with " +
        "stars above them and crescent moons between. @@query_level_desc@@\n");
    set_keep(1);
    add_prop(OBJ_I_CONTAIN_WATER, query_water);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_VOLUME, 500);
    add_prop(CONT_I_WEIGHT, 250);
    add_prop(CONT_I_MAX_WEIGHT, 500);
    add_prop(OBJ_I_VALUE, 600); // approx 4 gc.

    add_item(({"dent", "dents", "scratches" }), 
        "The soft gold metal surface of the goblet has various dents and "+
        "scratches accrued over the centuries.\n");
    add_item(({"orichalcum", "metal", "tarnish", "tarnished metal"}), 
	    "The metal of the goblet is an "+
        "ancient alloy of gold and copper, called orichalcum.\n");
    add_item(({"dragon", "dragons", "star", "stars", "moons", "crescent moon",
        "rim", "embossing"}),
        "There are seven dragons on the rim of the goblet, each with a star "+
        "above. Between each dragon is a crescent moon.\n");	
		
}

public string
query_level_desc(void)
{
    switch(level)
    {
    case 1..100:
	return "It is almost empty.";
    case 101..200:
	return "It is about a quarter full of water.";
    case 201..300:
	return "It is about half full of water.";
    case 301..400:
	return "It is about three-quarters full of water.";
    case 401..500:
	return "It is full of water.";
    default:
	return "";
    }
}

public int
do_empty(string str)
{
    object *obs;

    if (!strlen(str))
    {
	notify_fail("Empty what?\n");
	return 0;
    }

    if (!parse_command(str, TP, "[the] %i", obs) ||
	!sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))
    {
	notify_fail("Empty what?\n");   
	return 0;
    }

    if (sizeof(obs) != 1)
    {
	notify_fail("You can only empty one at a time.\n");
	return 0;
    }

    if (obs[0] != TO)
	return 0;

    if (!level)
    {
	notify_fail("The "+ short() +" is already empty.\n");
	return 0;
    }

    write("You empty your "+ short() +". The water rapidly soaks into " +
	"the ground.\n");
    say(QCTNAME(TP) + " empties " + TP->query_possessive() +
      " "+ short() +". The water rapidly soaks into the ground.\n");

    level = 0;
    return 1;
}

public int
do_refill(string str)
{
    object *obs, obj;

    if(!strlen(str))
    {
	notify_fail("Refill what?\n");
	return 0;
    }   

    if (!parse_command(str, TP, "[the] %i", obs) ||
	!sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))
    {
	notify_fail("Refill what?\n");	   
	return 0;
    }

    if (sizeof(obs) != 1)
    {
	notify_fail("Please try with one at a time.\n");
	return 0;
    }

    if (obs[0] != TO)
	return 0;

    int rtype = ENV(TP)->query_prop(ROOM_I_TYPE);

    if (ENV(TP)->query_prop(OBJ_I_CONTAIN_WATER) ||
	rtype == ROOM_BEACH || rtype == ROOM_IN_WATER ||
	rtype == ROOM_UNDER_WATER)
    {
	write("You fill your "+ short() +" with water.\n");
	say(QCTNAME(TP) + " fills " + TP->query_possessive() +
	    " "+ short() +" with water.\n");

	level = 500;
	return 1;
    }

    notify_fail("You cannot fill your "+ short() +" here.\n");
    return 0;
}

// do_drink uses while loops so players can drink a lot without lots of 
// spam.

public int
do_drink(string str)
{
    object *obs;

    if (!strlen(str))
    {
	notify_fail("Drink from what?\n");
	return 0;
    }   

    if (!parse_command(str, TP, "'from' [the] %i", obs) ||
	!sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))
    {
	notify_fail("Drink from what?\n");	   
	return 0;
    }

    if (sizeof(obs) != 1)
    {
	write("You can only drink from one at a time.\n");
	return 1;
    }

    if (obs[0] != TO)
	return 0;

    if (!level)
    {
	write("But the "+ short() +" is empty!\n");
	return 1;
    }

    int max = TP->drink_max();
    int capacity = max - TP->query_soaked();
    int lim = max / 15;

    /* Not thirsty. */
    if (capacity < 1)
    {
	write("You cannot drink anymore water!\n");
	say(QCTNAME(TP) +" tries to drink from "+ TP->query_possessive() +
	    " "+ short() +", but fails.\n");

	return 1;
    }

    /* We'll empty it. */
    if (capacity > level)
	capacity = (level); 

    /* Guzzle all we can. */
    while (capacity >= lim)
    {
	TP->drink_soft(lim, 0);
	level    -= lim;
	capacity -= lim;
    }

    /* Top us off. */
    if (capacity)
    {
	TP->drink_soft(capacity, 0);
	level -= capacity;
	capacity = 0;
    }

    if (level > 0)
    {
	/* Leftovers. */
	write("You drink from the "+ short() +" until you " +
	    "can't drink another drop.\n");
    }
    else
    {
	/* Empty. */
	level = 0;
	write("You drink from the "+ short() +" until its empty.\n");
    }
	
    say(QCTNAME(TP) +" drinks from "+ TP->query_possessive() +
	" "+ short() +".\n");

    return 1;
}

public void
init(void)
{
    ::init();

    if (this_player() != ENV())
	return;

    add_action(  do_drink, "drink"  );
    add_action( do_refill, "refill" );
    add_action( do_refill, "fill"   );
    add_action(  do_empty, "empty"  );
}

public string
query_recover(void)
{
    return MASTER + ":#LVL#"+ level +"#"+ query_keep_recover();
}

public void
init_recover(string arg)
{
    init_keep_recover(arg);
    sscanf(arg, "%s#LVL#%d#%s", arg, level, arg);
}
