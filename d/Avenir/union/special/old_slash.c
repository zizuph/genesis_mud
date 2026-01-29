/*
 * /d/Avenir/union/special/slash.c
 *
 * This is the union special 'slash' using
 * the standardized combat system.
 *
 * Updated combat aid so that it is doubled when protecting
 * specific Avenir locations.  Arman, Feb 2020.
 *
 * 2021-03-16 - Cotillion
 * - Fixed divsion by zero
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
# define CDB(x)	this_player()->catch_tell("SL: "+ x + "\n")
#else
# define CDB(x)
#endif

#define AOB_DEBUG(x)  find_player("arman")->catch_msg("[fling] " + x + "\n")

/* Caid is doubled when protecting specific areas. This
 * is managed in query_combat_aid_modifier
 */
int max_slash_caid = (SLASH_CAID * 2);

private mapping m_caid = ([]);

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

    set_dt(W_SLASH | W_IMPALE);
    set_tohit(SLASH_TOHIT);
    set_combat_aid(max_slash_caid);

    /* These are overriden by the masked query functions. */
    set_ability_prep_time(MIN_SLASH_PREP);
    set_ability_cooldown_time(MIN_SLASH_RECOVER);

    set_stats(SLASH_STATS);
    set_skills(SLASH_SKILLS);
    set_guild_stat_modifier(SS_OCCUP, 50, 100);

    set_ability_name("slash");
    set_ability_attack_during_prep(0);
    add_ability_restriction(SPECIAL + "fling");
}

public int
query_ability_prep_time(void)
{
    int skill = this_player()->query_skill(SS_SLASH);
#ifdef SKILLS_AFFECTED_BY_FLAME
    skill -= FLAME_DIFF(skill, PSTATE);
#endif
    int time = (MIN_SLASH_PREP * 100) / max(skill, 1);
    return max(MIN_SLASH_PREP, min(MAX_SLASH_PREP, time));
}

public int
query_ability_cooldown_time(void)
{
    int skill = this_player()->query_skill(SS_SLASH);
#ifdef SKILLS_AFFECTED_BY_FLAME
    skill -= FLAME_DIFF(skill, PSTATE);
#endif
    int time = (MIN_SLASH_RECOVER * 100) / max(skill, 1);
    return max(MIN_SLASH_RECOVER, min(MAX_SLASH_RECOVER, time));
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
    object knife = has_knife(actor);
    object sword = has_sword(actor);

    if (actor->query_skill(SS_SLASH) < 1)
    {
        actor->catch_msg("You lack the required skill to perform a slash.\n");
        return 0;
    }
    
    if (!objectp(knife) || !objectp(sword))
    {
	actor->catch_tell("You need to be wielding both a dagger "+
	    "and a sword in order to slash.\n");
	return 0;
    }

    return ({ sword, knife });
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
    if (!this_player()->query_npc() && this_player()->query_attack())
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
}

