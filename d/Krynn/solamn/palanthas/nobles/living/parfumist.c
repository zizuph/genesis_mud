/* Mortis 12.2005
 * 
 * Runs parfumerie in northeast of Court d'Plaisiri
 * in Palanthas.
 */

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"


inherit CITIZEN;

#define MY_CLOTHING		NOBLE + "arms/parmour"


void
create_krynn_monster()
{
    set_name("armil");
	set_living_name("armil");
    set_race_name("human");
    set_adj("handsome");
    add_adj("black-haired");
	add_name(({"armil", "jordesse", "human", "parfumist"}));
	set_title("Jordesse, Parfumist of the Court d'Plaisiri");
    set_long("This tall man is well-muscled with long, curly black hair "
	+ "hanging down about his shoulders.  He is clean-shaven and well-"
	+ "groomed with a prominent double chin and a wide smile brimming "
	+ "with perfect, white teeth.\n");
	set_gender(G_MALE);
    set_stats(({90, 65, 85, 55, 50, 45}));
	set_all_attack_unarmed(20, 60);
	set_all_hitloc_unarmed(30);

    set_skill(SS_AWARENESS, 45);
    set_size_descs("tall", "of normal width");
	set_appearance(6);

	set_alignment(350);
	set_knight_prestige(-20);
	
	set_introduce(1);
    set_act_time(12);
    add_act("say Hi, and welcome.");
    add_act("emote smiles charmingly at you.");
	add_act("smell");
	add_act("smile charm");
	add_act("wink friend");
	add_act("sample control");
	add_act("sample white hammer");
	add_act("sample krom");
	add_act("say A beautiful fragrance can change your day, perhaps even "
	+ "your outlook on life.");
	add_act("say A sophisticated cologne can change your day, sometimes "
	+ "even turn your life around.");
	add_act("say Can I help you find the perfect fragrance?");
	add_act("say The women of " + "@@women_from@@");
	add_act("emote turns around behind the counter and bends over, the "
	+ "tight fabric of his pants outlining his tight buttocks revealingly "
	+ "as he picks up a small box of phials and places it on the counter.");
	add_act("emote leans over the counter to reach a bottle, his revealing "
	+ "vest affording you a view of his chiseled pecks.");
	add_act("say The Court d'Plaisiri is the best place to receive desirable "
	+ "services.", 1);

    
    add_ask(({"pricelist", "prices", "price", "list"}), "say All our "
	+ "prices are on the sign on the counter here.", 1);
	add_ask(({"city", "palanthas"}), "say This is a great city, truly, and "
	+ "the women are the most beautiful in the world.", 1);
	add_ask(({"fragrance", "scent", "perfume", "cologne"}), "say All "
	+ "Jordesse perfumes and colognes are designed with the greatest skill "
	+ "and care by the master parfumist.", 1);
	add_ask(({"parfumist", "parfumists", "master parfumist",
		"master parfumists"}), "say Ahh, that would be my sister Vynessa.  "
	+ "She really is quite skilled, but enough about her.", 1);
	add_ask(({"sister", "vynessa"}), "say Oh yes, Vynessa.  Well she creates "
	+ "the perfumes and colognes.  Her sense of smell is the sharpest and "
	+ "her tastes impeccable.", 1);
	add_ask(({"cosmias", "tortuous", "jordessia"}), "say Ahh, these "
	+ "fragrances will add appeal to any lady.  Try a sample on the counter "
	+ "to your left?", 1);
	add_ask(({"control", "hammer", "white hammer", "krom"}), "say These "
	+ "manly scents are sure to give a man the attention of which he is "
	+ "worthy... and perhaps a bit more.  Try a sample on the counter to "
	+ "your right.", 1);
	add_ask(({"sample", "samples"}), "say Try a sample from either counter, "
	+ "the ladies' fragrances to your left or the mens' on the right.  Just "
	+ "<sample name>.", 1);
	add_ask(({"parfumerie", "parfumeries", "jordesse", "jordesse parfumerie"}),
	  "say The Jordesse parfumerie was founded by my sister not long ago.  "
	+ "She really is a skilled parfumist.  There are no parfumeries that "
	+ "rival the popularity of our perfumes and colognes.  I think you'll "
	+ "agree after trying them.  In fact why not try a sample now?", 1);
	add_ask(({"court", "court d'plaisiri", "plaisir district", "plaisiri"}),
	  "The parfumist's eyes light up as he goes:  Ahhhhh, the Court "
	+ "d'Plaisiri's every nook is filled with any desirable service and "
	+ "every cranny with whatever else you can imagine.\nHe winks "
	+ "very suggestively as he beams his wide, perfect smile.\n");
	add_ask(({"service", "services"}), "say We of course sell the most "
	+ "popular and desirable fragrances, but also in the Court d'Plaisiri "
	+ "is Dienya's fine clothing store, the Mer-Cantile cafe, the "
	+ "Laethorian  dayspa, and Gui's wine cellar.", 1);
	add_ask(({"dienya", "dienya's", "clothes", "clothing", "clothing store",
		"fine clothing"}), "say Mmm, Dienya.  She is so beautiful, and her "
	+ "clothes are excellent.  That is where I get all mine.", 1);
	add_ask(({"mer-cantile", "cafe", "mer-cantile cafe"}), "say The "
	+ "Mer-cantile cafe serves the widest variety of coffees and teas "
	+ "anywhere.  Ask for Lani.  She's very... how to say... friendly.", 1);
	add_ask(({"lani", "barista"}), "say Lani, ahh that lovely young lady.  "
	+ "She is a skilled barista at the Mer-Cantile cafe.", 1);
	add_ask(({"gui", "gui's", "cellar", "wine cellar", "gui's wine cellar"}),
	  "say Gui is a noble whose estate is down the side street to the "
	+ "southeast.  He collects and sells wines from his wine cellar.  That "
	+ "is -the- place to go for the finest wines.", 1);
	add_ask(({"laethorian", "spa", "dayspa", "laethorian dayspa"}), "say "
	+ "The Laethorian dayspa is so relaxing.  Baths, massages, and many "
	+ "other pleasurable services are available there, and the ladies who "
	+ "work there are exquisite.", 1);

    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");

}

