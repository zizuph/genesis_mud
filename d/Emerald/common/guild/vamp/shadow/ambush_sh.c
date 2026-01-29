#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define NONE      0
#define PREPARING 1
#define READY     2
#define RESETTING 3

#define PREP_TIME  20.0
#define RESET_TIME 30.0

public int ambush_status = NONE;
public int prep_alarm = 0;

public void complete_ambush_preparation();
public void reset_ambush();
public string damage_type_desc();

public mixed
prepare_ambush()
{
    if (ambush_status == PREPARING)
    {
        return "You are already preparing.\n";
    }

    if (ambush_status == READY)
    {
        return "There is no need to prepare any more:  you are ready for " +
            "an ambush.\n";
    }

    if (ambush_status == RESETTING)
    {
        return "You are not ready to prepare another ambush yet.\n";
    }

    ambush_status = PREPARING;
    prep_alarm = set_alarm(PREP_TIME, 0.0, complete_ambush_preparation);
    return 1;
}

public void
complete_ambush_preparation()
{
    prep_alarm = 0;
    ambush_status = READY;
    shadow_who->catch_tell("You are ready for an ambush.\n");
}

public void
abort_ambush_preparation()
{
    if (prep_alarm)
    {
        remove_alarm(prep_alarm);
        prep_alarm = 0;
    }

    ambush_status = NONE;
}

public int
query_ambush_prepared()
{
    return (ambush_status == READY);
}

public void
execute_ambush(object target)
{
    int hitsuc, hitval, seen;
    mixed why;
    object attacker_combat_ob;
    mixed *hit_res;

    /* make checks to be sure we can still attack */

    if (!target || (environment(shadow_who) != environment(target)))
    {
        shadow_who->catch_tell("Your enemy seems to have slipped away " +
            "before you could ambush.\n");
        return;
    }

    if (shadow_who->query_prop(LIVE_I_STUNNED))
    {
        shadow_who->catch_tell("You can't perform an ambush while stunned.\n");
        return;
    }

    if (target->query_not_attack_me(this_player(), -1))
    {
        shadow_who->catch_tell("You can't manage to ambush " +
            target->query_the_name(shadow_who) + ".\n");
        return;
    }

    if (stringp(why = c_can_attack(target, "slash")))
    {
        shadow_who->catch_tell(why);
        return;
    }

    shadow_who->attack_object(target);

    attacker_combat_ob = shadow_who->query_combat_object();
    /* Test to see if we hit the target and apply damage if so. */

    if (seen = (CAN_SEE_IN_ROOM(target) && CAN_SEE(target, shadow_who)))
    {
        hitval = 60;
    }
    else
    {
        hitval = 100;
    }
    if ((hitsuc = attacker_combat_ob->cb_tohit(-1, 100, target)) > 0)
    {
        int pen = (MIN(150, STR(shadow_who)) + 
                   MIN(150, DEX(shadow_who)) + 
                   shadow_who->query_skill(SS_VAMP_SLASH)) * 4;
    
        hit_res = target->hit_me(pen, MAGIC_DT, shadow_who, -1);
    
    }
    else
    {
        // miss!
        hit_res = target->hit_me(hitsuc, 0, shadow_who, -1);
    }

    /* apply fatigue */
    if (shadow_who->query_fatigue() > 2)
    {
        shadow_who->add_fatigue(-3);
    }
    else
    {
        shadow_who->set_fatigue(0);
        shadow_who->heal_hp(-3);
    }

    shadow_who->add_attack_delay(random(3));

    if (hit_res[0] >= 0)
    {
        shadow_who->catch_tell("You ambush " + target->query_the_name(shadow_who) +
                                ".\n");
        target->catch_tell("You were ambushed by " +
            shadow_who->query_the_name(target) + ".  You took damage.\n");
        /* Kill the target if hps are <= 0 */
        if (target->query_hp() <= 0)
        {
            target->do_die(shadow_who);
        }
    }
    else if (hit_res[0] < -50)
    {
        shadow_who->catch_tell("You leap toward " +
            target->query_the_name(shadow_who) + " in an ambush, but " +
            target->query_pronoun() + " easily avoids you.\n");

        if (seen)
        {
            shadow_who->catch_msg(shadow_who->query_The_name() +
                " leaps at you, trying to " + damage_type_desc() +
                ".  You easily avoid " + shadow_who->query_possessive() +
                " attack, though.\n");
        }
        else
        {
            shadow_who->catch_msg(shadow_who->query_The_name() + 
                " suddenly appears and leaps at you, trying to " +
                damage_type_desc() + ".  You easily avoid " +
		shadow_who->query_possessive() + " attack, though.\n");
        }
    }

    ambush_status = RESETTING;
    set_alarm(RESET_TIME, 0.0, reset_ambush);
}

public void
reset_ambush()
{
    shadow_who->catch_tell("You are ready to set up another ambush.\n");
    ambush_status = NONE;
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

public string
damage_type_desc()
{
    string dt_desc, wep_desc;
    object shield, wep, tmp1, tmp2;
    int dt;

    dt_desc = "smash";
    wep_desc = "fists";

    tmp1 = shadow_who->query_tool(W_LEFT);
    tmp2 = shadow_who->query_tool(W_RIGHT);

    if (tmp1 || tmp2)
    {
    	if (tmp1 == tmp2)
    	{
    	    if (check_weapon(tmp1))
 	    {
                wep = tmp1;
	    }
            else if (check_shield(tmp1))
	    {
	        shield = tmp1;
	    }
    	}
    	else
    	{
	    if (tmp1)
	    {
	    	if (check_weapon(tmp1))
	    	{
	    	    wep = tmp1;
	    	}
            	else if (check_shield(tmp1))
	    	{
	    	    shield = tmp1;
	        }
	    }

            if (!tmp1 || !wep)
	    {
	        if (check_weapon(tmp2))
		{
		    wep = tmp2;
		}
                else if (check_shield(tmp2))
		{
		    shield = tmp2;
		}
	    }
	}

        if (wep)
	{
            dt = wep->query_dt();
            if (dt & W_SLASH)
	    {
	        dt_desc = "slash";
	    }
	    else if (dt & W_BLUDGEON)
	    {
	        dt_desc = "smash";
	    }
	    else if (dt & W_IMPALE)
	    {
	        dt_desc = "stab";
	    }

	    wep_desc = QSHORT(wep);
	}
        else if (shield)
	{
            dt_desc = "bash";
	    wep_desc = QSHORT(shield);
	}
    }    

    return dt_desc + " you with " + shadow_who->query_possessive() + wep_desc;
}
