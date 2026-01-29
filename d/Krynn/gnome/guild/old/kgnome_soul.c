/*
 * Gnome_soul.c
 *
 * This soul holds the general commands and feelings of the Krynn
 * Gnomes. Begun by Percy.
 * Completed by Dajala.
 */

inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include "../guild.h"
#include "../modules.h"

#define HELP_DIR        GGUILD + "log/help_dir/"

/*****************************************************************************
 * Variables that are specific to each player
 *****************************************************************************/
/* for gflag */
#define GFLAG_MESSAGE(xx)        (xx->query_prop("_gnome_s_gflag_message"))
#define SET_GFLAG_MESSAGE(xx,yy) (xx->add_prop("_gnome_s_gflag_message",yy))
/* for idealight */
#define IDEALIGHT_ON(xx)         (xx->query_prop("_gnome_i_light_on"))
#define SET_IDEALIGHT_ON(xx,yy)  (xx->add_prop("_gnome_i_light_on",yy))
/* for analyze */
#define ANALYZE_ALARM(xx)        (xx->query_prop("_gnome_i_analyze_alarm"))
#define SET_ANALYZE_ALARM(xx,yy) (xx->add_prop("_gnome_i_analyze_alarm",yy))

/*****************************************************************************
 * Soul identifying and autoloading
 *****************************************************************************/

string get_soul_id() { return "Krynn Gnomes"; }

int query_cmd_soul() { return 1; }

/*****************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 *****************************************************************************/

mapping
query_cmdlist()
{
    seteuid(getuid());
    return ([
	     "analyze":"analyze",
	     "gbored":"gbored",
	     "build":"build",
	     "check":"check",        /* module, flag 3 */
	     "engulf":"engulf",      /* module, flag 3 */
	     "feed":"feed",          /* module, flag 7 */
	     "gflag":"gflag",        /* module, flag 1 */
	     "gset":"set_message",   /* module, flag 1 */
	     "gidea":"idea_light",   /* module, flag 0 */
	     "glint":"glint",
	     "gmarvel":"gmarvel",
	     "gmarv":"gmarvel",
	     "gnlist":"gnlist",
	     "gnli":"gnlist",
	     "gsay":"gsay",
	     "-":"gsay",
	     "gsmile":"gsmile",
	     "gthink":"gthink",
	     "gthi":"gthink",
	     "gtinker":"gtinker",
	     "gtink":"gtinker",
	     "help":"help",
	     "ignite":"ignite",      /* module, flag 3 */
	     "makecoffee":"makecoffee", /* module, flag 6 */
	     "measure":"measure",    /* module, flag 5 */
	     "no":"no",
	     "philosophy":"philosophy",
	     "philo":"philosophy",
	     "refresh":"refresh",    /* module, flag 2 */
	     "switch":"ext_engine",  /* module, flag 3 */
	     "toot":"toot",          /* module, flag 3 */
	     "travel":"travel"       /* module, flag 4 */
	     ]);
}

static mixed
parse_this(string str, string form)
{
    object   *oblist, *tmplist;
    int      i;

    tmplist = ({});
    if (!CAN_SEE_IN_ROOM(this_player()))
	return tmplist;

    if (!str || (!parse_command(lower_case(str), environment(this_player()),
			 form, oblist)))
	return ({});

    oblist = NORMAL_ACCESS(oblist, 0, 0);

    if (!sizeof(oblist))
	return ({});

    for (i = 0; i < sizeof(oblist); i++)
    {
	if (objectp(oblist[i]) && living(oblist[i]) &&
		(this_player() != oblist[i]) &&
		CAN_SEE(this_player(), oblist[i]))
	    tmplist = tmplist + ({ oblist[i] });
    }
    return tmplist;
}


/******************* general funtions *************************************/

/* returns the gizmo 
 * needed to call functions in the gizmo.
 */

object
find_gizmo(object player)
{
   object ob;
   ob = present("k_gizmo", player);
   return ob;
}


/* checks whether the correct module flag is set in the gizmo 
 * returns 1: module present
 *         0: module not present
 */

int
flag(int number, int break_check_flag)
{
   object gizmo;

   gizmo = find_gizmo(TP);
   if(break_check_flag)
	gizmo->break_chance(number);
   return (gizmo->query_flag(number));
}

/* Checks several parameters int the steamengine module as there is 
 * pressure, fire, wood and water.
 * Returns:  Somethings wrong: The failure message
 *           Nothing wrong:    'ok'
 */

string
steamengine_check(object player)
{
  if(!flag(3,0))
	return "What?\n";

  if(!flag(2,0))
	return "You'll need a waterdispenser first!\n";

   if(!(find_gizmo(player)->check_fire()))
	return "You have no fire in the engine.\n";

   if(!(find_gizmo(player)->check_water()))
	return "You have no water left.\n";

   if(!(find_gizmo(player)->check_steam()))
	return "You do not yet have enough pressure.\n";
   return "ok";
}

/* paralyzes the player for some time
 */

