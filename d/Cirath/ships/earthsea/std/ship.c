#pragma save_binary

inherit "/std/object";
inherit "/std/callout";

#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include <cmdparse.h>

/*
 * Global variables
 */
static object	captain;		/* The captain of the ship.  */
					/* E.g customized monster.c */
static mixed	cabin;			/* Filename for cabin room */
static mixed	deck;			/* Filename for the deck */
static mixed	*places_to_go;		/* Filenames for places to visit */
static mixed	ticket_id;		/* Unique id for the ticket needed */
					/* to travel */
static int	callout_fq;		/* Call_out frequence - secs between */
					/* each call_out */
static int	location;		/* We are at places_to_go[location] */
static int	event_enable;		/* Events enabled or disabled */
static int	board_enabled;		/* Add 'board' command in init()? */
static int	call_no;		/* Counts how many call_outs we stay */
					/*  somewhere */
static int	*time_between_stops;	/* Number of call_outs with callout_fq */
					/* frequency */
static mixed	*events;		/* Table of random events */

/*
 * Function prototypes
 */
void	set_captain(object cap);
void	set_cabin(mixed cab);
void	set_deck(mixed room);
void	set_places_to_go(string *rooms);
void	set_time_between_stops(mixed time);
void	set_ticket_id(string id);
void	set_board_enabled(int board);
void	tell_us(string what);
void	call_left(mixed where_i_am,mixed where_i_am_going);
void	call_arrive(mixed where_i_am_going);
void	sail_away_out_on_the_open_sea();
int	random_event();
int	valid_location(int loc_low,int loc_high);
object	query_captain();
mixed	query_cabin();
mixed	query_deck();
string	query_ticket_id();
int	query_callout_fq();
int	query_board_enabled();

/*
 * Function name: create_ship
 * Description	: Create the ship
 */
public void
create_ship()
{
    set_name("ship");
    set_long("A really neat ship.\n");
}

/*
 * Function name: create_object
 * Description	: Set up default values for parts of the ship
 */
nomask void
create_object()
{
    callout_fq = 3;
    event_enable = 0;
    add_prop(OBJ_M_NO_GET, "The roc is a big nasty bird, "+
     "you don't want it!\n");
    create_ship();
}

nomask void
reset_object() { this_object()->reset_ship(); }

/*
 * Function name: stop_ship
 * Description	: Stop the ship from doing it's thing
 * Arguments	: why - string with the reason the ship should be stopped
 */
public void
stop_ship(string why)
{
    tell_us(why);
    remove_call_out("sail_away_out_on_the_open_sea");
}

/*
 * Function name: start_ship
 * Description	: Make the ship do it's thing
 * Arguments	: where - the location number to start in
 * Returns	: 0 - failed to start the ship
 *		  1 - ship started
 */
