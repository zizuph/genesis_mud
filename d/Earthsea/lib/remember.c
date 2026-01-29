
/* 
   Inherit this into an npc that you want to address players properly by 
   using a name memory. 
   
   Configuring functions: set_num_remember(int number)

   Service functions: 
   query_address(object pl)
   query_art_address(object pl)
   query_Art_address(object pl)
   query_the_address(object pl)
   query_The_address(object pl)

   Maniac, Feb 22 1997
*/ 

#pragma strict_types
#pragma save_binary

#include <language.h>

inherit "/d/Earthsea/lib/intro"; 

#define MAX_REMEMBER 15

int num_remember = 5; 
string *intro_memory = ({ }); 

/* 
 * Function name: set_num_remember(int nr)
 * Description: Sets the number of player names remembered by this npc.   
 *              The default is 5. 
 * Arguments: int nr: the number of player names remembered.  
 */ 
public void
set_num_remember(int nr)
{
    if (nr > MAX_REMEMBER)
        num_remember = MAX_REMEMBER; 
    else if (nr < 0) 
        num_remember = 0;
    else 
        num_remember = nr; 
}


/*
 * Function name:   query_remember(object pl)
 * Description:     returns 1 if the npc remembers the player, 0 if not. 
 * Arguments:       object pl: the player. 
 */
int
query_remember(object pl)
{
    if (member_array(pl->query_real_name(), intro_memory) == -1) 
        return 0;
    else
        return 1;
}


/*
 * Function name:   add_introduced(string name)
 * Description:     Informs the npc that a living introduced itself. 
 * Arguments:       name: Name of the introduced living
 */
public void
add_introduced(string name)
{
    object pl;

    pl = find_player(name); 
    if (!objectp(pl) || !objectp(present(pl, environment(this_object())))) 
        return;

    if (num_remember)  { 
        if (!query_remember(pl)) { 
            if (sizeof(intro_memory) == num_remember) 
                intro_memory = exclude_array(intro_memory, 1, num_remember-1); 
            intro_memory += ({ name }); 
        } 
        else  
            return;
    } 

    if (intro_delay)
        set_alarm(itof(intro_delay), 0.0, &intro_hook(pl));  
    else
        intro_hook(pl); 
}

string
query_address(object pl)
{
    if (query_remember(pl)) 
        return pl->query_met_name(); 
    else 
        return (pl->query_nonmet_name()); 
}

string
query_art_address(object pl)
{
    if (query_remember(pl)) 
        return pl->query_met_name(); 
    else 
        return (LANG_ADDART(pl->query_nonmet_name())); 
}

string
query_Art_address(object pl)
{
    if (query_remember(pl)) 
        return pl->query_met_name(); 
    else 
        return (capitalize(LANG_ADDART(pl->query_nonmet_name()))); 
}

string
query_the_address(object pl)
{
    if (query_remember(pl)) 
        return pl->query_met_name(); 
    else 
        return ("the " + pl->query_nonmet_name()); 
}

string
query_The_address(object pl)
{
    if (query_remember(pl)) 
        return pl->query_met_name(); 
    else 
        return ("The " + pl->query_nonmet_name()); 
}

