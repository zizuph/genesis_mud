#include "defs.h"
#include "lists.h"

inherit "/cmd/std/command_driver";
inherit EXTRA_FILE;
//inherit TELL_FILE;
inherit LIST_MASTER;
//inherit EMOTE_SOUL;

#include "/secure/std.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include "/d/Shire/skills.h"
#include "/d/Shire/imladris/guild/fumble.c"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))

string
get_soul_id()
{
   seteuid(getuid());
   return "Imladris-soul";
}

/* This soul is auto_loading */
string
query_auto_load()
{
   seteuid(getuid());
   return MASTER_OB(TO);
}

void
using_soul(object live)
{
    seteuid(getuid());
}

/***************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 */

mapping
query_cmdlist()
{
    seteuid(getuid());
    return ([
	"info":   "info",
	"index":  "do_index",
	"slist":  "do_slist",
	"lists":  "do_slist",
	"teach":  "do_teach",
	"pref":   "do_pref",	  /* For the lazy typer. */
	"preferences": "do_pref",
	"factor": "do_factor",
	"sforget": "do_forget",
	"fumble" : "fumble",
	"learn":  "do_learn",
	"level":  "do_level",
	"mana" :  "do_mana",
	"stop" :  "do_stop",
	"chant":  "do_chant",
	"chanting": "do_chant"
    ]);
}

/****************************************************************************
 *  Some handy functions
 */

fail_ghost()
{
   seteuid(getuid());
   write("You fail.\n");
   return 1;
}

known_present(who,where)
{
   string intro, remem, list;
   seteuid(getuid());
   intro = this_player()->query_introduced();
   remem = this_player()->query_remembered();
   list = (intro ? intro : ({ })) + (remem ? remem : ({ }));
   return present(who,where);
}

/* **************************************************************************
    Here follows my special commands for Spellmasters.
 * ************************************************************************** */

#define SUB_DESC\
({"novice","junior","apprentice","","confident","seasoned","expert",\
  "eminent","brilliant","superior"})

#define DESC ({"student","amateur","layman","acolyte","journeyman",\
	       "craftsman","professional","veteran","master","guru"})

string skill_desc(int no)
{
    string sub_desc, desc;
    if(!no || no<0)
	return "without skill";
    if(no>100)
	return "better than veteran guru";
    no --;
    sub_desc = SUB_DESC[no%10];
    desc = DESC[no/10];
    if(strlen(sub_desc))
	return sub_desc+" "+desc;
    else
	return desc;
}

string
info_general(object who)
{                                                                             
  return                                                                      
    "General Magical Skills\n\n"+                                             
    "  Spellcraft...........: " + skill_desc(who->query_skill(SS_SPELLCRAFT)) + "\n" +
    "  Herbalism............: " + skill_desc(who->query_skill(SS_HERBALISM)) + "\n" +
    "  Alchemy..............: " + skill_desc(who->query_skill(SS_ALCHEMY)) + "\n" +
    "\n";
}

string
info_forms(object who)
{
  return
    "Magical Forms Skills\n\n"+                                               
    "  Form Transmutation...: " + skill_desc(who->query_skill(SS_FORM_TRANSMUTATION)) + "\n"+
    "  Form Illusion........: " + skill_desc(who->query_skill(SS_FORM_ILLUSION)) + "\n" +
    "  Form Divination......: " + skill_desc(who->query_skill(SS_FORM_DIVINATION)) + "\n"+
    "  Form Enchantment.....: " + skill_desc(who->query_skill(SS_FORM_ENCHANTMENT)) + "\n"+
    "  Form Conjuration.....: " + skill_desc(who->query_skill(SS_FORM_CONJURATION)) + "\n"+
    "  Form Abjuration......: " + skill_desc(who->query_skill(SS_FORM_ABJURATION)) + "\n"+
    "\n";
}

string
info_elements(object who)
{
  return
    "Elemental Skills\n\n"+                                                   
    "  Fire Spells..........: " + skill_desc(who->query_skill(SS_ELEMENT_FIRE)) + "\n"+
    "  Air Spells...........: " + skill_desc(who->query_skill(SS_ELEMENT_AIR)) + "\n"+
    "  Earth Spells.........: " + skill_desc(who->query_skill(SS_ELEMENT_EARTH)) + "\n"+
    "  Water Spells.........: " + skill_desc(who->query_skill(SS_ELEMENT_WATER)) + "\n"+
    "  Life Spells..........: " + skill_desc(who->query_skill(SS_ELEMENT_LIFE)) + "\n"+
    "  Death Spells.........: " + skill_desc(who->query_skill(SS_ELEMENT_DEATH)) + "\n";
}                                                                             

