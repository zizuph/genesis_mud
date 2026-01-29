 /*
 * EX-SHIP code modified to be that of a carriage. Note that
 * most of the comments still reflect ship.
 * - Alaron March 1997
 *
 * A lot of unused (though, possibly useful) code cut out, cleaned up....
 * It's not perfect, but it's a bit more readable.
 * - Shiva February 1999
 */

inherit "/std/object";

#include <language.h>
#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

static mixed   deck;
static int move_alarm; 
static string *places_to_go;
static int      board_enabled;
static int      *time_between_stops;

void    set_deck(mixed room);
void    set_places_to_go(string *rooms);
void    set_time_between_stops(mixed time);
void    tell_us(string what);
void    move_carriage(int where);
void    give_leave_warning();
varargs public int board(mixed what);

/*
 * Function name: create_carriage
 * Description  : Create the Carriage
 */
public void
create_carriage()
{
    set_name("carriage");
    set_long("A really neat carriage.\n");
}

nomask void
create_object()
{
    add_prop(OBJ_M_NO_GET, "The carriage is far too heavy to lift!!\n");
    create_carriage();
}

void
reset_carriage()
{
}

nomask void
reset_object()
{
    reset_carriage();
}

/*
 * Function name: stop_carriage
 * Description  : Stop the carriage from doing it's thing
 * Arguments    : why - string with the reason the carriage should be stopped
 */
public void
stop_carriage(string why)
{
    tell_us(why);
    remove_alarm(move_alarm);
}

/*
 * Function name: start_carriage
 * Description  : Make the ship do it's thing
 * Arguments    : where - the location number to start in
 * Returns      : 0 - failed to start the ship
 *                1 - ship started
 */
public varargs int
start_carriage(int where)
{
    if (!places_to_go || !time_between_stops || !deck ||
        (sizeof(places_to_go) > sizeof(time_between_stops)))
    {
        return 0;
    }

    move_carriage(where);
    return 1;
}

/*
 * Function name: move_carriage
 * Description  : The core of the ship; this is called every callout_fq
 *                seconds and will move the ship around at appropiate
 *                intervals
 */
void
move_carriage(int where)
{
    int time;

    board_enabled = 0;
    if (where >= sizeof(places_to_go)) 
    {
        where = 0;
    }

    tell_room(deck, "The carriage rumbles along.\n");

    move(places_to_go[where], 1);

    if (places_to_go[where]->query_carriage_stop(this_object()))
    {
        tell_room(deck,
            "The driver shouts from atop the carriage: Everyone please " +
            "exit the carriage.\n");

        tell_room(places_to_go[where],
            capitalize(LANG_ADDART(short())) + " just came in.\n");
        tell_room(environment(), "The driver shouts from atop the " +
            "carriage: Everybody On! We leave in " +
                (time = time_between_stops[where]) + " seconds!\n");
        set_alarm(itof(time - 20), 0.0, give_leave_warning);
        board_enabled = 1;
    }
    else
    {
        tell_room(places_to_go[where], capitalize(LANG_ADDART(short()))+
                  " rolls quickly by.\n");
    }

    move_alarm = set_alarm(itof(time_between_stops[where]), 0.0,
        &move_carriage(++where));

}

/*
 * Function name: give_leave_warning
 * Description:   This function is here to give the players a warning
                  before the ship leaves.
 */
void
give_leave_warning()
{
    tell_room(environment(), "The driver shouts from atop the carriage: " +
        "Okay, everybody board the carriage: we are departing in " +
        "20 seconds! Please hurry, there are schedules to be met!\n");
}

/*
 * Function name: init
 * Description  : Add commands to the player presend outside the ship
 */
public void
init()
{
    ::init();
    add_action(board, "board");
    add_action(board, "enter");
}

/*
 * Function name: board
 * Description  : Allow a player to board the ship if he have got a ticket, or
 *                if the fare is free of charge
 * Arguments    : what - what we want to enter
 * Returns      : 1 - success
 *                0 - wrong parameters
 */
varargs public int
board(mixed what)
{
    object ticket, *tmp;

    if (!board_enabled)
    {
        return 0;
    }

    if (what && (!sizeof(tmp = FIND_STR_IN_OBJECT(what,
                environment(this_player()))) || this_object() != tmp[0]))
    {
        return 0;
    }

    environment(this_player())->set_dircmd(what);
                      /* This will allow team members to do exactly the
                       * same command their leader did.*/


    tell_room(environment(), QCTNAME(this_player()) + " boards the "+
          short() + ".\n", this_player());
    write("You board the " + short() + ".\n");

    this_player()->move_living("boarding the carriage", deck);
    return 1;
}

/*
 * Function name: set_places_to_go
 * Description  : Sets up the array with the rooms the ship should traverse
 * Arguments    : x - array of rooms the ship should traverse
 */
public void
set_places_to_go(mixed *x)
{
    places_to_go = x;
}

/*
 * Function name: set_time_between_stops
 * Description  : Set up the time the ship should delay at each stop.
 * Arguments    : If a single number is passed as a parameter, this
 *                will be the number of call_out's the ship will wait
 *                at all places it stops.  If an array is passed, this
 *                should hold one value per room visited, and this
 *                number indicates how many call_out's the ship will
 *                wait at that particular location.
 */
public void
set_time_between_stops(mixed x)
{
    time_between_stops = (pointerp(x) ? x : ({ x }));
}
        
/*
 * Function name: tell_us
 * Description  : Give a message to all players in the ships environment
 *                and on the ships deck.
 * Arguments    : string containing message
 */
void
tell_us(string what)
{
    tell_room(environment(), what);
    tell_room(deck, what);
}

/*
 * Function name: set_deck
 * Description  : Set the object that should act as the ship's deck
 * Arguments    : x - either a pathname or an object, should be a room
 */
public void
set_deck(mixed x)
{
    deck = x;
    deck->set_ship(this_object());
}



