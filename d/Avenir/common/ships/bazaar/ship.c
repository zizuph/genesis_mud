/*
 * Filename: /d/Avenir/common/ships/bazaar/ship.c
 * Original creator: Kazz on May 1995
 * Purpose: carries people between the Outpost beach & Bazaar Island
 * Last update(s):
 *    Boriska on Sep 1995 - Lots of modifications.
 *                          Most notable, no more sail_away_...
 *                          exponential call_outs which make standard ship
 *                          the biggest CPU hog in the game.
 *                          Original three-state puller replaced by two-state
 *                          one (FED or HUNGRY)
 *    Lilith on Jun 1998? - changed FILTER_LIVE to FILTER_PLAYERS so that
 *                          leaving pigeons and such on the deck doesn't
 *                          make it impossible to call the boat.
 *    Manat on Jul 2000   - changed coding style and stuff
 *                          moved #include below inherit
 *
 *    Lucius on Aug 2010  - added separate messages for float vs. beach.
 *
 * Description: This boat moves slow or fast depending on food state of
 *              creature/captain. The creature can be fed by dropping
 *              food in water from the deck. If insufficient food was given
 *              then the ship slows down mid-sea until more food is provided.
 *              Beating the pipe at dock makes the beast sail there at 'fed'
 *              speed in hope to be actually fed at the other end.
 *              The creature does not answer calls if there're people on
 *              deck or it is fed.
 * Note: Might be used between some of the other Sea islands?
 * Known bug(s):
 * To-do: * handle 'stabbing' the creature through the water
 *          : a way to start fighting with the 'captain'.
 */
#pragma save_binary
#pragma strict_types
/* added strict_types check because you always want it! Manat on Jul 2000 */

inherit "/d/Genesis/ship/ship";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/ships/bazaar/ship.h"

/* #define DEBUG */
#undef DEBUG
#ifdef DEBUG
#define D(x) find_player("lucius")->catch_tell("BOAT DEBUG: " + (x))
#else
#define D(x) ;
#endif

/* public functions: */
public object query_puller();                     /* returns our puller */
public void add_food(int amount);                 /* feeds our puller */
public int call_boat(string calling_room_name);   /* called by pipe */

static int *hungry_schedule;                  /* arrays holding time tables */
static int *fed_schedule;
private static object puller;                     /* it makes us move */
private static int alarm_id;                      /* main sail() alarm id */

private void test_hunger();
private void sail();
private int find_room_index(string room);
private void change_dir(int index);
private int people_on_deck();

/*
 * Function name: create_schedules
 * Description  : Create fast and slow time tables.
 */
private void
create_schedules()
{
    int time = SAIL_TIME * HUNGER_FACTOR;
  
    fed_schedule=({ WAIT_TIME, SAIL_TIME, SAIL_TIME, SAIL_TIME, SAIL_TIME,
                               SAIL_TIME,
                    WAIT_TIME, SAIL_TIME, SAIL_TIME, SAIL_TIME, SAIL_TIME,
                               SAIL_TIME
		  });
    hungry_schedule = ({ WAIT_TIME, time, time, time, time, time,
                         WAIT_TIME, time, time, time, time, time });
}

/*
 * Function name: create_ship
 * Description  : The creator of this ship
 */
public void
create_ship()
{
    if (!IS_CLONE)
        return;

    set_name( ({ "boat", "ship" }) );
    add_adj( ({ "sturdy", "wooden" }) );
    set_long("A sturdy wooden boat, larger than a row-boat. " +
             "It is rather devoid of sails or oars.\n" );
  
    set_deck(BOAT_DIR + "deck");
    seteuid(getuid());
    puller = clone_object(BOAT_DIR + "puller");

    set_places_to_go( ({ FORT_DOCK,
                         SEA + "sea1", SEA + "sea2", SEA + "sea3",
                         SEA + "sea4", SEA + "sea5",
                         BAZAAR_DOCK,
                         SEA + "sea5", SEA + "sea4", SEA + "sea3",
                         SEA + "sea2", SEA + "sea1" }) );
    create_schedules();
    set_time_between_stops(hungry_schedule);
  /* enable_reset(); */
  /* enable resets and make appopriate reset_ship() when puller is killable. */
}

