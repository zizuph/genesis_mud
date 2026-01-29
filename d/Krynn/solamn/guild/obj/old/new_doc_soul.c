/*
 * Solamnian_soul.c
 * 
* This soul holds the special skills and certain commands ( kattack, rescue,
 * block, help, invite, mercy, whimpy) of the Solamnian Knights
 * 
 * Guild Emotions/Feelings are to be found in: -->
 * /d/Krynn/solamn/guild/obj/lib/sol_emotes.h -->
 * /d/Krynn/solamn/guild/obj/lib/sol_e2.h
 * 
 * Non-emote-related commands are to be found in: (break!, contact, expel,
 * guildlist, leave, knightlist, sponsorlist) -->
 * /d/Krynn/solamn/guild/obj/lib/sol_cmds.h
 * 
 * 
 * 
 * Made by Nick and Rastlin (When? Who knows? Haven't the Knights always
 * existed?) updated March 93 by Nick and Percy updated July 94 by Grace
 * 
 * block and mercy commands Oct 94 by Aridor wimpy/whimpy commands Oct 94 by
 * Aridor invite command Jan 95 by Aridor subdivision into lib files Dec 95
 * by Grace
 * 
 */

#pragma save_binary

inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <formulas.h>
#include <options.h>
#include <state_desc.h>
#include "/d/Krynn/open/sys/combat.h"
#include "../guild.h"

#define HELP_DIR    "/d/Krynn/solamn/guild/log/help_dir/"
#define KNIGHT_HITS "k_knight_hits"
#define DELAY       5

#define NORMAL_EXITS ({"north","south","east","west","up","down","enter",\
			 "out","northwest","northeast","southwest","southeast"})
#define TRANSLATE_EXIT (["n":"north",\
			 "s":"south",\
			 "e":"east",\
			 "w":"west",\
			 "u":"up",\
			 "d":"down",\
			 "se":"southeast",\
			 "sw":"southwest",\
			 "ne":"northeast",\
			 "nw":"northwest"])

/********************************************************************
 * Soul identifying and autoloading
 ********************************************************************/

string
get_soul_id()
{
    return "Solamnian Knight";
}

int
query_cmd_soul()
{
    return 1;
}

/***********************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 ***********************************************************************/

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());
return ([ "kattack":"special", "katt":"special",
	     "combatcry": "battlecry", "kc2": "battlecry", "kcry2":"battlecry",
	     "block":  "block",
	     "break!": "breakup",
	     "flex":   "flex",
	     "guildlist": "guildlist", "guildl":"guildlist",
	     "help":   "help",
	     "honour": "honour", "khonour": "honour", "khon":"honour",
	     "kaccept": "kaccept", "kacc":"kaccept",
	     "kamused": "kamused", "kamu":"kamused",
	     "kassist": "kassist", "kass":"kassist",
	     "kbow":   "kbow",
	     "kbrook": "kbrook", "kbro":"kbrook",
	     "kbye":   "kbye",
	     "kchant": "kchant", "kchan":"kchant",
	     "kchaste": "kchaste", "kchas":"kchaste",
	     "kclasp": "kclasp", "kclas": "kclasp", "kcla":"kclasp",
	     "kcount": "kcount", "kcou": "kcount", "kcoun":"kcount",
	     "kcry": "kcry", "kc1": "kcry", "kcry1":"kcry",
	     "kdeclare": "kdeclare", "koath":"koath",
	     "kdeem": "kdeem", "kdee":"kdeem",
	     "kdie":   "kdie",
	     "kduel1": "kduel1", "kd1": "kduel1", "challenge":"kduel1",
	     "kduel2": "kduel2", "kd2":"kduel2",
	     "khand": "khand", "khan":"khand",
	     "khelp":  "khelp",
	     "klaf": "klaugh", "klaugh": "klaugh", "laf":"klaugh",
	     "kmagic": "kmagic", "kmag":"kmagic",
	     "knees":  "knees",
	     "knod":   "knod",
	     "knose": "knose", "knos": "knose", "kno":"knose",
	     "kpraise": "kpraise", "kprais": "kpraise", "kpra":"kpraise",
	     "kpray":  "kpray",
	     "ks": "ks", "ksay":"ks",
	     "ksalute2": "ksalute2", "ksal": "ksalute2", "kwep":"ksalute2",
	     "ksmooth": "ksmooth", "ksmo": "ksmooth", "ksmoo":"ksmooth",
	     "ksomber": "ksomber", "ksom":"ksomber",
	     "kswear": "kswear", "kvow":"kswear",
	     "ksweat": "ksweat", "kwipe":"ksweat",
	     "kswift": "kswift", "kswi": "kswift", "ksteal":"kswift",
	     "kslap": "kslap", "kgauntlet":"kslap",
	     "kaspire": "ksqaspire", "kasp":"ksqaspire",
	     "kadmire": "ksqadmire", "kadm":"ksqadmire",
	     "kobey": "ksqnod",
	     "kcrown": "ksqcrown", "kcro":"ksqcrown",
	     "kloyal": "kseloyal", "kloy":"kseloyal",
	     "kdanger": "ksedanger", "kdan":"ksedanger",
	     "kfirm":"ksefirm", "kfir":"ksefirm",
	     "kfaith": "kcrfaith", "kfai":"kcrfaith",
	     "kstand": "kcrstand", "ksta":"kcrstand",
	     "kshake": "kswshake", "ksha":"kswshake",
	     "kwar": "kswwar",
	     "klead":"krolead",
	     "ksage":"krosage",
	     "kstudy": "kstudy", "kstu": "kstudy", "kstud":"kstudy",
	     "ktoast": "ktoast", "ktoa": "ktoast", "ktoas":"ktoast",
	     "ktrace": "trace", "ktra": "trace", "ktrac":"trace",
	     "knightlist":"knightlist",
	     "leave!": "leave",
	     "mercy": "mercy", "merciful": "merciful", "merciless":"merciless",
	     "nsmile": "nsmile",
	     "pledge": "pledge",
            "primary": "primary",
	     "rescue": "rescue",
	     "salute": "salute",
	     "ksing": "sing", "sing":"sing",
	     "slap":   "kslap",
	     "sponsorlist":"sponsorlist",
	     "tend":   "tend",
	     /* "whimpy":"whimpy","wimpy":"whimpy", */
	     ]);
}