public varargs int
start_ship(int where)
{
    int time;
    object pier, captain;

    if (!places_to_go || !time_between_stops || !query_deck() ||
	sizeof(places_to_go) > sizeof(time_between_stops) ||
	!(captain = query_captain()) || !query_callout_fq())
	return 0;
    captain->set_ship(this_object());
    if (where)
    {
	if (where < 0 || where >= sizeof(places_to_go))
	    return 0;
	location = where;
	move(places_to_go[where]);
    }
    else 
	move(places_to_go[0]);
    call_arrive(environment());
    call_no = time_between_stops[where];
    if (environment()->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
    {
	set_board_enabled(1);
	if (captain)
   	{
      captain->move_living("the roc", environment());
	    captain->command("say All aboard!  The " + short() +
		" leaves in " +
		(time = query_callout_fq() * time_between_stops[where]) +
		" seconds!");
	    call_out("give_leave_warning", time - 20);
	}
    }
    else if (query_captain())
    {
	pier = environment(captain);
    captain->move_living("climbing onto the roc", query_deck()[0]);
	captain->command("say And we're off!");
    tell_room(pier, "The roc lifts off.\n");
    }
    sail_away_out_on_the_open_sea();
}

/*
 * Function name: sail_away_out_on_the_open_sea
 * Description	: The core of the ship; this is called every callout_fq
 *		  seconds and will move the ship around at appropiate
 *		  intervals
 */
void
sail_away_out_on_the_open_sea()
{
    int time;
    object pier, captain;

    if (call_no < 1)
    {
	board_enabled = 0;
	location++;
	if (location >= sizeof(places_to_go)) 
	    location = 0;
	call_no = time_between_stops[location];
	if (captain = query_captain())
	    if (file_name(pier =
		environment(query_captain())) != query_deck()[0])
	    {
      captain->move_living("climbing onto the roc", query_deck()[0]);
		tell_room(pier,
     capitalize(LANG_ADDART(short())) + " launches itself into the "+
        "air.\n");
	    }
	call_left(environment(), places_to_go[location]);
	call_arrive(places_to_go[location]);
	move(places_to_go[location]);
	if (places_to_go[location]->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
	{
	    tell_room(places_to_go[location],
        capitalize(LANG_ADDART(short())) + " lands in a swirl of "+
          "dust.\n");
	    if (captain)
	    {
       captain->move_living("the roc", places_to_go[location]);
		captain->command("say All aboard!  The " + short() +
		    " leaves in " + (time = query_callout_fq() * call_no) +
		    " seconds!");
		if (query_ticket_id())
       captain->command("say Buy your tickets now!");
		call_out("give_leave_warning", time - 20);
	    }
	    set_board_enabled(1);
	}
	else
	    tell_room(places_to_go[location], capitalize(LANG_ADDART(short()))+
		      " passes by.\n");
    }
    else 	
	call_no--;

    if (event_enable)
    {
	if (!(event_enable = !random_event()))
	    return;
        call_out("sail_away_out_on_the_open_sea", query_callout_fq(), 0);
    } else {
 	call_out("sail_away_out_on_the_open_sea", query_callout_fq() *
				call_no, 0);
	call_no = 0;
    }
}

/*
 * Function name: give_leave_warning
 * Description:   This function is here to give the players a warning
		  before the ship leaves.
 */
void
give_leave_warning()
{
    if (query_captain())
    query_captain()->command("say Buy your tickets now, we are "+
         "leaving in 20 seconds!");
}

/*
 * Function name: random_event
 * Description	: Check if a random even should occur. If one is called,
 *		  call_out's are disabled.
 * Returns	: 0 - no event occured
 *		  1 - event occured
 */
int
random_event()
{
    /*
     * In case of event, the call_outs are removed just in case
     * random_event was called from the outside - if not, no new
     * call_out will be issued in the first place. Remember that
     * to re-enable events after one has occurred, one has to
     * set event_enable to a nonzero value again.
     */
    int i;

    if (!events || !pointerp(events))
	return 0;
    if (!pointerp(events[0])) {
	if (!valid_location(events[0], events[1]))
	    return 0;
	if (random(1000) + 1 > events[2])
	    return 0;
	remove_call_out("sail_away_out_on_the_open_sea");
	call_other(events[3], events[4], this_object());
	return 1;
    }
    i = 0;
    while (i < sizeof(events)) {
	if (!valid_location(events[i][0], events[i][1])) {
	    if (++i < sizeof(events)) 
		continue;
	    else
		return 0;
	}
	if (!(random(1000) + 1 > events[i][2])) {
	    remove_call_out("sail_away_out_on_the_open_sea");
	    call_other(events[i][3], events[i][4], this_object());
	    return 1;
	}
	i++;
    }
    return 0;
}

/*
 * Function name: valid_location
 * Description	: Check if the current location is within the boundaries
 *		  given in the random event
 * Returns	: 1 - the location is valid
 *		  0 - the location is invalid
 */
int
valid_location(int loc_low,int loc_high)
{
    if (loc_low > loc_high) 	
	return (location >= loc_low || location < loc_high);
    return (location >= loc_low && location <= loc_high);
}

/*
 * Function name: init
 * Description	: Add commands to the player presend outside the ship
 */
public void
init()
{
    ::init();
    add_action("board", "board");
    add_action("board", "enter");
}

/*
 * Function name: board
 * Description	: Allow a player to board the ship if he have got a ticket, or
 *		  if the fare is free of charge
 * Arguments	: what - what we want to enter
 * Returns	: 1 - success
 *		  0 - wrong parameters
 */
varargs public int
board(mixed what)
{
    object ticket, *tmp;

    if (!board_enabled)
	return 0;
    if (what && (!sizeof(tmp = FIND_STR_IN_OBJECT(what,
		environment(this_player()))) || this_object() != tmp[0]))
	return 0;

    environment(this_player())->set_dircmd(what);
		      /* This will allow team members to do exactly the
		       * same command their leader did.*/

    if (query_ticket_id() &&
		!(ticket = present(query_ticket_id(), this_player())))
    {
	if (query_captain())
 	{
	    tell_room(environment(),
		      QCTNAME(query_captain()) + " scowls menacingly "+
		      "at " + QTNAME(this_player()) + " and blocks " +
		      this_player()->query_possessive() + " way.\n",
		      this_player());
	    write(capitalize(query_captain()->query_the_name(this_player())) +
		" scowls at you.\n");
	    query_captain()->command("say You have no ticket, "+
				     this_player()->query_nonmet_name() + ".");
	}
	else
	{
     write("A guard prevents you from climbing onto the "+
		  short() + ".\n");
	    tell_room(environment(), QCNAME(this_player()) + " tries to "+
		      "board the " + short() + ", but is prevented.\n",
		      this_player());
	}
	return 1;
    }

    if (!query_ticket_id())
    {
    tell_room(environment(), QCTNAME(this_player()) + " climbs "+
       "onto the "+
		  short() + ".\n", this_player());
    write("You climb onto the " + short() + ".\n");
    }
    else
    {
	ticket->remove_object();

	if (query_captain())
	{
	    tell_room(environment(), QCNAME(this_player()) + " gives "+
		      this_player()->query_possessive() + " ticket to "+
		      QTNAME(query_captain()) + " and boards the " + short()+
		      ".\n", this_player());
	    write("You give your ticket to "+
		  query_captain()->query_the_name(this_player()) + " and "+
            "climb onto the " +short() + ".\n");
	}
    }

    this_player()->move_living("climbing onto the "+short(),query_deck()[0]);
    return 1;
}

/*
 * Function name: set_captain
 * Description	: Set the object that should act as the ship's captain
 * Arguments	: x - the living object to set
 */
public void
set_captain(object x)
{
//    if (living(x))
	captain = x;
}

/*
 * Function name: set_cabin
 * Description	: Set the object that should act as the ship's cabin
 * Arguments	: x - either a pathname or an object, should be a room
 */
public void
set_cabin(mixed x)
{
    if (!pointerp(x))
	cabin = ({ x });
    else
	cabin = x;
}

/*
 * Function name: add_cabin
 * Description:   Add another cabin object to the ship
 * Arguments:     x - either pathname or an object
 */
public void
add_cabin(mixed x)
{
    if (!pointerp(x))
	x = ({ x });
    if (!cabin)
	cabin = x;
    else
	cabin += x;
}

/*
 * Function name: set_places_to_go
 * Description	: Sets up the array with the rooms the ship should traverse
 * Arguments	: x - array of rooms the ship should traverse
 */
public void
set_places_to_go(mixed *x)
{
    places_to_go = x;
}

/*
 * Function name: set_ticket_id
 * Description	: Sets the ID of the ticket needed to board the ship. This
 *		  should be defined as (one of) the name(s) of the ticket
 *		  object.
 * Arguments	: x - the ID string of the ticket object
 */
public void
set_ticket_id(string x)
{
    ticket_id = x;
}

/*
 * Function name: set_callout_fq
 * Description	: Set up call_out frequency. This is used to decide how
 *		  fast the ship moves
 * Arguments	: x - number of seconds between call_out's
 */
public void
set_callout_fq(int x)
{
    if (!x)
	x = 5;	
    callout_fq = x;
}

/*
 * Function name: set_location
 * Description	: Set the current location of the ship
 * Arguments	: x - either a pathname or an object, should be a room
 */
public void
set_location(int x)
{
    location = x;
}
 
/*
 * Function name: set_event_enable
 * Description	: Enables or disables events in the ship
 * Arguments	: 1 - enable events
 *		  0 - disable events
 */
public void
set_event_enable(int x)
{
    event_enable = x;
}

/*
 * Function name: set_call_no
 * Description	:
 * Arguments	:
 */
public void
set_call_no(int x)
{
    call_no = x;
}

/*
 * Function name: set_time_between_stops
 * Description	: Set up the time the ship should delay at each stop.
 * Arguments	: If a single number is passed as a parameter, this
 *		  will be the number of call_out's the ship will wait
 *		  at all places it stops.  If an array is passed, this
 *		  should hold one value per room visited, and this
 *		  number indicates how many call_out's the ship will
 *		  wait at that particular location.
 */
public void
set_time_between_stops(mixed x)
{
    int ind;

    if (pointerp(x)) {
	time_between_stops = x;
	return;
    }
    ind = sizeof(places_to_go);
    time_between_stops = ({ });
    while (ind--)
	time_between_stops = time_between_stops + ({ x });
}
	
/*
 * Function name: set_events
 * Description	:
 * Arguments	:
 */
public void
set_events(mixed *x)
{
    if (!events && !event_enable)
	return;
    events = x;
}		

/*
 * Function name: add_event
 * Description	:
 * Arguments	:
 */
public void
add_event(mixed *x)
{
    events += x;
}

/*
 * Function name: tell_us
 * Description	: Give a message to all players in the ships environment
 *		  and on the ships deck.
 * Arguments	: string containing message
 */
void
tell_us(string what)
{
    mixed tmp;
    int i;

    tell_room(environment(),what);
    if (sizeof(tmp = query_deck()))
	for (i = 0; i < sizeof(tmp); i++)
	    tell_room(tmp[i], what);
    if (sizeof(tmp = query_cabin()))
	for (i = 0; i < sizeof(tmp); i++) 
	    tell_room(tmp[i], what);
}

/*
 * Function name: set_deck
 * Description	: Set the object that should act as the ship's deck
 * Arguments	: x - either a pathname or an object, should be a room
 */
public void
set_deck(mixed x)
{
    if (!pointerp(x))
	deck = ({ x });
    else
	deck = x;
}

/*
 * Function name: add_deck
 * Description:   Add another deck room to the array
 * Arguments:     x - Either pathname or an object
 */
public void
add_deck(mixed x)
{
    if (!pointerp(x))
	x = ({ x });
    if (!deck)
	deck = x;
    else
        deck += x;
}

/*
 * Function name: set_board_enabled
 * Description	: Set wether or not it is possible to board the ship
 * Arguments	: 0 - boarding disabled
 *		  1 - boarding enabled
 */
public void
set_board_enabled(int x)
{
    board_enabled = x;
}

/*
 * Function name: call_left
 * Description	: call ship_left() function in misc. attached objects
 * Arguments	: where_i_am       - the room we are leaving
 *		  where_i_am_going - the room we are going to
 */
void
call_left(mixed where_i_am,mixed where_i_am_going)
{
    mixed tmp;
    int i;

    if (sizeof(tmp = query_deck()))
	for (i = 0; i < sizeof(tmp); i++)
	    call_other(tmp[i], "ship_left", where_i_am, where_i_am_going);
    if (sizeof(tmp = query_cabin()))
	for (i = 0; i < sizeof(tmp); i++)
	    call_other(tmp[i], "ship_left", where_i_am, where_i_am_going);
    if (query_captain())
	call_other(query_captain(), "ship_left", where_i_am, where_i_am_going);
    if (where_i_am)
	call_other(where_i_am, "ship_left", where_i_am, where_i_am_going);
}

/*
 * Function name: call_arrive
 * Description	: call ship_arrived() function in misc. attached objects
 * Arguments	: where_i_arrive - the room we just arrived in
 */
void
call_arrive(mixed where_i_arrive)
{
    mixed tmp;
    int i;

    if (sizeof(tmp = query_deck()))
	for (i = 0; i < sizeof(tmp); i++)
	    call_other(tmp[i], "ship_arrived", where_i_arrive);
    if (sizeof(tmp = query_cabin()))
	for (i = 0; i < sizeof(tmp); i++)
	    call_other(tmp[i], "ship_arrived", where_i_arrive);
    if (query_captain())
	call_other(query_captain(), "ship_arrived", where_i_arrive);
    if (where_i_arrive)
	call_other(where_i_arrive, "ship_arrived", where_i_arrive);
}

/*
 * Function name: query_captain
 * Description	: Get the object that is set up as captain of the ship
 * Returns	: the captain object
 */
public object
query_captain()
{
    return captain;
}

/*
 * Function name: query_cabin
 * Description	: get the object or path of the room used as ship cabin
 * Returns	: the cabin path or object
 */
public mixed
query_cabin()
{
    if (!cabin)
	return ({});
    return cabin;
}

/*
 * Function name: query_deck
 * Description	: get the object or path of the room used as ship deck
 * Returns	: the deck path or object
 */
public mixed
query_deck()
{
    if (!deck)
	return ({});
    return deck;
}

/*
 * Function name: query_board_enabled
 * Description	: check weather or not boarding is enabled
 * Returns	: 0 - boarding disabled
 *		  1 - boarding enabled
 */
public int
query_board_enabled()
{
    return board_enabled;
}

/*
 * Function name: query_places_to_go
 * Description	: get the list of places the ship moves through
 * Returns	: an array of objects or path names
 */
public mixed *
query_places_to_go()
{
    return places_to_go;
}

/*
 * Function name: query_ticket_id
 * Description	: get the id string of the ticket used to board the ship
 * Returns	: the string id of the ticket or 0
 */
public string
query_ticket_id()
{
    return ticket_id;
}

/*
 * Function name: query_callout_fq
 * Description	: get the time interval to be used between call_outs
 * Returns	: the time to be used
 */
public int
query_callout_fq()
{
    return callout_fq;
}

/*
 * Function name: query_call_no
 * Description	:
 * Returns	:
 */
public int
query_call_no()
{
    return call_no;
}

/*
 * Function name: query_location
 * Description	: get the ship's current location
 * Returns	: The current location number of the ship
 */
public int
query_location()
{
    return location;
}

/*
 * Function name: query_event_enable
 * Description	: get the event enable flag
 * Returns	: 0 - events disabled
 *		  1 - events enabled
 */
public int
query_event_enable()
{
    return event_enable;
}

/*
 * Function name: query_time_between_stops
 * Description	: get the time delay used at various stops the ship make
 * Returns	: an array of numbers, one for each location the ship moves to
 */
public int *
query_time_between_stops()
{
    return time_between_stops;
}

/*
 * Function name: query_events
 * Description	:
 * Returns	:
 */
public mixed *
query_events()
{
    return events;
}

/*
 * Function name: query_present_location
 * Description	: get the ship's current location
 * Returns	: the ships current location as a path or object
 */
public mixed
query_present_location()
{
    return environment(this_object());
}
