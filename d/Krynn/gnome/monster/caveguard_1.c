/* 
 * /d/Krynn/gnome/monster/caveguard_1.c
 *
 * These guards are slightly sturdier than the other ones due to their
 * exposed position. 
 *
 * 18 FEB 2009: Update to fix small GnomeSpeak errors and make code cleaner. 
 * Aeg (Matthew Morin)
 */

/* Includes */
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h> /* This is needed to be able to use the macros, IS_CLONE */
#include <ss_types.h>

/* Inherits */
inherit M_FILE

/* Global variables */
object wolfob;
int pursuit, alert;
string wolf;

/* Prototypes */
string  namer();
void    hunt();
int     roomcheck();
void    retreat();

/*
 * Function name: create_krynn_monster
 * Description  : This function creates a monster with krynn settings
 */
void
create_krynn_monster()
{
    int i;
    string name, *word;

    set_name("guard");
    add_name("gnome");
    name = namer();
    set_short(name);
    word = explode(name, " ");
    set_adj(word[0]);
    set_long("A member of the gnomish militia, this gnome looks a lot "
           + "sturdier than all of the others. The gnomish Security Guild "
           + "is not to be trifled with, even if they are pretty short.\n");
    set_race_name("gnome");

    if (!IS_CLONE) /* Added by Nick, to get rid of some possible errors. */
	return;

    set_gender(random(2));
    
    /* Actions */
    add_act("say DamnCafeteriaMachineTookMyMoney!");
    add_act("yawn");
    add_act("think getting off work.");
    add_act("sigh");
    
    /* Combat Actions */
    add_cact("shout Gangway!");
    add_cact("say Don'tPanic,GoodPeople.ThisWillBeUnderControlSoon!");
    add_cact("say SuchASenselessActOfViolence...");
    add_cact("growl");
    set_act_time(15);
    set_cact_time(5);

    alert = 0;
    pursuit = 0;

    /* Stats */
    set_base_stat(SS_STR, 80 + random(15));
    set_base_stat(SS_DEX, 50 + random(15));
    set_base_stat(SS_CON, 50 + random(15));
    set_base_stat(SS_INT, 50 + random(15));
    set_base_stat(SS_WIS, 50 + random(15));    
    set_base_stat(SS_DIS, 80 + random(20));

    /* Skills */
    set_skill(SS_DEFENCE,   80);
    set_skill(SS_WEP_AXE,   90);
    set_skill(SS_PARRY,     65);
    
    /* Prestige for Knights */
    set_knight_prestige(-2);
    
    /* Health and Alignment */
    set_hp(18000);
    set_alignment(100);
    
    /* base attack and skin thickness */
    set_all_attack_unarmed(20, 30);
    set_all_hitloc_unarmed(50);

    /* Triggers */
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
    if ((alert == 1) && ((phrase[0] == "InTheCorridors!")
	|| (phrase[0] == "InTheTestArea!")))
    {
	alert = 0;
	command("say StayHere,We'llTakeCareOfIt!");
	wolf = phrase[2] + " " + extract(phrase[3], 0, strlen(phrase[3]) - 3);
	if (!roomcheck())
	{
	    if (phrase[0] == "InTheCorridors!")
		command("south");
	    else if (phrase[0] == "InTheTestArea!")
	    {
		command("south");
		command("south");
		command("south");
	    }
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
	command("shout ToArms!");
	command("kill " + killer);
	wolf = killer;
	pursuit = 0;
    }
}

void
info()
{
    tell_room(E(TO),
	"The guards perk up suddenly, thoughts of donuts forgotten.\n");
    command("say Where?");
    command("frown");
}

/*
 * Function name: namer
 * Description  : This function gives our monster it's descriptions
 * Return       : name
 */
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

/*
 * Function name: attacked_by
 * Description  : This function creates the reactions to being attacked.
 * Arguements   : object ob - the attacker
 */
void
attacked_by(object ob)
{
    ::attacked_by(ob);
    /* If the attacker is a gnome */
    if (QRACE(ob) == "gnome")
    {
    command("shout Traitor!HowDareYou?HowCouldYou?YouWillSurelyPay!");
    write_file("/d/Krynn/gnome/log/fight.log", ob->short());
    say("A scuffle breaks out among the gnomes, and one is carted off.\n");
    write("Your brethren grab you and cast you out of their home!\n");
    write("You are now persona non grata among the gnomes. Try "
        + "helping a gnome in need to redeem yourself.\n");
	  ob->move_living("this gnomish place.", TDIR + "entrance.c");
    }  
    /* If the attacker is non-gnome */
    else
    {
    wolfob = ob;
    wolf = ob->query_adj() + " " + QRACE(ob);
    command("say Help!StopThis" + capitalize(ob->query_adj())
        + capitalize(query_race()) + "!");

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
    command("say Wow,MyVeryOwn" + item + "!");
    command("say Hey,Thanks," + str1 + "!");
    command("wear " + item);
    command("wield " + item);
}

int
roomcheck()
{
    object *people;
    int i;
    string temp;

    people = all_inventory(environment());
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
	if (i == 0)
	    command("say AnotherDeathForWhichYouMustPay!");
	else if (i == 1)
	    command("say AnotherOfOurKin!Slain!FoulMurderer!");
    }
    set_alarm(2.0, -1.0, "tail", "here");
}

void
trail(string str1, string str2)
{
    if ((str1 != "Gnome") && (str1 != "Guard"))
	set_alarm(2.0, -1.0, "tail", str2);
}

void
tail(string str2)
{
    int i;
    string dir;
    object thisroom;

    if ((!wolf) || (!wolfob))
    {
	retreat();
	return;
    }
    if (!present(wolfob, environment()))
    {
	i = random(5);
	if (i == 0)
	    command("shout TheyWentThatWay!");
	dir = extract(str2, 0, strlen(str2) - 3);
	thisroom = environment();
	command(dir);
	if (environment() == thisroom)
	    wolf = "";
	command("kill " + wolf);
	if (!present(wolfob, environment()))
	{
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
	command("say Now,WhereDidIPutThoseDonuts?");
    }
    else
    {
	if (!roomcheck())
		set_alarm(3.0, -1.0, "retreat");
	if (!random(5))
		command("shout Gangway!");
	command(way);
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
	way = environment()->fromhelp();
	command(way);
   if(way == "done")
	{
	    set_alarm(3.0, -1.0, "tail", "here");
	}
	else
	{
	    set_alarm(3.0, -1.0, "hunt");
	}
    }
}
