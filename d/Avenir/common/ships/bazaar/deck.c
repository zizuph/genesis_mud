#pragma strict_types
/*
 * Filename: /d/Avenir/common/ships/bazaar/deck.c
 * Original creator: Kazz on Apr 1995
 * Purpose: Deck of the boat between outpost & islands
 * Last update(s):
 *    Boriska, Sep 1995: Changes in drop command. Correct handling of
 *                       heap objects. Possibility to drop several items.
 *                       Numerous other changes.
 *    Manat, Jul 2000 :  changed coding style and stuff
 *                       moved #include below inherit
 *    Manat, Aug 2000 :  fixed the drop command parse_command() uses split_heap()
 *                       so we need to use restore_heap()
 *                       also changed some variables names
 *    Sirra, Oct 2002 :  Added do_rock()
 *    Zielia, Jun 2009:  Cleanups, added krynn plague removal code.
 *    Lucius, Aug 2010:  Added float landing messages.
 *    Lucius, Jun 2017:  Completely re-wrote item processing.
 */
inherit "/d/Genesis/ship/deck";

#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/macros.h"
#include "ship.h"

#undef DEBUG
#ifdef DEBUG
#  define D(x) find_player("lucius")->catch_tell("DECK DEBUG: " + (x))
#else
#  define D(x)
#endif

public static string *slow_snd = ({
  "Circles of ripples appear beside the boat, then are left behind.\n",
  "The boat slows a bit, then resumes drifting over the sea.\n",
  "The boat coasts silently across the great sea.\n",
});

public static string *fast_snd = ({
  "The boat moves fast ahead, leaving behind a trail of white foam.\n",
  "The boat lunges forward momentarily, then glides along the water.\n",
  "You feel the boat being pulled fast ahead and almost fall overboard.\n"
});


/*
 * Function name: create_deck
 * Description  : the creator function of the deck
 */
public void
create_deck(void)
{
    /* room description */
    set_short("on the boat");
    set_long("This sturdy wooden boat doesn't have any oars or sails. " +
      "It floats high on the calm water, bobbing slightly " +
      "in the water. A wooden seat is built into the hull, " +
      "looking well made and even comfortable. Perhaps " +
      "you can sit on it to rest your legs.\n");

    /* room settings */
    /* why not use the IN define? nonstandard is even worse than obsolete */
    add_prop(ROOM_I_INSIDE, 1);

    /* deck and bump sounds depend on creature's food state. */
    set_deck_sound("@@sounds");
    set_bump_sound("@@bump_sound");

    /* room items */
    add_item(({ "boat", "wooden boat" }),
      "The boat looks well constructed, made of thick, dark wood, " +
      "too thick really to be called planks.\n" );
    add_item(({"seat","seats", "wooden seat", "wooden seats"}), 
      "The wooden seats are smooth and carved for comfort.\n");
    add_item(({ "water", "calm water" }),
      "The water is glassy smooth and very clear. At the front of " +
      "the boat, beneath the surface, you see a long grey creature.\n");

    /* creature description depends on its food state. */
    add_item(({ "creature", "grey creature" }), "@@describe_creature" );

    /* wiz info. Is this needed? */
    add_prop(OBJ_S_WIZINFO,
      "This boat has no visible captain, and is pulled from beach " +
      "to beach by an underwater creature. This creature must be " +
      "fed by the player to make it move without a huge delay. " +
      "Feeding occurs by dropping food in the water.  Examining the " +
      "creature from the deck will give a clue as to its current " +
      "state.  If enough food is dropped into the water, the boat " +
      "will reach the opposite shore. If the creature becomes " +
      "hungry during the trip, it will slow down. The creature can " +
      "be 'called' from either 'dock' by beating on the metal pipe " +
      "with a wielded weapon, but it will only respond if it is " +
      "hungry.\nFuture: The puller may be attackable by stabbing " +
      "into the water.\n");
}

