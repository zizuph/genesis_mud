#pragma strict_types
#pragma save_binary
 
inherit "/d/Genesis/specials/std/stun_sh";

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
    
    return specials;
}


void
init_stun_shadow()
{
     shadow_who->catch_msg("Your eyes soar in pain as the powder "
     +"in them starts to boil!\nYou are blinded!\n");
    
    tell_room(environment(shadow_who), QCTNAME(shadow_who) +
    " screams in pain as " + shadow_who->query_possessive() +
    " eyes seems to start boiling!\n", shadow_who);
}


/*
 * Function name :  remove_stun_shadow
 * Description   :  Handles the removal of the shadow.
 */
public void
remove_stun_shadow()
{
    shadow_who->catch_msg("You regain your ability to move freely again.\n");
    
    tell_room(environment(shadow_who), QCTNAME(shadow_who) +
    " seems to regain " + shadow_who->query_possessive() +
    " ability to move freely again.\n", shadow_who);
       
    remove_shadow();
}