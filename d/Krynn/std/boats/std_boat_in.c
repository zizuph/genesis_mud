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

#include "std_boat_defs.h"
#include "/d/Krynn/common/defs.h"

inherit STD_BOAT_ROOM;
inherit STD_CONTENTS_DESC;
inherit STD_AHOY_CMD; 
inherit STD_BOAT_OWNER; 

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h> 
#include <gmcp.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>

#define BOAT_OWNER_PROP    "_krynn_boat_owner"
#define KRYNN_FLAG         "/d/Krynn/std/boats/sailing_ensign"
#define CURRENTLY_SAILING  "_mariner_captain_currently_sailing"


object boat_loc;
string boat_loc_str;
object boat_out;
string boat_out_str;
int num_passengers = 0;
 
int flag_raised;
mixed * flag_desc = ({ });
mixed * flag_data;
string player_name, flag_short, flag_long, boat_owner_prop;

string * climb_string;
string * flag_name;


string
flag_tells()
{
    if(!flag_raised)
        return "";

    if(!sizeof(flag_data))
        return "";

    switch(random(3))
    {
        case 0:
            return "The " +flag_data[0]+ " high up " +
                "on the main mast dances with the wind.\n";
            break;
        case 1:
            return "The wind catches the " +flag_data[0]+ " " +
                "hoisted high up on the main mast, making it " +
                "unfurl with a crack!\n";
            break;
        default:
            return "A strong gust of wind blusters across " +
                "the deck, making the " +flag_data[0]+ " " +
                "high up above you dance a merry jig!\n";
    }

    return "";
} 

/*
   Here create_room has some basics.  config_boat_inside() should be
   defined in the (outside) boat object to set up whatever special
   details one wants.
*/
void
create_boat_room()
{
    set_short("Inside a small sailing ship");
    set_long("@@boat_long_desc");  

    set_tell_time(360);
    add_tell("@@flag_tells"); 
}

string
boat_long_desc()
{
    if(sizeof(flag_desc))
    {
        return "Inside a small sailing ship, common for the seas " +
            "of Genesis. " +flag_desc[2]+ "\n";
    }
    return "Inside a small sailing ship, common for the seas of Genesis.\n";
}

public int
query_inside_of_boat()
{
    return 1;
}


