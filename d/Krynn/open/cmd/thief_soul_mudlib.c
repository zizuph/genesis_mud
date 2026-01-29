/*
 * thief_soul_mudlib.c
 *
 * This soul holds the thief specific commands steal and backstab.
 *
 * created by Aridor, 1994
 * 
 * Revision history:
 *   Aridor,    ?   : miscellaneous stuff
 *   Aridor, 190899 : Added call to did_hit for backstab to allow poisoned
 *                    weapons to work correctly.
 *
 * FOR INCLUSION INTO THE MUDLIB, these aspects need to be checked:
 * - line 107 includes a Krynn specific file which checks whether
 *            someone can attack someone else. I do not know of
 *            any such check in the mudlib which could be called
 *            instead as a function. The file could be simply
 *            written into this file at the appropriate place.
 * - Logging of steal attempts: Quite a bit of data for logging
 *            purposes is collected. Before inclusion into the
 *            mudlib, logging should be reduced to only log
 *            successful steals for evaluation.
 *            To remove logging altogether, all references to the
 *            variable 'la' in the steal() function can be removed.
 *            Wizards are given special success info when stealing,
 *            this can be removed entirely.
 * - The add_exp_general function call should be enabled (line 940).
 *            Exp given out depends on how hard it was to steal
 *            something successfully (ie. the value determined for
 *            the victim is used as a basis), no matter how good or
 *            bad the thief can steal. Due to the recovery time of
 *            10 minutes to get back to full stealing capacity, the
 *            exp giving cannot be abused.
 * - Almost all items relevant to changing at mudlib inclusion time
 *            have been enclosed by #ifdef so that a simple undefine
 *            will fix most things.
 */

inherit "/cmd/std/command_driver";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>
#include <composite.h>
#include <formulas.h>
#include <std.h>
#include <money.h>

/* undefine this for inclusion into the mudlib */
#define NOT_MUDLIB_READY  1
#ifndef LIVE_AO_THIEF
#define LIVE_AO_THIEF     "_live_ao_thief"
#endif
                          /* list of thieves who have stolen from this living */
#ifndef STEAL_EXP_LOG
#define STEAL_EXP_LOG     "steal_exp"
#endif
                          /* log all exp that would be given out for stealing here to evaluate balance */
#ifdef NOT_MUDLIB_READY
#define STEAL_ATTEMPT_LOG "steal_attempts"
                          /* log all stealing attempts here to evaluate balance issues */
#define STEAL_LOG_CYCLE   1000000
                          /* recycle the log if > 100.000 bytes */
#endif /* NOT_MUDLIB_READY */

#ifndef LIVE_I_GOT_BACKSTABBED
#define LIVE_I_GOT_BACKSTABBED     "_live_i_got_backstabbed"
#endif

#ifndef LIVE_M_ATTACK_THIEF
#define LIVE_M_ATTACK_THIEF        "_live_m_attack_thief"
#endif

#ifndef VICTIM_I_ADDED_AWARENESS
#define VICTIM_I_ADDED_AWARENESS   "_victim_i_added_awareness"
#endif
#ifndef AWARENESS_BONU
#define AWARENESS_BONUS   5
#endif
                          /* the bonus if you notice someone stealing from you */
#ifndef LIVE_I_LAST_STEAL
#define LIVE_I_LAST_STEAL          "_live_i_last_steal"
#endif
                                   /* time of the last steal attempt */

/*------BACKSTAB FORMULAS--------*/
                                   /* did i hit my victim? */
#ifndef F_BS_HIT
#define F_BS_HIT(bs,dex,aware,def)  (random(80*bs+20*dex-40*(aware+def))-random(160))
#endif
                                   /* old formula was: (6*bs+2*dex-3*(aware+def)-random(100))*/
                                   /* the penetration of the backstab attack */
#ifndef F_BS_PEN
#define F_BS_PEN(bs, knife, wp, str) F_PENMOD(wp*(1+(bs+str))/10,knife)
#endif

/*------STEALEXP FORMULA---------*/
#ifndef F_STEAL_EXP
#define F_STEAL_EXP(vic_val)         (vic_val/4>1048?1048:vic_val/4)
#endif

#ifdef NOT_MUDLIB_READY
#define DEBUG ({"Aridor"})
#endif /* NOT_MUDLIB_READY */

/*----Some handy defines---------*/
#define TP    this_player()
#define TO    this_object()
#define C(x)  capitalize(x)
#define L(x)  lower_case(x)
#define E(x)  environment(x)
#define NF(x) notify_fail(x)
#define PRONOUN(x) (x->query_pronoun())

/*****************************************************************************
 * Variables
 *****************************************************************************/

private int thiefsuccess = 0;

/*****************************************************************************
 * Soul identifying and autoloading
 *****************************************************************************/

string get_soul_id() { return "Thief Commands"; }

int query_cmd_soul() { return 1; }

/*****************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 *****************************************************************************/

mapping
query_cmdlist()
{
    seteuid(getuid());
    return ([
	     "backstab":"backstab",
	     "steal":"steal",
	     ]);
}

/*****************************************************************************
 * Here follows the functions. New functions should be added in alphabetic
 * order.
 ****************************************************************************/

