 /* 
	*uruk_soul.c
	*contains emotes for the Middle Earth uruk race guild
	*Altrus
	*Last modified: May 18, 2006
 */

#pragma save_binary
//#pragma strict_types

inherit "/cmd/std/command_driver";

#include <macros.h>
#include <formulas.h>
#include <language.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>
#include <files.h>
#include <time.h>
#include <std.h>
#include <wa_types.h>
#include <ss_types.h>
#include <options.h>
#include <adverbs.h>
#include <cmdparse.h>
#include <options.h>


#include "/d/Shire/sys/defs.h"
#include "uruk.h"
#include "ulist.h"
//#include "oidea.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define MORE(x)   this_player()->more(read_file(x,2))

#define BATTLECRY	({"I will tear the flesh from your bones", "I will crush you to dust", \
				"Here's a maggot hole for your stomach", "Bleed! Bleed and die", })

#define HOBBITCRY	({"I will feast on halfling meat", "Curse the miserable halflings", })
#define ELFCRY		({"No elf will go unslain", "Death to elvenkind", \
				"Death will be your reward, elf", })
#define DWARFCRY	({"Flee, flee or die, puny dwarf", })
#define HUMANCRY	({"Pathetic human", "I will taste man-flesh", })
#define REDCRY		({"None can withstand the power of the Dark Lord", \
				"All will fall before the terror of the Red Eye", \
				"Cower before the might of Mordor", })
#define WHITECRY	({"Saruman will conquer all", "For the White Hand of Isengard", \
				"Victory to the White Hand, victory to Saruman", })

int same_check(object player, object target);
void same_aggressive_check(object player, object target);
void diff_aggressive_check(object player, object target);
public string check_ready(object who);
public string check_ready_enemy(object who, object target);

string get_soul_id()
{
    return "Uruks of Middle Earth";
}

int
query_cmd_soul()
{
    return 1;
}

mapping query_cmdlist()
{

    setuid();
    seteuid(getuid());

    return ([
	"help"			: "do_help",
	"ulist"          	: "list_active_uruks",
	"uruklist"      	: "list_active_uruks",
	"ugreet"		: "uruk_greet",
	"ubite"  		: "uruk_bite",
	"uagg"         	: "uruk_aggressive",
	"uaggressive"	: "uruk_aggressive",
	"ucry"         	: "uruk_battlecry",
	//"upledge"		: "uruk_pledge",
	//"umutter"		: "uruk_mutter",
	//"ucomplain"         : "uruk_complain",
	//"urage"        	: "uruk_rage",
	//"uthrash"    	: "uruk_thrash",
	//"udis"     	   	: "uruk_discipline",
	//"udiscipline"        	: "uruk_discipline",
	//"uscoff"		: "uruk_scoff",
	//"udisagree"		: "uruk_disagree",
	//"uagree"          	: "uruk_agree",
	//"ucringe"      	: "uruk_cringe",
	//"ubeg"            	: "uruk_beg",
	//"uobey"   		: "uruk_obey",
	//"ucower"	   	: "uruk_cower",
	//"uoffer"		: "uruk_offer",
	"uspeak"		: "uruk_speak",
	"usp"			: "uruk_speak",
	//"uchallenge"	: "uruk_challange",
	//"upaint"		: "uruk_paint",
	//"uchant"		: "uruk_chant",
	]);
}

int
do_help(string str)
{
	setuid(); 
	seteuid(getuid());
	switch (str)
	{
		case "uruk":
			MORE(URUK_HELP + "general");
			TP->catch_tell("Please report any problems you may encounter with the " + URUK_RACE_GUILD_NAME + " to " + COMPOSITE_WORDS(map(URUK_RACE_GUILD_MASTER, capitalize)) + ".\n");
			break;
		
		case "uruk emotions":
			if(TP->query_prop(I_URUK))
				MORE(URUK_HELP + "i_emotes");
			else
				MORE(URUK_HELP + "m_emotes");
			break;
		
		case "uruk news":
			MORE(URUK_HELP + "news");
			break;
		
		default:
		return 0;
	}
    return 1;
}