void
paralyze_player(object player, string fail_msg, string stop_msg, int time)
{
    object paralyze;
    setuid(); seteuid(getuid(TO));
    paralyze = clone_object("/std/paralyze");
    paralyze->set_name("_used_analyze_or_traveller_");
    paralyze->set_no_show(1);
    paralyze->set_remove_time(time);
    paralyze->set_stop_message(stop_msg);
    paralyze->set_fail_message(fail_msg);
    paralyze->set_stop_verb("depart"); /* No command to stop the paralyze! */
    paralyze->set_stop_object(0);   /* Use the messages set above */
    paralyze->move(player);       /* Now DO the paralyze */
}

/**************************************************************************
 * Here follow the functions. New functions should be added in alphabetic
 * order.
 **************************************************************************/

/********************* analyze ********************************************/

int
analyze(string str)
{
    mixed *info;
    int success, anzahl, i;
    float ti;
    object ob;
    
    ti = 42.0;
    setuid(); seteuid(getuid(TO));
    NF("You don't know how to do that.\n");
    if((TP->query_skill(SS_BUILD)) < 1)
	return 0;
    NF("Check what?\n");
    if(!str)
	return 0;
    NF("You do not hold a " + str + ".\n");
    ob = P(str, TP);
    if(!ob)
	return 0;
    NF("The " + str + " is too damaged to be analyzed.\n");
    if(ob->query_prop(OBJ_I_BROKEN))
	return 0;
    NF("You see no way of taking it apart.\n");
    if(ob->query_prop(OBJ_M_NO_DROP))
	return 0;

    NF("You are still busy with another object.\n");
    if(ANALYZE_ALARM(TP))
	return 0;

    write("You sit down and start to take apart the " + str + ".\n");
    say(QCTNAME(TP) + " seats " + OBJECTIVE(TP) + "self on the ground "
	+ "and starts to take apart " + POSSESSIVE(TP) + " " + str + ".\n");

    success = (40 * ((TP->query_skill(SS_BUILD)+10) * (90+random(20))) /100) * ((TP->query_stat(3))/5+(TP->query_stat(4)*2/5)+40) /10000;
    if (ob->query_prop(OBJ_I_RES_IDENTIFY))
	success =- (ob->query_prop(OBJ_I_RES_IDENTIFY));
    info = (P(str, TP)->query_prop(MAGIC_AM_ID_INFO));

    SET_ANALYZE_ALARM(TP, set_alarm(6.0, 6.0, "analyze_msg", TP));
    set_alarm(110.0, -1.0, "emergency_remove", ob, TP, str);

    if (!info)
    {
	set_alarm(40.0, -1.0, "no_magic", TP);
	set_alarm(42.0, -1.0, "end", ob, TP, str, ti);
	return 1;
    }
    anzahl = sizeof(info)  / 2;
    if(anzahl == 1)
    {
	if(success >= info[1])
	    set_alarm(40.0, -1.0, "give_info", info[0], TP);
	else
	    set_alarm(40.0, -1.0, "fail", TP);
	set_alarm(42.0, -1.0, "end", ob, TP, str);
	return 1;
    }

    if(info[1]<info[anzahl*2-1])
    {
	for (i=0; i<anzahl; i++)
	{
	    if(success>=info[2*i+1])
	    {
		ti = 42.0+itof(i*3);
		set_alarm(40.0+itof(i*3), -1.0, "give_info", info[2*i],
			TP, ti);
	    }
	}
    }
    else
    {
	for (i=anzahl-1; i>-1; i--)
	{
	    if(success>=info[2*i+1])
	    {
		ti = 42.0+itof(anzahl*3)-itof(i*3);
		set_alarm(40.0+itof(anzahl*3)-itof(i*3), -1.0, "give_info",
			info[2*i], TP, ti);
	    }
	}
    }
    if (ti < 42.5)
	set_alarm(ti , -1.0, "fail", TP);
    else
	paralyze_player(TP, "You are too absorbed with taking apart "
	+ "your " + str + ".\n", "", ftoi(ti));
    set_alarm(ti, -1.0, "end", ob, TP, str, ti);
    return 1;
}

void
analyze_msg(object player)
{
    int a;
    string *msg;

    msg = ({"take", " away some parts", "remove", " some bits", "look",
	 " at some bits", "check", " some especially interesting parts", 
	"look", " thoughtfully", "put", " aside some parts"});
    a = random(6);
    player->catch_msg("You " + msg[a*2] + msg[a*2+1] + ".\n");
    tell_room(E(player), QCTNAME(player) + " " + msg[a*2] + "s" 
	+ msg[a*2+1] + ".\n", player);
}

void
give_info(string str, object ob, float ti)
{
    if (ti < 42.5)
	ob->catch_msg("You get to know the following:\n");
    remove_alarm(ANALYZE_ALARM(ob));
    SET_ANALYZE_ALARM(ob,0);
    ob->catch_msg(str);
}

void
fail(object player)
{
    player->catch_msg("You couldn't find anything out.\nThis task seems to "
	+ "be beyond your skill.\n");
    tell_room(E(player), QCTNAME(player) + " seems to be finished but looks"
	+ " unhappy.\n", player);
    remove_alarm(ANALYZE_ALARM(player));
    SET_ANALYZE_ALARM(player,0);
}

