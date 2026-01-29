/*
 * /d/Gondor/common/guild/north/ranger_soul.c
 *
 * The soul of the Rangers of the North
 * By Elessar, 1998
 *
 * Revision history:
 *
 * First adapted for the Rangers of the North from the original Ranger soul,
 * by Elessar, November 1998.
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver.c";
inherit "/d/Gondor/common/lib/binbit.c";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

// Must be included before other guild header files:
#include "/d/Gondor/common/guild/lib/punish_defs.h"

// Must be defined before guild header files are included:
#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))

// Rangers of the North specific code
#include "/d/Gondor/common/guild/north/lib/officer.h"
#include "/d/Gondor/common/guild/north/lib/communicate.h"
#include "/d/Gondor/common/guild/north/lib/emotes.h"
// Code in common with the other Rangers
#include "/d/Gondor/common/guild/lib/brawl.c"
#include "/d/Gondor/common/guild/lib/listen.h"
#include "/d/Gondor/common/guild/lib/campfire.c"
#include "/d/Gondor/common/guild/lib/consider.h"
#include "/d/Gondor/common/guild/north/lib/diagnose.c"
#include "/d/Gondor/common/guild/lib/mark.h"
#include "/d/Gondor/common/guild/lib/rsongs.h"
#include "/d/Gondor/common/guild/lib/rbattle.h"
#include "/d/Gondor/common/guild/lib/obscure.h"
#include "/d/Gondor/common/guild/lib/special_track.h"
#include "/d/Gondor/common/guild/lib/forage.c"
#include "/d/Gondor/common/guild/lib/stealth.h"

/*
 * Return a name in order to get a nice printout.
 */
string
get_soul_id()
{
    return "Rangers of the North";
}

/*
 * Identify this soul as a command soul.
 */
int
query_cmd_soul()
{
    return 1;
}

/*
 * Returns a mapping of the form "verb":"function" with all the commands the
 * player can perform. Please add new commands in aphabetical order.
 */
mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());
    return ([
	     "battle"      : "battle",
	     "blind"       : "blind",
	     "brawl"       : "brawl",
	     "consider"    : "consider",
	     "deputize"    : "deputize",
             "diagnose"    : "diagnose",
	     "disarm"      : "disarm",
	     "forage"      : "try_forage",
	     "gather"      : "try_gather",
	     "nrsay"       : "speak_adunaic",
	     "guildlist"   : "guildlist",
	     "hail"        : "hail",
	     "rhail"       : "hail",
	     "kisshand"    : "kisshand",
	     "rhear"       : "do_listen",
	     "help"        : "help",
	     "rgleam"      : "rgleam",
	     "rhush"       : "hush",
	     "mark"        : "mark",
	     "obscure"     : "obscure",
	     "rbearing"    : "find_bearing",
	     "rcloak"      : "cloak_wrap",
	     "runcloak"    : "cloak_unwrap",
	     "rcheck"      : "rcheck",
	     "rgrip"       : "rgrip",
	     "rgrim"       : "rgrim",
	     "rgazefire"   : "gaze_fire",
	     "rhome"       : "rhome",
	     "rinspect"    : "inspect_weapon",
	     "rintro"      : "ranger_intro_type",
	     "rdirt"       : "emote_dirt",
	     "rlist"       : "list_active_rangers",
	     "nrlist"      : "list_active_rangers",
	     "rlisten"     : "rlisten",
	     "rpoke"       : "poke_fire",
	     "rrest"       : "emote_rest",
	     "rtitles"     : "rtitles",
	     "rstudy"      : "emote_study",
	     "rweary"      : "rweary",
	     "rwipe"       : "wipe_weapon",
	     "rwait"       : "rwait",
	     "rwarm"       : "warm_by_fire",
	     "rwarmback"   : "warm_back_by_fire",
	     "rpardon"     : "pardon_outlaw",
	     "rparley"     : "emote_parley",
	     "sing"        : "do_song",
	     "stealth"     : "stealth_mode",
	     "stop"        : "stop_brawl",
	     "trip"        : "trip",
	     "expel"       : "expel_ranger",
	     "release"     : "release_ranger",
	     "offer"       : "offer_to_join",
	     "outlaw"      : "outlaw_enemy"
     ]);
}

/*
 * Below this line come all the functions themselves. Please add new functions
 * in alphabetical order. Service and secondary functions can be added
 * wherever you like.
 */

