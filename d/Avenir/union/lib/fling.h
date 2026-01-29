#pragma strict_types
/*
 * Special Attack: FLING
 *
 * Revisions:
 *    Lilith, May 1998: Changed resolve_task to SIMPLE from ROUTINE.
 *    Lilith, May 1998: Added flick emote.
 *    Lilith, Jun 2003: Updated flick emote.
 *    Lilith, Sep 2003: Updated last_move per AoB note
 *    Lilith, Oct 2003: Rolled back last_move change -- Union attacks
 *                      already use randomized prep and recover times,
 *                      so additional code to prevent bouncing isn't needed.
 *    Lilith, May 2004: Trying to patch hitloc ck to get rid of runtime error.
 *    Lucius, May 2005: Changed dare check to allow attacking existing enemies
 *                      and allow for switching to an active enemy when one dies.
 *    Lucius, Jan 2008: Cleaned up a few bits, re-indented code and added
 *                      in the new query_speed mudlib calculations into
 *                      the alarms. Synced up checks + balances between
 *                      slash and fling specials.
 *    Lucius, Jan 2008: Re-ordered the checks in fling startup to reduce the
 *                      amount of spurious knife-drawings for event failures.
 *    Lucius, Apr 2008: Changes provoked by AoB.
 *    Lucius, Apr 2009: Changes to targetting logic, and specified knife
 *    			selection routines. Darkness checks as well.
 *    Lucius, Aug 2017: Minor cleanups, removed extraneous defines, fixed
 *    			prep/recover calculations.
 */
#define MIN_TIME_RECOVER_FLING	4
#define MAX_TIME_RECOVER_FLING	10
#define MIN_TIME_PREP_FLING	3
#define MAX_TIME_PREP_FLING	10