void
end(object ob, object player, string str, float time)
{
    object heap;

    if(abs(time) > 42.5)
	player->catch_msg("This is all information you could find out.\n");
    heap = clone_object(GOBJ + "heap");
    heap->add_prop(OBJ_I_WEIGHT, (ob->query_prop(OBJ_I_WEIGHT)));
    heap->add_prop(OBJ_I_VOLUME, (ob->query_prop(OBJ_I_VOLUME)));
    heap->move(E(TP));
    tell_room(E(player), PRONOUN(player) + " drops something.\n", player);
    ob->remove_object();
    player->catch_msg("You drop the now useless parts of the " + str + ".\n");
}

void
no_magic(object player)
{
    player->catch_msg("This object doesn't seem to be magical.\n");
    remove_alarm(ANALYZE_ALARM(player));
    SET_ANALYZE_ALARM(player,0);
}

void
emergency_remove(object ob, object player, string str)
{
   if(ANALYZE_ALARM(player))
   {
	fail(player);
	player->catch_msg("Something seems to be wrong with the item you "
		+ "tried to analyze. Please leave a bugreport where you "
		+ "found it.\n");
	end(ob, player, str, 1.0);
   }
}


/******************** gbored **********************************************/

int
gbored()
{
	write("YAWN... Again, there is nothing to do for your superior "
		+ "intellect.\n");
	say(QCTNAME(TP) + " yawns. There is no real challenge for "
		+ OBJECTIVE(TP) + " in the world today.\n");
	return 1;
}

/******************** build **********************************************/

int
build(string str)
{
	int alarm;
	object kit;

	if(!GMEMBER(TP))
		return 0;
	if(!P("kit", TP))
		return 0;
	NF("You don't have that kit.\n");
	if(!(kit = P("kit_for_" + str, TP)))
		return 0;
	NF("You don't know how to do that.\n");
	if((TP->query_skill(SS_BUILD)) < 1)
		return 0;
	write("You start assembling the parts.\n");
	say(QCTNAME(TP) + " sits down and starts working on something.\n"
		+ C(PRONOUN(TP)) + " seems to be completely absorbed.\n");
	paralyze_player(TP, "You are completely absorbed by building " 
		+ "the " + str + ".\n", "", 30);
	alarm = set_alarm(6.0, 6.0, "build_msg", TP);
	set_alarm(38.0, -1.0, "build_ready", TP, kit, alarm);
	return 1;
}

void
build_msg(object player)
{
	int a;
	string *msg;
	msg = ({"put together some parts","add some springs","add some wheels",
		"add a whistle", "add a bell"});
	a = random(4);
	player->catch_msg("You " + msg[a] + ".\n");
	tell_room(E(player), QCTNAME(player) + " " + msg[a][0..2] 
		+ "s" + msg[a][3..] + ".\n", player);
}

void
build_ready(object player, object kit, int alarm)
{
	int skill, min_skill, i;
	string type;

	remove_alarm(alarm);
	tell_room(E(player), QCTNAME(player) + " finished " +
		POSSESSIVE(player) + " work.\n", player);
	player->catch_msg("You finished your new module!\n");
	skill = (TP->query_skill(SS_BUILD));
	type = (kit->get_type());
	for(i=0;i<sizeof(TYPES);i++)
	{
		if(type == TYPES[i])
			min_skill = MIN_SKILLS[i];
	}

	if(skill < min_skill)
	{
		kit->is_bomb();
		if(skill > (min_skill - 10))
			player->catch_msg("But somehow, what you built "
				+ "doesn't look right.\n");
	}
	kit->set_short("readyToAttach" + capitalize(type));
	kit->set_long("This " + capitalize(type) + "-module is ready "
		+ "to attach to the gizmo.\n"); 
	kit->set_built();
	kit->set_break_chance(skill - min_skill);
	kit->add_name("module");
	/*tell_room(E(player), "skill: " + skill + " / min_skill: " + min_skill);*/
}


/****************** module: the gnomish recycler***************************
 *                           flag:   7                                    *
 **************************************************************************/
int
feed(string str)
{
   NF("What?\n");
   if(!flag(7,1))
	return 0;


}

/************* module: flag with individual message ***********************
 *                           flag:   1                                    *
 **************************************************************************/
int
gflag(string name)
{
   object ob, *oblist;
   
   NF("What?\n");
   if (!flag(1,1))
	return 0;

   NF("You haven't set a message yet.\n");
   if (!GFLAG_MESSAGE(TP))
     return 0;

   NF("I cannot see " + name + " here.\n");
   ob = P(name,E(TP));
   if (!ob)
	return 0;

   if (!living(ob))
	return 0;

   NF("You have a look at your flag.\n");
   if(TP == ob)
	return 0;   

   TP->catch_msg("You release the little flag to quickly talk to " + 
	TP->query_the_name(ob) + ".\n");
   ob->catch_msg(QCTNAME(TP) + " presses a button on " + POSSESSIVE(TP)
	+ " gizmo which then sproings a little flag at you, reading:\n"
	+ GFLAG_MESSAGE(TP) + "\n");
   oblist = ({ob, TP});
   tell_room(E(TP), QCTNAME(TP) + " talks to " + QTNAME(ob) + " by producing "
	+ "a little flag.\n", oblist);
   return 1;
}

