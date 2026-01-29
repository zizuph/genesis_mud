/*
 * decap_head.c
 *
 * Special head leftover for livings that have been decapitated
 * by blademasters.
 *
 * HISTORY:
 *   Khail - January 2/98 : Added a mask to the short() function
 *                          to clean up the short desc, and prevented
 *                          decapitated heads from merging as heap
 *                          objects.
 *   Khail - January 14/98: Added a query_recover() mask to return
 *                          "" always so heads wouldn't recover. This
 *                          is so players can't recover 40 heads and
 *                          get bugged when logging in since heads
 *                          no longer heap.
 *
 *  Tomas - Sept 2000:  increased set_amount to 400 from 10
 *  
 *  Treacher - Nov 2003: Made the head kickable
 * 
 *  Cotillion - Okt 2020: Fixed the heap code.
 *
 * Khail - Dec 12/97
 */
#pragma strict_types

#include "/d/Khalakhor/guilds/blademasters/objects/defs.h"
#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

inherit "/std/leftover";

string l_source;  // Head source

/*
 * Function name: create_leftover
 * Description  : Turns this object into a leftover head.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_leftover()
{
    set_name("head");
    set_pname("heads");
    add_name("leftover");
    add_pname("leftovers");
    set_adj("bloody");
    add_adj("decapitated");
    set_amount(400);
}

string
query_head_source()
{
    return l_source;
}

/*
 * Function name: custom_long
 * Description  : Generates a long description that varies
 *                depending on who's doing the looking.
 * Arguments    : n/a
 * Returns      : A string to use as a long desc.
 */
public string
custom_long()
{
    object pob;

    pob = vbfc_caller();
    if (!pob || !interactive(pob) || pob == this_object())
        pob = this_player();
    if (pob && pob->query_real_name() == l_source)
        return "Staring into the face of the bloody, decapitated " +
            "head, you recognize your own eyes staring back " +
            "at you!\n";
    else if (pob && pob->query_met(l_source))
        return "Staring into the face of the bloody, decapitated " +
            "head, you recognize " + capitalize(l_source) +
            "'s lifeless eyes staring back at you!\n";
    else
        return "Staring into the face of the bloody, decapitated " +
            "head, you wonder who this unknown " + l_race +
            " was.\n";
}

/*
 * Function name: setup_head
 * Description  : Sets this up as a head to match a given corpse.
 * Arguments    : who - Object pointer to the living who's head
 *                      this is.
 * Returns      : n/a
 */
public void
head_init(string name)
{
    l_source = name;
    add_adj(l_race);
    set_short(l_race + " head");
    set_pshort(l_race + " heads");
    set_long("@@custom_long");

    add_prop(HEAP_S_UNIQUE_ID, "_decap_head_" + l_race + "_" + l_organ + "_" + l_source);
}    

public void
setup_head(object who)
{
    leftover_init("head", who->query_race_name());
    head_init(lower_case(who->query_name()));

    int weight = (7 * who->query_prop(CONT_I_WEIGHT)) / 1000;
    set_amount(weight);

    int volume = (9 * who->query_prop(CONT_I_WEIGHT)) / 1000;
    add_prop(HEAP_I_UNIT_VOLUME, volume);

    object room = environment(who);
    add_prop(OBJ_O_LOOTED_IN_ROOM, room);
}

void
config_split(int new_num, object orig)
{
    ::config_split(new_num, orig);
    head_init(orig->query_head_source());
}

/*
 * Function name: query_recover (MASK)
 * Description  : Called to get a string to recover this object
 *                with after arma.
 * Arguments    : n/a
 * Returns      : Always returns "" to prevent this object from
 *                recovering.
 */
public string
query_recover()
{
    return "";
}

/*
 * Function name: find_exit
 * Description  : Finds an exit, and the corresponding exit
 *                in the target room.
 * Arguments    : direction - The direction in which the
 *                  exits is searched for. If no argument
 *                  is givven, a random obvious standard 
 *                  exit will be used.
 * Returns      : An array consisting of three strings.
 *                 0 - Exit name in the origin room
 *                 1 - Exit name in the target room
 *                 2 - Path to target room
 */
mixed
find_exit(string direction) {
  string   this_path, this_exit, other_path, other_exit;
  mixed    exits, other_exits;
  string  *obvious_exits;
  int      index;
  object to_dest;

  this_path = file_name(environment());
  
  exits = environment()->query_exit();
  obvious_exits = environment()->query_obvious_exits();

  if((direction && !exits) ||
     (!direction && sizeof(obvious_exits) == 0))
    return ({});

  if(direction)
    index = member_array(direction, exits);
  else {
    this_exit = obvious_exits[random(sizeof(obvious_exits))];
    index = member_array(this_exit, exits);
  }
  if(index < 0)
    return ({});
  // Don't kick that way if there's a block
  if(exits[index + 1] != 0)
    return ({});

  this_exit = exits[index];
  if(this_exit != "north" && this_exit != "south" &&
     this_exit != "east" && this_exit != "west" &&
     this_exit != "northwest" && this_exit != "northeast" &&
     this_exit != "southwest" && this_exit != "southeast")
    return ({});

  other_path = exits[index - 1];
  to_dest = find_object(other_path);
  other_exits = to_dest->query_exit();
  index = member_array(this_path, other_exits);
  if(index < 0)
    other_exit = "";
  else
    other_exit = other_exits[index + 1];

  return ({this_exit, other_exit, other_path});
}

/*
 * Function name: do_kick_head
 * Description  : Starts the kicking sequence
 * Arguments    : arg - The argument must be a head
 *                on the ground, and can include a
 *                direction.
 * Returns      : 1 or 0
 */
public int
do_kick_head(string arg) {
  mixed exit_ob;
  object kick_what;
  string where, exit, other_exit, target;
  
  //Check that the player actually can see the head
  if(!CAN_SEE_IN_ROOM(this_player()) ||
     !CAN_SEE(this_player(), this_object()))
    return 0;

  if(!living(environment()) && arg) {
    parse_command(arg, this_object(), " %o [to] [the] %w", 
                  kick_what, where);
    if(kick_what != this_object())
      return 0;
    
    exit_ob = find_exit(where);
    if(sizeof(exit_ob) == 0) {
      say(QCTNAME(this_player()) +
          " kicks the " + short() + " making it roll " +
          "about before it lies to rest again.\n");
      
      this_player()->catch_msg("You make a good kick at the " +
                               short(this_player()) + " making " +
                               "it roll about before it lies " +
                               "to rest at your feet again.\n");
    }
    else {
      exit = exit_ob[0];
      other_exit = exit_ob[1];
      target = exit_ob[2];
      say(QCTNAME(this_player()) +
          " kicks the " + short() + " so it rolls " +
          "off to the " + exit + ".\n", this_player());
      this_player()->catch_msg("You make a good kick at the " +
                               short(this_player()) + " making " +
                               "it roll off to the " +
                               exit + ".\n");
      move(target);
      if(other_exit != "") {
        tell_room(target, capitalize(LANG_ASHORT(this_object())) + " rolls " +
                  "in from the " + other_exit + ".\n");

      }
      else {
        tell_room(target, capitalize(LANG_ASHORT(this_object())) + " rolls " +
                  "into view.\n");
      }
    }

    //Make sure the head isn't hidden after being kicked
    add_prop(OBJ_I_HIDE, 0);    
    return 1;
  }
}

public void
init() {
  ::init();
  
  add_action(do_kick_head,  "kick");
}

