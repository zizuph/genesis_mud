/*
 * /d/Gondor/lebennin/sirith/farms/npc/pig.c
 * stats and attacks taken from /d/Gondor/dunland/npc/boar.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * originally tried to allow feeding random food (apples, carrots, ...)
 * to pig. too hard. it seems the only way to tell if an item is food
 * is to call query_amount(). unfortunately, herbs also set_amount().
 * i don't want her to eat random herbs because then i have to deal with
 * poisoning directly, as well as in scraps. easy enough to refuse herbs
 * and only eat food, but --- potatoes, carrots, beans and other "food"
 * are herbs. forget it. not worth the bother.
 */

#pragma strict_types


inherit "/d/Gondor/lebennin/sirith/farms/npc/livestock";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>		/* for W_SLASH, etc 		*/
#include <macros.h>		/* for QTNAME, etc		*/
#include <ss_types.h>		/* for SS_UNARM_COMBAT, etc	*/
#include <const.h>		/* for G_FEMALE			*/
#include <stdproperties.h>	/* for NPC_I_NO_LOOKS, etc	*/
#include <language.h>		/* for LANG_ADDART		*/
#include <cmdparse.h>		/* for NORMAL_ACCESS		*/
#include "/d/Gondor/defs.h"
#include "../defs.h"

#define	TRIED_TO_CATCH_PIG	"_tried_to_catch_pig"
#define	ATTACK_ON_NTH	 3	/* attack on 3rd attempt to catch	*/
#define	MIN_ANI_HANDL	 8	/* min level to follow you		*/
#define	WAIT_N_MOVES	 3	/* wait before moving pig away		*/


#define	MIN_POIS_MSG	 5	/* see at least 5 msgs for dying pig	*/
#define	POIS_MSG_EXTRA	 5	/* and at most 5 more			*/

/* just for a guideline, pelargir pub sells:
 *		alcohol	    soft    percent
 *		 amount	  amount    alcohol
 *	ale	      2      100	 2%
 *	beer	      9      120	 8%
 *	wine	     24      150	16%
 *	whiskey	     40       50	80%
 *	rum	     46       55	84%
 *
 * say minimum is a bottle of wine ... can't see a single beer affecting
 * a 300-lb pig.
 */
#define	MIN_ALCOHOL	24	/* alcohol in a pelargir bottle of wine	*/
#define	MIN_ALCOHOL_MSG	 2	/* see at least 2 msgs for tipsy pig	*/
#define	MAX_ALCOHOL_MSG	10	/* max of 10 msgs (depending on 	*/
				/* alcohol consumed and on random())	*/

#define	EASTYARD	(SIRITH_FARMS_DIR+"farm1/eastyard")
#define	SOUTHYARD	(SIRITH_FARMS_DIR+"farm1/southyard")

static object	Poison_obj;	/* our poison object			*/
static object	Prev_loc;	/* our previous location		*/
static string	Poisoned_by;	/* real name of poisoner		*/
static int	Did_follow,	/* did we follow player's last move?	*/
		Nwaits,		/* how many times we've waited		*/
		Alcohol_alarm,	/* alarm id of tipsy_pig() sequence	*/
		Poison_alarm,	/* alarm id of poisoned_pig() sequence	*/
		Count;		/* where we are in either sequence	*/

/* prototypes */
public void	create_sirith_livestock();
public void	init_living();
public void	cr_configure();
public string	cr_attack_desc(int aid);
public int	feed_scraps(object scraps);
public int	capture(string arg);
public int	tie_object(object obj, string arg);
public int	mtrig_follow(string s1, string s2);
public void	enter_env(object dest, object old);
public void	monster_ranwalk();
public void	run_away();
public void	tipsy_pig();
public void	poisoned_pig();
public void	do_die(object killer);
public int	second_life(object killer);
public int	feed_stuff(string arg);

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_TUSKS  0
#define A_CHARGE 1
#define A_FHOOVES 2
#define A_RHOOVES 3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_TAIL 3

/*
 * Function name:	create_sirith_livestock
 * Description	:	set up the pig
 */