/*
	*uruk_greet, greets the target in typical uruk fashion
*/
int uruk_greet(string str)
{
	object *oblist;
	if(!strlen(str)) /* no string supplied */
	{
		write("Greet who?\n");
		return 1;
	}
	
	oblist = parse_this(str, "[the] %l");
	
	if(!sizeof(oblist))
	{
		write("There is no one to greet.\n");
		return 1;
	}
	
	if(sizeof(oblist) > 1)
	{
		write("Greet one person at a time.\n");
		return 1;
	}
	
	if(IS_MEMBER(oblist[0]))
	{
		if(same_check(TP, oblist[0]))
		{
			actor("You forcefully knock heads with", oblist, " in greeting.");
			target(" forcefully knocks heads with you in greeting.", oblist);
			all2act(" headbutts", oblist, " in greeting.");
		}
		
		else
		{
			actor("You grudgingly greet", oblist, ", but keep your distance.");
			target(" grudgingly greets you, but maintains a safe distance.", oblist);
			all2act(" grudgingly greets", oblist, ", but keeps some distance between them.");
		}
	}
	
	else if(MAGE_MEMBER(oblist))
		actor("Don't even think about greeting a mage of Minas Morgul in such a way!");
	
	else
	{
		actor("You briefly snort at", oblist," in greeting.");
		target(" briefly snorts at you in greeting.", oblist);
		all2act(" briefly snorts at", oblist, " in greeting.");
	}
	
	return 1;
}

/*
	*uruk_bite, consider taking a bite out of someone
*/
int uruk_bite(string str)
{
	object *oblist;
	if(!strlen(str)) /* no string supplied */
	{
		write("Take a bite out of whom?\n");
		return 1;
	}
	
	oblist = parse_this(str, "[the] %l");
	
	if(!sizeof(oblist))
	{
		write("There is no one to bite.\n");
		return 1;
	}
	
	if(sizeof(oblist) > 1)
	{
		write("Patience, one person at a time.\n");
		return 1;
	}
	
	if(oblist->query_guild_name_occ() == "Morgul Mages")
		actor("Are you crazy?! That's a mage of Minas Morgul!");
	
	else
	{
		actor("You seriously consider taking a bite out of", oblist,"!");
		target(" looks like " + HE_SHE(TP) + " wants to take a bite out you!", oblist);
		all2act(" looks strangely at", oblist, ", as if wanting to take a bite out of " + HIM_HER(oblist[0]) + ".");
	}
	
	return 1;
}

/*
	*uruk_agressive, show other goblinoids who's boss!
*/
int uruk_aggressive(string str)
{
	object *oblist, targ;
	if(!strlen(str)) /* no string supplied */
	{
		write("To whom do you want to show aggression?\n");
		return 1;
	}
	
	oblist = parse_this(str, "[to] [the] %l");
	
	if(!sizeof(oblist))
	{
		write("There is no one here like that.\n");
		return 1;
	}
	
	if(sizeof(oblist) > 1)
	{
		write("Dominate one person.\n");
		return 1;
	}
	
	targ = oblist[0];
	
	if(IS_MEMBER(targ))
	{
		if(same_check(TP, targ))
		{
			actor("You attempt to muscle", targ, " into submission...");
			target(" attempts to force you into submission...", targ);
			all2act(" attempts to force", targ, " into submission...");
			set_alarm(2.0, 0.0, &same_aggressive_check(TP, targ));
		}
		
		else
		{
			actor("You take a wild swing at", targ, " with your fist, trying to beat " + HIM_HER(TP) + " into submission...");
			target(" takes a wild swing at you with " + HIS_HER(TP) + "fist, trying to beat you into submission...", targ);
			all2act(" takes a wild swing at", targ, " with " + HIS_HER(TP) + "fist, trying to beat " + HIM_HER(targ) + " into submission...");
			set_alarm(2.0, 0.0, &diff_aggressive_check(TP, targ));
		}
	}
	
	else if(MAGE_MEMBER(targ))
		actor("You must be insane! It would be suicide to try that!");
	
	else if(targ->query_race_name() == "uruk" | targ->query_race_name() == "uruk-hai" | targ->query_race_name() == "orc" | targ->query_race_name() == "goblin" | targ->query_race_name() == "hobgoblin")
	{
		if((TP->query_stat(SS_DIS) + random(50)) > targ->query_stat(SS_STR))
		{
			actor("Aiming for the head, you hurl your fist at", targ, ", hitting " + HIM_HER(targ) + " soundly! You're the boss around here!");
			target(" tries to show you who's the boss by hitting you soundly on the head! Are you going to take that??", targ);
			all2act(" let's", targ, " know who's boss by soundly beating " + HIS_HER(targ) + " head with " + HIS_HER(TP) + " fist!");
		}
		
		else
		{
			actor("Aiming for the head, you hurl your fist at", targ, ", but miss entirely! You lose your balance and fall pathetically to the ground.");
			target(" tries to show you who's the boss by taking a swing at your head, but " + HE_SHE(TP) + " misses and trips, pathetically falling to the ground.", targ);
			all2act(" tries to show", targ, " who's the boss by taking a swing at " + HIS_HER(targ) + " head, but misses, tripping and falling to the ground.");
		}
		
	}
	
	else
	{
		actor("If you're so eager to start a fight with", targ,", just attack!");
	}
	
	return 1;
}

