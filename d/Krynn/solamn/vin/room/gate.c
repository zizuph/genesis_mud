/* Vingaard Keep coded by Percy. */
/* Guarding of the gate by Aridor */
/* Modified by Morrigan, 11/11/96 for the New Vingaard Keep */
/* Modified slightly by Teth, 12/3/96 */

#include "../local.h"
#include "../knight/guild.h"
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>

inherit OUT_BASE;

#define COURTY     VROOM + "courtyard"

object guard1, guard2, guard3, guard4, guard5, guard6;
object *distrust_list = ({ });
object *vouch_list = ({ });
int called_for_help = 0;

/* load the gate guards */
void
reset_vin_room()
{
    if (!guard1)
    {
	guard1 = clone_object(VNPC + "gate_guard");
	guard1->move(TO);
	guard1->set_block_dir("south");
    }
    if (!guard2)
    {
	guard2 = clone_object(VNPC + "gate_guard");
	guard2->move(TO);
	guard2->set_block_dir("south");
    }
    if (!guard3)
    {
	guard3 = clone_object(VNPC + "gate_guard");
	guard3->move(TO);
	guard3->set_block_dir("south");
    }
    if (!guard4)
    {
	guard4 = clone_object(VNPC + "gate_guard");
	guard4->move(TO);
	guard4->set_block_dir("south");
    }
    if (!guard5)
    {
	guard5 = clone_object(VNPC + "gate_guard");
	guard5->move(TO);
	guard5->set_block_dir("south");
    }
    if (!guard6)
    {
	guard6 = clone_object(VNPC + "gate_guard");
	guard6->move(TO);
	guard6->set_block_dir("south");
    }
}

string
sign_desc()
{
    if (TP->query_guild_name_occ() == "Solamnian Knights")
    {
	if (TP->query_skill(SS_LANGUAGE) > 19)
	    return "The sign is written in old Solamnic and you read:\n" +
	    "      You can vouch here for someone who is not\n" +
	    "      allowed into the guild normally. In case\n" +
	    "      the gate is closed, knocking might help.\n";
	return "The sign is written in old Solamnic, but your knowlegde " +
	"of the language is insufficient to read it.\n";
    }
    if (TP->query_skill(SS_LANGUAGE) > 70)
	return "The sign is written in old Solamnic and you read:\n" +
	"      You can vouch here for someone who is not\n" +
	"      allowed into the guild normally. In case\n" +
	"      the gate is closed, knocking might help.\n";
    return "The sign is written in strange letters which you cannot read.\n";
}

void
create_vin_room()
{
    set_short("Before Vingaard Keep");
    set_long("@@long_desc");

    AE(COURTY, "north", "@@go_north");
    AE(VROOM + "bridge", "south", 0);

    AI("sign","@@sign_desc");
    ACI("sign","read","@@sign_desc");
    AI(({"keep", "castle", "stronghold"}), "@@keep");
    AI(({"gate", "gates","portcullis"}), "@@gate");
    AI(({"moat", "river", "rivers", "barrier", "barriers",
	"natural barrier", "natural barriers"}), "@@barrier");
    AI(({"battlement","battlements"}),"High above on the battlements, " +
      "you can see the standard of Vingaard Keep and the flag of " +
      "Solamnia presenting themselves.\n");
    AI(({"standard","flag","flag of Solamnia","standard of Vingaard Keep"}),
      "You are too far away to see them clearly. You'd need to get " +
      "closer.\n");
    reset_vin_room();
}

string
long_desc()
{
    return "You stand in awe before Vingaard Keep, a place known across "+
    "Krynn as the center of power for the Knights of Solamnia. It stands "+
    "guard on the Vingaard river and its tributary. Legends say that the "+
    "mighty fortress has never fallen to the forces of evil. The Knights "+ 
    "guarding it are on constant duty, some of them above on the " +
    "battlements. The walls stand 15 meters high, and are 2 meters " +
    "thick of solid impressive stone. "+season()+tod()+"\n";

}
void
init()
{
    ::init();
    ADD("vouch_for_someone","vouch");
    ADD("knock_on_gate","knock");
}


