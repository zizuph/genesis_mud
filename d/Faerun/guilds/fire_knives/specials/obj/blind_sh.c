#pragma strict_types
#pragma save_binary
 
inherit "/std/shadow";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <composite.h>

#include "../../guild.h"


/*
 * Function name :  turned_aggression
 * Description   :  This functions checks which specials are active.
 */
public int
query_special_attacks(object player)
{
    int specials = 0;
    
    /*
    if (SLING_ABILITY->query_ability_active(player))
        specials++;
    */
    
    /*if (DODGE_ABILITY->query_ability_active(player))
        specials--;*/
    
    return specials;
}


void
init_blind_shadow()
{
     shadow_who->catch_msg("Your eyes soar in pain as the powder "
     +"in them starts to boil!\nYou are blinded!\n");
    
    tell_room(environment(shadow_who), QCTNAME(shadow_who) +
    " screams in pain as " + shadow_who->query_possessive() +
    " eyes seems to start boiling!\n", shadow_who);
    
    shadow_who->inc_prop(LIVE_I_BLIND);
}


/*
 * Function name :  remove_blind_shadow
 * Description   :  Handles the removal of the shadow.
 */
public void
remove_blind_shadow()
{
    shadow_who->catch_msg("The searing pain in your eyes "
    +"fades away, and you regain most of your vision.\n");
    
    tell_room(environment(shadow_who), QCTNAME(shadow_who) +
    " seems to regain " + shadow_who->query_possessive() +
    " most of the vision again.\n", shadow_who);
    
    shadow_who->dec_prop(LIVE_I_BLIND);
       
    remove_shadow();
}