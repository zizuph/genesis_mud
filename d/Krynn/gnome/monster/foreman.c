/*
 * Navarre July 9th 2007, added support for ogre speech
 * Navarre December 29th 2007, changed "@@brain" to brain as is preferred
 * Also changed the 'brain' function to return a string rather than an int.
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h> /* This is needed to be able to use the macros, IS_CLONE */

inherit M_FILE
inherit LIB + "speech";

// Prototypes
string brain();

object this_room;


void
create_krynn_monster()
{
    int i;
    string name, *word;

    set_name("foreman");
    set_race_name("gnome");
    set_short("wizened gnomish foreman");
    set_adj("wizened");
    add_adj("gnomish");
    set_long("In theory, this person coordinates the use of the " +
	     "Transportation Guild's gnomeflingers. He shouts orders to " +
	     "the gnomes puttering about the catapults, some of which are " +
	     "obeyed.\n");

    if (!IS_CLONE) /* Added by Nick, to get rid of some possible errors. */
	    return;

    set_gender(0);
    set_act_time(5);
    add_act(brain);
    add_cact("say HeyHaveYouLostYourMind?");
    add_cact("say SomebodyGetTheGuards!I'llStallThem!");
    add_cact("say WhereWasThatFlamethrower?");

    set_cact_time(5);
    for (i = 0; i < 6; i++)
	    set_base_stat(i, 25 + random(15));
    set_alignment(100);
    set_all_attack_unarmed(10,15);
    set_all_hitloc_unarmed(20);
    set_knight_prestige(-1);
    set_hp(10000);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_NO_ACCEPT_GIVE, " is too busy running the gnomeflinger.\n"); 
    set_alarm(1.0, -1.0, "equip_me");
}

void
init_living()
{
    ADA("floor");
}

int
floor(string str)
{
    TP->command("say " + str);
    set_alarm(2.0,0.0,"commence", TP, "" + str + "\n");
    return 1;
}

void
equip_me()
{
    clone_object(OBJ + "clipb")->move(TO);
}

void
commence(object who, string floor)
{
    if (!call_other(OBJ + "flinger", "fling", who, lower_case(floor)))
    {
        command("say IDon'tUnderstandWhereYouWantToGo.");
        command("say PleaseSayOrShoutTheFloorWhereYouAreGoing," +
                "SuchAs'FirstFloor'Or'FloorTwo'.");
    }
}

public void
speech_hook(string verb, object actor, string adverb, object *oblist,
        string text, int target)
{
    int i;
    object attacker;
    string str;

    // If it's a fellow gnome, see if they are calling for help
    if (actor->id("gnome") && actor->query_npc())
    {
        attacker = find_attacker(text);
        if (attacker)
            command("$kill " + OB_NAME(attacker));
        return;
    }
    text = implode(explode(lower_case(text), " "), "");

    // Remove exclamation points or one period
    for (i = strlen(text) - 1; i > 0; i--)
    {
        if (text[i] == '.' && i == strlen(text) - 1)
        {
            i--;
            break;
        }
        if (text[i] != '!')
            break;
    }
    text = extract(text, 0, i);

    if (extract(text, 0, 4) == "floor" || extract(text, 0, 5) == "level")
    {
        switch(extract(text, 5))
        {
            case "1":
            case "one":
                commence(actor, "first");
                break;
            case "2":
            case "two":
                commence(actor, "second");
                break;
            case "3":
            case "three":
                commence(actor, "third");
                break;
            default:
                commence(actor, "default"); // causes response
                break;
        }
    }
    else if (extract(text, -5) == "floor" || extract(text, -5) == "level")
        commence(actor, extract(text, 0, -6));
}

public void
attacked_by(object ob)
{
    if (ob->query_race_name() == "gnome")
    {
	command("shout Traitor!  HowDareYouHowCouldYouYouWillSurelyPay.");
	write_file("/d/Krynn/gnome/log/fight.log", ob->short());
	say("A scuffle breaks out among the gnomes, and one is carted off.\n");
	write("Your brethren grab you and cast you out of their home!\n");
	write("You are now persona non grata among the gnome. Try to " +
		"help a gnome in need to redeem yourself.\n");
	ob->move_living("this gnomish place.", TDIR + "entrance.c");
    }
    else
	command("say Help! Stop this "+ ob->query_adj() + " " +
	    ob->query_race() + "!");
}

string
brain()
{
    int i = random(5);
    string *stuff = ({
        "an array of levers",
        "a cable running to level three",
	    "the firing angle of a gnomeflinger"
    });
    if (i == 0)
	    command("say OurStudiesShowFlyingIsSaferThanWalking!");
    else if (i == 1)
    {
	    command("say TheseSteampoweredCatapultsAreAwful.");
	    command("frown");
    }
    else if (i == 2)
    {
	    command("say HasAnyoneFixedTheNetOnLevelTwoYet?");
    }
    else if (i == 3)
    {
        command("shout Hey!Don'tTouchThatRope!");
        command("sigh");
        command("kick small gnome");
    }
    else
    {
	    command("emote makes an adjustment to " +
	        stuff[random(sizeof(stuff))] + ".");
    }
    return "";
}

/* Mask do_die to get the haunting */
void 
do_die(object killer)
{
  object ghost;

  seteuid(getuid());
  ghost = clone_object(TDIR + "monster/ghost"); 
  ghost->set_ghost_des(this_object()->query_nonmet_name());
  ghost->set_duration(800);
  ghost->move(killer);
  ghost->start_haunt();
  ghost->set_inform_msg("YouDeprivedMeOfThePossibilityTo"
	+ "FulfillMyOfficeInTheSocietyOfTheGnomes.\n"
	+ "YouWillSurelyPay.\n");
  ::do_die(killer);
}

