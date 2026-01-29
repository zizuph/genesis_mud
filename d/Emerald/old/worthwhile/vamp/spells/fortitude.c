#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include "spells.h"
#include "../guild.h"
#include "../voptions.h"
#include "/std/combat/combat.h"
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

public void exec_attack(object caster, int pwr);

public mapping attacks = ([]); 

#define ATT_RESTR_BIG_ONLY   	   1
#define ATT_RESTR_SMALL_ONLY 	   2
#define ATT_RESTR_NO_BIG      	   4
#define ATT_RESTR_NO_SMALL    	   8
#define ATT_RESTR_SHIELD      	  16
#define ATT_RESTR_WEAPON      	  32
#define ATT_RESTR_DUAL_WEAPON 	  64
#define ATT_RESTR_2H_WEAPON      128
#define ATT_RESTR_TALL_ONLY      256
#define ATT_RESTR_SHORT_ONLY     512
#define ATT_RESTR_NO_TALL       1024
#define ATT_RESTR_NO_SHORT      2048
#define ATT_RESTR_FREE_HAND     4096
#define ATT_RESTR_FREE_HANDS    8192
#define ATT_RESTR_HEAVY_ONLY   16384
#define ATT_RESTR_LIGHT_ONLY   32768
#define ATT_RESTR_NO_HEAVY     65536
#define ATT_RESTR_NO_LIGHT    131072
#define ATT_RESTR_NO_MOUNT    262144
#define ATT_RESTR_MOUNT       524288

public void attack_shoulder_bash(object caster, object target, int pwr);
public void attack_shield_bash(object caster, object target, int pwr);
public void attack_forearm_bash(object caster, object target, int pwr);
public void attack_punch(object caster, object target, int pwr);
public void attack_crush(object caster, object target, int pwr);
public void attack_grab_and_throw(object caster, object target, int pwr);
public void attack_shield_and_weapon(object caster, object target, int pwr);
public void attack_dual_weapon(object caster, object target, int pwr);
public void attack_2h_weapon(object caster, object target, int pwr);

public void
create()
{
    int restr;

    restr = ATT_RESTR_NO_SMALL | ATT_RESTR_NO_MOUNT;
    attacks[restr] = ({ attack_shoulder_bash });
    restr = ATT_RESTR_SHIELD;
    attacks[restr] = ({ attack_shield_bash });
    restr = ATT_RESTR_FREE_HAND | ATT_RESTR_NO_MOUNT;
    attacks[restr] = ({ attack_forearm_bash, attack_punch });
    restr = ATT_RESTR_FREE_HANDS | ATT_RESTR_NO_BIG | ATT_RESTR_NO_MOUNT;
    attacks[restr] = ({ attack_crush });
    restr = ATT_RESTR_FREE_HAND | ATT_RESTR_NO_BIG |
            ATT_RESTR_NO_HEAVY  | ATT_RESTR_NO_MOUNT;
    attacks[restr] = ({ attack_grab_and_throw });
    restr = ATT_RESTR_SHIELD | ATT_RESTR_WEAPON | ATT_RESTR_NO_MOUNT;
    attacks[restr] = ({ attack_shield_and_weapon });
    restr = ATT_RESTR_DUAL_WEAPON;
    attacks[restr] = ({ attack_dual_weapon });
    restr = ATT_RESTR_2H_WEAPON;
    attacks[restr] = ({ attack_2h_weapon });
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0 - configuration successful
 *                1 - configuration unsuccessful, abort spell
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    if (caster && caster->query_prop(VAMP_I_FORTITUDE))
    {
        caster->catch_tell("Fail.\n");
        return 1;
    }

    set_spell_name("fortitude");
    set_spell_desc("Increase strength");
    set_spell_time(2);
    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);
    set_spell_ingredients(({}));
    set_spell_resist(spell_resist_beneficial);
    set_spell_target(spell_target_caster);

    return 0;
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object ob;

    setuid();
    seteuid(getuid());
    ob = clone_object("/d/Emerald/vamp/spells/obj/fortitude_obj");
    ob->set_fortitude(result * (100 - resist[0]) / 100);
    make_spell_effect_object(ob, caster, caster, resist, result);

    caster->catch_tell("You feel stronger.\n");

    set_alarm(itof(random(5) + 2), 0.0, &exec_attack(caster, result));
}

public void
attack_shoulder_bash(object caster, object target, int pwr)
{
    caster->catch_tell("attack_shoulder_bash\n");
}

public void
attack_shield_bash(object caster, object target, int pwr)
{
    caster->catch_tell("attack_shield_bash\n");
}

public void
attack_forearm_bash(object caster, object target, int pwr)
{
    caster->catch_tell("attack_forearm_bash\n");
}

public void
attack_punch(object caster, object target, int pwr)
{
    caster->catch_tell("attack_punch\n");
}

public void
attack_crush(object caster, object target, int pwr)
{
    caster->catch_tell("attack_crush\n");
}