/* the routine if something can attack something else, it defines the function
 * c_can_attack used further down. Checks for stuff like NO_ATTACK, Attacker
 * has met the victim and Discipline.
 */
#include "/d/Krynn/open/sys/combat.h"

/*
 * Global variables
 */


/********************* backstab *********************************************/
int 
peek_access(object ob)
{
    if (!living(ob) || ob->query_ghost() || ob == TP)
      return 0;
    else
      return 1;
}

/*
 * remove_hide_prop from attacker after a while no matter what
 */
static void
remove_hide_prop(object who, object enemy)
{
    if (who && enemy && E(who) == E(enemy) && who->query_prop(OBJ_I_HIDE))
    {
	who->remove_prop(OBJ_I_HIDE);
	who->catch_msg(enemy->query_The_name(who) + " manages to turn " +
		       "around to face you, you are no longer hidden!\n");
	enemy->catch_msg("You manage to turn around to face your enemy, " +
			 "it is " + who->query_art_name(enemy) + ".\n");
    }
    
}

static void
remember_backstab_attempt(object who, object to_remem)
{
    int i;
    i = who->query_prop(LIVE_I_GOT_BACKSTABBED);
    who->add_prop(LIVE_I_GOT_BACKSTABBED, i + 1);
}

/*
 * backstab someone
 */
