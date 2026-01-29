/*
 * /d/Avenir/union/special/fling.c
 *
 * This is the union special 'fling' using
 * the standardized combat system.
 *
 * Updated combat aid so that it is doubled when protecting
 * specific Avenir locations.  Arman, Feb 2020.
 *
 * Modified to take in to account two sway variations,
 * 'unerring' and 'aggressive'.   Arman, Dec 2020.
 *
 * 2021-03-16 - Cotillion
 * - Fixed division by zero
 *
 * 2021-04-04 - Carnak:
 * - Fixed the aggressive and unerring cb_tohit functionality
 */
#pragma no_clone
#pragma no_shadow
#pragma strict_types

inherit "/d/Genesis/specials/std/damage";
#include "special.h"
/*
 * For debugging.
 */
#ifdef COMBAT_DEBUG
# define CDB(x)  TP->catch_tell("FL: "+ x + "\n")
#else
# define CDB(x)
#endif

#define QRN(x)	(x)->query_real_name()

/* Caid is doubled when protecting specific areas. This
 * is managed in query_combat_aid_modifier
 */
int max_fling_caid = (FLING_CAID * 2);

private mapping knives = ([]);
private mapping m_caid = ([]);

/*
 * Allow for choosing a specific knife to fling.
 * (but only in the top inventory level)
 */
public object *
target_fling(object actor, string str)
{
    object knife;

    if (strlen(str))
    {
	parse_command(str, filter(all_inventory(actor),
		&valid_knife(,actor)),
	    "[my] / [the] %o [at] [the] %s", knife, str);
    }

    knives[QRN(actor)] = knife;
    return target_one_other_present_living_or_enemy(actor, str);
}

/*
 * Function name: create_ability
 * Description  : Main fuction that configures the special.
 */
public void
create_ability(void)
{
    ::create_ability();

    setuid();
    seteuid(getuid());

    set_dt(W_IMPALE);
    set_tohit(FLING_TOHIT);
    set_combat_aid(max_fling_caid);

    /* These are overriden by the masked query functions. */
    set_ability_prep_time(MIN_FLING_PREP);
    set_ability_cooldown_time(MIN_FLING_RECOVER);

    set_stats(FLING_STATS);
    set_skills(FLING_SKILLS);
    set_guild_stat_modifier(SS_OCCUP, 50, 100);

    set_ability_name("fling");
    set_ability_target(target_fling);
    set_ability_attack_during_prep(0);
    add_ability_restriction(SPECIAL + "slash");
}

public int
query_ability_prep_time(void)
{
    int skill = TP->query_skill(SS_FLING);
#ifdef SKILLS_AFFECTED_BY_FLAME
    skill -= FLAME_DIFF(skill, PSTATE);
#endif
    int time = (MIN_FLING_PREP * 100) / max(skill, 1);
    return min(MAX_FLING_PREP, max(MIN_FLING_PREP, time));
}

public int
query_ability_cooldown_time(void)
{
    int skill = TP->query_skill(SS_FLING);
#ifdef SKILLS_AFFECTED_BY_FLAME
    skill -= FLAME_DIFF(skill, PSTATE);
#endif
    int time = (MIN_FLING_RECOVER * 100) / max(skill, 1);
    return max(MIN_FLING_RECOVER, min(MAX_FLING_RECOVER, time));
}

public void
apply_costs_to_player(object player)
{
    player->add_fatigue(-SPECIAL_FATIGUE);
}

/*
 * Function name: check_required_items
 * Description  : Check for wielded weapons to determine which of
 *                the various special attacks we will perform.
 */
