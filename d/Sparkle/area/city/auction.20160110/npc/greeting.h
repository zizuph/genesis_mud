 /*
 * /w/novo/open/auction/npc/greeting.h
 *
 * This library will try to make a more natural greeting system as 
 * players enter the room.  It will greet people as they enter,
 * as well as inform them of whether they are busy or not.
 * between two rooms.  To use this:
 * Inherit this file
 * In your init_living method, call notify_player_entered
 *
 * write your own do_action() 
 * write your own greet_player() 
 * write your own tell_player_occupied() 
 * write your own tell_player_still_occupied() 
 *
 * call set_available() and set_occupied() to indicate that
 * the NPC is busy performing a task, or is done.
 *
 *
 * Created March 2008, by Novo
 *
 *
 */

#include "../defs.h";

private int Available=1;

private mapping Greeting_alarms = ([ ]);

private mapping Waiting_alarms = ([ ]);

//Prototypes
private void initial_greet(string name);
private void still_busy(string name);
private void find_waiting();



/*
 * Function name: add_waiting
 * Description: Indicate that a player should be added to the waiting list
 * Arguments  : name - the player that has a pending action
 */
public void add_waiting(string name);


/*
 * Function name: greet_player
 * Description: Greet the player.  If the NPC is currently occupied,
                tell_player_occupied will be called instead.               
 * Arguments  : object - the player to be greeted.  
 *              is called instead.
 */
public void greet_player(object player);

/*
 * Function name: do_action
 * Description: Perform your action.  If the NPC is currently occupied,
                tell_player_occupied will be called instead.               
 * Arguments  : object - the player to be greeted.  
 *              is called instead.
 */
public void do_action(object player);


/*
 * Function name: tell_player_occupied
 * Description: Action to do when the NPC is occupied
 * Arguments  : object - the player to be greeted.  
 *              is called instead.
 */
public void tell_player_occupied(object player);

/*
 * Function name: tell_player_still_occupied
 * Description: If the NPC was busy when the player entered the room,
                and is still busy for a while, this will allow the NPC
                to remind the player that they are not forgotten.
 * Arguments  : object - the player to be greeted.  
 *              is called instead.
 */
public void tell_player_still_occupied(object player);


/*
 * Function name: set_available
 * Description: Call this to indicate the NPC is not busy
 */
public void set_available()
{
    if (!Available)
    {
        set_alarm(2.0,0.0,find_waiting);
    }
    Available=1;
}

/*
 * Function name: set_occupied
 * Description: Call this to indicate the NPC is busy
 */
public void set_occupied()
{
    Available=0;
}

/*
 * Function name: get_available
 * Description: Call this to test if the NPC is busy
 */
public int get_available()
{
    return Available;
}


/*
 * Function name: notify_player_entered
 * Description: Call this in your init_living to automatically
 * handle greetings
 */
public void notify_player_entered()
{
	if (interactive(TP) && CAN_SEE(TO, TP) && CAN_SEE_IN_ROOM(TO))
    {
        string name=TP->query_real_name();
        if (Greeting_alarms[name])
        {
            return;
        }
        if (Waiting_alarms[name])
        {
            return;
        }
        int alarm_id=set_alarm(2.0,0.0,&initial_greet(name));
        Greeting_alarms[name]=alarm_id;
    }
}

/*
 * Function name: find_visible_player
 * Description: This determines if the player is still a valid
 *              target.  If not, returns 0.
 * Returns: The player object, if they can be seen and are still
 *          present
 */
private object find_visible_player(string name)
{
    if (!stringp(name))
    {
        return 0;
    }
    object player=find_player(name);
    if (!objectp(player))
    {
        return player; 
    }
    if (environment(player)!=environment(TO))
    {
        return 0;
    }
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO,player))
    {
        return 0;
    }
    return player;
}

private void initial_greet(string name)
{
    m_delkey(Greeting_alarms,name);

    object player=find_visible_player(name);
     
    if (!objectp(player))
        return;

    if (!Available)
    {
        tell_player_occupied(player);
        int alarm_id=set_alarm(60.0,0.0,&still_busy(name));
        Waiting_alarms[name]=alarm_id;       
    }
    else 
    {
        greet_player(player);
        do_action(player); 
    }
       
}

public void add_waiting(string name)
{
    if (Greeting_alarms[name])
        return;
    if (Waiting_alarms[name])
        return;
        
    int alarm_id=set_alarm(2.0,0.0,&still_busy(name));
    Waiting_alarms[name]=alarm_id;

}

private void find_waiting()
{
    if (!Available || !m_sizeof(Waiting_alarms))
        return;
    
    string name=m_indexes(Waiting_alarms)[0];
    
    remove_alarm(Waiting_alarms[name]);
    
    still_busy(name);
}

private void still_busy(string name)
{

    m_delkey(Waiting_alarms,name);
    
    object player=find_visible_player(name);
     
    if (!objectp(player))
        return;

    if (Available)
    {
        do_action(player);
    }
    else
    {
        tell_player_still_occupied(player);     
        int alarm_id=set_alarm(60.0,0.0,&still_busy(name));
        Waiting_alarms[name]=alarm_id;       
    }
    
}