/*
 * Function name: feed_creature
 * Description  : add the food to the ship and give some messages back
 * Todo         : Go through the messages to see if one can improve them
 * Arguments    : int food_amount - the amount of food (totally)
 *                int num_objects  - how many objects (so that the
 *                                   description gets right)
 */
private void
feed_creature(object *foods, int amount)
{
    string msg, text;
    int size = sizeof(foods);

    if (!size)
	return;

    D("Food was dropped into the water... nom nom.\n");

    text = COMPOSITE_DEAD(foods);

    msg = "The creature's eyes glow brighter. It lunges for "+
	text + ", flashing its sharp teeth.\n";

    set_alarm(0.1, 0.0,
	&tell_room(this_object(), msg, 0, this_object()));

    /* Send a message to ship which will send it to the puller... */
    if (objectp(ship))  // Easier debugging
	set_alarm(2.0, 0.0, &ship->add_food(amount));
}

/*
 * Function name: msg_non_food
 * Description  : the message when it's not food that is dropped
 * Arguments    : string text - the description of the object
 */
private void
msg_non_food(object *obs)
{
    string text;
    int size = sizeof(obs);

    if (!size) return;

    D("Non-food was dropped into the water... blub blub.\n");

    text = capitalize(COMPOSITE_DEAD(obs));
    set_alarm(0.1, 0.0, &tell_room(this_object(),
	    text + (size > 1 ? " sink " : " sinks ") +
	    "out of sight.\n", 0, this_object()));
}

/*
 * Function name: msg_drop
 * Description  : The message when items are dropped
 * Arguments    : object *obs - Items being dropped.
 */
private void
msg_drop(object *obs)
{
    string verb = query_verb(),
	   text = COMPOSITE_DEAD(obs);

    write("You "+ verb + " " + text + " into the water.\n");
    say(QCTNAME(this_player()) + " " + verb +"s " + text +
	" into the water.\n");
}

/*
 * Function name: process_dropped
 * Description  : Drop a number of objects.
 * Arguments    : object *obs - the objects to drop
 * Returns      : void
 */
private void
process_dropped(object *obs)
{
    int amount;
    object *foods = ({});

    foreach(object ob: obs)
    {
	if (IS_FOOD_OBJECT(ob))
	{
	    int size = ob->num_heap();

	    if (IS_LEFTOVER_OBJECT(ob))
	    {
		D("Processing LEFTOVER: "+ ob->short() +"\n"); 
		amount += (FOOD_CONSUMPTION + 1) * size;
	    }
	    else
	    {
		D("Processing FOOD: "+ ob->short() +"\n"); 
		amount += ob->query_amount() * size;
	    }

	    foods += ({ ob });
	} else {
	    D("Processing item: "+ ob->short() +"\n"); 
	}
    }

    D("Food amount == "+ amount +"\n");

    /* Print messages */
    msg_drop(obs);
    feed_creature(foods, amount);
    msg_non_food(obs - foods);

#if 1
    /* Remove objects. */
    foreach(object ob: obs)
    {
	if (ob->query_prop(HEAP_I_IS))
	{
	    D("Removal (HEAP): "+ ob->short() +
		" ~ NUM == "+ ob->num_heap() +"\n"); 
	    ob->reduce_heap_size(ob->num_heap());
	}
	else
	{
	    D("Removal (OBJ): "+ ob->short() +"\n");
	    ob->remove_object();
	}
    }
#else
    /* Lets move them instead. */
    obs->move("/d/Avenir/common/void");
#endif
}

/*
 * Function name: deck_drop_access
 * Description  : Test if player carries the object
 * Arguments    : object ob - the object we are gonna check
 * Returns      : 1/0 - carried dropable object / noncarried object
 */
public int
deck_drop_access(object ob)
{
    /* do not destroy undroppable things like guild items or poisons. */
    if (ob->query_prop(OBJ_M_NO_DROP))
	return 0;

    return 1;
}