int
set_message(string str)
{
   NF("What?\n");
   if (!flag(1,0))
	return 0;

   NF("Inscribe what message?\n");
   if (!str)
	return 0;

   if (GFLAG_MESSAGE(TP))
	write("You erase the old inscription and put down the new one.\n");
   else write("You inscribe your message onto the little flag.\n");
   say(QCTNAME(TP) + " does something to " + POSSESSIVE(TP) + " gizmo.\n");
   SET_GFLAG_MESSAGE(TP,str);
   return 1;
}

/********************* glint *********************************************/

int
glint(string str)
{
   object target, *oblist;
   NF("Glint at whom?");
   if(!str)
   {
	write("A nasty gleam appears in your eyes.\n");
	tell_room(E(TP), "A nasty gleam appear in " + QTNAME(TP)
		+ "s eyes and you wonder what " + PRONOUN(TP) + " might "
		+ "be thinking.\n", TP);
	return 1;
   }
   if(living(target = (P(str, E(TP)))))
   {
	NF("You try to glint at yourself but fail.\n");
	if(target == TP)
		return 0;
	oblist = ({target, TP});
	TP->catch_msg("You look at " + QTNAME(target) + " with a nasty gleam "
		+ "in your eyes.\n");
	target->catch_msg(QCTNAME(TP) + " looks at you with a nasty "
		+ "gleam in " + POSSESSIVE(TP) + " eyes.\n");
	tell_room(E(TP), QCTNAME(TP) + " looks at " + QTNAME(target)
		+ " with a nasty gleam in " + POSSESSIVE(TP)
		+ " eyes.\n", oblist);
	return 1;
   }
   return 0;
}

/********************* gmarvel *******************************************/

int
gmarvel(string str)
{
	
	NF("Which race?\n");
	if (!str)
	{
		write("You marvel at the wonder of it all!\n");
		SAY(" is in awe of such a marvellous idea!");
		return 1;
	}
	if (str == "gnome" || str == "gnomes")
	{
		write("You marvel at the intelligence of your fellow "
			+ "gnomes.\n");
		SAY(" marvels at the amazing intelligence of " 
			+ POSSESSIVE(TP) + " fellow gnomes.");
		return 1;
	}
	if (str == "dwarf" || str == "dwarves")
	{
		write("You can't help but laugh at the stupidity of these "
			+ "dwarves.\n");
		SAY(" shakes his head in disbelief at the stupidity of "
			+ "dwarves.");
		return 1;
	}
	if (str == "elf" || str == "elves")
	{
		write("Ha! Sometimes elves can be soooo stupid!\n");
		SAY(" can't believe elves could be soooo stupid!");
		return 1;
	}
	if (str == "goblin" || str == "goblins")
	{
		write("Well noone said goblins were gifted with intelligence.\n");
		SAY(" smiles sympathetically at the stupidity of some "
			+ "goblins.");
		return 1;
	}
	if (str == "human" || str == "humans")
	{
		write("I guess bigger doesn't mean brainier in this case "
			+ "anyway.\n");
		SAY(" wonders if the size of some humans is proportionate "
			+ "to their stupidity!");
		return 1;
	}
	if (str == "hobbit" || str == "hobbits")
	{
		write("Ye gods! are these hobbits really as stupid as they "
			+ "look!\n");
		SAY(" sighs in exasperation at the lack of intelligence to "
			+ "be found in the average hobbit.");
		return 1;
	}
	return 0;
}

/********************* gnlist ********************************************/

int
gnlist(string str)
{       
	object *players;
	int i;
	
	players = users();
	write("The following Inventors are currently logged on:\n");
	for (i = 0; i < sizeof(players); i++)
	{
		if (players[i]->query_gnome_level() && 
			 players[i]->query_invis() == 0 &&
			extract(players[i]->query_name(), -2) != "jr")
			write(players[i]->query_name() + " " +
			players[i]->query_title() + "\n");
	}
	return 1;
}

/******************gsay****************************************************/

int
gsay(string str)
{
	string *words, sentence;
	int i;

	if(!str)
	{
		write("You didn't say much.\n");
		return 1;
	}
	words = explode(str, " ");
	for (i = 0; i<sizeof(words); i++)
		words[i]=capitalize(words[i]);
	sentence = implode(words,"");
	SAY(" says: " + sentence);
	if (TP->query_get_echo())
	{
		write(BS("You say: " +  sentence, 70));
	}
	else
	{
		write("Ok.\n");
	}
	return 1;


}

/********************* gsmile ********************************************/
int
gsmile()
{
	write("You smile gnomishly.\n");
	SAY(" smiles gnomishly.");
	return 1;
}

/********************* gthink ********************************************/
int
gthink()
{
	write("You think hard for a solution to the problem...\n");
	SAY(" screws " + POSSESSIVE(TP) + " face up and appears to be deep "
		+ "in thought.");
	return 1;
}

/********************* gtinker *******************************************/

