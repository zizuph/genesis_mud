/* The special attacks and abilities of the Union
 *    Cirion 042996
 *
 * Revisions:
 *    Lilith, May 1998: Changed resolve_task to SIMPLE from ROUTINE
 *    Lilith, Jun 2003: Fixed typo, using debug for testing.
 *    Lilith, Sep 2003: Updated last_move per AoB note
 *    Lilith, Oct 2003: Rolled back last_move change -- Union attacks
 *                      already use randomized prep and recover times,
 *                      so additional code to prevent bouncing isn't needed.
 *    Lilith, May 2004: Trying to patch hitloc ck to get rid of runtime error.
 *    Lucius, May 2005: Allow for switching to an active enemy when one dies.
 *    Lucius, Jan 2008: Cleaned up a few bits, re-indented code and added
 *                      in the new query_speed mudlib calculations into
 *                      the alarms. Synced up checks + balances between
 *                      slash and fling specials.
 *    Lucius, Jan 2008: Re-arranged initial checks to catch failures earlier.
 *    Lucius, Aug 2017: Minor cleanups, removed extraneous defines, fixed
 *    			prep/recover calculations.
 */
#define MIN_TIME_RECOVER_SLASH	5
#define MAX_TIME_RECOVER_SLASH	10
#define MIN_TIME_PREP_SLASH	3
#define MAX_TIME_PREP_SLASH	10
/*
 * Special Attack: SLASH
 */
