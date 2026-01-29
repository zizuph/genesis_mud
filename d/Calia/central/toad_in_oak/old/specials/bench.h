/*
 * /d/Calia/central/toad_in_oak/specials/bench.c
 *
 * A generic bench that can be installed (not included) into a room.
 * 
 * HISTORY: [99-11-07] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */
// GLOBAL VARIABLES

object *Bench = ({}); 

// FUNCTIONS

/*  Function    bench_contents
    Purpose     Creates a list fo mortals sitting on the bench 
    Arguments   None
    Returns     String
*/ 
string
bench_contents()
{
    object player = this_player(); 
    string *contents = ({}); 
    string return_value = ""; 
    string verb = " are "; 
    int pos;

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
            "sitting on the bench.\n"; 
    }

    return return_value; 
}
    
/*  Function    bench_sit
    Purpose     Adds properties and so on when a player sits on the bench.
                This is a seperate function so that other functions can make a
                person sit without duplicating effort                
    Arguments   player sitting
    Returns     Nothing
*/ 
void
bench_sit(object player)
{
    /*  Add the player to the array of bench contents  */ 
    Bench += ({player}); 
    
    /*  This property indicates the player is sitting.  */ 
    player->add_prop(CALIA_TIO_GREEN_SITS, 1); 

    /*  This makes certain that the player does not appear in the normal 
        inventory  of the room*/
    player->set_no_show_composite(1); 
    
    return; 
}

/* 
    Function    bench_stand
    Purpose     Does everything necessary to make somebody stand up except
                the messages. 
    Arguments   Player standing up 
    Returns     Nothing
*/ 
void
bench_stand(object player)
{
    Bench -= ({player}); 
    
    player->remove_prop(CALIA_TIO_GREEN_SITS); 
    player->unset_no_show_composite(); 

    return;
}

/*  Function    exits_description
    Purpose     redefinition of base function to include the contents of the
                bench
    Arguments   None
    returns     Description of the exits from the room, plus whatevers sitting
                on the bench. 
*/
string
exits_description()
{
    return ::exits_description() + bench_contents(); 
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
   
/* 
    Function    leave_inv
    Purpose     Called when a player leaves the room. The last chance to catch
                a sitting duck... mortal. 
    Arguments   object leaving, destination
    Returns     Nothing
*/
void
leave_inv(object player, object dest)
{
    ::leave_inv(player, dest); 

    if (player->query_prop(CALIA_TIO_GREEN_SITS))
    {
        bench_stand(player);

        set_alarm(0.5, 0.0, &leave_messages(player)); 
    }
}

/*
    Function    player_sit
    Purpose     Allows a player to sit on the bench
    Arguments   command typed
    Returns     0/1
*/
int
player_sit(string command) 
{
    int success = 1; 
    object player = this_player(); 

    if (!player->query_prop(CALIA_TIO_GREEN_SITS))
    {
        if (!command || parse_command(command, this_object(), 
            "[down] [on] [the] [long] 'bench'"))
        {
            write("You sit down on the long bench.\n"); 
            say(QCTNAME(player) + " sits down on the long bench.\n"); 
    
            bench_sit(player); 
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
    Function    player_stand
    Purpose     Allows a player to stand up when they're on the bench
    Arguments   command typed
    Returns     0/1
*/ 
int
player_stand(string command)
{
    int success = 1; 
    object player = this_player(); 

    if (player->query_prop(CALIA_TIO_GREEN_SITS))
    {
        if (!command || command == "up")
        {
            write("You stand up.\n"); 
            say(QCTNAME(player) + " stands up.\n"); 
    
            bench_stand(player); 
        }
        else
        {
            success = 0; 
        }   
    }
    else
    {
        notify_fail("You aren't sitting down.\n"); 
        success = 0; 
    }

    return success; 
}

/*
    Function    room_exit
    Purpose     Called when somebody exits the room. Makes sure they stand
                up if necessary. 
    Arguments   None
    Returns     0
*/
int 
room_exit()
{
    object player = this_player(); 

    if (player->query_prop(CALIA_TIO_GREEN_SITS))
    {
        write("You stand up rather than trying to drag the bench " + 
            "along with you.\n"); 
        say(QCTNAME(player) + " stands up.\n"); 
        
        bench_stand(player); 
    }

    return 0; 
}