/*
 * Function name: board
 * Description  : Some of standard ship routines rewritten there with
 *                captain stuff stripped off.
 * Arguments    : string str - the argument to the command
 * Returns      : 1/0 - I can handle this / This aint my concern
public int
board(string str)
{
    object *tmp;

    if (!board_enabled)
        return 0;

    if (str && (!sizeof(tmp = FIND_STR_IN_OBJECT(str,
        environment(this_player()))) || this_object() != tmp[0]))
        return 0;

    write("You board the boat.\n");
    environment(TP)->set_dircmd(str);
    TP->move_living("into the boat", query_deck()[0]);
    return 1;
}

/*
 * Function name: start_ship
 * Description  : We are ready to sail
 * Arguments    : (vararg) int where - the starting place along the line
 * Returns      :
 */
public varargs int
start_ship(int where)
{
    if (!places_to_go || !time_between_stops || !query_deck() ||
        sizeof(places_to_go) > sizeof(time_between_stops))
        return 0;

    if (where < 0 || where >= sizeof(places_to_go))
        return 0;

    location = where;
    move(places_to_go[where], 1);

    call_arrive(environment());
  
    if (environment()->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
        set_board_enabled(1);
    if (!alarm_id)
        remove_alarm(alarm_id);
    alarm_id = set_alarm (itof(time_between_stops[location]), 0.0, sail);
}

/*
 * Function name: sail
 * Description  : Heavily modified sail_away_whatever_wherever..
 *                func from the standard ship.
 *                We do not need lots of callouts here. --Boriska
 */
public void
sail()
{
    board_enabled = 0;

    if (++location >= sizeof(places_to_go)) 
        location = 0;
  
    int rtype = environment()->query_prop(ROOM_I_TYPE);
    if (rtype != ROOM_IN_WATER)
    {
        switch (puller->query_food_state())
        {
        case HUNGRY :
	    if (rtype == ROOM_BEACH) {
		tell_us("The boat is pulled away from the beach.\n");
	    } else {
		tell_us("The boat is pulled away from the float.\n");
	    }
            break;
        case FED:
	    tell_us("The boat rushes towards the open sea pulled by "+
	 	   "some great force.\n");
            break;
        default:
            tell_us("Something is wrong with the boat. Leave bug report " +
                    "please.\n");
            break;
        }
    }

    call_left(environment(), places_to_go[location]);
    call_arrive(places_to_go[location]);
    move(places_to_go[location], 1);

    test_hunger();
    if (puller->query_food_state() == HUNGRY)
        set_time_between_stops(hungry_schedule);
  
    /* D( "current room location = "+ location + "\n" ); */

    rtype = places_to_go[location]->query_prop(ROOM_I_TYPE);
    if (rtype != ROOM_IN_WATER)
    {
	string msg;

        switch (puller->query_food_state())
        {
        case HUNGRY :
	    if (rtype == ROOM_BEACH) {
		msg = "A wooden boat drifts into " +
                      "view and lands gently on the beach.";
	    } else {
		msg = "A wooden boat drifts into view and gently "+
		      "bumps against the float.";
	    }
            break;
        case FED:
	    if (rtype == ROOM_BEACH) {
		msg = "A wooden boat is thrown on " +
                      "the beach by some great force.";
	    } else {
		msg = "A wooden boat is jammed up against " +
                      "the float by some great force.";
	    }
            break;
        }
        set_board_enabled(1);
        puller->set_hungry(); // become hungry when arriving at dock.
        tell_room(places_to_go[location], msg + "\n");
    }
    else
        tell_room(places_to_go[location], "A boat passes by.\n");

    alarm_id = set_alarm(itof(time_between_stops[location]), 0.0, sail);
}

/*
 * Function name: add_food
 * Description  : Called by the deck when food is dropped into the water
 * Arguments    : int amount - the total food amount in all items dropped
 */
public void
add_food(int amount)
{
    float time;
    int old_state, new_state;

    D("add food called with " + amount + "\n");

    if (!objectp(puller))
        return;

    /* we do not move faster when too small amount of food is dropped */
    old_state = puller->query_food_state();
    puller->add_food(amount);
    new_state = puller->query_food_state();

    if (new_state == old_state) /* no state changes */
        return;

    if (new_state == HUNGRY) /* damn wizards playing pranks on us */
        return;

    /* state change hungry -> fed */
    /* we cannot go fed -> hungry as a result of add_food() */
    /* unless some wizard plays a prank on us */
    set_time_between_stops(fed_schedule);
  
    if (environment()->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER) /* at pier */
    {
        D("fed at port. Sailing in LEAVING_TIME...\n");
        remove_alarm(alarm_id);
        alarm_id = set_alarm(itof(LEAVING_TIME), 0.0, sail);
        tell_us("The water around the boat churns briefly.\n");
    }
    else /* at sea */
        D("fed at sea. Updating time table..\n");

    time = itof(time_between_stops[location]);
    /* move faster after dropping food, but not faster than fed schedule */
    if (get_alarm(alarm_id)[2] > time)
    {
        remove_alarm(alarm_id);
        alarm_id = set_alarm(time, 0.0, sail);
    }
}

/*
 * Function name: query_puller
 * Description  : Return the creature object
 * Returns      : object - the captain
 */
public object
query_puller()
{
    return puller;
}

/* Called from sail() alarm. Performs state transitions for the puller. */
private void
test_hunger()
{
    int old_state;

    if (!objectp(puller))
        return;

    old_state = puller->query_food_state();
    /* decrement food value and test for stopping. */
    /* puller should know how much to eat. */
    puller->decrease_food();
    if (puller->query_food_state() == HUNGRY )
    {
        if (old_state == HUNGRY) /* we were HUNGRY already */
            return; /* no messages, just usual deck sounds. */

        if (environment()->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
            return; /* at pier */

        /* transition from FED to HUNGRY: */
        if (people_on_deck())
        {
            D("creature became hungry, people are on deck --> slowing " +
              "down.\n");
            tell_us("The boat slows down. A rapid bubbling noise can be " +
                    "heard from the front.\n");
        }
        else
        {
            /* never should happen, we become hungry each time we arrive */
            /* at dock or while sailing with ppl. */
            D("creature is hungry, but boat is empty, so not stopping.\n");
        }
    }
}

/*
 * Function name: people_on_deck
 * Description  : telling about players is present on deck
 * Returns      : 1/0 - players on deck / no players on deck
 */
private int
people_on_deck()
{
    object *inv;
    string live_objects_string;
  
    inv = FILTER_PLAYERS(all_inventory(find_object(query_deck()[0])));

    if (!sizeof(inv))
        return 0;
    return 1;
}

/*
 * Function name: call_boat
 * Description  : this function is called from a dock room.
 * Arguments    : string calling_room - which dock we should go to
 * Returns      : 1 - always 1 so that one can check that it's called.
 * Note: I wonder why one don't make it into a void function... Manat
 */
public int
call_boat(string calling_room)
{
    int index;

    if (!objectp(puller))
        return 1;

    if (file_name(environment()) == calling_room)
    {
        write("The pipe hits you between the eyes! When you are able to see " +
              "again you notice that the boat is already here!\n");
        /* this_player()->command("$duh"); Never used anyway. */
        return 1;
    }

    if (people_on_deck())
    {
        write("Nothing happens, maybe you should try later.\n");
        return 1;
    }

    switch (puller->query_food_state())
    {
    case FED:
        D( "captain is FED, not answering call yet\n" );
        write("Nothing happens, maybe you should try in a moment.\n");
        break;
    case HUNGRY:
        if ((index = find_room_index(calling_room)) > -1)
        {
            write("You hear vibrations from the pipe thundering through the " +
                  "water.\n");
            /* We will go FED now, enough for trip between docks. */
            /* This makes us move fast when called and prevents undesirable */
            /* situation of two players sitting at both docks and beating */
            /* the pipes continiously without results. */
            add_food(FOOD_CONSUMPTION * (sizeof(places_to_go)/2 + 1));
            change_dir(index);
        }
        else
            write("The pipe seems to be broken. Please leave a bug report " +
                  "or try 'commune here'.\n" );
        break;
    default:
        write("Something is wrong with the boat. Please leave a bug report." +
              "\n");
    }
    return 1;
}

/*
 * Function name: change_dir
 * Description  : Changes ships direction if needed when called from
 *                room # index.
 * Arguments    : int index - the index in the array I should go to
 */
private void
change_dir(int index)
{
    int last = sizeof(places_to_go); 
    int mid = last/2;

    D("old location: " + location + ".\n");
    if (index == 0)
    {
        if (location < mid && location != 0)
            location = last - location;
    }
    else /* index == mid */
        if (location > mid)
            location = last - location;

    D("new location: " + location + ".\n");
}

/*
 * Function name: find_room_index
 * Description  : find dock's index in places_to_go array.
 * Arguments    : string room - the room to search for in the sail path
 * Returns      : int - the position of the room string in the sail path
 * Note         : this function is only able to locate the docks...
 */
private int
find_room_index(string room)
{
    int mid = sizeof(places_to_go)/2;

    if (room == places_to_go[0])
        return 0;
    if (room == places_to_go[mid])
        return mid;

    D( "find_room_index() failed to locate calling room!\n" );
    return -1;
}

/*
 * Function name: remove_object
 * Description  : the destructor of this ship
 */
public void
remove_object()
{
    if (objectp(puller))
        catch(puller->remove_object());
    ::remove_object();
}
