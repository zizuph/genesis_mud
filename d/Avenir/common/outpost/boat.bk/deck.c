// -*-C++-*-
// $Id: deck.new.c,v 1.5 1995/09/12 17:28:15 bob Exp $
// file name:   /d/Avenir/common/ships/sparkle/deck.c  
// creator(s):  Kazz   April, 1995
// last update: May
// update:      Boriska, Sep 95. Changes in drop command. Correct handling
//              of heap objects. possibility to drop several items.
//              Numerous other changes.
// purpose:     Deck of the boat between outpost & islands
// note:
// bug(s):     
// to-do:   	

#include <macros.h>
#include <stdproperties.h>
#include "/d/Avenir/common/outpost/boat/ship.h"

#define TP this_player()

#define DEBUG
#ifdef DEBUG
#define D(x) find_player("boriska")->catch_msg("DECK DEBUG: " + (x))
#else
#define D(x) ;
#endif

#pragma save_binary

inherit "/d/Genesis/ship/deck";

int do_drop(string str);

void
create_deck() {
  set_short("on the boat");
  set_long("This sturdy wooden boat doesn't have any oars or sails. A few "+
	   "seats are built into the hull, looking well made and even "+
	   "comfortable. It floats high on the calm water, bobbing "+
	   "slightly.\n" );

  add_prop(ROOM_I_INSIDE, 1);

  add_item(({"boat", "wooden boat"}),
	   "The boat looks well constructed, made of thick, dark wood, "+
	   "too thick really to be called planks.\n" );
  add_item("seats", "The wooden seats are smooth and carved for comfort.\n");
  add_item(({"water", "calm water"}),
	   "The water is glassy smooth and very clear. At the front of the "+
	   "boat, beneath the surface, you see a long grey creature.\n" );
  
  // creature description depends on its food state.
  add_item( ({"creature", "grey creature"}), "@@describe_creature" );

  // deck and bump sounds depend on creature's state as well.
  set_deck_sound( "@@sounds" );
  set_bump_sound( "@@bump_sound");
  
  add_prop( OBJ_S_WIZINFO,
        "This boat has no visible captain, and is pulled from beach to "+
        "beach by an underwater creature. This creature must be fed by the "+
        "player to make it move without a huge delay. Feeding occurs by "+
 	"dropping food in the water.  Examining the creature from the deck "+
 	"will give a clue as to its current state.  If enough food is "+
 	"dropped into the "+
 	"water, the boat will reach the opposite shore. If the creature "+
 	"becomes hungry during the trip, it will slow down. The "+
 	"creature can be 'called' from either 'dock' by beating on the "+
 	"metal pipe with a wielded weapon, but it will "+
	"only respond if it is hungry.\n"+
	"Future: The puller may be attackable by stabbing into the water.\n");
}

void
init()
{
  ::init();
  add_action(do_drop, "drop" );
}

private void
feed_creature(int food_amount, int heap_count)
{
  string food_string;
  
  D( "in feed_creature,  heap count = " + heap_count + "\n" );
  
  food_string = (heap_count > 1) ? "first bite" : "food";
  
  TP->catch_msg( "As you drop the food into the water, the creature's " +
		"eyes glow brighter. It lunges for the " + food_string +
		", flashing its sharp teeth.\n" );
  if (heap_count > 1) 
    TP->catch_msg( "The beast dives deep catching the food, before " +
		  "noticing the rest of it and stopping. The boat " +
		  "bumps into it causing a snarl, and it lunges forward " +
		  "again catching edible scraps scattered around.\n" );
  else 
    TP->catch_msg( "The beast dives deeply catching the food.\n" );

  // Send a message to ship which will send it to the puller...
  ship->add_food(food_amount * heap_count);
  
  if ((ship->query_puller())->query_food_state() == HUNGRY)
    TP->catch_msg("The creature still looks hungry when it appears " +
		  "on the surface again.\n");
}

private void
msg_non_food() {
  
  D( "Non-food was dropped into the water... blub blub.\n" );
  tell_room(environment(TP),
	    "One of the creature's eyes follows it while it sinks out " +
	    "of sight.\n");
}

private void
msg_drop(string text) {
  TP->catch_msg("You drop " + text + " into the water.\n");
  say(QCTNAME(TP) + " drops " + text + " into the water.\n");
}