public void
create_sirith_livestock()
{
    if (!IS_CLONE)
    {
	return;
    }

    FIX_EUID;
    set_name( ({ "pig", "sow", "beast", "animal", PIGNAME }) );
    set_living_name(PIGNAME);
    set_short("huge pig");
    set_long(BSN("The pig is enormous, with tusklike teeth and sharp "+
	"hooves."));
    set_adj(({"huge", "enormous"}));
    set_race_name("pig");
    set_alignment(0);
    set_gender(G_FEMALE);

		/* str, dex, con, int, wis, dis */
    set_stats(({random(30)+20, random(15)+30, random(40)+40,
	random(25), random(15), random(25)+25}));
    set_skill(SS_UNARM_COMBAT,random(20)+30);
    set_skill(SS_CLIMB,random(15)+10);
    set_skill(SS_SWIM,random(10)+5);
    set_skill(SS_DEFENCE,random(20)+30);
    set_skill(SS_PARRY,random(20)+30);
    set_whimpy(30);
    set_random_move(random(5)+1);
    set_monster_home(PIGWOODS);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(NPC_I_NO_LOOKS, 1);
    add_leftover(SIRITH_FARMS_DIR+"obj/pigskin", "skin", 1, "", 0, 1);

    /* "A full-grown boar is up to three feet tall at the shoulder, four
     * to five feet long from snout to rump and weighs about 300 pounds."
     */
    add_prop(CONT_I_HEIGHT, 91);
    add_prop(CONT_I_WEIGHT, 136080);
    add_prop(CONT_I_VOLUME, 849618);	/* 3' tall x 5' long x 2' wide */

    set_alarm(0.0, 0.0, &set_m_in("ambles into view"));
    set_alarm(0.0, 0.0, &set_m_out("ambles"));
} /* create_sirith_livestock */


/*
 * Function name:	init_living
 * Description	:	add player verbs
 */
public void
init_living()
{
    ::init_living();

    add_action(capture, "get");
    add_action(capture, "take");
    add_action(capture, "capture");
    add_action(capture, "corner");
    add_action(capture, "catch");
    add_action(capture, "kidnap");
    add_action(capture, "grab");

    add_action(feed_stuff, "feed");
    add_action(feed_stuff, "give");
    add_action(feed_stuff, "show");
    add_action(feed_stuff, "lure");
    add_action(feed_stuff, "tempt");
} /* init_living */


/*
 * Function name:	cr_configure
 * Description	:	add attacks and hitlocations:
 */
public void
cr_configure()
{
    /*
     * add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
     * add_hitloc(int *ac, int prchit, string desc, int id)
     *
     * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
     */
    add_attack(random(15)+5,random(20)+15,W_SLASH,45,A_TUSKS);
    add_attack(random(40)+30,random(30)+30,W_BLUDGEON,25,A_CHARGE);
    add_attack(random(20)+15,random(15)+5,W_SLASH,20,A_FHOOVES);
    add_attack(random(20)+10,random(30)+10,W_BLUDGEON,10,A_RHOOVES);
 
    add_hitloc(({random(15)+25,random(20)+15,random(20)+20}),10,"head",H_HEAD);
    add_hitloc(({random(6)+4,random(12)+11,random(12)+10}),45,"body",H_BODY);
    add_hitloc(({random(10)+15,random(4)+4,random(4)+5}),40,"legs",H_LEGS);
    add_hitloc(({random(30)+40,random(12)+13,random(15)+25}),5,"tail",H_TAIL);
} /* cr_configure */


/*
 * Function name:	cr_attack_desc
 * Description	:	Give description of each attack.
 * Arguments	:	int aid -- the attack id
 *
 * We could also redefine the entire hitdescription by redefining 'cr_did_hit'
 */
public string
cr_attack_desc(int aid)
{
    switch (aid)
    {
    case A_TUSKS:	return "tusks";
    case A_CHARGE:	return "charge";
    case A_FHOOVES:	return "front feet";
    case A_RHOOVES:	return "trample";
    default:		return "mind"; /* should never occur */
    }
} /* cr_attack_desc */


/* 
 * Function name:	feed_scraps
 * Description	:	respond to player's give/feed/show/lure with scraps
 * Arguments	:	object scraps -- the scraps
 * Returns	:	1	calling scraps should self destruct
 *			0	not self destruct
 */
