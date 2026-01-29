/*
 * /d/Gondor/common/guild/brawl.c
 *
 * This is the coded that is needed to brawl an opponent. A brawl can either
 * disarm him or blind him for some time. Currently, you are not certain what
 * will happen if you brawl someone... There is a random chance that you do
 * either one of them. This code is prepared for an easy split though.
 *
 ****************************************************************************
 *
 * Brawl was originally coded by Elessar Telcontar, 1992.
 *
 * Revision history:
 * November 17, 1993, Mercade: Added error-checking code.
 * Summer 1994, Elessar: A few patches.
 * September 1994, Elessar: Bug in blinding happened because of a
 *                          call_out to remove_object() in the
 *                          blind_ob.
 * 16-Sep-1994, Elessar: Adding of stun-effect for the North Rangers.
 * 17-Sep-1994. Elessar: Adding of knee-effect for the Ithilien Rangers.
 * 31-Mar-1997, Olorin:  Fixed a bug in definition BRAWL_SKILL which
 *                       gave every ranger at least a skill level of
 *                       10 in brawl skill.  
 * 19-Aug-1997, Olorin:  Started general revision, trying to fix a
 *                       problem with initiating combat. 
 *                       Most functions rewritten or modified.
 *                       Introduced fixnorm, check_tohit, call to
 *                       cb_tohit
 * 1999, Elessar:        More balancing checks added, plus beefed up
 *                       the Ithilien alternative since it was the weakest.
 * Dec. 2000, Gwyneth:   Some modifications to make the code more
 *                       efficient, and removed the penalty for brawling
 *                       when brawl isn't reset.
 */
#undef DEBUG
#define DEBUG 1
#if DEBUG>1
#define DEBUG_MSG(x) find_player("gwyneth")->catch_tell("DEBUG: " + x + "\n");
#else
#define DEBUG_MSG(x)
#endif
#ifdef DEBUG
static int *Brawl_Stats = allocate(23);
static int *Fail_Stats  = allocate(23);
#endif

/* 
 * set this prop in an NPC to prevent it from being brawled at all 
 */
#define RANGER_M_NOT_BRAWL       "_ranger_m_not_brawl"
#define RANGER_I_NOT_BRAWL       "_ranger_i_not_brawl"
/* 
 * set this prop in an NPC if you want to prevent blinding: 
 */
#define RANGER_M_NOT_BLIND       "_ranger_m_not_blind"
#define RANGER_I_NOT_BLIND       "_ranger_i_not_blind"
/* 
 * set this prop to prevent disarming:
 */
#define RANGER_M_NOT_DISARM	"_ranger_m_not_disarm"
#define RANGER_I_NOT_DISARM	"_ranger_i_not_disarm"
/* 
 * set this prop to prevent tripping:
 */
#define RANGER_M_NOT_TRIP	"_ranger_m_not_trip"
#define RANGER_I_NOT_TRIP	"_ranger_i_not_trip"
/*
 * This prop is the same used by the Krynn thieves soul
 * and perhaps we'll see it in the mudlib some time
 * We use it here to test if an npc is supposed to attack
 * thieves who steal, if so we let them attack the disarming
 * ranger as well.
 */
#ifndef LIVE_M_ATTACK_THIEF
#define LIVE_M_ATTACK_THIEF   "_live_m_attack_thief"
#endif
/* 
 * The level of preparation of a brawl this player is in.
 * 0	     = no preparation, he can brawl again
 * PREPARE_BRAWL = he is preparing a brawl.
 * RECOVER_BRAWL = he is recovering from the brawl
 * MOVED_WHILE_BRAWLING = he moved out of the room while preparing a brawl.
 */
#define RANGER_I_PREPARE_BRAWL   "_ranger_i_prepare_brawl"
/* The location where preparation was started */
#define RANGER_O_START_BRAWL     "_ranger_o_start_brawl"
/* The type of brawl a player wants to perform */
#define RANGER_I_BRAWL_TYPE      "_ranger_i_brawl_type"
/* The exact time() the brawl was started. */
#define RANGER_I_TIME_BRAWL      "_ranger_i_time_brawl"
/* The time the player has to recover to brawl again. */
#define RANGER_I_TIME_RECOVER    "_ranger_i_time_recover"
/* 
 * How good someone is in recognizing when someone prepares to
 * brawl. This value is compared to brawl and sneak skills:
 */
#define RANGER_I_RECOGNIZE_BRAWL "_ranger_i_recognizing_brawl"
/* Some props for keeping track of alarm-ids */
#define RANGER_DB_AID    "_ranger_do_brawl_alarm_id"
#define RANGER_CBA_AID   "_ranger_can_brawl_again_alarm_id"

#define PREPARE_BRAWL        1
#define RECOVER_BRAWL        2
#define MOVED_WHILE_BRAWLING 3

#define BRAWL_UNKNOWN 0
#define BRAWL_BLIND   1
#define BRAWL_DISARM  2
#define BRAWL_TRIP    3
#define BRAWL_KNEE    4

#define MAX_TIME_TO_RECOVER       35
/* directly following from the function */
#define MIN_TIME_TO_RECOVER       15
#define MAX_TIME_BRAWL            22
#define MIN_TIME_BRAWL             7
#define TIME_BEFORE_ACTUAL_BRAWL   6
/* read BUG in 'man time' */
#define TIME_TO_PROTECT_ERRORS    20
#define BRAWL_CHOOSE_MIN          90
#define BRAWL_CHOOSE_CHANCE       66
#define BRAWL_BASE_TRIP_RATE      20

/*
 * Max rate increase for BRAWL_I_RECOGNIZE_BRAWL 
 * (at awareness of  100): 
 */
#define BRAWL_RECOGNIZE_RATE       3
#define BRAWL_PUNISH_MOD          90
#define BRAWL_PUNISHED_MIN        10
#define BRAWL_PUNISHED(o) \
    (((o)->query_skill(SS_PUNISHMENT)==NOSKILLS) \
    || ((o)->query_skill(SS_PUNISHMENT)==NOABILITIES))
  // This has been replaced by the function query_brawl_skill():
  /* #define BRAWL_SKILL(o) \
    (MAX(10, (o->query_skill(SS_BRAWLING) - \
    (BRAWL_PUNISH_MOD * BRAWL_PUNISHED(o)))))
    */
/*
 * Time to brawl again after a succesfull brawl.
 */
#define TIME_TO_BRAWL_AGAIN(o) (MIN(MAX((MAX_TIME_TO_RECOVER - \
    ((query_brawl_skill(o)) / 5)), \
    MIN_TIME_TO_RECOVER), MAX_TIME_TO_RECOVER))
/*
 * Time to recover is someone prevented your brawl.
 */
#define TIME_AFTER_BRAWL_FUMBLE(o) \
    (MAX((TIME_TO_BRAWL_AGAIN(o) / 2), MIN_TIME_TO_RECOVER))
#define BRAWL_BUG_LOG (LOG_DIR + "brawl")
#define BLIND_OBJECT  (RANGER_DIR + "obj/blind_ob")
#define DISARM_OBJECT (RANGER_DIR + "obj/disarm_ob")

/* Prototypes */
private nomask int     fixnorm(int offence, int defence);
public void    do_brawl(object brawler, object victim, int seen = 0);
       void    can_brawl_again(object brawler);

/*
 * Function name: query_brawl_skill
 * Description:   determine the effective brawl skill, taking
 *                punishments into account.
 *                Reduces the skill by BRAWL_PUNISH_MOD, down
 *                to BRAWL_PUNISHED_MIN but no further.
 * Argument:      object o - the ranger
 * Returns:       the skill level after modifications
 */