static mixed *
check_required_items(object actor, mixed *targets,
                     string arg, int pretest)
{
    object *oblist, band, knife;

    if (actor->query_skill(SS_FLING) < 1)
    {
        actor->catch_msg("You lack the required skill to fling a blade.\n");
        return 0;
    }
    
    /* Shields are not allowed. */
    if (sizeof(filter(actor->query_armour(-1),
		&operator(==)(A_SHIELD) @ &->query_at())))
    {
	actor->catch_tell("You cannot properly prepare to fling "+
	    "when hiding behind a shield.\n");

	return 0;
    }
    /*
     * We may already have a knife, either from pre-testing
     * or specifying one as an argument.
     */
    if (objectp(knife = knives[QRN(actor)]))
    {
	if (environment(knife) != actor)
	{
	    knife->remove_prop(UNION_FLINGING);
	    knife = 0;
	}
	else if (!pretest) return ({ knife });
    }
    /*
     * We lost our readied knife or are pre-testing
     * and did not specify one as an argument.
     */
    if (!objectp(knife))
    {   /*
	 * We cannot use the get_knife() here due to the double call
         * and need for inserted messages. So this is mostly a copy.
         */
	foreach(object item: filter(all_inventory(actor), &->id(BAND_ID)))
	{
	    if (!item->check_seen(actor))
		continue;

	    if (sizeof(oblist = filter(all_inventory(item), &valid_knife(,actor))))
	    {
		band = item;
		break;
	    }
	}

	if (!sizeof(oblist) &&
	    !sizeof(oblist = filter(all_inventory(actor), &valid_knife(,actor))))
	{
	    actor->catch_tell("You do not have anything to fling!\n");
	    return 0;
	}

	knife = oblist[0];
	if (knife->move(actor))
	{
	    actor->catch_tell("You are unable to fling the "+
		knife->short() +"!\n");
	    return 0;
	}
    }

//    if (pretest)
    {
	if (objectp(band))
	{
	    actor->catch_tell("You draw "+ LANG_ASHORT(knife) +
		" out of your "+ band->short() +".\n");
	}

	actor->catch_tell("You prepare to fling the "+ knife->short() +
	    " at "+ targets[0]->query_the_name(actor) +".\n");

	if (objectp(band))
	{
	    actor->tell_watcher(QCTNAME(actor) +" draws "+
		LANG_ASHORT(knife) +" out of "+ HIS(actor) +" "+
		band->short() +".\n", 0, 0);
	}
#if 0
/* Does anyone do this anymore? */
	/* If not already in a fight, the enemy has a chance to
	 * detect what the player is up to... */
	if (!targets[0]->query_attack() &&
	    ((targets[0]->query_skill(SS_AWARENESS) * 2) >
		actor->query_stat(SS_DEX)))
	{
	    targets[0]->catch_tell("You notice "+
		actor->query_the_name(targets[0]) +
		" looking at you closely, as if preparing to do something.\n");
	}
#endif
    }

    knife->add_prop(UNION_FLINGING, 1);
    knives[QRN(actor)] = knife;
    return ({ knife });
}

/*
 * Function name: hook_special_complete
 * Description  : Hook that gets called when a special completes
 *                Use this to display messages and to restart
 *                specials.
 */
#ifndef Genesis
public void
hook_special_complete(void)
{
    // Mimic npc's in doing auto-specials.
    if (!TP->query_npc() && TP->query_attack())
	restart_npc_special(0, "");
    else
	::hook_special_complete();
}
#endif

/*
 * The default hook prints garbage.
 */
public void
hook_targets_gone(object *targets)
{
    write("Your enemy is no longer present!\n");
    knives[QRN(TP)]->remove_prop(UNION_FLINGING);
}

public void
hook_autochanged_target(object target)
{
    write("With alacrity and grace you switch focus to " +
	target->query_the_name(TP) +".\n");
}

/*
 * Function name: ability_msg
 * Description  : Mask this function so that the prepare messages don't
 *                show up when this ability goes off.
 */
static void
ability_msg(object actor, mixed *targets, string arg)
{
    // Messages are printed in check_required_items().
}

/*
 *  Shadow Union special attacks provide double caid in combat areas 
 *  they are specifically tasked to protect.
 *
 */
public int
query_union_protected_area()
{
    if( wildmatch("/d/Avenir/union/room/*", file_name(environment(TP))) ||
        wildmatch("/d/Avenir/common/city/*", file_name(environment(TP))) ||
        wildmatch("/d/Avenir/common/bazaar/*", file_name(environment(TP))) ||
        wildmatch("/d/Avenir/common/outpost/*", file_name(environment(TP))) ||
        wildmatch("/d/Avenir/common/port/*", file_name(environment(TP))) )
        return 1;
    else
        return 0;
}

/*
 * As well as reducing the hit success, we also apply the modifier
 * for intox + encumberance to combat aid, lowering effectiveness.
 */
