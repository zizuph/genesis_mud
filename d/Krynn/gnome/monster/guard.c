/* A rather complex NPC. When a gnome NPC appears in guard room to report
 * an attack on the gnomish society a conversation evolves and the guards
 * leave the room to find and eliminate the offender.
 * Last update: 20.03.1994 by Dajala
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h> /* This is needed to be able to use the macros, IS_CLONE */
inherit M_FILE

/* Global variables */
object wolfob;
int pursuit, alert;
string wolf;

/* Prototypes */
void hunt();
int roomcheck();
void retreat();
string namer();

void
create_krynn_monster()
{
    int i;
    string name, *word;

    set_name("guard");
    add_name("gnome");
    //set_living_name("guard");
    name = namer();
    set_short(name);
    word = explode(name, " ");
    set_adj(word[0]);
    set_long("A member of the gnomish militia, this gnome looks a good " +
	"bit sturdier than most of the others.  The gnomish Security Guild " +
	"is not to be trifled with, even if they are pretty short.\n");
    set_race_name("gnome");

    if (!IS_CLONE) /* Added by Nick, to get rid of some possible errors. */
	return;

    set_gender(random(2));
    add_act("say AMachineInTheCafeteriaTookMyMoney!");
    add_act("yawn");
    add_act("sigh");
    add_cact("shout Gangway!");
    add_cact("say Don'tPanic,GoodPeople.ThisWillBeUnderControlSoon!");
    add_cact("say SuchASenselessActOfViolence!");
    add_cact("growl");
    set_act_time(15);
    set_cact_time(5);

    alert = 0;
    pursuit = 0;

    for (i = 0; i < 6; i++)
	set_base_stat(i, 35 + random(25));
    set_base_stat(SS_DIS, 60 + random(40));
    set_skill(SS_DEFENCE, 65);
    set_skill(SS_WEP_AXE, 75);
    set_skill(SS_PARRY, 50);
    set_knight_prestige(-2);
    set_hp(15000);
    set_alignment(100);
    set_all_attack_unarmed(15, 25);
    set_all_hitloc_unarmed(40);

    trig_new("%s 'gives' %s", "gimme");
    trig_new("%s 'says:' %s", "strike");
    trig_new("%s 'dies.'", "requiem");
    trig_new("%s 'leaves' %s", "trail");
    set_alarm(1.0, -1.0, "equipme");
}

void
equipme()
{
    seteuid(getuid());
    clone_object(OBJ + "chainmail")->move(TO);
    clone_object(OBJ + "boots")->move(TO);
    clone_object(OBJ + "helmet")->move(TO);
    clone_object(OBJ + "battleaxe")->move(TO);
    command("wear all");
    command("wield axe");
}

void
strike(string str1, string str2)
{
    int i;
    string *phrase, temp, killer;

    if (str1 != "Gnome") 
	return;
    if (str2 == "AStrangerIsFightingOneOfOurKindred!Help!\n")
    {
	set_alarm(3.0, -1.0, "info");
	alert = 1;
    }
    phrase = explode(str2, " ");
    if ((alert) && ((phrase[0] == "Inthemaincaverns!")
	|| (phrase[0] == "Inthelivingquarters!")
	|| (phrase[0] == "Hereonthisfloor!")))
    {
	alert = 0;
	command("say StayHere,We'llTakeCareOfIt!");
	wolf = phrase[2] + " " + extract(phrase[3], 0, strlen(phrase[3]) - 3);
	if (!roomcheck())
	{
	    if (phrase[0] == "Inthemaincaverns!")
		command("west");
	    else if (phrase[0] == "Inthelivingquarters!")
		command("north");
	    else if (phrase[0] == "Hereonthisfloor!")
		command("south");
	    pursuit = 1;
	    hunt();
	}
    }
    if ((phrase[0] == "Help!") && (phrase[1] == "Stop") &&
	(phrase[2] == "this"))
    {
	if ((!phrase[3]) || (!phrase[4]))
	{
	    command("emote looks puzzled.");
	    return;
	}
	killer = phrase[3] + " " + extract(phrase[4], 0, strlen(phrase[4]) - 3);
	command("shout HowDareYou...ToArms!");
	set_alarm(1.0, -1.0, "react", killer);
	wolf = killer;
	pursuit = 0;
    }
}