public int
query_brawl_skill(object o = TP)
{
    int     brawl = o->query_skill(SS_BRAWLING);

    if (BRAWL_PUNISHED(o) &&  (brawl > BRAWL_PUNISHED_MIN))
    {
        brawl -= BRAWL_PUNISH_MOD;
        if (brawl < BRAWL_PUNISHED_MIN)
            brawl = BRAWL_PUNISHED_MIN;
    }

    return brawl;
}

/*
 * Function name: brawl_bug
 * Description  : Log a bug with the brawl command.
 * Arguments    : brawler - the player that was brawling
 *		  str     - the fail message.
 */
static void
brawl_bug(object brawler, string str)
{
    FIX_EUID;

    write_file(BRAWL_BUG_LOG, (ctime(time()) + ", "
      + CAP(brawler->query_name()) + ": " + str));
}

/*
 * Function name: reset_brawl_properties
 * Description  : Removes all brawl-related properties from a person.
 * Arguments    : brawler - the player that is brawling
 */
void
reset_brawl_properties(object brawler, int all = 1)
{
    int al_id;
 
    brawler->remove_prop(RANGER_I_TIME_RECOVER);
    brawler->remove_prop(RANGER_I_TIME_BRAWL);
    brawler->remove_prop(RANGER_I_PREPARE_BRAWL);
    brawler->remove_prop(RANGER_O_START_BRAWL);

    if (all)
    {
	brawler->remove_prop(RANGER_I_BRAWL_TYPE);
    }

    al_id = (int)brawler->query_prop(RANGER_DB_AID);
    if (al_id)
    {
        remove_alarm(al_id);
        brawler->remove_prop(RANGER_DB_AID);
        al_id = 0;
    }

    al_id = (int)brawler->query_prop(RANGER_CBA_AID);
    if (al_id)
    {
        remove_alarm(al_id);
        brawler->remove_prop(RANGER_CBA_AID);
    }
}

void
restart_brawl_recovery(object brawler)
{
    int recover, al_id;

    al_id = (int)brawler->query_prop(RANGER_CBA_AID);
    if (al_id)
    {
        remove_alarm(al_id);
    }

    brawler->add_prop(RANGER_I_PREPARE_BRAWL, RECOVER_BRAWL);
    recover = TIME_AFTER_BRAWL_FUMBLE(brawler);
    brawler->add_prop(RANGER_I_TIME_RECOVER, recover);
    al_id = set_alarm(itof(recover), 0.0, &can_brawl_again(brawler));
    brawler->add_prop(RANGER_CBA_AID, al_id);
}

/*
 * Function name: still_has_to_recover
 * Description  : This function checks whether the player still has to
 *		  recover from a brawl. If the brawl is 'stuck' for some
 *		  reason the brawl will be reset. If the player can not
 *		  brawl again, notify_fail will set to the appropriate
 *		  message. This function may have some overhead, but that
 *		  is meant to guard against all brawl bugs. If any problem
 *		  is found, this function resets the brawl posibilities of
 *		  the player completely without trying to partially reset
 *		  them to let the player wait... If we make a mistake, he
 *		  may have the pleasure of a quick recovery.
 * Returns      : 1 - the player still has to recover
 *		  0 - the player can brawl again
 */
int
still_has_to_recover()
{
    object brawler = this_player();
    int prep  = (int)brawler->query_prop(RANGER_I_PREPARE_BRAWL);
    int rtime = (int)brawler->query_prop(RANGER_I_TIME_RECOVER);
    int start = (int)brawler->query_prop(RANGER_I_TIME_BRAWL);

    if (!prep)
    {
	reset_brawl_properties(brawler, 0);
	return 0;
    }

    if (prep == PREPARE_BRAWL)
    {
	if ((time()) > (start + TIME_BEFORE_ACTUAL_BRAWL +
            TIME_TO_PROTECT_ERRORS))
	{
	    brawl_bug(brawler, "Too long preparation: " + (time() - start)
              + ".\n");
	    reset_brawl_properties(brawler);
	    return 0;
	}

        notify_fail("You were already preparing a brawl.\n\n");
        return 1;
    }

    if (prep != RECOVER_BRAWL && 
      prep != MOVED_WHILE_BRAWLING)
    {
	brawl_bug(brawler, "Illegal preparation property: " + prep + ".\n");
	reset_brawl_properties(brawler);
	return 0;
    }

    if ((rtime < MIN_TIME_TO_RECOVER) || (rtime > MAX_TIME_TO_RECOVER))
    {
	brawl_bug(brawler, "Strange recover time: " + rtime + ".\n");
	reset_brawl_properties(brawler);
	return 0;
    }

    if (time() > (start + rtime + TIME_BEFORE_ACTUAL_BRAWL +
        TIME_TO_PROTECT_ERRORS))
    {
	brawl_bug(brawler, "Too long recovery time. Time: " + time() +
	    ", Start: " + start + ", Recover: " + rtime + ".\n");
	reset_brawl_properties(brawler);
	return 0;
    }

    notify_fail(ONE_OF_LIST( ({"You are still somewhat out of balance " +
        "from your last brawl.\n", "You do not feel ready to attempt " +
        "another brawl yet.\n"}) ));
    return 1;
}

/*
 * Function name: can_attack
 * Description  : This function determines whether a certain person can and
 *		  is allowed to attack someone else. If not, a fail message
 *		  is written to the player.
 * Arguments    : victim  - the victim of the brawl.
 * Returns      : 1 - the brawl is possible/ allowed.
 *		  0 - it is not possible to brawl.
 */
int
can_attack(object victim)
{
    string  message;
    int     roomtype;
    mixed   dp;
    object  brawler = this_player();

    if (!objectp(brawler))
    {
        return 0;
    }

    roomtype = environment(brawler)->query_prop(ROOM_I_TYPE);
    if ((roomtype == ROOM_UNDER_WATER) || 
      (roomtype == ROOM_IN_WATER))
    {
        write("Brawling is quite impossible in this aquatic environment!\n");
        return 0;
    }

    if (victim->id("ranger"))
        log_file("brawl", brawler->query_name() + " tried to "
        + "brawl a Ranger NPC, in " + file_name(environment(victim))
        + ", " + ctime(time()) + ".\n");

    if (victim->id("_gondor_guard"))
        log_file("brawl", brawler->query_name() + " tried to "
        + "brawl a Gondor NPC, in " + file_name(environment(victim))
        + ", " + ctime(time()) + ".\n");

    if (!objectp(brawler->query_attack()) && 
      (message = (environment(brawler)->query_prop(ROOM_M_NO_ATTACK))))
    {
	if (stringp(message))
        {
	    brawler->catch_msg(message);
        }
	else
        {
	    write("The peaceful surroundings calm your aggressive mind.\n");
        }

        return 0;
    }

    if (message = victim->query_prop(OBJ_M_NO_ATTACK))
    {
        if (stringp(message))
	{
            brawler->catch_msg(message);
	}
        else
	{
            write("You feel a strong force protecting that being.\n");
	}

        return 0;
    }

    if ((!F_DARE_ATTACK(brawler, victim)) &&
        (member_array(victim, (object *)brawler->query_enemy(-1)) == -1))
    {
        write("Umm... no, You do not have enough self-discipline to dare!\n");
        return 0;
    }

    if (brawler->query_prop(LIVE_I_STUNNED))
    {
        write("You are stunned and cannot brawl right now!\n");
        brawl_bug(brawler, "Tried to brawl while stunned. Stun level: "
          + brawler->query_prop(LIVE_I_STUNNED) + ".\n");
        return 0;
    }

    if (brawler->query_prop(LIVE_I_ATTACK_DELAY) > TIME_TO_PROTECT_ERRORS)
    {
        /* If delay is long, don't allow brawl.
         * If it is a delay shorter than TIME_TO_PROTECT_ERRORS,
         * allow the brawl but delay is added to preparation time.
         */
        write("You can't seem to compose yourself enough to brawl " +
	    "right now.\n");
        brawl_bug(brawler, "Tried to brawl while delayed. Delay level: " +
            brawler->query_prop(LIVE_I_ATTACK_DELAY) + ".\n");
        return 0;
    }        

    if (stringp(dp = victim->query_prop(RANGER_M_NOT_BRAWL)))
    {
        brawler->catch_msg(dp);
        brawl_bug(brawler, MASTER_OB(victim) + " has M_NOT_BRAWL set to: "
          + dp + "\n");
        return 0;
    }
    else if (dp ||
      (victim->query_prop(RANGER_I_NOT_BRAWL)))
    {
        write("Your brawling seems pointless against this opponent.\n");
        brawl_bug(brawler, MASTER_OB(victim) + " has M_NOT_BRAWL set.\n");
        return 0;
    }

    if (brawler->query_met(victim) &&
      (member_array(victim, brawler->query_enemy(-1)) == -1) &&
      (brawler->query_prop(LIVE_O_LAST_KILL) != victim))
    {
        write("Brawl " + victim->query_the_name(brawler) + "? It just " +
	    "might make " + victim->query_objective() + " upset enough " +
	    "that there will be a fight! Please confirm by trying again!\n");
        brawler->add_prop(LIVE_O_LAST_KILL, victim);
        return 0;
    }

    return 1;
}