public int
query_combat_aid_modifier(void)
{
    int max_caid, sway_phase;
    float sway_caid_mod;

    sway_phase = TP->query_prop(SWAY_PHASE_PROP);

    string name = TP->query_real_name();
    CDB("Combat aid modifier: reducing by: "+ m_caid[name]);
    max_caid = (100 - m_caid[name]);

    if(!query_union_protected_area())
        max_caid = max_caid / 2;


    // If in aggressive sway stance specials gets a 
    // caid bonus of up to 20%
    if (present(SWAY_ID_AGG, TP))
    {
        switch(sway_phase)
        {
            case 1:
                sway_caid_mod = 1.10;
                break;
            case 2:
                sway_caid_mod = 1.15;
                break;
            case 3..5:
                sway_caid_mod = 1.20;
                break;
            default:
                sway_caid_mod = 1.00;
                break;
        }

        max_caid = ftoi(itof(max_caid) * sway_caid_mod);
    }

    return min(100, max_caid);
}

/*
 * We apply additional penalties for high encumberance
 * and especially intoxication.
 *
 * query_tohit() gets called twice, however, we only wish
 * to influence the first call from query_success which
 * applies the value unmodified to cobj->cb_tohit
 */
public int
query_tohit(void)
{
    string name;
    int drunk, encumb, mod, tohit = ::query_tohit();
    int sway_phase = TP->query_prop(SWAY_PHASE_PROP);
    // Has no real bearings on the special balance, just a feature.
    if (!present(SWAY_ID_AGG, TP) && !present(SWAY_ID_UNERR, TP))
        tohit += 20;

    if (present(SWAY_ID_AGG, TP))
    {
        switch(sway_phase)
        {
            case 1:
                tohit += 10;
                break;
            case 2:
                tohit += 5;
                break;
        }
    }

    /* Do not influence caid modifiers. */
    if (calling_function(0) != "query_success")
        return tohit;

    // Should be re-balanced if FLING_TOHIT is changed from 80
    if (present(SWAY_ID_UNERR, TP))
    {
        switch(sway_phase)
        {
            case 1:
                tohit = FLING_TOHIT + 20;
                break;
            case 2:
                tohit = FLING_TOHIT + 25;
                break;
            case 3..5:
                tohit = FLING_TOHIT + 28;
                break;
        }
    }

    drunk  = DRUNK(TP);
    encumb = TP->query_encumberance_weight();

    name = TP->query_real_name();
    m_caid[name] = 0;

    if (drunk >= DRUNK_LIMIT)
    {
	mod = EFF_REDUCE(drunk, DRUNK_LIMIT);
	m_caid[name] += mod;
	tohit -= mod;

	CDB("Intox Ck: "+ drunk +"; tohit: "+ tohit);
	write("Your throw is adversely affected by your intoxicated state.\n");
    }

    if (encumb >= ENCUMB_FLING)
    {
	mod = EFF_REDUCE(encumb, ENCUMB_FLING);
	m_caid[name] += mod;
	tohit -= mod;

	CDB("Encumb Ck: "+ encumb +"; tohit: "+ tohit);
	write("You are so loaded down that your throw is poorly aimed.\n");
    }

    CDB("Encumb-Intox ck: query_tohit() == "+ tohit);
    return tohit;
}

private void
enemy_pickup(object target, object weapon)
{
    if (!objectp(target) || !objectp(weapon))
	return;

    if (environment(weapon) == environment(target))
	target->command("$get "+ OB_NAME(weapon));
}

private void
lose_knife(object target, object knife)
{
    /* Move to the room and dull */
    knife->move(environment(target), 1);
    /*
     * If the target is smart & humanoid,
     * they'll try to pickup the knife
     */
    if (target->query_npc() && target->query_humanoid() &&
	target->query_stat(SS_INT) > (30 + random(20)))
    {
	set_alarm(itof(1 + random(2)), 0.0,
	    &enemy_pickup(target, knife));
    }
}

/* Nicer hit locations. */
private static mapping hit_locs = ([
    A_HEAD : ({ "face", "forehead", "nose", "eye", "ear",
		"chin", "cheek", "throat", }),
    A_BODY : ({ "chest", "abdomen", "stomach", "kidney", "ribs", }),
    A_LEGS : ({ "left leg", "right leg", "left thigh", "right thigh",
		"lower left leg", "lower right leg", }),
    A_L_ARM: ({ "left arm", "left shoulder",
		"lower left arm", "upper left arm", }),
    A_R_ARM: ({ "right arm", "right shoulder",
		"lower right arm", "upper right arm", }),
]);