public int
slash(string str)
{
    mixed tmp;
    object *who, enemy;

    if (tmp = check_prep(TP, P_SLASH))
    {
	NF((stringp(tmp) ? tmp : "You are not yet ready.\n"));
	return 0;
    }

    if (!strlen(str) && !TP->query_attack())
	return NF("Slash who?\n");

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

    if (!sizeof(who = parse_this(str, "[the] %l")))
    {
	enemy = TP->query_attack();
    }
    else if (sizeof(who) > 1)
    {
	write("You can't slash "+ COMPOSITE_LIVE(who) +
	  " at the same time.\n");
	return 1;
    }
    else
    {
	enemy = who[0];
    }

    if (!objectp(enemy) || !CAN_SEE(TP, enemy))
    {
	write("You do not see anyone to slash.\n");
	return 1;
    }

    if (!F_DARE_ATTACK(TP, enemy) &&
	(TP->query_attack() != enemy))
    {
	write("You don't dare attack.\n");
	return 1;
    }

    if (!has_sword(TP) || !has_knife(TP))
    {
	write("You would need to be wielding both a sword "+
	  "and a knife to succeed.\n");
	return 1;
    }

    if (!TP->query_npc() && TP->query_met(enemy) &&
	!IN_ARRAY(enemy, TP->query_enemy(-1)) &&
	TP->query_prop(LIVE_O_LAST_KILL) != enemy)
    {
	write("Slash "+ enemy->query_the_name(TP) +
	  "? Please confirm by typing again.\n");

	TP->add_prop(LIVE_O_LAST_KILL, enemy);
	return 1;
    }

    tmp = SLASH(TP);
#ifdef SKILLS_AFFECTED_BY_FLAME
    tmp -= FLAME_DIFF(tmp, PSTATE);
#endif
    tmp = (MIN_TIME_PREP_SLASH * 100) / tmp;
    tmp = max(MIN_TIME_PREP_SLASH, tmp);
    tmp = min(MAX_TIME_PREP_SLASH, tmp);

    float delay = TP->query_speed((int)tmp);
    set_alarm(delay, 0.0, &do_slash(TP, enemy));
    TP->add_prop(PREP, P_SLASH);

    write("You prepare to slash "+
      enemy->query_the_name(TP) +".\n");

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
do_slash(object me, object enemy)
{
    mixed *hitres, tmp;
    string weps, hitloc;
    object wep, sword, knife;
    int success, wcpen, pen, skill, pdam;

    if (!objectp(me))
	return;

    me->add_prop(PREP, P_WAITING);

    tmp = SLASH(me);
#ifdef SKILLS_AFFECTED_BY_FLAME
    tmp -= FLAME_DIFF(tmp, PSTATE);
#endif
    tmp = (MIN_TIME_RECOVER_SLASH * 100) / tmp;
    tmp = max(MIN_TIME_RECOVER_SLASH, tmp);
    tmp = min(MAX_TIME_RECOVER_SLASH, tmp);

    float delay = me->query_speed((int)tmp);
    //    float delay = itof(tmp);
    set_alarm(delay, 0.0, &rem_prep(me));

    if (!present(enemy, ENV(me)))
    {
	if (present(enemy = me->query_attack(), ENV(me)))
	{
	    ME("With alacrity and grace you switch focus "+
	      "to your new enemy.\n");
	}
	else
	{
	    ME("You stop preparing your slash since "+
	      "the target is no longer present.\n");
	    return;
	}
    }

    if (!enemy || !living(enemy) || !me)
    {
	ME("Something went wrong! You stop preparing your slash.");
	return;
    }

    if (!objectp(knife = has_knife(me)) ||
	!objectp(sword = has_sword(me)))
    {
	ME("You would need to be wielding both a sword "+
	  "and a knife to succeed.");
	return;
    }

    if (enemy->query_ghost())
    {
	ME("You slash through "+ QTPNAME(enemy) +
	  " incorporeal body, doing no damage.");
	return;
    }

    /* Check to see if the enemy can be hit at all */
    if (enemy->query_not_attack_me(me, -1))
	return;

    /* Check again to see if you are in a peace room, because you might have
     * chased someone into one after you started preparing.
     */
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

    success = me->resolve_task(TASK_SIMPLE,
	({ TS_DEX, SS_WEP_KNIFE, SS_WEP_SWORD, SS_SLASH }),
	enemy, ({ TS_WIS, SS_DEFENCE }));

    CDB("Success of "+success);

    /* To hit is affected by how much you carry and how drunk you are,
     * both calculated in %s of the max. Note if you are at max
     * intox or max encumberance, you will _always_ miss the target.
     */
    if (success > 0)
    {
	success -= (success * me->query_encumberance_weight()) / 100;
	success -= (success * DRUNK(me)) / 100;
	CDB("Encumb-Intox ck: Success of "+ success);
    }

    /* Be nice and tell the player why is he fighting so lousy... */
    if (DRUNK(me) > 60 + random(20))
	ME("You feel your drunkenness is affecting your abilities poorly.");
    else if (me->query_encumberance_weight() > 60 + random(20))
	ME("You are so weighed down that your attack is not as "+
	  "effective as it might be.");

    weps = knife->short() +" and "+ sword->short();

    /* Complete miss */
    if (success <= 0)
    {
	ME("You slash at "+ QTNAME(enemy) +" with your "+ weps +
	    ", but "+ HE(enemy) +" dodges out of the way.");
	TW(QCTNAME(me) +" slashes at "+ QTNAME(enemy) +" with "+ HIS(TP) +
	    " "+ weps +", but "+ QTNAME(enemy) +" dodges out of the way.");
	YOU(QCTNAME(me) + " slashes at you with "+ HIS(TP) +" "+ weps +
	    ", but you dodge out of the way.");
	return;
    }

    /* Enemy parried the attack. Needs to be holding a weapon, have parry skill,
     * and be concentrating his attack on this player. The better his health,
     * calculated with php() = %hp, the better he will succeed.
     */
    tmp = min((enemy->query_hp() * 100) / enemy->query_max_hp(), 100);
    tmp = enemy->query_skill(SS_PARRY) * php(enemy) / 100;
    wep = one_of_list(enemy->query_weapon(-1));

    if (success < random(tmp) && objectp(wep) &&
	(enemy->query_attack() == TP))
    {
	CDB("Enemy parries");
	ME("You slash at "+ QTNAME(enemy) +" with your "+ weps +", but "+
	    HE(enemy) +" parries them aside with "+
	    HIS(enemy) +" "+ QSHORT(wep) +".");
	TW(QCTNAME(me) +" slashes at "+ QTNAME(enemy) +" with "+ HIS(TP) +
	    " "+ weps +", but "+ QTNAME(enemy) +" parries them aside with "+
	    HIS(enemy) +" "+ QSHORT(wep) +".");
	YOU(QCTNAME(me) +" slashes at you with "+ HIS(TP) +" "+ weps +
	    ", but you parry them aside with your "+ QSHORT(wep) +".");
	return;
    }

    skill = (((SLASH(me) + SWORD(me) + KNIFE(me)) * 3) + (DEX(me) * 2)) / 11;
    wcpen = knife->query_pen() + sword->query_pen();
    pen = F_PENMOD(wcpen, skill);

    CDB("Pen of "+wcpen);
    CDB("Skill of "+skill);
    CDB("F_PENMOD of "+pen);
#ifdef SKILLS_AFFECTED_BY_FLAME
    pen -= FLAME_DIFF(pen, PSTATE);
    CDB("Modified Pen of "+ pen);
#endif

    hitres = enemy->hit_me(pen, W_SLASH, me, -1);
    /* Combat system is buggered and returns 0 for hitres sometimes. */
    hitloc = (strlen(hitres[1]) ? hitres[1] : "body");
    pdam   = hitres[0];
    CDB("Slash pen:"+pen+" hp:"+hitres[3]+" %dam:"+pdam);

    if (!enemy->query_hp() && enemy->query_humanoid())
    {
	ME("You slash your "+ knife->short() +" across "+ QTPNAME(enemy) +
	    " throat.\n"+ CAP(enemy->query_pronoun()) +
	    " falls to the ground gurgling blood.");
	TW(QCTNAME(me) +" slashes "+ HIS(TP) +" "+ knife->short() +
	    " across "+ QTPNAME(enemy) +" throat.\n"+
	    CAP(enemy->query_pronoun()) +" falls to ground gurgling blood.");
	YOU(QCTNAME(me) +" slashes "+ HIS(TP) +" "+ knife->short() +
	    " across your throat.");

	me->adjust_union_virtue(US_GRACE, 20);
	enemy->do_die(me);
	return;
    }

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

    /* Gain some grace from a successful hit, but only a little */
    if (pdam > 1)
	me->adjust_union_virtue(US_GRACE, random(pdam / 10));

    string kn = knife->short();
    string sw = sword->short();

    switch(pdam + (pdam > 0 ? random(5) : 0) )
    {
    case -9..0:
	ME("You try to slash at "+ QTNAME(enemy) +" with your "+ weps +
	    ", but you miss completely.");
	TW(QCTNAME(me) +" tries to slash at "+ QTNAME(enemy) +" with "+
	    HIS(TP) +" "+ weps +", but misses completely.");
	YOU(QCTNAME(me) +" tries to slash at you with "+ HIS(TP) +" "+
	    weps +", but misses you completely.");
	break;
    case 1..3:
	ME("Guarding with your "+ sw +", you lightly nick "+ QTPNAME(enemy) +
	    " "+ hitloc +" with your "+ kn +".");
	TW("Guarding with "+ HIS(TP) +" "+ sw +", "+ QTNAME(me) +
	    " lightly nicks "+ QTPNAME(enemy) +" "+ hitloc +" with "+
	    HIS(TP) +" "+ kn +".");
	YOU("Guarding with "+ HIS(TP) +" "+ sw +", "+ QTNAME(me) +
	    " lightly nicks your "+ hitloc +" with "+ HIS(TP) +
	    " "+ kn +".");
	break;
    case 4..6:
	ME("You swing your "+ sw +" up to block, and slash your "+
	    kn +" lightly along "+ QTPNAME(enemy) +" "+ hitloc +".");
	TW(QCTNAME(me) +" swings "+ HIS(TP) +" "+ sw +" up to block, "+
	    "and slashes "+ HIS(TP) +" "+ kn +" lightly along "+
	    QTPNAME(enemy) +" "+ hitloc +".");
	YOU(QCTNAME(me) +" swings "+ HIS(TP) +" "+ sw +" up to block, "+
	    "and slashes "+ HIS(TP) +" "+ kn +" lightly along your "+
	    hitloc +".");
	break;
    case 7..10:
	ME("You bring your "+ kn +" in low, slashing a shallow "+
	    "wound across "+ QTPNAME(enemy) +" "+ hitloc +" while guarding "+
	    "with your "+ sw +".");
	TW(QCTNAME(me) +" brings "+ HIS(TP) +" "+ kn +" in low, slashing "+
	    "a shallow wound across "+ QTPNAME(enemy) +" "+ hitloc +
	    " while guarding with "+ HIS(TP) +" "+ sw +".");
	YOU(QCTNAME(me) +" brings "+ HIS(TP) +" "+ kn +" in low, slashing "+
	    "a shallow wound across your "+ hitloc +" while guarding with "+
	    HIS(TP) +" "+ sw +".");
	break;
    case 11..15:
	ME("You manage to cut into the "+ hitloc +" of "+ QTNAME(enemy) +
	    " with your "+ sw +" while feinting with your "+ kn +".");
	TW(QCTNAME(me) +" cuts into "+ QTPNAME(enemy) +" "+ hitloc +
	    " with "+ HIS(TP) + " "+ sw +" while feinting with "+ HIS(TP) +
	    " "+ kn +".");
	YOU(QCTNAME(me) +" cuts into your "+ hitloc +" with "+ HIS(TP) +
	    " "+ sw +" while feinting with "+ HIS(TP) +" "+ kn +".");
	break;
    case 16..18:
	ME("Swinging your "+ sw +" in a wide arc, you slip your "+ kn +
	    " past "+ QTPNAME(enemy) +" defences and cut into "+ HIS(enemy) +
	    " "+ hitloc +".");
	TW("Swinging "+ HIS(TP) +" "+ sw +" in a wide arc, "+ QTNAME(me) +
	    " slips "+ HIS(TP) +" "+ kn +" past "+ QTPNAME(enemy) +" defences "+
	    "and cuts into "+ HIS(enemy) +" "+ hitloc +".");
	YOU("Swinging "+ HIS(TP) +" "+ sw +" in a wide arc, "+ QTNAME(me) +
	    " slips "+ HIS(TP) +" "+ kn +" past your defences and "+
	    "cuts into your "+ hitloc +".");
	break;
    case 19..25:
	ME("You open a large wound in "+ QTPNAME(enemy) +" "+ hitloc +
	    " with your "+ sw +", as well as cutting "+ HIM(enemy) +
	    " with your "+ kn +".");
	TW(QCTNAME(me) +" opens a large wound in "+ QTPNAME(enemy) +" "+
	    hitloc +" with "+ HIS(TP) +" "+ sw +", as well as cutting "+
	    HIM(enemy) + " with "+ HIS(TP) +" "+ kn +".");
	YOU(QCTNAME(me) +" opens a large wound in your "+ hitloc +
	    " with "+ HIS(TP) +" "+ sw +", as well as cutting you with "+
	    HIS(TP) +" "+ kn +".");
	break;
    case 26..35:
	ME("You bring your "+ sw +" down hard onto "+ QTPNAME(enemy) +" "+
	    hitloc +", and stab into "+ HIM(enemy) +" with your "+ kn +".");
	TW(QCTNAME(me) +" brings "+ HIS(TP) +" "+ sw +" down hard onto "+
	    QTPNAME(enemy) +" "+ hitloc +", and stabs into "+ HIM(enemy) +
	    " with "+ HIS(TP) +" "+ kn +".");
	YOU(QCTNAME(me) +" brings "+ HIS(TP) +" "+ sw +" down hard onto "+
	    "your "+ hitloc +", and stabs into you with "+ HIS(TP) +" "+
	    kn +".");
	break;
    case 36..45:
	ME("With one sweeping motion, you slash deeply into "+
	    QTPNAME(enemy) +" "+ hitloc +" with both your "+weps+".");
	YOU("With one sweeping motion, "+QTNAME(me)+" slashes deeply "+
	    "into your "+ hitloc +" with both "+ HIS(TP) +" "+weps+".");
	break;
	TW("With one sweeping motion, "+QTNAME(me)+" slashes deeply into "+
	    QTPNAME(enemy) +" "+ hitloc +" with both "+ HIS(TP) +" "+weps+".");
	break;
    case 46..60:
	ME("You bury your "+ kn +" deep into "+ QTPNAME(enemy) +" " + hitloc +
	    ", while getting a brilliant slash in with your "+ sw +".");
	TW(QCTNAME(me) +" buries "+ HIS(TP) +" "+ kn +" deep into "+
	    QTPNAME(enemy) +" "+ hitloc +", while getting a brilliant slash "+
	    "in with "+ HIS(TP) +" "+ sw +".");
	YOU(QCTNAME(me) +" buries "+ HIS(TP) +" "+ kn +" deep into your "+
	    hitloc + ", while getting a brilliant slash in with "+ HIS(TP) +
	    " "+ sw +".");
	break;
    default:
	ME("You nearly sever "+ QTPNAME(enemy) +" "+ hitloc +" with your "+
	    sw + " at the same time as you drive your "+ kn +" deep into "+
	    HIM(enemy) +".");
	TW(QCTNAME(me) +" nearly severs "+ QTPNAME(enemy) +" "+ hitloc +
	    " with "+ HIS(TP) +" "+ sw +" at the same time as "+
	    HE(me) +" drives "+ HIS(TP) +" "+ kn +" deep into "+
	    QTNAME(enemy) +".");
	YOU(QCTNAME(me) +" nearly severs your "+ hitloc +" with "+
	    HIS(TP) +" "+ sw +" at the same time as "+ HE(me) +
	    " drives "+ HIS(TP) +" "+ kn +" deep into you.");
	break;
    }

    if (!enemy->query_hp())
	enemy->do_die(me);
}