int
backstab(string str)
{
    object spwiz;
    mixed *res, what;
    string damage, vb, str1, str2;
    object *p, *inv, enemy, *weapon;
    int perform, hurt, hit, where_wielded, i, bs_skill, hidden, aware;
    
    vb = query_verb();
    notify_fail(capitalize(vb) + " who with what?\n");
    
    if (!str)
      return 0;
    
    i = sscanf(str, "%s with %s", str1, str2);
    if (i != 2)
      return 0;
    
    /* p = CMDPARSE_ONE_ITEM(str1, "peek_access", "peek_access"); */
    p = parse_this(str1,"%l");
    
    bs_skill = TP->query_skill(SS_BACKSTAB);
    NF("Couldn't locate " + str1 + ".\n");
    if (!p || !sizeof(p))
      return 0;
/* commented to allow 'backstab elf' when there are 2 elves present.
   NF("You have to be specific, you can't backstab more than one " +
   "person at a time!\n")
   if (sizeof(p) > 1)
   return 0;
*/
    enemy = p[0];
    
    hidden = (!CAN_SEE_IN_ROOM(TP) || !CAN_SEE(enemy, TP));
    NF("You can only backstab when you're hidden from your victim!\n");
    if (!hidden)
      return 0;

    NF("You are too tired to backstab.\n");
    if (TP->query_fatigue() < 5)
      return 0;

    what = c_can_attack(enemy,vb);
    if (what)
    {
	NF(C(what));
	return 0;
    }
    
    /* inv = all_inventory(TP);
     * if (sizeof(inv))
     *  weapon = FIND_STR_IN_ARR(str2, inv);
     *
     * NF("You don't have a " + str2 + " to backstab with.\n");
     * if (!weapon || !sizeof(weapon))
     *  return 0;
     *
     * weapon = (object*)TP->query_weapon(-1) & weapon;
     */
    weapon = (object*)TP->query_weapon(-1);
    NF("You must wield the weapon to be able to backstab.\n");
    if (!weapon || !sizeof(weapon))
      return 0;

    weapon = FIND_STR_IN_ARR(str2, weapon);
    NF("You don't have a " + str2 + " to backstab with.\n");
    if (!weapon || !sizeof(weapon))
      return 0;

    where_wielded = (weapon[0]->query_wielded() == TP);
    if (!where_wielded)
      return 0;
    
    NF("You need a knife or a dagger to backstab with.\n");
    if (weapon[0]->weapon_type() != "knife")
      return 0;
    
    aware = enemy->query_skill(SS_AWARENESS) / 2;
/*calculate the newbie bonus here! */
    if (!enemy->query_npc() && enemy->query_average_stat() < 30)
    {
	aware += (35 - enemy->query_average_stat());
	aware += random(aware) / 2;
    }
    /*calculate the npc bonus here - or rather, the bonus for npcs without awareness :) */
    i = (enemy->query_stat(SS_INT) + enemy->query_stat(SS_WIS)) / 3;
    /* too high?? too low??*/
    if (enemy->query_npc() && enemy->query_base_skill(SS_AWARENESS == 0))
      aware = (i > 100 ? 100 : i);
    i = enemy->query_prop(LIVE_I_GOT_BACKSTABBED);
    aware += (i * i * 2);

    perform = F_BS_HIT(bs_skill, TP->query_stat(SS_DEX),
		       /*TP->query_skill(SS_WEP_KNIFE),  instead of dex?*/
		       aware, TP->query_skill(SS_DEFENCE));

    if (perform < -bs_skill)
    {
	write("You fail to backstab " + enemy->query_the_name(TP) +
	      ", and you are revealed.\n");
	TP->remove_prop(OBJ_I_HIDE);
	enemy->catch_msg(TP->query_Art_name(enemy) +
			 " lunges at you from behind, but misses.\n");
	TP->tell_watcher(QCNAME(TP) + " lunges at " + QTNAME(enemy) +
			 " from behind, but misses.\n", enemy);
	remember_backstab_attempt(enemy,TP);
	return 1;
    }
    else if (perform <= 0) 
      /*otherwise he will stay hidden and simply fails to backstab */
    {
	write("You fail to backstab " + enemy->query_the_name(TP) +
	      ", but you manage to stay hidden.\n");
	enemy->catch_msg(QCNAME(TP) + " lunges at you from behind, but misses.\n");
	TP->tell_watcher(QCTNAME(TP) + " lunges at " + QTNAME(enemy) +
			 " from behind, but misses.\n", enemy);
	remember_backstab_attempt(enemy,TP);
	return 1;
    }
    hit = F_BS_PEN(bs_skill, TP->query_skill(SS_WEP_KNIFE),
		   weapon[0]->query_pen(), TP->query_stat(SS_STR));

    res = (enemy->hit_me(hit, W_IMPALE, TP, -1 /*where_wielded*/));
    
    hurt = res[0];
    TP->add_fatigue(-3);

#ifdef NOT_MUDLIB_READY
    /* Info for special wizards */
    spwiz = find_living(L(DEBUG[0]));
    if (spwiz && !(spwiz->query_prop("_live_i_no_thief_info")))
      spwiz->catch_msg("BACKSTAB: " + TP->query_name() +
		       " \tEnemy: " + enemy->short(TP) +
		       " \tHit  : " + hit +
		       " \tHurt%: " + hurt +
		       " \tPhit : " + res[2] +
		       " \tDam  : " + res[3] + "\n");
    /* give wizzes special info */
    if (TP->query_wiz_level() && !TP->query_prop("_live_i_no_thief_info"))
      write("HIT  : " + hit + "\nHURT%: " + hurt + "\n" + 
	    "PHIT : " + res[2] + "\nDAM  : " + res[3] + "\n");
#endif /* NOT_MUDLIB_READY */
    if (hurt > 99)
      damage = "assassinated";
    else if (hurt > 70)
      damage = "massacred";
    else if (hurt > 45)
      damage = "hurt really badly";
    else if (hurt > 25)
      damage = "hurt rather badly";
    else if (hurt > 10)
      damage = "hurt";
    else if (hurt > 5)
      damage = "grazed";
    else if (hurt > 0)
      damage = "slightly hurt";
    else
      damage = "unhurt";
    if (hurt > 0)
    {
	TP->catch_msg("You sneak up on " + enemy->query_the_name(TP) +
		      " and " + PRONOUN(enemy) + " is " + damage + ".\n");
	enemy->catch_msg(QCNAME(TP) + " stabs your " + res[1] +
			 " from behind and you are " + damage + ".\n");
	TP->tell_watcher(QCTNAME(enemy) + " cries out in pain as " +
			 PRONOUN(enemy) + " is " + damage +
			 " by " + QTNAME(TP) + ".\n", enemy);
    }
    else
    {
	TP->catch_msg("You sneak up on " + enemy->query_the_name(TP) +
		      " and try to stab but " + PRONOUN(enemy) + " is " +
		      damage + ".\n");
	enemy->catch_msg(QCNAME(TP) + " stabs your " + res[1] + " from behind " +
			 "but you are " + damage + ".\n");
	TP->tell_watcher(QCTNAME(enemy) + " turns around irritated as " +
			 PRONOUN(enemy) + " is stabbed by " + QTNAME(TP) + 
			 " but remains " + damage + ".\n", enemy);
    }

    /* NEW: */
    weapon[0]->did_hit(where_wielded,res[1],res[0],enemy,W_IMPALE,res[2],res[3]);
    /* This may produce messages which we do not want.
     * On the other hand, this call is needed to allow eg. poisoned weapons to work correctly
     */

    if (i = TP->query_prop(OBJ_I_HIDE))
      TP->change_prop(OBJ_I_HIDE,
		      i - (E(TP)->query_prop(ROOM_I_HIDE)) - random(12));
    if (TP->query_prop(OBJ_I_HIDE) <= 0)
      remove_hide_prop(TP,enemy);
    else
      set_alarm(itof(3 + random(bs_skill/11)),0.0,"remove_hide_prop",TP,enemy);
    remember_backstab_attempt(enemy,TP);
    if ((int)enemy->query_hp() <= 0)
      enemy->do_die(TP);
    return 1;
}



/************************* steal ****************************************/

/* check_watchers_see_steal - check all uninvolved players in the room
 *                            if they noticed the steal.
 */
