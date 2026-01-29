/*
 * new Genesis ship
 * Adapted from the original file by Tapakah, Dec 2007
 */

#pragma save_binary

#include <cmdparse.h>
#include <gmcp.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>

#include "../ships.h"

inherit "/std/object";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*
 * Global variables
 */
static object captain;          /* The captain of the ship.  */
                                /* E.g customized monster.c */
static string *cabin;           /* Filename for cabin room */
static string *deck;            /* Filename for the deck */
static string ticket;           /* Unique id for the ticket needed */
                                /* to travel */
static int  *location;          /* We are at coordinates X, Y */
static int  board_enabled;      /* Add 'board' command in init()? */
static int  no_steed_allowed;       // No steeds allowed on this ship

static int  ship_id;
int         is_at_harbor;
string      is_near_harbor;

string      continents_desc = "";

/*
 * Function prototypes
 */
void       set_captain          (object captain);
void       set_cabin            (mixed room);
void       set_deck             (mixed room);
void       set_ticket           (string ticket_file);
void       set_board_enabled    (int board);
void       tell_us              (string what, int outside_only);
object   query_captain        ();
mixed      query_cabin          ();
mixed      query_deck           ();
string   query_ticket         ();
int      is_valid_ticket      (object ticket_candidate);
int      query_board_enabled  ();
int      get_ship_id          ();
int      query_is_at_harbor   ();
void     set_ship_id          (int id);
void     signal_master        (string signal);
void     start_loading        (string next_port);
object  *get_people_on_deck   ();
object  *get_people_in_cabins ();
object  *get_people_on_ship   ();
varargs
void     relay_message        (string message, int outside_only, int obey_silent_ship = 0);
void     unload_cargo         (string reason);
void     signal_arrival       (string port, string next_port);
/*
 * Function name: create_ship
 * Description  : Create the ship
 */
public void
create_ship()
{
    set_name("ship");
    set_long("A really neat ship.\n");
}

/*
 * Function name: create_object
 * Description  : Set up default values for parts of the ship
 */
nomask void
create_object()
{
    setuid();
    seteuid(getuid());

    add_prop(OBJ_M_NO_GET, "You have got to be kidding!\n");
    create_ship();
}

/*
 * Function name: init
 * Description  : Add commands to the player presend outside the ship
 */
public void
init()
{
    ::init();
    add_action("board", "embark");
    add_action("board", "board");
    add_action("board", "enter");
}

/* Function name: query_cannot_board_ship
 * Description:   Can a player not board? This function should
 *                handle all messages itself.
 * Arguments:     object player, mixed destination room
 * Returns:       int 1 if unable to board
 */
public int
query_cannot_board_ship (object player, mixed destination)
{
    return player->query_cannot_board_ship(destination);
}

/* Function name: query_prevent_board_ship
 * Description:   prevent a player from boarding. This function
 *                should handle all messages itself.
 * Arguments:     object player
 * Returns:       int 1 if not allowed to board
 */
public int
query_prevent_board_ship (object player)
{
    return 0;
}

/*
 * Function name: board
 * Description  : Allow a player to board the ship if he have got a ticket, or
 *        if the fare is free of charge.
 *      Added by Fysix, Sep 1997: When riding a steed, the rider should
 *      have a ticket for himself, the steed and co-riders.
 * Arguments    : what - what we want to enter
 * Returns  : 1 - success
 *        0 - wrong parameters
 */
