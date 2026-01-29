// -*-C++-*-
// $Id: ship.new.c,v 1.5 1995/09/13 01:05:23 bob Exp $
// name:  	/d/Avenir/common/outpost/boat/ship.c   
// creator(s):  Kazz   May 1995
// last update: Lilith, changed FILTER_LIVE to FILTER_PLAYERS
//              so that leaving pigeons and such on the deck doesn't
//              make it impossible to call the boat.
//              Boriska, Sept 1995 Lots of modifications.
//              Actually, there's little left of standard ship code :)
//              Most notable, no more sail_away_... exponential call_outs
//              which make standard ship the biggest CPU hog in the game.
//              Original three-state puller replaced by two-state one
//              (FED or HUNGRY)
// purpose:     carries people between the Outpost beach & Bazaar Island
//
// description: This boat moves slow or fast depending on food state of
//		creature/captain. The creature can be fed by dropping
//              food in water from the deck. If insufficient food was given
//		then the ship slows down mid-sea until more food is provided.
//              Beating the pipe at dock makes the beast sail there at 'fed'
//              speed in hope to be actually fed at the other end.
//              The creature does not answer calls if there're people on
//              deck or it is fed. 
// note:	Might be used between some of the other Sea islands?
//
// to-do:	* handle 'stabbing' the creature through the water
//		  : a way to start fighting with the 'captain'.

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/boat/ship.h"

#define DEBUG
#ifdef DEBUG
#define D(x) find_player("boriska")->catch_msg("BOAT DEBUG: " + (x))
#else
#define D(x) ;
#endif

#pragma save_binary

inherit "/d/Genesis/ship/ship";

// public functions:
object query_puller();                     // returns our puller
void add_food(int amount);                 // feeds our puller
int call_boat(string calling_room_name);   // called by pipe

private object puller;                     // it makes us move
int *hungry_schedule;                      // arrays holding time tables
int *fed_schedule;
private int alarm_id;                      // main sail() alarm id

private void test_hunger();	           
private sail();
private int find_room_index(string room);
private void change_dir(int index);
private status people_on_deck();

// Create fast and slow time tables.
private void
create_schedules() {
  int time = SAIL_TIME * HUNGER_FACTOR;
  
  fed_schedule=({ WAIT_TIME, SAIL_TIME,SAIL_TIME,SAIL_TIME,SAIL_TIME,SAIL_TIME,
		  WAIT_TIME, SAIL_TIME,SAIL_TIME,SAIL_TIME,SAIL_TIME,SAIL_TIME
		  });
  hungry_schedule = ({ WAIT_TIME, time, time, time, time, time,
		       WAIT_TIME, time, time, time, time, time });
}

void
create_ship() {
  if (!IS_CLONE)
    return;
  
  set_name("boat");
  add_adj("wooden");
  set_long("A sturdy wooden boat, larger than a row-boat. " +
	   "It is rather devoid of sails or oars.\n" );
  
  set_deck(OUTPOST + "boat/deck");
  seteuid(getuid());
  puller = clone_object(OUTPOST + "boat/puller");

  set_places_to_go(({
    FORT_DOCK,
    SEA + "sea1",
    SEA + "sea2",
    SEA + "sea3",
    SEA + "sea4",
    SEA + "sea5",
    BAZAAR_DOCK,
    SEA + "sea5",
    SEA + "sea4",
    SEA + "sea3",
    SEA + "sea2",
    SEA + "sea1", }));
  create_schedules();
  set_time_between_stops(hungry_schedule);
  // enable_reset();
  // enable resets and make appopriate reset_ship() when puller is killable.
}

// Some of standard ship routines rewritten there with captain stuff
// stripped off.
int
board(string str) {
  if (!board_enabled)
    return 0;
  
  if (str != "boat" && str != "ship")
    return 0;
  
  write("You board the boat.\n");
  environment(TP)->set_dircmd(str);
  TP->move_living("into the boat", query_deck()[0]);
  return 1;
}


varargs int
start_ship(int where) {
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
} // start_ship()


// Heavily modified sail_away_whatever_wherever.. func from the standard
// ship. We do not need lots of callouts here. --Boriska
void
sail()
{
  board_enabled = 0;
  location++;
  if (location >= sizeof(places_to_go)) 
    location = 0;
  
  if (environment()->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER) {
    switch (puller->query_food_state()) {
    case HUNGRY :
      tell_us("The boat is pulled away from the beach.\n");
      break;
    case FED:
      tell_us("The boat rushes towards the open sea pulled by some great " +
	      "force.\n");
      break;
    default:
      tell_us("Something is wrong with the boat. Leave bug report please.\n");
      break;
    }
  }
  
  call_left(environment(), places_to_go[location]);
  call_arrive(places_to_go[location]);
  move(places_to_go[location], 1);

  test_hunger();
  if (puller->query_food_state() == HUNGRY)
    set_time_between_stops(hungry_schedule);
  
  //D( "current room location = "+ location + "\n" );
  
  if (places_to_go[location]->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER) {
    switch (puller->query_food_state()) {
    case HUNGRY :
      tell_room(places_to_go[location], "A wooden boat drifts into view " +
		"and lands gently on the beach.\n" );
      break;
    case FED:
      tell_room(places_to_go[location], "A wooden boat is thrown on the " +
		"beach by some great force.\n");
      break;
    }
    set_board_enabled(1);
    puller->set_hungry(); // become hungry when arriving at dock.
  }
  else
    tell_room(places_to_go[location], "A boat passes by.\n");
  
  alarm_id = set_alarm(itof(time_between_stops[location]), 0.0, sail);
} 