int
battle(string str)
{
    object  enemy,
	   *ob;
    string *cries = BATTLE_CRY;
    int     n;

    cries += BATTLE_CRY_ELVES;
    cries += BATTLE_CRY_HUMANS;
    n = random(sizeof(cries));

    if (!stringp(str))
    {
	if (!objectp(enemy = TP->query_attack()))
	{
	    TP->command("shout " + cries[n] + "!");
	    return 1;
	}
	else
	    ob = ({ enemy });
    }
    else
	ob = parse_this(str, "%l");
    if (!sizeof(ob))
	return 0;
    if(sizeof(ob) > 1)
    {
	TP->catch_msg("Be specific, you cannot kill " + COMPOSITE_LIVE(ob) +
		      " at the same time. \n");
	return 1;
    }
    if (TP->query_attack() == ob[0])
    {
	TP->catch_msg("You shout out: "+cries[n]+"! and attack " +
		      QTNAME(ob[0]) + " with renewed fervour.\n");
	ob[0]->catch_msg(QCTNAME(TP) + " shouts out: "+cries[n] +
			 "! and attacks with renewed fervour.\n");
	say(QCTNAME(TP)+" shouts out: "+cries[n]+"! as " + PRONOUN(TP) +
	    " attacks "+QTNAME(ob[0])+" with renewed fervour.\n",
	    ({ TP,ob[0] }));
	return 1;
    }
    if (!F_DARE_ATTACK(TP, ob[0]))
    {
	NF("Umm... no, You do not have enough self-discipline to dare!\n");
	return 0;
    }
    TP->catch_msg("You shout out: "+cries[n]+"! as you join battle with " +
        QTNAME(ob[0]) + ".\n");
    ob[0]->catch_msg(QCTNAME(TP) + " shouts out: "+cries[n]+"! as " +
        PRONOUN(TP) + " joins battle with you.\n");
    say(QCTNAME(TP)+" shouts out: "+cries[n]+"! as " + PRONOUN(TP) +
	" joins battle with "+QTNAME(ob[0])+".\n",({ TP,ob[0] }));
    /* 
     * this construct does not allow 'battle second man' if there are
     * several men with the same real_names in the room
       TP->command("kill " + ob[0]->query_real_name());
     */
    TP->command("$kill " + str);
    return 1;
}

int
hail(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You hail everybody in the name of Arnor.\n");
	all(" bows deeply, saying: Hail Arnor!");
	return 1;
    }
    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	NFN0("Hail who?");
    }

    actor("You hail", oblist, " in the name of Arnor.");
    target(" bows deeply before you, saying: Hail Arnor!", oblist);
    all2act(" bows before", oblist, " saying: Hail Arnor!");
    return 1;
}

int
guildlist(string str)
{
    string name;
    object ob;

    if (strlen(str))
    {
	if (!(TP->query_wiz_level()))
	    NFN0("Curious aren't we?");

	if (!(ob = find_player(str)))
	    NFN0("No such player found.");

	name = CAP(str) + " is ";
    }
    else
    {
	ob = TP;
	name = "You are ";
    }

    str = ob->list_mayor_guilds();

    if (strlen(str))
	write(name + "member of following guilds.\n" + str);
    else
	write(name + "not member of any guilds.\n");

    return 1;
}


int
help(string str)
{
    string subject, filename;

    if (!strlen(str))
	return 0;

    setuid();
    seteuid(getuid(TO));

    if (str == "ranger" || str == "guild")
    {
	cat(RANGER_NORTH_HELP_DIR + "commands");
	return 1;
    }

    if (sscanf(str, "ranger %s", subject) != 1)
	return 0;

    filename = RANGER_NORTH_HELP_DIR + subject;

    if (file_size(filename) <= 0)
    {
	NFN0("No help on that subject I'm afraid.");
    }

    TI->more(read_file(filename));
    return 1;
}

int
hush(string str)
{
    object *oblist;
    if (!strlen(str))
    {
        write("You whisper 'Hush!', and motion for all to be silent.\n");
        allbb(" whispers 'Hush!', and motions with "+POSSESSIVE(TP)+
          " hand for silence.");
        return 1;
    }
    oblist = parse_this(str,"[at] [the] %l");
    if (!sizeof(oblist))
    {
        write("You whisper 'Hush!' and motion for all to be silent.\n");
        allbb("whispers 'Hush!', and motions with "+ POSSESSIVE(TP)+
          " hand for you all to be silent.");
        return 1;
    }
    else 
    {
        actor("You whisper 'Hush!', and motion for", oblist, " to be silent.");
        targetbb(" whispers 'Hush!', and motions with "+POSSESSIVE(TP)+
          " hand for you to be silent.",oblist);
        all2actbb(" whispers 'Hush!', and motions with "+POSSESSIVE(TP)+" hand for",
          oblist, " to be silent.");
        return 1;
    }
}

int
kisshand(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] [hand] [of] [the] %l");

    if (!sizeof(oblist))
    {
	NFN0("Kiss the hand of whom?");
    }
    else
    {
	oblist = ({ oblist[0] });
    }

    actor("You take", oblist, "'s hand into yours, and gently kiss it.");
     target(" takes your hand into " + POSSESSIVE(TP) + (TP->query_gender() == 1 ? "s" : "") +
	", and gently kisses it.", oblist);
    all2act(" takes", oblist, "'s hand into " + POSSESSIVE(TP) +
	" own, and gently kisses it.");
    return 1;
}