void
arm_me()
{
    seteuid(getuid(TO));

	// Armil's custom vest.
	string cusvest = one_of_list(({"tight", "low-cut", "unbuttoned",
		"unlaced"}));
	string colvest = one_of_list(({"black", "charcoal", "silvery"}));
	string matvest = one_of_list(({"elfwyr", "organdie", "messaline", 
		"silk"}));

	object dvest = clone_object(MY_CLOTHING);
    dvest->set_armour_data("armil" + "&&"
							+ cusvest + "&&"
							+ colvest + "&&"
							+ matvest + "&&"
							+ "vest");
	dvest->move(TO);

	// Armil's custom legwear.
	string cuspants = one_of_list(({"tight", "low-cut", "sporty"}));
	string colpants = one_of_list(({"black", "silvery", "white",
		"beige"}));
	string matpants = one_of_list(({"elfwyr", "silk", "suede"}));
	string artpants = one_of_list(({"pants", "baggy-pants"}));

	object dpants = clone_object(MY_CLOTHING);
    dpants->set_armour_data("armil" + "&&"
							+ cuspants + "&&"
							+ colpants + "&&"
							+ matpants + "&&"
							+ artpants);
	dpants->move(TO);

	command("wear all");
	MONEY_MAKE_GC(random(23))->move(TO);
	MONEY_MAKE_SC(40 + random(35))->move(TO);
}

string
def_answer()
{
    command("say I'm very sorry.  But I haven't heard about that...  yet.");
	command("emote smiles charmingly at you as he flips back his long, curly "
	+ "black hair behind his shoulder.");
    return "";
}

string
women_from()	// If you use \n in an npc's <say> does it do a newline?
{
	return one_of_list(({"Palanthas are so beautiful.",
		"Sybarus are so alluring.",
		"Undraeth are so dangerously exciting.",
		"Qualinesti are so elusive.",
		"Tyr are so firm with a rugged beauty.",
		"Gont are so homey.",
		"Neraka have such a dark beauty.",
		"Edoras are so shield-maideny.",
		"Minas tirith have such noble beauty.",
		"Rivendell are so hot, and they stay that way a long time.",
		"Vingaard are so lovely.",
		"Dargaard have such a bountiful beauty.\nHe wiggles his eyebrows "
			+ "suggestively.",
		"Calathin smell so foresty.",
		"Emerald have such a pale beauty.",
		"Sparkle are hot... if a little young.\nHe winks suggestively.",
		"the Silent Forest are not only well endowed, but they don't "
			+ "talk too much either."}));
}