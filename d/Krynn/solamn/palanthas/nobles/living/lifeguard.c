/* Mortis 01.2006
 * 
 * The lifeguard of the Laethorian spa and body in the
 * Plaisir district of Palanthas.  Trains swimming.
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

#define TOWEL			"_i_have_not_returned_towel"
#define SWIMMING		"_i_am_swimming_at_the_laethorian"
#define PTOWEL			"_laethorian_pool_towel"

inherit CITIZEN;
inherit "/std/act/action";

void
create_krynn_monster()
{
    seteuid(getuid(TO));

    set_name("georg");
	set_living_name("georg");
    set_race_name("human");
    set_adj("lean");
    add_adj(({"adolescent", "life"}));
	add_name(({"georg", "philipp", "human", "lifeguard", "guard",
		"telemann"}));
	set_title("Philipp, Lifeguard and Swim Instructor of the Laethorian");
	set_short("lean adolescent male lifeguard");
    set_long("Without an ioda of fat on his body, the lifeguard's trim, "
	+ "cordlike muscles ripple through the skin of his very thin frame.\n"
	+ "He is twirling a whistle on a string.\n"
	+ "He is wearing very short and tight, sheer red swimwear.\n"
	+ "He has a stack of towels beside him.\n"
	+ "He offers swimming lessons.\n");
	set_gender(G_MALE);
    set_stats(({80, 85, 85, 50, 25, 80}));
	set_all_hitloc_unarmed(20);

	set_skill(SS_DEFENCE, 30);
    set_skill(SS_AWARENESS, 30);
	set_skill(SS_SWIM, 30);
    set_size_descs("of normal length", "skinny");
	set_appearance(8);

	add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

	set_alignment(550);
	set_knight_prestige(-25);
	
	set_introduce(1);
    set_act_time(80);
	add_act("emote stands up and touches his toes, his small buttocks "
	+ "stretching the sheer red material of his very short, very tight "
	+ "swimwear.\nHe sits back down in his tall, wooden, lifeguard chair.");
	add_act("emote stands up and stretches his arms above his head, the "
	+ "sheer red material of his very short, very tight swimwear slipping "
	+ "down revealingly.\nHe sits back down in his tall, wooden, lifeguard "
	+ "chair.");
	add_act("emote smiles self-consciously as he places his hands over "
	+ "his sheer red, very short, very tight swimwear.");
	add_act("emote twirls his whistle around his finger.");
	add_act("ponder if anyone can help him.");
	add_act("emote teaches a " + "@@teach_emote@@" + " advanced swimming "
	+ "techniques.");
	add_act("emote gives a swimming lesson to a " + "@@teach_emote@@" + ".");
    
	add_ask(({"swim", "swimming"}), "say Swimming is easy.  I can teach "
	+ "you how.", 1);
    add_ask(({"lesson", "lesson", "swimming lesson", "swimming lessons"}),
	  "say Yeah, ok.  Just hop in the pool and all, and we can work on "
	+ "<learn>-ing and <improve>-ing your swimming technique.", 1);
	add_ask(({"city", "palanthas"}), "say Yeah, Palanthas is great, and I "
	+ "-love- working in the Plaisir district.", 1);
	add_ask(({"task", "help", "quest"}), "The lifeguard says: Well, I "
	+ "could use a date.\n");
	add_ask("date", "@@ask_date");
	add_ask(({"towel", "towels"}), "@@give_towel");

    set_default_answer("@@def_answer");

}

string
def_answer()
{
    command("emote sticks his tongue out and rubs his pects while trying "
	+ "to look up for the answer.");
	command("say Uhhhh.  I, don't know.");
    return "";
}

string
teach_emote()
{
	return one_of_list(({"bureaumancer", "young boy", "boy", "young girl",
	"girl", "large man", "man", "woman", "guardsman", "pair of boys",
	"pair of girls", "morbidly obese woman in a muumuu", "young aesthetic",
	"pair of aesthetics", "beastly hairy man", "boy with a snot trail in "
	+ "his nose"}));
}

string
ask_date()
{
	if (TP->query_gender() == G_MALE)
	{
		command("say Oh gross, man.  Like, I don't date dudes.");
		return "";
	}
	command("say What?  You want a date with me?  Gosh!");
	write(QCTNAME(TO) + " hugs you, his hands sliding down in an attempt to "
	+ "squeeze your butt.\n");
	say(QCTNAME(TO) + " hugs " + QTNAME(TP) + ", his hands sliding down in "
	+ "an attempt to squeeze " + HIS(TP) + " butt.\n");
	return "";
}

string
give_towel()
{
	string givewho = L(TP->query_real_name());
	string thetowel;
	object towel;

	if (TP->query_prop(TOWEL) == 1)
	{
		command("say I already gave you a towel, " + QTNAME(TP) + ", and you "
		+ "never gave it back.  You're not getting another until you do.");
		return "";
	}
	if (TP->query_prop(SWIMMING) == 1)
	{
		command("say Hey, uhh, climb out of the pool first, and then I'll "
		+ "give you a towel.");
		return "";
	}
	
	towel = clone_object(NOBLE + "obj/pool_towel");
	towel->move(TO);
	thetowel = towel->query_name();

	if (TP->query_gender() != G_FEMALE)
		command("say Here's your towel sir.  Please return it before you "
		+ "leave.");
	else
	{
		command("emote smiles with a rosy hue to his cheeks.");
		command("say Here's your towl, ma'am.  Would you return that to me "
		+ "before you leave?");
	}

	if (!command("give " + thetowel + " to " + givewho))
	{
		towel->remove_object();
		command("emote scratches his head as he looks around in confusion "
		+ "for who to give his towel to.");
	}

	else
		TP->add_prop(TOWEL, 1);
	return "";
}

void
give_it_back(object ob, object from)
{
    string what, who, whatshort;

	if (ob->query_prop(PTOWEL) == 1)
	{
		command("say hi");
		return;
	}

    what = L(ob->query_name());
	whatshort = L(ob->short());
    who = from->query_real_name();

	if (!whatshort)
	{
		whatshort = "one";
	}

	command("say Uhh, that's a swell " + whatshort + " and all, but I don't "
	+ "have anywhere to put it.");
	command("emote gestures at his very short, very tight, sheer red "
	+ "swimwear.");
	command("give " + what + " to " + who);
	return;
}

void
enter_inv(object ob, object from)
{
	::enter_inv(ob, from);

	if (ob->query_prop(PTOWEL) == 1 && from != TO)
	{
		command("say Thanks for returning the towel.");
		command("emote bows, stretching the sheer red material of his "
		+ "very short, very tight swimwear.");
		ob->remove_object();
		from->remove_prop(TOWEL);
		return;
	}

	else
	{
		command("smile");
		set_alarm(1.0, 0.0, &give_it_back(ob, from));
	}

}

int
react_slap(object actor)
{
    if (actor)
    {
        if(actor->query_gender() == G_MALE)
        {
			command("say Dang, man.  What was that for?");
            command("sniff");
			return 1;
        }
		command("say Oh man, no!");
		command("emote whimpers pitifully.");
		command("say I just thought you wanted to go out with me is all.");
        return 1;
    }
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "slap")
        set_alarm(1.0, 0.0, &react_slap(actor));
}

void
init_living()
{
    ::init_living();
}