/* add_item descriptions */
keep()
{
    write("The keep is very ancient and has withstood the test of time" +
      " just as much as it has withstood numerous battles. The keep is" +
      " the stronghold for the Solamnian Knighthood, a powerful army" +
      " of knights devoted to the cause of the good deity Paladine. " +
      "The walls here at the outside of the keep are enormous and have "+
      "never fallen to the vile clutches of the Dragonqueen.\n");
    return "";
}

gate()
{
    if ((COURTY)->query_portcullis_closed())
	write("The gate is made of iron. It looks extremely solid. At the " +
	  "moment, the gates are closed! A most disturbing sign!\n");
    else
	write("The gate is made of iron. It looks extremely solid. At the " +
	  "moment however the gate lies open, a sign of the " +
	  "knighthood's confidence in their power to defeat the evil " +
	  "in the world.\n");
    return "";

}

barrier()
{
    write("There is a moat surrounding the keep which comes from the " +
      "rivers that flow to the west and east of the keep.\n");
    return "";
}


int
not_called_for_help_yet()
{
    return (!called_for_help);
}

/* send one of the guards into the keep to get help */
void
call_for_help(object g1, object g2, object enemy)
{
    int strong, i;
    object *team;
    if (!g1 || !g2 || !enemy)
	return;
    if (called_for_help)
    {
	g1->attack_object(enemy);
	g2->attack_object(enemy);
	return;
    }
    strong = enemy->query_average_stat();
    team = enemy->query_team_others();
    for (i=0;i<sizeof(team);i++)
	strong += team[i]->query_average_stat();
    if (strong < 90)
    {
	g1->command("say Only a fool would attack Vingaard with such "+
	  "a pathetic force!");
	g2->command("chuckle");
	g2->command("say I think we can handle the vermin ourselves.");
	g1->command("say Indeed.");
	g2->command("say By the Measure now and always, let swords fall "+
	  "as swords will fall!");
	g1->command("say For Vingaard!");
	g1->attack_object(enemy);
	g2->attack_object(enemy);
	return;
    }
    called_for_help = 1;
    g1->command("shout Vingaard is under attack!  Alert the guards, to "+
      "battle!  Vingaard shall never fall!");
    g1->attack_object(enemy);
    if (g2->command("north"))
    {
	g2->set_me_alarmed(1);
	g2->command("north");
	g2->command("west");
	g2->command("alarm guards");
	g2->command("out");
	g2->command("east");
	g2->command("alarm guards");
	g2->command("out");
	g2->command("south");
	set_alarm(4.0,0.0,"close_the_portcullis_again",g2);
	set_alarm(150.0,0.0,"open_the_portcullis_again",g2);
    }
    else
	g2->attack_object(enemy);
}

void
alarm_guards(object att)
{
    if (guard1 && guard2)
	call_for_help(guard1,guard2,att);
    else
    {
	guard1->command("emote valiantly stands to defend Vingaard.");
	guard2->command("emote gets into position to defend Vingaard.");
    }
}

/* return 0 to allow travel under gate */
int
go_north()
{
    int rnd_num = -random(100) - 20;
    object gu;
    string say_refuse;
    if ((COURTY)->query_portcullis_closed())
    {
	write("The portcullis is closed, denying you access.\n");
	return 1;
    }
    gu = present("knight",TO);
    if (!CAN_SEE(gu, TP))
      return 0;
    if (gu && TP->query_alignment() < rnd_num &&
      member_array(TP,vouch_list) != -1)
    {
	gu->command("say Very well, you have been vouched for.");
	gu->command("say You are allowed to enter this one time, "+
	  "please enter and be welcome.");
	vouch_list -= ({ 0,TP });
	return 0;
    }
    if (gu && (TP->query_alignment() < rnd_num ||
	TP->query_prop("_i_attacked_in_vingaard")) && CAN_SEE(gu,TP) &&
	TP->query_average_stat() > 21 && !present("tour6",TP))
    {
	say_refuse = "shout I'm sorry, " + TP->query_nonmet_name() +
	", I don't trust you! You are denied permission to enter. " +
	"If you persist I will be forced to attack!";
	distrust_list -= ({ 0 });
	if (member_array(TP, distrust_list) != -1)
	{
	    if (guard1 && guard2)
	    {
		guard1->command("shout Very will, if you insist!\n");
		guard1->command("shout I warned you not to try " +
		  "again!\n");
		call_for_help(guard1, guard2, TP);
	    }
	    else if (guard2)
	    {
		guard2->command("say Hmm, do you really think I'm " +
		  "stupid?");
		guard2->attack_object(TP);
	    }
	    else if (guard1)
	    {
		guard1->command("say Hmm, do you really think I'm " +
		  "stupid?");
		guard1->attack_object(TP);
	    }
	    else
	    {
		gu->command("say Hmm, do you really think I'm stupid?");
		gu->attack_object(TP);
	    }
	}
	else
	{
	    gu->command(say_refuse);
	    gu->command("say A knight can vouch for you here so you " +
			"can get in.");
	    distrust_list += ({ TP });
	}
	return 1;
    }
    if (MEMBER(TP))
    {
	write("\nA trumpet blares from the battlements!\n\n\n"+
	  "Welcome back to Vingaard Keep, Knight of Solamnia!\n\n\n");
	return 0;
    }

    write("You pass through the gates and into the huge courtyard beyond.\n");
    return 0;
}