public void
attack_grab_and_throw(object caster, object target, int pwr)
{
    caster->catch_tell("attack_grab_and_throw\n");
}

public void
attack_shield_and_weapon(object caster, object target, int pwr)
{
    caster->catch_tell("attack_shield_and_weapon\n");
}

public void
attack_dual_weapon(object caster, object target, int pwr)
{
    caster->catch_tell("attack_dual_weapon\n");
}

public void
attack_2h_weapon(object caster, object target, int pwr)
{
    caster->catch_tell("attack_2h_weapon\n");
}


public mixed *
damage_target(object caster, object target, int pen)
{
    int ran, i, j, hit, *hloc_ids, ac;
    object cob;
    mixed *hloc;

    /* Pick a hitlocation and apply armour mod to pen */
    ran = random(100);

    cob = target->query_combat_object();
    hloc_ids = cob->query_hitloc_id();
    hit = -1;
    j = 0;
    
    for (i = 0; i < sizeof(hloc_ids); i++)
    {
        hloc = cob->query_hitloc(hloc_ids[i]);
    
        j += hloc[HIT_PHIT];
        if (j >= ran)
        {
            hit = hloc_ids[i];
            ac = (intp(hloc[HIT_AC]) ? 
                hloc[HIT_AC] : hloc[HIT_AC][random(sizeof(hloc[HIT_AC]))]);
            pen -= random(ac / 2);
            break;
        }
    }

    return target->hit_me(pen, MAGIC_DT, caster, hit);
}

public int
check_weapon(object weapon)
{
    return weapon->check_weapon();
}

public int
check_shield(object armour)
{
    return armour->check_armour() && (armour->query_ac() > 5);
}