public int
feed_scraps(object scraps)
{
    object	env,		/* pig's env */
		door,		/* door/gate here? */
		tp,		/* this player */
		fplayer;	/* player we're following */
    int		pstr,		/* strength of poison in scraps */
		pdam,		/* hp damage done by poison in scraps */
		alch;		/* alcohol in scraps */
    string	vb,		/* verb */
		pname,		/* tp's name */
    		followed;	/* fplayer's name */

    if (Poison_alarm)
    {
	write(BSN("The pig appears to be in some distress; she "+
	    "pays no attention to you."));
	return 0;	/* don't destroy scraps */
    }

    if (Alcohol_alarm)
    {
	write(BSN("The pig sways tipsily and seems unable to "+
	    "focus on the scraps."));
	return 0;	/* don't destroy scraps */
    }

    tp = TP;
    if (tp->query_skill(SS_ANI_HANDL) < MIN_ANI_HANDL)
    {
	write(BSN("You approach the huge pig with the scraps, but she "+
	    "eyes you mistrustfully. It's a pity you're not better "+
	    "with animals."));
	return 0; /* don't destroy scraps */
    }

    /* ok, we've done the easy returns -- initialize some vars */
    vb = query_verb();
    env = ENV();
    pname = tp->query_real_name();
    if (!strlen(followed = query_follow()))
    {
	followed = query_prop(SIRITH_S_WAS_LED);
    }
    if (vb == "show" ||
	vb == "lure")
    {
	if (file_name(env) == PIGSTY)
	{
	    /* don't follow out of sty */
	    write(BSN("You show the scraps to the huge pig, "+
		"who gives a hungry grunt."));
	    return 0;	/* don't destroy scraps */
	}

	/* no SAY here -- don't want to give away the trick */
	write(BSN("You show the scraps to the huge pig. She gives a "+
		"loud grunt and edges closer."));

	/* don't call set_follow() repeatedly for the same player,
	 * because it continues to add (identical) trigger patterns. 
	 * unset_follow() will only remove one of those patterns,
	 * which means the pig will continue to follow even after
	 * we've said she's lost interest.
	 */
	if (!strlen(followed))
	{
	    set_follow(pname, 0);
	}
	else if (followed != pname &&
		 objectp(fplayer = present(followed, env)))
	{
	    /* already following another player */
	    write(BSN("The pig eyes the scraps "+
		"for a moment, but then turns back towards "+
		( tp->query_met(fplayer) ? fplayer->query_name() :
		    "the "+fplayer->query_nonmet_name() )+"."));
	    tell_object(fplayer, 
		BSN(( fplayer->query_met(tp) ? tp->query_cap_name() :
			"The "+tp->query_nonmet_name() )+
		" shows some scraps to the pig. The pig wavers "+
		"for a moment, then turns back towards you."));
	}
	else
	{
	    unset_follow();
	    set_follow(pname, 0);
	}
	return 0;	/* don't destroy scraps */
    }
    /* else verb is feed or give */
    write(BSN("You feed the scraps to the huge pig, who consumes "+
        "them with loud grunts of pleasure."));
    SAY(" feeds something to the huge pig.");

    pstr =  scraps->query_poison_str();
    pdam = scraps->query_poison_dam();
    alch = scraps->query_soft_amt() * scraps->query_alcohol_per();
    if (pstr >= MIN_POIS_STR &&
	pdam >= MIN_POIS_DAM)
    {
	DEBUG_LOG(" poisoned by "+pname+" pstr "+
		pstr+" pdam "+pdam+"\n");
	Poisoned_by = pname;
	tp->add_prop(SIRITH_I_POIS_PIG, 1);
	Count = MIN_POIS_MSG + random(POIS_MSG_EXTRA);
	Poison_alarm = set_alarm(5.0, 10.0, &poisoned_pig());
    }
    else if (alch >= MIN_ALCOHOL)
    {
        Count = MIN_ALCOHOL_MSG + random(alch/10);
	if (Count > MAX_ALCOHOL_MSG)
	    Count = MAX_ALCOHOL_MSG;
	Alcohol_alarm = set_alarm(5.0, 10.0, &tipsy_pig());
    }

    /* if poisoned pig, or pig is not in sty, we're done */
    if (Poison_alarm ||
	file_name(env) != PIGSTY)
    {
	if (pname == followed)
	{
	    unset_follow();	/* got what we want, quit following */
	}
	return 1;	/* destroy scraps */
    }

    /* must have followed this player in */
    if (pname != followed)
    {
	DEBUG_LOG(pname+" fed pig, but pig had followed "+
	    (strlen(followed) ? followed : "no one")+"\n");
	return 1;	/* destroy scraps */
    }

    /* ok, player led pig in the pigsty and fed her ... but did
     * s/he close the gate?
     */
    if (!objectp(door = present(SIRITH_DOOR, env)) ||
	door->query_open())
    {
	DEBUG_LOG(pname+" led pig into sty, but fed w/out closing gate\n");
	unset_follow();
	remove_prop(SIRITH_S_WAS_LED);
	tp->remove_prop(SIRITH_I_LED_PIG);
	env->move_pig(env, 0);
	return 1;	/* destroy scraps */
    }
    env->set_nresets(0);	/* stay put for awhile */
    unset_follow();
    return 1;	/* destroy scraps */
} /* feed_scraps */