/*
 * Function name: do_drop
 * Description  : the drop action
 * Arguments    : string str - the argument to the drop command
 * Returns      : 1/0 - I handled this/It's not mine
 */
public int
do_drop(string str)
{
    mixed *arr; 
    object *obs;

    if (!strlen(str))
	return 0;

    notify_fail(capitalize(query_verb()) +" what in the water?\n");
    if (!parse_command(str, all_inventory(this_player()),
	    "%i 'in' / 'into' [the] 'water'", arr))
    {
	return 0;
    }

    obs = NORMAL_ACCESS(arr, "deck_drop_access", this_object());
    if (!sizeof(obs))
	return 0;

    process_dropped(obs);
    return 1;
}

public int
do_rock(string str)
{
    if (str != "boat")
	return notify_fail("Rock what? The boat?\n");

    write("You rock the boat causing rippling waves along the "
      +"surface of a dark sea.\n");
    say(QCTNAME(this_player())
      +" rocks the boat, causing rippling waves along the "
      +"surface of a dark sea.\n");

    return 1;
}

/*
 * Function name: sounds
 * Description  : VBFC that give a random sound depending on the food state
 * Returns      : string - the sound
 */
public string
sounds()
{
    switch ((ship->query_puller())->query_food_state())
    {
    case FED:
	return one_of_list(fast_snd);
    case HUNGRY:
	return one_of_list(slow_snd);
    default:
	return "You feel that something is wrong with the boat. Leave bug " +
	"report please.\n";
    }
}

/*
 * Function name: bump_sounds
 * Description  : VBFC that give the message when the ship enter it's harbour
 * Returns      : string - the message
 */
public string
bump_sound(void)
{
    /* This mess is necessary as the ship isn't in arrival location
     * until _after_ this is called.
     */
    int loc = ship->query_location();
    string *places = ship->query_places_to_go();
    int rtype = places[loc]->query_prop(ROOM_I_TYPE);
    string msg = "You feel that something is wrong with the boat.\n"+
	"Please leave a bug report.\n";

    switch ((ship->query_puller())->query_food_state())
    {
    case FED:
	if (rtype == ROOM_BEACH) {
	    msg = "You hardly keep your balance as the boat is thrown "+
		"on the sandy beach.";
	} else {
	    msg = "You hardly keep your balance as the boat is thrown "+
		"against the wooden float.";
	}
	break;
    case HUNGRY:
	if (rtype == ROOM_BEACH) {
	    msg = "The boat drifts into the beach and stops.";
	} else {
	    msg = "The boat bumps up against the float and stops.";
	}
	break;
    } 
    return msg + "\n";
}

/*
 * Function namme: ship_arrived
 * Description   : this is called whenever the ships arrive somewhere
 * Arguments     : mixed where -
 */
