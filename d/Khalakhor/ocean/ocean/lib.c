/*
 * Common functions library
 * Tapakah, 10/2021
 */

#pragma strict_types
#pragma no_clone

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>

#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/std/room";
inherit "/d/Khalakhor/lib/logger";

/* Global Variables */
string  sink_path;
string *row_exits_arg   = ({ });
string *row_exits_path  = ({ });
int    *row_exits_tired = ({ });
mixed  *row_exits_check = ({ });

object *boats = ({ }); 
string  boat_vista; 

int   sailing_difficulty = 0;
mixed sailing_difficulty_message = 0;
mixed sailing_fail_message = 0;

/* Returns the appropriate desc to be added for the row exits */
string
row_exit_desc ()
{
  if (! sizeof(row_exits_arg)) {
    log_me(TPQN + " sailed into room without exits", "error", file_name(TO));
    return "You have sailed into a vortex without an exit!\n";
  }
  string desc;
  desc = "";
  if (sizeof(row_exits_arg))
    desc += ("You may sail: " + COMPOSITE_WORDS(row_exits_arg)+".\n");
  return desc;
}

/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */
int
query_standard_water_room ()
{
  return 1; 
}

/* Set the path to the room where things will sink to, if any. 
   Non living objects will automatically sink to that exit. 
   You don't have to set this if you want things to sink "down", as
   this is done by default if you add a swim exit for that direction. */
void
set_sink_path (string sp)
{
  sink_path = sp;
}

string
query_sink_path ()
{
  return sink_path;
}

void
boat_enter (object b)
{
  boats = filter(boats, objectp); 
  boats += ({ b }); 
}

void
boat_exit (object b)
{
  boats = filter(boats, objectp); 
  boats -= ({ b }); 
}

object *
query_boats ()
{
  boats = filter(boats, objectp); 
  return boats; 
}
 
void
set_boat_vista (string s)
{
  boat_vista = s; 
}

string
query_boat_vista ()
{
  return boat_vista;
}

/* Code to check the sailing skill requirement of the sailor for
 * this particular room.
 */

void
set_sailing_difficulty (int skill)
{
  sailing_difficulty = skill;
}

int
query_sailing_difficulty ()
{
  return sailing_difficulty;
}

void
set_sailing_difficulty_message (string msg)
{
  sailing_difficulty_message = msg;
}

mixed
query_sailing_difficulty_message ()
{
  return sailing_difficulty_message;
}

void
set_sailing_fail_message (string msg)
{
  sailing_fail_message = msg;
}

mixed
query_sailing_fail_message ()
{
  return sailing_fail_message;
}

string
query_sailing_difficulty_desc ()
{
  int difficulty = query_sailing_difficulty();

  switch (difficulty) {
  case 0..TRICKY_DIFFICULTY-1:
    return "The waters here are comfortable to navigate.";
  case TRICKY_DIFFICULTY..ROUGH_SEAS_DIFFICULTY-1:
    return "The waters here are tricky to navigate.";
  case ROUGH_SEAS_DIFFICULTY..HIGH_SEAS_DIFFICULTY-1:
    return "The waters here are challenging to navigate.";
  case HIGH_SEAS_DIFFICULTY..IMPOSSIBLE_SEAS_DIFFICULTY-1:
    return "The waters are extremely challenging to navigate.";
  default:
    return "The waters here are near impossible to navigate.";
  }
}

string
dir_alias (string str)
{
  switch (str) { 
  case "n" : return "north"; 
  case "s" : return "south"; 
  case "e" : return "east"; 
  case "w" : return "west"; 
  case "nw": return "northwest"; 
  case "ne": return "northeast"; 
  case "se": return "southeast"; 
  case "sw": return "southwest"; 
  case "u" : return "up"; 
  case "d" : return "down"; 
  default  : return str;
  }
}


/*
 * This is the function which checks the rowing action and makes 
 * the call to carry out the row if it's possible. 
 * It is called from the inside of the rowing boat itself when a 
 * player does an action there. 
 */

int
fail_by_skill (object tp, int difficulty, string exit)
{
  mixed sail_fail;
  if (tp->query_skill(SAILING_SKILL) < difficulty) {
    if(tp->id("_ansalon_charter_captain"))
      tp->not_enough_skill_response();
    else {
      sail_fail = exit->query_sailing_fail_message();
      if (!stringp(sail_fail))
        sail_fail =
          "The conditions in that direction are beyond " +
          "your sailing skill to navigate through!\n";
      notify_fail(sail_fail);
    }
    return 1;
  }
  return 0;
}

mixed
fail_by_size (object tp, int difficulty)
{
  int ship_size = environment(tp)->query_ship_size();
  string size_fail = 0;
  switch(ship_size) {
  case 0..SLOOP:
    if(difficulty > NORMAL_DIFFICULTY)
      size_fail = "too tricky for this small";
  case CUTTER:
    if(difficulty > CONDITIONS_TRICKY)
      size_fail = "too challenging for this";
  case SCHOONER:
    if(difficulty > CONDITIONS_CHALLENGING)
      size_fail = "way too challenging for this";
  case CORVETTE:
    if(difficulty > CONDITIONS_EXT_CHALLENGING)
      size_fail = "way too extreme for this ";
  }
  if (size_fail && tp->id("_ansalon_charter_captain"))
    size_fail = "";
  return size_fail;
}