varargs public int
board (mixed what)
{
    object *good_tickets, *tmp, steed;
    int     no_of_tickets_wanted;
    string  str;
    if (!board_enabled)
    {
        NF0("You try and board the ship, but a ship officer sternly "
            + "informs you that the ship is not ready for boarding.");        
        return 0;
    }
    
    // Check syntax
    if (what && (!sizeof(tmp = FIND_STR_IN_OBJECT(
        what,
        environment(this_player())
    )) || this_object() != tmp[0]))
        return 0;

    // A hook for not allowing a player on the ship
    if (query_prevent_board_ship(this_player()))
        return 1;

    steed = this_player()->query_prop(LIVE_O_STEED);

    no_of_tickets_wanted = 1;  // By default the player needs one ticket
    // If the player is riding a steed he needs more tickets
    // One for the steed, and x for all its riders.
    // check if the steed is based on the std steed.
    if (objectp(steed) && steed->is_steed())
        no_of_tickets_wanted = 1 + sizeof(steed->query_riders());
    
    /* This will allow team members to do exactly the
     * same command their leader did.*/
    environment(this_player())->set_dircmd(what);
    // Check if there is a ticket_id, if not, just board the ship
    // This also goes for newbies without a ticket
    if (!stringp(ticket = query_ticket()) ||
            (no_of_tickets_wanted <= 2 &&
             captain->query_ride_for_free(this_player()))) {
        // Check if the player can board.
        if (!query_cannot_board_ship(this_player(), query_deck()[0])) {
            tell_room(
                environment(), QCTNAME(this_player()) + " boards the "+
                short() + ".\n", this_player()
            );
            write("You board the " + short() + ".\n");
            this_player()->move_living(
                "boarding the " + short(),
                query_deck()[0]
            );
        }
		
        mapping row = PIER_DATABASE->query_row_by_id(query_is_at_harbor());
        CONTROLROOM->send_debug_message(
                                        "gslcontrol_traffic",
                                        this_player()->query_name() +
                                        " boarded " +
                                        get_ship_id() + " " +
                                        row["port"],
                                        BOARD_LOG
                                        );
        return 1;
    }

    // Now check all the good tickets the player has
    good_tickets = filter(all_inventory(this_player()), is_valid_ticket);
    if (sizeof(good_tickets) < no_of_tickets_wanted) {
        if (captain
            && environment(captain) == environment(this_object())) 
        {
            tell_room(
                environment(),
                QCTNAME(captain) + " scowls menacingly " +
                "at " + QTNAME(this_player()) + " and blocks " +
                this_player()->query_possessive() + " way.\n",
                this_player()
            );
            write(
                capitalize(captain->query_the_name(this_player())) +
                " scowls at you.\n"
            );
            str = (
                no_of_tickets_wanted > 1 ? "not enough tickets" : "no ticket"
            );
            captain->command(
                "say You have " + str + ", "+
                this_player()->query_nonmet_name() + "."
            );
        }
        else {
            write(
                "A ship officer prevents you from boarding the "+
                short() + ".\n"
            );
            tell_room(
                environment(), QCNAME(this_player()) + " tries to "+
                "board the " + short() + ", but is prevented.\n",
                this_player()
            );
        }
        return 1;
    }

    // Check if the player can board.
    if (!query_cannot_board_ship(this_player(), query_deck()[0])) {
        // Remove the right number of tickets
        good_tickets[0..no_of_tickets_wanted - 1]->remove_object();
        str = (no_of_tickets_wanted > 1 ? "tickets" : "ticket");
        if (captain && environment(captain) == environment(this_object())) 
        {
            tell_room(environment(), QCTNAME(this_player()) + " gives "
                + this_player()->query_possessive() + " " + str + " to "
                + QTNAME(captain) + " and boards the " + short() + ".\n", 
                this_player());
            write("You give your " + str + " to "
                + captain->query_the_name(this_player()) + " and "
                + "board the " + short() + ".\n");
        }
        else
        {
            tell_room(environment(), QCTNAME(this_player()) + " gives "
                + this_player()->query_possessive() + " " + str + " to "
                + "a ship officer and boards the " + short() + ".\n", 
                this_player());
            write("You give your " + str + " to a ship officer "
                + "and board the " + short() + ".\n");
        }                        
        this_player()->move_living("boarding the " + short(), 
            query_deck()[0]);
        mapping row = PIER_DATABASE->query_row_by_id(query_is_at_harbor());
        CONTROLROOM->send_debug_message(
                                        "gslcontrol_traffic",
                                        this_player()->query_name() +
                                        " boarded " +
                                        get_ship_id() +" "+
                                        row["port"],
                                        BOARD_LOG
                                        );
    }

    return 1;
}

/*
 * Function name: set_captain
 * Description  : Set the object that should act as the ship's captain
 * Arguments    : x - the living object to set
 */
public void
set_captain(object x)
{
  captain = x;
}