int 
gtinker(string str)
{
	object ob, *oblist;
	NF("I can't see that object here.\n");
	if (!str)
	{
		write("You must say which object to tinker with.\n");
		return 1;
	}
	if (ob = P(str,E(TP)))
	{
		if (!living(ob))
		{
			write("You tinker away at the " + str + " with your "
				+ "gizmo.\n");
			SAY(" gets out a wierd device and starts tinkering "
				+ "with the " + str);
			return 1;
		}
		oblist = ({TP, ob});
		TP->catch_msg("You start looking for ways to improve "
			+ QTNAME(ob) + ".\n");
		tell_room(E(TP), QCTNAME(TP) + " looks at " + QTNAME(ob)
			+ " strangely, as if eyeing " + OBJECTIVE(ob)
			+ " up for some devilish experiment.\n", oblist);
		if(ob != TP)
		    ob->catch_msg(QCTNAME(TP) + " looks at you strangely, "
			+ "as if eyeing you up for some devilish "
			+ "experiment.\n");
		return 1;
	}
	return 0;
}

/********************* help *************************************************/

int
help(string str)
{
    string subject, filename;

    if (!str)
	return 0;

    if (sscanf(str, "gnomes %s", subject) != 1)
      if (sscanf(str, "gnome %s", subject) != 1)
	return 0;

    filename = HELP_DIR + subject;
    if (file_size(filename) > 0)
    {
	write("\n");
	setuid();
	seteuid(getuid());
	cat(filename);
	write("\n");
	return 1;
    }

    NF("No help on that subject I'm afraid.\n");
    return 0;
}
/********************* module: coffeemaker ********************************
 *                     flag:   5                                          *
 **************************************************************************/

int
makecoffee(string str)
{
   int coffee_alarm;
   string result;

   NF("What?\n");
   if(!flag(6,1))
	return 0;

   result = steamengine_check(TP);
   if(result == "What?\n")
	result = "You'll need a steamengine first.\n";
   if(result != "ok")
   {
	write(result);
	return 1;
   }

   write("You press the button requesting a cup of HOT coffee "
	+ "and wait ...\n");
   tell_room(QCTNAME(TP) + " does something to " + POSSESSIVE(TP) 
	+ " gizmo but nothing seems to happen ... yet.\n");
   coffee_alarm = set_alarm(5.0, 5.0, "coffee_msg", TP);
   set_alarm(26.0, -1.0, "coffee_2", TP, coffee_alarm);
   return 1;
}

void
coffee_msg(object player)
{
   int a;
   string *msg = ({"You hear nothing ..", "The coffemaker rumbles "
	+ "dangerously", "The whole gizmo shakes fiercly", "A valve opens "
	+ "and releases a cloud of steam", "Something rattles noisily inside "
      "the gizmo", "A smelly brownish liquid drips from your gizmo",
	  "The coffeemaker creates a buzzing sound"}) 
      , *telr = ({"", QCTNAME(player) + "'s gizmo shakes fiercly.\n"
	, QCTNAME(player) + " releases a cloud of steam.\n"
	, QCTNAME(player) + "'s gizmo rattles noisily.\n", QCTNAME(player) 
	+ " produces a smelly brownish liquid which drops to the floor.\n"
	, "You hear a buzzing sound.\n"});
   
    a = random(7);
   player->catch_msg(msg[a] + ".\n");
   tell_room(telr[a] , player);
   return;
}

void
coffee_2(object player, int coffee_alarm)
{
   remove_alarm(coffee_alarm);
   find_gizmo(player)->reduce_water();
   if (!random(5))
   {     
	player->catch_msg("A stream of hot coffee splashes into the "
		+ "dispensing chamber. Then a cup arrives. Frustrated you "
		+ "recycle the cup.\n");
	if(!random(5))
		player->catch_msg("You make a note you want to hand to "
			+ "the responsible comittee on next occasion.\n");
	tell_room(QCTNAME(player) + " recieves some hot coffee, then "
		+ "a cup.\n", player);
	return;
   }
   player->catch_msg("A cup appears in the dispensing slot which is "
	+ "rapidly filling with delicious hot coffee.\nYou eagerly "
	+ "take the cup.\n"); 
   tell_room(QCTNAME(player) + " recieves a cup of hot coffee.\n", player);
   setuid();
   seteuid(getuid());
   clone_object(FOOD + "coffee.c")->move(player);
   return;
}

/********************* module: measure ************************************
 *                     flag:   5                                          *
 **************************************************************************/

string
measure_2(object target, string str)
{
	string sht;
	if(living(target))
	  return QTNAME(target) + ".\n";
	if(strlen(sht = (target->query_short())) == 0)
	  sht = str;
	return "the " + sht + ".\n";
}

int
measure(string str)
{
    object target, *oblist;
    int toflag = 0;
    
    NF("What?\n");
    if (!flag(5,1))
      return 0;

    NF("Measure what?\n");
    if (!str)
      return 0;
    if (str[0..2] == "to ")
      {
	  toflag = 1;
	  str = str[3..];
	  NF("Measure to what?\n");
      }

    oblist = FIND_STR_IN_OBJECT(str,E(TP));
    if (!oblist || !sizeof(oblist))
      return 0;
    
    target = oblist[0];
    if (!toflag)
      {
	  NF("You don't bother with the tape. You know your size.\n");
	  if(target == TP)
	    return 0;
	  TP->catch_msg("You get out your convenient measure tape and "
			+ "measure the size of " + measure_2(target, str)
			+ "You calculate the volume to be about " +
			(target->appraise_volume(50 + TP->query_skill(SS_BUILD) / 2)) +
			".\n");
	  tell_room(E(TP), QCTNAME(TP) + " gets out a "
		    + "measure tape and quickly measures the size "
		    + "of " + measure_2(target, str), ({TP,target}));
	  if(living(target))
	    target->catch_msg(QCTNAME(TP) + " gets out a "
			      + "measure tape and quickly measures your size.\n");
	  return 1;
      }
    else
      {
	  NF("The distance between you and you is zero.\n");
	  if(target == TP)
	    return 0;
	  TP->catch_msg("You get out your convenient measure tape and "
			+ "measure the distance to " + measure_2(target, str));
	  tell_room(E(TP), QCTNAME(TP) + " gets out a "
		    + "measure tape and quickly measures the distance between "
		    + OBJECTIVE(TP) + " and " + measure_2(target, str), ({TP, target}));
	  if(living(target))
	    target->catch_msg(QCTNAME(TP) + " gets out a measure "
				  + "tape and quickly measures the distance between you "
				  + "and " + OBJECTIVE(TP) + ".\n");
	  return 1;
      }
    NF("Measure what?\n");
    return 0;
}