/*
 * Function name: find_victim_to_brawl
 * Description  : This function is called for general access. If first
 *		  test whether the player is able to brawl and if so, it
 *		  searches for an opponent. If this function fails,
 *		  notify_fail will be set.
 * Arguments    : brawler - the player that wants to brawl
 *		  str     - the command line string
 * Returns      : object  - the victim to brawl
 *		  0       - no victim could be found
 */
object
find_victim_to_brawl(string str)
{
    object  victim,
           *oblist,
	   brawler = this_player();

    if (still_has_to_recover())
    {
	/* Notify_fail will be set in the function. */
	return 0;
    }

    if (brawler->query_ghost())
    {
	notify_fail("A ghost needs a body before it can brawl.\n");
	return 0;
    }

    if (!strlen(str))
    {
        if (!objectp(victim = (object)brawler->query_attack()))
        {
            notify_fail(capitalize(query_verb()) + " who?\n");
            return 0;
        }
    }
    else
    {
	oblist = parse_this(str, "[the] %l");
	if (sizeof(oblist) >= 2)
	{
            notify_fail("Be specific. You can't brawl " +
                COMPOSITE_LIVE(oblist) + " at the same time.\n");
            return 0;
	}
	else if (sizeof(oblist))
	{
	    victim = oblist[0];
	    if ((brawler->query_attack() != victim ||
		 victim->query_attack() != brawler) &&
		(!CAN_SEE_IN_ROOM(brawler) || !CAN_SEE(brawler, victim)))
	    {
                notify_fail("You cannot see or find anyone like that to " +
                    "brawl.\n");
                return 0;
	    }
	}
	else
	{
            notify_fail(capitalize(query_verb()) + " who?\n");
            return 0;
	}
    }

    return victim;
}

/*
 * Function name: can_hide_brawl
 * Description  : This function will determine whether a player is able to
 *		  discover that someone is preparing a brawl against him.
 *		  He will learn every time he fails to notices that a
 *                brawl is prepared against him.
 *                This check is done at preparation time and
 *                determines the chance for avoiding the brawl as well
 *                as the chance of brawl to initiate combat.
 * Arguments    : victim  - the player that is the intended victim
 * Returns      : 1 - it is possible to hide the action from him.
 *		  0 - it is not possible to hide it from him.
 */
int
can_hide_brawl(object victim)
{
    object brawler = this_player();
    int recognize = victim->query_prop(RANGER_I_RECOGNIZE_BRAWL),
	awareness = victim->query_skill(SS_AWARENESS);

    if (!CAN_SEE_IN_ROOM(victim) || 
      !CAN_SEE(victim, brawler)) 
    {
	return 1;
    }

    /* victim learns only if the brawl is successfully hidden: */
    if ((recognize + awareness) < (brawler->query_prop(OBJ_I_HIDE) + 
      brawler->query_skill(SS_SNEAK) + query_brawl_skill(brawler)))
    {
	if (random(recognize) >= awareness)
	{
	    return 1;
	}

	victim->add_prop(RANGER_I_RECOGNIZE_BRAWL,
	    recognize + (awareness * BRAWL_RECOGNIZE_RATE / 100));

	return 1;
    }
    
    return 0;
}

/*
 * Function name: can_avoid_brawl
 * Description  : Compute whether the victim is able to avoid being brawled
 *		  by the brawler. This function comes in the place of the
 *		  former try_react_brawl and try_avoid_brawl for it is my
 *		  opinion that you shall always try to avoid a brawl if you
 *		  see that someone tries to brawl them. Let us hope that this
 *		  function always returns 0 *grin*
 * Arguments    : victim  - the intended victim
 * Returns      : 1 - the brawl can be avoided
 *		  0 - the brawl cannot be avoided.
 */
private int
can_avoid_brawl(object victim)
{
    object brawler = this_player();

    if (!CAN_SEE(victim, brawler)) 
    {
        return 0;
    }
    else if (!CAN_SEE_IN_ROOM(victim) &&
      (random(100) > victim->query_skill(SS_BLIND_COMBAT)))
    {
        return 0;
    }
    else if (victim->resolve_task(TASK_DIFFICULT, 
      ({ SKILL_AVG, TS_DEX, TS_INT, SKILL_END, 
      SKILL_AVG, SS_AWARENESS, SS_DEFENCE, SKILL_END }),
      brawler, ({ TS_INT, &(TO)->query_brawl_skill(brawler) })) > 0)
    {
	return 1;
    }

    return 0;
}

/*
 * Function name: check_seen_brawl
 * Description:   check if the victim notices who has brawled him
 *                this is a check _after_ the brawl, used to determine
 *                if the brawl initiates combat
 */
private int
check_seen_brawl(object brawler, object victim)
{
    return (CAN_SEE_IN_ROOM(victim) && 
      CAN_SEE(victim, brawler) &&
      (victim->resolve_task(TASK_SIMPLE, ({ TS_INT, SS_AWARENESS }), 
        brawler, ({ &brawler->query_prop(OBJ_I_HIDE), SS_SNEAK })) > 0)); 
}

/*
 * Function name: check_wielding
 * Description  : Tests if pl is wielding a weapon.
 * Arguments    : pl - the living we want to test.
 * Returns      : 0 - no weapon wielded.
 *                1 - some kind of weapon wielded.
 *                2 - successfully disarmed a two-handed weapon
 */
private int
check_wielding(object pl)
{
    object  ob;

    if (sizeof(pl->query_weapon(-1)))
    {
        return 1;
    }
    else if (objectp(ob = present("Ranger_Disarm_Object", pl)) &&
      ob->query_two_handed()) 
    {
	return 2;
    }

    return 0;
}

/*
 * Function name: size_diff
 * Description  : Tests the difference in volume and weight
 * Arguments    : brawler - the player who tries to brawl
 *                victim - the living being brawled
 * Returns      : The ratio between victim's and brawler's volume and
 *                weight 
 */
int
size_diff(object brawler, object victim)
{
    return ((victim->query_prop(OBJ_I_VOLUME) /
	     brawler->query_prop(OBJ_I_VOLUME)) +
	    (victim->query_prop(OBJ_I_WEIGHT) /
	     brawler->query_prop(OBJ_I_WEIGHT))) / 2;
}