/*
 * Function name:	capture
 * Description	:	handle attempts to catch the pig
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 otherwise
 */
public int
capture(string arg)
{
    object	target;
    int		ntries;

    if (!strlen(arg))
    {
	NF0(capitalize(query_verb())+" what?\n");
    }

    /* pig has lots of names and adjectives -- use parse_command */
    if (parse_command(LOW(arg), ENV(TP), "%o", target))
    {
	if (target != TO)
	{
	    NF0(capitalize(query_verb())+" what?\n");
	}

	ntries = TP->query_prop(TRIED_TO_CATCH_PIG);
	if (++ntries >= ATTACK_ON_NTH)
	{
	    write(BSN("You make a futile grab at the huge pig, "+
		"who squeals furiously!"));
	    SAY(" grabs at the huge pig, who squeals furiously!");
            command("kill " +TP->query_real_name());
	}
	else
	{
	    write(BSN("You make a futile grab at the huge pig, "+
		"who grunts angrily."));
	    SAY(" grabs at the huge pig, who grunts angrily.");
	    TP->add_prop(TRIED_TO_CATCH_PIG, ntries);
	}
	return 1;
    }
    NF0(capitalize(query_verb())+" what?\n");
} /* capture */


/*
 * Function name:	tie_object
 * Description	:	respond to attempts to tie rope to pig
 * Arguments	:	object rope -- the rope
 *			string arg -- string to tie to
 * Returns	:	0 -- cannot tie rope to pig
 *
 * behaves just like attempts to catch pig. keep trying and pig will
 * get annoyed and attack.
 */
public int
tie_object(object obj, string arg)
{
    int		ntries;

    ntries = TP->query_prop(TRIED_TO_CATCH_PIG);
    if (++ntries >= ATTACK_ON_NTH)
    {
	SAY(" tries to tie a rope to the huge pig, who squeals furiously!");
        set_alarm(1.0, 0.0, &command("kill " +TP->query_real_name()));
	NFN0("You try to tie the rope to the huge pig, "+
		"who squeals furiously!");
    }
    SAY(" tries to tie a rope to the huge pig, who grunts angrily "+
	"and backs away.");
    TP->add_prop(TRIED_TO_CATCH_PIG, ntries);
    notify_fail(BSN("You try to tie the rope to the huge pig, "+
	" who grunts angrily and backs away."));
    return 0;
} /* tie_object */


/*
 * Function name:	mtrig_follow
 * Description	:	intercept domove's mtrig_follow() to introduce
 *			a chance of pig losing interest if player's
 *			skills aren't very high
 * Arguments	:	s2, s2: The strings returned by the trig-function
 * Returns	:	1 if we follow, 0 if not
 */