/*
 * uruk_battlecry - battle has been engaged! roar with fury!
 * Parts of this borrowed from ranger "rbattle"
 */
int uruk_battlecry(string str)
{
	object enemy, *ob;
	string *battlecries = BATTLECRY;
	string race, ready, battlecry;
	
	ready = check_ready(TP);
	if(strlen(ready))
	{
		notify_fail(ready);
		return 0;
	}
	
	if(!stringp(str))
	{
		enemy = TP->query_attack();
		if(!objectp(enemy))
		{
			TP->catch_msg("But you aren't in combat.\n");
			return 1;
		}
		
		else
			ob = ({ enemy });
	}
	
	else
		ob = parse_this(str, "%l");

	if(!sizeof(ob))
	{
		write("There is nothing like that to attack.\n");
		return 1;
	}
	
	if(sizeof(ob) > 1)
	{
		write("You cannot attack " + COMPOSITE_LIVE(ob) + " at once. Attack one thing.\n");
		return 1;
	}
	
	ready = check_ready_enemy(TP, ob[0]);
	if(strlen(ready))
	{
		notify_fail(ready);
		return 0;
	}
	
	race = ob[0]->query_race_name();
	if(race == "hobbit")
		battlecries += HOBBITCRY;
	
	if(race == "elf")
		battlecries += ELFCRY;
	
	if(race == "dwarf")
		battlecries += DWARFCRY;
	
	if(race == "human")
		battlecries += HUMANCRY;
	
	if(TP->query_prop(I_URUK))
		battlecries += WHITECRY;
	
	if(TP->query_prop(M_URUK))
		battlecries += REDCRY;
	
	if(TP->query_attack() == ob[0])
	{
		battlecry = one_of_list(battlecries);
		actor("You loudly roar: '" + battlecry + "!', and fight", ob," with increased rage.");
		target(" loudly roars: '" + battlecry + "!', and fights you with increased rage.", ob);
		all2act(" loudly roars: '" + battlecry + "!', and fights", ob, " with increased rage.");
		return 1;
	}
	
	battlecry = one_of_list(battlecries);
	actor("You furiously roar: '" + battlecry + "!', as you rush into battle with", ob,".");
	target(" furiously roars: '" + battlecry + "!', as " + HE_SHE(TP) + " rushes into battle with you.", ob);
	all2act(" furiously roars: '" + battlecry + "!', as " + HE_SHE(TP) + " rushes into battle with", ob, ".");
        TP->attack_object(ob[0]);
	return 1;
}

/*
 * uspeak - borrowed from orc speaking
 */
int uruk_speak(string str)
{
	object oActor = this_player ();
	int    iListener;
	object oListener;
	object *aoListeners;
	
	notify_fail("What do you want to say?\n");
	
	if (!strlen (str)) 
	    return 0;
	
	write("You loudly bark in the black tongue: " + str + "\n");

	aoListeners = FILTER_LIVE (all_inventory (environment (oActor)) - ({ oActor }));
	for (iListener = 0 ; iListener < sizeof (aoListeners) ; iListener ++)
	{
		oListener = aoListeners [iListener];
		if(IS_MEMBER (oListener))
		{
			oListener->catch_tell (oActor->query_The_name (oListener) + " loudly barks in the black tongue: " + str + "\n");
		}
		
		else if(ORC_MEMBER (oListener))
		{
			oListener->catch_tell (oActor->query_The_name (oListener) + " loudly barks in the black tongue: " + str + "\n");
		}
		
		else if(!TP->query_wiz_level())
		{
			oListener->catch_tell (oActor->query_The_name (oListener) + " loudly barks in the black tongue: " + str + "\n");
		}
		
		else	
		{
			oListener->catch_tell (oActor->query_The_name (oListener) + " loudly barks something unintelligible in the black tongue.\n");
		}
		
	}
	
	return (1);
}