/*
 * Function name: blind_or_disarm
 * Description:   Chance for disarm vs blind is 50 :  50,
 *                if no weapon is wielded        0 : 100,
 *                if victim is blinded up to    90 :  10
 *                depending on skill.
 * Arguments:     brawler,
 *                victim,
 *                int brawl    - brawl skill
 *                int wielding - true if the victim is wielding a weapon
 */
private void
blind_or_disarm(object brawler, object victim, int brawl, int wielding)
{
    int     rnd = random(100);

    if (!wielding)
	brawler->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_BLIND);
    else if ((rnd < 50) ||
	((brawl > 50) &&
	 objectp(present("Ranger_Blind_Object", victim)) &&
	 (rnd < (10 + brawl * 80 / 100))))
    {
#ifdef DEBUG
	Brawl_Stats[22]++;
	Brawl_Stats[ brawl / 10 ]++;
#endif
	brawler->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_DISARM);
    }
    else
    {
#ifdef DEBUG
	Brawl_Stats[22]++;
	Brawl_Stats[ brawl/10 + 11]++;
#endif
	brawler->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_BLIND);
    }
    DEBUG_MSG(brawler->query_name() + " BD: " + brawl + ", " + 
	wielding + ", " + ((brawler->query_prop(RANGER_I_BRAWL_TYPE) == 
	BRAWL_BLIND) ? "BLIND" : "DISARM"));
}

#ifdef DEBUG
public string
query_brawl_stats(int fail = 0) 
{
    int     i,
	   *stats;
    string  msg;

    if (fail)
	stats = Fail_Stats;
    else
	stats = Brawl_Stats;
    msg = "Total number of entries: " + stats[22];
    if (fail)
	msg += "\n\tSkill\tSuccess\tFailure\n";
    else
	msg += "\n\tSkill\tDisarm\tBlind\n";
    for (i = 0; i <= 10; i++)
	msg += "\t" + i * 10 + "\t" + stats[i] + "\t" + stats[11 + i] + "\n"; 
    return msg; 
}
#endif

/*
 * Function name: decide_on_brawl_type
 * Description  : As long as the brawl command is still use for both blind
 *		  and disarm, this function is used to determine whether
 *		  the player disarms or blinds, trips or knees. If the 
 *                opponent does not
 *		  have a weapon, you shall always try to blind him, if not
 *		  it uses random to determine the type.
 *		  If you are going to split the commands, the only change
 *		  you will have to make is to remove the call to this
 *		  function in the function do_brawl.
 * Arguments    : brawler - the player that wants to brawl
 *		  victim  - the intended victim
 */
private void
decide_on_brawl_type(object brawler, object victim)
{
    int     rnd = random(100),
	    brawl = query_brawl_skill(brawler),
	    wielding,
	    sd,
	    stat_diff;

    wielding = check_wielding(victim);
    // if a two handed weapon was disarmed, try disarm again:
    if ((rnd < (brawl / 2)) && (wielding == 2))
    {
	brawler->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_DISARM);
	return;
    }

    switch (brawler->query_company())
    {
    case "the North":
	// Compare strength of brawler with strength of victim:
	stat_diff = fixnorm(brawler->query_skill(SS_STR),
			    victim->query_skill(SS_STR));
	if (((sd = size_diff(brawler, victim)) < 10) && 
	    (rnd < (BRAWL_BASE_TRIP_RATE - stat_diff - sd)))
            brawler->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_TRIP);
	else
	    blind_or_disarm(brawler, victim, brawl, wielding);
	break;
    case "Ithilien":
	if ((brawler->query_attack() == victim) && 
	    (rnd >= (50 + victim->query_hp() * 50 / victim->query_max_hp()))
          && (size_diff(brawler, victim) < 10))
            brawler->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_KNEE);
	else
	    blind_or_disarm(brawler, victim, brawl, wielding);
	break;
    case "Gondor":
    default:
	blind_or_disarm(brawler, victim, brawl, wielding);
	break;
    }
}

/*
 * Function name: can_brawl_again
 * Description  : Call this function when the brawler recovered from his
 *		last brawl and is able to brawl again.
 * Arguments    : brawler - the player that can brawl again.
 */
void
can_brawl_again(object brawler)
{
    brawler->catch_tell(ONE_OF_LIST(({"You recover your balance from your "
      + "last brawl.", "You once again feel ready to try a brawl.",
        "You feel you might be able to attempt another brawl now.",
    })) + "\n");
    reset_brawl_properties(brawler);
}

/*
 * Function name: access_brawl
 * Description  : The actual brawl command. 
 *                This function is called when the player types to
 *                brawl someone. 
 * Arguments    : str - command line argument
 * Returns      : 1/0 - success/failure of the command
 */
private int
access_brawl(string str)
{
    object  tp = this_player();
    object  victim;
    int     recover,
            al_id,
	    seen = 0;

    if (!objectp(victim = find_victim_to_brawl(str)))
    {
	return 0;
    }

    if (!can_attack(victim))
    {
	return 1;
    }

    tp->add_prop(RANGER_I_PREPARE_BRAWL, PREPARE_BRAWL);
    tp->add_prop(RANGER_I_TIME_BRAWL, time());
    tp->add_prop(RANGER_O_START_BRAWL, environment(tp));

    if (can_hide_brawl(victim))
    {
	write("You prepare to brawl " + victim->query_the_name(tp) + ".\n");
    }
    else
    {
	if (can_avoid_brawl(victim))
	{
            write("You prepare to brawl " + victim->query_the_name(tp) +
		", though " + victim->query_pronoun() + " discovers " +
		"what you are planning to do and deftly avoids your " +
		"brawling maneuver! You have no idea what went wrong.\n");
	    victim->catch_tell("With a shock, you discover that " +
		tp->query_the_name(victim) + " is preparing to brawl " +
		"you. Skillfully, you avoid " + tp->query_possessive() +
		" attempt, leaving " + tp->query_objective() +
		" dazed and confused.\n");

	    tp->add_prop(RANGER_I_PREPARE_BRAWL, RECOVER_BRAWL);
	    recover = TIME_AFTER_BRAWL_FUMBLE(tp);
	    tp->add_prop(RANGER_I_TIME_RECOVER, recover);
            al_id = set_alarm(itof(recover), 0.0, &can_brawl_again(tp));
	    tp->add_prop(RANGER_CBA_AID, al_id);
	    return 1;
	}
	else
	{
	    write("You prepare to brawl " + victim->query_the_name(tp) +
		", though " + victim->query_pronoun() + " discovers " +
		"what you are planning to do and tries to avoid your " +
		"brawling maneuver.\n");
	    victim->catch_tell("With a shock, you discover that " +
		tp->query_the_name(victim) + " is preparing to " +
		"brawl you. You try to avoid " + tp->query_possessive() +
		" attempt.\n");
	    seen = 1;
	}
	
    }

    /* If player is suffering a short attack delay,
     * we allow brawl to be initiated with the delay added
     * to the total prep time.
     */
    al_id = set_alarm(itof(TIME_BEFORE_ACTUAL_BRAWL 
          + tp->query_prop(LIVE_I_ATTACK_DELAY)), 0.0, 
          &do_brawl(tp, victim, seen));
    tp->add_prop(RANGER_DB_AID, al_id);
    return 1;
}

/*
 * Function name: do_blind
 * Description  : This function is used to do the actual blinding. This
 *		  means to tell the people in the room and the victim and
 *		  to clone the blind-object
 * Arguments    : victim  - the victim of the brawl
 *                seen    - victim already recognized the brawler at
 *                          prep time
 */
