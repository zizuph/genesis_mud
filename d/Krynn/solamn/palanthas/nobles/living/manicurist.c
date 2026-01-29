/* Mortis 01.2006
 * 
 * Does nails in the Laethorian spa and body in the
 * Plaisir district of Palanthas.
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <composite.h>

inherit CITIZEN;

#define MY_CLOTHING				NOBLE + "arms/parmour"

string cusdress = one_of_list(({"tight", "low-cut", "alluring"}));
string coldress = one_of_list(({"white", "pink", "indigo"}));
string matdress = one_of_list(({"cotton", "dupion",	"swansdown"}));

int alrm = 0; /* The alarm while giving service. */

void
create_krynn_monster()
{
    set_name("tildee");
	set_living_name("tildee");
    set_race_name("human");
    set_adj("wide-hipped");
    add_adj("pouty-lipped");
	add_name(({"tildee", "waddell", "human", "manicurist", "pedicurist"}));
	set_title("Waddell, Nail Specialist of the Laethorian");
    set_long("The lady before you is not particularly tall but has "
	+ "particularly wide hips and a curvy figure.  The cut of her "
	+ cusdress + " " + coldress + " dress pushes her considerable bosom "
	+ "up flatteringly.  Her pouty lips are glossy and pink and surrounded "
	+ "by wide, flat cheeks with a rosy hue.  Her hands, though small, are "
	+ "strong, and her wrists bear several bracelets.  Her waist length, "
	+ "dark brown hair is tied back with a white ribbon behind her neck but "
	+ "hangs down from there across her shoulders and bosom.\n");
	set_gender(G_FEMALE);
    set_stats(({55, 45, 100, 60, 45, 80}));
	set_all_hitloc_unarmed(20);

    set_skill(SS_AWARENESS, 30);
    set_size_descs("short", "plump");
	set_appearance(6);

	set_alignment(600);
	set_knight_prestige(-30);
	
	set_introduce(1);
    set_act_time(12);
    add_act("say Hello and welcome to the Laethorian.  Would you like "
	+ "@@you_like@@" + "?");
	add_act("smell");
	add_act("smile cheer");
	add_act("say You really deserve to pamper yourself, and for that you've "
	+ "come to the right place.");
	add_act("say The Laethorian is the best place in the city for "
	+ "pampering.");
    
    add_ask(({"pricelist", "prices", "price", "list"}), "say All manicures "
	+ "are just six gold coins.", 1);
	add_ask(({"city", "palanthas"}), "say Oh my.  Palanthas is such a "
	+ "nice, clean city and with so many wonderful services.  And safety?  "
	+ "Well, I really feel safe here, too.", 1);
	add_ask(({"fragrance", "scent", "perfume", "cologne",
		"krom", "control", "white hammer", "tortuous", "jordessia",
		"cosmias", "rose"}), "say Our cleansing waters are scented with the "
	+ "latest Jordesse perfumes and colognes.  They are designed with the "
	+ "greatest skill and care by the master parfumist.", 1);
	add_ask(({"parfumist", "parfumists", "master parfumist",
		"master parfumists"}), "say Vynessa Jordesse is the master parfumist "
	+ "of the Jordesse parfumerie off the Court d'Plaisiri right here in the "
	+ "Plaisir district.  She really is quite skilled, but her handsome "
	+ "brother is the face of the business.", 1);
	add_ask(({"vynessa"}), "say Oh Vynessa.  Though her sense of smell is "
	+ "the sharpest and her tastes impeccable, she is so shy and reclusive!  "
	+ "I don't think she'll ever find herself a husband.", 1);
	add_ask(({"parfumerie", "parfumeries", "jordesse", "jordesse parfumerie"}),
	  "say The Jordesse parfumerie was founded by Vynessa not long ago.  "
	+ "She really is a skilled parfumist.  There are no parfumeries that "
	+ "rival the popularity of her perfumes and colognes.  They offer "
	+ "free samples.  You should try one.  In fact we use only Jordesse "
	+ "parfumerie scented waters here for our facials.", 1);
	add_ask(({"court", "court d'plaisiri", "plaisir district", "plaisiri"}),
	  "say Oh, the court is such a pleasant place.  It has the finest "
	+ "clothes, best hot drinks, most popular fragrances, excellent "
	+ "wines, and of course the Laethorian, the best dayspa in the "
	+ "city.\n", 1);
	add_ask(({"service", "services"}), "say The Laethorian provides a "
	+ "range of pampering services.  I can give you a facial if you like, "
	+ "dear.  Have a look at our sign for help getting started.  To the "
	+ "east my sister can give you a facial.", 1);
	add_ask(({"dienya", "dienya's", "clothes", "clothing", "clothing store",
		"fine clothing"}), "say Oh, Dienya!  Such a lovely girl, and her "
	+ "clothes are just perfect.  That is where I get this dress!", 1);
	add_ask(({"mer-cantile", "cafe", "mer-cantile cafe"}), "say The "
	+ "Mer-cantile cafe serves the widest variety of coffees and teas "
	+ "anywhere.  And that Lani is such a cute little darling.", 1);
	add_ask(({"lani", "barista"}), "say Lani, oh what a beautiful little "
	+ "girl.  Her father must be proud.  She is a skilled barista at the "
	+ "Mer-Cantile cafe.", 1);
	add_ask(({"gui", "gui's", "cellar", "wine cellar", "gui's wine cellar"}),
	  "say Gui is a noble whose estate is down the side street to the "
	+ "southeast.  He collects and sells wines from his wine cellar.  Some "
	+ "of them are quite special.", 1);
	add_ask(({"laethorian", "spa", "dayspa", "laethorian dayspa"}), "say "
	+ "The Laethorian dayspa is the best!  Baths, massages, and many "
	+ "other pleasurable services are available here like facials, "
	+ "manicures, pedicures, and you can even have your nail done.", 1);
	add_ask("dress", "say Oh, the dress?  Do you like it?  Dienya tailored "
	+ "it for me.  She is so skilled!", 1);
	add_ask(({"manicure", "nails", "nail", "nail-claws", "claws", "talons"}),
	  "say I'd love to your nails.  Have a look at the sign and pick out how "
	+ "you'd like them done.", 1);

    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");

}

