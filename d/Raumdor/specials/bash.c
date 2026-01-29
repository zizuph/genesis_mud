#pragma strict_types

#include "defs.h"

inherit "/d/Genesis/specials/std/combat_special_base";

public void 
config_ability()
{
    ::config_ability();

    set_ability_name("bash");
    set_combat_aid(40);
    set_tohit(100);
    set_skills(({ SS_BASHSTUN }) );
    set_ability_offensive(1);
    set_ability_stationary(0);
    set_ability_prep_time(5);
    set_ability_cooldown_time(30);
    set_ability_target(target_one_other_present_living_or_enemy);
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
}

public void
resolve_combat_special(object actor, object target, int hitloc,
   int random_hitloc, int pen, int damage_type,
   mixed * items, int result)
{
    object oStun;
    int iCombatAid;
    string a_desc,
           e_desc,
           arm_desc;

    iCombatAid = query_combat_aid();
        
    if (actor->query_armour(A_R_ARM) || actor->query_armour(A_L_ARM))
        arm_desc = "armoured";
    else
    {
        arm_desc = "bare";
        iCombatAid /= 2;
    }
    // Specials tire us a bit.
    apply_costs_to_player(actor);

    switch (result)
    {
        case -2:
            a_desc = "but " + HE(target) + " deflects the attack";
            e_desc = "but you deflect the attack";
            break;
        case -1:
            a_desc = "but " + HE(target) + " sidesteps the attack";
            e_desc = "but you sidestep the attack";
            break;
        case 0:
            a_desc = "but you miss";
            e_desc = "but " + HE(actor) + "misses";
            break;
        case 1..6:
            a_desc = "slightly dazing " + HIM(target);
            e_desc = "slightly dazing you";
            break;
        case 7..10:
            a_desc = "somewhat numbing " + HIM(target);
            e_desc = "somewhat numbing you";
            break;
        case 11..15:
            a_desc = "leaving " + HIM(target) + " stunned";
            e_desc = "leaving you stunned";
            break;
        case 16..20:
            a_desc = "leaving " + HIM(target) + " greatly dazed and confused";
            e_desc = "leaving you greatly dazed and confused";
            break;
        case 21..25:

            a_desc = "leaving " + HIM(target) + " virtually paralyzed";
            e_desc = "leaving you virtually paralyzed";
            break;
        default:
            a_desc = "rendering " + HIM(target) + " nearly unconscious";
            e_desc = "rendering you nearly unconscious";
    }

    a_desc += "!\n";
    e_desc += "!\n";

    actor->catch_msg("You quickly swing your " + arm_desc +
        "shoulder to bash " + QTPNAME(target) + " body, " + a_desc);
    
    target->catch_msg(QCTNAME(actor) + " suddenly swings " + HIS(actor) +
        " " + arm_desc + " shoulder to bash your body, " + e_desc);

    actor->tell_watcher(QCTNAME(actor) + " suddenly swings " + HIS(actor) +
        " " + arm_desc + " shoulder to bash " + QTPNAME(target) + " body, " +
        a_desc, target);

    if (result > 0)
    {
        oStun = clone_object(SPECIALS_OBJ_DIR + "bash_obj");
        oStun->set_stun_cycle_time(query_ability_time());
        
        // We modify the combat aid to take into account tohit
        iCombatAid = iCombatAid * 100 / (100 - calc_hitme_modifier());
        
        if (!actor->query_npc())
        {
            // NPCs don't generally have guild stat, so we don't limit
            // their abilities by guildstat.
            iCombatAid = calc_guildstat_modifier(actor, iCombatAid);
        }
        oStun->set_stun_combat_aid(iCombatAid);
        oStun->set_effect_caster(actor);
        oStun->set_effect_target(target);
        oStun->move(target, 1);
        oStun->start();
    }
}
