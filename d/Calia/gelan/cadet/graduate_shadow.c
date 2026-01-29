
/*
 *  /d/Calia/gelan/cadet/graduate_shadow.c
 *  
 *  This is a shadow for graduates from the Cadets of
 *  Gelan guild, it will remove the graduation ring 
 *  if they kill a Cadet of Gelan who didn't initiate combat, 
 *  or an npc citizen of Gelan or guard of Gelan. 
 *
 *  Coded by Maniac, May 1998
 */

inherit "/std/shadow"; 

#include <macros.h>
#include <stdproperties.h>
#include "cadet.h"

object *cadets_attacked = ({ }); 

int i_attacked_cadets = 0;  


void
gc_set_unworthy()
{
    i_attacked_cadets = 1; 
}

void
gc_set_exemplary()
{
    // gonna do something here at a later date
}

int
query_i_attacked_cadets()
{
    return i_attacked_cadets; 
}


/* Stealing from a cadet means that it's ok to kill this graduate 
   without penalty.. fat chance, but still possible. */ 
void
hook_thief_stolen_object(object item, object victim, object place)
{
    if (IS_GELAN_CADET(victim)) 
        i_attacked_cadets = 1; 

    shadow_who->hook_thief_stolen_object(item, victim, place); 
}


/*
 * Function:     remove_graduation_ring
 * Description:  Suspend the graduate's status or remove ring
 *               as appropriate
 */
private void
remove_graduation_ring(string victim)
{
    present(GC_RING_ID, shadow_who)->suspend("attacking and killing " + 
                                     capitalize(victim)); 
}


void
attack_object(object victim)
{
    if (IS_GELAN_CADET(victim) || IS_CADET_FRIEND(victim)) {
        if (!CADETS_CAN_DUEL(victim, shadow_who) &&
            !CADETS_CAN_BRAWL(victim, shadow_who) && 
            !(victim->query_i_attacked_cadets()) && 
            (member_array(victim, cadets_attacked) == -1)) { 
             i_attacked_cadets = 1; 
             cadets_attacked += ({ victim }); 
             tell_object(shadow_who, "\nYou realise that you " +
                 "have just attacked a cadet, a citizen of Gelan " +
                 "or a guard of Gelan, and that if you " +
                 "kill " + victim->query_objective() + " you " +  
                 "will be punished.\n\n"); 
        } 
    } 

    shadow_who->attack_object(victim); 
}


void
gc_remove_graduate_shadow() 
{
    remove_shadow(); 
}


/*
 *  Remove the ring of a cadet who kills a cadet unprovoked or
 *  a guard or a citizen of Gelan.
 */
void
notify_you_killed_me(object victim)
{
    if (IS_GELAN_CADET(victim) || IS_CADET_FRIEND(victim)) { 
        if (!CADETS_CAN_DUEL(shadow_who, victim)) 
            if (!(victim->query_i_attacked_cadets()))   
                set_alarm(1.0, 0.0, 
                      &remove_graduation_ring(victim->query_real_name()));
    } 

    shadow_who->notify_you_killed_me(victim); 
}