private void
do_blind(object victim, int seen = 0)
{
    object  blind_object, brawler = this_player();
    int     already_blinded = 0,
            time_brawl,
            busy_hands;
    mixed   blind_prop;
    string  how;

    if (stringp(blind_prop = victim->query_prop(RANGER_M_NOT_BLIND)))
    {
        brawler->catch_msg(blind_prop);
        return;
    }
    else if (blind_prop ||
      victim->query_prop(RANGER_I_NOT_BLIND))
    {
	write("It seems impossible to blind " +
		victim->query_the_name(brawler) + ".\n");
	return;
    }

    if (objectp(blind_object = present("Ranger_Blind_Object",victim)))
    {
        already_blinded = 1;
    }
    else
    {
	FIX_EUID;  
        blind_object = clone_object(BLIND_OBJECT);
    }
  
    if (brawler->query_weapon(W_BOTH))
    {
	busy_hands = 1;
    }
    else if (brawler->query_weapon(W_RIGHT) && 
      brawler->query_weapon(W_LEFT)) 
    {
	busy_hands = 1;
    }

    if (busy_hands)
    {
	how = "kick";
    }
    else
    {
        how = "throw";
    }

    if (seen || 
      check_seen_brawl(brawler, victim))
    {
        blind_object->set_brawler(brawler);
        victim->catch_tell(brawler->query_The_name(victim) + " suddenly " 
	    + how + "s a shower of sand into your eyes! You are blinded!\n");
    }
    else
    {
	victim->catch_tell("You scream loudly as a shower of sand hits " +
	    "your eyes! You are blinded!\n");
    }
  
    brawler->reveal_me(1);

    if (already_blinded)
    {
        write("You successfully " + how + " some more " +
	    "sand in the eyes of " + victim->query_the_name(brawler) +
	    ". " + capitalize(victim->query_pronoun()) + " is still " +
	    "blinded!\n");
        tell_room(environment(brawler), QCTNAME(brawler) + " manages " +
	    "to " + how + " some more sand into the already blinded " +
	    "eyes of " + QTNAME(victim) + "!\n", ({ brawler, victim }), );
    }
    else
    {
	write("You successfully " + how + " a shower " + "of sand into " +
	    "the eyes of " + victim->query_the_name(brawler) + ". " + 
	    capitalize(victim->query_pronoun(brawler)) + " looks blinded!\n");

        if (busy_hands)
	{
            how = " kicks at the dusty ground,";
	}
        else
	{
            how = " jerks " + brawler->query_possessive() + " hand up,";
	}

        tell_room(environment(brawler), QCTNAME(brawler) + " suddenly" + 
            how + " sending a shower of sand into the eyes of " + 
	    QTNAME(victim) + "!\n", ({ brawler, victim }), );
    }
  
    time_brawl = query_brawl_skill(brawler) / (2 + already_blinded * 2);

    if (time_brawl > MAX_TIME_BRAWL)
    {
        time_brawl = MAX_TIME_BRAWL;
    }

    if (time_brawl < MIN_TIME_BRAWL)
    {
        time_brawl = MIN_TIME_BRAWL;
    }

    blind_object->set_time(time_brawl);

    if (!already_blinded)
    {
        blind_object->move(victim, 1);
    }
}

/*
 * Function name: do_disarm
 * Description  : This function is used to do the actual disarming. This
 *		  means to tell the people in the room and the victim and
 *		  to clone the disarm-object
 * Arguments    : victim  - the victim of the brawl
 *                seen    - victim already recognized the brawler at
 *                          prep time
 */
private void
do_disarm(object victim, int seen = 0)
{
    object  disarm_object, brawler = this_player();
    int     time_brawl,
            attack_brawler,
            was_disarmed;
    mixed   dp;
  
    if (stringp(dp = victim->query_prop(RANGER_M_NOT_DISARM)))
    {
        brawler->catch_msg(dp);
        return;
    }
    else if ((intp(dp) &&
      (dp != 0)) ||
      (victim->query_prop(RANGER_I_NOT_DISARM) != 0))
    {
        write("It seems impossible to disarm " +
            victim->query_the_name(brawler) + ".\n");
        return;
    }

    if (objectp(disarm_object = present("Ranger_Disarm_Object", victim)))
    {
        if (disarm_object->query_two_handed())
	{
            was_disarmed = 1;
	}
    }

    if (!objectp(disarm_object) || 
      !was_disarmed)
    {
	setuid();
	seteuid(getuid());
        disarm_object = clone_object(DISARM_OBJECT);
    }
  
    if (seen || 
      check_seen_brawl(brawler, victim))
    {
        disarm_object->set_seen();
	victim->catch_tell(brawler->query_The_name(victim) + " delivers " +
	    "a painful blow on your hand!\n");

        if (victim->query_prop(LIVE_M_ATTACK_THIEF))
        {
            attack_brawler = 1;
        }
    }
    else
    {
        victim->catch_tell("Something hits you painfully on your hand!\n");
    }
  
    brawler->reveal_me(1);

    write("You skillfully deliver a painful blow on " +
	victim->query_the_possessive_name(brawler) + " hand!\n");
    tell_room(environment(brawler), QCTNAME(brawler) + " delivers a " +
        "painful blow on " + QTPNAME(victim) + " hand!\n", 
	({ brawler, victim }) );
    disarm_object->set_brawler(brawler);
    time_brawl = query_brawl_skill(brawler) / 2;

    if (time_brawl > MAX_TIME_BRAWL)
    {
        time_brawl = MAX_TIME_BRAWL;
    }
    if (time_brawl < MIN_TIME_BRAWL)
    {
        time_brawl = MIN_TIME_BRAWL;
    }

    disarm_object->set_time(time_brawl);

    if (!was_disarmed)
    {
        disarm_object->move(victim, 1);
    }
    else 
    {
        if (disarm_object->query_two_handed())
        {
	    disarm_object->complete_disarm();
        }
    }

    if (attack_brawler)
    {
        if (!victim->query_attack())
        {
	    write(victim->query_The_name(brawler) + 
		" glares at you angrily and attacks you!\n");
            brawler->attack_object(victim);
        }
        else
        {
	    write(victim->query_The_name(brawler) +
		" throws you a hateful glare, but continues " +
		victim->query_possessive() + " fight.\n");
            victim->query_combat_object()->cb_add_enemy(brawler);
        }
    }
}

/*
 * Function name: do_trip
 * Description  : This function handles the stunning effect that
 *                Rangers of the North can deliver.
 * Arguments    : victim - the victim of the brawl
 *                seen    - victim already recognized the brawler at
 *                          prep time
 */
