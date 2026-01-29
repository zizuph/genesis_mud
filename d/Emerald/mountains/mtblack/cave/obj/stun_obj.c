/* This object stuns you for a while. Coded 26/11/95 by Tulix III.        */
/* It is used by /d/Emerald/cave/npc/wise_old_mage in a combat spell.     */
/* He is found at /d/Emerald/cave/levelc/cave27c.                         */

inherit "/std/object";
#include "/d/Emerald/defs.h"

/* Define the sub-location which we are going to add to the player */
#define SUBLOC "enz_stun_obj_subloc"

/* Prototype functions */
public void set_unstun_delay(int time_to_stun);
public string show_subloc(string subloc, object carrier, object for_obj);
public void unstun_victim(object victim); 

/* Global variable */
int delay;

public void
create_object()
{
    if (!IS_CLONE)
        return;
    
    set_name("enz_stun_object");
    set_no_show();                            /* Make completely invisible */
    add_prop(OBJ_I_NO_DROP, 1);
}

/*
 * Function name:   enter_env
 * Description:     called when this object enters a new environment
 * Arguments:       victim: destination environment
 *                  old:    previous environment
 */
public void
enter_env(object victim, object old)
{
    ::enter_env(victim, old);
    
    set_alarm( itof(delay), 0.0, &unstun_victim(victim));  /* Unstun later */
    
    if (living(victim))              /* Check destination object is living */
    {    
        victim->add_stun();                           /* Stun the victim   */
        victim->add_subloc(SUBLOC, TO);               /* add sub-location  */
        
        tell_room( ENV(victim), QCTNAME(victim) +
            " seems to have been stunned.\n", victim);
        victim->catch_msg("You seem to be stunned for some reason.\n");
    }    
    
    return;
}

/*
 * Function name:   show_subloc
 * Description:     show the subloc which tell us that the player is stunned
 * Arguments:       subloc:  string identifying this sub-location
 *                  carrier: player carrying this object
 *                  for_obj: the player who is examining the carrier 
 * Returns:         sting describing the players stunned state
 */
public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier -> query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return ""; /* Don't show sub-location as inventory */

    if (for_obj == carrier)
        str = "You seem ";
    else
        str = capitalize(carrier->query_pronoun()) + " seems ";

    return str + "to have been stunned.\n";
}

/*
 * Function name:   set_delay
 * Description:     Set the time for which the victim is stunned.
 */
public void
set_unstun_delay(int time_to_stun)
{
    delay = time_to_stun;
    return;
}

/*
 * Function name:   unstun_victim
 * Description:     return victim to normal state
 */
public void
unstun_victim(object victim)
{
    set_this_player(victim);  /* this_player() not defined by set_alarm() */
    
    tell_room( ENV(TP), QCTNAME(TP) +
        " shakes off the effects of the stun.\n", TP);
    TP -> catch_msg("You shake off the effects of the stun.\n");
    
    TP -> remove_stun();               /* Unstun our victim and also      */
    TP -> remove_subloc(SUBLOC);       /* remove sub-location and this    */
    TO -> remove_object();             /* object when victim is defrosted */
    
    return;
}

/*
 * Function name:   replace_stun
 * Description:     called when this object is replaced by a new one
 */
public void
replace_stun()
{
    set_this_player(EO);
    
    TP -> remove_stun();
    TP -> remove_subloc(SUBLOC);       /* Remove sub-location and this    */
    TO -> remove_object();             /* object when replaced            */
    
    return;
}