string
info_skills(object who)
{
    return info_general(who)+info_forms(who)+info_elements(who);
}

string
mana_desc(int no, int max)
{
    if(!no || no<=0)
	return "nothing";
    switch(no*1000/max) {
	case 1..10    : return "close to nothing";
	case 11..20   : return "almost nothing";
	case 21..30   : return "very bad";
	case 31..40   : return "quite bad";
	case 41..50   : return "bad";
	case 51..900  : return ratio_str(no, max);
	case 901..950 : return "quite good";
	case 951..980 : return "very good";
	default       : return "at top";
    }
}

string
max_desc(int no)
{
    switch(no) {
	case 0	      : return "nothing";
	case 1..100    : return "very poor";
	case 101..200	: return "quite poor";
	case 201..300	: return "some";
	case 301..400	: return "quite some";
	case 401..500	: return "a lot";
	case 501..600	: return "much";
	case 601..700	: return "very much";
	case 701..800	: return "a whole lot";
	case 801..900	: return "extremely much";
	case 901..1000	: return "devastating";
	case 1001..1100 : return "awesome";
	case 1101..1200 : return "fabulous";
	case 1201..1300 : return "spiritual";
	case 1301..1400 : return "demi-godly";
	default 	: return "godly";
    }
}

#include "index.c"

string
info_mana(object who)
{
    return
	"Your mana amount is now "+mana_desc(who->query_mana(),who->query_max_mana())+" of max.\n"+
	"Your maximum amount is "+max_desc(who->query_max_mana())+" when compared to an average.\n";
}

int
info(string str)
{
    seteuid(getuid());
    if(str=="all") {
	write(info_mana(TP)+"\n"+
	      info_skills(TP)+"\n");
	return 1;
    } else if(str=="skills") {
	write(info_skills(TP)+"\n");
	return 1;
    } else if(str=="general"||str=="general skills") {
	write(info_general(TP));
	return 1;
    } else if(str=="forms"||str=="magical"||str=="magical forms") {
	write(info_forms(TP));
	return 1;
    } else if(str=="elements"||str=="elementals"||str=="elemental skills") {
	write(info_elements(TP));
	return 1;
    }
    if(do_info(str))
	return 1;
    notify_fail("Info on what?\nSyntax: info [all/mana/skills/general/forms/elements]\n");
    return 0;
}

int
do_mana(string str)
{
    if(!strlen(str)) {
	write(info_mana(TP));
	return 1;
    }
    return 0;
}

#define LIVE_O_CONSENTRATES_SPELL "_live_o_consentrates_spell"

int
do_stop(string str)
{
    mixed spell;

    notify_fail("Stop what? The world?\n");
    if (str != "spell")
	return 0;

    spell = TP->query_prop(LIVE_O_CONSENTRATES_SPELL);

    if(stringp(spell))
	spell = find_object(spell);
    if(!spell)
	return 0;

    spell -> remove_object();
    TP->remove_prop(LIVE_O_CONSENTRATES_SPELL);
    write("You stop chanting upon the spell.\n");
    say(QCTNAME(TP)+" stops chanting on the spell.\n");
    return 1;
}


/* ************************************************************************** *
    Here follows the handling of the different spell lists, which realy are
    just sole standing objects.
 * ************************************************************************** */

do_slist(string str)
{
    int i;
    object *lists;
    object list;

    notify_fail("Syntax: slist all\n"+
		"        slist <what lists>\n");

    lists = query_lists(TP);

    if(!str || str=="all" || str=="all lists" ||str=="lists") {
	if(sizeof(lists)==0)
	    return notify_fail("You have no spell lists.\n");
	write("You know the following spell lists:\n");
	write("-------------------------------------------\n");
	for(i=0;i<sizeof(lists);i++)
	{
	    list = lists[i];
	    write("["+list->query_list_short()+"]  "+
		  CAP(list->query_list_name())+" (Of "+CAP(list->query_realm())+").\n");
	}
	write("-------------------------------------------\n");
	return 1;	
    }

    if(sizeof(lists)) {
	for(i=0;i<sizeof(lists);i++)
	    if(lists[i]->id(str))
		lists[i]->list_me();
	return 1;
    }
    return 0;
}

/*
 * Function:	list_level
 * Description: Support function to show how many spells a caster
 *		knows in a list.
 */
int
list_level(object who, int exp)
{
    return MIN(level(who), 1 + who->exp_to_stat(exp)/4);
}

/*
 * Function: do_level
 * Desc:     Code for the spell user to know his current spell level.
 */
