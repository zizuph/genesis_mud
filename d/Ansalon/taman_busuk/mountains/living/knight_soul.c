/*
* Solamnian_soul.c - Soul for the Knights of Solamnia 
* 
* This soul holds the special skills and certain commands (rescue,
    * block, help, mercy, wimpy) of the Solamnian Knights
* 
* Commands found in other files:
* Emotes - /d/Krynn/solamn/vin/knight/obj/sol_emotes1.h & sol_emotes2.h
* Non-emote commands - /d/Krynn/solamn/vin/knight/obj/sol_cmds.h
* Combat special - /d/Krynn/solamn/vin/knight/obj/kattack.h
*
*
* Made by Nick and Rastlin (When? Who knows? Haven't the Knights always
    * existed?) updated March 93 by Nick and Percy updated July 94 by Grace
* 
*
* Updates:
* -block and mercy commands Oct 94 by Aridor 
* -wimpy/whimpy commands Oct 94 by Aridor 
* -invite command Jan 95 by Aridor 
* -subdivision into lib files Dec 95 by Grace
* -emote changes Oct 95 by Morrigan
* -removal of bash and kick, replaced with kattack Nov 96 by Morrigan
* -removal of contact Nov 96 by Morrigan
* -moving of the invite command from the soul to the medal Nov 96 by 
*  Morrigan
*
*  Borrowed from the backup knights soul, as the new one doesn't have block - AK
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
#include "/d/Krynn/solamn/vin/knight/guild.h"

#define HELP_DIR     "/d/Krynn/solamn/vin/knight/help/"
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

    return ([    "kattack":"special", "katt":"special",
      "battlecries":"battlecries", "bcries":"battlecries",
      "block":  "block",
      "break!": "breakup",
      "combatcry": "battlecry", "kc2": "battlecry", "kcry2":"battlecry",
      "consider":"consider",
      "guildlist": "guildlist", "guildl":"guildlist",
      "help":   "help",
      "honour": "honour", "khonour": "honour", "khon":"honour",
      "kaccept": "kaccept", "kacc":"kaccept",
      "kadmire": "ksqadmire", "kadm":"ksqadmire",
      "kamused": "kamused", "kamu":"kamused",
      "kaspire": "ksqaspire", "kasp":"ksqaspire",
      "kassist": "kassist", "kass":"kassist",
      "kbow":   "kbow",
      "kbrook": "kbrook", "kbro":"kbrook",
      "kbrush":"kbrush",
      "kbye":   "kbye",
      "kchant": "kchant", "kchan":"kchant",
      "kchaste": "kchaste", "kchas":"kchaste",
      "kclasp": "kclasp", "kclas": "kclasp", "kcla":"kclasp",
      "kcount": "kcount", "kcou": "kcount", "kcoun":"kcount",
      "kcrown": "ksqcrown", "kcro":"ksqcrown",
      "kcry": "kcry", "kc1": "kcry", "kcry1":"kcry",
      "kdanger": "ksedanger", "kdan":"ksedanger",
      "kdeclare": "kdeclare", "koath":"koath",
      "kdeem": "kdeem", "kdee":"kdeem",
      "kdie":"kdie",
      "kdraw":"kplan",
      "kduel1": "kduel1", "kd1": "kduel1", "challenge":"kduel1",
      "kduel2": "kduel2", "kd2":"kduel2",
      "kfaith": "kcrfaith", "kfai":"kcrfaith",
      "kfirm":"ksefirm", "kfir":"ksefirm",
      "khand": "khand", "khan":"khand",
      "khelp":  "khelp",
      "klaf": "klaugh", "klaugh": "klaugh", "laf":"klaugh",
      "klead":"krolead",
      "kloyal": "kseloyal", "kloy":"kseloyal",
      "kmagic": "kmagic", "kmag":"kmagic",
      "knees":  "knees",
      "knightlist":"knightlist",
      "knod":   "knod",
      "knose": "knose", "knos": "knose", "kno":"knose",
      "kobey": "ksqnod",
      "koptions":"koptions", "kopt":"koptions",
      "kpraise": "kpraise", "kprais": "kpraise", "kpra":"kpraise",
      "kpray":  "kpray",
      "ks": "ks", "ksay":"ks",
      "ksage":"krosage",
      "ksalute2": "ksalute2", "ksal": "ksalute2", "kwep":"ksalute2",
      "ksing": "sing", "sing":"sing",
      "ksmooth": "ksmooth", "ksmo": "ksmooth", "ksmoo":"ksmooth",
      "ksomber": "ksomber", "ksom":"ksomber",
      "kswear": "kswear", "kvow":"kswear",
      "ksweat": "ksweat", "kwipe":"ksweat",
      "kswift": "kswift", "kswi": "kswift", "ksteal":"kswift",
      "kslap": "kslap", "kgauntlet":"kslap",
      "kstand": "kcrstand", "ksta":"kcrstand",
      "kshake": "kswshake", "ksha":"kswshake",
      "kstern": "kstern", "kste": "kstern", "kster": "kstern",
      "kstudy": "kstudy", "kstu": "kstudy", "kstud":"kstudy",
      "ktoast": "ktoast", "ktoa": "ktoast", "ktoas":"ktoast",
      "ktrace": "trace", "ktra": "trace", "ktrac":"trace",
      "kwar": "kswwar",
      "mercy": "mercy", "merciful": "merciful", "merciless":"merciless",
      "nsmile": "nsmile",
      "observe": "observe",
      "pledge": "pledge",
      "primary": "primary",
      "rescue": "rescue",
      "salute": "salute",
      "slap":   "kslap",
      "sponsorlist":"sponsorlist",
      "kthrust":"kthrust",
      "tend": "tend" ]);
}

int kdie_true(string str);
int kdie_fake(string str);

#include "/d/Krynn/solamn/vin/knight/obj/sol_cmds.h"  /* Non-emote commands */
#include "/d/Krynn/solamn/vin/knight/obj/sol_emotes1.h"  /* Emotes file */
#include "/d/Krynn/solamn/vin/knight/obj/sol_emotes2.h"  /* Emotes file */
#include "/d/Krynn/solamn/vin/knight/obj/kattack.h"
#include "/d/Krynn/solamn/vin/knight/obj/kdie.h"  /* Kdie ability */
#include "/d/Krynn/solamn/vin/knight/obj/observe.h"  /* Observe ability */
#include "/d/Krynn/solamn/vin/knight/obj/consider.h"  /* Consider ability */