void
arm_me()
{
    seteuid(getuid(TO));

	// tildee's custom dress.
	object ddress = clone_object(MY_CLOTHING);
    ddress->set_armour_data("tildee" + "&&"
							+ cusdress + "&&"
							+ coldress + "&&"
							+ matdress + "&&"
							+ "dress");
	ddress->move(TO);

	command("wear all");
	MONEY_MAKE_GC(random(13))->move(TO);
	MONEY_MAKE_SC(30 + random(30))->move(TO);
}

string
def_answer()
{
    command("emote folds an arm across her chest, places her other "
	+ "elbow upon it, pushing her bosom together, and rests her chin "
	+ "upon her hand, .");
	command("say Hmmmmm.  Sorry, don't know.");
    return "";
}

string
you_like()
{
	return one_of_list(({"a manicure", "a pedicure", "me to do your nails"}));
}

void
init_living()
{
    ::init_living();
}


/*
int
order(string str)
{
    if (alrm == 1)
	{
		command("say I am in the middle of a facial at the moment, but "
		+ "I will be right away at your service shortly.");
		return 1;
	}

	NF("Order what?  A facial?  Try <read sign>.\n");
    if (!str)
      return 0;

	NF("Order what kind of facial?  A cucumber paste, seaweed wrap, or "
	+ "apricot scrub?  Try <read sign>.\n");
	if (str != "cucumber paste" && str != "seaweed wrap" && str != "apricot scrub")
	{ return 0; }

	NF("You've already had a facial.  You'll either have to come back "
	+ "tomorrow or scrub that one off in the bath.\n");
/*	if (TP->query_prop(HAD_FACIAL))
	{ return 0; }

	if (TP->query_prop(TSIT))
	{
		command("say You'll need to be reclined first, dear.  Please pull "
		+ "the handle on the left of your cnail.");
		return 1;
	}

	if (TP->query_prop(FSIT))
	{
		if (str == "cucumber paste")
		{
			if (!MONEY_ADD(TP, -864))
			{
				command("say Oh, I'm sorry dear, but facials are six gold "
				+ "coins, and I'm afraid you don't quite have that.");
				return 1;
			}
			TP->catch_msg("You pay the pamperer six gold coins.\n");
			alrm = 1;
			set_alarm(2.0, 0.0, "cucumber_paste", TP);
			return 1;
		}

		if (str == "seaweed wrap")
		{
			if (!MONEY_ADD(TP, -864))
			{
				command("say Oh, I'm sorry dear, but facials are six gold "
				+ "coins, and I'm afraid you don't quite have that.");
				return 1;
			}
			TP->catch_msg("You pay the pamperer six gold coins.\n");
			alrm = 1;
			set_alarm(2.0, 0.0, "seaweed_wrap", TP);
			return 1;
		}

		if (str == "apricot scrub")
		{
			if (!MONEY_ADD(TP, -864))
			{
				command("say Oh, I'm sorry dear, but facials are six gold "
				+ "coins, and I'm afraid you don't quite have that.");
				return 1;
			}
			TP->catch_msg("You pay the pamperer six gold coins.\n");
			alrm = 1;
			set_alarm(2.0, 0.0, "apricot_scrub", TP);
			return 1;
		}
	}
	command("say You'll need to have a seat in one of the cnails first, "
	+ "dear, and then recline.  Have you read the sign yet?\n");
	return 1;
}
*/
void
apricot_scrub(object facee)
{
	command("curtsey");
	command("introduce myself");
	command("say Alright, let's get started.");
	facee->catch_msg("tildee waddles around behind your cnail, takes a jar "
	+ "of clear Gent-Oil from the counter station to your right, and rubs "
	+ "it into her fingers.\n");
	say("tildee waddles around behind " + QCTNAME(facee) + "'s cnail, takes "
	+ "a jar of clear Gent-Oil from the counter station to " + HIS(facee)
	+ " right, and rubs it into her fingers.\n");
	set_alarm(8.5, 0.0, "apricot_scrub2", facee);	
}

