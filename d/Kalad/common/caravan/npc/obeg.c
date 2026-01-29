#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

int key;
object obeg;

void
create_kalad_monster()
{
    set_name("beggar");
    set_race_name("human");
    set_adj("poor");
    set_long("This poor old man must be one of the many beggars scratching "+
      "out an existence on Beggar's Alley. He looks quite miserable.\n");
    set_stats(({25, 30, 25, 30, 30, 20}));
    set_alignment(1000);
    set_knight_prestige(-10);
    add_speak("Why have the gods forsaken me?\n");
    set_act_time(3);
    add_act("sniff");
    add_act("say Please...you must help me...");
    set_default_answer("The poor human says: I'm sorry, what was that?\n");
    add_ask(({"help"}), "The poor human whispers: You must recover the key "+
      "to my happiness.\n");
    add_ask(({"key"}), "The poor human quivers: That horrible beast of a man, "+
      "Egore, stole it from me!\n");
    add_ask(({"happiness"}), "The poor human whimpers: The key is the only thing that means anything to me.\n");
    add_ask(({"egore"}), "The poor human whispers: He is a horrible man, not a trace of kindness can be found in him.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    object arm;
    seteuid(getuid(this_object()));
    arm = clone_object(OBJ + "mstone.c");
    arm->move(this_object());
}

void
key_return()
{
    key = 1;
}

void
drop_the_object(object ob)
{
    command("drop all");
}

void
remove_the_object(object ob)
{
    command("emote pats the key lovingly and then tucks it into his rags.");
    command("emote wanders down the street.");

    if(obeg = present("beggar", environment(TP)))
    {
	obeg->remove_object();
    }
}

public void
enter_inv(object ob, object from)
{
    if (MASTER_OB(ob) != OBJ + "ikey")
    {
	::enter_inv(ob, from);
	set_alarm(2.0, 0.0, &drop_the_object(ob));
	return;
    }

    if (!interactive(from))
	return;
    else
	set_this_player(from);

    if (from->test_bit("Kalad", 0, 0))
    {
	write(query_The_name(from) + " thanks you and then scratches his crotch.\n");
	TP->catch_msg("You don't feel more experienced.\n");
    }

    else {
	write("The beggar thanks you gratefully.\n");
	TP->catch_msg("You feel more experienced.\n");
	TP->add_exp(1500);
	TP->set_bit(0, 0);
    }

    ::enter_inv(ob, from);
    set_alarm(2.0, 0.0, &remove_the_object(ob));
}
