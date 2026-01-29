/*
 * Modifications
 *  - checking GUILD_FOCUS_PROP instead of query_is_focused since that
 *    function doesn't seem to exist.
 */

#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
// #include "/d/Ansalon/common/defs.h"

#include "../local.h"

inherit "/d/Genesis/specials/std/evade_obj_base";

void print_defence_messages(object player, object target);
private mixed mess_with_weapon(object who, object target, object weapon);
private mixed mess_with_shield(object who, object target, object shield);
private mixed mess_with_dodge(object who, object target);


public void
create_effect()
{
    set_name("_templar_evade_object_");
    setuid();
    seteuid(getuid());
    
    set_evade_stats(TS_DEX);
    set_evade_skills(SS_GUILD_DEFEND_SKILL);
    set_evade_combat_aid(25);
}

/*
 * Function     : query_evade_valid
 * Description  : Validation function to see whether this evade object is
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_evade_valid(object player,
                  object attacker,
                  int attack_id)
{
    if (player->query_prop(GUILD_FOCUS_PROP))
    {
        return 1;
    }
    return 0;
}

public void
attack_blocked(object player,
               object attacker,
               int attack_id)
{
    print_defence_messages(player, attacker);
}

/**
 * When a successful defence occurs, print the messages to
 * those involved
 */
void
print_defence_messages(object player, object target)
{
    object who = player;
    object *weapons = who->query_weapon(-1);
    object *armours = who->query_armour(-1);
    string *messages;
    int hasWeapon = 0;
    int hasShield = 0;
    int shieldLoc = 0;
    
    if (sizeof(weapons))
    {
        hasWeapon = 1;
    }
    
    for (int j = 0; j < sizeof(armours); j++)
    {
        if (armours[j]->id("shield"))
        {
            hasShield = 1;
            shieldLoc = j;
            break;
        }
    }
    
    if (hasWeapon && !random(4))
    {
        messages = mess_with_weapon(player, target,  weapons[0]);
    } else if (hasShield && !random(4))
    { 
        messages = mess_with_shield(player, target, armours[shieldLoc]);
    } else 
    {
        messages = mess_with_dodge(player, target);
    }

    who->catch_tell(messages[0]);
    target->catch_tell(messages[1]);
    who->tell_watcher(messages[2], target);
        
}

/**
 * Create the messages when a weapon is used to block
 */
private mixed
mess_with_weapon(object who, object target, object weapon)
{
    string *message;
    
    message = ({"You parry "+target->query_the_name(who)+"'s attack with "+
        "your "+weapon->query_short()+"!\n",
        who->query_The_name(target)
            +" parries your attack with "+HIS(who)+
            " "+weapon->query_short()+"!\n",
        QCTNAME(who)+" parries "+QTNAME(target)+"'s "
            +"attack with "+HIS(who)+" "+weapon->query_short()
            +"!\n"});
        
    return message;
}

/**
 * Create the messages when a shield is used to block
 */
private mixed
mess_with_shield(object who, object target, object shield)
{
    string *message;
    
    message = ({"You block "+target->query_the_name(who)
                +"'s attack with "+
                "your "+shield->query_short()+"!\n",
        who->query_The_name(target)
            +" blocks your attack with "+HIS(who)+
            " "+shield->query_short()+"!\n",
        QCTNAME(who)+" blocks "+QTNAME(target)+"'s "+
            "attack with "+HIS(who)+" "+shield->query_short()+"!\n"});
        
    return message;
}


/**
 * Create the messages for a dodge
 */
 
private mixed
mess_with_dodge(object who, object target)
{

    string *message;
    
    message = ({"You dodge "+target->query_the_name(who)+"'s attack!\n",
        who->query_The_name(target)
            +" dodges your attack!\n",
        QCTNAME(who)+" dodges "+QTNAME(target)+"'s attack!\n"});
        
    return message;     
}