void
outer_room_check()
{
    if (!objectp(boat_loc))
        if (stringp(boat_loc_str))  
        {
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

object
query_boat_out()
{
    return boat_out;
}

/* Sets the associated object for the outside of the boat */
void
set_boat_out(object bo)
{
    if (objectp(bo)) 
    {
        boat_out = bo;
        boat_out_str = MASTER_OB(bo);
    }
}

void
set_boat_loc(object bl)
{
     if (objectp(bl) && bl->query_prop(ROOM_I_IS)) 
    {
         boat_loc = bl;
         boat_loc_str = file_name(bl);
     }
}

int
query_num_passengers()
{
    return num_passengers; 
}

void
set_num_passengers(int num)
{
    num_passengers = num;
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

/* The skill needed to sail the ship. Same named function in sea rooms
   that are more difficult to sail through */
public int
query_sailing_difficulty()
{
    return boat_out->query_sailing_difficulty(); 
}

public int
query_ship_size()
{
    return boat_out->query_ship_size(); 
}

int
do_row(string str)
{
    int r;
    object o;

    outer_room_check();

    if (!objectp(boat_loc)) 
    {
        notify_fail("Ack! No boat environment! This should not " +
            "happen, please commune a wizard.\n");
        log_file("water", "Boat without any external boat location! " +
            ctime(time()) + ", player was " +
            this_player()->query_real_name() + ".\n");
        return 0;
    }

    // If you don't have minimal sailing skills you can't sail a ship!
    if((TP->query_skill(SAILING_SKILL) < DIFFICULTY_NOVICE))
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

    if(TO->query_prop(BOAT_OWNER_PROP) && 
        (TP->query_real_name() != TO->query_prop(BOAT_OWNER_PROP)))
    {
        write("While an ensign of another captain is raised up the main " +
            "mast, you cannot commandeer this ship.\n");
        return 1;
    }

    // If in combat with an npc on a ship you cannot keep sailing.
    // Will allow sailing against a player to avoid unwanted pvp 
    // ganking situations.

    if (TP->query_attack())
    {
        object enemy = TP->query_attack();

        if(enemy->query_npc())
        {
            write("You cannot sail the ship while in combat!\n");
            return 1;
        }
    }

    int sailing_skill = TP->query_skill(SAILING_SKILL);
    int ship_size = query_ship_size();
    int sailing_difficulty = query_sailing_difficulty();

    if(sailing_difficulty == NO_SAIL_ANCHORED)
    {
        write("This ship has been anchored here, and you are " +
            "unable to find the mechanism to raise the anchor.\n");
        return 1;
    }

    if(sailing_difficulty == NO_SAIL_DISABLED)
    {
        write("The steering for this ship has been damaged, and " +
            "you are unable to sail it.\n");
        return 1;
    }

    // Bigger ships can have crews helping to sail adding to the 
    // captains skill check.
    int crew_bonus = ((min(ship_size, query_num_passengers()) - 1) * 5);

    if((sailing_skill + crew_bonus) <= sailing_difficulty)
    {
        write("This ship is too large or you are too unskilling at " +
            "sailing to sail it by yourself. You'll " +
            "need more sailing skill or a number of willing crew " +
            "to help you sail it!\n");
        return 1;
    }
    else
    {
        r = boat_loc->try_row(str);  
  
        if (r)
        {
            owned_object_action(this_player(), "sail " + str);
        }
        return r;
    }

    notify_fail("Ack! Something went wrong! This should not " +
            "happen, please commune a wizard.\n");
    return 0;
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

    tell_room(environment(tp), QCTNAME(tp) + " sails " + 
        LANG_THESHORT(boat_out) + " " + direc + ".\n", tp); 
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

    if (interactive(ob))
        start_room_tells();

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
            write("You grab a rope from the rigging and swing mightily " +
                "across to the other ship! However, your acrobatic skills " +
                "are less than admirable, and you end up swinging back to " +
                "your own ship and falling gracelessly to the deck!\n");

            say(QCTNAME(TP)+ " grabs a rope from the rigging and swings " +
                "across to the " +board_desc+ "... and then to your " +
                "amusement swings back across to your ship, " +
                "falling gracelessly to the deck, " +HIS(TP)+ " acrobatic " +
                "skills leaving much to be desired!\n");
            return "";
        }

        if (!objectp(outside_obj->query_boat_in()))  
            outside_obj->config_boat_inside(); 

        write("You grab a rope from the rigging above and swing across " +
            "to the " +board_desc+ ", landing with catlike grace on its deck.\n");
        say(QCTNAME(TP)+ " grabs a rope from the rigging above and swings " +
            "across to the " +board_desc+ ", landing with catlike grace on its deck.\n");
        tell_room(outside_obj->query_boat_in(), QCTNAME(TP) + " swings across " +
            "from another ship, landing on the deck in front of you!\n");
        tell_room(environment(boat_out), QCTNAME(TP)+ " swings on a rope from the " +
            boat_out->short()+ " to the " +board_desc+ "!\n",
        this_player());
        TP->move_living("M",outside_obj->query_boat_in(), 1, 0); 

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

    return 0;
}

void 
set_climb_data(string* climb_data)
{
    climb_string = climb_data;
}

mixed *
query_flag_desc()
{
    return flag_desc;
}

int
do_raise(string str)
{
    object flag;

    if(!str)
        return 0;

    if(str != "ensign" && str != "flag")
    {
        notify_fail("Raise or hoist what? An ensign?\n");
        return 0;
    }

    if(flag_raised)
    {
        notify_fail("An ensign is already raised on this ship.\n");
        return 0;
    }

    if((TO->query_owner() != 0) && (TP != TO->query_owner()))
    {
        notify_fail("You are not the owner of the ship! You " +
            "cannot raise an ensign on it!\n");
        return 0;
    }

    if (!objectp(flag = present("_krynn_sailing_ensign", TP)))
    {
        write("You don't have an ensign to hoist!\n");
        return 1;
    }

    flag_data = flag->query_ensign_details();

    if(!sizeof(flag_data))
    {
        notify_fail("There is something wrong with your ensign. " +
            "Please bug report this!\n");
        return 0;
    }

    if(strlen(flag_data[4]) > 1)
        if (!TP->query_wiz_level() && 
            (TP->query_guild_name_lay() != flag_data[4]) &&
            (TP->query_guild_name_occ() != flag_data[4]) && 
            (TP->query_guild_name_craft() != flag_data[4]) &&
            (TP->query_guild_name_race() != flag_data[4]))
        {
            write("You cannot fly that ensign! You are not a member " +
                "of that guild!\n");
            return 1;
        }

    player_name = TP->query_real_name();
    flag_short = flag_data[0];
    flag_long = flag_data[1] + capitalize(player_name) + ".";
    flag_name = flag_data[3];

    flag_desc = ({ player_name, flag_short, flag_long, flag_name });

    write("You hoist your " +flag_desc[1]+ " ensign up the main mast, " +
        "letting everyone know you are the master of this ship!\n");
    say(QCTNAME(TP)+ " hoists " +LANG_ADDART(flag_desc[1])+ " ensign up " +
        "the main mast.\n");
    tell_room(environment(boat_out), "The ensign of " +LANG_ADDART(flag_desc[1])+
        " suddenly rises up the main mast of the " +boat_out->short()+ "!\n",
        this_player());

    boat_out->update_boat_descriptions();
    flag->remove_object();
    flag_raised = 1;
    TO->add_prop(BOAT_OWNER_PROP, player_name);

    return 1;
}

int
do_lower(string str)
{
    object flag;

    if(!str)
        return 0;

    if(str != "ensign" && str != "flag")
    {
        notify_fail("Lower what? The ensign?\n");
        return 0;
    }

    if(!flag_raised)
    {
        notify_fail("No ensign is raised on this ship.\n");
        return 0;
    }

    if(TP->query_real_name() != TO->query_prop(BOAT_OWNER_PROP) &&
        !TP->query_wiz_level())
    {
        notify_fail("You are not the owner of the ship! You cannot " +
            "lower the ensign flag.\n");
        return 0;
    }

    write("You lower the " +flag_desc[1]+ " ensign from the main mast " +
        "and store it away for safe keeping.\n");
    say(QCTNAME(TP)+ " lowers " +LANG_ADDART(flag_desc[1])+ " ensign from " +
        "the main mast and stores it away.\n");
    tell_room(environment(boat_out), "The ensign of " +LANG_ADDART(flag_desc[1])+
        " is suddenly lowered from the main mast of the " +boat_out->short()+ ".\n",
        this_player());

    if(!sizeof(flag_data))
    {
        write("There is something wrong with your ensign when lowering it. " +
            "Please bug report this!\n");
    }

    seteuid(getuid());
    flag = clone_object(KRYNN_FLAG);
    flag->set_ensign_details(flag_data);
    flag->create_the_ensign();
    flag->move(TP, 1);

    flag_raised = 0;
    remove_item(flag_desc[3][0]);
    flag_desc = ({ });
    flag_data = ({ });
    boat_out->update_boat_descriptions();
    TO->remove_prop(BOAT_OWNER_PROP);

    return 1;
}

void
init()
{
    ::init();
    add_action(do_row, "sail");
    add_action(do_raise, "raise");
    add_action(do_raise, "hoist");
    add_action(do_lower, "lower");
    add_action(ahoy, "ahoy");
    add_action(investigate, "investigate"); 
    add_action(board, "board");
    add_action(climb, "climb");
}

