/*  Shire's room tell.  My thanks to Aridor and Rastlin
 *  I used their room_tell as a base for mine.
 *
 *  Example on how to use this.
 
    void
    create_shire_room()
    {
         set_room_tell_time(30);  //  30 seconds between tells.
	 add_room_tell("You hear chirping in the distance.");
	 add_room_tell("A loud howling noise is heard in the "+
	     "distance!");
    }

 *  -Igneous-
 * 
 * Room tells for Faerie, Based on Shire's room tell file. Thanks to Igneous 
 * for converting it over to Shire, and Aridor and Rastlin for the original 
 * concept.
 * -- Finwe, August 2004
 */

#include <filter_funs.h>
#include "defs.h"

//  Prototypes
void do_room_tell();
void stop_room_tells();

static int gTell_alarm;
static string *gTell_strings = ({ });
static int gTell_repeat_time = random(6) + 10 ;

/*
 * Function name : Set_room_tell_time
 * Arguments     : time:  The time between tells.
 * Description   : Sets the time for when the room tell repeats
 */
public void
set_room_tell_time(int time)
{
  if (time > 0)
    gTell_repeat_time = time;
}

/*
 * Function name : Add_room_tell
 * Arguments     : str:  The string which you want the room to tell the player.
 * Description   : Adds a string to the list of tells.
 */
public void
add_room_tell(string str)
{
    if (str) 
       gTell_strings += ({ str });
}

/*
 * Function name : Query_room_tells
 * Description   : Returns a list of the room tell strings.
 * Returns       : The list of tell strings.
 */
string * 
query_room_tells() 
{ 
    return gTell_strings; 
}

/*
 * Function name : Do_room_tells
 * Description   : Produces the room tell.
 */
static void
do_room_tell()
{
    if (!sizeof(FILTER_PLAYERS(all_inventory(this_object()))) || 
	!sizeof(gTell_strings)) 
    {
        stop_room_tells();
        return;
    }
    tell_room(this_object(), this_object()->check_call(
	      gTell_strings[random(sizeof(gTell_strings))]) + "\n");
}

/*
 * Function name : Start_room_tells
 * Description   : Will attempt to start the room_tell alarm.
 */
public void
start_room_tells()
{
    if (gTell_alarm || !sizeof(gTell_strings))
        return;
    gTell_alarm = set_alarm(itof(random(10)+1), itof(gTell_repeat_time), 
        &do_room_tell());
    

}

/* Function:    stop_room_tells
 * Description: Stop the room_tells even if someone is still in the room.
 */
public void
stop_room_tells()
{
    if (!gTell_alarm)
        return;
    remove_alarm(gTell_alarm);
    gTell_alarm = 0;
}
