/**
 * Navarre December 29th 2007:
 * Changed the 'int brain' function to 'string brain' and
 * changed the "@@brain" to brain as is the preferred VBFC way.
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit M_FILE

#include <macros.h> /* This is needed to be able to use the macros, IS_CLONE */

// Prototypes
string brain();

void
create_krynn_monster()
{
    int i;

    set_name("bartender");
    set_living_name("bartender");
    set_short("sympathetic bartender");
    set_long(BS("An understanding soul for the temporarily uninspired " +
    	"gnome to talk to.", 70));
    set_race_name("gnome");

    if (!IS_CLONE)
    	return;

    set_gender(random(2));
    set_act_time(10);
    add_act(brain);
    add_cact("say Heyhaveyoulostyourmind?");
    add_cact("say Somebodygettheguards!  I'llstallthem...");
    add_cact("say Wherewasthatflamethrower?");

    set_cact_time(10);
    for (i = 0; i < 6; i++)
	set_base_stat(i, 15 + random(25));
    set_hp(10000);
    set_alignment(100);
    set_all_hitloc_unarmed(10);
    set_knight_prestige(-2);

    trig_new("%s 'gives' %s", "gimme");
    trig_new("%s 'says:' %s", "strike");
}

int
strike(string str1, string str2)
{
    int i;

    string *phrase, temp, killer;
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
  	if (i <= 1)
	{
            command("say Pleasedon'twreckthefurniture!");
        }
    	else if (i >= 5)
	{
            command("say Youmustbehavingahardday! Wanttotalkaboutit?");
      	}
    	else
	{
            command("say Hey, don'tmakeamess!");
            command("kill " + killer);
      	}
    }
    return 0;
}

public void
attacked_by(object ob)
{
    if (QRACE(ob) == "gnome")
    {
    	command("shout Traitor!  Howdareyouhowcouldyouyouwillsurelypay.");
        write_file("/d/Krynn/gnome/log/fight.log", ob->short() + " " +
            ob->query_nonmet_name() + "\n");
        say("A scuffle breaks out among the gnomes, and one is carted off.\n");
        write("Your brethren grab you and cast you out of their home!\n");
        write("You are now persona non grata among the gnomes." +
	    "  Try performing a good deed for a gnome to redeem " +
	    "yourself.\n");
        TP->move_living("this happy gnomish place..", TDIR + "entrance.c");
    }
    else
  	command("say Thisisnotaconstructivewaytodealwithyourfeelings!");
}

int
gimme(string str1, string str2)
{
    string *phrase, item, temp;
    phrase = explode(str2, " ");
    if (phrase[0] != "you")
	return 1;
    temp = phrase[sizeof(phrase) - 1];
    item = extract(temp, 0, strlen(temp) - 3);
    command("say Thankyou, butIhavenorealuseforthis...");
    set_alarm(2.0, -1.0, "dropit", item);
    return 1;
}

void
dropit(string item)
{
    command("drop " + item);
}

string
brain()
{
    int i;
    string *stuff;
    stuff = ({"a few chairs", "a table", "the countertop"});
    i = random(4);
    if (i == 0)
	command("say There,there.Thiswillgetbetter.");
    else if (i == 1)
    {
    	command("nod");
    	command("Iknowexactlyhowyoufeel.");
    }
    else if (i == 2)
    {
    	command("sigh");
    	command("say Thesamethinghappenendtomeonce.");
    }
    else
    {
	tell_room(environment(), "The bartender cleans off " +
	    stuff[random(sizeof(stuff))] + ".\n");
    }
    return "";
}