void
apricot_scrub2(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("tildee gently rubs the massage oil into your neck, "
		+ "immediately relaxing you, and warming your skin.\n");
		say("tildee gently rubs the massage oil into "
		+ QCTNAME(facee) + "'s neck eliciting a smile from " + HIM(facee)
		+ ".\n");
		set_alarm(10.5, 0.0, "apricot_scrub3", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
apricot_scrub3(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("tildee rubs the massage oil slowly up your neck "
		+ "to your jaw, swirling it around your cheeks, then nose and "
		+ "forehead, pausing as she goes to gently massage your temples.\n"
		+ "The skin of your face flushes as a luxurious warmth spreads "
		+ "out across it.\n");
		say("tildee gently rubs the massage oil slowly up " + QCTNAME(facee)
		+ "'s neck to " + HIS(facee) + " jaw, swirling it around "
		+ HIS(facee) + " cheeks, then nose and forehead, pausing as she "
		+ "goes to gently massage " + HIS(facee) + " temples.  "
		+ C(HIS(facee)) + " face flushes as " + HE(facee) + " smiles in a "
		+ "very relaxed manner.\n");
		set_alarm(12.5, 0.0, "apricot_scrub4", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
apricot_scrub4(object facee)
{
	if (facee->query_prop(FSIT))
	{
		string sjar;

		if (facee->query_gender() == 0)
		{
			sjar = one_of_list(({"White Hammer", "Krom", "Control"}));
		}
		
		if (facee->query_gender() != 0)
		{
			sjar = one_of_list(({"rose", "Jordessia", "Cosmias", "Tortuous"}));
		}

		facee->catch_msg("tildee takes a small, white towel from the stack "
		+ "of towels on the counter, dips it into a jar of " + sjar
		+ "-scented water, and dabs softly at your face cleansing it.\n");
		say("tildee takes a small, white towel from the stack of towels "
		+ "on the counter, dips it into a jar of " + sjar + "-scented "
		+ "water, and dabs softly at " + QCTNAME(facee) + "'s face "
		+ "cleansing it.\n");
		set_alarm(11.5, 0.0, "apricot_scrub5", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
apricot_scrub5(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("tildee takes a jar of thick, brown-speckled "
		+ "apricot scrub from the counter.  She begins caressing it into "
		+ "your neck, slowly swirling her fingers in circles as she works "
		+ "her way up to your face.  As she begins rubbing the thick, "
		+ "apricot coloured cream into your cheeks you feel an ultra-fine "
		+ "grainy abrasive gently scrubbing away the dry, dead outer layer "
		+ "of your skin.\n");
		say("tildee takes a jar of thick, brown-speckled apricot scrub from "
		+ "the counter.  She begins caressing it into " + QCTNAME(facee)
		+ "'s neck, slowly swirling her fingers in circles as she works her "
		+ "way up to " + HIS(facee) + " face.\n");
		set_alarm(16.0, 0.0, "apricot_scrub6", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
apricot_scrub6(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("tildee continues swirling the thick, apricot- "
		+ "coloured scrub in small circles moving across your nose, up to "
		+ "your forehead, and rubs in slow, firm circles around your "
		+ "temples.  Your skin feels as if it is being set free from an old, "
		+ "dry prison and immersed in apricot rich moisturizer as you become "
		+ "extremely relaxed.\nYour neck and face throb pleasurably with the "
		+ "sensation.\n");
		say("tildee continues swirling the thick, apricot-coloured scrub in "
		+ "small circles moving across " + QCTNAME(facee) + "'s nose, up to "
		+ HIS(facee) + " forehead, and rubs in slow, firm circles around "
		+ HIS(facee) + " temples.  " + C(HE(facee)) + " appears extremely "
		+ "relaxed and is breathing slowly and deeply.\n");
		set_alarm(17.0, 0.0, "apricot_scrub7", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
apricot_scrub7(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("tildee folds out a fan from the counter and waves "
		+ "it over your face.  You feel the apricot scrub thicken into a "
		+ "gel which she peels from your face and neck in one rubbery "
		+ "piece leaving the fresh skin beneath it feeling exceptionally "
		+ "fresh and free.\n");
		say("tildee folds out a fan from the counter and waves it over "
		+ QCTNAME(facee) + "'s face thickening " + HIS(facee) + " apricot "
		+ "scrub into a gel which she then peels from " + HIS(facee) + " in "
		+ "one rubbery piece exposing fresh skin beneath.\n");
		set_alarm(18.5, 0.0, "apricot_scrub8", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
apricot_scrub8(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("tildee takes a jar of apricot finishing cream "
		+ "from the counter and applies a quantity to your neck and "
		+ "cheeks.  She then begins gently caressing it into your neck, "
		+ "chin, cheeks, nose, and forehead in small, swirling circles "
		+ "before massaging your temples luxuriously.\n");
		say("tildee takes a jar of apricot finishing cream from the counter "
		+ " and applies a quantity to " + QCTNAME(facee) + "'s neck and "
		+ "cheeks.  She then begins gently caressing it into " + HIS(facee)
		+ " neck, chin, cheeks, nose, and forehead in small, swirling "
		+ "circles befoer massaging " + HIS(facee) + " temples "
		+ "luxuriously.\n");
		command("say There, you just lay back and relax while that does "
		+ "its thing.  Take as much time as you like.  When it has finished, "
		+ "you may call an attendant over at anytime to <finish facial>.");
		set_alarm(60.0, 0.0, "apricot_scrub8", facee);
		set_alarm(15.0, 0.0, "apricot_enjoy", facee);
		set_alarm(30.0, 0.0, "apricot_enjoy", facee);
		set_alarm(45.0, 0.0, "apricot_enjoy", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
apricot_scrub9(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Your apricot finishing cream has finished soaking "
		+ "in.  It has a sweet citrus aroma and feels luxurious across your "
		+ "face and neck.  You could lay here all day in comfort.  When you "
		+ "are ready to have it removed, you may <finish facial>.\n");
		say(QCTNAME(facee) + "'s apricot finishing cream has finished "
		+ "soaking in.\n");
		facee->add_prop(BSIT, 3); // 3 indicates apricot scrub
		alrm = 0;
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
apricot_enjoy(object facee)
{
	string self = one_of_list(({"As sweet citrus sensations tingle across "
	+ "your face and neck, you feel as if you're floating through a walled "
	+ "orchard of grapefruits, oranges, and apricots.\nYour skin is "
	+ "starting to really feel refreshed.",
	  "The apricot finishing cream thickens a bit as its rich moisturizers "
	+ "seep into your skin.\nYour face and neck feel refreshed.",
	  "Your skin tingles warmly under the apricot finishing cream, sending "
	+ "pleasurable shivers down your spine and into your extremities.",
	  "Your skin feels warm and fresh.",
	  "You drift away in deep relaxation feeling as if the sun shone on your "
	+ "face for you alone.",
	  "You can't recall the last time you felt so good as you squirm "
	+ "comfortably in your reclined pale leather cnail and sigh deeply.",
	  "You think to yourself:  Mmmmmm.",
	  "You sigh to yourself as you wonder how you got by for so long without "
	+ "indulging yourself so pleasurably."}));

	string others = one_of_list(({"sighs quietly as " + HE(facee)
	+ "squeezes " + HIS(facee) + " arms around " + HIS(facee) + " body.",
	  "says: Mmmmm.",
	  "squirms comfortably in " + HIS(facee) + " pale leather cnail and "
	+ "sighs deeply.",
	  "licks " + HIS(facee) + " lips slowly.",
	  "smiles and sighs deeply.",
	  "says: Mmmmm, apricots.",
	  "sighs in utter relaxation.",
	  "sighs pleasurably.",
	  "breathes in and out slowly in a state of deep relaxation.",
	  "smiles in an extremely relaxed manner.",
	  "says: You have GOT to try this."}));

	facee->catch_msg(self + "\n");
	say(QCTNAME(facee) + " " + others + "\n");
}

void
ruin_facial(object facee)
{
	facee->catch_msg("As you are no longer reclining in a chair at the "
	+ "Laethorian pampering room, you have ruined your massage!\n");
	command("sigh");
	alrm = 0;
}
