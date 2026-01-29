/* This object causes the player carrying it to attack at half the normal */ 
/* rate. This effect lasts for approximately 2 minutes, at which point    */
/* this object self-destructs. The object is used in a spell cast by      */
/* Enzalcaspin(/d/Emerald/cave/npc/wise_old_mage.c) who is to be found at */
/* /d/Emerald/cave/levelc/cave27c.c. Coded 10/11/95 by Tulix III.         */

inherit "/std/object";
#include "/d/Emerald/defs.h"

/* Define the sub-location which we are going to add to the player */
#define SUBLOC "enz_slow_obj_subloc"

/* Prototype functions */
public string show_subloc(string subloc, object carrier, object for_obj);
public void unslow_victim(object victim); 


public void
create_object()
{
    if (!IS_CLONE)
        return;
    
    set_name("enz_slow_object");
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
    
    set_alarm( 120.0, 0.0, &unslow_victim(victim));        /* Unslow later */
    
    if (living(victim))              /* Check destination object is living */
    {    
        victim->add_prop(LIVE_I_QUICKNESS, 50);       /* Slow the victim   */
        victim->add_subloc(SUBLOC, TO);               /* add sub-location  */
        
        tell_room( ENV(victim), QCTNAME(victim) +
            " seems to have slowed down.\n", victim);
        victim->catch_msg("You seem to have slowed down for some reason.\n");
    }    
    
    return;
}

/*
 * Function name:   show_subloc
 * Description:     show the subloc which tell us that the player is slowed
 * Arguments:       subloc:  string identifying this sub-location
 *                  carrier: player carrying this object
 *                  for_obj: the player who is examining the carrier 
 * Returns:         sting describing the players slowed state
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

    return str + "to have slowed down.\n";
}

/*
 * Function name:   unslow_victim
 * Description:     return victim to normal state
 */
public void
unslow_victim(object victim)
{
    set_this_player(victim);  /* this_player() not defined by set_alarm() */
    
    tell_room( ENV(TP), QCTNAME(TP) +
        " seems a little quicker again.\n", TP);
    TP -> catch_msg("You feel less slow.\n");
    
    TP -> add_prop(LIVE_I_QUICKNESS, 100);  /* Unslow our victim and also */
    TP -> remove_subloc(SUBLOC);       /* remove sub-location and this    */
    TO -> remove_object();             /* object when victim is unslowed  */
    
    return;
}

/*
 * Function name:   replace_slow
 * Description:     called when this object is replaced by a new one
 */
public void
replace_slow()
{
    set_this_player(EO);
    
    TP -> remove_subloc(SUBLOC);       /* Remove sub-location and this    */
    TO -> remove_object();             /* object when replaced            */
    
    return;
}
