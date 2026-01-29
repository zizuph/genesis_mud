
/*  

    /d/Calia/gelan/cadet/peace_shadow.c

    This shadow stops people fighting for very long in the hall 
    of peace. It should only be present on players who are in
    that room. 

    Coded by Maniac, 19/5/99

*/

#pragma save_binary

inherit "/std/shadow";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "cadet.h"

int fight_alarm; 

/* 
 * Function:      gc_hop_escort_out
 * Description:   Escort an aggressor out of the hall of peace. 
 */ 
void
gc_hop_escort_out(object target)
{
    fight_alarm = 0; 
    environment(shadow_who)->move_living_downstairs(shadow_who); 
}


/*
 * Function:      gc_hop_stop_fight
 * Description:   Stop a fight in the hall of peace. 
 */ 
void
gc_hop_stop_fight()
{
    object target; 

    fight_alarm = 0; 

    if (objectp(target = shadow_who->query_attack())) { 
        tell_room(environment(shadow_who), 
                  "Some guards arrive and break up the fight between " + 
                  QTNAME(shadow_who) + " and " + QTNAME(target) + 
                  ".\n", ({ shadow_who, target })); 
        tell_object(shadow_who, "Some guards arrive and break up " +
                   "the fight between you and " + 
                   target->query_the_name(shadow_who) + ".\n");  
        tell_object(target, "Some guards arrive and break up " +
                   "the fight between you and " + 
                   shadow_who->query_the_name(target) + ".\n");  
        target->stop_fight(shadow_who); 
        shadow_who->stop_fight(target); 
    } 
}


/*
 * Function name:   hit_me
 * Description:     Called to make damage on this object. The actually
 *                  made damage is returned and will be used to change
 *                  the score of the aggressor. Masked here to break 
 *                  up a fight that wasn't started in the hall of peace. 
 * Arguments:       wcpen         - The wc-penetration
 *                  dt            - damagetype, use MAGIC_DT if ac will not
 *                                  help against this attack.
 *                  attacker      - Object hurting us
 *                  attack_id     - Special id saying what attack hit us. If 
 *                                  you have made a special attack, let the 
 *                                  id be -1
 *                  target_hitloc - Optional argument specifying a hitloc
 * Returns:         The hitresult as given by the external combat object
 */
varargs public mixed 
hit_me(int wcpen, int dt, object attacker, int attack_id, 
       int target_hitloc = -1)
{
    if (!fight_alarm) 
        fight_alarm = set_alarm(itof(random(3) + 2), 0.0, gc_hop_stop_fight); 
    return shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc); 
}


/* 
 * Function:      attack_object
 * Description:   Called when the shadowed player attacks a target 
 *                object. 
 */ 
void
attack_object(object target)
{
    shadow_who->attack_object(target); 
    if (!fight_alarm) 
        fight_alarm = set_alarm(itof(random(3) + 2), 0.0, 
                                &gc_hop_escort_out(target)); 
}


/*
 * Function:      gc_remove_peace_shadow
 * Description:   Remove this peace shadow from the shadowed player. 
 */
void
gc_remove_peace_shadow()
{
    remove_shadow(); 
}

