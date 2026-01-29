/*
 *  /d/Kalad/common/farmland/camps/rooms/rf_war_room
 *
 *  This is the master file for rooms in the Red Fang camp
 *
 *  Created October 2015, by Andreas Bergstrom (Zignur)
 */
 
#pragma strict_types

inherit "/std/room";

#include </sys/macros.h>
#include </sys/stdproperties.h>
#include "../defs.h"



/* Definitions */

/* Global Variables */
public int Redfang_camp_state = 1;
public int Goblin_warrior_counter = 0;
public string *Redfang_camp_rooms = ({ });


/* Prototypes */
public nomask void  create_room();
public int          get_redfang_camp_state();
public void         set_redfang_camp_state(int state);
public int          get_goblin_warrior_counter();
public void         add_goblin_warriors(int goblins);
public void         remove_goblin_warriors(int goblins);
public void         add_redfang_camp_room(string room);
public void         notify_redfang_camp_room(string room);


/*
 * Function name:        create_room
 * Description  :        the basic constructor for rooms
 */
public nomask void
create_room()
{

    add_name("War room");
    add_prop(ROOM_I_LIGHT, 1);
    set_short("Inside a war room");
    set_long("This is a war room, where you can keep track of the"
     +  " current state in the redfang camp.\n");
    
} /* create_room */




/*
 * Function name:        get_redfang_camp_state
 * Description  :        returns the value of the Redfang_camp_state
 * Returns      :        the value of Redfang_camp_state
 */
public int
get_redfang_camp_state()
{
    return Redfang_camp_state;     
    
} /* get_redfang_camp_state */


/*
 * Function name:        set_redfang_camp_state
 * Description  :        returns the value of the Redfang_camp_state
 * Arguments    :        int state - the new state on the camp
 */
public void
set_redfang_camp_state(int state)
{
    Redfang_camp_state = state;
    
} /* set_redfang_camp_state */


/*
 * Function name:        get_goblin_warrior_counter
 * Description  :        returns the value of the Goblin_warrior_counter
 * Returns      :        the value of Goblin_warrior_counter
 */
public int
get_goblin_warrior_counter()
{
    return Goblin_warrior_counter;     
    
} /* get_goblin_warrior_counter */


/*
 * Function name:        add_goblin_warriors
 * Description  :        Adds goblins to the Goblin_warrior_counter
 * Arguments    :        int goblins - the number of goblins to add
 */
public void
add_goblin_warriors(int goblins)
{
    Goblin_warrior_counter = Goblin_warrior_counter + goblins;
    
} /* add_orc_warriors */


/*
 * Function name:        remove_goblin_warriors
 * Description  :        Removes goblins to the Goblin_warrior_counter
 * Arguments    :        int goblins - the number of goblins to remove
 */
public void
remove_goblin_warriors(int goblins)
{
    Goblin_warrior_counter = Goblin_warrior_counter - goblins;
    
} /* remove_goblin_warriors */


/*
 * Function name:        add_redfang_camp_room
 * Description  :        Add a room to the Redfang_camp_rooms array
 * Arguments    :        string room - the name of the room
 */
public void
add_redfang_camp_room(string room)
{
    Redfang_camp_rooms += ({room});
    
} /* add_redfang_camp_room */


/*
 * Function name:        notify_redfang_camp_room
 * Description  :        Notifies a room about the change of state
                         that a change has occurred in the camp state
 * Arguments    :        string room - the room we want to notify
 */
public void
notify_redfang_camp_room(string room)
{
    int counter = sizeof(Redfang_camp_rooms);
    string currentRoom = "";
    for (int i = 0; i < counter; i++)
    {
        currentRoom =  Redfang_camp_rooms[i];
        // See if it is the correct room that we want to notify
        if(currentRoom == room){
           Redfang_camp_rooms[i]->notify_redfang_camp_room(); 
        }
    }
    
} /* notify_redfang_camp_room */

