/*
 * Mortis 02.2006
 * 
 * Cook in kitchen of merchant house Trusq.
 */

#include "../../local.h"
#include <macros.h>
#include <ss_types.h>

inherit M_FILE

void
create_krynn_monster()
{
    seteuid(getuid(TO));

    set_name("meggie");
    set_race_name("human");
    add_name(({"cook"}));
	set_gender(G_FEMALE);
	set_adj("aging");
	add_adj("moustachioed");
	set_title("the Cook of Merchant House Trusq");
	set_long("\n");

	set_stats(({20, 20, 45, 35, 50, 30}));

	set_alignment(900);
	set_knight_prestige(-100);
	set_introduce(1);

	set_size_descs("of normal length", "fat");
	set_appearance(3);
	
    set_skill(SS_AWARENESS, 20);

	set_all_hitloc_unarmed(5);

	remove_prop(LIVE_M_NO_ACCEPT_GIVE);
	
    set_act_time(25);
	add_act("emote stirs a bowl, turns a slab of meat, and powders a pastry.");
	add_act("emote bustles around the kitchen.");
	add_act("smell");
	add_act("say Oh how joyous this cooking.");
	add_act("emote sings to herself:  Hmm, hmm, hmm...  cook, cook, cook...");
	add_act("emote jiggles as she giggles while she cooks.");


	set_cact_time(50);
    add_cact("scream");
	add_cact("shout Murder!  MURDER!");
	add_cact("clobbers you over the head with a roller.");

	set_default_answer("@@def_answer");
	add_ask(({"cook", "cooking", "food"}), "say Oh, I just love to cook.", 1);
	add_ask(({"help", "task", "quest"}), "say Hmm, I get so thirsty cooking.  "
	+ "Could you fetch me a glass of water?\n", 1);

	command("pull right rope");

	set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
	clone_object(SHIP + "arms/trusq_cook_apron")->move(TO);

	command("wear all");
	command("pull left rope");
}

string
def_answer()
{
    command("say Oh, I'm far too busy cooking to worry about such a thing as "
	+ "that.  What joy cooking!");
    return "";
}

void
attacked_by(object ob)
{
	ob->add_prop(LIVE_I_ATTACKED_TRUSQ, 1);

	command("shout Please guards!  Save me!  It's a miscreant!");

    ::attacked_by(ob);
}

void
drink1()
{
	command("remove apron");
	set_alarm(3.0, 0.0, "drink2");
}

void
drink2()
{
	command("say I was soo thirsty.");
	set_alarm(3.0, 0.0, "drink3");
}

void
drink3()
{
	command("drink water");
command("emote mops her forehead with a handkerchief.");
	set_alarm(2.0, 0.0, "drink4");
}

void
drink4()
{
	command("wear apron");
	command("emote puts her apron back on.");
	command("say Thank you.");
}

void
give_it_back(object ob, object from)
{

    string what, who, whatshort;

    what = L(ob->query_name());
	whatshort = L(ob->query_short());
    who = from->query_real_name();

	if (!whatshort)
	{
		whatshort = "one";
	}

	command("say What a very special " + whatshort + ".  You must be very "
	+ "proud.");
	command("give " + what + " to " + who);
	return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

	if (ob->query_name() == "water")
	{
		if (from->query_prop(LIVE_I_ATTACKED_TRUSQ) == 1)
		{
			command("say Evildoer!  I wouldn't drink anything you gave me!");
			command("drop water");
			return;
		}
		
		command("sigh thirst");
		command("say Oh, thank you!");
		set_alarm(2.0, 0.0, "drink1");
		return;
	}

	if (ob->query_name() == "apron")
	{
		return;
	}

	set_alarm(1.0, 0.0, &give_it_back(ob, from));
	return;
}
