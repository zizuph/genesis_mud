/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 */

#pragma strict_types
#include "/d/Krynn/common/defs.h"
#include "../local.h"

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";

inherit OBJ+"special_attacks";

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "emotes.c"


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

      "tattack"   :   "offensive_special",
      "tfocus"    : "focus_special",
      "tsap"      : "sap_special",
      
    ]) +emote_cmdlist();
}

/**
 * Defend Focus Special
 * Attempt to parry/block/dodge a % of the incoming attacks.
 */
int
focus_special(string str)
{
    //If the player is trying to turn it off, these won't be true
    //since she will have been focusing on defense the whole time til now.

    //Full Templars can do both focus and attack at the same time.
    if (TP->query_offensive_preparing() && !(TP->query_full_templar_member()))
    {
        write("You cannot do that while preparing another attack!\n");
        return 1;
    }
    
    if (TP->query_offensive_attacking() && !(TP->query_full_templar_member()))
    {
        write("You are not ready to begin focusing on defense.\n");
        return 1;
    }
    
    TP->switch_focus_state();
    return 1;
}

/**
 * Offensive special
 */
int
offensive_special(string str)
{
    object ob, *obj, *oblist;
    string how;


    /* What are we attacking? */
    if (strlen(str))
    {
        if (!sizeof(obj = parse_this(str, "[the] %l")))
        {
            notify_fail("Attack whom?\n");
            return 0;
        }

        ob = obj[0];
    }
    
    /* If no target     */
    else if (!(ob = this_player()->query_attack()))
    {
        notify_fail("Attack whom?\n");
        return 0;
    }

    /* Does attacker have the skill? */
    if (!(this_player()->query_skill(SS_GUILD_ATTACK_SKILL)))
    {
    write("You do not have the skill.\n");
    return 1;
    }


    /* Are we ready */
    if(TP->query_offensive_preparing())
    {
        write("You are already preparing an attack.\n");
        return 1;
    }

    if(TP->query_offensive_attacking())
    {
        write("You are not ready to do that yet.\n");
        return 1;
    }

    //Full Templars can focus and attack.
    if (TP->query_is_focused() && !(TP->query_full_templar_member()))
    {
        NF("You cannot do that while focusing on defense!\n");
        return 0;
    }

    /* Are we even allowed to attack it?  Use can_attack_with_lay_special(),
     * which is defined in the guild shadow, to find out.
     */
    if (stringp(how = cannot_attack_with_lay_special(TP, ob, "attack")))
    {
        write(how);
        return 1;
    }

    if ( TP->query_prop(LIVE_O_LAST_KILL) != ob )
        TP->add_prop(LIVE_O_LAST_KILL, ob);
      
    /* The shadow takes care of the rest */
    lay_offensive_special(TP, ob);

    return 1;
}

/**
 * sap special
 * Try to hit someone with something
 */
int
sap_special(string str)
{
    object ob, weapon, *weapons, *obj, *oblist, sapob, testob;
    string how, weapon_desc;
    object *weaponlist;
    
    /*
    if (TP->query_name() != "Louiejr")
    {
        NF("This ability is temporarily deactivated.\n");
        return 0;
    }
    
    */
    
    if (TP->query_attack())
    {
        NF("You can't sap anything while in combat!\n");
        return 0;
    }
    
    if (!CAN_SEE_IN_ROOM(TP)) {
        NF("You can't see to sap.\n");
        return 0;
    }    
    
    if (!strlen(str))
    {
        NF("Sap whom with what?\n");
        return 0;
    }
    
   
    if (!parse_command(str, environment(TP), 
            "[the] %l [with] %o", obj, weapon))
    {
            
        if (!parse_command(str, environment(TP),
            "[the] %l", obj))
        {
            NF("Sap whom with what?\n");
            return 0;
        }
        
        if (TP->query_weapon(W_RIGHT)) 
        {
            weapon = TP->query_weapon(W_RIGHT);
        } else if (weapon = TP->query_weapon(W_LEFT))
        {
            weapon = TP->query_weapon(W_LEFT);
        } else if (TP->query_weapon(W_BOTH))
        {
            weapon = TP->query_weapon(W_BOTH);
        } else 
        {
            NF("Sap whom with what?\n");
            return 0;
        }
    }
    
    
    ob = obj[1];
    /* Make sure we're not trying ourself (like with "attack human")*/
    if (TP == ob && (sizeof(obj) > 2) ) {
        ob = obj[2];
    } else if (TP == ob) {
        NF("Sap whom with what?\n");
        return 0;
    }
    
    if (!CAN_SEE(TP, ob)) {
        NF("Sap whom with what?\n");
        return 0;
    }

    
    if (!weapon) {
        NF("Sap "+ob->query_the_name(TP)+" with what?\n");
        return 0;
    }
    
    if (!weapon->query_short()) {
        weapon_desc = weapon->query_name();
    } else 
    {
        weapon_desc = weapon->query_short();
    }
    
    if (environment(weapon) != TP)
    {
        NF("You're not holding "+weapon_desc+"!\n");
        return 0;
    }
    
    if (weapon->query_prop(OBJ_I_WEIGHT) < 101)
    {
        NF("The "+weapon_desc+" is too light to use.\n");
        return 0;
    }
    
    if (weapon->query_prop(OBJ_I_VOLUME) < 50)
    {
        NF("The "+weapon_desc+" is too small to use.\n");
        return 0;
    }
    
    if (ob->query_attack())
    {
        NF("You can't sap something that is in combat!\n");
        return 0;
    }
    
    /* Does attacker have the skill? */
    if (!(this_player()->query_skill(SS_GUILD_SAP_SKILL)))
    {
        write("You do not have the skill.\n");
        return 1;
    }


    /* Are we ready */
    if(TP->query_offensive_preparing())
    {
        write("You are already preparing an attack.\n");
        return 1;
    }

    if(TP->query_sap_timer())
    {
        write("You are not ready to do that yet.\n");
        return 1;
    }

    /* We can only sap something that isn't expecting it*/
    if (time() - ob->query_prop(GUILD_SAP_PROP) < SAP_IMMUNE_TIME)
    {
        write(ob->query_The_name(TP)+" is alert to that sort of attack.\n");
        return 1;
    }
        

    /* Are we even allowed to attack it?  Use can_attack_with_lay_special(),
     * which is defined in the guild shadow, to find out.
     */
    if (stringp(how = cannot_attack_with_lay_special(TP, ob, "attack")))
    {
        write(how);
        return 1;
    }
    
    if ( TP->query_prop(LIVE_O_LAST_KILL) != ob )
        TP->add_prop(LIVE_O_LAST_KILL, ob);
      
    /* The shadow takes care of the rest */
    lay_sap_special(TP, ob, weapon);

    return 1;
}