int
do_level(string str) 
{
    if( (str && str=="me") || !str) {
	write("You are a "+num2order(level(TP))+" level spell caster.\n");
	return 1;
    }
    return 0;
}

/*
 * Function:	do_teach
 * Desc:	Lets a wizard teach other a spell list.
 */
int
do_teach(string str)
{
    object who;
    string name, what;
    string *lists;
    int i, ind;

    if(!strlen(str) || !TP->query_wiz_level())
	return 0;

    if(sscanf(str, "%s to %s", what, name)!=2)
	return notify_fail("Teach what to whom?\n");

    who = present(name, EP);

    if(!who || !living(who))
	return notify_fail("Teach who?\n");

    lists = query_lists(TP, what);

    if(sizeof(lists)) {
	for(i=0;i<sizeof(lists);i++)
	{
		write("You teach the " + lists[i]->query_list_name() +
		      " spell list to " + who->query_the_name(TP) + ".\n");
		who->catch_msg(
		    QCTNAME(TP) + " teaches you a spell list which is called " +
		    lists[i]->query_list_name() + " spell list.\n");
		tell_room(QCTNAME(TP) + " teaches " + QTNAME(who) + " something.\n", who);

		ind = member_array(lists[i], LIST_FILES );
		if(ind >= 0)
		    who->learn_spell_list(ind);

		who->add_cmdsoul(lists[i]);
	}
	who->update_hooks();
	return 1;
    }
    return notify_fail("You have not got that list, stupid!\n");
}

int
do_learn(string str)
{
    int i;
    int index;
    int num;
    string *files;

    if (!strlen(str) || !TP->query_wiz_level())
	return 0;

    if (sscanf(str, "%d", num)==1)
    {
	TP->learn_spell_list(num);
	return 1;
    }
    else
    {
	files = query_all_lists(str);

	for (i=0; i<sizeof(files); i++)
	{
	    index = member_array(files[i], LIST_FILES);
	    if (index == -1)
	       break;

	    TP->learn_spell_list(index);
	}
	write("Ok.\n");
	return 1;
    }


    return 0;
}

string
learn_prefs(object tp)
{
    int *ids = tp->query_spell_list_ids();
    int *exp = tp->query_spell_list_exp();
    int *lrn = tp->query_spell_list_learn();
    int i, sum;
    string list;
    string ret;

    if(!sizeof(ids))
	return "You have no guild spell lists.\n";

    for(i=0;i<sizeof(ids);i++)
	sum += lrn[i];

    ret =  sprintf("%-30s %-15s Factor     Level\n", "Spell List", "Realm");
    ret += "------------------------------------------------------------------------\n";

    for(i=0;i<sizeof(ids);i++)
    {
	list = LIST_FILES[ids[i]];

	if(catch(list->short())) {
	    if(tp->query_wiz_level())
		ret += "ERROR: "+list+" would not load.\n";
	    continue;
	}

	ret += sprintf("[%s] %-25s %-15s %5d/%d    %3d\n",
		  list->query_list_short(), CAP(list->query_list_name()),
		  "Of "+CAP(list->query_realm()),lrn[i], sum,
		  list_level(tp, exp[i]));
    }
    ret += "------------------------------------------------------------------------\n";

    return ret;
}

int
do_pref(string str)
{
    string who;
    object tp;

    if(TP->query_wiz_level())
    {
	if(!strlen(str)) {
	    write(learn_prefs(TP));
	    return 1;
	}

	if(sscanf(str, "on %s", who)==1)
	{
	    tp = find_player(who);
	    if(!tp)
		return 0;
	    write(learn_prefs(tp));
	    return 1;
	}
    }

    write(learn_prefs(TP));
    return 1;
}

int
do_factor(string str)
{
    string list;
    int num;
    int index;
    int *ids, *lrn;
    int i;

    notify_fail("Syntax: "+query_verb()+" <list> <number>\n");
    if(!strlen(str))
	return 0;
    if(sscanf(str, "%s %d", list, num)!=2)
	return 0;

    ids = TP->query_spell_list_ids();
    lrn = TP->query_spell_list_learn();

    if(!sizeof(lrn))
	return notify_fail("But.. You don't know any spell lists to "+query_verb()+"!\n");

    index = -1;
    for(i=0;i<sizeof(ids);i++)
	if(LIST_FILES[ids[i]]->id(list))
	{
	    index = i;
	    break;
	}

    if(index==-1)
	return notify_fail("Which list do you want to "+query_verb()+"?\n");

    if(num<1 || num>1000)
	return notify_fail(CAP(query_verb())+" list only allowed in range 1..1000.\n");

    lrn[index] = num;
    TP->set_spell_list_learn(lrn);
    write("New setting:\n");
    write(learn_prefs(TP));
    return 1;
}