#include "/d/Krynn/solamn/guild/obj/lib/sol_cmds.h"	/* NON-EMOTE COMMANDS */
#include "/d/Krynn/solamn/guild/obj/lib/sol_emotes_test.h"	/* EMOTES kA-kO */
#include "/d/Krynn/solamn/guild/obj/lib/sol_e2_test.h"
#include "/d/Krynn/solamn/guild/obj/lib/kattack.h"

/*
 * Global variables
 */


/***********************************************************************
 *  Here follows the functions.
 *  New functions should be added in alphabetic order.
 **********************************************************************/

/**********************************************************************
 *  Guild-specific skills.
 *  New skills should be added in alphabetic order.
 **********************************************************************/

/********************* rescue **************************************/
int
rescue(string str)
{
    object          ob, *others, *obj;
    int             i, j;

    NF("Rescue who?\n");
    if (!str || !sizeof(obj = parse_this(str, "%l")))
      return 0;
    ob = obj[0];
    NF("You cannot rescue because you can't see " + QTNAME(ob) + "!\n");
    if (!CAN_SEE(TP, ob))
      return 0;
    others = all_inventory(E(TP)) - ({ob}) - ({TP});
    for (i = 0; i < sizeof(others); i++)
      if (others[i]->query_attack() == ob) 
      {
	  j = F_RESCUE(TP, ob);
	  if (random(RESCUE_HIT) > random(j)) 
	  {
	      TP->catch_msg("You fail to rescue " + QTNAME(ob) + ".\n");
	      ob->catch_msg(QCTNAME(TP) +
			    " tries to rescue you but fails.\n");
	      say(QCTNAME(TP) + " fails to rescue " + QTNAME(ob) + ".\n",
		  ({ob, TP}));
	      return 1;
	  }
	  TP->attack_object(others[i]);
	  others[i]->attack_object(TP);
	  TP->catch_msg("You heroically rescue " + QTNAME(ob) + ".\n");
	  say(QCTNAME(TP) + " heroically rescues " + QTNAME(ob) + ".\n",
	      ({ob, TP}));
	  ob->catch_msg(QCTNAME(TP) + " rescues you heroically.\n");

	  if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 2000)
	    TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 2000);

	  return 1;
      }
    TP->catch_msg("There is no one here hitting on " + QTNAME(ob) + ".\n");
    return 1;
}


/************************** block ******************************************
 * this command is a special attack of the occupational full knights.
 * it allows to block one exit of a room for the enemy while fighting.
 **************************************************************************/
