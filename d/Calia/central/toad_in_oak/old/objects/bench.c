/*
 * /d/Calia/central/toad_in_oak/objects/bench.c
 *
 * A generic bench that can be installed (not included) into a room.
 * 
 * HISTORY: [00-01-09] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 2000
 *
 */

//  INCLUSIONS AND DEFINITIONS

inherit "/std/object"; 

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include "defs.h"

// GLOBAL VARIABLES
   
object *Bench = ({}); 
string Parse_String = "[down] [on] [the] [long] 'bench'";
int Limit = 0; 

//  FUNCTIONS

/*  Forward Declarations  */ 

string contents(object player); 
int exit();
void leave(object player);
void leave_messages(object player);
void set_limit(int new_limit); 
void set_parse_string(string new_string); 
int sit(string command);
int stand(string command);

/*  Function    contents
    Purpose     Creates a list fo mortals sitting on the bench 
    Arguments   None
    Returns     String
*/ 
string
contents(object player)
{
    string *contents = ({}); 
    string return_value = ""; 
    string verb = " are "; 
    int pos;

    if (player == 0 )
    {
        player = this_player();
    }

    if (sizeof(Bench))
    {
        contents = Bench->query_art_name(player); 
        
        pos = member_array(player, Bench); 
    
        if (pos >= 0) 
        {
            contents -= ({contents[pos]}); 
            contents = ({"you"}) + contents; 
        }

        if (sizeof(contents) == 1 && contents[0] != "you")
        {
            verb = " is "; 
        }

        return_value = capitalize(COMPOSITE_WORDS(contents)) + verb + 
            "sitting on the " + query_short() + "\n"; 
    }

    return return_value; 
}

/*
    Function    exit
    Purpose     Called when somebody exits the room. Makes sure they stand
                up if necessary. This should be included directly or indirectly 
                in every add_exit of the room. 
    Arguments   None
    Returns     0
*/
int 
exit()
{
    object player = this_player(); 

    if (member_array(player, Bench) >= 0)
    {
        write("You stand up rather than trying to drag the " + query_short() + 
            " along with you.\n"); 
        say(QCTNAME(player) + " stands up.\n"); 
        
        Bench -= ({player});         
        player->unset_no_show_composite(); 
    }

    return 0; 
}

/* 
    Function    leave
    Purpose     Removes players from the bench as they try to leave the room. 
                This should be called from the rooms leave_inv function
    Arguments   object leaving, destination
    Returns     Nothing
*/
void
leave(object player)
{

    if (member_array(player, Bench) >= 0 )
    {
        Bench -= ({player});         
        player->unset_no_show_composite(); 

        set_alarm(0.5, 0.0, &leave_messages(player)); 
    }
}

/*  Function    leave_messages
    Purpose     Prints messages when a player teleports from a sitting
                position
    Arguments   Player teleporting
    Returns     Nothing
*/
void
leave_messages(object player)
{
    player->catch_msg("You struggle for a moment to stay on your feet after " + 
        "arriving in a sitting position.\n"); 
    tell_room(environment(player) , QCTNAME(player) + " flails " + 
        player->query_possessive() + " arms wildly trying not to fall " +
        "on " + player->query_possessive() + " bottom.\n", player); 
}
   
/*  Function    set_limit 
    Purpose     Change the number of people who can sit on the bench
    Arguments   new limit
    Returns     Nothing */ 
void
set_limit(int new_limit)
{
    Limit = new_limit; 
}

/*  Function    set_parse_string
    Purpose     Change the string used to parse the players sit command
    Arguments   new string
    Returns     Nothing
*/ 
void
set_parse_string(string new_string)
{
    Parse_String = new_string; 
}

/*  Function    sit
    Purpose     Adds properties and so on when a player sits on the bench.
                This is a seperate function so that other functions can make a
                person sit without duplicating effort                
    Arguments   player sitting
    Returns     Nothing
*/ 
int
sit(string command)
{
    object player = this_player(); 
    int success = 1; 

    if (member_array(player, Bench) == -1) 
    {
        if (!command || parse_command(command, this_object(), 
            Parse_String))
        {

            if (Limit == 0 || sizeof(Bench) < Limit)
            {
                write("You sit down on the " + query_short() + ".\n"); 
                say(QCTNAME(player) + " sits down on the " + query_short() + 
                    ".\n"); 

                /*  Add the player to the array of bench contents  */ 
                Bench += ({player}); 
    
                /*  This makes certain that the player does not appear in the 
                    normal inventory  of the room*/
                player->set_no_show_composite(1); 
            }
            else
            {
                write("There isn't enough room for you on the " + 
                    query_short() + ".\n");         
            }
        }
        else
        {
            notify_fail("Sit where?\n"); 
            success = 0; 
        }
    }
    else
    {
        notify_fail("You're already sitting down.\n"); 
    
        success = 0;
    }

    return success; 
}

/* 
    Function    stand
    Purpose     Does everything necessary to make somebody stand up except
                the messages. 
    Arguments   Player standing up 
    Returns     Nothing
*/ 
int
stand(string command)
{
    object player = this_player(); 
    int success = 1; 

    if (member_array(player, Bench) >= 0) 
    {
        if (!command || command == "up")
        {
            write("You stand up.\n"); 
            say(QCTNAME(player) + " stands up.\n"); 
      
            Bench -= ({player}); 
    
            player->unset_no_show_composite(); 
        }
        else
        {            
            success = 0; 
        }    
    }
    else
    {
        notify_fail("You're not sitting down.\n"); 
    
        success = 0;
    }

    return success;
}

// OBJECT DEFINITION

void
create_object()
{
    set_name("bench"); 
    set_long("A long wooden bench.\n"); 

    add_prop(OBJ_M_NO_GET, "You and what army?"); 
    set_no_show_composite(1); 
}

void
init()
{
    ::init(); 

    add_action(stand, "stand"); 
    add_action(sit, "sit"); 

    return;
}
