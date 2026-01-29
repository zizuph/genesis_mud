/* This is the basefile for the humans inhabiting the Plains of Solamnia
 * Aridor 08/99
 */

#include "/d/Krynn/solamn/road/local.h"
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#define ADJ1 ({"dirty","weathered","worn","noble"})
#define ADJ2 ({"brown-haired","brown-eyed","dark-haired","green-eyed","blue-eyed","grey-eyed","light-haired","dark-eyed","long-haired"})

inherit M_FILE

string village = "Plains of Solamnia";
int give_quest = 0;

void arm_me();
string say_rubish();

void
create_solamnian()
{

}

nomask void
create_krynn_monster()
{
    add_name("solamnian");
    set_race_name("human");

    add_pname(({"solamnians","humans"}));
    set_long("This is a @@short@@ of the @@query_village@@.\n");
    set_gender(random(2));
    if (random(20))
    {
	set_adj(ONE_OF(ADJ1));
	if (random(20))
	  add_adj(ONE_OF(ADJ2));
    }
    else
      add_adj(ONE_OF(ADJ2));
    add_adj(0);

    default_config_npc(30);
    set_skill(SS_AWARENESS, 20);
    set_skill(SS_DEFENSE, 21);
    set_skill(SS_UNARM_COMBAT, 30);

    add_prop(LIVE_I_NEVERKNOWN,1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_HEIGHT,176+random(19));
    set_alignment(1 + random(200));
    set_knight_prestige(-1);

    set_appearance(random(100));
    set_appearance_offset(random(5));

//    set_default_answer("@@command|emote looks blankly back at you.@@");
    set_default_answer("@@say_rubish@@");
    add_ask("'help'","say Free us of the evil " +
	    "invasion from the north. Unfortunately, we cannot offer " +
	    "anything in return. The reward lies in the satisfaction " +
	    "of helping the good side.",1);
    add_ask("[small] 'task'","answer_task",2);
    add_ask("'quest'","answer_quest",2);
    add_ask("[evil] 'invasion' / 'draconian' / 'draconians' [from] [the] [north]",
	    "say The draconians have come from the north, we do not know " +
	    "exactly from where. They were here suddenly, without warning, " +
	    "to burn our farms and plunder everything.",1);

    create_solamnian();

    add_adj("solamnian");
    set_alarm(1.0,0.0,arm_me);
}

string
answer_task()
{
    if (!give_quest)
      return "emote looks blankly back at you.";

    if (QUERY_QUEST("help_refugees"))
      return "say I don't have a task for you right now.";
    else
      return "say It would be very helpful to us if we " +
	"knew more about the plans of the dragon armies.";
}

string
answer_quest()
{
    if (!give_quest)
      return "emote looks blankly back at you.";

    if (QUERY_QUEST("help_refugees"))
      return "say Our only quest right now is to survive, but " +
	"you could help us with that.";
    else
      return "say Our only quest right now is to survive, but " +
	"you could help us with that. I might have a small task for you.";
}

void
arm_me()
{
    object b;

    if (!random(4))
    {
	b = clone_object(MSACK);
	b->move(TO,1);
    }
    else
      b = TO;

    MONEY_MAKE_CC(random(20))->move(b,1);
    MONEY_MAKE_SC(random( 5))->move(b,1);
    
    set_alarm(1.0,0.0,&command("wear all"));
    set_alarm(1.0,0.0,&command("wield all"));
}

/*
string
query_nonmet_name()
{
    return ::query_nonmet_name() + " solamnian";
}
*/

string
query_village()
{
    return village;
}

void
set_village(string str)
{
    village = str;
}

void
set_give_quest(int on)
{
    give_quest = on;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (give_quest &&
	ob->id("help_refugees_quest_paper"))
      set_alarm(1.0,0.0,"reward_player",ob,from);
    else
      set_alarm(0.1,0.0,"give_back",ob,from);
}

void
give_back(object ob, object tp)
{
    if (tp)
    {
	if (command("give " + ob->query_name() + " to " + tp->query_real_name()))
	  command("say I have no use for this.");

    }
}

void
reward_player(object ob, object tp)
{
    int xp;

    ob->remove_object();
    if (!tp)
      return;

    /* just once per clock cycle */
    if (QUERY_QUEST("help_refugees"))
    {
	command("say I have no use for this at this time.");
	return;
    }
    if (tp->test_bit("Krynn",1,18))
    {
	command("say Thank you very much for helping us again.");
	return;
    }

    xp = 500;
    tp->set_bit(1,18);
    tp->add_exp(xp);
    tp->adjust_alignment(600);
    command("say Thank you very much for your help. Hopefully we will be " +
	    "able to fend off the evil armies for a while longer now.");
    tp->catch_msg("You feel more experienced.\n");
    DONE_QUEST("help_refugees");
    STD_QUEST_LOG("Help Refugees",tp,xp);
}

string
say_rubish()
{
	// we make him stare blank or do something else
    if(!random(5))
    {
        command("blank");
    }
    else
    { 
	 command("chuckle");
         command("say I am not sure what are you asking about. Maybe you " +
		"should talk to someone else?");	 
    }
    return "";
}
