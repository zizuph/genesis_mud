
/* 
 * This is the "last boss" for the Underworld. 
 *   
 * Coded by Jaacar July, 2017.
*/ 

#include <ss_types.h>
#include <macros.h> 
#include <stdproperties.h>
#include "defs.h"

inherit "/std/monster";

/*
 * Function:    my_time
 * Description: Returns the time format used for logs.
 */
public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

void
create_monster()
{
    set_name("Boss"); 
    add_name("boss");

    set_adj(({"massive", "deadly"}));  
   
    set_race_name("boss");

    set_long("This is a massive, deadly boss. You shouldn't mess with "+
        "it.\n"); 

    default_config_npc(350);

    set_skill(SS_UNARM_COMBAT, 100); 
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_WEP_POLEARM, 90);
    set_alignment(0);

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_WEIGHT, 65000); 
    add_prop(CONT_I_VOLUME, 65000);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_SEE_INVIS, 1); 
    set_act_time(60);
    add_act("emote growls.");
}