/********************* no *************************************************/

int
no()
{
	write("You shake your head firmly and begin to explain...\n");
	say(QCTNAME(TP) + " shakes " + POSSESSIVE(TP) + " head firmly "
		+ "and begins to explain how things really are...\n");
	return 1;
}

/********************* philosophy *****************************************/

int
philosophy()
{
	write("You think about the universe as such and soon come up with "
		+ "a completely new theory.\n");
	say(QCTNAME(TP) + " pauses to think about the mysteries of the "
		+ "universe, and soon comes up with an entirly new theory.\n");
	return 1;
}

/********************************* module: idea light *********************
 *                                   flag: 0
 **************************************************************************/

int
idea_light()
{
   NF("What?\n");
   if (!flag(0,1))
	return 0;

   NF("The light is already on.\n");
   if(IDEALIGHT_ON(TP))
	return 0;
   write("You switch on your idea light to indicate a fantastic idea.\n");
   say(QCTNAME(TP) + " switches on a tiny light to indicate that "
	+ PRONOUN(TP) + " has a great idea.\n");
   find_gizmo(TP)->add_prop(OBJ_I_LIGHT, 1);
   set_alarm(itof(4 + random(6) + TP->query_skill(SS_BUILD) / 6), -1.0, "outout", TP);
   SET_IDEALIGHT_ON(TP,1);
   return 1;
}

void
outout(object player)
{
    player->catch_msg("The light flickers out.\n");
    tell_room(E(player), QCTNAME(player) + "'s light flickers and goes "
	+ "out.\n", player);
    find_gizmo(player)->add_prop(OBJ_I_LIGHT, 0);
    SET_IDEALIGHT_ON(player,0);
}


/******************************* module: water dispenser ******************
 *                                 flag: 2
 **************************************************************************/

void
do_refresh(object player)
{
   if ((player->query_fatigue()) > ((player->query_max_fatigue()) - 20))
	player->set_fatigue(player->query_max_fatigue());
   else
	player->add_fatigue(20);
}

int
refresh(string str)
{
   int number;
   object target, *oblist;

   NF("What?\n");
   if (!flag(2,1))
	return 0;

   NF("You don't have any water left.\n");
   if(!find_gizmo(TP)->check_water())
	return 0;

   NF("Refresh whom?\n");
   if (!str)
	return 0;

   write("You release a splash of water ");
   tell_room(E(TP), "A splash of water spurts forth out of " + QTNAME(TP)
	+ "'s gizmo", TP);
   find_gizmo(TP)->reduce_water();

   number = random(10);
   if (number < 2 || str == "me" || str == "myself" || str == lower_case(TP->query_name()))
   {
	if ((TP->query_stat(1)) >= (random(40) + 10) && number > 1)
	{
	   write("and skillfully catch it with your mouth.\n");
	   say(", which " + PRONOUN(TP) + " skillfully directs into "
		+ POSSESSIVE(TP) + " mouth.\n");
	}
	else
	{
	   write("which misses your mouth but hits your nose! You feel refreshed "
		+ "though.\n");
	   say(" and hits " + OBJECTIVE(TP) + "self in the face.\n");
	   do_refresh(TP);
	}
	return 1;
   }

   target = present(str, E(TP));
   if (!target)
   {
	write("but cannot find your target.\n");
	say(".\n");
	return 1;
   }

   if (!living(target))
   {
	write("and soak the " + str + ".\n");
	say(" soaking the " + str + ".\n");
	return 1;
   }

   oblist = ({target, TP});
   if ((target->query_stat(1)) >= (random(140) + 20))
   {
	TP->catch_msg("and refresh " + QTNAME(target) + ".\n");
	tell_room(E(target), " which " + target->query_the_name(target) + " skillfully "
		+ "catches with " + OBJECTIVE(target) + " mouth.\n"
		,oblist);
	target->catch_msg(" which you skillfully catch with your mouth.\n");
	return 1;
   }
   TP->catch_msg("and hit " + QTNAME(target) + " in the face.\n");
   tell_room(E(TP), " which " + QTNAME(target) + " gets in the face.\n"
	,oblist);
   target->catch_msg(" hits you between the eyes! You feel refreshed.\n");
   do_refresh(target);
   return 1;
}


