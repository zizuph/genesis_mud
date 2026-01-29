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
 * Louie April 2006 - Added command for Cavalry to ksummon their steeds.
 *
 * Navarre April 2007, changed tend emote to ktend to avoid conflict
 *                     with smiths in the realm.
 */

#pragma save_binary

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

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

#define HELP_DIR     "/d/Krynn/solamn/vin/knight/help/"
#define KNIGHT_HITS "k_knight_hits"
#define DELAY       5

#define NORMAL_EXITS ({"north","south","east","west","up","down","enter", \
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

public mapping
query_ability_map()
{
    return ([
    "block" : "/d/Genesis/specials/std/block",
     ]);
}

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());

    return ([
	     "kattack":"special",
	     "katt":"special",
	     "battlecries":"battlecries",
	     "bcries":"battlecries",
         "block":"do_ability",
	     "break!": "breakup",
	     "combatcry": "battlecry",
	     "kc2": "battlecry",
	     "kcry2":"battlecry",
	     "consider":"consider",

	     "guildlist": "guildlist",
	     "guildl":"guildlist",

	     "help":   "help",

	     "honour": "honour", "khonour": "honour", "khon":"honour",
	     "kaccept": "kaccept", "kacc":"kaccept",

	     "kadmire": "ksqadmire", "kadm":"ksqadmire",
	     "kamused": "kamused", "kamu":"kamused",
	     "kaspire": "ksqaspire", "kasp":"ksqaspire",
	     "kassist": "kassist", "kass":"kassist"
	     ,
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
	     "kdismiss":"kdismiss","kdis":"kdismiss",
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
	     "ksummon":"ksummon","ksum":"ksummon",
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
	     "squirepromote":"squirepromote",
	     "squiredemote":"squiredemote",
	     "kthrust":"kthrust",
	     "ktend": "ktend",
	     "kauto": "kauto",
	     ]);
}

int kdie_true(string str);
int kdie_fake(string str);

#include "sol_cmds.h"  /* Non-emote commands */
#include "sol_emotes1.h"  /* Emotes file */
#include "sol_emotes2.h"  /* Emotes file */
#include "kattack.h"
#include "kdie.h"  /* Kdie ability */
#include "observe.h"  /* Observe ability */
#include "consider.h"  /* Consider ability */
/*
*/
#include "ksummon.h" /*summon steed*/
#include "kdismiss.h" /*dismiss steed */
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


