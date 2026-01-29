#include "default.h"

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

int medallion;
object mtrader;

void
create_kalad_monster()
{
    set_name("degaard");
    add_name("trader");
    set_race_name("human");
    set_adj("wizened");
    add_adj("friendly");
    set_long("A kindly old man that sits here within this magnificently "+
      "decorated wagon. He gazes at you with eyes that seem to stare straight "+
      "into your soul and possess a knowledge most people only wish they "+
      "had.\n");
    set_stats(({60, 50, 55, 75, 100, 50}));
    set_alignment(350);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_TRADING, 100);
    set_act_time(3);
    add_act("smile know");
    add_act("say Welcome travellers, perhaps we can both be of use to "+
      "one another?");
    add_act("say I seek knowledge, first and foremost.");
    set_cact_time(3);
    add_cact("say You barbarian!");
    add_cact("say This senseless act of violence only proves your lack "+
      "of intellect.");
    set_title("the Master Trader");
    add_speak("Remember, knowledge is the most valueable thing anyone "+
      "can trade you.\n");
    set_knight_prestige(-4);
    add_ask(({"knowledge"}), "The wizened friendly human says: It is good "+
      "to see younger folk such as yourself interested in such things. "+
      "Perhaps you can do me a favor, and in trade I shall reward you.\n");
    add_ask(({"favor", "favour", "assistance", "help"}), "The wizened friendly human says: I've developed a "+
      "fairly recent interest in holy symbols...bring me one, of the church "+
      "of Thanar and you shall be richly rewarded.\n");
    add_ask(({"reward"}), "The wizened friendly human says: You shall "+
      "know what it is once you have done what I've asked!\n");
    add_ask(({"use"}), "The wizened friendly human says: If you were to do "+
      "me a favor, then perhaps I could do one for you.\n");
    add_ask(({"holy symbols", "holy symbol", "symbols", "symbol"}), "The "+
      "wizened friendly human says: Hmm...Last time I remember, their holy "+
      "symbol was in the form of a medallion.\n");
    add_ask(({"medallion"}), "The wizened friendly human says: Why that's "+
      "what you're supposed to bring me!\n");
    set_default_answer("The wizened friendly human says: I have no "+
      "interest in such a topic.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
}

void
medallion_return()
{
    medallion = 1;
}

void
drop_the_object(object ob)
{
    command("drop all");
}

void
remove_the_object(object ob)
{
    command("say Thank you again for bringing me the medallion, I've been "+
      "wanting to study one for years.");
    command("smile");
    command("say Farewell! I must put this in a safe place now.");
    command("wave all");
    command("emote puts the medallion in his pocket and leaves.");

    if(mtrader = present("degaard", environment(TP)))
    {
	mtrader->remove_object();
    }
}

public void
enter_inv(object ob, object from)
{
    if (MASTER_OB(ob) != ARM + "ktmed")
    {
	::enter_inv(ob, from);
	set_alarm(2.0, 0.0, &drop_the_object(ob));
	return;
    }

    if (!interactive(from))
	return;
    else
	set_this_player(from);

    if (from->test_bit("Kalad", 0, 1))
    {
	write(query_The_name(from) + " thanks you gratefully and proceeds to "+
	  "inspect the medallion.\n");
	TP->catch_msg("You don't feel more experienced.\n");
    }
    else
    {
	write("The wizened friendly human thanks you gratefully for your "+
	  "priceless gift.\n");
	TP->catch_msg("You feel more experienced.\n");
	TP->add_exp(3000);
	TP->set_bit(0, 1);
    }

    ::enter_inv(ob, from);
    set_alarm(2.0, 0.0, &remove_the_object(ob));
}