/*
* Global variables
*/

/***********************************************************************
*  Here follows the functions.
*  New functions should be added in alphabetic order.
**********************************************************************/

/***********************************************************************
*  Guild-specific skills.
    *  New skills should be added in alphabetic order.
**********************************************************************/

/************************** block **************************************
* this command is a special attack of the occupational full knights.
* it allows to block one exit of a room for the enemy while fighting.
**********************************************************************/

int
block(string str)
{
    object          enemy, block, my_block;
    object          me = TP;
    string          the_exit;
    int             success, i;
    NF("What?\n");


/* Want to allow my npc to use it
    if (me->query_knight_level() < 2)
	return 0;
*/
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
	    block = clone_object(KOBJ + "block_object");
	    block->move(enemy, 1);
	}
	if (!block->add_blocked_exit(me, the_exit))
	    return 1;
	setuid();
	seteuid(getuid());
	my_block = clone_object(KOBJ + "block_control_obj");
	my_block->set_block_object(block);
	my_block->move(me, 1);
	me->catch_msg("You try to keep yourself between " +
	  enemy->query_the_name(me) + " and the " + the_exit +
	  " exit during this fight.\n");
	if (success < 20)
	    enemy->catch_msg(me->query_The_name(enemy) + " maneuvers " +
	      OBJECTIVE(me) + "self between you and the " +
	      the_exit + " exit.\n");
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


