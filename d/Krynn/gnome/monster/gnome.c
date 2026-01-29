/* A rather complex being able to react upon threat like fetching the
 * guards, joining the fight or simply leaving.
 * Latest update by Dajala 20.03.1994
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h> /* This is needed to be able to use the macros, IS_CLONE */
#include "../local.h"
inherit M_FILE

/* Global variables */
int lassie;
string wolf, area;

/* Prototypes */
void get_guards(string str);
string namer();
string flee();
string brain();

void
create_krynn_monster()
{
    int i;
    string name, *word;

    set_name("gnome");
    add_name("emong");
    set_living_name("gnome");
    name = namer();
    set_short(name);
    word = explode(name, " ");
    set_adj(word[0]);
    set_long("A very industrious little gnome.  There are so many flitting"
	+ " about, it's hard to keep them straight.  They seem busy, but it's"
	+ " not clear whether they are actually achieving anything.\n");
    set_race_name("gnome");

    if (!IS_CLONE) /* Added by Nick, to get rid of some possible errors. */
	return;

    set_gender(random(2));

    add_prop(NPC_I_NO_LOOKS, 1);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    add_act(brain);
    add_cact("say HeyHaveYouLostYourMind?");
    add_cact("say SomebodyGetTheGuards!I'llStallThem...");
    add_cact("say WhereWasThatFlameThrower?");
    set_act_time(10);
    set_cact_time(5);
    for (i = 0; i < 6; i++)
	set_base_stat(i, 15 + random(25));
    set_hp(10000);
    set_alignment(100);
    set_all_hitloc_unarmed(10);
    set_knight_prestige(-2);

    trig_new("%s 'gives' %s", "gimme");
    trig_new("%s 'says:' %s", "strike");
    set_alarm(1.0, -1.0, "equipme");
}

void
equipme()
{
    seteuid(getuid());
    if (!random(4))
	clone_object(OBJ + "hammer")->move(TO);
    if (!random(4))
	clone_object(OBJ + "cloak")->move(TO);
    if (!random(4))
	clone_object(OBJ + "helmet")->move(TO);
    if (!random(6))
	clone_object(OBJ + "blast_goggles")->move(TO);
    command("wear all");
    command("wield hammer");
}

int
strike(string str1, string str2)
{
    int i;
    string *phrase, temp, killer;

    if ((str1 == "Guard") && (str2 == "Where?\n") && (lassie == 1))
    {
	lassie = 0;
	set_alarm(3.0, -1.0, "cry_wolf");
    }
    if (str1 != "Gnome")
	return 1;
    phrase = explode(str2, " ");
    if ((phrase[0] == "Help!") && (phrase[1] == "Stop") &&
	(phrase[2] == "this"))
    {
	if ((!phrase[3]) || (!phrase[4]))
	{
	    command("emote looks puzzled.");
	    return 1;
	}
	killer = phrase[3] + " " + extract(phrase[4], 0, strlen(phrase[4]) - 3);
	i = random(7);
	if (i <= 3)
	{
	    area = E(TO)->area();
	    wolf = killer;
	    lassie = 1;
	    command("say I'llGoGetTheGuards!");
	    set_alarm(1.0, -1.0, "get_guards", killer);
	}
	else if (i == 6)
	{
	    command("say OhMy,LookAtTheTime...");
	    set_alarm(1.0, -1.0, "react", 1);
	}                     
	else
	{
	    command("shout To arms!");
	    set_alarm(1.0, -1.0, "react", 2, killer);
	}
    }
    return 0;
}

varargs void
react(int how = 0, string killer = "")
{            
   if(how == 1)
	command(flee());
   if(how == 2)
	command("kill " + killer);
}

string
namer()
{
    string *desc1, *desc2;
    string name;
 
    desc1 = ({"small", "stout", "fat", "short", "clever" });
    desc2 = ({"red-bearded", "blue-eyed", "elderly", "white-haired" });
    name = desc1[random(4)] + " " + desc2[random(4)] + " gnome";
    return name;
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if (QRACE(ob) == "gnome")
    {
	command("shout Traitor! Howdareyouhowcouldyouyouwillsurelypay.");
	write_file("/d/Krynn/gnome/log/fight.log", ob->short() + " " +
	    ob->query_nonmet_name() + "\n");
	say("\nA scuffle breaks out among the gnomes, and one is carted off.\n");
	write("\nYour brethren grab you and cast you out of their home!\n");
	write("You are now persona non grata among the gnomes. Try helping "
		+ "a gnome in need to redeem yourself.\n");
	TP->move_living("this happy gnomish place..", TDIR + "entrance.c");
	say("\n");
    }
    else
      command("say Help! Stop this " + ob->query_adj() + " "
	      + QRACE(ob) + "!");
}

void
gimme(string str1, string str2)
{
    string *phrase, item, temp;

    phrase = explode(str2, " ");
    if (phrase[0] != "you")
	return;
    temp = phrase[sizeof(phrase) - 1];
    item = extract(temp, 0, strlen(temp) - 3);
    command("say Wow,MyVeryOwn" + C(item) + "!");
    command("say Hey,Thanks," + C(str1) + "!");
    set_alarm(2.0, -1.0, "useit", item);
}

void
useit(string item)
{
    command("wear " + item);
    command("wield " + item);
}

void
get_guards(string str)
{
    string way;

    if(!E(TO)->tohelp())
        return;

    way = E(TO)->tohelp();
    command("say "+ str + " on the loose!");
    command(way);
    if (!random(5))
	command("shout Fire!Murder!Help!");
    if (way == "done")
	command("say AStrangerIsFightingOneOfOurKindred!Help!");
    else
    {    
	command(way);
	set_alarm(3.0, -1.0, "get_guards", str);
    }
}

string
flee()
{
    string way, *exits;
    way = environment(this_object())->wayout();
    if (!stringp(way))
	return "";
    exits = explode(way, " ");
    return exits[random(sizeof(exits))];
}

string
brain()
{
    int i;
    string *stuff;

    stuff = ({"a hammer", "a spring-loaded whatsit",
	"several large balls of string", "a smoking pair of shoes"});
    i = random(5);
    if (!i)
	command(flee());
    else if (i == 1)
    {
	command("say SoonEveryOneWillBeUsingMySteampoweredCatapults!");
	command("say I'llBeFamous!");
	command("emote smiles gnomishly.");
    }
    else if (i == 2)
    {
	command("say NeedsMoreBellsAndWhistlesAndStuff.");
   }
    else if (i == 3)
    {
	command("say WhatHappensWhenIPullThisLever?");
	command("grin");
    }
    else
    {
	tell_room(environment(), "A gnome runs by carrying " +
	    stuff[random(sizeof(stuff))] + ".\n");
    }
    return "";
}

void
cry_wolf()
{
    command("say " + area + "! It'sA " + wolf + "!");
}
