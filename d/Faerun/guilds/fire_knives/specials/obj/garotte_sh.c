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


void
init_garotte_shadow()
{
    shadow_who->catch_msg("You grasp your neck in shock of the pain "
    +"and find yourself unable to speak!\nYou are silenced!\n");

    tell_room(environment(shadow_who), QCTNAME(shadow_who) +
    " grasps " + shadow_who->query_possessive() + 
    " neck in shock of the pain, but is unable to speak!\n", shadow_who);
    
    shadow_who->inc_prop(LIVE_M_MOUTH_BLOCKED);
}


/*
 * Function name :  remove_blind_shadow
 * Description   :  Handles the removal of the shadow.
 */
public void
remove_garotte_shadow()
{
    shadow_who->catch_msg("The burning in your throat "
    +"subsides, and you find yourself able to speak again with "
    +"some difficulties.\n");

    tell_room(environment(shadow_who), QCTNAME(shadow_who) +
    " seems to almost regain " + shadow_who->query_possessive() +
    " voice again.\n", shadow_who);
    
    shadow_who->dec_prop(LIVE_M_MOUTH_BLOCKED);
       
    remove_shadow();
}