/********************* rescue **************************************/
int
rescue(string str)
{
    object          ob, *others, *obj;
    int             i, j, hp, max;
    string          rescue, *rescue2;

    NF("Rescue who?\n");
    if (!str || !sizeof(obj = parse_this(str, "%l")))
	return 0;
    ob = obj[0];
    NF("You cannot rescue because you can't see " + QTNAME(ob) + "!\n");
    if (!CAN_SEE(TP, ob))
	return 0;
    others = all_inventory(E(TP)) - ({ob}) - ({TP});

    NF(ob->query_The_name(TP)+" may not be rescued.\n");
    if (ob->query_prop(KNIGHT_I_NO_RESCUE))
	return 0;
    hp = ob->query_hp();
    max = ob->query_max_hp();

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

	    /* Less than 10 % health */
	    rescue = "Realizing that "+QTNAME(ob)+" is about to fall before "+
	    "the onslaught "+PRONOUN(ob)+"'s receiving at the hands of "+
	    QTNAME(others[i])+", you ";
	    if (hp > max / 10) /* Between 10% and 25% health */
		rescue = "You notice that "+QTNAME(ob)+" is beginning to to "+
		"buckle beneath "+QTNAME(others[i])+"'s attacks, and ";
	    if (hp > max / 4) /* Between 25% and 40% health */
		rescue = "Observing "+QTNAME(ob)+" steadily losing ground "+
		"to "+QTNAME(others[i])+", you ";
	    if (hp > max * 4 / 10) /* Between 40% and 60% health */
		rescue = "You see "+QTNAME(others[i])+" force "+QTNAME(ob)+
		" back a step and ";
	    if (hp > max * 3 / 5) /* Over 60% health */
		rescue = "Though "+QTNAME(ob)+" seems to be holding "+
		POSSESSIVE(ob)+" own against "+QTNAME(others[i])+", you ";

	    switch(random(6))
	    {
	    case 5:
		rescue2 = ({ "shout a command to "+QTNAME(ob)+", having "+
		  OBJECTIVE(ob)+" fall back so that you stand between "+
		  OBJECTIVE(ob)+" and "+QTNAME(others[i])+".\n",
		  "You fall back as "+QTNAME(TP)+" shouts a command to "+
		  "you, leaving "+OBJECTIVE(TP)+" standing between "+
		  "you and "+QTNAME(others[i])+".\n",
		  QCTNAME(ob)+" falls back at a command from "+QTNAME(TP)+
		  ", leaving "+QTNAME(TP)+" standing between "+
		  OBJECTIVE(ob)+" and "+QTNAME(others[i])+".\n",
		  QCTNAME(ob)+" falls back at a command from "+QTNAME(TP)+
		  ", who moves to stand between you and "+QTNAME(ob)+".\n" });
		break;
	    case 4:
		rescue2 = ({ "run toward "+QTNAME(others[i])+", forcing "+
		  OBJECTIVE(others[i])+" to engage in combat with you, "+
		  "rather than "+QTNAME(ob)+".\n",
		  QCTNAME(TP)+" runs toward "+QTNAME(others[i])+
		  ", forcing "+QTNAME(others[i])+" to engage in combat "+
		  "with "+OBJECTIVE(TP)+" rather than you.\n",
		  QCTNAME(TP)+" runs toward "+QTNAME(others[i])+
		  ", forcing "+QTNAME(others[i])+" to engage in combat "+
		  "with "+OBJECTIVE(TP)+" rather than "+QTNAME(ob)+".\n",
		  QCTNAME(TP)+" runs toward you, forcing you to engage "+
		  "in combat with "+OBJECTIVE(TP)+", rather than "+
		  QTNAME(ob)+".\n" });
		break;
	    case 3:
		rescue2 = ({ "shout out a Solamnic battlecry as you charge "+
		  "forward, drawing the attention of "+QTNAME(others[i])+".\n",
		  QCTNAME(TP)+" draws the attention of your enemy, "+
		  QTNAME(others[i])+", as "+PRONOUN(TP)+" charges forward, "+
		  "shouting out a Solamnic battlecry.\n",
		  QCTNAME(TP)+" draws the attention of "+QTNAME(others[i])+
		  " as "+PRONOUN(TP)+" charges forward, shouting out a " +
		  "Solamnic battlecry.\n",
		  QCTNAME(TP)+" draws your attention as "+PRONOUN(TP)+
		  " charges forward, shouting out a Solamnic battlecry.\n" });
		break;
	    case 2:
		rescue2 = ({ "maneuver so that "+QTNAME(others[i])+" is "+
		  "forced to fight you, and ignore "+QTNAME(ob)+".\n",
		  QCTNAME(TP)+" maneuvers so that "+QTNAME(others[i])+" is "+
		  "forced to fight "+OBJECTIVE(TP)+", and ignore you.\n",
		  QCTNAME(TP)+" maneuvers so that "+QTNAME(others[i])+" is "+
		  "forced to fight "+OBJECTIVE(TP)+", and ignore "+
		  QTNAME(ob)+".\n",
		  QCTNAME(TP)+" maneuvers so that you are forced to fight "+
		  "him, and ignore "+QTNAME(ob)+".\n" });
		break;
	    case 1:
		rescue2 = ({ "pull "+QTNAME(ob)+" out of harm's way, stepping "+
		  "forward to take the brunt of "+QTNAME(others[i])+"'s "+
		  "attacks.\n",
		  "Pulling you out of harm's way, "+QTNAME(TP)+" steps "+
		  "forward to take the brunt of "+QTNAME(others[i])+"'s "+
		  "attacks.\n",
		  "Pulling "+QTNAME(ob)+" out of harm's way, "+QTNAME(TP)+
		  " steps forward to take the brunt of "+QTNAME(others[i])+
		  "'s attacks.\n",
		  "Pulling "+QTNAME(ob)+" out of harm's way, "+QTNAME(TP)+
		  " steps forward to take the brunt of your attacks.\n" });
		break;
	    default:
		rescue2 = ({ "manage to distract "+QTNAME(others[i])+", "+
		  "enabling "+QTNAME(ob)+" to escape as "+PRONOUN(others[i])+
		  " turns to attack you.\n",
		  QCTNAME(others[i])+" turns to attack "+QTNAME(TP)+" as "+
		  QTNAME(TP)+" distracts "+OBJECTIVE(others[i])+", allowing "+
		  "you to escape.\n",
		  QCTNAME(others[i])+" turns to attack "+QTNAME(TP)+" as "+
		  QTNAME(TP)+" distracts "+OBJECTIVE(others[i])+", allowing "+
		  OBJECTIVE(ob)+" to escape.\n",
		  "You turn to attack "+QTNAME(TP)+" as "+PRONOUN(TP)+
		  " distracts you, allowing "+QTNAME(ob)+" to escape.\n" });
		break;
	    }

	    TP->attack_object(others[i]);
	    others[i]->attack_object(TP);
	    TP->catch_msg(rescue + rescue2[0]);
	    ob->catch_msg(rescue2[1]);
	    say(rescue2[2], ({ob, TP, others[i]}));
	    others[i]->catch_msg(rescue2[3]);

	    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 2000)
		TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 2000);

	    return 1;
	}
    TP->catch_msg("There is no one here hitting on " + QTNAME(ob) + ".\n");
    return 1;
}
/************************************************************************
*      Special attacks & Guild-specific skills end here
    ***********************************************************************/