int
do_forget(string str) {
    string list;
    int *ids;
    int i, index;

    notify_fail(CAP(query_verb()) + " what?\n"
	      + "Syntax: " + query_verb() + " <spell list>\n");

    if (!str)
	return 0;
    
    str = lower_case(str);

    ids = TP->query_spell_list_ids();
    if(!sizeof(ids))
	return notify_fail("But you haven't got a spell list.\n");

    index = -1;
    for(i=0;i<sizeof(ids);i++)
	if(LIST_FILES[ids[i]]->id(str))
	{
	    index = i;
	    break;
	}

    if(index==-1)
	return notify_fail("Which list do you want to "+query_verb()+"?\n");

    list = LIST_FILES[ids[index]];

    TP->forget_spell_list(index);

    write("You erase the "+list->query_list_name()+" from your memory.\n");
    say(QCTNAME(TP) + " tears " + HIS_HER(TP) + " spell list apart.\n");

    return 1;
}

/*
 * Function name:   do_chant
 * Arguments:	    arg - the argument
 * Description:     Let the spell caster decide for how long he/she
 *		    wants to chant a spell before cast.
 */
int
do_chant(string arg)
{
    string timestr;
    int time;

    notify_fail("Chant how?\n" +
	    "Syntax: chant spells in <time_desc>\n" +
	    "        chant spells <time_desc> faster\n" +
	    "        chant spells <time_desc> more\n" +
	    "        chant spells normally\n" +
	    "        chant time\n" +
	    "Where <time_desc> is as an example:\n" +
	    "    two seconds, 14 seconds, a minute, 1/2 minute etc.\n");

    if (!strlen(arg))
	return 0;

    if (parse_command(arg, ({}), "[spells] [time] 'normally' / 'normal' / 'standard'"))
    {
	TP->set_chanting_time(0);
	TP->set_relative_chanting_time(1);
	write("Ok, you now chant spells in normal time.\n");
	return 1;
    }

    if (parse_command(arg, ({}), "[for] [how] [long] 'time'"))
    {
	time = TP->query_chanting_time();

	if (time<0)
	{
	    write("You are chanting spells " + LANG_WNUM(-time)
		+ " seconds faster than normally.\n");
	    return 1;
	}

	if (time == 0)
	{
	    write("You are chanting spells normally.\n");
	    return 1;
	}

	if (TP->query_relative_chanting_time())
	{
	    write("You are chanting spells " + LANG_WNUM(time)
		+ " seconds longer than normally.\n");
	    return 1;
	}

	write("You will now chant all your spells for " + LANG_WNUM(time)
	    + " seconds.\n");

	return 1;
    }
    if (parse_command(arg, ({}), "[spells] [time] %s 'faster' / 'quicker'", timestr))
    {
	time = PARSE_FILE->get_time(timestr);

	if (time == 0)
	{
	    write("Sorry, didn't understand your time description.\n");
	    return 1;
	}

	TP->set_relative_chanting_time(1);
	TP->set_chanting_time(-time);
	write("Ok, you will now chant your spells " + LANG_WNUM(time) +
	      " seconds faster.\n");
	write("Note that it is difficult to cast spells faster than normal.\n");
	return 1;
    }

    if (parse_command(arg, ({}), "[spells] [time] %s 'more' / 'longer' / 'slower'", timestr))
    {
	time = PARSE_FILE->get_time(timestr);

	if (time == 0)
	{
	    write("Sorry, didn't understand your time description.\n");
	    return 1;
	}

	TP->set_relative_chanting_time(1);
	TP->set_chanting_time(time);
	write("Ok, you will now chant your spells " + LANG_WNUM(time) +
	      " seconds longer than normally.\n");
	return 1;
    }

    if (parse_command(arg, ({}), "[spells] 'time' / 'for' / 'in' %s", timestr))
    {
	time = PARSE_FILE->get_time(timestr);

	if (time == 0)
	{
	    write("Sorry, didn't understand your time description.\n");
	    return 1;
	}

	if (time < 2)
	    time = 2;
	if (time > 60)
	    time = 60;

	TP->set_relative_chanting_time(0);
	TP->set_chanting_time(time);

	write("Ok, you will now chant all your spells " + LANG_WNUM(time) +
	      " seconds.\n");
	return 1;
    }

    return 0;
}

/*
 * Function name:   do_sinfo
 * Arguments:	    arg - the spell the caster wants to obtain info about.
 */