int
block(string str)
{
    object          enemy, block, my_block;
    object          me = TP;
    string          the_exit;
    int             success, i;
    NF("What?\n");
    /* Only occupational real knights can use this. */
    if (me->query_knight_level() < 3)
      return 0;
    NF("You are currently not in a fight!\n");
    enemy = me->query_attack();
    if (!enemy || E(enemy) != E(me))
      return 0;
    NF("Block which exit?\n");
    if (!str)
      return 0;

    if (strlen(str) <= 2)
      the_exit = TRANSLATE_EXIT[str];
    if (!the_exit)
      the_exit = str;

    if (block = present("knight_block_object", enemy)) 
    {
	if (block->query_blocked_exit(TP) == the_exit) 
	{
	    NF("You are already blocking the " + the_exit + " exit.\n");
	    return 0;
	    /*
	     * Below is what it was, but since we don't want the use of
	     * unnecessary do commands, we'll be mean here. We return 0 to
	     * stop the execution of a do command.
	     */
	    write("You are already blocking the " + the_exit + " exit.\n");
	    return 1;
	}
    }
    if (my_block = present(me->query_real_name() + "_block_object", enemy)) 
    {
	my_block->remove_blocked_exit(TP, "You decide to leave your " +
				      "blocking position.\n");
	if (the_exit == "off")
	  return 1;
    }
    if (the_exit == "off") 
    {
	write("You are not trying to block currently.\n");
	return 1;
    }
    NF("No such exit, or exit cannot be blocked.\n");
    if (member_array(the_exit, NORMAL_EXITS) == -1)
      return 0;

    if (block = present("knight_block_object", enemy)) 
    {
	if (block->query_blocked_exit(TP) == the_exit) 
	{
	    write("You are already blocking the " + the_exit + " exit.\n");
	    return 1;
	}
    }
    success = (random(2 * me->query_skill(SS_BLOCK)) -
	       random((enemy->query_stat(SS_INT) +
		       enemy->query_skill(SS_AWARENESS)) / 2));
    if (success > 0) 
    {
	if (!block) 
	{
	    setuid();
	    seteuid(getuid());
	    block = clone_object(OBJ + "block_object");
	    block->move(enemy, 1);
	}
	if (!block->add_blocked_exit(me, the_exit))
	  return 1;
	setuid();
	seteuid(getuid());
	my_block = clone_object(OBJ + "block_control_obj");
	my_block->set_block_object(block);
	my_block->move(me, 1);
	me->catch_msg("You try to keep yourself between " +
		      enemy->query_the_name(me) + " and the " + the_exit +
		      " exit during this fight.\n");
	if (success < 20)
	  enemy->catch_msg(me->query_The_name(enemy) + " maneuvers " +
			   OBJECTIVE(me) + "self between you and the " +
			   the_exit + " exit.\n");
	/*
	 * if (!(P("pal_med",me)->query_generous())) {
	 * P("pal_med",me)->set_generous(1); me->catch_msg("You are now a
	 * mercyful fighter!\n"); }
	 */
    }
    else 
    {
	me->catch_msg("You fail to maneuver yourself into position to " +
		      "block the " + the_exit + " exit.\n");
	enemy->catch_msg("You notice " + me->query_the_name(enemy) +
			 " trying to move into a certain position, but " +
			 "you are able to prevent this.\n");
    }
    return 1;
}

/*********************************************************************
 *      Special attacks & Guild-specific skills end here
 *********************************************************************/

/********************* help *************************************************/
int
help(string str)
{
    string subject, filename;
    
    if (!str)
      return 0;
    
    if (sscanf(str, "guild %s", subject) != 1)
      if (sscanf(str, "knight %s", subject) != 1)
	if (sscanf(str, "knights %s", subject) != 1)
	  return 0;


    filename = HELP_DIR + subject;
    if (file_size(filename) > 0) 
    {
	setuid();
	seteuid(getuid());
	cat(filename);
	return 1;
    }
    NF("No help on that subject I'm afraid.\n");
    return 0;
}

/******************************************************************************
 *           KNIGHTS have a special invite command!
 * Black Knights may not lead a team (invite) at all! Knights who have recently
 * Pkilled have a skill set with the age. They may not lead a team for 2 days
 * (AGE!) or until a conclave or assistant has pardoned them.
 *****************************************************************************/
int
invite(string name)
{
    object         *member_list, member;

    /* this is the knight specific part */

    /* if (TP->query_knight_level() == L_BROSE)  */
    //Line above doesn 't seem to cut it, using int instead of macro
      if (TP->query_knight_level() == 1) 
      {
	  write("Knights of the Black Rose have disgraced the Knights of Solamnia " +
		"and may not lead any teams.\n");
	  return 1;
      }
    if (REALAGE(TP) < TP->query_skill(SS_DISGRACED))
    {	/* 2 days playing time! */
	write("You have disgraced the Knights of Solamnia and may not lead a team currently.\n");
	return 1;
    }
    else
      TP->remove_skill(SS_DISGRACED);
    
    /* end knight specific part */
    
    if (!name) 
    {
	member_list = (object *) this_player()->query_invited();
	if (!member_list || !sizeof(member_list))
	  write("You have not invited anyone to join you.\n");
	else
	{
	    if (sizeof(member_list) == 1)
	      write("You have invited " + member_list[0]->short() +
		    ".\n");
	    else 
	    {
		name = (string) COMPOSITE_FILE->desc_live(member_list);
		write("You have invited " +
		      (string) LANG_FILE->word_num(sizeof(member_list)) +
		      " people:\n");
		write(break_string(name, 76, 3));
	    }
	}
	return 1;
    }
    member = find_player(name);
    
    if (!member || (member && !present(member, environment(this_player()))))
    {
	notify_fail(capitalize(name) +
		    " is not a good potential team member!\n");
	return 0;
    }
    if (!CAN_SEE(this_player(), member)) 
    {
	notify_fail("Invite whom?");
	return 0;
    }
    if (this_player()->query_leader()) 
    {
	notify_fail("You can't be a leader when you have a leader!\n");
	return 0;
    }
    if ((!member->query_met(this_player())) ||
	(!this_player()->query_met(member)))
      return (notify_fail("You have not been introduced!\n"), 0);
    
    if (member == this_player()) 
    {
	notify_fail("You do not need an invitation to your own team!\n");
	return 0;
    }
    this_player()->team_invite(member);
    member->catch_msg(this_player()->query_The_name(member) +
		      " invites you to join " + this_player()->query_possessive() +
		      " team.\n");
    this_player()->reveal_me(1);
    member->reveal_me(1);
    
    write("Ok.\n");
    return 1;
}



