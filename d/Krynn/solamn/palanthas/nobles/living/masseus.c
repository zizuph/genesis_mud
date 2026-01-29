/* Mortis 02.2006
 * 
 * Woman who gives massages to men/women in the Laethorian spa
 * and body in the Plaisir district of Palanthas.
 *
 * Massage heals 500 health if player is undisturbed.
 * Only allowed once per login.
 */

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"

inherit CITIZEN;

#define MY_ARMOUR			MERCH + "arms/larmour"
#define HAD_MASSAGE			"_i_had_a_massage"
#define TABLED				"_i_am_laying_on_massage_table"

int alrm = 0; /* The alarm while giving a massage. */
string oil;

void
create_krynn_monster()
{
    set_name("seng");
	set_living_name("seng");
    set_race_name("human");
    set_adj("thin");
    add_adj("black-haired");
	add_name(({"seng", "human", "masseus"}));
	set_title("of the City Afar, Masseus of the Laethorian");
	set_short("thin black-haired masseus");
    set_long("The masseus is very thin with dark, almond shaped brown eyes "
	+ "and long black hair folded stylishly across her brow and tied back "
	+ "into a pony tail that hangs midway down her back.  She appears very "
	+ "young, perhaps not twenty yet, with a very lightly muscled, athletic "
	+ "build.\nHer curvy lips are smiling in a friendly manner.\n");
	set_gender(G_FEMALE);

    set_stats(({40, 115, 55, 60, 65, 40}));
	set_all_hitloc_unarmed(25);
	set_all_attack_unarmed(30, 28);

    set_skill(SS_AWARENESS,    35);
	set_skill(SS_DEFENCE,      50);
	set_skill(SS_UNARM_COMBAT, 50);
	set_skill(SS_BLIND_COMBAT, 50);

    set_size_descs("of normal length", "skinny");
	set_appearance(5);

	set_alignment(550);
	set_knight_prestige(-35);
	
	set_introduce(1);
    set_act_time(35);
    add_act("say Welcome, may I offer you a massage?");
	add_act("emote turns to the counter by the massage table and arranges "
	+ "@@counter_arrange@@" + ".");
	add_act("smell");
	add_act("emote folds her hands together and stretches her neck to each "
	+ "side.");
	add_act("emote pours a drop of green-tinged moisturizing lotion onto the "
	+ "back of her hand and massages it in.");

	set_cact_time(15);
	add_cact("emote plants a hand and flips to her " + one_of_list(({"left",
	"right"})) + " in a sudden defensive maneuver.");
	add_cact("emote bends backwards avoiding your strike, the light muscles "
	+ "of her stomach visible through the stretched white material of her "
	+ "elfwyr bodysuit.");
	add_cact("emote brushes your attack aside with her open palm.\nHer dark, "
	+ "almond-shaped, brown eyes do not waver from yours.");

    
    add_ask(({"pricelist", "prices", "price", "list"}), "say Our prices "
	+ "are on the marble sign.  A massage is ten gold coins.", 1);
	add_ask(({"palanthas"}), "say Palanthas is nice, yes.  My family "
	+ "came here when I was little.", 1);
	add_ask("family", "say My father and I came here from a city far away.  "
	+ "I don't think you would recognize it.", 1);
	add_ask(({"city", "city afar"}), "emote smiles reminiscently.", 1);
	add_ask(({"fragrance", "scent", "perfume", "cologne",
		"krom", "control", "white hammer", "tortuous", "jordessia",
		"cosmias", "rose"}), "say Our cleansing waters are scented with the "
	+ "latest Jordesse perfumes and colognes.  They are designed with the "
	+ "greatest skill and care by the master parfumist.", 1);
	add_ask(({"parfumist", "parfumists", "master parfumist",
		"master parfumists"}), "say Vynessa Jordesse is the master parfumist "
	+ "of the Jordesse parfumerie off the Court d'Plaisiri right here in the "
	+ "Plaisir district.  She is very skilled, but her brother is the face "
	+ "of the business... and also handsome.", 1);
	add_ask(({"vynessa"}), "say Oh, Vynessa is very nice but very shy and "
	+ "reclusive.  They say her sense of smell is the sharpest and her "
	+ "tastes impeccable.", 1);
	add_ask(({"parfumerie", "parfumeries", "jordesse", "jordesse parfumerie"}),
	  "say The Jordesse parfumerie was founded by Vynessa not long ago.  "
	+ "She really is a skilled parfumist.  There are no parfumeries that "
	+ "rival the popularity of her perfumes and colognes.  They offer "
	+ "free samples.  You should try one.  In fact we use only Jordesse "
	+ "parfumerie scented waters here for our massages.", 1);
	add_ask(({"court", "court d'plaisiri", "plaisir district", "plaisiri"}),
	  "say The court is very beautiful.  It has the finest "
	+ "clothes, best hot drinks, most popular fragrances, excellent "
	+ "wines, and of course the Laethorian, the best dayspa in the "
	+ "city.\n", 1);
	add_ask(({"service", "services"}), "say The Laethorian provides a "
	+ "range of pampering services.  I can give you a massage if you like.  "
	+ "Have a look at our sign for help getting started.", 1);
	add_ask(({"dienya", "dienya's", "clothes", "clothing", "clothing store",
		"fine clothing"}), "say Oh, I love Dienya!  Her clothes are so "
	+ "amazing.", 1);
	add_ask(({"mer-cantile", "cafe", "mer-cantile cafe"}), "say The "
	+ "Mer-cantile cafe serves the widest variety of coffees and teas "
	+ "anywhere.  Their barista Lani is nice, too, I suppose.", 1);
	add_ask(({"lani", "barista"}), "say Lani, oh.  She is very beautiful "
	+ "and a barista at the Mer-Cantile cafe owned by her father.", 1);
	add_ask(({"gui", "gui's", "cellar", "wine cellar", "gui's wine cellar"}),
	  "say Gui is a noble whose estate is down the side street to the "
	+ "southeast.  He collects and sells wines from his wine cellar.  Some "
	+ "of them are quite special.", 1);
	add_ask(({"laethorian", "spa", "dayspa", "laethorian dayspa"}), "say "
	+ "The Laethorian dayspa is the best!  Baths, massages, and many "
	+ "other pleasurable services are available here like massages, "
	+ "manicures, pedicures, and you can even have your hair done.", 1);
	add_ask("bodysuit", "say Do you like it?\nShe smiles softly.", 1);
	add_ask("age", "say I'm eighteen.", 1);

    set_default_answer("@@def_answer");

	set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    seteuid(getuid(TO));

	// Seng's custom belt.
	object sbelt = clone_object(MY_ARMOUR);
    sbelt->set_armour_data("plain"  + "&&"
							+ "white" + "&&"
							+ "soft" + "&&"
							+ "belt");
	sbelt->move(TO);

	// Seng's custom boots.
	object sboots = clone_object(MY_ARMOUR);
    sboots->set_armour_data("thin"  + "&&"
							+ "white" + "&&"
							+ "soft" + "&&"
							+ "boots");
	sboots->move(TO);

	// Seng's bodysuit.
	object sbody = clone_object(NOBLE + "arms/seng_bodysuit");
	sbody->move(TO);

	command("wear all");
	MONEY_MAKE_GC(5 + random(19))->move(TO);
	MONEY_MAKE_SC(20 + random(35))->move(TO);
}