int
try_row (string str)
{
  int e, tired, difficulty;
  object row_to;
  object charter_captain = environment(TP)->query_owner();
  object tp = TP;
  string size_fail;
  
  if (!str)
    NF0("Sail where?\n");

  if(tp != charter_captain && charter_captain->id("_ansalon_charter_captain"))
    tp = charter_captain; 

  str = dir_alias(str);

  e = member_array(str, row_exits_arg);

  if (e == -1)
    NF0("You can't sail in that direction.\n");
  if (this_object()->check_call(row_exits_check[e])) 
    return 1;

  difficulty = row_exits_path[e]->query_sailing_difficulty();
  tired      = row_exits_tired[e] * difficulty/10; 
  if (tp->query_fatigue() < tired) 
    NF0("You are too tired to sail anywhere at the moment. " +
        "You decide to drift where you are.\n"); 

  if (sizeof(row_exits_path[e]->query_boats()) >= KHALAKHOR_MAX_BOATS_IN_ROOM) 
    NF0("Oh dear! It seems there are too many ships " +
        "over there and your ship won't fit!\n"); 

  if (fail_by_skill(tp, difficulty, row_exits_path[e]))
    return 0;

  if (size_fail = fail_by_size(tp, difficulty)) {
    if (strlen(size_fail)) {
      size_fail = sprintf("The sailing conditions in that direction are %s " +
                          "ship to handle! You will need a bigger ship!\n",
                          size_fail);
      NF(size_fail);
    }
    else
      tp->ship_too_small_response();
    return 0;
  }
                  
  
  if (row_exits_path[e]->query_sailing_difficulty_message())
    tp->catch_tell(row_exits_path[e]->query_sailing_difficulty_message());

  tp->add_fatigue(-tired);
  environment(tp)->carry_out_row(str, row_exits_path[e]); 
  return 1;
}

/*
 * Function name: add_swim_exit
 * Description:   Add one swim exit to the room. 
 */
varargs void
add_swim_exit (string place, string cmd, mixed efunc, mixed tired, 
               mixed non_obvious)
{
  if ((cmd == "down") && (!stringp(query_sink_path())))
    set_sink_path(place); 

  add_exit(place, cmd, efunc, tired, non_obvious);  
}

/*
 * Function name: add_wade_exit
 * Description:   Add one wade exit to the room. 
 */
int
add_wade_exit (string place, string cmd, mixed efunc, mixed tired,
               mixed non_obvious)
{
  add_exit(place, cmd, efunc, tired, non_obvious); 
}

/*
 * Function name: add_row_exit
 * Description:   Add one ROW exit (for rowing boats) to the room. 
 * Arguments:     path: The filename of the room to move to
 *                arg:  The argument given after "row" e.g.
 *                       "north", "cave"
 *                check: A check to see if can move in that direction,
 *                       often uses vbfc. Possible values are: 
 *                       0: Direct move to destination
 *                       1: Can not move in this dir, do not try others
 *                tired: How much more tired the player should become from
 *                       rowing in that direction. Default is 1.
 */

varargs void
add_row_exit (string path, string arg, mixed check, int tired)
{
  if (! tired)
    tired = 1;

  row_exits_path  += ({ path  });
  row_exits_arg   += ({ arg   });
  row_exits_check += ({ check });
  row_exits_tired += ({ tired });
}


/*
 * Function name: remove_row_exit
 * Description:   Remove one row exit from the room.
 * Arguments:     arg:   The argument given after "row" for the exit to be 
 *                       removed.
 */
int
remove_row_exit (string arg)
{
  int i;

  if (query_prop(ROOM_I_NO_EXTRA_EXIT))
    return 0;

  i = member_array(arg, row_exits_arg);
  if (i == -1) 
    return 0;

  row_exits_arg   = exclude_array(row_exits_arg, i, i);
  row_exits_path  = exclude_array(row_exits_path, i, i);
  row_exits_check = exclude_array(row_exits_check, i, i);
  row_exits_tired = exclude_array(row_exits_tired, i, i);
  return 1;
}


/* An object sinks */
void
sink (object ob)
{
  string sp, sv;

  if (!objectp(ob)) 
    return;

  if (!objectp(present(ob, this_object())))
    return;

  if (!stringp(sp = query_sink_path()))
    return;

  sv = ((ob->num_heap() > 1) ? "sink" : "sinks"); 
  tell_room(this_object(), capitalize(LANG_THESHORT(ob)) + 
            " " + sv + " downwards.\n");
  ob->move(sp);
  tell_room(sp, capitalize(LANG_THESHORT(ob)) + " " + sv + " in.\n");
}


int
deep_water_room (object r)
{
  return r->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER || 
    stringp(r->query_sink_path()) ? 1 : 0;
}

void
leave_inv(object ob, object to)
{
  object dob;
  ::leave_inv(ob, to);

  if (!living(ob)) 
    return;

  /* quitting */
  if (!objectp(to)) 
    return;

  dob = ob->query_prop(LIVE_O_DROWN_OB);
  if (!objectp(dob)) 
    return;

  /* If they've gone linkdead, we'll not remove the drown object. */ 
  if (file_name(to) == OWN_STATUE) 
    return;

  /* Otherwise, if they're gone into a room which isn't one of 
     our standard underwater rooms, get rid of the drown object. */ 
  if (!to->query_standard_water_room()) 
    dob->remove_object();

  /* Another possibility is if you've swum to the surface, in which  
     case catch your breath but retain the drown object. */ 
  if (!(to->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER))
    dob->reset_oxygen_debt(); 
}

varargs int
no_go (int force_no = 0)
{

  if(this_player()->query_wiz_level())
    return 0;

  if(SAILING_OPEN && !force_no)
    return 0;
    
  write("You decided not to sail in that direction, as the waters are " +
        "uncharted. Rumour has it that those who do sail too far into the " +
        "high seas of Genesis are never seen of again!\n");
  return 1;
}