private void
do_trip(object victim, int seen = 0)
{
    int     time_stun,
            sd;
    string  how,
            how2,
            how3;
    object  stun_ob, brawler = this_player();
    mixed   dp;

    if (stringp(dp = victim->query_prop(RANGER_M_NOT_TRIP)))
    {
        brawler->catch_msg(dp);
        return;
    }
    else if ((intp(dp) &&
	      (dp != 0)) ||
             (victim->query_prop(RANGER_I_NOT_TRIP) != 0))
    {
        write("It seems impossible to trip " +
          victim->query_the_name(brawler) + ".\n");
        return;
    }

    if ((sd = size_diff(brawler, victim)) > 10)
    {
	write(victim->query_The_name(brawler) + " is just " +
	    "too big for you to try to trip.\n");
        return;
    }

    if (!seen && !check_seen_brawl(brawler, victim))
    {
	write("You sneak a foot between " + 
	    victim->query_the_possessive_name(brawler) + ", and stand " +
	    "back to watch the unprepared " + victim->query_race_name() +
	    " struggle to keep " + victim->query_possessive() +
	    " balance!\n");
	victim->catch_tell("You trip over something, and struggle to " +
	    "stay on your feet!\n");
        how = "who was quite unaware";
        how2 = "struggles to regain " + victim->query_possessive() + 
	    " balance";
    }
    else if ((query_brawl_skill(brawler) + brawler->query_stat(SS_STR)) < 
	     (victim->query_skill(SS_ACROBAT) +
	      victim->query_stat(SS_DEX) + 10*(sd-1)))
    {
        victim->catch_tell(brawler->query_The_name(victim) + " tries " +
	    "to trip you, but you manage to avoid it!\n");
        write("You try to trip " + victim->query_the_name(brawler) + 
	    " but " + victim->query_pronoun() + " manages to avoid it!\n");
        return;
    }
    else
    {
	seen = 1;
        switch (sd)
	{
	case 0..2:
	    how = "without difficulty";
	    how2 = "stumbles around, wavering while trying to regain balance";
	    how3 = "stumble around, waving your arms, trying to regain balance";
	    break;
	case 3..5:
	    how = "with some problems";
	    how2 = "stumbles backwards, out of balance for a moment";
	    how3 = "stumble backwards, out of balance for a moment";
	    break;
	case 6..10:
	    how = "with great luck";
	    how2 = "takes a few steps back, to regain balance";
	    how3 = "take a few steps back, regaining balance";
	    break;
	}
    }

    brawler->reveal_me(1);

    if (seen)
    {
	write("You manage to trip " + victim->query_the_name(brawler) + 
	    " " + how + ". " + capitalize(victim->query_pronoun()) + 
	    " " + how2 + ".\n");
        victim->catch_tell(brawler->query_The_name(victim) + 
	    " skillfully trips you, and you " + how3 + ".\n");
    }

    brawler->tell_watcher(QCTNAME(brawler) + " manages to trip " +
        QTNAME(victim) + " " + how + ", and " + QTNAME(victim) + " " +
        how2 + ".\n", victim, brawler);
    time_stun = MAX(((query_brawl_skill(brawler) +
        brawler->query_ranger_rank())/10 - sd), MIN_TIME_BRAWL);

    if (!objectp(stun_ob = present("Ranger_Stun_Object",victim)))
    {
	setuid();
	seteuid(getuid());
        stun_ob = clone_object(RANGER_DIR + "obj/stun_ob");
        stun_ob->set_brawler(brawler);
        stun_ob->set_time(time_stun);
        stun_ob->set_seen(seen);
        stun_ob->move(victim,1);
        victim->add_stun();
    }
    else
    {
        stun_ob->set_brawler(brawler);
        stun_ob->set_time(time_stun);
        stun_ob->set_seen(seen);
    }
}

/*
 * Function name: do_knee
 * Description  : This function takes care of the Ithilien Company's
 *                kneeing effect. It uses a BLUDGEON attack at the
 *                lower abdomen (kidneys, groin) and will allow belts
 *                to subtract from the damage.
 * Arguments    : victim - the living who stands to be brawled.
 *                seen    - victim already recognized the brawler at
 *                          prep time
 */
private void
do_knee(object victim, int seen = 0)
{
    int     phurt,
            hp,
            dam,
            phit,
            wpen,
            ac,
            hum,
            sd,
            time_stun;
    object  belt,
            stun_ob,
	    brawler = this_player();
    string  how,
            where, 
            how2;

    if (victim->query_ghost())
    {
        write(victim->query_The_name(brawler) + 
	    " is already dead.\n");
        return;
    }

    if (seen || 
      check_seen_brawl(brawler, victim))
    {
	seen = 1;
    }

    setuid();
    seteuid(getuid());
    if ((sd = size_diff(brawler, victim)) > 10)
    {
        write(victim->query_The_name(brawler) + 
	    " is just too big for you to try to knee.\n");
        return;
    }

    brawler->reveal_me(1);

    if (objectp(belt = victim->query_armour(A_WAIST)))
    {
        ac = belt->query_ac() + belt->query_am()[2];
    }

    phit = random(F_PENMOD(brawler->query_stat(SS_STR)/4,
			   query_brawl_skill(brawler)/2 + 25*(1-seen)));
    ac = random(ac);
    dam = F_DAMAGE(phit, ac);

    if (dam < 1)
    {
        dam = 0;
    }

    hp = victim->query_hp();

    if (victim->query_wiz_level() && (dam >= hp))
    {
        victim->catch_tell(brawler->query_The_name(victim) +
	    " knees you in the groin.\n");
        victim->catch_tell("Your wizardhood protects you from death.\n");
        tell_room(environment(victim), QCTNAME(victim) +
            " is immortal and fails to die!\n", victim);
        return;
    }

    if ((dam > 0) && hp)
    {
        phurt = (100 * dam) / hp;

        if (phurt > 100)
	{
            phurt = 100;
	}

        if (dam && !phurt)
	{
            phurt = 1;
	}
    }
    else if (dam > 0)
    {
        phurt = 100;
    }
    else
    {
        phurt = -1;
    }

    if (dam > 0)
    {
        victim->heal_hp(-dam);
    }

    if (!objectp(victim->query_attack()))
    {
        brawler->attack_object(victim);
    }
    else
    {
        victim->query_combat_object()->cb_add_enemy(brawler);
    }

    if (phurt >= 0)
    {
        victim->add_panic(2 + phurt/5);
    }

    if (dam > (random(victim->query_stat(SS_DIS))/2))
    {
        victim->cmdhooks_break_spell();
    }

    if (phurt == -1)
    {
        write("Your attempt to knee " + victim->query_the_name(brawler) + 
	    " fails miserably, " + "and you stumble to regain balance.\n");
        brawler->add_attack_delay(random(4)+1, 1);
        brawler->add_fatigue(-3);

        /* The victim only knows the brawler fails,
         * if he knows the brawler tried.
         */
        if (seen)
        {
            victim->catch_tell(brawler->query_The_name(victim) + 
		" tries to knee you, but fails, losing " + 
		brawler->query_possessive() + " balance for a while.\n");
            brawler->tell_watcher(QCTNAME(brawler) + " tries to knee " +
              	QTNAME(victim) + ", but fails, losing " + 
		brawler->query_possessive() + " balance for a moment.\n", 
		victim, brawler);
        }
        return;
    }

    if ((victim->query_combat_file() == "/std/combat/chumlock") ||
      (victim->query_combat_file() == "/std/combat/chumanoid"))
    {
        hum = 1;
    }

    switch (phurt)
    {
    case 0:
	how = "but it doesn't seem to do any harm";

	if (hum)
	    where = "thigh";
	else
	    where = "body";

	break;
    case 1..4:
	how = "but it causes only a little pain";

	if (hum) 
	    where = "hip";
	else 
	    where = "body";

	break;
    case 5..9:
	how = "and it seems to hurt a little";

	if (hum) 
	    where = "stomach";
	else 
	    where = "middle";

	break;
    case 10..19:
          how = "causing some pain";

          if (hum) 
	      where = "stomach";
          else 
	      where = "middle";

          break;
    case 20..34:
          how = "rather painfully";

          if (hum) 
	      where = "kidneys";
          else 
	      where = "torso";

          break;
    case 35..54:
          how = "and it really hurts bad";

          if (hum) 
	      where = "groin";
          else 
	      where = "torso";

          break;
    case 55..84:
          how = "inflicting severe pain";

          if (hum) 
	      where = "groin";
          else 
	      where = "softer parts";

          break;
    case 85..99:
          how = "causing severe internal damage";

          if (hum) 
	      where = "groin";
          else 
	      where = "softer parts";

          break;
    default:
          how = "with a devastating result";
          how2 = "and the pain is surely killing you";

          if (hum) 
	      where = "groin";
          else 
	      where = "softer parts";

          break;
    }

    if (!strlen(how2)) 
    {
	how2 = how;
    }

    write("You raise your knee, hitting " + 
	victim->query_the_name(brawler) + " in the " + where + 
	", " + how + ".\n");

    if (!seen)
    {
        victim->catch_tell("Suddenly something hits you in " +
            where + ", " + how2 + ".\n");
    }
    else
    {
        victim->catch_tell(brawler->query_The_name(victim) + 
	    " suddenly raises a knee, hitting you in the " + 
	    where + ", " + how2 + ".\n");
    }

    brawler->tell_watcher(QCTNAME(brawler) + " suddenly raises a knee, " +
        "hitting " + victim->query_the_name(brawler) + " in the " + 
	where + ", " + how + ".\n", victim, brawler);

    if (phurt > 6 || dam > 66)
    {
        time_stun = MAX(((query_brawl_skill(brawler) +
            brawler->query_ranger_rank())/10 - sd), MIN_TIME_BRAWL);

        if (!objectp(stun_ob = present("Ranger_Stun_Object",victim)))
        {
	    setuid();
	    seteuid(getuid());
            stun_ob = clone_object(RANGER_DIR + "obj/stun_ob");
            stun_ob->set_brawler(brawler);
            stun_ob->set_time(time_stun);
            stun_ob->set_seen(seen);
            stun_ob->move(victim,1);
            victim->add_stun();
        }
        else
        {
            stun_ob->set_brawler(brawler);
            stun_ob->set_time(time_stun);
            stun_ob->set_seen(seen);
        }
    }

    if (victim->query_hp() <= 0)
    {
        victim->do_die(brawler);
    }

    return;
}

