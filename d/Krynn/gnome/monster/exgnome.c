/* A gnome especially equipped for working at ...: THE MACHINE!
 * Created by Dajala
 * Latest update 20.03.95
 *
 * Navarre December 29th 2007
 * Changed "@@brain" and "@@do_flick" to brain and do_flick as is
 * the preferred VBFC way.
 * Also changed those two functions to return a string rather than
 * void.
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h> /* This is needed to be able to use the macros, IS_CLONE */
inherit M_FILE

/* Global variables */
object this_room;
int lassie;
string wolf, area;

/* Prototypes */
void get_guards(string str);
string namer();
string do_flick();
string brain();

void
create_krynn_monster()
{
    int i;
    string name, *word;

    set_name("gnome");
    add_name("exgnome");
    add_name("emong");
    set_living_name("gnome");
    name = namer();
    set_short(name);
    word = explode(name, " ");
    set_adj(word[0]);
    set_long("A very industrious little gnome. He is working at the "
	+ "huge machine in the middle of the room. He seems busy, but it's"
	+ " not clear whether he is actually achieving anything.\n");
    set_race_name("gnome");

    if (!IS_CLONE) /* Added by Nick, to get rid of some possible errors. */
	return;

    add_prop(NPC_I_NO_LOOKS, 1);

    set_gender(random(2));
    add_act(brain);
    add_act(do_flick);
    add_cact("say HeyHaveYouLostYourMind?");
    add_cact("say SomebodyGetTheGuards!  I'llStallThem...");
    add_cact("say WhereWasThatFlameThrower?");
    set_act_time(9 + random(3));
    set_cact_time(10);
    for (i = 0; i < 6; i++)
	set_base_stat(i, 15 + random(25));
    set_hp(10000);
    set_alignment(100);
    set_all_hitloc_unarmed(30);
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
    clone_object(OBJ + "lhelmet2")->move(TO);
    command("wear all");
    command("wield hammer");
}

void
strike(string str1, string str2)
{
    string *phrase, temp, killer;

    if ((str1 == "Guard") && (str2 == "Where?\n") && (lassie == 1))
    {
	lassie = 0;
	set_alarm(3.0, -1.0, "cry_wolf");
    }
    if (str1 != "Gnome")
	return;
    phrase = explode(str2, " ");
    if ((phrase[0] == "Help!") && (phrase[1] == "Stop") &&
	(phrase[2] == "this"))
    {
	if ((!phrase[3]) || (!phrase[4]))
	{
	    command("emote looks puzzled.");
	    return;
	}
	killer = phrase[3] + " " + extract(phrase[4], 0, strlen(phrase[4]) - 3);
	if (random(4))
	{
	    area = environment(TO)->area();
	    wolf = killer;
	    lassie = 1;
	    command("say I'llGoGetTheGuards!");
	    set_alarm(1.0, -1.0, "get_guards", killer);
	}
	else
	{
	    command("shout ToArms!");
	    set_alarm(1.0, -1.0, "react", killer);
	}
    }
}

void
react(string killer)
{
    command("kill " + killer); 
}

string
namer()
{
    string *desc1, *desc2;
    string name;
    int a, b;
 
    desc1 = ({"small", "stout", "fat", "short", "clever" });
    desc2 = ({"red-bearded", "blue-eyed", "elderly", "white-haired" });
    a = random(4);
    b = random(4);
    name = desc1[a] + " " + desc2[b] + " gnome";
    return name;
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if (QRACE(ob) == "gnome")
    {
	command("shout Traitor!  Howdareyouhowcouldyouyouwillsurelypay.");
	write_file("/d/Krynn/gnome/log/fight.log", ob->short() + " " +
	    ob->query_nonmet_name() + "\n");
	say("A scuffle breaks out among the gnomes, and one is carted off.\n");
	write("Your brethren grab you and cast you out of their home!\n");
	write("You are now persona non grata among the gnomes. Try helping "
		+ "a gnome in need to redeem yourself.\n");
	TP->move_living("this happy gnomish place..", TDIR + "entrance.c");
    }
    else
      command("say Help! Stop this "+ ob->query_adj() + " " +
	      QRACE(ob) + "!");
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
    int i;
    string way;
    way = environment(this_object())->tohelp();
    command("say "+ str + " on the loose!");
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
brain()
{
    int i;
    
    i = random(3);
    if (i == 1)
    {
	command("say SoonMyMachineWillBeWorking!");
	command("say I'llBeFamous!");
	command("smile");
    }
    else if (i == 2)
    {
	command("say NeedsMoreBellsAndWhistlesAndStuff.");
    }
    else
    {
	command("say WhatHappensWhenIPullThisLever?");
	command("grin");
    }
    return "";
}

string
do_flick()
{
    command("say LookAtWhatI'veFoundHere.");
    command("say ThatIsReallyInteresting.");
    command("flick");
    return "";
}

void
cry_wolf()
{
	command("say " + area + "! It'sA " + wolf + "!");
}

/* triggered from explosroom.c to get light for loading the wagon */

void
do_light()
{
	if (light() < 1)
	{
		command("say WeNeedSomeMoreLightInHere.");
		command("flick");
	}
	command("say WhatAMess!Let'sCleanThatUp.");
}