public int
fling(string str)
{
    mixed tmp;
    string str1, str2;
    object knife, enemy, *what;

    if (tmp = check_prep(TP, P_FLING))
    {
	NF((stringp(tmp) ? tmp : "You are not yet ready.\n"));
	return 0;
    }

    if (TP->query_prop(LIVE_I_STUNNED) ||
      TP->query_prop(LIVE_I_ATTACK_DELAY))
    {
	write("You cannot attack when you are stunned.\n");
	return 1;
    }

    if (!(tmp = ENV(TP)->query_prop(ROOM_M_NO_ATTACK)))
	tmp = enemy->query_prop(OBJ_M_NO_ATTACK);

    if (tmp)
    {
	write_vbfc(stringp(tmp) ? tmp :
	  "A feeling of peace prevents that.\n");
	return 1;
    }

    if (strlen(str))
    {
	if (sscanf(str, "%s at %s", str1, str2) != 2)
	    str1 = str2 = str;
    }

    if (!strlen(str2) || (str2 == "enemy"))
    {
	enemy = TP->query_attack();
	if (!CAN_SEE(TP, enemy))
	    enemy = 0;
    }
    else
    {
	/* Only check this for target selection, we
	 * are kind and allow to fling to existing
	 * ones in the dark.
	 */
	if (!CAN_SEE_IN_ROOM(TP))
	{
	    write("You cannot see your surroundings, "+
	      "let alone a new target.\n");
	    return 1;
	}

	if (!sizeof(what = PARSE_COMMAND(str2,
	      filter(all_inventory(environment(TP)), living),
	      "[at] [the] %l")))
	{
	    enemy = TP->query_attack();
	    if (!CAN_SEE(TP, enemy))
		enemy = 0;
	}
	else if (sizeof(what) > 1)
	{
	    write("You can't fling something at more than "+
	      "one thing at a time.\n");

	    return 1;
	}
	else
	{
	    enemy = what[0];
	    /*
	     * If we matched a living, do not try to re-use
	     * the same pattern to match a knife later.
	     */
	    if (str1 == str2)
		str1 = "";
	}
    }

    if (!objectp(enemy))
    {
	write("You don't see anything to fling at.\n");
	return 1;
    }

    if (!F_DARE_ATTACK(TP, enemy) &&
	(TP->query_attack() != enemy))
    {
	write("You don't dare.\n");
	return 1;
    }

    what = 0;

    if (strlen(str1))
    {
	what = PARSE_COMMAND(str1,
	    filter(all_inventory(TP), is_knife), "%i");
    }

    if (sizeof(what))
	knife = what[0];
    else
	knife = get_knife(TP);

    if (!objectp(knife))
    {
	write("Fling what?\n");
	return 1;
    }

    if (knife->query_wt() != W_KNIFE)
    {
	write("You can only fling knives.\n");
	return 1;
    }

    if (knife->query_prop(OBJ_I_BROKEN))
    {
	write("You cannot fling a broken weapon.\n");
	return 1;
    }

    if (sizeof(filter(TP->query_armour(-1),
	  &operator(==)(A_SHIELD) @ &->query_at())))
    {
	write("You cannot properly prepare to fling "+
	  "when hiding behind a shield.\n");
	return 1;
    }

    if (!TP->query_npc() && TP->query_met(enemy) &&
	!IN_ARRAY(enemy, TP->query_enemy(-1)) &&
	TP->query_prop(LIVE_O_LAST_KILL) != enemy)
    {
	write("Fling "+ LANG_THESHORT(knife) +" at "+
	  enemy->query_the_name(TP) +"? "+
	  "Please confirm by typing again.\n");

	TP->add_prop(LIVE_O_LAST_KILL, enemy);
	return 1;
    }

    tmp = FLING(TP);
#ifdef SKILLS_AFFECTED_BY_FLAME
    tmp -= FLAME_DIFF(tmp, PSTATE);
#endif
    tmp = (MIN_TIME_PREP_FLING * 100) / tmp;
    tmp = max(MIN_TIME_PREP_FLING, tmp);
    tmp = min(MAX_TIME_PREP_FLING, tmp);

    float delay = TP->query_speed((int)tmp);
    set_alarm(delay, 0.0, &do_fling(TP, enemy, knife));

    knife->add_prop(UNION_FLINGING, 1);
    TP->add_prop(PREP, P_FLING);

    write("You prepare to fling "+ LANG_THESHORT(knife) +
      " at "+ enemy->query_the_name(TP) +".\n");

    /* If not already in a fight, the enemy has a chance to
     * detect what the player is up to... */
    if (!enemy->query_attack() &&
	(enemy->query_skill(SS_AWARENESS) * 2 > TP->query_stat(SS_DEX)))
    {
	enemy->catch_tell("You notice "+ TP->query_the_name(enemy) +
	  " looking at you closely, as if preparing to do something.\n");
    }

    return 1;
}

private void
enemy_pickup(object enemy, object weapon)
{
    if (objectp(enemy) && present(weapon, ENV(enemy)))
	enemy->command("$get "+ OB_NAME(weapon));
}

/*
 * The result of the fling attack. A few checks, and
 * the hit result.
 */