/* return 0 to allow travel south */
int
go_south()
{
    return 0;
}


void
close_the_portcullis_again(object who)
{
    if (who)
    {
	who->command("lower portcullis");
    }
}

void
open_the_portcullis_again(object who)
{
    object *guards = ({}), *dummy = all_inventory(TO);
    object gua;
    int i;
    for(i = 0; i < sizeof(dummy); i++)
	if (dummy[i]->id("knight"))
	    guards += ({ dummy[i] });
    for(i = 0; i < sizeof(guards); i++)
	if ((gua = guards[i]->query_enemy(0)) && E(gua) == TO)
	{
	    set_alarm(100.0,0.0,"open_the_portcullis_again",who);
	    return;
	}

    if (who)
    {
	who->command("open portcullis");
	who->command("south");

    }
    else
	(COURTY)->do_open_portcullis();

    guards -= ({ guard1 });
    guards -= ({ guard2 });
    guards->command("north");
    guards->command("north");
    guards[0..3]->command("west");
    guards[4..7]->command("east");
    guards->set_me_alarmed(0);
    called_for_help = 0;
}

int
vouch_for_someone(string str)
{
    mixed *who;
    NF("What?\n");
    if (TP->query_guild_name_occ() != "Solamnian Knights")
	return 0;
    if (TP->query_alignment() < 0)
    {
	TP->catch_msg("You are evil yourself! How can you expect to be able to vouch for someone?\n");
	return 1;
    }
    NF("Vouch for who?\n");
    if (!str)
	return 0;
    if (str[0..3] != "for ")
	return 0;
    who = FIND_STR_IN_OBJECT(str[4..],TO);
    if (who && sizeof(who) == 1)
    {
	if (who[0] == TP)
	    TP->catch_msg("You can't vouch for yourself!\n");
	else if (who[0]->query_alignment() >= 0)
	    TP->catch_msg("There is no need to vouch for " + QTNAME(who[0]) +
	      ".\n");
	else if (member_array(who[0],vouch_list) >= 0)
	    TP->catch_msg(QCTNAME(who[0]) + " has already been vouched for!\n");
	else
	{
	    TP->catch_msg("You vouch for "+QTNAME(who[0])+" to be able to enter the keep once.\n");
	    vouch_list += ({ who[0] });
	    vouch_list -= ({ 0 });
	}
    }
    else
	write("Ambiguous description, no vouching done.\n");
    return 1;
}


int
knock_on_gate(string str)
{
    NF("What?\n");
    /*    if (!MEMBER(TP))
	return 0;*/
    NF("Knock where?\n");
    if (!str)
	return 0;
    if (str != "gate" && str != "on gate" && str != "gates" &&
      str != "on gates" && str != "portcullis" && str != "at portcullis" &&
      str != "at gate" && str != "at gates")
	return 0;

    if (!(COURTY)->query_portcullis_closed())
    {
	write("The gate is open already.\n");
	return 1;
    }
    write("You knock on the gate.\n");
    say(QCTNAME(TP) + " knocks on the gate.\n");
    if (TP->query_guild_name_occ() != "Solamnian Knights")
    {
	write("Nothing happens.\n");
	return 1;
    }

    (COURTY)->do_open_portcullis();
    return 1;
}
