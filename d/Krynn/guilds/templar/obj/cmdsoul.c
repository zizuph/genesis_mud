/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 */

#pragma strict_types
#include "/d/Krynn/common/defs.h"
#include "../local.h"

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "emotes.c"

#define LIVE_O_ACTION "_live_o_action_"

string
get_soul_id() 
{ 
    return GUILD_NAME + " soul"; 
}


int 
query_cmd_soul() 
{ 
    return 1; 
}


mapping
query_cmdlist()
{
    return ([
      /* Command name : Function name */

      "tattack"   : "do_ability",
      "tfocus"    : "focus_special",
      "tsap"      : "do_ability",
      
    ]) +emote_cmdlist();
}

public mapping
query_ability_map()
{
    return ([
             "tattack" : OBJ+"tattack",
             "tsap"    : OBJ+"tsap"
            ]);
}

/**
 * Defend Focus Special
 * Attempt to parry/block/dodge a % of the incoming attacks.
 */
int
focus_special(string str)
{
    setuid();
    seteuid(getuid());
    
    int state = TP->query_prop(GUILD_FOCUS_PROP);

    if(TP->query_real_name() == "navarre")
    {
        find_player("navarre")->catch_msg("Focus prop is : "+state+"\n");
        find_player("navarre")->catch_msg("Delay Prop is : "+TP->query_prop(GUILD_FOCUS_DELAY_PROP)+"\n");
    }
    
    // If we are in the middle of an attack we use a delay prop instead.
    // This will change the property when we have finished the tattack.
    // This way the player can still switch in the middle of combat.
    // But will never get more than allowed combat aid.
    if(TATTACK_OB->query_ability_active(TP))
    {
        if (TP->query_prop(GUILD_FOCUS_DELAY_PROP))
        {
            // The player has already tried to change tfocus before during
            // the preparation.
            //            TP->remove_prop(GUILD_FOCUS_DELAY_PROP);
            if (TP->query_prop(GUILD_FOCUS_DELAY_PROP) == 2)
            {
                TP->catch_tell("You change your mind and decide you wish "
                             + "to continue focusing against attacks "
                             + "after the current attack.\n");
                TP->add_prop(GUILD_FOCUS_DELAY_PROP, 1);
            }
            else
            {
                TP->catch_tell("You change your mind and decide you do "
                             + "not wish to defend against attacks after "
                             + "the current attack.\n");
                TP->add_prop(GUILD_FOCUS_DELAY_PROP, 2);
            }
        }
        else
        {
            if (state)
            {
                // Currently focusing, but want to change to unfocused
                TP->catch_tell("You decide to stop defending against attacks "
                             + "after you complete your current attack.\n");
                TP->add_prop(GUILD_FOCUS_DELAY_PROP, 2);
            }
            else
            {
                TP->catch_tell("You decide to attempt defending against attacks "
                             + "after you complete your current attack.\n");            
                TP->add_prop(GUILD_FOCUS_DELAY_PROP, 1);
            }        
        }
        
        return 1;
    }    
    
    if (state)
    {
        TP->catch_tell("You stop attempting to defend against attacks.\n");
        state = 0;
    }
    else
    {
        TP->catch_tell("You begin focusing on defending against attacks.\n");
        state = 1;
    }

    TP->remove_prop(GUILD_FOCUS_DELAY_PROP);
    TP->add_prop(GUILD_FOCUS_PROP, state);        

    return 1;
}