// Called by the deck when food is dropped into the water
// This is total food amount in all items dropped.
void
add_food(int amount) {
  float time;
  int old_state, new_state;
  
  D("add food called with " + amount + "\n");

  // we do not move faster when too small amount of food is dropped
  if (!objectp(puller))
    return;

  old_state = puller->query_food_state();
  puller->add_food(amount);
  new_state = puller->query_food_state();

  if (new_state == old_state) // no state changes
    return;
  
  // state change hungry -> fed
  // we cannot go fed -> hungry as a result of add_food()
  
  set_time_between_stops(fed_schedule);
  
  if (environment()->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER) { // at pier
    D("fed at port. Sailing in LEAVING_TIME...\n");
    remove_alarm(alarm_id);
    alarm_id = set_alarm(itof(LEAVING_TIME), 0.0, sail);
    tell_us("The water around the boat churns briefly.\n");
  }
  else // at sea
    D("fed at sea. Updating time table..\n");
  time = itof(time_between_stops[location]);
  // move faster after dropping food, but not faster than fed schedule
  if (get_alarm(alarm_id)[2] > time) {
    remove_alarm(alarm_id);
    alarm_id = set_alarm(time, 0.0, sail);
  }
}

object
query_puller() { return puller; }

// Called from sail() alarm. Performs state transitions for the puller.
private void
test_hunger() {
  int old_state;
  
  if (!objectp(puller))
    return;

  old_state = puller->query_food_state();
  // decrement food value and test for stopping.
  // puller should know how much to eat,
  puller->decrease_food();
  if (puller->query_food_state() == HUNGRY ) {
    if (old_state == HUNGRY) // we were HUNGRY already
      return; // no messages, just usual deck sounds.

    if (environment()->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
      return; // at pier

    // transition from FED to HUNGRY:
    if (people_on_deck()) {
      D( "creature became hungry, people are on deck --> slowing down.\n" );
      tell_us( "The boat slows down. A rapid bubbling noise can be heard " +
	      "from the front.\n");
    }
    else
      // never should happen, we become hungry each time we arrive
      // at dock or while sailing with ppl.
      D( "creature is hungry, but boat is empty, so not stopping.\n" );
  }
}

// returns boolean value telling about players present on deck
private status
people_on_deck() {
  object *inv;
  string live_objects_string;
  
  inv = all_inventory(find_object(query_deck()[0]));
  
  live_objects_string = COMPOSITE_LIVE(FILTER_PLAYERS(inv));
  D( "live_objects_string = "+ live_objects_string +"\n" );

  if(!FILTER_PLAYERS(inv) || (live_objects_string == "someone")) 
    return 0;
  return 1;
}

// this function is called from a dock room.
// if the creature is in the right 'state', it will head toward that dock.
// NOTE:  *laugh* people could fool the boat using this...
//     	if 1 player goes across, and a friend wants to later join, but has
//	no food, and doesn't wish to wait while the boat wanders over,
//      the new player could call the boat
//	get in, and then player 1 could call the boat to bring it over 
//	This situation isn't likely to occur, and even if it does ... 
//	'good for them' for discovering how to abuse the poor creature.
//	Perhaps this will piss off the monster in the future, but not now,
//	(it's rather a dimwitted creature).
//      Always returns 1 to provide a possibility to check if
//      it were called at all.
int
call_boat(string calling_room) {
  int index;
  
  if (!objectp(puller))
    return 1;

  if (file_name(environment()) == calling_room) {
    TP->catch_msg("The pipe hits you between the eyes! When you are able to " +
		  "see again you notice that the boat is already here!\n");
    TP->command("duh");
    return 1;
  }
  
  if (people_on_deck()) {
    TP->catch_msg("Nothing happens, maybe you should try later.\n");
    return 1;
  }

  switch (puller->query_food_state()) {
  case FED:
    D( "captain is FED, not answering call yet\n" );
    TP->catch_msg( "Nothing happens, maybe you should try in a moment.\n");
    break;
  case HUNGRY:
    if((index = find_room_index(calling_room)) > -1) {
      TP->catch_msg("You hear vibrations from the pipe thundering through " +
		    "the water.\n");
      // We will go FED now, enough for trip between docks.
      // This makes us move fast when called and prevents undesirable
      // situation of two players sitting at both docks and beating
      // the pipes continiously without results.
      add_food(FOOD_CONSUMPTION * (sizeof(places_to_go)/2 + 1));
      change_dir(index);
    }
    else
      TP->catch_msg("The pipe seems to be broken.\n"+
		    "Please leave a bug report or try 'commune here'.\n" );
    break;
  default:
    TP->catch_msg("Something is wrong with the boat. " +
		  "Please leave a bug report.\n");
  }
  return 1;
}

// Changes ships direction if needed when called from room # index.
private void
change_dir(int index) {
  int last = sizeof(places_to_go); 
  int mid = last/2;

  D("old location: " + location + ".\n");
  if (index == 0) {
    if (location < mid && location != 0)
      location = last - location;
  }
  else
    // index == mid
    if (location > mid)
      location = last - location;
  
  D("new location: " + location + ".\n");
}

// find dock's index in places_to_go array. 
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
} // find_room_index()

void
remove_object() {
  if (objectp(puller))
    catch(puller->remove_object());
  ::remove_object();
}