/********************** module: steam engine ******************************
 *                        flag: 3                                         *
 **************************************************************************/

int
check(string str)
{
   int res;

   if(str == "water")
   {
	NF("What?\n");
	if(!(flag(2,0)))
	   return 0;
	write("The tank inside the dispenser is ");
	say(QCTNAME(TP) + " does something with " + POSSESSIVE(TP)
		+ " gizmo.\n");
	res = (find_gizmo(TP)->check_water());
	if(res == 30) write("full.\n");
	if(res > 25 && res != 30)write("nearly full.\n");
	if(res > 20 && res < 26) write("well filled.\n");
	if(res > 10 && res < 21) write("about half full.\n");
	if(res > 5  && res < 11) write("quite empty.\n");
	if(res < 6  && res != 0) write("nearly empty.\n");
	if(res == 0) write ("empty.\n");
	return 1;
   }
   NF("What?\n");
   if(!(flag(3,0)))
	return 0;
   NF("Check what?\n");
   if(str != "wood" && str != "engine")
	return 0;

   if(str == "wood")
   {
	write("The storage chamber for wood inside the engine is ");
	say(QCTNAME(TP) + " does something with " + POSSESSIVE(TP)
		+ " gizmo.\n");
	res = (find_gizmo(TP)->check_wood());
	if(res ==12) write("full.\n");
	if(res > 8 && res != 12)write("nearly full.\n");
	if(res > 3 && res <  9) write("about half full.\n");
	if(res < 4 && res != 0) write("nearly empty.\n");
	if(res == 0) write ("empty.\n");
	return 1;
   }
   write("You check the steamengine:\n");
   say(QCTNAME(TP) + " does something with " + POSSESSIVE(TP)
	+ " gizmo.\n");
   if(find_gizmo(TP)->check_fire())
	write("The fire is burning.\n");
   else
   {
	write("The engine is switched off.\n");
	return 1;
   }
   if(find_gizmo(TP)->check_steam())
	write("Pressure of the steam is ok.\n");
   else write("There is not yet enough pressure.\n");
   return 1;
}

int
engulf(string str)
{
   object target, *oblist;
   string result;

   result = steamengine_check(TP);
   if(result != "ok")
   {
	write(result);
	return 1;
   }

   write("You open a valve at the engine and release a cloud of steam");
   say(QCTNAME(TP) + " does something to his gizmo and releases a cloud "
	+ "of steam");
   find_gizmo(TP)->reduce_water();

   if(random (10) < 2 || str == "me" || str == "myself" || str == lower_case(TP->query_name()))
   {
	write(" completely engulfing yourself.\n");
	say(" which engulfs " + OBJECTIVE(TP) + " completely. "
		+ C(PRONOUN(TP)) + " is invisible for a second.\n");
	TP->command("cough");
	return 1;
   }

   target = present(str, E(TP));
   if (!target)
   {
	write(" but cannot find your target.\n");
	say(".\n");
	return 1;
   }

   if (!living(target))
   {
	tell_room(E(TP)," engulfing the " + str + ".\n");
	return 1;
   }

   oblist = ({target, TP});
   if ((target->query_stat(1)) >= (random(80) - 20))
   {
	TP->catch_msg(" but miss " + QTNAME(target) + ".\n");
	tell_room(E(TP), " which closely misses " + QTNAME(target)
		+ ".\n", oblist);
	target->catch_msg(" at you which you can easily evade.\n");
	return 1;
   }
   TP->catch_msg(" engulfing " + QTNAME(target) + ". "
	+ PRONOUN(TP) + " is invisible for a second.\n");
   tell_room(E(TP), " engulfing " + QTNAME(target) + ". " 
	+ capitalize(PRONOUN(target)) + " is invisible for a second.\n"
	, oblist);
   target->catch_msg(" which engulfs you.\n");
   target->command("cough");
   return 1;
}


int
toot()
{
   string *exits;
   int i;
   string result;

   result = steamengine_check(TP);
   if(result != "ok")
   {
	write(result);
	return 1;
   }

   find_gizmo(TP)->reduce_water();
   write("You open a valve of the steam engine.\n");
   say(QCTNAME(TP) + " does something to his gizmo.\n");
   tell_room(E(TP), "Toooooot.\n");

   exits = (E(TP)->query_exit());
   for(i=0; i < sizeof(exits); i+=3)
	tell_room(exits[i], "Tooooot!\n");
   return 1;
}

int
ignite(string str)
{
   NF("What?\n");
   if(!flag(3,1))
	return 0;

   NF("Ignite what?\n");
   if(str != "engine")
	return 0;

   NF("The engine has already been ignited.\n");
   if(find_gizmo(TP)->check_fire())
	return 0;

   NF("There isn't any wood left.\n");
   if(!(find_gizmo(TP)->check_wood()))
	return 0;

   find_gizmo(TP)->burn_wood();
   write("Ok.\n");
   say(QCTNAME(TP) + " does something to " + POSSESSIVE(TP) + " gizmo.\n");
   return 1;
}