int same_check(object player, object target)
{
	if(player->query_prop(I_URUK) && target->query_prop(I_URUK))
		return 1;
	
	else if(player->query_prop(M_URUK) && target->query_prop(M_URUK))
		return 1;
	
	else
		return 0;
}

void same_aggressive_check(object player, object victim)
{
	int p_stat = (player->query_stat(SS_STR) + player->query_stat(SS_DIS));
	int v_stat = (victim->query_stat(SS_STR) + victim->query_stat(SS_DIS));
	int p_rank = player->query_stat(SS_RACE);
	int v_rank = victim->query_stat(SS_RACE);
	
	//Target is smaller in size and rank, totally dominate him
	if((p_stat > v_stat) && (p_rank > v_rank))
	{
		write("...And succeed! Now " + QTNAME(victim) + " knows that you're the boss around here.\n");
		victim->catch_msg("..." + HE_SHE(player) + " succeeds! " + QTNAME(player) +" asserts " + HIS_HER(player) + " dominance over you.\n");
		tell_room("..." + HE_SHE(victim) + " succeeds! " + QTNAME(player) + " asserts " + HIS_HER(player) + " dominance over " + QTNAME(victim) + ".\n", victim, player);
	}
	
	//Target is smaller in size, but higher in rank, show contempt for such a weak superior
	if((p_stat > v_stat) && (p_rank <= v_rank))
	{
		write("...But hold back, as " + QTNAME(victim) + " is obviously higher in the ranks, but you show utter contempt for such a weak superior.\n");
		victim->catch_msg("..." +HE_SHE(player) + " holds back, unwilling to strike a superior but sneering in contempt at your weakness.\n");
		tell_room("..." +HE_SHE(player) + " holds back, unwilling to continue but sneering in contempt at " + QTNAME(victim) + "'s weakness.\n", victim, player);
	}
	
	//Target is larger in size, lower in rank, you feel unsure about your ability to dominate him
	if((p_stat <= v_stat) && (p_rank > v_rank))
	{
		write("...But you fail. You are obviously higher in the ranks, but " + QTNAME(victim) + " is just too strong.\n");
		victim->catch_msg("...But " + HE_SHE(player) + " fails. " + HE_SHE(player) + " is obviously higher in the ranks, but you are simply too strong.\n");
		tell_room("...But fails to dominate " + QTNAME(victim) + ".\n", victim, player);
	}
	
	//Target is larger in size and rank, get your butt handed back to you for being stupid
	else
	{
		write("...You utterly fail, and " + QTNAME(victim) + " punches you soundly on the nose, letting you know not to try that again.\n");
		victim->catch_msg("..." + HE_SHE(player) + " utterly fails, and you punch " + HIM_HER(player) + " soundly on the nose, letting " + HIM_HER(player) + " know not to try that again.\n");
		tell_room("..." + HE_SHE(player) + " utterly fails, and " + QTNAME(victim) +" punches " + HIM_HER(player) + " soundly on the nose.\n", victim, player);
	}
}

void diff_aggressive_check(object player, object target)
{
	int p_stat = (player->query_stat(SS_STR) + player->query_stat(SS_DIS));
	int t_stat = (target->query_stat(SS_STR) + target->query_stat(SS_DIS));
	int p_rank = player->query_stat(SS_RACE);
	int t_rank = target->query_stat(SS_RACE);
	write("...NOT FINISHED YET...\n");
	
}

public string check_ready(object who)
{
	string message;

	if(environment(who) && (message = environment(who)->query_prop(ROOM_M_NO_ATTACK)))
		return (stringp(message) ? message : "A divine presence prevents any attack.\n");
}

public string check_ready_enemy(object who, object target)
{
	string message;

	if(environment(who) && (message = environment(who)->query_prop(ROOM_M_NO_ATTACK)))
		return (stringp(message) ? message : "A divine presence prevents any attack.\n");
  
	if(message = target->query_prop(OBJ_M_NO_ATTACK))
		return (stringp(message) ? message : "A strong presence prevents your attack.\n");
 
	if(who->query_met(target) && who->query_enemy(0) != target)
	{
		if(who->query_prop(LIVE_O_LAST_KILL) != target)
		{
			who->add_prop(LIVE_O_LAST_KILL, target);
			return "Attack " + target->query_the_name(who) + "? Please confirm by trying again.\n";
		}
	}
	
	if(target != who->query_attack())
	{
		if (!F_DARE_ATTACK(who, target))
			return "Umm... no, You do not have enough self-discipline to dare!\n";
	}
}