/********************* help ********************************************/
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

/* Added by Morrigan Nov 96
* This command allows the Knight to set his preferred weapon and primary
* hand by typing <primary left/right>. The Knight will then swing with 
* the preferred weapon a percentage of the time which is defined in the
* /d/Krynn/solamn/guild/obj/lib/kattack.h file.
*/

int
primary(string which)
{
    object medal = P("pal_med", TP);
    int pr;
    string prs;

    setuid(); seteuid(getuid());
    NF("You don't have a medal, you should seek guidance.\n");
    if (!medal)
	return 0;

    if (!which)
    {
	pr = medal->query_primary();
	if (pr == 1)
	    prs = "left";
	else if (pr == 2)
	    prs = "random";
	else
	    prs = "right";
	write("-= Primary hand: "+prs+" =-\n");
	return 1;
    }

    NF("Set your primary hand as `right', `left', or `random'?\n");
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
    else if (which == "random")
    {
	medal->set_primary(2);
	write("-= Primary hand: random =-\n");
	return 1;
    }

    return 0;

}


/************************** koptions ******************************/
int
koptions(string str)
{
    string cry, pri, mer;
    object medal = P("pal_med", TP);

    if (TP->query_prop("_i_quiet_knight"))
	cry = "off";
    else
	cry = "on";

    if (medal->query_generous() == 1)
	mer = "on";
    else
	mer = "off";

    if (medal->query_primary() == 1)
	pri = "left";
    else if (medal->query_primary() == 0)
	pri = "right";
    else if (medal->query_primary() == 2)
	pri = "random";

    NF("Koptions what??\n");
    if (str)
	return 0;

    write("\n--==< Knight Options >==--\n\n");
    write("  Battlecries: "+cry+" \n");
    write("        Mercy: "+mer+" \n");
    write("      Primary: "+pri+" \n\n");
    return 1;
}

/**************************** battlecries ********************************/
/* This is a command to disable the default battlecries used in kattack, due */
/* To complains from people who wanted to be mute. */
int
battlecries(string str)
{
    string tmp;

    if (TP->query_prop("_i_quiet_knight"))
	tmp = "off";
    else
	tmp = "on";

    if (!str)
    {
	write("-= Battlecries: "+tmp+" =-\n");
	return 1;
    }

    if (str == "off")
    {
	write("-= Battlecries: off =-\n");
	if (!TP->query_prop("_i_quiet_knight"))
	    TP->add_prop("_i_quiet_knight", 1);
	return 1;
    }

    if (str == "on")
    {
	write("-= Battlecries: on =-\n");
	if (TP->query_prop("_i_quiet_knight"))
	    TP->remove_prop("_i_quiet_knight");
	return 1;
    }

    NF("What? Use 'battlecries <on/off>'.\n");
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