string
def_answer()
{
    command("emote blushes briefly and smiles.");
	command("say Ummmmm, sorry.  I don't know.");
    return "";
}

string
counter_arrange()
{
	return one_of_list(({"a few jars of fragrant oils", "a row of jars",
	"a stack of small, white towels"}));
}

int
react_bow(object actor)
{
	command("bow");
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "bow")
        set_alarm(1.0, 0.0, &react_bow(actor));
}

void
init_living()
{
    ADA("order");
    ::init_living();
}

int
order(string str)
{
    if (alrm == 1)
	{
		command("say I am in the middle of a massage, but I will be right "
		+ "with you.  Have a seat?");
		return 1;
	}

	NF("Order what?  A massage?  Try <read sign>.\n");
    if (!str || str != "massage")
      return 0;

	NF("You've already had a massage.  Relax a little?\n");
	if (TP->query_prop(HAD_MASSAGE))
		return 0;

	if (TP->query_prop(TABLED))
	{
		if (!MONEY_ADD(TP, -1440))
		{
			command("say I'm sorry, but massages are ten gold coins.  "
			+ "Can you get that and come back?");
			return 1;
		}
		TP->catch_msg("You pay the masseus ten gold coins.\n");
		alrm = 1;
		set_alarm(2.0, 0.0, "massage_routine", TP);
		return 1;
	}
	command("say If you would like a massage, please lay on the table.");
	return 1;
}

void
massage_routine(object facee)
{
	oil = one_of_list(({"red-tinged", "green-tinged", "clear",
		"clear blue"}));

	command("curtsey");
	command("introduce myself");
	command("say Alright, let's begin.");
	facee->catch_msg("Seng takes a jar of " + oil + " oil from the counter "
	+ "and works it into her fingers and hands.\n");
	say("Seng takes a jar of " + oil + " oil from the counter beside "
	+ QTNAME(facee) + "'s massage table and works it into her fingers and "
	+ "hands.\n");
	set_alarm(8.5, 0.0, "massage_routine2", facee);	
}