/*
 * Function name: special_did_hit
 * Description  : Mask this function to process when the special
 *                scores. Descriptions seen by everyone are set
 *                here.
 * Arguments    : aid   - attack id (always -1)
 *                hdesc - hitloc description
 *                hid   - hitloc id
 *                phurt - % hurt
 *                target - person hit
 *                dt    - damage type
 *                phit  - % hit
 *                dam   - damage amount
 *                items - result of check_required_items
 *                result - result from query_success on 'target'
 */
public void
special_did_hit(int aid, string hdesc, int hid,  int phurt,
    		object target, int dt, int phit, int dam,
		mixed *items,  int result)
{
    mixed tmp;
    object knife = items[0];
    string kn = knife->short(), qkn = QSHORT(knife);
    string zeal = " ";

    CDB(TP->short() +" vs. "+ target->short() + " :: RES="+ result);
    CDB(kn +"\n    ["+ file_name(items[0]) +"]");
    CDB("hitres[0] (% hurt) = "+ phurt);
    CDB("hitres[1] (hitloc) = "+ hdesc);
    CDB("hitres[3] (damage) = "+ dam);
    CDB("hitres[4] (hit id) = "+ hid);

    knife->remove_prop(UNION_FLINGING);

    if(query_union_protected_area())
        zeal = " with zeal ";

    if (target->query_humanoid())
    {
	if (!strlen(hdesc = one_of_list(hit_locs[hid])))
	    hdesc = one_of_list(hit_locs[one_of_list(m_indexes(hit_locs))]);
    }

    ME("You fling" +zeal+ "your "+ kn +" at "+ QTNAME(target) +".");
    TW(QCTNAME(TP) +" flings" +zeal+ HIS(TP) +" "+ qkn +" at "+
	QTNAME(target) +".");
    YOU(QCTNAME(TP) +" flings" +zeal+ HIS(TP) +" "+ qkn +" at you.");

    hdesc = (strlen(hdesc) ? hdesc : "body");
    
    /*
     * Flung weapons should not last forever.
     * Taken from /std/weapon did_hit()
     */
    int hit = knife->query_weapon_hits();
    knife->set_weapon_hits(++hit);
    if (F_WEAPON_CONDITION_DULL(hit,
        knife->query_pen(), knife->query_likely_dull()))
    {
        knife->set_weapon_hits(0);
        knife->set_dull(knife->query_dull() + 1);
    }
    
    if (result < 1)
    {
        /* Lose some virtue. */
        TP->adjust_union_virtue(US_GRACE,   -(5 + random(5)));
        ME("You miss completely, and your "+ kn +
	    " flies into the ground.");
        TWM(QCTNAME(TP) +" misses completely, and the "+
	    qkn +" flies into the ground.");
        TWM(QCTNAME(TP) +" misses you completely, and the "+
	    qkn +" flies into the ground.");

	lose_knife(target, knife);
	return;
    }

    /* Gain some grace from a successful hit, but only a little */
    if (phurt >= 0) TP->adjust_union_virtue(US_GRACE, random(phurt / 10));

    /* We hit... */
    switch(phurt)
    {
    case -2: /* ... but were parried! */
        tmp = (object)one_of_list(target->query_weapon(-1));

        ME("Your "+ kn +" flies straight at "+ QTNAME(target) +
	    " but "+ HE(target) +" parries it aside with "+ HIS(target) +
	    " " + QSHORT(tmp) +".");
        TWM(QCTNAME(target) +" manages to parry aside the "+ qkn +
	    " with "+ HIS(target) +" "+ QSHORT(tmp) +".");
        YOU("You manage to parry aside "+ QTPNAME(TP) +" "+
	    qkn +" with your "+ tmp->short() +".");

	lose_knife(target, knife);
        return;

    case -1:
        tmp = (object *)target->query_armour(-1);

        if (sizeof(tmp))
        {
            object arm = one_of_list(tmp);

	    ME("Your "+ kn +" strikes "+ QTPNAME(target) +
		QSHORT(arm) +" and falls to the ground.");
            TWM("The "+ qkn +" strikes "+ QTPNAME(target) +" "+
		QSHORT(arm) +" and falls to the ground.");
            YOU("The "+ qkn +" strikes your "+
		arm->short() +" and falls to the ground.");
        }
        else
        {
	    ME("Your "+ kn +" strikes "+ QTPNAME(target) +" "+ hdesc +
		" and falls to the ground.");
            TWM("The "+ qkn +" bounces off "+ QTPNAME(target) +
		" "+ hdesc +" and falls to the ground.");
            YOU("The "+ qkn +" bounces off your "+ hdesc +
		" and falls to the ground.");
        }

	lose_knife(target, knife);
        return;
        
    case 0..4:
        ME("The "+ kn +" grazes along "+ QTPNAME(target) +" "+
	    hdesc +".");
        TW("The "+ qkn +" grazes along "+ QTPNAME(target) + " "+
	    hdesc +".");
        YOU("The "+ qkn +" grazes along your "+ hdesc +".");
        break;

    case 5..12:
        ME("The "+ kn +" flies into "+ QTPNAME(target) +" "+
	    hdesc +", opening a small wound.");
        TW("The "+ qkn +" flies into "+ QTPNAME(target) +" "+
	    hdesc +", opening a small wound.");
        YOU("The "+ qkn +" flies into your "+ hdesc +
	    ", opening a small wound.");
        break;

    case 13..20:
        ME("The "+ kn +" stabs into "+ QTPNAME(target) +" "+
	    hdesc +".");
        TW("The "+ qkn +" stabs into "+ QTPNAME(target) +" "+
	    hdesc +".");
        YOU("The "+ qkn +" stabs into your "+ hdesc +".");
        break;

    case 21..34:
        ME("The "+ kn +" tears open a wound in "+ QTPNAME(target) +
	    " "+ hdesc +".");
        TW("The "+ qkn +" tears open a wound in "+ QTPNAME(target) +
	    " "+ hdesc +".");
        YOU("The "+ qkn +" tears open a wound in your "+ hdesc +".");
        break;

    case 35..50:
        ME("The "+ kn +" slams into "+ QTPNAME(target) +" "+ hdesc +
	    ", opening a large wound.");
        TW("The "+ qkn +" slams into "+ QTPNAME(target) +" "+
	    hdesc +", opening a large wound.");
        YOU("The "+ qkn +" slams into your "+ hdesc +
	    ", opening a large wound.");
        break;

    case 51..70:
        ME("The "+ kn +" rips open a gash in "+ QTPNAME(target) +
	    " "+ hdesc +".");
        TW("The "+ qkn +" rips open a gash in "+ QTPNAME(target) +
	    " "+ hdesc +".");
        YOU("The "+ qkn +" rips open a gash in your "+ hdesc +".");
        break;

    case 71..90:
        ME("The "+ kn +" buries itself into "+ QTPNAME(target) +
	    " "+ hdesc +".");
        TW("The "+ qkn +" buries itself into "+ QTPNAME(target) +
	    " "+ hdesc +".");
        YOU("The "+ qkn +" buries itself into your "+ hdesc +".");
        break;

    case 91..98:
        ME("The "+ kn +" nearly impales "+ QTPNAME(target) +" "+
	    hdesc +".");
        TW("The "+ qkn +" nearly impales "+ QTPNAME(target) +" "+
	    hdesc +".");
        YOU("The "+ qkn +" nearly impales your "+ hdesc +".");
        break;

    default:
        ME("The "+ kn +" buries itself into "+ QTPNAME(target) +" "+
	    hdesc +", coming out the other side!");
        TW("The "+ qkn +" buries itself into "+ QTPNAME(target) +" "+
	    hdesc +", coming out the other side!");
        YOU("The "+ qkn +" buries itself into your "+ hdesc +
	    ", coming out the other side!");
        break;
    }
    
    /* We did damage, move knife into target's inv and hurt */
    knife->move(environment(target), 1);  // This is because many npcs auto-drop
    knife->move(target, 1);               // things from enter_inv if from a living

    /* Lifeform -> deadform */
    if (target->query_hp() < 1)
    {
	target->do_die(TP);
	return;
    }

    /* Make their wounds bleed -- if still alive. */
    if (phurt > 20 &&
	!target->query_prop(LIVE_I_UNDEAD) &&
	!target->query_prop(LIVE_I_NO_BODY))
    {
	object wound = clone_object(WOUND_OBJ);
	/* Cosmetic effect only. */
	wound->set_wounding_damage(0);
	wound->set_wounding_hitloc(hid);
	wound->move(target, 1);
	wound->start();
    }
}


/*
 * Function name: hook_changed_env
 * Description:   Return the string that will be printed to the player when
 *                he or she has moved rooms while preparing the ability.
 * Returns:       The message to print.
 */
public void
hook_changed_env()
{
    write("Your sudden movement interrupted your stance, causing you to "
    + "forfeit your " + short() + ".\n");
} /* hook_changed_env */
