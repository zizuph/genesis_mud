/*
   Standard inside of a boat.

   Copyright Miguel Leith 1996 

   Coded by Maniac, April 96
   Updated, Maniac, 30/7/96

   Borrowed and modified by Arman Kharas with permission from Bishop
   14 April 2004
 
   2019-11-24 - Carnak - Changed the living check to interactive so it
                         doesnt prevent players from boarding when there
                         are 3 chipmunks on the boat, or a flying DA dragon.

*/

#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit BPATH + "std/boat_room_base";
inherit "/d/Calia/std/contents_desc";
inherit "/d/Calia/std/ahoy";
inherit "/d/Calia/std/owner"; 

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h> 
#include <gmcp.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include "/d/Calia/sys/water.h"
#include "/d/Ansalon/common/defs.h"

object boat_loc;
string boat_loc_str;
object boat_out;
string boat_out_str;
int num_passengers = 0; 

string* climb_string;

#define HARD_TO_JUMP 20
#define SAILING_SKILL 143020


/*
   Here create_room has some basics.  config_boat_inside() should be
   defined in the (outside) boat object to set up whatever special
   details one wants.
*/
void
create_bloodsea_room()
{
    set_short("Inside a small sailing ship");
    set_long("Inside a small sailing ship, common for the Bloodsea.\n");
    
}


int
query_inside_of_boat()
{
    return 1;
}


void
outer_room_check()
{
    if (!objectp(boat_loc))
        if (stringp(boat_loc_str))  {
            boat_loc_str->load_me();
            boat_loc = find_object(boat_loc_str);
        }
}


void
move_out(object player)
{
    outer_room_check(); 
    player->catch_tell("The ship begins leaking badly, and sinks!\n");
    player->move_living("outside", boat_loc, 1); 
}

public void
kick_out(object player)
{
    outer_room_check(); 
    player->move_living("overboard", boat_loc, 1); 
}


void
m_p_o()
{
    map(FILTER_PLAYERS(all_inventory(this_object())), move_out); 

    remove_object(); 
}


/* 
   This is called from the (outside object of the) boat when 
   it is removed, to move players outside the boat. 
   The inside of the boat is then removed.  
 */  
void
move_players_out()
{
    if (sizeof(FILTER_PLAYERS(all_inventory(this_object())))) 
        set_alarm(1.0, 0.0, m_p_o);
    else
        remove_object(); 
}


string
row_exit_desc()
{
    string red;

    outer_room_check();

    if (!stringp(red = boat_loc->row_exit_desc()))
        return "";
    else
        return red;
}

string
query_boat_vista()
{
    string bv;

    outer_room_check();

    if (!stringp(bv = boat_loc->query_boat_vista()))
        if (!stringp(bv = boat_loc->long())) 
            return "";
    else
        return bv;
}


string
query_contents_desc()
{
     string d;

     outer_room_check();

     if (!stringp(d = this_object()->contents_desc(boat_loc)))
         return "";
     else
         return d;
}


string
view_long()
{
    string ot, b, r, q; 

    b = query_boat_vista();
    if (!strlen(b)) 
        b = "It doesn't look like very interesting scenery actually."; 
    r = row_exit_desc(); 
    if (!strlen(r)) 
        r = "It seems you can't sail anywhere from here.\n"; 
    q = query_contents_desc();

    ot = (break_string(b, 65, "  } ") + "\n" + 
          break_string(q, 65, "  } ") + "\n");  
    return ("\n" + "  } Outside you see the following view:\n" + ot + r); 
}


varargs public mixed
long(string str)
{
    mixed lg;

    lg = ::long(str);

    if (str)
       return lg;

    return (lg + view_long()); 
}


/* Sets the associated object for the outside of the boat */
void
set_boat_out(object bo)
{
    if (objectp(bo)) {
        boat_out = bo;
        boat_out_str = MASTER_OB(bo);
    }
}



void
set_boat_loc(object bl)
{
     if (objectp(bl) && bl->query_prop(ROOM_I_IS)) {
         boat_loc = bl;
         boat_loc_str = file_name(bl);
     }
}

