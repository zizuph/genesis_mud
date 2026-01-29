#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

/*
 * Global declarations
 */
static string	deck_sounds;    /* sounds to be heard when ship moves (VBFC) */
static  string  bump_sound; 	/* The sound to hear when ship lands. (VBFC) */
static object	ship;
static int	exit_enabled;
static int	no_disembark;

/*
 * Function name: set_deck_sound
 * Description:   Set the sound that should be heard when the ship moves
 *	 	  Can be VBFC.
 * Arguments:	  str - The string to print
 */
public nomask void
set_deck_sound(string str)
{
    deck_sounds = str;
}

/*
 * Function name: set_bump_sound
 * Description:   Set what sound to be heard when ship lands on a pier
 * Arguments:     The string to print
 */
public void
set_bump_sound(string str)
{
    bump_sound = str;
}

/*
 * Function name: create_deck
 * Description  : Create the shipdeck
 */
public void
create_deck()
{
    set_short("Shipdeck");
    set_long("You are on a shipdeck.\n");
}

/*
 * Function name: create_room
 * Description  : Set up default values for the ship deck
 */
nomask void
create_room()
{
    add_item(({ "view", "land", "surroundings" }), "@@surroundings");
    set_deck_sound("The ship sways slightly in the wind.\n");
    set_bump_sound("The crew throws the anchor - splash!\n");
    create_deck();
}

nomask void
reset_room() { this_object()->reset_deck(); }

/*
 * Function name: surroundings
 * Description  : Get a description of the ship's surroundings
 * Returns      : A string describing the surroundings
 */
public string
surroundings()
{
    object *inv, *live, *dead;
    string live_desc, dead_desc, add_desc;

    if (!ship || !environment(ship))
	return "It seems like you are sailing around in a void!\n";

    inv = all_inventory(environment(ship));

    live = FILTER_LIVE(inv);
    dead = filter(inv, "other_dead_than_this", this_object(), ship);

    live_desc = (live && sizeof(live) ? capitalize(COMPOSITE_LIVE(live)) : 0);
    dead_desc = (dead && sizeof(dead) ? capitalize(COMPOSITE_DEAD(dead)) : 0);
    add_desc  = ((live_desc ? break_string(live_desc + ".", 76) + "\n" : "") +
                 (dead_desc ? break_string(dead_desc + ".", 76) + "\n" : ""));

    if (this_player()->query_brief())
        return environment(ship)->short() + ".\n" + add_desc ;
    else
        return environment(ship)->long() + add_desc ;
}

/*
 * Function name: other_dead_than_this
 * Description  : Filter function for correct room descriptions.
 * Returns      : 1 or 0
 */
public int
other_dead_than_this(object obj, object ref)
{
  if (obj == ref || living(obj))
    return 0;
  else
    return 1;
}

/*
 * Function name: ship_arrived
 * Description  : Give a description about where we currently got to
 * Arguments    : A string or object pointing to the current room
 */
public void
ship_arrived(mixed where)
{
    ship = previous_object();
    if (where->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER) {
	tell_room(this_object(), check_call(bump_sound));
	if (ship->query_captain())
	    tell_room(this_object(), QCTNAME(ship->query_captain()) +
        " says: We have arrived, disembark!\n");

	ship->set_board_enable(1);
	exit_enabled = 1;
    }
    else {
	exit_enabled = 0;
	tell_room(this_object(), check_call(deck_sounds));
    }
}	
	
/*
 * Function name: init
 * Description  : Add commands to the player on the deck
 */
public void
init()
{
    ::init();
    if (!no_disembark)
    {
    	add_action("disembark", "disembark");
    	add_action("disembark", "exit");
    	add_action("disembark", "leave");
    }
}

/*
 * Function name: set_no_disembark
 * Description:   Call this function if players should not be able to
 *		  leave the ship at all from this location
 */
public void
set_no_disembark() { no_disembark = 1; }

/*
 * Function name: disembark
 * Description  : Allow a player to leave the ship if the ship is in a room
 *		  that is NOT of water type
 * Arguments    : what - what we want to leave, if 0 the command have to be
 *		  disembark for the command to work.
 * Returns      : 1 - success, 0 - wrong parameters
 */
varargs public int
disembark(mixed what)
{
    object ticket;

    if (!ship || ((!what || !ship->id(what)) && query_verb() != "disembark")) {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }
    set_dircmd(what);

    if (!exit_enabled) {
    notify_fail("Wanna be eaten by a mekillot or what?\n");
	return 0;
    }
   write("You leave the wagon.\n");
   this_player()->move_living("the wagon", environment(ship));
    return 1;
}