/*
 * Function name: set_cabin
 * Description  : Set the object that should act as the ship's cabin
 * Arguments    : x - either a pathname or an object, should be a room
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
  x->set_ship(TO);
  x->set_is_cabin(1);
}

/*
 * Function name: set_ticket
 * Description  : Sets the ID of the ticket needed to board the ship. This
 *        should be defined as (one of) the name(s) of the ticket
 *        object.
 * Arguments    : x - the ID string of the ticket object
 */
public void
set_ticket (string x)
{
    ticket = x;
}

/*
 * Function name: tell_us
 * Description  : Give a message to all players in the ships environment
 *        and on the ships deck.
 * Arguments    : string containing message
 */
void
tell_us (string what, int outside_only)
{
    int     i;
    object *tmp;
    if (sizeof(tmp = query_deck()))
        for (i = 0; i < sizeof(tmp); i++)
        tell_room(tmp[i], what);
    if (outside_only && sizeof(tmp = query_cabin()))
        for (i = 0; i < sizeof(tmp); i++) 
        tell_room(tmp[i], what);
}

/*
 * Function name: set_deck
 * Description  : Set the object that should act as the ship's deck
 * Arguments    : x - either a pathname or an object, should be a room
 */
public void
set_deck (mixed x)
{
  if (!pointerp(x))
    deck = ({ x });
  else
    deck = x;
  x->set_ship(TO);
  x->set_is_deck(1);
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
  x->set_ship(TO);
  x->set_is_deck(1);
}

/*
 * Function name: set_board_enabled
 * Description  : Set wether or not it is possible to board the ship
 * Arguments    : 0 - boarding disabled
 *        1 - boarding enabled
 */
public void
set_board_enabled(int x)
{
    board_enabled = x;
    if (!board_enabled && objectp(query_captain()))
    {
        // If we manually stop the ship, the captain needs to stop
        // announcing ship departures.
        captain->disable_boarding();
    }
}

/*
 * Function name: query_captain
 * Description  : Get the object that is set up as captain of the ship
 * Returns  : the captain object
 */
public object
query_captain()
{
    return captain;
}

/*
 * Function name: query_cabin
 * Description  : get the object or path of the room used as ship cabin
 * Returns  : the cabin path or object
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
 * Description  : get the object or path of the room used as ship deck
 * Returns  : the deck path or object
 */
public mixed
query_deck ()
{
    if (!deck)
        return ({});
    return deck;
}

/*
 * Function name: query_board_enabled
 * Description  : check weather or not boarding is enabled
 * Returns  : 0 - boarding disabled
 *        1 - boarding enabled
 */
public int
query_board_enabled ()
{
    return board_enabled;
}

/*
 * Function name: query_ticket
 * Description  : Returns the master file of the ticket
 */
public string
query_ticket ()
{
  return ticket;
}

public int
is_valid_ticket (object ticket_candidate)
{
    return MASTER_OB(ticket_candidate) == ticket;
}
/*
 * Function name: query_location
 * Description  : get the ship's current location
 * Returns  : The current location number of the ship
 */
public int *
query_location()
{
    return location;
}

public nomask int
is_ship ()
{
  return 1;
}

public nomask int
get_ship_id ()
{
  return ship_id;
}

public nomask void
set_ship_id (int id)
{
  ship_id = id;
}

public nomask int
query_is_at_harbor ()
{
    object harbor;
    
    harbor = environment(this_object());
    if (!objectp(harbor))
    {
        return -1;
    }
    mapping pier = PIER_DATABASE->query_row_by_filename(MASTER_OB(harbor));
    if (!mappingp(pier))
    {
        return -1;
    }
    
    return pier["id"];
}

public nomask int
query_is_at_this_harbor (int pier_id)
{
  return query_is_at_harbor() == pier_id;
}

public nomask string
query_is_near_harbor ()
{
  return is_near_harbor;
}

public nomask void
set_is_near_harbor (string harbor_name)
{
  is_near_harbor = harbor_name;
}

public nomask void
clear_continents_desc ()
{
  continents_desc = "";
}

public nomask void
set_continents_desc (string desc)
{
  continents_desc = desc;
}

public nomask string
query_continents_desc ()
{
  return continents_desc;
}

public nomask void
signal_master (string signal)
{
  NAVIGATION_MANAGER->get_signal(TO, signal);
}