void
check_watchers_see_steal(object place, object from_who, object who,
			 int thief_value, object what)
{
    mixed tmp;
    object see;
    object *seers = FILTER_PLAYERS(all_inventory(E(who))) -
                    ({ who, from_who, 0 });
    object *watcher_list = ({});
    int i,j, value;

    if (!place)
      return;

    for(j=0;j<sizeof(seers);j++)
    {
	see = seers[j];
	value = 12 * see->query_skill(SS_AWARENESS) / 2;
	value += (see->query_wiz_level() ? 100000 : 0);
	i = (600 * see->query_intoxicated() / see->intoxicated_max());
	value -= (i > 0 ? i : -i);
	i = (200 * see->query_fatigue() / see->query_max_fatigue());
	value -= (100 - i);
	value -= (see->query_attack() ? 600 : 0);
	if (!CAN_SEE_IN_ROOM(see))
	  value -= 100;
	if (!CAN_SEE(see, who))
	  value -= 1000;
	if (!CAN_SEE(see, from_who))
	  value -= 1000;
	
	if (value > thief_value)
	{
	    if (from_who)
	      see->catch_msg("You notice " + who->query_the_name(see) +
			     " gently removing something from " +
			     from_who->query_the_name(see) +
			     ".\n");
	    else
	      see->catch_msg("You notice " + who->query_the_name(see) +
			     " gently removing something from " +
			     place->short() + ".\n");
	    if (who->query_skill(SS_AWARENESS) > see->query_skill(SS_AWARENESS) / 2 &&
		CAN_SEE(who,see))
	      watcher_list += ({ see });
	    /* if the watcher has a prop set do something with it.
	       the prop can be -1/0/1, or a function name.
	       if it's a function name, call it with:
	       watcher->function(thief,victim,object);
	       note that (victim != watcher) means you witnessed a theft.
	       
	       if it's 1, attack the thief.
	       */

	    see->hook_onlooker_stolen_object(who, from_who);
	    
	    tmp = see->query_prop(LIVE_M_ATTACK_THIEF);
	    if (stringp(tmp))
	      call_other(see,tmp,who,from_who,what);
	    else if (intp(tmp) && tmp > 0)
	    {
		see->command("say Stop it, you thief!!");

		/* TP->attack_object(see); */

		if (!see->query_attack())
		  see->command("kill " + TP->query_real_name());
	    }
	}
    }
    if (watcher_list && sizeof(watcher_list))
      who->catch_msg(C(COMPOSITE_LIVE(watcher_list)) + " seem" +
		     ((sizeof(watcher_list) > 1) ? "" : "s") +
		     " to have noticed the theft!\n");
}

/* remove_extra_skill - remove the extra awareness after some time again
 */
void
do_remove_extra_skill(object who)
{
    int i;

    if (!who)
      return;
    i = who->query_prop(VICTIM_I_ADDED_AWARENESS);
    if (i <= 1)
    {
	who->set_skill_extra(SS_AWARENESS,
			     who->query_skill_extra(SS_AWARENESS) -
			     AWARENESS_BONUS);
	who->remove_prop(VICTIM_I_ADDED_AWARENESS);
    }
    else
      who->add_prop(VICTIM_I_ADDED_AWARENESS, i-1);
}

/* we need this support function to calculate the total value of
 * a container (bag,pouch,sack etc.). It is important that not
 * only the value of the container itself is taken into account,
 * but also it's contents!
 */
int
query_internal_value(object what)
{
    int i, sum = 0;
    object *objs = deep_inventory(what);
    
    if (!objs || sizeof(objs) < 1)
      return 0;

    for(i=0;i<sizeof(objs);i++)
      if (!objs[i])
	sum += 0;
      else if (function_exists("create_heap", objs[i]))
	sum += objs[i]->heap_value();
      else if (function_exists("create_herb", objs[i]))
	sum += objs[i]->query_herb_value();
      else
	sum += objs[i]->query_value();
    
    return sum;
}


/* different kinds of object access their monetary value in
 * different ways. This function will try to pick the correct
 * form to query the value of the object.
 */
int
query_the_value(object obj)
{
    if (!obj)
      return 0;
    else if (function_exists("create_heap", obj))
      return obj->heap_value();
    else if (function_exists("create_herb", obj))
      return obj->query_herb_value();
    else if (function_exists("create_potion", obj))
      return obj->query_potion_value();
    else if (function_exists("create_container", obj))
      return obj->query_value() + query_internal_value(obj);
    else
      return obj->query_value();
}



/*
 * steal - Steal something from someone's inventory
 */