int
primary(string which)
{
    object medal = P("pal_med", TP);
    int pr;
    string prs;
    
    NF("You don't have a medal, you should seek guidance.\n");
    if (!medal)
      return 0;
    
    if (!which)
    {
	pr = medal->query_primary();
	if (pr == 1)
	  prs = "left";
	else
	  prs = "right";
	write("-= Primary hand: "+prs+" =-\n");
	return 1;
    }
    
    NF("Set your primary hand as `right' or `left'?\n");
    if (which == "left")
    {
	medal->set_primary(1);
	write("-= Primary hand: left =-\n");
	return 1;
    }
    else if (which == "right")
    {
	medal->set_primary(0);
	write("-= Primary hand: right =-\n");
	return 1;
    }
    
    return 0;
    
}


/********************* mercy ************************************************/
int
mercy(string str)
{
    string          what;
    object          medal = P("pal_med", TP);
    
    NF("You don't have a medal, you should seek guidance.\n");
    if (!medal)
      return 0;
    if (!str)
    {
	what = (medal->query_generous() ? "ful" : "less");
	write("You are currently a merci" + what + " fighter!\n");
	return 1;
    }
    NF("Mercy on or off?\n");
    if (str == "yes" || str == "on")
      medal->set_generous(1);
    else if (str == "no" || str == "off")
      medal->set_generous(0);
    else
      return 0;
    
    what = (medal->query_generous() ? "ful" : "less");
    write("You are now a merci" + what + " fighter!\n");
    allbb(" gets a merci" + what + (medal->query_generous() ? " smile" :
				    " expression") + " on " + POSSESSIVE(TP) +
	  " face.");
    return 1;
}

int
merciful()
{
    return mercy("yes");
}

int
merciless()
{
    return mercy("no");
}



/****************************************************************************
 *  wimpy/whimpy, Knights may only set a rather low wimpy.
 * NOTE: SHOULD THE ORIGINAL WIMPY CODE EVER BE CHANGED, BE SURE TO ADJUST
 *       THIS CODE, TOO!!!!!!!!!
 ***************************************************************************/
int
whimpy(string str)
{
    string          how, *health = SD_HEALTH;
    int             wi, lim;
    
    if (!str)
    {
	wi = this_player()->query_whimpy();
	if (wi == 0)
	{
	    write("You are not wimpy at all.\n");
	    return 1;
	}
	if (wi > 99)
	  wi = 99;
	wi = wi * sizeof(health) / 100;
	write("You are wimpy at: '" + health[wi] + "'.\n");
	return 1;
    }
    if (str == "brave")
    {
	this_player()->set_whimpy(0);
	write("Brave mode.\n");
	return 1;
    }
    wi = member_array(str, health);
    
    if (wi < 0)
    {
	notify_fail("No such health descriptions (" + str + ") Available:\n" +
		    break_string(COMPOSITE_WORDS(health) + ".", 70, 3) + "\n");
	return 0;
    }
    wi = (100 * (wi + 1)) / sizeof(health);
    if (wi > 99)
      wi = 99;
    how = health[sizeof(health) * wi / 100];
    lim = WIMPY_LIMIT[TP->query_knight_level()] +
      WIMPY_LIMIT2[TP->query_knight_sublevel()];
    if (lim > 99)
      lim = 99;
    if (wi > lim)
    {
	wi = lim;
	if (health[sizeof(health) * wi / 100] != how)
	  write("This wimpy level is not allowed for a Knight of " +
		"Solamnia!\n");
    }
    how = health[sizeof(health) * wi / 100];
    write("You are now wimpy at: '" + how + "'.\n");
    TP->set_whimpy(wi);
    return 1;
}