int
query_num_passengers()
{
    return num_passengers; 
}

object
query_boat_loc()
{
    return boat_loc; 
}

/* Needed for the map to know we are in a boat in a room somewhere else */
object
query_room_env()
{
    return boat_loc;
}

int
do_row(string str)
{
     int r;
     object o;

     outer_room_check();

     if (!objectp(boat_loc)) {
         notify_fail("Ack! No boat environment! This should not " +
                     "happen, please commune a wizard.\n");
         log_file("water", "Boat without any external boat location! " +
                          ctime(time()) + ", player was " +
                          this_player()->query_real_name() + ".\n");
         return 0;
     }

     if((TP->query_race_name() != "minotaur") &&
        (TP->query_guild_name_lay() != "Pirate of the Bloodsea") &&
        (TP->query_skill(SAILING_SKILL) < 30))
     {
     write("It seemed like a good idea at the time, however you " +
        "have no idea how to sail a ship!\n");
     say(QCTNAME(TP)+ " looks around the ship with bewilderment, " +
        HE(TP)+ " obviously has no idea how to sail a boat!\n");
     return 1;
     }


     if((TO->query_owner() != 0) && (TP != TO->query_owner()))
     {
       write("There is still an existing captain of this ship! You cannot " +
       "sail off with it until that has been rectified.\n");
       return 1;
     }

     if((TP->query_skill(SAILING_SKILL)/4) + query_num_passengers() > 
        boat_out->query_max_passengers())
     {
        r = boat_loc->try_row(str); 
   
        if (r)
             owned_object_action(this_player(), "sail " + str); 
        return r;
     }


     if((boat_out->query_max_passengers() > 19) &&
        (query_num_passengers() < 9))
     {
        write("This ship is too large to sail by yourself. You'll " +
        "need a score of crew to help you with it!\n");
        return 1;
     }
     if((boat_out->query_max_passengers() > 9) &&
        (query_num_passengers() < 3))
     {
        write("This ship is too large to sail by yourself. You'll " +
        "need a handful of crew to help you with it!\n");
        return 1;
     }



     r = boat_loc->try_row(str); 

     if (r)
          owned_object_action(this_player(), "sail " + str);  

     return r;
}


/* Move the boat to a new location, this is called from the water room one
   rowed _from_ when one tries to row in a legitimate direction */
void
carry_out_row(string direc, string to_path)
{
    object tp = TO->query_owner();
    object *players;

    if (!tp)
      tp = this_player(); 

    if (!stringp(to_path))
        return;

    tell_room(E(tp), QCTNAME(tp) + " sails " + LANG_THESHORT(boat_out) + " " + 
                             direc + ".\n", tp); 
    tp->catch_msg("You sail " + LANG_THESHORT(boat_out) + " " + direc + ".\n"); 

    boat_out->set_direc(direc); 
    boat_out->move(to_path);  
    set_boat_loc(find_object(to_path));

    remove_exit("out");
    add_exit(to_path, "out");

    tell_room(this_object(), view_long());

    /* Advise the GMCP of the new room. */
    players = filter(all_inventory(), interactive);
    foreach(object player: players)
    {
        if (player->query_gmcp(GMCP_ROOM))
        {
            gmcp_room_info(player);
        }
    }
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 

    if (interactive(ob)) 
        num_passengers++; 
    enter_owned_room(ob, from);  
}


void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to); 

    if (interactive(ob))
        num_passengers--; 
    leave_owned_room(ob, to); 
}

string
investigate(string str)
{
    string outside_item;
    object *outside_ob, outside_obj; 

    if(!strlen(str))
    {
       write("Investigate what?\n");
       return "";
    }

    if(!P("spyglass",TP))
    {
       write("You need a spyglass to investigate distant objects!\n");
       return "";
    }

    outside_ob = FIND_STR_IN_OBJECT(str, query_boat_loc());     

    if(!intp(query_boat_loc()->long(str, this_player())))
    {
       outside_item = query_boat_loc()->long(str, this_player());
    }
    else if(sizeof(outside_ob))
    {
       if(sizeof(outside_ob) > 1)
       {
          write("Investigate one thing at a time.\n");
          return "";
       }
       outside_obj = outside_ob[0];
       outside_item = outside_obj->long();
    }
    else
    {
       outside_item = "You notice nothing of interest.\n";
    }


    write("You look through your spyglass and see:\n" +
    outside_item);
    say(QCTNAME(TP) + " looks through " +HIS(TP)+ " spyglass " +
    "and scans the horizon.\n");

    return "";

}