public int
mtrig_follow(string s1, string s2)
{
    object	tp;
    string	followed;

    /* always follow out of pigsty (unless of course we were fed by 
     * the player we were following, but in that case
     * unset_follow would've been called and we wouldn't be here.)
     * n.b. assume we have an env, since this routine is only 
     * called when we get a pattern match on the player we're following
     * and if player was here, then surely 'here' exists.
     */
    if (file_name(ENV()) != PIGSTY &&
	Did_follow &&
        strlen(followed = query_follow()))
    {
	/* if player is gone, quit following. otherwise, there's 
	 * always a 1 in 12 chance of the pig losing interest, however
	 * skilled the player. beyond that, if player has low skills
	 * there's an even better chance of losing the pig.
	 */
	if (!objectp(tp = find_living(followed)) ||
	    !random(12) ||
            tp->query_skill(SS_ANI_HANDL) <
		(MIN_ANI_HANDL + random(MIN_ANI_HANDL)))
	{
	    unset_follow();
	    Did_follow = 0;
	    set_random_move(random(5)+1);
	    return 0;
	}
    }
    Did_follow = ::mtrig_follow(s1, s2);
    return Did_follow;
} /* mtrig_follow */


/*
 * Function name:	enter_env
 * Description	:	after calling parent, be sure we haven't left farms
 * Arguments	:	object destination, object old env
 *
 * if the player repeatedly shows the scraps to the pig, i think the
 * follow-player code will take precedence over random moves, and so the
 * restrain paths might not get checked. also, if the pig is led to 
 * an unfrequented spot and left there, i think random moves stop
 * firing until an interactive appears (which could be quite a while)
 * and so again might miss the restrain path checks.
 *
 * also, don't want pig led indoors on farm, unless it's a barn.
 */
public void
enter_env(object dest, object old)
{
    object	tp;
    string	destname,
		tmpstr;

    ::enter_env(dest, old);
    destname = file_name(dest);

    /* did we follow someone into sty ? */
    if (destname == PIGSTY)
    {
	if (!strlen(tmpstr = query_follow()))
	{
	    if (objectp(old))
	    {
		/* "cannot" happen */
		DEBUG_LOG(" entered sty from "+
		   file_name(old)+" of her own accord\n");
	    }
	    return;
	}
	if (objectp(tp = present(tmpstr, ENV())))
	{
	    DEBUG_LOG(" followed "+tmpstr+" into sty\n");
	    tp->add_prop(SIRITH_I_LED_PIG, 1);
	    add_prop(SIRITH_S_WAS_LED, tmpstr);
	    dest->set_nresets(0);	/* stay put for awhile */
	}
	else
	{
	    /* "cannot" happen, either */
	    DEBUG_LOG(" followed "+tmpstr+" into sty, but "+
		tmpstr+" disappeared\n");
	}
	/* pigsty will take care of us following player back out */
	unset_follow();
	return;
    }

    if (!sscanf(destname, SIRITH_FARMS_DIR+"%s", tmpstr) ||
        (dest->query_prop(ROOM_I_INSIDE) &&
	 !sscanf(tmpstr, "%sbarn", tmpstr)))
    {
	if (strlen(tmpstr = query_follow()))
	{
	   tmpstr = " following "+tmpstr+".\n";
	}
	else
	{
	    tmpstr = ".\n";
	}
	DEBUG_LOG(" in "+file_name(ENV())+tmpstr);

	if (dest->query_prop(ROOM_I_INSIDE))
	{
	    Prev_loc = old;
	}
	else
	{
	    Prev_loc = 0;
	}
	set_alarm(3.0, 0.0, &run_away());
    }
} /* enter_env */


/*
 * Function name:   monster_ranwalk
 * Description:	    check before calling real monster_ranwalk()
 *
 * never let monster_ranwalk() move pig from pigwoods or pigsty;
 * those rooms manage pig movement on their own.
 *
 * farm1/eastyard and southyard also are special cases. pig will
 * only be there if led by player, and those 2 rooms are the path
 * to the pigsty. don't want monster_ranwalk() to remove pig because it
 * could happen too quickly -- want to give player time to continue/resume
 * leading pig. also, in the case of southyard, there is no legitimate exit
 * for the pig to take, which means that monster_ranwalk() will move it to
 * pigwoods and say that the pig "goes home". this could be confusing,
 * since the player might logically expect "home" to mean "the adjacent
 * pigsty". unfortunately, there doesn't seem to be any way to 
 * customize the "goes home" msg.
 * 
 * soooo ... roll our own. give the player WAIT_N_MOVES chances to
 * re-acquire the pig's interest, then move it.
 *
 * n.b. call set_random_move() before returning, or the sequencing stops.
 *
 */