int
ext_engine(string str)
{
   NF("What?\n");
   if(!flag(3,0))
	return 0;

   NF("Switch what off?\n");
   if(str != "engine off")
	return 0;

   NF("The engine is already switched off.\n");
   if(!(find_gizmo(TP)->check_fire()))
	return 0;

   write("You extinguish the fire and lower the pressure.\n");
   say(QCTNAME(TP) + " does something to " + POSSESSIVE(TP) + " gizmo.\n");
   find_gizmo(TP)->ext_fire();
}

/********************** module: advance traveller *************************
 *                        flag: 4                                         *
 **************************************************************************/

int
travel(string str)
{
   NF("What?\n");
   if(!(flag(4,1)))
	return 0;

   if(str == "n") str = "north";
   if(str == "ne") str = "northeast";
   if(str == "e") str = "east";
   if(str == "se") str = "southeast";
   if(str == "s") str = "south";
   if(str == "sw") str = "southwest";
   if(str == "w") str = "west";
   if(str == "nw") str = "northwest";

   NF("You cannot travel into that direction.\n");
   if(str!="north"&&str!="northeast"&&str!="east"&&str!="southeast"&&
	str!="south"&&str!="southwest"&&str!="west"&&str!="northwest")
	return 0;       

   TP->catch_msg("You take aim carefully and open the valve...\n");
   say(QCTNAME(TP) + " does something to " + PRONOUN(TP) + " gizmo.\n");
   if(random(100) < 6) 
   {
	set_alarm(4.0, -1.0, "do_whirl", TP, str);
	return 1;
   }
   set_alarm(4.0, -1.0, "do_travel", TP, str, 0);
   return 1;
}

string
check_exit(string direction, object player, int flag)
{
   int i;
   mixed *exits;
   string result;

   result = steamengine_check(player);
   if(flag > 0)
	result = "ok";  /* We are already moving */
   if(result != "ok")
   {
	player->catch_msg("Why...? Nothing happened.\n");
	if(result == "What?\n")
		player->catch_msg("You don't have a steamengine.\n");
	else
		player->catch_msg(result);
	return "fault";
   }
   result = "no_exit";
   exits = (E(player)->query_exit());
   for(i=0;i<sizeof(exits)/3;i++)
   {
	if(exits[3*i+1] == direction)
	{
	    result = exits[3*i];
	    if(exits[3*i+2] != 0)
		result = "no_exit";
	}
   }
   return result;
}

void
do_travel(object player, string direction, int flag)
{
   string exit;

   exit = check_exit(direction, player, flag);
   if(exit == "fault")
	return;
   if(exit == "no_exit" && flag != 0)
   {
	set_alarm(2.0, -1.0, "bonk", player, direction, flag);
	return;
   }
   if(exit == "no_exit")
   {
	player->catch_msg("There is no exit to the " + direction + ".\n");
	return;
   }

   if((find_gizmo(player)->check_water()) > 0)
   {
	if(flag == 0)
	{
	   player->catch_msg("Wwush.... Off you go!\n");
	   tell_room(E(player), "Leaving a lot of steam behind, "
		+ QTNAME(player) + " is  flung " + direction + "wards.\n"
		, player);
	}
	else
	{
	   player->catch_msg("You rush " + direction + "wards.\n");
	   tell_room(E(player), "Leaving a lot of steam behind, a gnome "
		+ "rushes past you to the " + direction + ".\n"
		+ "What a speed!\n", player);
	}
	flag++;
	player->move(exit);
	find_gizmo(player)->reduce_water();
	set_alarm(1.5, -1.0, "do_travel", player, direction, flag);
   }
   else
   {
	player->catch_msg("You suddenly lose control of direction.\n");
	set_alarm(2.0, -1.0, "bonk", player, direction, flag);
   }
}

void
bonk(object player, string direction, int flag)
{
   player->catch_msg("OUCH... you hit something!! Everything goes black"
	+ "...\n");
   tell_room(E(player), "A gnome rushes past you. The next second you "
	+ "hear a terrible crashing sound and see, as you turn, " + QNAME(player)
	+ " lying flat on the ground.\n", player);
   player->heal_hp(-((player->query_max_hp()) / 20) - flag*5);
   if((player->query_hp()) < 0)
   {
	player->do_die();
	return;
   }
   paralyze_player(player, "Your head is too dizzy for that.\n",
	"You can see again.\n", (10+3*flag));
}

string
find_exit(object player)
{
   int a;
   string *exits;

   exits = (E(player)->query_exit());
   a = random((sizeof(exits)/3));
   return exits[a*3+1];
}

void
do_whirl(object player, string str)
{
    string exit = str;
    int tries = 0;

    player->catch_msg("... and release too much steam!\nOops! "
	+ "Something went wrong!\nYou are flung about the "
	+ "room like balloon with a hole in it.\n");
    tell_room(E(player), QCTNAME(player) + " creates a huge cloud "
	+ "of smoke and is flung about the room like a balloon "
	+ "with a hole in it!\n", player);
    while(exit == str && tries < 3)
    {
	exit = find_exit(player);
	tries++;
    }
    set_alarm(5.0, -1.0, "flung_msg", player, exit);
    set_alarm(8.0, -1.0, "do_travel", player, exit, 1);
}

void
flung_msg(object player, string exit)
{
   player->catch_msg("Then the Traveller chooses direction for you!\n");
   tell_room(E(player), QCTNAME(player) + " then leaves to the " + exit 
	+ ".\n", player);
}