public void
exec_attack(object caster, int pwr)
{
    object target, cob;
    int i, restrs = 0, *restr_list;
    mixed tmp1, tmp2;
    function f, *att_funs = ({});

    if (!(target = caster->query_attack()))
    {
        return;
    }

    if (!(cob = caster->query_combat_object()))
    {
        return;
    }

    if (caster->query_prop(LIVE_I_STUNNED))
    {
        caster->catch_tell("You miss your chance to attack " +
            target->query_the_name(caster) + ".\n");
        return;
    }

    if (target->query_not_attack_me(this_player(), -1))
    {
        caster->catch_tell("You can't manage to attack " +
            target->query_the_name(caster) + ".\n");
        return;
    }

    if (target->query_prop(OBJ_I_NO_ATTACK))
    {
        caster->catch_tell("You sense a divine presence protecting the " +
            "intended victim.\n");
        return;
    }

    if (environment(target)->query_prop(ROOM_I_NO_ATTACK))
    {
        caster->catch_tell("Your senses detect a magical peace spell over " +
            "the room.\n");
        return; 
    }

    restrs |= 
        caster->query_prop(LIVE_O_STEED) ? ATT_RESTR_MOUNT : ATT_RESTR_NO_MOUNT;

    tmp1 = target->query_prop(CONT_I_HEIGHT);
    tmp2 = caster->query_prop(CONT_I_HEIGHT);
    if (tmp1 >= (tmp2 * 80 / 100))
    {
        restrs |= ATT_RESTR_TALL_ONLY | ATT_RESTR_NO_SHORT;
    }
    else
    {
        restrs |= ATT_RESTR_NO_TALL;

        if (tmp1 <= (tmp2 * 40 / 100))
	{
            restrs |= ATT_RESTR_SHORT_ONLY;
        }
        else
        {
            restrs |= ATT_RESTR_NO_SHORT;
	}
    }

    tmp1 = target->query_prop(OBJ_I_WEIGHT);
    tmp2 = caster->max_weight();
    if (tmp1 >= (tmp2 * 180 / 100))
    {
        restrs |= ATT_RESTR_HEAVY_ONLY | ATT_RESTR_NO_LIGHT;
    }
    else
    {
        restrs |= ATT_RESTR_NO_HEAVY;

        if (tmp1 <= (tmp2 * 40 / 100))
	{
            restrs |= ATT_RESTR_LIGHT_ONLY;
	}
        else
	{
            restrs |= ATT_RESTR_NO_LIGHT;
	}
    }

    tmp1 = target->query_prop(CONT_I_VOLUME);
    tmp2 = caster->query_prop(CONT_I_VOLUME);
    if (tmp1 >= (tmp2 * 180 / 100))
    {
        restrs |= ATT_RESTR_BIG_ONLY | ATT_RESTR_NO_SMALL;
    }
    else
    {
        restrs |= ATT_RESTR_NO_BIG;

        if (tmp1 <= (tmp2 * 40 / 100))
	{
            restrs |= ATT_RESTR_SMALL_ONLY;
	}
        else
	{
            restrs |= ATT_RESTR_NO_SMALL;
	}
    }

    tmp1 = caster->query_tool(W_LEFT);
    tmp2 = caster->query_tool(W_RIGHT);
    if (!tmp1 && !tmp2)
    {
        restrs |= ATT_RESTR_FREE_HANDS | ATT_RESTR_FREE_HAND;
    }
    else if (!tmp1 || !tmp2)
    {
        restrs |= ATT_RESTR_FREE_HAND;

        if (check_weapon(tmp1) || check_weapon(tmp2))
	{
            restrs |= ATT_RESTR_WEAPON;
	}
        else if (check_shield(tmp1) || check_shield(tmp2))
	{
            restrs |= ATT_RESTR_SHIELD;
	}
    }
    else
    {
        if (check_shield(tmp1) || check_shield(tmp2))
	{
            restrs |= ATT_RESTR_SHIELD;

            if (check_weapon(tmp1) || check_weapon(tmp2))
	    {
                restrs |= ATT_RESTR_WEAPON;
	    }
	}

        if (check_weapon(tmp1))
        {
            restrs |= ATT_RESTR_WEAPON;

            if (tmp1 == tmp2)
	    {
                restrs |= ATT_RESTR_2H_WEAPON;
	    }
            else if (check_weapon(tmp2))
	    {
                restrs |= ATT_RESTR_DUAL_WEAPON;
            }
	}
        else if (check_weapon(tmp2))
	{
            restrs |= ATT_RESTR_WEAPON;
	}
    }

    restr_list = m_indices(attacks);
    for (i = 0; i < sizeof(restr_list); i++)
    {
        if (restr_list[i] &~ restrs)
	{
            continue;
	}

        att_funs += attacks[restr_list[i]];
    }

    set_this_player(caster);
    dump_array(restrs);
    dump_array(att_funs);

    if (!sizeof(att_funs))
    {
        return;
    }

    f = att_funs[random(sizeof(att_funs))];
    f(caster, target, pwr);


#if 0
    if (target->query_humanoid())
    {
        att_funs += ({ attack_back, attack_front });

        // Do a shoulder bash if the target isn't too short
        if (target->query_prop(CONT_I_HEIGHT) >=
            (caster->query_prop(CONT_I_HEIGHT) * 80 / 100))
	{
	    att_funs += ({ attack_shoulder_bash });
	}

        // Do a shield attack if there's a solid enough shield
        if (((tmp1 = left) &&
            left->check_armour() &&
            (left->query_ac() > 5)) ||
            ((tmp1 = right) &&
            right->check_armour() &&
            (right->query_ac() > 5)))
        {
            att_funs += ({ &att_shield_bash(tmp1) });
        }

        
        // Attacks requiring one or both hands to be free
        if (!left || !right)
        {
            att_funs += ({ attack_forearm_bash, attack_punch });

            // Check for large targets
            if (target->query_prop(CONT_I_VOLUME) <=
                (caster->query_prop(CONT_I_VOLUME) * 180 / 100))
            {
  	        // Check for heavy targets
                if (target->query_prop(OBJ_I_WEIGHT) <=
                    caster->max_weight() * 180 / 100)
                {
                    att_funs += ({ attack_grab_and_throw });
                }
    
                // Attacks that require both hands to be free
                if (!left && !right)
                {
                    att_funs += ({ attack_crush });
                }
            }
        }
        else
	{
            if ((((tmp1 = left)  && (tmp1->check_armour()) && (tmp1->query_ac() > 5)) ||
                ((tmp1  = right) && (tmp1->check_armour()) && (tmp1->query_ac() > 5))) &&
                (((tmp2 = left)  && (tmp2->check_weapon())) ||
                ((tmp2  = right) && (tmp2->check_weapon()))))
	    {
  	        att_funs += ({ attack_shield_weapon(tmp1, tmp2) });
	    }
            else if ((left == right) && (left->check_weapon()))
	    {
  	        att_funs += ({ &attack_2h_weapon(left) });
	    }
            else if (left->check_weapon() && right->check_weapon())
	    {
	        att_funs += ({ &attack_double_weapons(left, right) });
	    }
            else
    }
    else
    {
    }

    if (cob->cb_tohit(-1, 90, target) > 0)
    {
        pen = min(1200, max(200, (caster->query_stat(SS_STR) +
              caster->query_skill(SS_UNARM_COMBAT) * 2 +
              caster->query_effective_vamp_stat() +
              caster->query_skill(SS_ELEMENT_DEATH) +
              pwr) * 2));
        caster->catch_tell(pwr + "\n" + pen + "\n");
        hit_res = damage_target(caster, target, pen);
    }
    else
    {
        // miss!
        hit_res = target->hit_me(-1, 0, caster, -1);
    }

    /* apply fatigue */
    if (caster->query_fatigue() > 2)
    {
        caster->add_fatigue(-3);
    }
    else
    {
        caster->set_fatigue(0);
        caster->heal_hp(-3);
    }

    /* Give some nice messages */
    applyv(&desc_attack(caster, target), hit_res);

    if (hit_res[0] >= 0)
    {
        caster->add_panic(-3 - hit_res[3] / 5);

        /* Kill the target if hps are <= 0 */
        if (target->query_hp() <= 0)
        {
            target->do_die(caster);
        }
    }
#endif
}