public void
monster_ranwalk()
{
    object	env;
    string	tmpstr;

    if (!objectp(env = ENV()))
    {
	set_random_move(random(5)+1);
	return;
    }

    if (strlen(tmpstr = query_follow()) &&
	objectp(present(tmpstr, env)))
    {
	set_random_move(random(5)+1);
	return;
    }

    tmpstr = file_name(env);
    if (tmpstr == PIGSTY ||
	tmpstr == PIGWOODS)
    {
	set_random_move(random(5)+1);
	return;
    }

    if (tmpstr == EASTYARD ||
	tmpstr == SOUTHYARD)
    {
	if (++Nwaits <= WAIT_N_MOVES)
	{
	    set_random_move(random(5)+1);
	    return;
        }
        Nwaits = 0;
	unset_follow();	/* must be done before move_pig() */
        PIGSTY->move_pig(env, 0);
	/* no set_random_move() here -- pigsty will do it */
	return;
    }
    ::monster_ranwalk();
} /* monster_ranwalk */


/*
 * Function name:	run_away
 * Description	:	called from combat if whimpy fires, or from enter_env
 *			if player leads pig outside SIRITH_FARMS_DIR or
 *			leads pig inside a building (except barns) on farm
 */
public void
run_away()
{
    object	env = ENV();

    if (query_attack())
    {
	if (file_name(env) == PIGSTY)
	{
	    env->leave_sty(PIG_HURT);
	}
	::run_away();
	return;
    }

    /* not called from combat, so we've been led somewhere we shouldn't
     * be. if Prev_loc is set, return there if we can. if Prev_loc is
     * not set or return fails, call pigsty to move us randomly
     */
    unset_follow();
    Did_follow = 0;
    if (objectp(Prev_loc) &&
	!move_living("away", Prev_loc))
    {
	    Prev_loc = 0;
	    set_random_move(random(5)+1);
	    return;
    }
    Prev_loc = 0;
    PIGSTY->move_pig(env, 0);
} /* run_away */


/*
 * Function name:	tipsy_pig
 * Description	:	actions of a drunk pig
 */
public void
tipsy_pig()
{
    object	env = ENV();

    if (objectp(query_attack()))
    {
	return;
    }

    if (Count <= 0)
    {
	remove_alarm(Alcohol_alarm);
	Alcohol_alarm = Count = 0;
	if (file_name(env) == PIGSTY)
	{
	    env->leave_sty(PIG_DRUNK);
	    command("emote stumbles north.");
	}
	else
	{
	    command("emote stumbles away.");
	}
	/* reduce hp so we stay in the woods for a little while */
	TO->heal_hp(-(TO->query_max_hp()/10));
	TO->move(PIGWOODS, 1);
	return;
    }
    --Count;
    command( ({ "emote stumbles.", "burp", "hiccup",
	"emote exhales a boozy breath.",
	"emote turns in a tipsy circle.",
	"emote blunders into you.",
	"emote sways on her stubby legs and almost tips over.",
	"emote grunts tipsily.",
	"emote weaves back and forth.",
	"emote seems to have trouble focusing her eyes." })[random(10)] );
} /* tipsy_pig */


/*
 * Function name:	poisoned_pig
 * Description	:	actions of a dying pig
 */
public void
poisoned_pig()
{
    if (Count <= 0)
    {
	remove_alarm(Poison_alarm);
	Poison_alarm = Count = 0;
	heal_hp(-(TO->query_max_hp()+20));

	/* cobble up a tmp 'killer' arg for do_die(). can't just use
	 * this_object() because if killer arg is living, combat/cbase.c
	 * prints a death msg and we'll see:
	 *	The huge pig caused her death.
	 * the killer arg has to be a global var so we can check it
	 * in second_life().
	 */
	Poison_obj = clone_object("/std/poison_effect");
	do_die(Poison_obj);
	Poison_obj->remove_object();
	Poison_obj = 0;

	return;
    }
    --Count;
    command( ({ "cough", "shiver", "moan", "groan",
	"emote lowers her head and pukes.",
	"emote squeals in agony." })[random(6)] );
    TO->heal_hp(-(TO->query_max_hp()/12));
} /* poisoned_pig */