void
react(string killer)
{
   command("kill " + killer);
}

void
info()
{
    tell_room(E(TO),
	"The guards perk up suddenly, thoughts of donuts forgotten.\n");
    command("say Where?");
    command("frown");
}

string
namer()
{
    string *desc1, *desc2;
    string name;
    int a, b;

    desc1 = ({"muscled", "agile", "burly", "gruff" });
    desc2 = ({"red-bearded", "blue-eyed", "elderly", "white-haired" });
    a = random(4);
    b = random(4);
    name = desc1[a] + " " + desc2[b] + " gnome";
    return name;
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if (QRACE(ob) == "gnome")
    {
	command("shout Traitor!  Howdareyouhowcouldyouyouwillsurelypay.");
	write_file("/d/Krynn/gnome/log/fight.log", ob->short());
	say("A scuffle breaks out among the gnomes, and one is carted off.\n");
	write("Your brethren grab you and cast you out of their home!\n");
	write("You are now persona non grata among the gnome. Try helping "
		+ "a gnome in need to redeem youself.\n");
	ob->move_living("this gnomish place.", TDIR + "entrance.c");
    }  
    else
    {
	wolfob = ob;
	wolf = ob->query_adj() + " " + QRACE(ob);
	command("say Help! Stop this " + ob->query_adj() +
		QRACE(ob) + "!");
    }
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

/* OLD GIMME, LUNATARI
void
gimme(string str1, string str2)
{
    string *phrase, item, temp;

    phrase = explode(str2, " ");
    if (phrase[0] != "you")
	return;
    temp = phrase[sizeof(phrase) - 1];
    item = extract(temp, 0, strlen(temp) - 3);
    command("say Wow,MyVeryOwn" + item + "!");
    command("say Hey,Thanks," + str1 + "!");
    command("wear " + item);
    command("wield " + item);
}
*/

int
roomcheck()
{
    object *people;
    int i;
    string temp;

    people = all_inventory(E(TO));
    for (i = 0; i < sizeof(people); i++)
    {
	temp = people[i]->query_adj() + " " + QRACE(people[i]);
	if (temp == wolf)
	{
	    wolfob = people[i];
	    command("kill " + wolf);
	    command("shout Begone!");
	    pursuit = 0;
	    return 1;
	}
    }
    return 0;
}

void
requiem(string str)
{
    int i;
    if (str == "Gnome")
    {
	i = random(5);
	if (!i)
	    command("say AnotherDeathForWhichYouMustSurelyPay!");
	else if (i == 1)
	    command("say AnotHeroOfOurKinSlain!FoulMurderer!");
   }
    set_alarm(2.0, -1.0, "tail", "here");
}

void
trail(string str1, string str2)
{
    if ((str1 != "Gnome") && (str1 != "Guard"))
	set_alarm(1.0, -1.0, "tail", str2);
}

void
tail(string str2)
{
    string dir;
    object thisroom;

    if ((!wolf) || (!wolfob))
    {
	retreat();
	return;
    }
    if (!P(wolfob, E(TO)))
    {
	if (!random(5))
	    command("shout TheyWentThatWay!");
	dir = extract(str2, 0, strlen(str2) - 3);
	thisroom = environment();
	command(dir);
	if (environment() == thisroom)
	    wolf = "";
	command("kill " + wolf);
	if (!P(wolfob, E(TO)))
	{
	    if(!random(2))
		command("shrug");
	    retreat();
	}
    }
}

void
retreat()
{
    string way;

    way = environment(this_object())->tohelp();
    if (way == "done")
    {
	wolfob = 0;
	wolf = "";
	if(!random(3))
		command("say Where'dIPutThoseDonuts?");
    }
    else
    {
	if (!random(5))
		command("shout Gangway!");
	command(way);
	if (!roomcheck())
		set_alarm(3.0, -1.0, "retreat");
    }
}

void
hunt()
{
    string way;
    
    if (!pursuit)
	return;
    if (!roomcheck())
    {
	way = E(TO)->fromhelp();
	if (way == "done")
	{
	    set_alarm(3.0, -1.0, "tail", "here");
	}
	else
	{
	    command(way);
	    set_alarm(3.0, -1.0, "hunt");
	}
    }
}
