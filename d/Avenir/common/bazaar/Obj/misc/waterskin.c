/* A waterskin made by Glinda, may-95. */
/* Thanks to Grace for making it recoverable, dec-95 */
/* August-07 Updated by Zielia and Lucius to make it more useful  
/* and less spammy */
#pragma strict_types
inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

#define TP	this_player()
#define TO	this_object()
#define ENV	environment

private static int level = 25000;


private int
query_water(void)	{ return (level ? 1 : 0); }

public void
create_object(void)
{
    set_keep(1);
    set_name(({"waterskin", "skin"}));
    set_short("waterskin");
    set_long("A large waterskin made from leather. You can drink " +
      "from it. It can also be refilled with water at a suitable " +
      "place. The waterskin is " + "@@query_level_desc@@" + "\n");

    add_prop(OBJ_I_VALUE,   230);
    add_prop(OBJ_I_VOLUME, 5500);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_CONTAIN_WATER, query_water);
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

public string
query_level_desc(void)
{
    switch(level)
    {
    case 1..5000:
	return "almost empty.";
    case 5001..10000:
	return "less than half full of water.";
    case 10001..15000:
	return "half full of water.";
    case 15001..20000:
	return "more than half full of water.";
    case 20001..25000:
	return "full of water.";
    default:
	return "empty.";
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
	write("You refill your "+ short() +".\n");
	say(QCTNAME(TP) + " refills " + TP->query_possessive() +
	    " "+ short() +".\n");

	level = 25000;
	return 1;
    }

    notify_fail("You cannot refill your "+ short() +" here.\n");
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

    /* We'll empty the skin. */
    if (capacity > level)
	capacity = (level); //Was there a reason this was level - 1?
			    //Because it wasn't emptying the skin then...
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