// Drop num items out of ob (can be heap). Text is the string typed
// by player as in <drop text in water>
private int
process_dropped(int num, object ob, string text) {
  int n_heap;
  object tp = this_player();

  // do not destroy undroppable things like guild items or poisons.
  if (ob->query_prop(OBJ_M_NO_DROP))
    return 0;

  if (function_exists("create_heap", ob)) { // we have heap here..
    D("dropping heap object.\n");

    n_heap = ob->num_heap();
    if (ABS(num) > n_heap) // cannot drop third potato when we have only one
      return 0;
    if (num < 0)
      num = 1; // num == -2 means 'second chicken', which does not differ
               // from just 'chicken' when dealing with heaps.
    
    msg_drop(text);
    
    if (function_exists("create_food", ob)) { // it is heap food object.
      if (function_exists("create_leftover", ob)) {
	D("Leftover dropped in the water.\n");
	// for us each leftover is enough for exactly one step
	feed_creature(FOOD_CONSUMPTION + 1, num);
      } else { // its just food. not leftover
	D("Food was dropped into the water.\n");
	feed_creature(ob->query_amount(), num); // yummy!
      }
    }
    else
      msg_non_food(); // they dropped non-edible things like coins, let them
                      // sink
    
    if (num == n_heap)
      ob->remove_object(); // generous, nothing left.
    else
      ob->set_heap_size(n_heap - num); //substract dropped stuff from heap.
    return 1;
  }
  else { // not heap
    if (num != 1)
      return 0; // do not handle 'drop two swords in water'
    
    msg_drop(text);
    msg_non_food(); 
    ob->remove_object(); // let them sink stuff if they want
    return 1;
  }
}

// action handler
int
do_drop(string str) {
  object ob;
  int num;
  string text;
  
//  D("do_drop called\n");

  // parse_command working on empty list is fast like sscanf
  // We need the text because ob->short() does not work correclty
  // with heaps. %o below will match the heap before split.
  if (!parse_command(str, ({0}), "%s 'in' [the] 'water'", text))
    return 0;

  notify_fail("Drop what in the water?\n");
  
  // drop coin in water or drop steak in water go here
  if (parse_command(str, all_inventory(TP), "%o 'in' [the] 'water'", ob))  
    return process_dropped(1, ob, text);
  
  // drop second coin in water or drop 2 steaks in water go here
  if (parse_command(str, all_inventory(TP), "%d %o 'in' [the] 'water'",
		    num, ob))  
    return process_dropped(num, ob, text);
  return 0; // should never get here.
}

static string *slow_snd = ({
  "Circles of ripples appear beside the boat, then are left behind.\n",
  "The boat slows a bit, then resumes drifting over the sea.\n",
  "The boat coasts silently across the great sea.\n",
});
static int slow_snds = sizeof(slow_snd);

static string *fast_snd = ({
  "The boat moves fast ahead, leaving behind a trail of white foam.\n",
  "The boat lunges forward momentarily, then glides along the water.\n",
  "You feel the boat being pulled fast ahead and almost fall overboard.\n"
});
static int fast_snds = sizeof(fast_snd);

// sounds VBFC
string
sounds() {
  switch ((ship->query_puller())->query_food_state()) {
  case FED :
    return fast_snd[random(fast_snds)];
  case HUNGRY:
    return slow_snd[random(slow_snds)];
  default:
    return "You feel that something is wrong with the boat. Leave bug " +
      "report please.\n";
  }
}

// bump sound VBFC
string
bump_sound() {
  switch ((ship->query_puller())->query_food_state()) {
  case FED :
    return "You hardly keep your balance as the boat is thrown on the " +
      "sandy beach.\n";
  case HUNGRY :
    return  "The boat drifts into the beach and stops.\n";
  default:
    return "You feel that something is wrong with the boat. Leave bug " +
      "report please.\n";
  } 
}

// stripped down from the standard ship code
void
ship_arrived(mixed where) {
  ship = previous_object();
  if (where->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER) {
    tell_room(this_object(), check_call(bump_sound));
    ship->set_board_enable(1);
    exit_enabled = 1;
  }
  else {
    exit_enabled = 0;
    tell_room(this_object(), check_call(deck_sounds));
  }
} 

// function for describing the creature,
// based on the 'fed' state.
string
describe_creature() {
  switch ((ship->query_puller())->query_food_state()) {
  case FED :
    return "Its body seems to be grey, with glowing eyes; you can't " +
      "determine more about how it looks. It's swimming straight ahead " +
      "at a good speed.\n";
  case HUNGRY :
    return "Its grey skin is sleek. Two glowing eyes at the front of " +
      "the head stare up at you. Every now and then they blink and a " +
      "large mouth opens hungrily to reveal teeth and a long tongue.\n";
  default:
    return "It looks like something is wrong in the fabric of space. " +
      "Leave bug report or use <commune here>.\n";
  }
}