/*
 * Function name: fixnorm
 * Description:   normalize offensive/defensive values
 *                taken from /std/combat/cbase where it is stupidly
 *                declared static. 
 * Arguments:     int offense - offensive value
 *                int defense - defensive value
 * Returns:       Value in the range -50 .. 50
 */
private nomask int
fixnorm(int offence, int defence)
{
    if ((offence + defence) == 0)
	return 0;

    return ((100 * offence) / (offence + defence)) - 50;
}

/*
 * Function name: check_tohit
 * Description:   All the checks from cb_tohit for the special attacks
 *                that do no hp damage.
 * Arguments:     object brawler - the ranger who is brawling
 *                object victim  - the victim
 *                int    type    - brawl type (RANGER_I_BRAWL_TYPE)
 * Returns:       > 0 if we hit, else < 0
 */
private varargs int
check_tohit(object brawler, object victim, int type = BRAWL_BLIND)
{
    int     whit, old,
            tmp,
	    bskill;
    object  cobj = brawler->query_combat_object();

#ifdef DEBUG
    Fail_Stats[22]++;
#endif
    /*
     * Three factors are normalized (-50, 50) in the 'to-hit'.
     * 1 - brawl skill vs defence/parry skill
     * 2 - Weight
     * 3 - Volume
     * 4 - Dexterity
     * These are weighted with the factors (4, 1, 1, 2)
     */

    /*
     * For brawl, we check the defence and parry skills, but with a
     * reduced effectiveness for parry. 
     * This could be modified depending on the brawl type:
     * Only unarmed combat checked for blind and trip, parry check
     * fully for disarm.
     */
    tmp = victim->query_skill(SS_DEFENSE);

    /*
     * Parry skill does not help to avoid throwing of sand:
     */
    if (type != BRAWL_BLIND)
    {
	/* Any weapons wielded? */
	if (sizeof((object *)victim->query_weapon(-1) - ({ 0 })))  
	    tmp += (int)victim->query_skill(SS_PARRY) / 2;
	else
	    tmp += (int)victim->query_skill(SS_UNARM_COMBAT) / 2;
    }

    /*
     * Is it dark or opponent invis? Then how well do we fight?
     *
     * The check for light levels and invisibility is contained in
     * find_victim_to_brawl(), making it impossible to brawl unless we
     * can see the victim.
     * We add the check for the opponent, however:
     */
    if (!CAN_SEE_IN_ROOM(victim) || !CAN_SEE(victim, brawler))
    {
	bskill = victim->query_skill(SS_BLIND_COMBAT);
        bskill = ((bskill == 0) && victim->query_npc()) ? 40 : bskill;
	tmp = bskill * tmp / 100;
    }

    bskill = query_brawl_skill(brawler) / 2;
    whit = 4 * fixnorm(random(bskill) + random(bskill) + 
      random(bskill) + random(bskill), random(tmp));

    old = whit;
    whit += 2 * fixnorm(brawler->query_stat(SS_DEX), victim->query_stat(SS_DEX)) -
	       fixnorm(brawler->query_prop(CONT_I_VOLUME), victim->query_prop(CONT_I_VOLUME)) -
	       fixnorm(brawler->query_encumberance_weight() + victim->query_encumberance_volume(),
		       brawler->query_encumberance_weight() + victim->query_encumberance_volume());

    DEBUG_MSG(brawler->query_name() + " HIT:" + whit + ", " + old);

#ifdef DEBUG
    bskill /= 5;
#endif
    if (whit > 0)
    {
#ifdef DEBUG
	Fail_Stats[bskill]++;
#endif
        return 1;
    }
    else
    {
#ifdef DEBUG
	Fail_Stats[bskill + 11]++;
#endif
        return whit - 1;
    }
}

/*
 * Function name: do_brawl
 * Description  : This function checks whether the enemy did not flee during
 *		  the call_out.
 * Arguments    : brawler - the player that wants to brawl.
 *		  victim  - the victim of the brawl.
 */