void
massage_routine2(object facee)
{
	if (facee->query_prop(TABLED))
	{
		command("emote bends over the massage table, the elfwyr of her "
		+ "skin-tight white bodysuit stretching across her small buttocks.");
		facee->catch_msg("Seng firmly rubs the " + oil + " oil into your "
		+ "shoulders as her thumbs massage the muscles of your neck "
		+ "immediately relaxing them.\n");
		say("Seng firmly rubs the " + oil + " oil into " + QCTNAME(facee)
		+ "'s shoulders as her thumbs massage the muscles of " + HIS(facee)
		+ "neck.\n");
		set_alarm(4.5, 0.0, "massage_enjoy", facee);
		set_alarm(14.5, 0.0, "massage_routine3", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_massage", facee);
}

void
massage_routine3(object facee)
{
	if (facee->query_prop(TABLED))
	{
		facee->catch_msg("Seng firmly rubs the " + oil + " oil down your "
		+ "triceps to your forearms rubbing in slow circles as she comes "
		+ "to your hands and massages your palm and each finger with "
		+ "tender care.\n");
		say("Seng firmly rubs the " + oil + " down " + QCTNAME(facee)
		+ "'s triceps to " + HIS(facee) + " forearms rubbing in slow circles "
		+ "as she comes to " + HIS(facee) + " hands, massaging " + HIS(facee)
		+ " palm and each finger with tender care.\n");
		set_alarm(6.5, 0.0, "massage_enjoy", facee);
		set_alarm(17.5, 0.0, "massage_routine4", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_massage", facee);
}

void
massage_routine4(object facee)
{
	if (facee->query_prop(TABLED))
	{
		oil = one_of_list(({"red-tinged", "green-tinged", "clear",
		"blue-tinged"}));

		command("stretch");
		facee->catch_msg("Seng wipes her hands on a white towel, takes a jar "
		+ "of " + oil + " oil from the counter and works some more massage "
		+ "oil into her fingers and hands before continuing her ministrations "
		+ "down your spine, easing the muscles of your back as she strokes "
		+ "your sensitive, muscular sides.\n");
		say("Seng wipes her hands on a white towel, takes a jar of " + oil
		+ " oil from the counter and works some more massage oil into her "
		+ "fingers and hands before continuing her ministrations down "
		+ QTNAME(facee) + "'s spine, easing the muscles of " + HIS(facee)
		+ " back as she strokes " + HIS(facee) + " muscular sides.\n");
		set_alarm(7.5, 0.0, "massage_enjoy", facee);
		set_alarm(19.5, 0.0, "massage_routine5", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_massage", facee);
}

void
massage_routine5(object facee)
{
	if (facee->query_prop(TABLED))
	{
		facee->catch_msg("Seng firmly massages the " + oil + " oil into your "
		+ "outer thighs rubbing in slow circles as she moves around to your "
		+ "inner thighs then gradually down to the backs of your knees.\n");
		say("Seng firmly massages the " + oil + " into " + QCTNAME(facee)
		+ "'s outer thighs rubbing in slow circles as she moves around to "
		+ HIS(facee) + " inner thighs then gradually down to the backs of "
		+ HIS(facee) + " knees.\n");
		set_alarm(4.5, 0.0, "massage_enjoy", facee);
		set_alarm(18.5, 0.0, "massage_routine6", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_massage", facee);
}

void
massage_routine6(object facee)
{
	if (facee->query_prop(TABLED))
	{
		command("emote pulls her shoulders back as she works, the elfwyr of "
		+ "her skin-tight white bodysuit stretching tight against the small, "
		+ "firm curves of her chest.");
		facee->catch_msg("Seng continues massaging the " + oil + " oil from "
		+ "your knees down your calves squeezing them in slow circles as she "
		+ "makes her way to your ankles.\nSeng takes your feet and squeezes "
		+ "and kneads their bottoms with her thumbs before gently caressing "
		+ "each toe individually.\n");
		say("Seng continues massaging the " + oil + " oil from "
		+ QTNAME(TP) + "'s knees down to " + HIS(facee) + " calves squeezing "
		+ "them in slow circles as she makes her way to " + HIS(facee)
		+ " ankles.\nSeng takes " + HIS(facee) + " feet and squeezes and "
		+ "kneads their bottoms with her thumbs before gently caressing each "
		+ "toe individually.\n");
		set_alarm(7.5, 0.0, "massage_enjoy", facee);
		set_alarm(17.5, 0.0, "massage_routine7", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_massage", facee);
}

void
massage_routine7(object facee)
{
	if (facee->query_prop(TABLED))
	{
		string sjar;

		if (facee->query_gender() == G_MALE)
		{
			sjar = one_of_list(({"White Hammer", "Krom", "Control"}));
		}
		
		if (facee->query_gender() != G_MALE)
		{
			sjar = one_of_list(({"rose", "Jordessia", "Cosmias", "Tortuous"}));
		}

		facee->catch_msg("Seng takes a small, white towel from the stack "
		+ "of towels on the counter, soaks it into a jar of " + sjar
		+ "-scented water, and uses both hands to squeeze your body, neck "
		+ "to toes, wiping off the " + oil + " massage oil and cleansing "
		+ "your skin.\n");
		say("Seng takes a small, white towel from the stack of towels "
		+ "on the counter, soaks it into a jar of " + sjar + "-scented "
		+ "water, and uses both hands to squeeze " + QCTNAME(facee) + "'s "
		+ "body, neck to toes, wiping off the massage " + oil + " oil and "
		+ "cleansing " + HIS(TP) + " skin.\n");
		set_alarm(4.5, 0.0, "massage_enjoy", facee);
		set_alarm(9.5, 0.0, "massage_enjoy", facee);
		set_alarm(21.0, 0.0, "massage_routine8", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_massage", facee);
}

void
massage_routine8(object facee)
{
	object msubloc, myroom = E(TO);

	if (facee->query_prop(TABLED))
	{
		command("emote shifts from one leg to the other, the lithe muscles "
		+ "of her thin body pressing against the skin-tight elfwyr of her "
		+ "bodysuit, as she washes her hands in a bowl on the counter and "
		+ "dries them on a small, white towel.");
		facee->catch_msg("Seng helps you up from the massage table as "
		+ "she says:  Thank you for coming.  I hope you enjoyed yourself.  "
		+ "Please come see me again.\n");
		say("Seng helps " + QCTNAME(facee) + " up from the massage table as "
		+ "she says:  Thank you for coming.  I hope you enjoyed yourself.  "
		+ "Please come see me again.\n");
		facee->remove_prop(TABLED);
		facee->remove_prop(LIVE_S_EXTRA_SHORT);
		myroom->off_table();
		facee->add_prop(HAD_MASSAGE, 1);
		facee->heal_hp(500);

		msubloc = clone_object(NOBLE + "obj/spa_masseus_subloc");
		msubloc->move(facee);

		alrm = 0;
		return;
	}
	set_alarm(0.5, 0.0, "ruin_massage", facee);
}

void
massage_enjoy(object facee)
{
	string self = one_of_list(({"As pleasurable sensations tingle across "
	+ "your body, you feel yourself floating off the massage table.\nA "
	+ "rainbow streaks by.\nYour head is swimming.",
	  "The " + oil + " oil heats up upon your skin.  You feel your "
	+ "muscles relaxing sensually as your head swims under its heady "
	+ "fragrance.",
	  "Your skin throbs warmly under the " + oil + " oil, sending "
	+ "shivers of warmth down your spine and into your extremities.",
	  "Your neck feels pleasurably warm underneath the " + oil + " oil.\n"
	+ "You almost doze off, overcome by the sensation.",
	  "Your muscles loosen and feel as if energy is pouring directly into "
	+ "them.\nYour body feels dreamy.",
	  "You think to yourself:  Mmmmmm.",
	  "You groan under the masseus' ministrations:  Ahhhhh.",
	  "\"Oh, yes,\" this feels good.",
	  "The masseus is undeniably a professional you think to yourself as her "
	+ "strong, able hands restore your energy.",
	  "You feel yourself transported to another world full of relaxing "
	+ "energies and " + oil + " skies of pleasure.",
	  "You sigh to yourself as you wonder how you got by for so long without "
	+ "indulging yourself so pleasurably."}));

	string others = one_of_list(({"moans quietly as " + HE(facee)
	+ " squeezes " + HIS(facee) + " legs together.",
	  "says: Mmmmm.",
	  "says: Oh, gods, don't stop.",
	  "says: Ohp!  That's the spot... yes, ohhhhh.",
	  "mumbles something about pretty rainbows.",
	  "licks " + HIS(facee) + " lips slowly.",
	  "says: Mmmm, my skin... so good.",
	  "groans under the masseus' ministrations:  Ohhhhh.",
	  "mumbles something about a world of new age energies.",
	  "says: My body feels so good.",
	  "sighs in utter relaxation.",
	  "sighs pleasurably.",
	  "breathes in and out slowly in a state of deep relaxation.",
	  "smiles in an extremely relaxed manner.",
	  "says: You have GOT to try this.",
	  "says: Mmm, this is amazing."}));

	facee->catch_msg(self + "\n");
	say(QCTNAME(facee) + " " + others + "\n");
}

void
ruin_massage(object facee)
{
	facee->catch_msg("As you are no longer laying on the massage table at "
	+ "the Laethorian massage parlour, you have ruined your massage!\n");
	command("emote chews on her lower lip in confusion.");
	command("say Oh.");
	alrm = 0;
}