/*
 * Function name:	do_die
 * Description	:	intercept the normal do_die() to prevent
 *			the pig dying of anything but poison
 *			in her scraps or normal combat
 * Arguments	:	object killer -- cause of death
 *
 * i want the pig to die only of poison in her scraps (in which case
 * the skin is not damaged) or combat (in which case it is damaged).
 * if players kill the pig by other non-combat means (e.g., spells),
 * then either the skin is undamaged and they get credit for the quest
 * without having solved it, or somehow the spell cuts/tears/bloodies
 * the skin -- which can be very unlikely.
 * 
 * soooo .. make the pig run away and then i don't have to 
 * deal with every magical attack in the game
 */
public void
do_die(object killer)
{
    object	env = ENV();

    if (killer == Poison_obj ||
	interactive(killer))
    {
	::do_die(killer);
    }
    else
    {
	if (file_name(env) == PIGSTY)
	{
	    env->leave_sty(PIG_HURT);
	    tell_room(env, "The huge pig staggers north.\n");
	}
	else
	{
	    tell_room(env, "The huge pig staggers away.\n");
	}
	unset_follow();
	Did_follow = 0;
	TO->move(PIGWOODS, 1);
    }
} /* do_die */


/*
 * Function name:	second_life
 * Description	:	handle the stuff that must be done
 *			after we die, but before this object
 *			is destructed, if player poisoned us
 * Arguments	:	object killer -- who did us in
 * Returns	:	0 -- no second life
 */
public int
second_life(object killer)
{
    object	corpse;

    /* assume that since our corpse was just moved into env,
     * it will be the one found by present()
     */
    if (killer == Poison_obj)
    {
	if (objectp(corpse = present("corpse of pig", ENV())))
	{
	    DEBUG_LOG("adding WAS_KILLED ("+Poisoned_by+") to "+
		file_name(corpse)+"\n");
	    corpse->add_prop(SIRITH_S_WAS_POIS, Poisoned_by);
            corpse->add_name(PIGCORPSE);
	}
	else
	{
	    /* "cannot" happen */
	    DEBUG_LOG("poisoned, but no corpse in "+file_name(ENV())+"\n");
	}
    }
    return 0;
} /* second_life */


/*
 * Function name:	feed_stuff
 * Description	:	responds to attempts to feed/give/show/lure ...
 *				pig something other than the scraps
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
feed_stuff(string arg)
{
    mixed	*oblist;
    int		parse_ret;
    string	vb = query_verb(),
		what, whom,
		failstr;

    if (!CAN_SEE_IN_ROOM(TP) ||
	!strlen(arg))
    {
        return 0;
    }

    /* there's a bug in parse_command(), so we can't do the obvious
     * parse of "%i to %l" or "%l with %i". so use sscanf to split
     * out what & whom, then do two calls to parse_command.
     */
    if (vb != "lure" &&
	vb != "tempt") /* feed, give, show */
    {
	failstr = capitalize(vb)+" what to whom?\n";
	if (sscanf(LOW(arg), "%s to %s", what, whom) != 2)
	{
	    NF0(failstr);
	}
    }
    else	/* lure, tempt */
    {
	failstr = capitalize(vb)+" whom with what?\n";
	if (sscanf(LOW(arg), "%s with %s", whom, what) != 2)
	{
	    NF0(failstr);
	}
    }

    parse_ret = parse_command(whom, all_inventory(ENV(TP)), "%l", oblist);
    if (!parse_ret ||
	!sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)) ||
    	oblist[0] != TO)
    {
	NF0(failstr);
    }

    parse_ret = parse_command(what, all_inventory(TP), "%i", oblist);
    if (!parse_ret ||
	!sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)) ||
    	oblist[0]->id(SIRITH_SCRAPS))
    {
	NF0(failstr);
    }

    what = oblist[0]->query_short();
    write(BSN("You hold the "+what+" under the huge pig's nose."));
    SAY(" holds "+LANG_ADDART(what)+" under the huge pig's nose.");
    if (oblist[0]->query_amount() ||
        oblist[0]->query_soft_amount())
    {
        /* food, herb or drink */
	tell_room(ENV(),
	    "The huge pig snuffles at the "+what+", then turns away\n");
    }
    return 1;
} /* feed_stuff */