public void
hook_autochanged_target(object target)
{
    write("With alacrity and grace you switch focus to " +
	target->query_the_name(this_player()) +".\n");
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
 * Function name: ability_msg
 * Description  : Mask this function so that the prepare messages don't
 *                show up when this ability goes off.
 */
static void
ability_msg(object actor, mixed *targets, string arg)
{
    string zeal = " ";

    if(query_union_protected_area())
        zeal = " zealously ";

    actor->catch_tell("You prepare to" +zeal+ "slash "+
	targets[0]->query_the_name(actor) + "!\n");

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
    
    // Should be re-balanced if SLASH_TOHIT is changed from 80
    if (present(SWAY_ID_UNERR, TP))
    {
        switch(sway_phase)
        {
            case 1:
                tohit = SLASH_TOHIT + 20;
                break;
            case 2:
                tohit = SLASH_TOHIT + 25;
                break;
            case 3..5:
                tohit = SLASH_TOHIT + 28;
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
	write("Your intoxicated state is adversely affecting "+
	    "your abilities.\n");
    }

    if (encumb >= ENCUMB_SLASH)
    {
	mod = EFF_REDUCE(encumb, ENCUMB_SLASH);
	m_caid[name] += mod;
	tohit -= mod;

	CDB("Encumb Ck: "+ encumb +"; tohit: "+ tohit);
	write("You are so weighed down that your attack is not as "+
	    "effective as it might be.\n");
    }

    CDB("Encumb-Intox ck: query_tohit() == "+ tohit);
    return tohit;
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
special_did_hit(int aid, string hdesc, int hid, int phurt,
    		object target, int dt, int phit, int dam,
		mixed *items, int result)
{
    mixed tmp;
    string qweps, sw = items[0]->short(), kn = items[1]->short(),
	   weps, qsw = QSHORT(items[0]), qkn = QSHORT(items[1]);

    CDB(TP->short() +" vs. "+ target->short() + " :: RES="+ result);
    CDB(kn +"\n    ["+ file_name(items[1]) +"]");
    CDB(sw +"\n    ["+ file_name(items[0]) +"]");
    CDB("hitres[0] (% hurt) = "+ phurt);
    CDB("hitres[1] (hitloc) = "+ hdesc);
    CDB("hitres[3] (damage) = "+ dam);
    CDB("hitres[4] (hit id) = "+ hid);

    if (target->query_humanoid())
    {
	if (!strlen(hdesc = one_of_list(hit_locs[hid])))
	    hdesc = one_of_list(hit_locs[one_of_list(m_indexes(hit_locs))]);
    }

    hdesc = (strlen(hdesc) ? hdesc : "body");

    if (random(2))
    {
	weps = kn +" and "+ sw;
	qweps = qkn +" and "+ qsw;
    }
    else
    {
	weps = sw +" and "+ kn;
	qweps = qsw +" and "+ qkn;
    }

    if (result < 1)
    {
        /* Lose some virtue. */
        TP->adjust_union_virtue(US_GRACE,   -(5 + random(5)));
        
	ME("You slash at "+ QTNAME(target) +" with your "+ weps +
	    " but miss completely.");
	TWM(QCTNAME(TP) +" slashes at "+ QTNAME(target) +" with "+
	    HIS(TP) +" "+ qweps +" but misses completely.");
	YOU(QCTNAME(TP) + " slashes at you with "+ HIS(TP) +
	    " "+ qweps +" but completely misses.");
	return;
    }

    /* Gain some grace from a successful hit, but only a little */
    if (phurt >= 0) TP->adjust_union_virtue(US_GRACE, random(phurt / 10));

    /* We hit... */
    switch(phurt)
    {
    case -2: /* ... but were parried! */
        tmp = (object)one_of_list(target->query_weapon(-1));

	ME("You slash at "+ QTNAME(target) +" with your "+ weps +
	    ", but "+ HE(target) +" parries your attack with "+
	    HIS(target) +" " + QSHORT(tmp) +".");
	TWM(QCTNAME(TP) +" slashes "+ HIS(TP) +" "+ qweps +" at "+
	    QTNAME(target) +", but "+ HE(target) +" parries the "+
	    "attack with "+ HIS(target) +" "+ QSHORT(tmp) +".");
	YOU(QCTNAME(TP) + " slashes at you with "+ HIS(TP) +" "+
	    weps +", but you manage to parry it with your " +
	    tmp->short() +".");
        return;

    case -1: /* ... but were dodged! */
	ME("You slash at "+ QTNAME(target) +" with your "+ weps +
	    ", but "+ HE(target) +" dodges out of the way.");
	TWM(QCTNAME(TP) +" slashes at "+ QTNAME(target) +" with "+
	    HIS(TP) +" "+ weps +", but "+ QTNAME(target) +
	    " dodges out of the way.");
	YOU(QCTNAME(TP) + " slashes at you with "+ HIS(TP) +" "+
	    weps +", but you dodge out of the way.");
	return;

    case 0..4:
	ME("Guarding with your "+ sw +", you lightly nick "+
	    QTPNAME(target) +" "+ hdesc +" with your "+ kn +".");
	TW("Guarding with "+ HIS(TP) +" "+ qsw +", "+ QTNAME(TP) +
	    " lightly nicks "+ QTPNAME(target) +" "+ hdesc +" with "+
	    HIS(TP) +" "+ qkn +".");
	YOU("Guarding with "+ HIS(TP) +" "+ qsw +", "+ QTNAME(TP) +
	    " lightly nicks your "+ hdesc +" with "+ HIS(TP) +" "+
	    qkn +".");
	break;

    case 5..10:
	ME("You swing your "+ sw +" up to block, and slash your "+ kn +
	    " lightly along "+ QTPNAME(target) +" "+ hdesc +".");
	TW(QCTNAME(TP) +" swings "+ HIS(TP) +" "+ qsw +" up to block, and "+
	    "slashes "+ HIS(TP) +" "+ qkn +" lightly along "+ QTPNAME(target) +
	    " "+ hdesc +".");
	YOU(QCTNAME(TP) +" swings "+ HIS(TP) +" "+ qsw +" up to block, "+
	    "and slashes "+ HIS(TP) +" "+ qkn +" lightly along your "+
	    hdesc +".");
	break;

    case 11..15:
	ME("You bring your "+ kn +" in low, slashing a shallow wound "+
	    "across "+ QTPNAME(target) +" "+ hdesc +" while guarding "+
	    "with your "+ sw +".");
	TW(QCTNAME(TP) +" brings "+ HIS(TP) +" "+ qkn +" in low, slashing "+
	    "a shallow wound across "+ QTPNAME(target) +" "+ hdesc +
	    " while guarding with "+ HIS(TP) +" "+ qsw +".");
	YOU(QCTNAME(TP) +" brings "+ HIS(TP) +" "+ qkn +" in low, "+
	    "slashing a shallow wound across your "+ hdesc +" while "+
	    "guarding with "+ HIS(TP) +" "+ qsw +".");
	break;

    case 16..20:
	ME("You manage to cut into the "+ hdesc +" of "+ QTNAME(target) +
	    " with your "+ sw +" while feinting with your "+ kn +".");
	TW(QCTNAME(TP) +" cuts into "+ QTPNAME(target) +" "+ hdesc +
	    " with "+ HIS(TP) +" "+ qsw +" while feinting with "+
	    HIS(TP) +" "+ qkn +".");
	YOU(QCTNAME(TP) +" cuts into your "+ hdesc +" with "+ HIS(TP) +
	    " "+ qsw +" while feinting with "+ HIS(TP) +" "+ qkn +".");
	break;

    case 21..25:
	ME("Swinging your "+ sw +" in a wide arc, you slip your "+ kn +
	    " past "+ QTPNAME(target) +" defences and cut into "+
	    HIS(target) +" "+ hdesc +".");
	TW("Swinging "+ HIS(TP) +" "+ qsw +" in a wide arc, "+ QTNAME(TP) +
	    " slips "+ HIS(TP) +" "+ qkn +" past "+ QTPNAME(target) +
	    " defences and cuts into "+ HIS(target) + hdesc +".");
	YOU("Swinging "+ HIS(TP) +" "+ qsw +" in a wide arc, "+ QTNAME(TP) +
	    " slips "+ HIS(TP) +" "+ qkn +" past your defences and "+
	    "cuts into your "+ hdesc +".");
	break;

    case 26..30:
	ME("You open a large wound in "+ QTPNAME(target) +" "+ hdesc +
	    " with your "+ sw +", as well as cutting "+ HIM(target) +
	    " with your "+ kn +".");
	TW(QCTNAME(TP) +" opens a large wound in "+ QTPNAME(target) +
	    " "+ hdesc +" with "+ HIS(TP) +" "+ qsw +", as well as "+
	    "cutting "+ HIM(target) +" with "+ HIS(TP) +" "+ qkn +".");
	YOU(QCTNAME(TP) +" opens a large wound in your "+ hdesc +
	    " with "+ HIS(TP) +" "+ qsw +", as well as cutting you with "+
	    HIS(TP) +" "+ qkn +".");
	break;

    case 31..45:
	ME("You bring your "+ sw +" down hard onto "+ QTPNAME(target) +" "+
	    hdesc +" and stab into "+ HIM(target) +" with your "+ kn +".");
	TW(QCTNAME(TP) +" brings "+ HIS(TP) +" "+ qsw +" down hard onto "+
	    QTPNAME(target) +" "+ hdesc +" and stabs into "+ HIM(target) +
	    " with "+ HIS(TP) +" "+ qkn +".");
	YOU(QCTNAME(TP) +" brings "+ HIS(TP) +" "+ qsw +" down hard onto "+
	    "your "+ hdesc +" and stabs into you with "+ HIS(TP) +" "+
	    qkn +".");
	break;

    case 46..55:
	ME("With one sweeping motion, you slash deeply into "+
	    QTPNAME(target) +" "+ hdesc +" with your "+ weps +".");
	TW("With one sweeping motion, "+ QTNAME(TP) +" slashes deeply "+
	    "into "+ QTPNAME(target) +" "+ hdesc +" with "+ HIS(TP) +
	    " "+ weps +".");
	YOU("With one sweeping motion, "+ QTNAME(TP) +" slashes deeply "+
	    "into your "+ hdesc +" with "+ HIS(TP) +" "+ weps +".");
	break;

    case 56..70:
	ME("You bury your "+ kn +" deep into "+ QTPNAME(target) +" " +
	    hdesc +" while also scoring a brilliant slash with "+
	    "your "+ sw +".");
	TW(QCTNAME(TP) +" buries "+ HIS(TP) +" "+ qkn +" deep into "+
	    QTPNAME(target) +" "+ hdesc +" while also scoring a "+
	    "brilliant slash with "+ HIS(TP) +" "+ qsw +".");
	YOU(QCTNAME(TP) +" buries "+ HIS(TP) +" "+ qkn +" deep into "+
	    "your "+ hdesc +" while also scoring a brilliant slash with "+
	    HIS(TP) +" "+ qsw +".");
	break;

    default:
	ME("You nearly sever "+ QTPNAME(target) +" "+ hdesc +" with "+
	    "your "+ sw +" at the same time as you drive your "+ kn +
	    " deep into "+ HIM(target) +" body.");
	TW(QCTNAME(TP) +" nearly severs "+ QTPNAME(target) +" "+ hdesc +
	    " with "+ HIS(TP) +" "+ qsw +" at the same time as "+
	    HE(TP) +" drives "+ HIS(TP) +" "+ qkn +" deep into "+
	    QTPNAME(target) +"body.");
	YOU(QCTNAME(TP) +" nearly severs your "+ hdesc +" with "+
	    HIS(TP) +" "+ qsw +" at the same time as "+ HE(TP) +
	    " drives "+ HIS(TP) +" "+ qkn +" deep into your body.");
	break;
    }

    /* Lifeform -> deadform */
    if (target->query_hp() < 1)
    {
	if (target->query_humanoid())
	{
	    ME("You bring your "+ kn +" around once more and slash it "+
		" across "+ QTPNAME(target) +" throat!\n"+
		CAP(HE(target)) +" falls to the ground gurgling blood.");
	    TW(QCTNAME(TP) +" brings "+ HIS(TP) +" "+ kn +" around once "+
		"more and slashes it across "+ QTPNAME(target) +
		" throat!\n"+ CAP(HE(target)) +" falls to the ground "+
		"gurgling blood.");
	    YOU(QCTNAME(TP) +"brings "+ HIS(TP) +" "+ kn +" around once "+
		"more and slashes it across your throat!");
	}

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