public void
start_loading (string next_port)
{
    set_board_enabled(1);
    if (captain && environment(captain) != ENV)
    {
        captain->move_living("the ship", ENV);
    }    
    captain->announce_loading(next_port);
}

public string
query_mm_in ()
{
  return capitalize(LANG_ASHORT(TO)) + " navigates in.\n";
} 

public string
query_mm_out ()
{
  return capitalize(LANG_THESHORT(TO)) + " navigates out.\n";
}

object *
get_people_on_deck ()
{
  int     d, do_num;
  object *deck_objects, *deck_livings;

  deck_objects = map(deck, find_object);
  do_num = sizeof(deck_objects);
  deck_livings = ({});
  for(d=0;d<do_num;d++)
    if (deck_objects[d])
      deck_livings += all_inventory(deck_objects[d]);
  if (!sizeof(deck_livings))
    return ({});
  return filter(deck_livings, interactive);
}

object *
get_people_in_cabins ()
{
  int     c, co_num;
  object *cabin_objects, *cabin_livings;

  cabin_objects = map(cabin, find_object);
  co_num = sizeof(cabin_objects);
  cabin_livings = ({});
  for(c = 0; c < co_num; c++)
    if (cabin_objects[c])
      cabin_livings += all_inventory(cabin_objects[c]);
  if (!sizeof(cabin_livings))
    return ({});
  return filter(cabin_livings, interactive);
}

object *
get_people_on_ship ()
{
    return
        get_people_on_deck() +
        get_people_in_cabins();
}

varargs public void
relay_message (string message, int outside_only, int obey_silent_ships = 0)
{
  object *watchers;

  watchers = (outside_only ? get_people_on_deck() : get_people_on_ship());
  if(obey_silent_ships)
    watchers -= filter(watchers, &->query_option(OPT_SILENT_SHIPS));
  watchers->catch_tell(message);
}

public void
leave_harbor ()
{
  //    captain->move_living("arrives onboard", query_deck()[0]);
    set_board_enabled(0);
    relay_message("You feel the ship catching the wind.\n", 0);
    tell_room(ENV, capitalize(LANG_THESHORT(TO)) + " starts moving away.\n");
}

void
unload_cargo (string reason)
{
    relay_message("This is an emergency stop!\n", 0);
    relay_message("You are being transferred at once to your destination.\n", 0);
    if(reason == "disable")
        relay_message("The ship is going at once to the docks.\n", 0);
    else
        relay_message("The ship is going to park at the port indefinitely.\n", 0);
    get_people_on_ship()->move_living(ENV);
}

/*
 * Function name: signal_move
 * Description  : Called when the ship moves, to give messages to the players
 *                on board.
 */
void
signal_move()
{
    object *deck_objects, *cabin_objects, *players;

    /* Give people on deck the info, and update their GMCP with the room info
     * if they are interested.
     */
    deck_objects = map(query_deck(), find_object);
    deck_objects = filter(deck_objects, objectp);
    foreach(object deck: deck_objects)
    {
        players = filter(all_inventory(deck), interactive);
        players->catch_tell(deck->query_deck_sound());
        foreach(object player: players)
        {
            if (player->query_gmcp(GMCP_ROOM))
            {
                deck->gmcp_room_info(player);
            }
        }
    }

    /* Inform people who are in the cabins. */
    cabin_objects = map(query_cabin(), find_object);
    cabin_objects = filter(cabin_objects, objectp);
    foreach(object cabin: cabin_objects)
    {
        players = filter(all_inventory(cabin), interactive);
        players->catch_tell(cabin->query_cabin_sound());
    }
}

void
signal_arrival (string port, string next_port)
{
    relay_message("The crew throws the anchor! Splash!\n", 1);
    get_people_in_cabins()->catch_tell("You feel the ship bump into something.\n");
    captain->command("shout We have arrived at " + port + "! Disembark!");
    captain->command("shout Next stop is " + next_port + "!");
    set_alarm(0.5, 0.0, &start_loading(next_port));
}

public void
set_ship_line(string filename, string captain, string ticket,
              string * piers)
{
    SHIP_DATABASE->add_ship_entry(filename, captain, ticket, piers);
    set_ticket(ticket);
}

public void
remove_object()
{
    if (objectp(query_captain()))
    {
        query_captain()->remove_object();
    }
    ::remove_object();
}