/********************* rescue **************************************/
int
rescue(string str)
{
    object *obs;
    object ob, foe, *attackers, rescue_ob;
    int    i, j, hp, max;
    string rescue, *rescue2;
    string t1, t2;

    NF("Rescue whom [from what]?\n");
    if (!str)
	return 0;

    if (sscanf(str, "%s from %s", t1, t2) == 2)
    {
	obs = FIND_STR_IN_OBJECT(t1, environment(this_player()));
    } else {
	obs = FIND_STR_IN_OBJECT(str, environment(this_player()));
    }

    if (!sizeof(obs))
	return 0;

    ob = obs[0];

    if (ob == TP)
    {
	NF("You try to rescue yourself but fail.\n");
	return 0;
    }

    if (!CAN_SEE(this_player(), ob))
    {
	return 0;
    }

    if (!living(ob))
    {
	notify_fail("You can only rescue living things.\n");
	return 0;
    }

    if ((time() - TP->query_prop(RESCUE_TIME)) < RESCUE_INTERVAL)
    {
	NF("You are not yet ready to rescue again.\n");
	return 0;
    }

    if (TP->query_prop("_kcharge_preparing"))
    {
	NF("You are too far away from the battle to rescue " +
	    ob->query_the_name(TP) + "!\n");
	return 0;
    }

    if (ob->query_prop(KNIGHT_I_NO_RESCUE))
    {
	NF(ob->query_The_name(TP) + " may not be rescued.\n");
	return 0;
    }

    attackers = filter(all_inventory(environment(this_player())),
	&operator(==)(ob) @ &->query_attack());

    if (!sizeof(attackers))
    {
	notify_fail(ob->query_The_name(TP) + " is not under attack.\n");
	return 0;
    }

    if (member_array(TP, attackers) >= 0)
    {
	notify_fail("But you are attacking " + ob->query_The_name(TP) + ".\n");
	return 0;
    }

    /* We want to rescue a specific foe */
    if (stringp(t2))
    {
	obs = FIND_STR_IN_ARR(t2, attackers);
	if (!sizeof(obs))
	{
	    notify_fail("You find no such foe attacking " +
		ob->query_the_name(TP) + ".\n");
	    return 0;
	}

	foe = obs[0];
    } else {
	foe = attackers[random(sizeof(attackers))];
    }

    TP->add_prop(RESCUE_TIME, time());

    hp = ob->query_hp();
    max = ob->query_max_hp();


    j = F_RESCUE(TP, foe);

    if (random(RESCUE_HIT) > random(j))
    {
	TP->catch_msg("You fail to rescue " + QTNAME(ob) + ".\n");
	ob->catch_msg(QCTNAME(TP) + " tries to rescue you but fails.\n");
	say(QCTNAME(TP) + " fails to rescue " + QTNAME(ob) + ".\n",
	    ({ ob, TP}));
	return 1;
    }

    /* Less than 10 % health */
    rescue = "Realizing that "+QTNAME(ob)+" is about to fall before "+
	"the onslaught "+PRONOUN(ob)+"'s receiving at the hands of "+
	QTNAME(foe)+", you ";
    if (hp > max / 10) /* Between 10% and 25% health */
	rescue = "You notice that "+QTNAME(ob)+" is beginning to to "+
	    "buckle beneath "+QTNAME(foe)+"'s attacks, and ";
    if (hp > max / 4) /* Between 25% and 40% health */
	rescue = "Observing "+QTNAME(ob)+" steadily losing ground "+
	    "to "+QTNAME(foe)+", you ";
    if (hp > max * 4 / 10) /* Between 40% and 60% health */
	rescue = "You see "+QTNAME(foe)+" force "+QTNAME(ob)+
	    " back a step and ";
    if (hp > max * 3 / 5) /* Over 60% health */
	rescue = "Though "+QTNAME(ob)+" seems to be holding "+
	    POSSESSIVE(ob)+" own against "+QTNAME(foe)+", you ";

    switch(random(6))
    {
    case 5:
	rescue2 =
	    ({ "shout a command to "+QTNAME(ob)+", having "+
		   OBJECTIVE(ob)+" fall back so that you stand between "+
		   OBJECTIVE(ob)+" and "+QTNAME(foe)+".\n",
		   "You fall back as "+QTNAME(TP)+" shouts a command to "+
		   "you, leaving "+OBJECTIVE(TP)+" standing between "+
		   "you and "+QTNAME(foe)+".\n",
		   QCTNAME(ob)+" falls back at a command from "+QTNAME(TP)+
		   ", leaving "+QTNAME(TP)+" standing between "+
		   OBJECTIVE(ob)+" and "+QTNAME(attackers[i])+".\n",
		   QCTNAME(ob)+" falls back at a command from "+QTNAME(TP)+
		   ", who moves to stand between you and "+QTNAME(ob)+".\n" });
	break;
    case 4:
	rescue2 = ({ "run toward " + QTNAME(foe)+", forcing "+
			 OBJECTIVE(foe)+" to engage in combat with you, "+
			 "rather than "+QTNAME(ob)+".\n",
			 QCTNAME(TP)+" runs toward " + QTNAME(foe)+
			 ", forcing "+QTNAME(foe) + " to engage in combat "+
			 "with "+OBJECTIVE(TP)+" rather than you.\n",
			 QCTNAME(TP)+" runs toward "+QTNAME(foe)+
			 ", forcing "+QTNAME(attackers[i])+" to engage in combat "+
			 "with "+OBJECTIVE(TP)+" rather than "+QTNAME(ob)+".\n",
			 QCTNAME(TP)+" runs toward you, forcing you to engage "+
			 "in combat with "+OBJECTIVE(TP)+", rather than "+
			 QTNAME(ob)+".\n" });
	break;
    case 3:
	rescue2 =
	    ({ "shout out a Solamnic battlecry as you charge "+
		   "forward, drawing the attention of " + QTNAME(foe)+".\n",
		   QCTNAME(TP)+" draws the attention of your enemy, "+
		   QTNAME(foe) + ", as "+PRONOUN(TP)+" charges forward, "+
		   "shouting out a Solamnic battlecry.\n",
		   QCTNAME(TP)+" draws the attention of "+QTNAME(foe)+
		   " as "+PRONOUN(TP)+" charges forward, shouting out a " +
		   "Solamnic battlecry.\n",
		   QCTNAME(TP)+" draws your attention as "+PRONOUN(TP)+
		   " charges forward, shouting out a Solamnic battlecry.\n" });
	break;
    case 2:
	rescue2 =
	    ({ "maneuver so that "+QTNAME(foe)+" is "+
		   "forced to fight you, and ignore "+QTNAME(ob)+".\n",
		   QCTNAME(TP)+" maneuvers so that "+QTNAME(foe)+" is "+
		   "forced to fight "+OBJECTIVE(TP)+", and ignore you.\n",
		   QCTNAME(TP)+" maneuvers so that "+QTNAME(foe)+" is "+
		   "forced to fight "+OBJECTIVE(TP)+", and ignore "+
		   QTNAME(ob)+".\n",
		   QCTNAME(TP)+" maneuvers so that you are forced to fight "+
		   "him, and ignore "+QTNAME(ob)+".\n" });
	break;
    case 1:
	rescue2 =
	    ({ "pull "+QTNAME(ob)+" out of harm's way, stepping "+
		   "forward to take the brunt of "+QTNAME(attackers[i])+"'s "+
		   "attacks.\n",
		   "Pulling you out of harm's way, "+QTNAME(TP)+" steps "+
		   "forward to take the brunt of "+QTNAME(foe)+"'s "+
		   "attacks.\n",
		   "Pulling "+QTNAME(ob)+" out of harm's way, "+QTNAME(TP)+
		   " steps forward to take the brunt of "+QTNAME(foe)+
		   "'s attacks.\n",
		   "Pulling "+QTNAME(ob)+" out of harm's way, "+QTNAME(TP)+
		   " steps forward to take the brunt of your attacks.\n" });
	break;
    default:
	rescue2 =
	    ({ "manage to distract "+QTNAME(foe)+", "+
		   "enabling "+QTNAME(ob)+" to escape as "+ PRONOUN(foe)+
		   " turns to attack you.\n",
		   QCTNAME(attackers[i])+" turns to attack "+QTNAME(TP)+" as "+
		   QTNAME(TP)+" distracts "+OBJECTIVE(foe)+", allowing "+
		   "you to escape.\n",
		   QCTNAME(foe) + " turns to attack "+QTNAME(TP)+" as "+
		   QTNAME(TP) + " distracts "+OBJECTIVE(foe)+", allowing "+
		   OBJECTIVE(ob)+" to escape.\n",
		   "You turn to attack "+QTNAME(TP)+" as "+PRONOUN(TP)+
		   " distracts you, allowing "+QTNAME(ob)+" to escape.\n" });
	break;
    }

    TP->attack_object(foe);
    foe->attack_object(TP);
    TP->catch_msg(rescue + rescue2[0]);
    ob->catch_msg(rescue2[1]);
    say(rescue2[2], ({ob, TP, foe}));
    foe->catch_msg(rescue2[3]);

    setuid();
    seteuid(getuid());

    if (!(rescue_ob = present(RESCUE_OBJECT, ob)))
    {
	rescue_ob = clone_object(KOBJ + "rescue_object");
	rescue_ob->move(ob);
    }

    rescue_ob->add_guard(TP, foe);
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
    string cry, pri, mer, kat, cha, aid;
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

	if (medal->query_auto_kattack())
	  kat = "enabled";
	else
	  kat = "disabled";

	if (medal->query_auto_charge())
	  cha = "enabled";
	else
	  cha = "disabled";

	if (medal->query_auto_aid())
	  aid = "enabled";
	else
	  aid = "disabled";


/*  Removed by Boron, as it is silly to force no parameters, lets just display it
    okt 26, 03
    NF("Koptions what??\n");
    if (str)
	return 0;
*/

    write("\n--==< Knight Options >==--\n\n");
    write("  Battlecries: "+cry+" \n");
#ifdef NEW_MERCY
#else
    write("        Mercy: "+mer+" \n");
#endif
    write("      Primary: "+pri+" \n");

	write(" Auto kattack: "+kat+"\n");
	write("  Auto charge: "+cha+"\n");
	write("    Auto kaid: "+aid+"\n");

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

#ifdef NEW_MERCY
    if (medal->query_generous())
    {
	medal->set_generous(0);
	write("BEWARE: You were still merciful. This has been turned off now!\n");
    }
    write("Please use the 'options merciful [on|off]' command from now on instead.\n");
    return 1;
#endif


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

int
kauto(string str)
{
	object medal = P("pal_med", TP);

	setuid(); seteuid(getuid());
	NF("You don't have a medal, you should seek guidance.\n");
    if (!medal)
	return 0;

	if (str == "kattack")
	{
		if (medal->toggle_auto_kattack())
		{
		write("Auto kattack has been enabled.\n");
		}
		else
		{
		write("Auto kattack has been disabled.\n");
		}
		return 1;
	}

	else if (str == "charge")
	{
		if (medal->toggle_auto_charge())
		{
		write("Auto charge has been enabled.\n");
		}
		else
		{
		write("Auto charge has been disabled.\n");
		}
		return 1;
	}

	else if (str == "kaid")
	{
		if (medal->toggle_auto_aid())
		{
		write("Auto kaid has been enabled.\n");
		}
		else
		{
		write("Auto kaid has been disabled.\n");
		}
		return 1;
	}
	else
	{
	  koptions("");
	  write("\nYou may use 'kauto [kattack|charge|kaid]' to aid you " +
	        "in combat\n");
	  return 1;
    }


    return 1;
}
