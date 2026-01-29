#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

int corpse;
object trader;

void
create_kalad_monster()
{
    set_name("horace");
    add_name("trader");
    set_race_name("human");
    set_adj("fat");
    set_long("This rotund individual is one of the traders of the "+
      "Trading Company of Kabal. This man however, deals not with the usual "+
      "things, such as spices and other things. This man deals with people, "+
      "more specifically, in the capture of such people.\n");
    set_stats(({50, 60, 50, 60, 60, 40}));
    set_alignment(0);
    set_title("the Trader");
    set_knight_prestige(100);
    add_speak("I might have a job for you.\n");
    set_act_time(6);
    add_act("grin .");
    add_act("say Ahh...are you here to trade?");
    add_act("emote whistles tunelessly.");
    set_default_answer("The fat human says: Eh?\n");
    add_ask(({"trade", "job"}), "The fat human goes hmm.\n"+
      "The fat human says: Are you up to it?\n"+
      "The fat human says: If you are, then ask me for more information.\n");
    add_ask(({"more information"}), "The fat human says: Many people have "+
      "commited crimes against the Company, such as stealing and the like. "+
      "I want you to bring back to me, the dead body of the vilest scumbag "+
      "to have commited a crime against the company! All I can tell you is that "+
      "this filth has an eyepatch over his right eye, beyond that I only "+
      "know that he lives somewhere in Kabal.\n");
    add_ask(({"more"}), "The fat human says: More? More what?\n");
    add_ask(({"information"}), "The fat human says: What about it?\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    MONEY_MAKE_GC(random(10))->move(TO, 1);
}

int
corpse_return()
{
    corpse = 1;
}

void
drop_the_object(object ob)
{
    command("drop all");
}

void
remove_the_object(object ob)
{
    command("emote leaves to tell the Lord of the Trading Company the wonderful news.");
    if(trader = present("horace", environment(TP)))
    {
	trader->remove_object();
    }
}

public void
enter_inv(object ob, object from)
{
    if (MASTER_OB(ob) != PORT + "obj/jomocorpse")
    {
	::enter_inv(ob, from);
	set_alarm(2.0, 0.0, &drop_the_object(ob));
	return;
    }

    if (!interactive(from))
	return;
    else
	set_this_player(from);

    if (from->test_bit("Kalad", 0, 10))
    {
	write(query_The_name(from) + " thanks you for bringing back the corpse.\n");
	TP->catch_msg("You don't feel more experienced.\n");
    }
    else
    {
	write("The fat human thanks you for bringing back the corpse.\n");
	TP->catch_msg("You feel more experienced.\n");
	TP->add_exp(2000);
	TP->set_bit(0, 10);
    }

    ::enter_inv(ob, from);
    set_alarm(2.0, 0.0, &remove_the_object(ob));
}