public void
ship_arrived(mixed where)
{
    ship = previous_object();
    if (where->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
    {
	tell_room(this_object(), check_call(bump_sound));
	ship->set_board_enable(1);
	exit_enabled = 1;
    }
    else
    {
	tell_room(this_object(), check_call(deck_sounds));
	exit_enabled = 0;
    }
} 

/*
 * Function name: describe_creature
 * Description  : describing the creature based on the food state
 * Returns      : string - the describing message
 */
public string
describe_creature(void)
{
    switch ((ship->query_puller())->query_food_state())
    {
    case FED:
	return "Its body seems to be grey, with glowing eyes; you can't " +
	"determine more about how it looks. It's swimming straight " +
	"ahead at a good speed.\n";
    case HUNGRY:
	return "Its grey skin is sleek. Two glowing eyes at the front of " +
	"the head stare up at you. Every now and then they blink " +
	"and a large mouth opens hungrily to reveal teeth and a long " +
	"tongue.\n";
    default:
	return "It looks like something is wrong in the fabric of space. " +
	"Leave bug report or use <commune here>.\n";
    }
}

public int
do_sit(string str)
{
    if (str != "on seat")
    {
	notify_fail("Sit on what?\n");
	return 0;
    }

    if (TP->query_prop("i_am_sitting_on_a_seat"))
    {
	write("You're already sitting down.\n");
	return 1;
    }

    TP->add_prop("i_am_sitting_on_a_seat",1);
    TP->add_prop(LIVE_S_EXTRA_SHORT, " sitting on a seat");

    write("You sit down on the seat.\n");
    say(QCTNAME(TP)+ " sits down on a seat.\n");

    return 1;
}

public int
do_stand(void)
{
    if (TP->query_prop("i_am_sitting_on_a_seat"))
    {
	TP->remove_prop("i_am_sitting_on_a_seat");
	TP->remove_prop(LIVE_S_EXTRA_SHORT);

	write("You stand up from the seat, feeling rested.\n");
	say(QCTNAME(TP)+ " stands up from the seat.\n");
    } else {
	write("You are already standing.\n");
    }
    return 1;
}

public int
do_nothing(void)
{
    if (TP->query_prop("i_am_sitting_on_a_seat"))
    {
	write("You must stand up from the seat before you can do that.\n");
	return 1;
    }
    return 0;
}

public void
cure_plague(object carrier, int inc)
{
    if (ENV(carrier) != TO) {
#ifdef DEBUG
	if (carrier->query_wiz_level()) {
	    write("!! PLAGUE: No longer present!\n");
	}
#endif
	return;
    }

    float wait = 1.0 + rnd();

    switch(inc)
    {
    case 0:
    {
	int flag;
	object ob;
	
	while(ob = present("nasty_sickness", carrier)) 
	{
	    ob->cure_poison( ({"all"}), 999 );   
	    // And just in case...
	    ob->timeout();
	    // Did we cure it?
	    flag++;
	}

	if (flag)
	{
	    wait = 5.0 + (10.0 * rnd());
#ifdef DEBUG
	    if (carrier->query_wiz_level()) {
		write("\n>> PLAGUE: Removed "+ flag +" occurance(s)\n");
	    }
#endif
	    break;
	}
    } /* Deliberate Fallthru */
    default:
	wait = 0.0;
	break;

    case 1:
	carrier->catch_tell("Suddenly the sweet and soothing aroma "+
	  "of fresh herbs surrounds you.\n");
	break;

    case 2:
	carrier->catch_tell("You hear a voice whispering in your ear. "+
	  "It sounds strange, as though it were coming from a long "+
	  "distance. It says: Plague-bearer, Ae'll not let what su "+
	  "carry harm the people of this land. By the Pact they are "+
	  "under Our protection.\n");
	break;

    case 3:		
	wait = 0.0;
	carrier->catch_tell("An electric jolt passes through your "+
	  "body, but it isn't painful. In fact, it leaves you "+
	  "feeling much better.\n");

	tell_room(ENV(carrier), QCTNAME(carrier) +" pulses briefly with "+
	  "a blinding blue light.\n", carrier, carrier);
	break;
    }

    if (wait) {
	set_alarm(wait, 0.0, &cure_plague(carrier, ++inc));
#ifdef DEBUG
	if (carrier->query_wiz_level()) {
	    write(sprintf("** PLAGUE: Alarm delay >> %f\n", wait));
	}
#endif
    }
#ifdef DEBUG
    else if (carrier->query_wiz_level()) {
	write(sprintf("!! PLAGUE: Fini!\n"));
    }
#endif
}

/*
 * Function name: init
 * Description  : Init the players command set
 */
public void
init(void)
{
    ::init();

    cure_plague(TP, 0);

    add_action(    do_drop, "put"       );
    add_action(    do_drop, "drop"      );
    add_action(    do_rock, "rock"      );
    add_action(     do_sit, "sit"       );
    add_action(   do_stand, "stand"     );
    add_action( do_nothing, "enter"     );
    add_action( do_nothing, "get"       );
    add_action( do_nothing, "search"    );
    add_action( do_nothing, "disembark" );
    add_action( do_nothing, "leave"     );
}