public void
do_brawl(object brawler, object victim, int seen = 0)
{
    int     recover,
            al_id,
	    wchit,
	    type;
    object  cobj,
	   *wep;
  
    set_this_player(brawler);

    if (!objectp(brawler))
    {
        return;
    }

    if ((brawler->query_prop(RANGER_I_PREPARE_BRAWL) == MOVED_WHILE_BRAWLING)
      && (environment(brawler) == brawler->query_prop(RANGER_O_START_BRAWL)))
    {
        find_player("gwyneth")->catch_tell("Moved.\n");
        write("You cancel the prepared brawl since you moved too much " +
	    "while preparing.\n");
        brawler->add_prop(RANGER_I_PREPARE_BRAWL, RECOVER_BRAWL);
        recover = TIME_AFTER_BRAWL_FUMBLE(brawler) / 4;
        brawler->add_prop(RANGER_I_TIME_RECOVER, recover);
        al_id = set_alarm(itof(recover), 0.0, &can_brawl_again(brawler));
        brawler->add_prop(RANGER_CBA_AID, al_id);
        log_file("brawl", brawler->query_name() + " moved while preparing " +
            "to brawl " + victim->query_name() + ", in " +
            file_name(environment(brawler)) + ", " + ctime(time()) + ".\n");
        brawler->remove_prop(RANGER_O_START_BRAWL);
        return;
    }  

    /* The player obviously decided to stop his brawl. */
    if (brawler->query_prop(RANGER_I_PREPARE_BRAWL) != PREPARE_BRAWL)
    {
        return;
    }

    if ((!objectp(victim)) || (environment(brawler) != environment(victim)))
    {
        write("You stop preparing your brawl since the " +
            "intended target is no longer present.\n");
        brawler->add_prop(RANGER_I_PREPARE_BRAWL, RECOVER_BRAWL);
        recover = TIME_AFTER_BRAWL_FUMBLE(brawler);

        brawler->add_prop(RANGER_I_TIME_RECOVER, recover);
        al_id = set_alarm(itof(recover), 0.0, &can_brawl_again(brawler));
        brawler->add_prop(RANGER_CBA_AID, al_id);
        return;
    }
  
    if (brawler->query_prop(RANGER_I_BRAWL_TYPE) == BRAWL_UNKNOWN)
    {
        decide_on_brawl_type(brawler, victim);
    }

    brawler->add_prop(RANGER_I_PREPARE_BRAWL, RECOVER_BRAWL);
    recover = TIME_TO_BRAWL_AGAIN(brawler);

    if (!recover)
    {
	brawl_bug(brawler, "Recover time 0 in access_brawl: main code path.\n");
    }

    brawler->add_prop(RANGER_I_TIME_RECOVER, recover);
    al_id = set_alarm(itof(recover), 0.0, &can_brawl_again(brawler));
    brawler->add_prop(RANGER_CBA_AID, al_id);
    brawler->add_prop(LIVE_O_LAST_KILL, victim);

    /* Do we hit the enemy? */
    if ((type = brawler->query_prop(RANGER_I_BRAWL_TYPE)) == BRAWL_KNEE)
    {
	/*
	 * For 'knee' we use the standard cb_tohit function to
	 * determine the chance of a hit:
	 */
	cobj = brawler->query_combat_object();
	wep = brawler->query_weapon(-1);

	if (sizeof(wep))
	{
	    wchit = wep[0]->query_hit();
	}
	else
	{
	    wchit = W_HAND_HIT;
	}

	wchit += F_UNARMED_HIT(query_brawl_skill(brawler),
			       brawler->query_skill(SS_DEX)); 

	if (cobj->cb_tohit(-1, wchit, victim) < 0)
	{
	    write("Your attempt to knee " + victim->query_the_name(brawler) +
		" fails miserably, and you stumble to regain your balance.\n");
	    if (seen)
	    {
		victim->catch_tell(brawler->query_The_name(victim) + 
		    " tries to knee you, " + "but fails, losing " + 
		    brawler->query_possessive() + " balance for a while.\n");
		brawler->tell_watcher(QCTNAME(brawler)+" tries to knee "
                    + QTNAME(victim) + ", but fails, losing " + 
		    brawler->query_possessive() + " balance for a moment.\n", 
		    victim, brawler);

		if (!objectp(victim->query_attack()))
		{
		    victim->add_prop(LIVE_O_LAST_KILL, brawler);
		    victim->attack_object(brawler);
		}
	    }

	    return;
	}
    }
    else if (check_tohit(brawler, victim, type) < 0)
    {
	write("Your attempt to brawl " + victim->query_the_name(brawler) +
	    " fails miserably, and you stumble to regain your balance.\n");
	if (seen)
	{
	    victim->catch_tell(brawler->query_The_name(victim) + 
		" tries to brawl you, " + "but fails, losing " + 
		brawler->query_possessive() + " balance for a while.\n");
	    brawler->tell_watcher(QCTNAME(brawler)+" tries to brawl " +
                QTNAME(victim) + ", but fails, losing " + 
		brawler->query_possessive() + " balance for a moment.\n", 
		victim, brawler);

	    if (!objectp(victim->query_attack()))
	    {
		victim->add_prop(LIVE_O_LAST_KILL, brawler);
		victim->attack_object(brawler);
	    }
	}

	return;
    }

    switch (type)
    {
    case BRAWL_DISARM:
        do_disarm(victim, seen);
	break;

    case BRAWL_TRIP:
        do_trip(victim, seen);
	break;

    case BRAWL_KNEE:
        do_knee(victim, seen);
	break;

    case BRAWL_BLIND:
    default:
        do_blind(victim, seen);
	break;
    }
}

/*
 * Function name: check_choose
 * Description:   With guru brawl skill, a player may improve the
 *                chance that the chosen kind of brawl will be
 *                executed. 
 * Argument:      object player - player object
 * Returns:       1/0 - success/failure
 */
private int
check_choose(object player)
{
    int     skill;

    if ((skill = (query_brawl_skill(player) - BRAWL_CHOOSE_MIN)) <= 0)
	return 0;

    return (random(100) < (skill * BRAWL_CHOOSE_CHANCE / 
      (100 - BRAWL_CHOOSE_MIN)));
}
	
/*
 * Function name: blind
 * Description  : The actual blind command. This function is called when the
 *		  player types to blind someone.
 * Arguments    : str - whetever he wants to blind.
 * Returns      : 1/0
 */
public int
blind(string str)
{
    if (check_choose(this_player()))
    {
	this_player()->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_BLIND);
    }
    else 
    {
	this_player()->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_UNKNOWN);
    }

    return access_brawl(str);
}

/*
 * Function name: disarm
 * Description  : The actual disarm command. This function is called when the
 *		  player types to disarm someone.
 * Arguments    : str - whatever he wants to disarm.
 * Returns      : 1/0
 */
public int
disarm(string str)
{
    if (check_choose(this_player()))
    {
	this_player()->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_DISARM);
    }
    else
    { 
	this_player()->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_UNKNOWN);
    }

    return access_brawl(str);
}

/*
 * Function name: knee
 * Description  : The actual knee command. This function is called when the
 *		  player types to knee someone.
 * Arguments    : str - whatever he wants to knee.
 * Returns      : 1/0
 */
public int
knee(string str)
{
    if (this_player()->query_company() != "Ithilien")
    {
	return 0;
    }

    if (check_choose(this_player()))
    {
	this_player()->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_KNEE);
    }
    else
    { 
	this_player()->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_UNKNOWN);
    }

    return access_brawl(str);
}

/*
 * Function name: trip
 * Description  : The actual trip command. This function is called when the
 *		  player types to trip someone.
 * Arguments    : str - whatever he wants to trip.
 * Returns      : 1/0
 */
public int
trip(string str)
{
    if (this_player()->query_company() != "the North")
    {
	return 0;
    }

    if (check_choose(this_player()))
    {
	this_player()->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_TRIP);
    }
    else 
    {
	this_player()->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_UNKNOWN);
    }

    return access_brawl(str);
}

/*
 * Function name: brawl
 * Description  : The actual brawl command. This function is called when the
 *		  player types to brawl someone. What the player actually
 *                does (blind or disarm) is decided later.
 * Arguments    : str - whatever he wants to brawl.
 * Returns      : 1/0
 */
public int
brawl(string str)
{
    this_player()->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_UNKNOWN);
    return access_brawl(str);
}

/*
 * Function name: stop_brawl
 * Description  : The actual stop-brawl command. This function is called when
 *		  the player types to stop his brawl.
 * Arguments    : str - whatever he wants to stop.
 * Returns      : 1/0
 */
int
stop_brawl(string str)
{
    object tp = TP;
    int prep = (int)tp->query_prop(RANGER_I_PREPARE_BRAWL);

    if ((str != "brawl") && (str != "brawling"))
    {
	NFN0("Stop what? The world?");
    }

    /* All possible errors are handled in this function. */
    if (!still_has_to_recover())
    {
	WRITE("You are able to brawl without any further preparation.");
	return 1;
    }

    if (prep == PREPARE_BRAWL)
    {
	WRITE("You decide to stop preparing for a brawl.");
	reset_brawl_properties(tp);
	return 1;
    }

    WRITE("You have to recover from your last brawl.");
    return 1;
}

#ifdef DEBUG
public void
remove_object()
{
    FIX_EUID;
    log_file("brawl_stats", "\n\t" + ctime(time()) + "\n" +
	     query_brawl_stats() +
	     query_brawl_stats(1));
    destruct();
}
#endif