string
board(string str)
{
    string board_desc;
    object *outside_ob, outside_obj; 

    if(!strlen(str))
    {
       write("Board what?\n");
       return "";
    }

    outside_ob = FIND_STR_IN_OBJECT(str, query_boat_loc());     

    if(sizeof(outside_ob))
    {
       if(sizeof(outside_ob) > 1)
       {
          write("You can only board one ship at a time.\n");
          return "";
       }
       outside_obj = outside_ob[0];

       if(!outside_obj->query_ship())
       {
          write("You can only board ships!\n");
          return "";
       }

       board_desc = outside_obj->short();

       if(TP->query_skill(SS_ACROBAT) < HARD_TO_JUMP) 
       {
          write("You grab a rope from the rigging and swing mightily across to the other " +
          "ship! However, your acrobatic skills are less than admirable, and you end " +
          "up swinging back to your own ship and falling gracelessly to the deck!\n");
          say(QCTNAME(TP)+ " grabs a rope from the rigging and swings across to the " +
          board_desc+ "... and then to your amusement swings back across to your ship, " +
          "falling gracelessly to the deck, " +HIS(TP)+ " acrobatic skills leaving much to " +
          "be desired!\n");
          return "";
       }

       if (!objectp(outside_obj->query_boat_in()))  
           outside_obj->config_boat_inside(); 

       write("You grab a rope from the rigging above and swing across to the "+board_desc+ 
          ", landing with catlike grace on its deck.\n");
       say(QCTNAME(TP)+ " grabs a rope from the rigging above and swings across to the " +
          board_desc+ ", landing with catlike grace on its deck.\n");
       tell_room(outside_obj->query_boat_in(), QCTNAME(TP) + " swings across from another ship, " +
       "landing on the deck in front of you!\n");
       TP->move_living("M",outside_obj->query_boat_in(),1,0); 
       return "";
    }


    write("That ship is not around to board.\n");
    return "";

}


int
query_ship()
{
    return 1;
}

// Requires climb_string to be set with:
// {what_to_climb, emote/move, description}
// Move Example:
// {"second mast", "/d/Ansalon/ship/mast", "up the mast like a monkey"}
// Emote Example:
// {"second mast", "You try to climb up but fail.", "The brown-nosed big eared gnome tries to climb the mast but fails."}
int
climb(string str)
{
    if(!strlen(str))
    {
      notify_fail("What?\n");
      return 0;
    }
    
    if(sizeof(climb_string) != 3)
    {
      notify_fail("What?\n");
      return 0;
    }

    // Does the length of the string array match
    // What we require?
    if(sizeof(climb_string) == 3)
    {
      // Does the command the player gave match what 
      // we require?
      if(str == climb_string[0])
      {
	string secondStr = climb_string[1];
	if(strchar(secondStr[0]) == "/")
	{
	  this_player()->catch_msg("You manage to climb "+secondStr+".\n");
	  this_player()->move_living(climb_string[2], secondStr, 0, 0);
	  return 1;
	}
	else
	{
	  this_player()->catch_msg(secondStr);
	  tell_room(environment(this_player()), climb_string[2],this_player());
	  return 1;
	}
      }
      else
      {
	notify_fail("What?\n");
	return 0;
      }
    }
}

void set_climb_data(string* climb_data)
{
  climb_string = climb_data;
}


void
init()
{
    ::init();
    add_action(do_row, "sail");
    add_action(ahoy, "ahoy");
    add_action(investigate, "investigate"); 
    add_action(board, "board");
    add_action(climb, "climb");
}