private void
do_fling(object me, object enemy, object knife)
{
    knife->remove_prop(UNION_FLINGING);

    if (!objectp(me))
	return;

    me->add_prop(PREP, P_WAITING);

    mixed tmp = FLING(me);
#ifdef SKILLS_AFFECTED_BY_FLAME
    tmp -= FLAME_DIFF(tmp, PSTATE);
#endif
    tmp = (MIN_TIME_RECOVER_FLING * 100) / tmp;
    tmp = max(MIN_TIME_RECOVER_FLING, tmp);
    tmp = min(MAX_TIME_RECOVER_FLING, tmp);

    float delay = me->query_speed((int)tmp);
    set_alarm(delay, 0.0, &rem_prep(me));

    if (!present(enemy, ENV(me)))
    {
	if (present(enemy = me->query_attack(), ENV(me)))
	{
	    ME("With alacrity and grace you switch focus "+
	      "to your new enemy.");
	}
	else
	{
	    ME("You stop preparing your throw since "+
	      "your target is no longer here.");
	    return;
	}
    }

    if (!present(knife, me))
    {
	ME("You stop preparing your throw since you "+
	  "no longer hold the knife.");
	return;
    }

    if (!enemy || !living(enemy) || !knife || !me)
    {
	ME("Something went wrong! You stop preparing your throw.");
	return;
    }

    if (enemy->query_ghost())
    {
	ME(QCTNAME(enemy) +" is already dead!");
	return;
    }

    /* Check to see if the enemy can be hit at all */
    if (enemy->query_not_attack_me(me, -1))
	return;

    if (!(tmp = ENV(me)->query_prop(ROOM_M_NO_ATTACK)))
	tmp = enemy->query_prop(OBJ_M_NO_ATTACK);

    if (tmp)
    {
	me->catch_msg(stringp(tmp) ? tmp :
	  "A feeling of peace prevents that.\n");
	return;
    }

    if (me->query_attack() != enemy)
	me->attack_object(enemy);

    ME("You fling "+ LANG_THESHORT(knife) +" at "+ QTNAME(enemy) +".");
    YOU(QCTNAME(me) +" flings "+ LANG_ASHORT(knife) +" at you.");
    TW(QCTNAME(me) +" flings "+ LANG_ASHORT(knife) +" at "+
	QTNAME(enemy)+".");

    int success = me->resolve_task(TASK_SIMPLE,
	({ TS_DEX, SS_WEP_KNIFE, SS_FLING }),
	enemy, ({ TS_INT, SS_DEFENCE }));

    CDBB; CDB("Success of "+success);

    /* To hit is affected by how much you carry and how drunk you are,
     * both calculated in %'s of the max. Note if you are at max
     * intox or max encumberance, you will _always_ miss the target.
     */
    if (success > 0)
    {
	success -= (success * me->query_encumberance_weight()) / 100;
	success -= (success * DRUNK(me)) / 100;
	CDB("Encumb-Intox ck: Success of "+success);
    }

    /* Be nice and tell the player why is he fighting so lousy... */
    if (DRUNK(me) > 60 + random(20))
	ME("Your throw is adversely affected by your drunken state.");
    else if (me->query_encumberance_weight() > 60 + random(20))
	ME("You are so loaded down that your throw is poorly aimed.");

    string kn = knife->short();

    if (success <= 0)  // We miss completely
    {
	/* lose some grace */
	me->adjust_union_virtue(US_GRACE, -(random(5)));

	/* Otherwise just miss */
	ME("You miss completely, and your "+ kn +
	  " flies into the ground.");
	TW(QCTNAME(me) +" misses completely, and "+
	  LANG_THESHORT(knife) +" flies into the ground.");

	knife->move(ENV(me), 1);
	if (!random(3))
	    knife->set_dull(knife->query_dull() + 1);

	/* If the enemy is smart & a humanoid, he'll try to pickup the knife */
	if (!query_interactive(enemy) && enemy->query_humanoid() &&
	    enemy->query_stat(SS_INT) > (30 + random(50)))
	{
	    set_alarm(1.0 + itof(random(25 - (DEX(enemy) / 10))),
	      0.0, &enemy_pickup(enemy, knife));
	}
	return;
    }

    /*  We hit! Hurrah!  */
    int skill = FLING(TP) * ((4 * KNIFE(me)) + (3 * DEX(me))) / 500;
    int wcpen = random(STR(me) / 4) + (knife->query_pen() * 2) + 10;
    int   pen = F_PENMOD( wcpen, skill);

    CDB("F_PENMOD("+ wcpen +", "+ skill +") ==  "+pen);
#ifdef SKILLS_AFFECTED_BY_FLAME
    pen -= FLAME_DIFF(pen, PSTATE);
    CDB("After FLAME_DIFF: "+ pen);
#endif

    mixed *hitres = enemy->hit_me(pen, W_IMPALE, me, -1);
    /* Combat system is buggered and returns 0 for hitres sometimes. */
    if (!pointerp(hitres) || (sizeof(hitres) < 4))
	hitres = ({ 0, "body", 0, 0, 0 });

    string hitloc = (hitres[1] ?: "");
    int pdam = hitres[0];

    CDB("hitres[0] (% hurt) = "+ hitres[0]);
    CDB("hitres[1] (hitloc) = "+ hitres[1]);
    CDB("hitres[2] ( phit ) = "+ hitres[2]);
    CDB("hitres[3] (damage) = "+ hitres[3]);
    CDB("hitres[4] (hit id) = "+ hitres[4]);

    /* Lets make the hitlocs look a bit prettier and more descriptive */
    if (enemy->query_humanoid())
    {
	string str = "";

	if (hitloc == "legs")
	    hitloc = (random(2) ? "right" : "left") +" leg";
	if (hitloc == "head" && !random(5))
	    hitloc = (random(2) ? "face" : "throat");
	if (sscanf(hitloc, "%s arm", str) && random(2))
	    hitloc = (random(2) ? "lower "+ hitloc : str +" shoulder");
	if (sscanf(hitloc, "%s leg", str) && random(2))
	    hitloc = (random(2) ? "lower "+ hitloc : str +" thigh");
	if (hitloc == "body" && random(2))
	    hitloc = (random(2) ? "chest" : "stomach");
    }

    /* We hit, but did no damage. Simulate knife was deflected by armour */

    switch(pdam)
    {
    case -2:
	object dummy = one_of_list(enemy->query_weapon(-1));

	ME("Your "+ kn +" flies straight at "+ QTNAME(enemy) +
	    ", but "+ enemy->query_pronoun() +" parries it aside with "+
	    HIS(enemy) +" "+ dummy->short() +".\n");
	TW(QCTNAME(enemy)+" manages to parry aside "+
	    LANG_THESHORT(knife) +"with "+ HIS(enemy) +" "+
	    dummy->short() +".\n");
	YOU("You manage to parry aside "+ QTPNAME(me) +" "+ kn +
	    " with your "+ dummy->short() +".\n");

	knife->move(ENV(me), 1);
	if (!random(3)) knife->set_dull(knife->query_dull() + 1);

	/* If the enemy is smart & a humanoid, he'll try to pickup the weapon */
	if (!query_interactive(enemy) && enemy->query_humanoid() &&
	    enemy->query_stat(SS_INT) > (50 + random(50)))
	{
	    set_alarm(1.0 + itof(random(25 - (DEX(enemy) / 10))), 0.0,
		&enemy_pickup(enemy, knife));
	}
	return;
    case -1:
	object *worn = enemy->query_armour(-1);

	if (sizeof(worn))
	{
	    object arm = one_of_list(worn);

	    tell_room(ENV(enemy), CAP(LANG_THESHORT(knife)) +
		" strikes "+ QTPNAME(enemy) +" "+ arm->short() +
		" and falls to the ground.\n", enemy);
	    YOU(CAP(LANG_THESHORT(knife)) +" strikes your "+
		arm->short() +" and falls to the ground.\n");
	}
	else
	{
	    tell_room(ENV(enemy), CAP(LANG_THESHORT(knife)) +
		" bounces off "+ QTPNAME(enemy) +" "+ hitloc +
		" and falls to the ground.\n", enemy);
	    YOU(CAP(LANG_THESHORT(knife)) +" bounces off your "+
		hitloc +" and falls to the ground.\n");
	}

	knife->move(ENV(enemy), 1);

	/* If the enemy is smart & a humanoid, he'll try to pickup the knife */
	if (!query_interactive(enemy) && enemy->query_humanoid() &&
	    enemy->query_stat(SS_INT) > (50 + random(50)))
	{
	    set_alarm(1.0 + itof(random(25 - (DEX(enemy) / 10))),
	      0.0, &enemy_pickup(enemy, knife));
	}
	return;
    case 0..4:
	ME("The "+ kn +" grazes along "+ QTPNAME(enemy) +" "+ hitloc +".");
	TW("The "+ kn +" grazes along "+ QTPNAME(enemy) +" "+ hitloc +".");
	YOU("The "+ kn +" grazes along your "+ hitloc +".");
	break;
    case  5..12:
	ME("The "+ kn +" flies into the "+ hitloc +" of "+
	    QTNAME(enemy) +", opening a small wound.");
	TW("The "+ kn +" flies into the "+ hitloc +" of "+
	    QTNAME(enemy) +", opening a small wound.");
	YOU("The "+ kn +" flies into your "+ hitloc +
	    ", opening a small wound.");
	break;
    case 13..20:
	ME("The "+ kn +" stabs into "+ QTPNAME(enemy) +" "+ hitloc +".");
	TW("The "+ kn +" stabs into "+ QTPNAME(enemy) +" "+ hitloc +".");
	YOU("The "+ kn +" stabs into your "+ hitloc +".");
	break;
    case 21..34:
	ME("The "+ kn +" tears open a wound in "+ QTPNAME(enemy) +
	    " "+ hitloc +".");
	TW("The "+ kn +" tears open a wound in "+ QTPNAME(enemy) +
	    " "+ hitloc +".");
	YOU("The "+ kn +" tears open a wound in your "+ hitloc +".");
	break;
    case 35..50:
	ME("The "+ kn +" slams into the "+ hitloc +" of "+ QTNAME(enemy) +
	    ", opening a large wound.");
	TW("The "+ kn +" slams into the "+ hitloc +" of "+ QTNAME(enemy) +
	    ", opening a large wound.");
	YOU("The "+ kn +" slams into your "+ hitloc +
	    ", opening a large wound.");
	break;
    case 51..70:
	ME("The "+ kn +" rips open a gash in "+ QTPNAME(enemy) +
	    " "+ hitloc +".");
	TW("The "+ kn +" rips open a gash in "+ QTPNAME(enemy) +
	    " "+ hitloc +".");
	YOU("The "+ kn +" rips open a gash in your "+ hitloc +".");
	break;
    case 71..90:
	ME("The "+ kn +" buries itself into the "+ hitloc +" of "+
	    QTNAME(enemy) +".");
	TW("The "+ kn +" buries itself into the "+ hitloc +" of "+
	    QTNAME(enemy) +".");
	YOU("The "+ kn +" buries itself into your "+ hitloc +".");
	break;
    case 91..98:
	ME("The "+ kn +" nearly impales the "+ hitloc +" of "+
	    QTNAME(enemy) +".");
	TW("The "+ kn +" nearly impales the "+ hitloc +" of "+
	    QTNAME(enemy) +".");
	YOU("The "+ kn +" nearly impales your "+ hitloc +".");
	break;
    default:
	ME("The "+ kn +" buries itself into the "+ hitloc +" of "+
	    QTNAME(enemy) +", coming out the other side!");
	TW("The "+ kn +" buries itself into the "+ hitloc +" of "+
	    QTNAME(enemy) +", coming out the other side!");
	YOU("The "+ kn +" buries itself into your "+ hitloc +
	    ", coming out the other side!");
	break;
    }

    /* Gain some grace from a successful hit, but only a little */
    me->adjust_union_virtue(US_GRACE, random(pdam / 10));

    /* We did damage, move knife into enemy's inv and hurt */
    knife->move(ENV(enemy), 1);  // This is because many npcs auto-drop
    knife->move(enemy, 1);       // things from enter_inv if from is living

    if (!enemy->query_hp())
    {
	enemy->do_die(me);
	return;
    }

    /* Make their wounds bleed */
    if (pdam > 20 && enemy->query_humanoid() &&
	!enemy->query_prop(LIVE_I_UNDEAD))
    {
	object blood = present("avenir_blood", enemy);

	if (objectp(blood))
	    blood->add_hurt(hitloc);
	else
	{
	    setuid();
	    seteuid(getuid());

	    blood = clone_object("/d/Avenir/inherit/blood");
	    blood->add_hurt(hitloc);
	    blood->move(enemy, 1);
	}
    }
}