int
steal(string str)
{
#ifdef NOT_MUDLIB_READY
    mixed *la = ({});
    string logstr;
#endif /* NOT_MUDLIB_READY */
    string vb;
    mixed tmp, what;
    mixed *arr;
    int xp, moveresult = 0, bonus;
    object *p, place, *inv, victim;
    int res,thief_value, victim_value,i,pp_skill, aw_skill, success, caught;
    string str1, str2, str3, str4;

    vb = query_verb();
    notify_fail(capitalize(vb) + " what from where or who?\n");

    if (!str)
      return 0;

  /* figure out who and/or where to steal from */
    if (sscanf(str,"%s from %s",str1,str2) != 2)
      return 0;
    if (sscanf(str2,"%s of %s",str3,str4) == 2)
      str2 = str4;
    p = FILTER_CAN_SEE(all_inventory(E(TP)) - ({ TP, 0 }),TP);
    if (str2 == "here" || str2 == "ground" || str2 == "floor" ||
	str2 == "the floor" || str2 == "the ground")
    {
	place = E(TP);
	victim = 0;
    }
    else if (p && sizeof(p) && str2 == "someone")
    {
	victim = p[random(sizeof(p))];
	place = victim;
    }
    else
    {
	p = FIND_STR_IN_ARR(str2, p);
	if (!p)
	  return 0;
	if (!p || !sizeof(p))
	  return 0;
	else
	{
	    place = p[0];
	    if (place->query_prop(LIVE_I_IS))
	      victim = p[0];
	}
    }
    if (str3)
    {
	if (victim)
	  p = FIND_STR_IN_OBJECT(str3, victim);
	else
	  p = FIND_STR_IN_OBJECT(str3, place);
	if (!sizeof(p) || !function_exists("create_container", p[0]))
	  place = 0;
	else
	  place = p[0];
    }
/* 'victim' should be the person to steal from.
 * and 'place' should be the container to steal from.
 * 'victim' and 'place' can be identical, 'victim' can be 0.
 * 'place' should be specified and be a container.
 * if not, attempt the steal anyway, but you won't succeed.
 */
    /* first expand money in npcs */
    if (victim && victim->query_npc() &&
	member_array(OBJ_M_HAS_MONEY, victim->query_props()) != -1)
      MONEY_EXPAND(victim);
    /* now figure out what object the thief wants! */
    if (place)
    {
	if (victim)
	  p = deep_inventory(place);
	else
	  p = all_inventory(place);
	if (!p || !sizeof(p))
	  what = 0;
	else if (str1 == "something" || str1 == "item")
	  what = p[random(sizeof(p))];
	else
	{
	    if (sizeof(p))
	      p = FIND_STR_IN_ARR(str1, p);
	    if (!sizeof(p))
	      what = 0;
	    else
	      what = p[0];
	}
    }
/* 'what' contains the object to look for or 0.
 * if it's 0, the thief will try anyway, but
 * there is 0 chance s/he'll find something ;-)
 */
/* calculate thief value */
    thief_value = 10 * TP->query_skill(SS_PICK_POCKET);
#ifdef NOT_MUDLIB_READY
    la += ({TP->query_skill(SS_PICK_POCKET)});
#endif
    thief_value += (3 * MIN(TP->query_stat(SS_DEX),120));
#ifdef NOT_MUDLIB_READY
    la += ({MIN(TP->query_stat(SS_DEX),120)});
#endif

/* malus so you can't steal too frequently, this is probably the most
 * important factor of the formula!!!
 * New addition to this factor is that difficulty increases with each
 * steal attempt if you don't wait long enough.
 */
    i = TP->query_prop(LIVE_I_LAST_STEAL) - time() + 600;
    if (i > 0)
#ifdef NOT_MUDLIB_READY
    {
#endif
	thief_value -= i;
#ifdef NOT_MUDLIB_READY
	la += ({i});
    }
    else
      la += ({ 0 });
#endif
    TP->add_prop(LIVE_I_LAST_STEAL, time() + (i > 0 ? (i > 1200 ? 600 : i / 2) : 0));
    
/* does the player get a bonus for some reason? */
    bonus = TP->hook_thief_steal_bonus(victim, place, what);
    thief_value += (bonus);
#ifdef NOT_MUDLIB_READY
    la += ({bonus});
#endif
    
    thief_value += (str1 == "something" || str1 == "item" ? 400 : 0);
    thief_value += (str2 == "someone" ? 200 : 0);
    i = (sizeof(FILTER_OTHER_LIVE(all_inventory(E(TP)))) - 5) * 50;
    thief_value += (i > 200 ? 200 : i);
    thief_value -= (TP->query_attack() ? 600 : 0);
    thief_value += (what ? 0 : 300);
    thief_value += (victim ? 0 : 300);
    thief_value += (place ? 0 : 300);
    i =  (200 * TP->query_intoxicated() / TP->intoxicated_max());
    thief_value -= (i > 0 ? i : -i);
    i = (100 * TP->query_fatigue() / TP->query_max_fatigue());
    thief_value -= (100 - i);
    if (what)
      if (function_exists("create_heap", what))
      {
	  thief_value -= (what->heap_light() * 600);/*600*/
#ifdef NOT_MUDLIB_READY
	  la += ({what->heap_light() * 600});
#endif /* NOT_MUDLIB_READY */
	  thief_value -= (what->heap_weight() / 60);/*100*/
#ifdef NOT_MUDLIB_READY
	  la += ({what->heap_weight() / 60});
#endif /* NOT_MUDLIB_READY */
	  thief_value -= (what->heap_volume() / 60);/*100*/
#ifdef NOT_MUDLIB_READY
	  la += ({what->heap_volume() / 60});
#endif /* NOT_MUDLIB_READY */
      }
      else
      {
	  thief_value -= (what->query_prop(OBJ_I_LIGHT) * 600);/*600*/
#ifdef NOT_MUDLIB_READY
	  la += ({what->query_prop(OBJ_I_LIGHT) * 600});
#endif /* NOT_MUDLIB_READY */
	  thief_value -= (what->query_weight() / 60);/*100*/
#ifdef NOT_MUDLIB_READY
	  la += ({what->query_weight() / 60});
#endif /* NOT_MUDLIB_READY */
	  thief_value -= (what->query_volume() / 60);/*100*/
#ifdef NOT_MUDLIB_READY
	  la += ({what->query_volume() / 60});
#endif /* NOT_MUDLIB_READY */
      }
#ifdef NOT_MUDLIB_READY
    else
      la += ({ -1,-1,-1 });
#endif /* NOT_MUDLIB_READY */
    
    tmp = query_the_value(what)/(victim && objectp(victim) &&
				 victim->query_average_stat() ? 
				 victim->query_average_stat() :
				 100);
    /* modify the value of things according to the stat of the player:
     *   experienced players don't value things as highly as lower level players.
     *   newbies might even 'hold onto' really valuable stuff, so that should be considered.
     */
    thief_value -= tmp; 
#ifdef NOT_MUDLIB_READY
    la += ({ tmp });
#endif /* NOT_MUDLIB_READY */

    if (!CAN_SEE_IN_ROOM(TP) || !CAN_SEE(TP, victim))
    {
	thief_value /= 2;
#ifdef NOT_MUDLIB_READY
	la += ({ 0 });
#endif /* NOT_MUDLIB_READY */
    }
#ifdef NOT_MUDLIB_READY
    else
      la += ({ 1 });
#endif /* NOT_MUDLIB_READY */

/* value cannot be negative so that you can always steal from non-living objects */    
    if (thief_value <= 0)
      thief_value = 1;

/* calculate victim value */
    if (victim)
    {
	victim_value = 14 * victim->query_skill(SS_AWARENESS) / 2;
#ifdef NOT_MUDLIB_READY
	la += ({ victim->query_skill(SS_AWARENESS) / 2 });
#endif /* NOT_MUDLIB_READY */
	if (victim->query_npc() &&
	    victim->query_base_skill(SS_AWARENESS) == 0)
	  victim_value = 14 * (victim->query_stat(SS_INT) +
			       victim->query_stat(SS_WIS)) / 3;
#ifdef NOT_MUDLIB_READY
	la += ({ victim->query_stat(SS_INT) });
	la += ({ victim->query_stat(SS_WIS) });
#endif /* NOT_MUDLIB_READY */
	if (!victim->query_npc() && victim->query_average_stat() < 30)
	  victim_value += 6 * (35 - victim->query_average_stat());
/* does the victim get a bonus for some reason? */
	victim_value += (victim->hook_victim_no_steal_bonus(what));
	victim_value += (victim->query_wiz_level() ? 100000 : 0);
	victim_value += (victim->query_linkdead() ? 1000 : 0);
/*victim_value -= 50; statistics show this is not necessary.*/

	/*i = min(1000 + 10 * victim->query_stat(SS_DEX),2000);*/
	i = 1400;
	victim_value += (what && what->query_worn() ? i : 0);
	/*i = min(1500 + 13 * victim->query_stat(SS_STR),2800);*/
	i = 2000;
	victim_value += (what && what->query_wielded() ? i : 0);

	victim_value += (victim != place ? 10 : 0);

	if (victim->intoxicated_max())
	    i = (200 * victim->query_intoxicated() / victim->intoxicated_max());
	else
	    i = 0;
	victim_value -= (i > 0 ? i : -i);

	if (victim->query_max_fatigue())
	    i = (100 * victim->query_fatigue() / victim->query_max_fatigue());
	else
	    i = 0;
	victim_value -= (100 - i);
	
	if (!CAN_SEE_IN_ROOM(TP) || !CAN_SEE(victim, TP))
	{
	    victim_value /= 2;
#ifdef NOT_MUDLIB_READY
	    la += ({ 0 });
#endif /* NOT_MUDLIB_READY */
	}
#ifdef NOT_MUDLIB_READY
	else
	  la += ({ 1 });
#endif /* NOT_MUDLIB_READY */
    }
    else
    {
	victim_value = 0;
#ifdef NOT_MUDLIB_READY
	la += ({ -1,-1,-1,-1 });
#endif /* NOT_MUDLIB_READY */
    }
    
/* add some (better) randomization into the outcome here */
    thief_value += ((-thief_value/3) +
		    random(thief_value/3) +
		    random(thief_value/3));
    
#ifdef NOT_MUDLIB_READY
    la += ({ thief_value });
    la += ({ victim_value });

/* display info about the attempt to wizzes */
    if ((SECURITY)->query_wiz_rank(TP->query_real_name()) >= WIZ_NORMAL &&
	!(TP->query_prop("_live_i_no_thief_info")) &&
	member_array(TP->query_name(),DEBUG) == -1)
    {
	write("Wizinfo: Object: " + (!what ? "0" : 
				     file_name(what)) + "\n");
	write("         Victim: " + (!victim ? "0" : 
				     file_name(victim)) + "\n");
	write("         Place:  " + (!place ? "0" :
				     file_name(place)) + "\n");
	write("         Skill:  " + thief_value + "\n");
	write("         Aware:  " + victim_value + "\n");
    }
    tmp = find_living(L(DEBUG[0]));
    if (tmp && !(tmp->query_prop("_live_i_no_thief_info")))
    {
	tmp->catch_msg("STEAL: Thief: " + (!TP ? "0" : 
					   TP->query_name()));
	tmp->catch_msg(" \tObject: " + (!what ? "0" : 
					what->short()));
	tmp->catch_msg(" \tVictim: " + (!victim ? "0" : 
					victim->short()));
	tmp->catch_msg(" \tPlace:  " + (!place ? "0" :
					place->short()));
	tmp->catch_msg(" \tSkill:  " + thief_value);
	tmp->catch_msg(" \tAware:  " + victim_value + "\n");
    }
#endif /* NOT_MUDLIB_READY */


/* calculate the result of the attempt */
    res = thief_value - victim_value;
    if (res <= 0)
    {
	if (random(TP->query_stat(SS_DEX)) > 
	    random(victim->query_stat(SS_DEX)))
	{
	    success = 0;
	    caught = 0;
#ifdef NOT_MUDLIB_READY
	    la += ({ -1 });
#endif /* NOT_MUDLIB_READY */
	}
	else
	{
	    success = 0;
	    caught = 1;
#ifdef NOT_MUDLIB_READY
	    la += ({ 0 });
#endif /* NOT_MUDLIB_READY */
	}
    }
    else
    {
	res = random(res*res) - random(60000);
	/* 
	 * The formula will allow limited success chances only, even
	 * for high stat/skill differences between thief and victim.
	 * To get the list of basic success chances, execute:
	 *     exec
	 *     for(i=0;i<110;i+=10) { for(j=0;j<110;j+=10) {
	 *     k = 13*i-7*j;k=k>0?k*k:k;l=60000;
	 *     write("  " + (k<=0?0:(k>l?(100-50*l/k):(50*k/l)))); }
	 *     write("\n"); }
	 *     **
	 * The horizontal axis is the stat/skills of the victim, from
	 * 0 to 100 in steps of 10, vertically, it's the stat/skills
	 * of the thief, similarly distributed.
	 */
	if (res <= 0)
	{
	    if (random(TP->query_stat(SS_DEX)) > 
		random(victim->query_stat(SS_DEX)))
	    {
		success = 1;
		caught = 1;
#ifdef NOT_MUDLIB_READY
		la += ({ 2 });
#endif /* NOT_MUDLIB_READY */
	    }
	    else
	    {
		success = 0;
		caught = 0;
#ifdef NOT_MUDLIB_READY
		la += ({ -1 });
#endif /* NOT_MUDLIB_READY */
	    }
	}
	else
	{
	    success = 1;
	    caught = 0;
#ifdef NOT_MUDLIB_READY
	    la += ({ 1 });
#endif /* NOT_MUDLIB_READY */
	}
    }

#ifdef NOT_MUDLIB_READY    
/* generate specific log data to be able to make statistics */
    
    logstr = sprintf("%-11s: %@4d%@5d%@4d %O %O %O %O\n",TP->query_name(),la[0..12],
		     la[13..14],la[15..15],
		     (victim ? victim->short(TO) : "none"),
		     (victim ? file_name(victim) : "none"),
		     (what ? what->short(TO) : "none"),
		     (what ? file_name(what) : "none"));
#endif /* NOT_MUDLIB_READY */

/* evaluate messages sent to all involved */
    if (!place || !what)
    {
	TP->catch_msg("You couldn't find what you wanted to steal.\n");
    }
    else
    {
	if (success)
	{
	    tmp = what->query_prop(OBJ_M_NO_STEAL);
	    if (stringp(tmp))
	    {
		tmp = what->check_call(tmp);
		if (stringp(tmp))
		{
		    TP->catch_msg(tmp);		  
		    moveresult = -2;
		}
		else if (tmp)
		  moveresult = -1;
	    }
	    else if (functionp(tmp))
	      moveresult = -!!tmp();
	    else if (intp(tmp))
	      moveresult = -!!tmp;

	    if (!moveresult)
	      moveresult = what->move(TP);

	    if (moveresult)
	    {
		success = 0;
		/* Distinguish different move failures here */
		if (moveresult == 9)
		  TP->catch_msg("You cannot steal " +
				COMPOSITE_DEAD(what) + " from " +
				(victim ? victim->query_the_name(TP) :
				 "the " + place->short()) +
				", since the " + place->short() + " is closed!\n");
		else if (moveresult == 1 ||
			 moveresult == 4 ||
			 moveresult == 5 ||
			 moveresult == 8 ||
			 moveresult == 10)
		  TP->catch_msg("You cannot steal " +
				COMPOSITE_DEAD(what) + " from " +
				(victim ? victim->query_the_name(TP) :
				 "the " + place->short()) +
				", since you are unable to carry the item!\n");
		else if (moveresult == 2 ||
			 moveresult == 3 ||
			 moveresult == 6)
		  TP->catch_msg("You cannot steal " +
				COMPOSITE_DEAD(what) + " from " +
				(victim ? victim->query_the_name(TP) :
				 "the " + place->short()) +
				", since the item isn't allowed to leave it's place!\n");
		else if (moveresult == -1)
		  TP->catch_msg("You cannot steal " +
				COMPOSITE_DEAD(what) + " from " +
				(victim ? victim->query_the_name(TP) :
				 "the " + place->short()) +
				", since the item seems protected from thievery!\n");
		else if (moveresult >= -1 && moveresult != 7)
		  TP->catch_msg("You almost managed to get " +
				COMPOSITE_DEAD(what) + " from " +
				(victim ? victim->query_the_name(TP) :
				 "the " + place->short()) +
				" but a wrongness in the fabric of space prevented it.\n");
	    }
	    else
	    {
		thiefsuccess = 0;
		if (!caught)
		  thiefsuccess = victim_value;
		TP->hook_thief_stolen_object(what, victim, place);
		victim->hook_victim_stolen_object(what, TP, place);
		
		/*
		 * Give out general exp for successful stealing!
		 *
		 */
		if (!caught && victim_value > 0)
		{
		    arr = victim->query_prop(LIVE_AO_THIEF);
		    if (!arr)
		      arr = ({});
		    xp = (what ? F_STEAL_EXP(victim_value) : 0);
		    if (member_array(TP,arr) >= 0)
		      xp /= 3;
		    /* Stealing more than once from the same victim gives less XP */
		    else
		    {
			arr += ({ TP });
			victim->add_prop(LIVE_AO_THIEF, arr);
		    }
#ifndef NOT_MUDLIB_READY
		    setuid();
		    seteuid(getuid());
		    /*Exp giving is disabled for now. Let's hope this changes soon. */
		    /*TP->add_exp_general(xp);*/
#endif /* NOT_MUDLIB_READY */

#ifdef NOT_MUDLIB_READY
		    setuid();
		    seteuid(getuid());
		    log_file(STEAL_EXP_LOG, sprintf("%12s %11s: %5d %s %s (%s)\n",
						    ctime(time())[4..15],
						    TP->query_name(),
						    xp,
						    file_name(what),
						    victim->short(TO),
						    file_name(victim)),
			     STEAL_LOG_CYCLE);
#endif /* NOT_MUDLIB_READY */
		}
		
		TP->catch_msg("You managed to get " + 
			      COMPOSITE_DEAD(what) + " from " + 
			      (victim ? victim->query_the_name(TP) : 
			       place->short()) + ".\n");
	    }
	}
	else
	{
	    TP->catch_msg("You failed to get " + COMPOSITE_DEAD(what) +
			  " from " + (victim ? victim->query_the_name(TP) :
				      place->short()) + ".\n");
	}
    }
    
    if (!what)
      what = "something";
    if (victim && caught)
    {
	if (success)
	  victim->catch_msg("You notice that " + TP->query_the_name(victim) +
			    " has stolen " +
			    (objectp(what) ? COMPOSITE_DEAD(what) : what) +
			    " from you!\n");
	else
	  victim->catch_msg("You catch " + TP->query_the_name(victim) +
			    " trying to steal " +
			    (objectp(what) ? COMPOSITE_DEAD(what) : what) +
			    " from you!\n");
	
	TP->catch_msg("Ooops! " + victim->query_The_name(TP) +
		      " seems to have caught on to you!\n");
	
	/* if the victim has a prop set do something with it.
	   the prop can be -1/0/1, or a function name.
	   if it's a function name, call it with:
	   victim->function(thief,victim,object);
	   if it's 1, attack the thief. If it's -1 only attack if i'm the victim.
	   Be careful with this!!!! it may also be a means to start a fight
	   if the DIS isn't high enough. You may want to write a function
	   yourself if the victim is a creature and cannot talk but still
	   needs to attack thieves.
	   */
	
	/* Additionally: if the prop hasn't been set at all, always attack! */
	if (member_array(LIVE_M_ATTACK_THIEF,victim->query_props()) < 0 &&
	    victim->query_npc())
	{
	    victim->command("say Stop it, you thief!!");
	    
	    /* TP->attack_object(victim); */

	    if (!victim->query_attack())
	      victim->command("kill " + TP->query_real_name());
	}
	
	
	tmp = victim->query_prop(LIVE_M_ATTACK_THIEF);
	if (stringp(tmp))
	  call_other(victim,tmp,TP,victim,what);
	else if (intp(tmp) && tmp != 0)
	{
	    victim->command("say Stop it, you thief!!");

	    /* TP->attack_object(victim); */

	    if (!victim->query_attack())
	      victim->command("kill " + TP->query_real_name());
	}
	
	i = victim->query_prop(VICTIM_I_ADDED_AWARENESS);
	if (i == 0)
	{
	    victim->set_skill_extra(SS_AWARENESS,
				    victim->query_skill_extra(SS_AWARENESS)
				    + AWARENESS_BONUS);
	    set_alarm(300.0,0.0,"do_remove_extra_skill",victim);
	}
	victim->add_prop(VICTIM_I_ADDED_AWARENESS, i + 1);
    }
    check_watchers_see_steal(place, victim, TP, thief_value, what);
    

#ifdef NOT_MUDLIB_READY
/* write specific data to a log file to be able to make statistics */
 
    setuid();
    seteuid(getuid());
    if (logstr[80..88] != "none none")
      log_file(STEAL_ATTEMPT_LOG, ctime(time()) + " " + logstr, STEAL_LOG_CYCLE);
#endif /* NOT_MUDLIB_READY */

    return 1;
}

/* This is a function to check the ability of the thief in the
 * current steal attempt. A number between 0 and 100 is returned
 * describing the potency of the thief. A 1 means the guy managed
 * to steal something after killing it first ;-) and a 100 means
 * that someone just lost the weapon he had in his hand :)
 */
public nomask int
query_thief_success()
{
    int suc = thiefsuccess / 24;
    return (suc > 100 ? 100 : (suc < 0 ? 0 : suc));
}
