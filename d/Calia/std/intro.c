
/* 
   Just inherit this into the npc you want to intro and 
   configure it with set_intro_delay(int delay); (default is 1 second) 
   You can mask intro_hook(object pl) if you want a special 
   intro effect of some sort. 

   Maniac, Feb 22 1997
*/ 

#include <macros.h>

#pragma strict_types
#pragma save_binary

#define MAX_INTRO_DELAY 5

int intro_delay = 1;

/* 
 * Function name: intro_hook(object pl)
 * Arguments: object pl: the player who has introduced. 
 * Desccription: This function is called in an npc that you want to intro 
 *               after a player has introduced himself. 
 */ 
public void
intro_hook(object pl) 
{
    if (objectp(pl) && present(pl, environment(this_object()))) 
        this_object()->command("introduce me to " + OB_NAME(pl));  
}


/*
 * Function name: set_intro_delay(int dl)
 * Description: Sets the delay in seconds from when add_introduced and 
 *              intro_hook is called. 
 * Arguments: int dl: the delay in seconds.
 */
public void
set_intro_delay(int dl)
{
    if (dl > MAX_INTRO_DELAY)
        intro_delay = MAX_INTRO_DELAY;
    else if (dl < 0)
        intro_delay = 0;
    else
        intro_delay = dl;
}


/*
 * Function name:   add_introduced(string name)
 * Description:     Informs the npc that a living introduced itself. 
 * Arguments:       name: Name of the introduced living
 */
public void
add_introduced(string name)
{
    object ch; 

    ch = present(name, environment(this_object())); 

    if (!objectp(ch) || 
        ch->query_npc() || 
        ch->query_met(this_object()->query_real_name())) 
        return;

    if (intro_delay)
        set_alarm(itof(intro_delay), 0.0, &intro_hook(ch));  
    else
        intro_hook(ch); 
}

