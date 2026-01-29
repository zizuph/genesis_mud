/* This object freezes you for a while. Coded 2/09/95 by Tulix III.       */
/* It is used by /d/Emerald/conq_tower/wep/diamond_axe during combat.     */

inherit "/std/object";
#include "/d/Emerald/defs.h"

/* Define the sub-location which we are going to add to the player */
#define SUBLOC "diamond_axe_freeze_subloc"

/* Prototype functions */
public void set_unfreeze_delay(int time_to_freeze);
public string show_subloc(string subloc, object carrier, object for_obj);
public void unfreeze_victim(); 

/* Global variable */
int delay;

public void
create_object()
{
    if (!IS_CLONE)
        return;
    
    set_name("diamond_axe_freeze_object");
    set_no_show();                            /* Make completely invisible */
    add_prop(OBJ_I_NO_DROP, 1);
}

/*
 * Function name:   enter_env
 * Description:     called when this object enters a new environment
 * Arguments:       dest: destination environment
 *                  old:  previous environment
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    
    set_alarm( itof(delay), 0.0, unfreeze_victim);      /* Unfreeze later */
    
    if (living(dest))               /* Check destination object is living */
    {    
        dest->add_stun();                            /* Freeze the victim */
        dest->add_subloc(SUBLOC, TO);                /* add sub-location  */
    }    
    
    return;
}

/*
 * Function name:   show_subloc
 * Description:     show the subloc which tell us that the player is shocked
 * Arguments:       subloc:  string identifying this sub-location
 *                  carrier: player carrying this object
 *                  for_obj: the player who is examining the carrier 
 * Returns:         sting describing the players shocked state
 */
public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier -> query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return ""; /* Don't show sub-location as inventory */

    if (for_obj == carrier)
        str = "You are ";
    else
        str = capitalize(carrier->query_pronoun()) + " is ";

    return str + "suffering from the effects of a shock.\n";
}

/*
 * Function name:   set_delay
 * Description:     Set the time for which the victim is frozen.
 */
public void
set_unfreeze_delay(int time_to_freeze)
{
    delay = time_to_freeze;
    return;
}

/*
 * Function name:   unfreeze_victim
 * Description:     return victim to normal state
 */
public void
unfreeze_victim()
{
    set_this_player(ENV(TO)); /* this_player() not defined by set_alarm() */
    
    TP -> remove_stun();               /* Unfreeze our vcitim and also    */
    TP -> remove_subloc(SUBLOC);       /* remove sub-location and this    */
    TO -> remove_object();             /* object when victim is defrosted */
    
    return;
}

