/*
 * /d/Faerun/guilds/fire_knives/obj/silence_cooldwn_obj.c
 *
 * Nerull 2018
 */

#pragma strict_types
inherit "/std/object";

#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <mail.h>
#include <filter_funs.h>
#include <composite.h>
#include "../../guild.h"


string bestower = 0;


/*
 * Function name: destroy_me
 * Description  : Destroys the item when the cooldown expires
 */
void
destroy_me()
{
    //environment(this_object())->catch_msg("You feel ready to execute garrote or any other primary ability again.\n");
    
    remove_object();
}


void
set_bestower(string isbestower)
{
    bestower = isbestower;
    
    return;
}


string
query_bestower()
{ 
    return bestower;
}


public void
create_object()
{
    set_name("_silence_cooldwn_obj");
    add_adj( ({"moldy"}) );

    set_short("moldy silence_cooldwn_obj");
    set_long("This is a fire knives silence cooldown object.\n");

    add_prop(OBJ_S_WIZINFO,"A fire knives silence cooldown object.\n");
                      
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    
    add_prop(OBJ_I_INVIS, 100);

    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_TELEPORT, 1);
    
    // By setting this, players should not know that this is in their
    // inventory.
    set_no_show();
    
    set_alarm(SILENCE_COOLDOWN_DURATION, 0.0, &destroy_me());
} 