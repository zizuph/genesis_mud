/* Mortis 01.2006
 * 
 * Gives facials in the Laethorian spa and body in the
 * Plaisir district of Palanthas.
 *
 * Gent-oil massage followed by:  seaweed wrap, cucumber paste,
 * or apricot scrub.
 *
 * Mortis 01.2007 - Added fire and shadow facials for morgul mages
 *                  at request of their nazgul.
 */

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"


inherit CITIZEN;

#define MY_CLOTHING		NOBLE + "arms/parmour"
#define HAD_FACIAL		"_i_had_a_facial"	/* 1 indicates cucumber paste
											 * 2 indicates seaweed wrap
											 * 3 indicates apricot scrub
											 * 4 indicates morgul fire
											 * 5 indicates morgul shadow */

int alrm = 0; /* The alarm while giving a facial. */

void
create_krynn_monster()
{
    set_name("zayzee");
	set_living_name("zayzee");
    set_race_name("human");
    set_adj("plump");
    add_adj("beehive-haired");
	add_name(({"zayzee", "waddell", "human", "facialist"}));
	set_title("Waddell, Facialist of the Laethorian");
    set_long("This middle-aged lady has wide, flat cheeks and a cheery "
	+ "smile.  Her hands, though small, are strong and covered with rings "
	+ "and bracelets, and her waist length hair is swirled around into a "
	+ "tall bun atop the back of her head.\n");
	set_gender(G_FEMALE);
    set_stats(({35, 30, 45, 40, 50, 60}));
	set_all_hitloc_unarmed(15);

    set_skill(SS_AWARENESS, 30);
    set_size_descs("of normal height", "plump");
	set_appearance(1);

	set_alignment(650);
	set_knight_prestige(-30);
	
	set_introduce(1);
    set_act_time(12);
    add_act("say Welcome to the pampering room!  May I offer you a facial?");
	add_act("emote waddles over to a counter beside a chair and arranges "
	+ "@@counter_arrange@@" + ".\n");
    add_act("emote smiles cheerily at you.");
	add_act("smell");
	add_act("smile cheer");
	add_act("say Rejuvenate yourself with a Gent-oil facial massage followed "
	+ "by the facial of your choice.");
	add_act("say You really deserve to pamper yourself, and for that you've "
	+ "come to the right place.");
	add_act("say The Laethorian is the best place in the city for "
	+ "pampering.");
    
    add_ask(({"pricelist", "prices", "price", "list"}), "say Our prices "
	+ "are on the sign hanging from the ceiling.  All facials are just "
	+ "six gold coins.", 1);
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
	+ "west you can have your nails done, and to the south is the hair "
	+ "stylist.", 1);
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
	+ "manicures, pedicures, and you can even have your hair done.", 1);
	add_ask("dress", "say Oh, the dress?  Do you like it?  Dienya tailored "
	+ "it for me.  She is so skilled!", 1);

    set_default_answer("@@def_answer");

}

void
arm_me()
{
    seteuid(getuid(TO));

	// Zayzee's custom dress.
	string cusdress = one_of_list(({"loose", "billowing", "buttoned",
		"long"}));
	string coldress = one_of_list(({"yellow", "pink", "pale-blue"}));
	string matdress = one_of_list(({"cotton", "dupion",	"swansdown"}));

	object ddress = clone_object(MY_CLOTHING);
    ddress->set_armour_data("zayzee" + "&&"
							+ cusdress + "&&"
							+ coldress + "&&"
							+ matdress + "&&"
							+ "dress");
	ddress->move(TO);

	command("wear all");
	MONEY_MAKE_GC(random(9))->move(TO);
	MONEY_MAKE_SC(20 + random(35))->move(TO);
}

string
def_answer()
{
    command("emote smiles cheerily.");
	command("say Oh my.  I'm afraid I just don't know about that.");
    return "";
}

string
counter_arrange()
{
	return one_of_list(({"a few jars of poultices", "a row of jars",
	"a stack of small, white towels", "a few cucumber slices"}));
}

void
init_living()
{
    ADA("order");
	ADD("finish_facial", "finish");
    ::init_living();
}

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

	if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		NF("Order what kind of facial?  A cucumber paste, seaweed wrap, "
		+ "apricot scrub, Morgul fire, or Morgul shadow?  Try <read sign>"
		+ ".\n");
		if (str != "cucumber paste" && str != "seaweed wrap" &&
			str != "apricot scrub" && str != "morgul fire" &&
			str != "morgul shadow")
			return 0;
	}
	else
	{
		NF("Order what kind of facial?  A cucumber paste, seaweed wrap, or "
		+ "apricot scrub?  Try <read sign>.\n");
		if (str != "cucumber paste" && str != "seaweed wrap" &&
			str != "apricot scrub")
			return 0;
	}

	NF("You've already had a facial.  You'll either have to come back "
	+ "tomorrow or scrub that one off in the bath when it opens.\n");
	if (TP->query_prop(HAD_FACIAL))
	{ return 0; }

	if (TP->query_prop(TSIT))
	{
		command("say You'll need to be reclined first, dear.  Please pull "
		+ "the handle on the left of your chair.");
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

		if (str == "morgul fire")
		{
			if (!MONEY_ADD(TP, -864))
			{
				command("say Oh, I'm sorry morgul dear, but facials are "
				+ "six gold coins, and I'm afraid you don't quite have "
				+ "that.  Maybe you could summon it?");
				return 1;
			}
			TP->catch_msg("You pay the pamperer six gold coins.\n");
			alrm = 1;
			set_alarm(2.0, 0.0, "morgul_fire", TP);
			return 1;
		}

		if (str == "morgul shadow")
		{
			if (!MONEY_ADD(TP, -864))
			{
				command("say Oh, I'm sorry morgul dear, but facials are "
				+ "six gold coins, and I'm afraid you don't quite have "
				+ "that.  Maybe you could summon it?");
				return 1;
			}
			TP->catch_msg("You pay the pamperer six gold coins.\n");
			alrm = 1;
			set_alarm(2.0, 0.0, "morgul_shadow", TP);
			return 1;
		}
	}
	command("say You'll need to have a seat in one of the chairs first, "
	+ "dear, and then recline.  Have you read the sign yet?\n");
	return 1;
}

void
cucumber_paste(object facee)
{
	command("curtsey");
	command("introduce myself");
	command("say Alright, let's get started.");
	facee->catch_msg("Zayzee waddles around behind your chair, takes a jar "
	+ "of clear Gent-Oil from the counter station to your right, and rubs "
	+ "it into her fingers.\n");
	say("Zayzee waddles around behind " + QCTNAME(facee) + "'s chair, takes "
	+ "a jar of clear Gent-Oil from the counter station to " + HIS(facee)
	+ " right, and rubs it into her fingers.\n");
	set_alarm(8.5, 0.0, "cucumber_paste2", facee);	
}

void
cucumber_paste2(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee gently rubs the massage oil into your neck, "
		+ "immediately relaxing you, and warming your skin.\n");
		say("Zayzee gently rubs the massage oil into "
		+ QCTNAME(facee) + "'s neck eliciting a smile from " + HIM(facee)
		+ ".\n");
		set_alarm(10.5, 0.0, "cucumber_paste3", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
cucumber_paste3(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee rubs the massage oil slowly up your neck "
		+ "to your jaw, swirling it around your cheeks, then nose and "
		+ "forehead, pausing as she goes to gently massage your temples.\n"
		+ "The skin of your face flushes as a luxurious warmth spreads "
		+ "out across it.\n");
		say("Zayzee gently rubs the massage oil slowly up " + QCTNAME(facee)
		+ "'s neck to " + HIS(facee) + " jaw, swirling it around "
		+ HIS(facee) + " cheeks, then nose and forehead, pausing as she "
		+ "goes to gently massage " + HIS(facee) + " temples.  "
		+ C(HIS(facee)) + " face flushes as " + HE(facee) + " smiles in a "
		+ "very relaxed manner.\n");
		set_alarm(12.5, 0.0, "cucumber_paste4", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
cucumber_paste4(object facee)
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

		facee->catch_msg("Zayzee takes a small, white towel from the stack "
		+ "of towels on the counter, dips it into a jar of " + sjar
		+ "-scented water, and dabs softly at your face cleansing it.\n");
		say("Zayzee takes a small, white towel from the stack of towels "
		+ "on the counter, dips it into a jar of " + sjar + "-scented "
		+ "water, and dabs softly at " + QCTNAME(facee) + "'s face "
		+ "cleansing it.\n");
		set_alarm(11.5, 0.0, "cucumber_paste5", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
cucumber_paste5(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee takes a pale green, cucumber paste poultice "
		+ "from the counter.  She begins caressing it into your neck, slowly "
		+ "swirling her fingers in circles as she works her way up to your "
		+ "face.  As she begins rubbing the pale green poultice into your "
		+ "cheeks your nose fills with a bright, cucumber fragrance blended "
		+ "with herbal essences.\n");
		say("Zayzee takes a pale green, cucumber paste poultice from the "
		+ "counter.  She begins caressing it into " + QCTNAME(facee) + "'s "
		+ "neck, slowly swirling her fingers in circles as she works her way "
		+ "up to " + HIS(facee) + " face.\nYou catch a hint of a bright, "
		+ "cucumber and herbal essence fragrance.\n");
		set_alarm(16.0, 0.0, "cucumber_paste6", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
cucumber_paste6(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee continues swirling the pale green poultice "
		+ "in small circles moving across your nose, up to your forehead, "
		+ "and rubs in slow, firm circles around your temples.  You feel "
		+ "your head buzzing from the bright, cucumber fragrance as you "
		+ "grow extremely relaxed.\nZayzee places a pair of paper thin "
		+ "cucumber slices over your eyes.\n");
		say("Zayzee continues swirling the pale green poultice in small "
		+ "circles moving across " + QCTNAME(facee) + "'s nose, up to "
		+ HIS(facee) + " forehead, and rubs in slow, firm circles around "
		+ HIS(facee) + " temples.  " + C(HE(facee)) + " appears extremely "
		+ "relaxed and is breathing slowly and deeply.\nZayzee places a "
		+ "pair of paper thin cucumber slices over " + HIS(facee)
		+ "eyes.\n");
		command("say There, you just lay back and relax while that dries.  "
		+ "Take as much time as you like.  When it has finished, you may "
		+ "call an attendant over at anytime to <finish facial>.");
		set_alarm(60.0, 0.0, "cucumber_paste7", facee);
		set_alarm(15.0, 0.0, "cucumber_enjoy", facee);
		set_alarm(30.0, 0.0, "cucumber_enjoy", facee);
		set_alarm(45.0, 0.0, "cucumber_enjoy", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
cucumber_paste7(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Your cucumber paste poultice has finished drying.  "
		+ "It tingles invigoratingly across your face and neck.  You could "
		+ "lay here all day in comfort.  When you are ready to have it "
		+ "removed, you may <finish facial>.\n");
		say(QCTNAME(facee) + "'s cucumber paste poultice has finished "
		+ "drying.\n");
		facee->add_prop(BSIT, 1); // 1 indicates cucumber paste
		alrm = 0;
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
cucumber_enjoy(object facee)
{
	string self = one_of_list(({"As pleasurable sensations tingle across "
	+ "your face, you feel yourself floating out of your chair.\nA stream "
	+ "of yellow butterflies flutters by.\nYour head is swimming.",
	  "The pale green poultice thickens as it continues to dry.  You feel "
	+ "impurities being drawn away as your head swims under the heady "
	+ "fragrance.\nA large, dancing, teddy bear leaves east.",
	  "Your skin throbs warmly under the pale green poultice, sending "
	+ "shivers of warmth down your spine and into your extremities.",
	  "Your neck feels pleasurably warm underneath the pale green "
	+ "poultice as it elongates enough for you to see the room from "
	+ "above.\nYour head swims buzzingly.",
	  "Through the paper thin cucumber slices over your eyes, you see the "
	+ "light from the silver braziers die out leaving a galaxy of stars "
	+ "swirling across the ceiling overhead.\nYour head feels dreamy.",
	  "You lift your arm to touch your pale green poultice, but it instead "
	+ "lifts you away on a sleepy flight through the fluffy clouds overhead.",
	  "Zayzee says: In the sky of yesteryear's dawn, we shed a tear for "
	+ "tomorrow's night for in that world, the blind man teaches the living "
	+ "his trade.",
	  "Your chair sinks slowly through the floor into another room where "
	+ "pleasurable sensations race across your skin.\nThe room looks just "
	+ "like the one above.",
	  "You think to yourself:  Mmmmmm.",
	  "You sigh to yourself as you wonder how you got by for so long without "
	+ "indulging yourself so pleasurably."}));

	string others = one_of_list(({"moans quietly as " + HE(facee)
	+ " squeezes " + HIS(facee) + " legs together.",
	  "says: Mmmmm.",
	  "mumbles something about pretty butterflies.",
	  "licks " + HIS(facee) + " lips slowly.",
	  "lifts one of " + HIS(facee) + " arms and snakes it searchingly "
	+ "through the air.",
	  "mumbles something about yesteryear's dawn, tomorrow's night, and a "
	+ "blind man.",
	  "says: My head feels so good.",
	  "sighs in utter relaxation.",
	  "sighs pleasurably.",
	  "breathes in and out slowly in a state of deep relaxation.",
	  "smiles in an extremely relaxed manner.",
	  "says: You have GOT to try this."}));

	facee->catch_msg(self + "\n");
	say(QCTNAME(facee) + " " + others + "\n");
}

void
seaweed_wrap(object facee)
{
	command("curtsey");
	command("introduce myself");
	command("say Alright, let's get started.");
	facee->catch_msg("Zayzee waddles around behind your chair, takes a jar "
	+ "of clear Gent-Oil from the counter station to your right, and rubs "
	+ "it into her fingers.\n");
	say("Zayzee waddles around behind " + QCTNAME(facee) + "'s chair, takes "
	+ "a jar of clear Gent-Oil from the counter station to " + HIS(facee)
	+ " right, and rubs it into her fingers.\n");
	set_alarm(8.5, 0.0, "seaweed_wrap2", facee);	
}

void
seaweed_wrap2(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee gently rubs the massage oil into your neck, "
		+ "immediately relaxing you, and warming your skin.\n");
		say("Zayzee gently rubs the massage oil into "
		+ QCTNAME(facee) + "'s neck eliciting a smile from " + HIM(facee)
		+ ".\n");
		set_alarm(10.5, 0.0, "seaweed_wrap3", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
seaweed_wrap3(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee rubs the massage oil slowly up your neck "
		+ "to your jaw, swirling it around your cheeks, then nose and "
		+ "forehead, pausing as she goes to gently massage your temples.\n"
		+ "The skin of your face flushes as a luxurious warmth spreads "
		+ "out across it.\n");
		say("Zayzee gently rubs the massage oil slowly up " + QCTNAME(facee)
		+ "'s neck to " + HIS(facee) + " jaw, swirling it around "
		+ HIS(facee) + " cheeks, then nose and forehead, pausing as she "
		+ "goes to gently massage " + HIS(facee) + " temples.  "
		+ C(HIS(facee)) + " face flushes as " + HE(facee) + " smiles in a "
		+ "very relaxed manner.\n");
		set_alarm(12.5, 0.0, "seaweed_wrap4", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
seaweed_wrap4(object facee)
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

		facee->catch_msg("Zayzee takes a small, white towel from the stack "
		+ "of towels on the counter, dips it into a jar of " + sjar
		+ "-scented water, and dabs softly at your face cleansing it.\n");
		say("Zayzee takes a small, white towel from the stack of towels "
		+ "on the counter, dips it into a jar of " + sjar + "-scented "
		+ "water, and dabs softly at " + QCTNAME(facee) + "'s face "
		+ "cleansing it.\n");
		set_alarm(11.5, 0.0, "seaweed_wrap5", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
seaweed_wrap5(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee takes a jar of moisture rich, white cream "
		+ "from the counter.  She begins caressing it into your neck, slowly "
		+ "swirling her fingers in circles as she works her way up to your "
		+ "face.  As she begins rubbing the rich, white cream into your "
		+ "cheeks your nose catches a hint of the clean, moisturizer cream "
		+ "blended with gentle herbal essences.\n");
		say("Zayzee takes a jar of moisture rich, white cream from the "
		+ "counter.  She begins caressing it into " + QCTNAME(facee) + "'s "
		+ "neck, slowly swirling her fingers in circles as she works her way "
		+ "up to " + HIS(facee) + " face.\n");
		set_alarm(16.0, 0.0, "seaweed_wrap6", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
seaweed_wrap6(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee continues swirling the rich, white cream "
		+ "in small circles moving across your nose, up to your forehead, "
		+ "and rubs in slow, firm circles around your temples.  You feel "
		+ "your skin growing enriched and moisturized as you become "
		+ "extremely relaxed.\nZayzee takes a bowl of wide, green seaweed "
		+ "from the cabinet below the counter.\n");
		say("Zayzee continues swirling the rich, white cream in small "
		+ "circles moving across " + QCTNAME(facee) + "'s nose, up to "
		+ HIS(facee) + " forehead, and rubs in slow, firm circles around "
		+ HIS(facee) + " temples.  " + C(HE(facee)) + " appears extremely "
		+ "relaxed and is breathing slowly and deeply.\nZayzee takes a "
		+ "bowl of wide, green seaweed from the cabinet below the "
		+ "counter.\n");
		set_alarm(17.0, 0.0, "seaweed_wrap7", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
seaweed_wrap7(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee takes wide leaves of thin, green seaweed "
		+ "from a bowl on the counter and begins wrapping your neck and "
		+ "face with it, placing it carefully upon your cheeks, nose, "
		+ "then forehead.  You feel a tingling cool break out upon your "
		+ "skin as the seaweed interacts with the rich, white moisturizer "
		+ "cream turning it bright green.\n");
		say("Zayzee takes wides wide leaves of thin, green seaweed from a "
		+ "bowl on the counter and begins wrapping " + QCTNAME(facee)
		+ "'s neck and face with it, placing it carefully upon " + HIS(facee)
		+ " cheeks, nose, then forehead.  As the seaweed interacts with the "
		+ "rich, white moisturizer, the cream turns a bright green.\n");
		command("say There, you just lay back and relax while that soaks "
		+ "in.  Take as much time as you like.  When it has finished, you "
		+ "may call an attendant over at anytime to <finish facial>.");
		set_alarm(60.0, 0.0, "seaweed_wrap8", facee);
		set_alarm(15.0, 0.0, "seaweed_enjoy", facee);
		set_alarm(30.0, 0.0, "seaweed_enjoy", facee);
		set_alarm(45.0, 0.0, "seaweed_enjoy", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
seaweed_wrap8(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Your seaweed wrap has finished soaking in.  "
		+ "It tingles cool and fresh across your face and neck.  You could "
		+ "lay here all day in comfort.  When you are ready to have it "
		+ "removed, you may <finish facial>.\n");
		say(QCTNAME(facee) + "'s bright green seaweed wrap has finished "
		+ "soaking in.\n");
		facee->add_prop(BSIT, 2); // 2 indicates seaweed wrap
		alrm = 0;
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
seaweed_enjoy(object facee)
{
	string self = one_of_list(({"As cool sensations tingle across your "
	+ "face and neck, you feel as if you're floating at the bow of a swift "
	+ "sailing ship.\nYour skin feels refreshed.",
	  "The bright green seaweed wrap thickens a bit as its rich moisturizers "
	+ "seep into your skin.\nYour face and neck feel refreshed.",
	  "Your skin tingles coolly under the bright green seaweed wrap, sending "
	+ "pleasurable shivers down your spine and into your extremities.",
	  "Through the thin green seaweed hanging over your eyes, you think "
	+ "you see a light snow start to fall, or at least your tingling skin "
	+ "feels like tiny snowflakes are touching down gently upon it.\n"
	+ "Your skin feels cool and dreamy.",
	  "You drift away in deep relaxation feeling as if a flurried snowfall "
	+ "is parting before you leaving a path to silvery lights flickering "
	+ "nearby.",
	  "You can't recall the last time you felt so good as you squirm "
	+ "comfortably in your reclined pale leather chair and sigh deeply.",
	  "You think to yourself:  Mmmmmm.",
	  "You sigh to yourself as you wonder how you got by for so long without "
	+ "indulging yourself so pleasurably."}));

	string others = one_of_list(({"sighs quietly as " + HE(facee)
	+ " squeezes " + HIS(facee) + " arms around " + HIS(facee) + " body.",
	  "says: Mmmmm.",
	  "squirms comfortably in " + HIS(facee) + " pale leather chair and "
	+ "sighs deeply.",
	  "licks " + HIS(facee) + " lips slowly.",
	  "smiles and sighs deeply.",
	  "says: My head feels so good.",
	  "sighs in utter relaxation.",
	  "sighs pleasurably.",
	  "breathes in and out slowly in a state of deep relaxation.",
	  "smiles in an extremely relaxed manner.",
	  "says: You have GOT to try this."}));

	facee->catch_msg(self + "\n");
	say(QCTNAME(facee) + " " + others + "\n");
}

void
apricot_scrub(object facee)
{
	command("curtsey");
	command("introduce myself");
	command("say Alright, let's get started.");
	facee->catch_msg("Zayzee waddles around behind your chair, takes a jar "
	+ "of clear Gent-Oil from the counter station to your right, and rubs "
	+ "it into her fingers.\n");
	say("Zayzee waddles around behind " + QCTNAME(facee) + "'s chair, takes "
	+ "a jar of clear Gent-Oil from the counter station to " + HIS(facee)
	+ " right, and rubs it into her fingers.\n");
	set_alarm(8.5, 0.0, "apricot_scrub2", facee);	
}

void
apricot_scrub2(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee gently rubs the massage oil into your neck, "
		+ "immediately relaxing you, and warming your skin.\n");
		say("Zayzee gently rubs the massage oil into "
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
		facee->catch_msg("Zayzee rubs the massage oil slowly up your neck "
		+ "to your jaw, swirling it around your cheeks, then nose and "
		+ "forehead, pausing as she goes to gently massage your temples.\n"
		+ "The skin of your face flushes as a luxurious warmth spreads "
		+ "out across it.\n");
		say("Zayzee gently rubs the massage oil slowly up " + QCTNAME(facee)
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

		facee->catch_msg("Zayzee takes a small, white towel from the stack "
		+ "of towels on the counter, dips it into a jar of " + sjar
		+ "-scented water, and dabs softly at your face cleansing it.\n");
		say("Zayzee takes a small, white towel from the stack of towels "
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
		facee->catch_msg("Zayzee takes a jar of thick, brown-speckled "
		+ "apricot scrub from the counter.  She begins caressing it into "
		+ "your neck, slowly swirling her fingers in circles as she works "
		+ "her way up to your face.  As she begins rubbing the thick, "
		+ "apricot coloured cream into your cheeks you feel an ultra-fine "
		+ "grainy abrasive gently scrubbing away the dry, dead outer layer "
		+ "of your skin.\n");
		say("Zayzee takes a jar of thick, brown-speckled apricot scrub from "
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
		facee->catch_msg("Zayzee continues swirling the thick, apricot- "
		+ "coloured scrub in small circles moving across your nose, up to "
		+ "your forehead, and rubs in slow, firm circles around your "
		+ "temples.  Your skin feels as if it is being set free from an old, "
		+ "dry prison and immersed in apricot rich moisturizer as you become "
		+ "extremely relaxed.\nYour neck and face throb pleasurably with the "
		+ "sensation.\n");
		say("Zayzee continues swirling the thick, apricot-coloured scrub in "
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
		facee->catch_msg("Zayzee folds out a fan from the counter and waves "
		+ "it over your face.  You feel the apricot scrub thicken into a "
		+ "gel which she peels from your face and neck in one rubbery "
		+ "piece leaving the fresh skin beneath it feeling exceptionally "
		+ "fresh and free.\n");
		say("Zayzee folds out a fan from the counter and waves it over "
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
		facee->catch_msg("Zayzee takes a jar of apricot finishing cream "
		+ "from the counter and applies a quantity to your neck and "
		+ "cheeks.  She then begins gently caressing it into your neck, "
		+ "chin, cheeks, nose, and forehead in small, swirling circles "
		+ "before massaging your temples luxuriously.\n");
		say("Zayzee takes a jar of apricot finishing cream from the counter "
		+ " and applies a quantity to " + QCTNAME(facee) + "'s neck and "
		+ "cheeks.  She then begins gently caressing it into " + HIS(facee)
		+ " neck, chin, cheeks, nose, and forehead in small, swirling "
		+ "circles befoer massaging " + HIS(facee) + " temples "
		+ "luxuriously.\n");
		command("say There, you just lay back and relax while that does "
		+ "its thing.  Take as much time as you like.  When it has finished, "
		+ "you may call an attendant over at anytime to <finish facial>.");
		set_alarm(60.0, 0.0, "apricot_scrub9", facee);
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
	+ "comfortably in your reclined pale leather chair and sigh deeply.",
	  "You think to yourself:  Mmmmmm.",
	  "You sigh to yourself as you wonder how you got by for so long without "
	+ "indulging yourself so pleasurably."}));

	string others = one_of_list(({"sighs quietly as " + HE(facee)
	+ " squeezes " + HIS(facee) + " arms around " + HIS(facee) + " body.",
	  "says: Mmmmm.",
	  "squirms comfortably in " + HIS(facee) + " pale leather chair and "
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
morgul_fire(object facee)
{
	command("curtsey");
	command("introduce myself");
	command("say Alright, let's get started.");
	facee->catch_msg("Zayzee waddles around behind your chair, takes a jar "
	+ "of clear Gent-Oil from the counter station to your right, and rubs "
	+ "it into her fingers.\n");
	say("Zayzee waddles around behind " + QCTNAME(facee) + "'s chair, takes "
	+ "a jar of clear Gent-Oil from the counter station to " + HIS(facee)
	+ " right, and rubs it into her fingers.\n");
	set_alarm(8.5, 0.0, "morgul_fire2", facee);	
}

void
morgul_fire2(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee gently rubs the massage oil into your neck, "
		+ "immediately relaxing you, and warming your skin.\n");
		say("Zayzee gently rubs the massage oil into "
		+ QCTNAME(facee) + "'s neck eliciting an icy smile from " + HIM(facee)
		+ ".\n");
		set_alarm(10.5, 0.0, "morgul_fire3", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_fire3(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee rubs the massage oil slowly up your neck "
		+ "to your jaw, swirling it around your cheeks, then nose and "
		+ "forehead, pausing as she goes to gently massage your temples.\n"
		+ "The skin of your face flushes as a luxurious warmth spreads "
		+ "out across it.\n");
		say("Zayzee gently rubs the massage oil slowly up " + QCTNAME(facee)
		+ "'s neck to " + HIS(facee) + " jaw, swirling it around "
		+ HIS(facee) + " cheeks, then nose and forehead, pausing as she "
		+ "goes to gently massage " + HIS(facee) + " temples.  "
		+ C(HIS(facee)) + " face flushes as " + HE(facee) + " smiles in a "
		+ "powerfully relaxed manner.\n");
		set_alarm(12.5, 0.0, "morgul_fire4", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_fire4(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee takes a small, white towel from the stack "
		+ "of towels on the counter, dips it into a jar of Ithilduin"
		+ "-scented water, and dabs softly at your face cleansing it.\n");
		say("Zayzee takes a small, white towel from the stack of towels "
		+ "on the counter, dips it into a jar of Ithilduin-scented "
		+ "water, and dabs softly at " + QCTNAME(facee) + "'s face "
		+ "cleansing it.\n");
		set_alarm(11.5, 0.0, "morgul_fire5", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_fire5(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee slips on a pair of shiny gloves and takes "
		+ "a small cauldron of thick, pasty, red hot, smouldering embers "
		+ "from beneath the counter.  She begins caressing it into "
		+ "your neck, slowly swirling her fingers in circles as she works "
		+ "her way up to your face.  As she begins rubbing the thick, "
		+ "smouldering paste into your cheeks you feel the heat of a "
		+ "thousand furnaces erupting beneath your skin.\n");
		say("Zayzee slips on a pair of shiny gloves and takes a small "
		+ "cauldron of thick, pasty, red hot, smouldering embers from "
		+ "beneath the counter.  She begins caressing it into "
		+ QCTNAME(facee) + "'s neck, slowly swirling her fingers in "
		+ "circles as she works her way up to " + HIS(facee) + " face.\n");
		set_alarm(16.0, 0.0, "morgul_fire6", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_fire6(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee continues swirling the thick, pasty, red "
		+ "hot, smouldering embers in small circles moving across your nose, "
		+ "up to your forehead, and rubs in slow, firm circles around your "
		+ "temples.  Your skin feels as if it is being set free from an old, "
		+ "dry prison and ignited in the flames of Orodruin.\nYour neck and "
		+ "face throb powerfully with the sensation.\n");
		say("Zayzee continues swirling the thick, pasty, red hot, smouldering "
		+ "embers in small circles moving across " + QCTNAME(facee) + "'s "
		+ "nose, up to " + HIS(facee) + " forehead, and rubs in slow, firm "
		+ "circles around " + HIS(facee) + " temples.  " + C(HE(facee))
		+ " appears extremely relaxed and is breathing slowly and deeply "
		+ "with wisps of smoke pouring from " + HIS(facee) + " nostrils.\n");
		set_alarm(17.0, 0.0, "morgul_fire7", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_fire7(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee folds out a fan from the counter and waves "
		+ "it over your face.  The embers beneath your skin ignite and "
		+ "smoulder wreathing your face in a veil of roiling smoke.\n");
		say("Zayzee folds out a fan from the counter and waves it over "
		+ QCTNAME(facee) + "'s face igniting the embers beneath "
		+ HIS(facee) + " skin and wreathing " + HIS(facee) + " in a veil of "
		+ "roiling smoke.\n");
		set_alarm(18.5, 0.0, "morgul_fire8", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_fire8(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee drops her shiny gloves into the trash and "
		+ "backs away from the heat rising from your face as she wipes the "
		+ "sweat from her forehead.\n");
		say("Zayzee drops her shiny gloves into the trash and backs away "
		+ "from the heat rising from " + QCTNAME(facee) + "'s face as she "
		+ "wipes the sweat from her forehead.\n");
		command("say There, you just lay back and relax while that does "
		+ "its thing.  Take as much time as you like.  When it has finished, "
		+ "you may call an attendant over at anytime to <finish facial>.");
		set_alarm(60.0, 0.0, "morgul_fire9", facee);
		set_alarm(15.0, 0.0, "morgul_enjoy_fire", facee);
		set_alarm(30.0, 0.0, "morgul_enjoy_fire", facee);
		set_alarm(45.0, 0.0, "morgul_enjoy_fire", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_fire9(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("The embers smouldering beneath your skin have "
		+ "risen to a blazing glow.  The smell of sulfur is strong.  You "
		+ "could lay here all day in comfort.  When you are ready to have "
		+ "it completed, you may <finish facial>.\n");
		say(QCTNAME(facee) + "'s smouldering facial embers have risen to "
		+ "a blazing glow.\n");
		facee->add_prop(BSIT, 4); // 4 indicates morgul fire
		alrm = 0;
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_enjoy_fire(object facee)
{
	string self = one_of_list(({"As incendiary sensations spark across "
	+ "your face and neck, you feel as if you're floating across a vale of "
	+ "morgurth and angurth plants.\nYour skin throbs with dark energy.",
	  "The smouldering ember paste swirls and churns deep beneath your "
	+ "skin.\nYour face and neck heat rapidly.",
	  "Your skin crackles under the heat of the smouldering ember paste "
	+ "sending pleasurable jolts of fiery energy down your spine and into "
	+ "your extremities.",
	  "Your skin begins to burn with a blazing red glow.",
	  "You drift away in deep relaxation feeling as if the fires of Orodruin "
	+ "far below erupted at your bidding.",
	  "You can't recall the last time you felt so good as you squirm "
	+ "comfortably in your reclined pale leather chair and sigh deeply.",
	  "You think to yourself:  Mmmmmm.",
	  "You sigh to yourself as you wonder how you got by for so long without "
	+ "indulging yourself so pleasurably."}));

	string others = one_of_list(({"rasps quietly as " + HE(facee)
	+ " raises " + HIS(facee) + " arms above " + HIS(facee) + " body in "
	+ "exultation.",
	  "hisses: Yesssss.",
	  "squirms comfortably in " + HIS(facee) + " pale leather chair as "
	+ HE(facee) + " moves mysteriously beneath the folds of " + HIS(facee)
	+ "black hooded robe.",
	  "licks " + HIS(facee) + " lips dastardly.",
	  "smiles coldly and sighs deeply.",
	  "hisses: Ahhhh, morgurth...",
	  "sighs in utter relaxation.",
	  "sighs pleasurably.",
	  "breathes in and out slowly in a state of deep relaxation as wisps of "
	+ "smoke pour from " + HIS(facee) + " nostrils.",
	  "smiles in an extremely relaxed manner.",
	  "hisses: The flames will purge from you all untruths."}));

	facee->catch_msg(self + "\n");
	say(QCTNAME(facee) + " " + others + "\n");
}

void
morgul_shadow(object facee)
{
	command("curtsey");
	command("introduce myself");
	command("say Alright, let's get started.");
	facee->catch_msg("Zayzee waddles around behind your chair, takes a jar "
	+ "of swirling, greyish Gent-Oil from the counter station to your right, "
	+ "and rubs it into her fingers.\n");
	say("Zayzee waddles around behind " + QCTNAME(facee) + "'s chair, takes "
	+ "a jar of swirling, greyish Gent-Oil from the counter station to "
	+ HIS(facee) + " right, and rubs it into her fingers.\n");
	set_alarm(8.5, 0.0, "morgul_shadow2", facee);	
}

void
morgul_shadow2(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee gently rubs the massage oil into your neck, "
		+ "immediately relaxing you, and cooling your skin.\n");
		say("Zayzee gently rubs the massage oil into "
		+ QCTNAME(facee) + "'s neck eliciting a dark smile from " + HIM(facee)
		+ ".\n");
		set_alarm(10.5, 0.0, "morgul_shadow3", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_shadow3(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee rubs the massage oil slowly up your neck "
		+ "to your jaw, swirling it around your cheeks, then nose and "
		+ "forehead, pausing as she goes to gently massage your temples.\n"
		+ "The skin of your face flushes as a prickly iciness spreads "
		+ "out across it.\n");
		say("Zayzee gently rubs the massage oil slowly up " + QCTNAME(facee)
		+ "'s neck to " + HIS(facee) + " jaw, swirling it around "
		+ HIS(facee) + " cheeks, then nose and forehead, pausing as she "
		+ "goes to gently massage " + HIS(facee) + " temples.  "
		+ C(HIS(facee)) + " face darkens as " + HE(facee) + " smiles in a "
		+ "powerfully relaxed manner.\n");
		set_alarm(12.5, 0.0, "morgul_shadow4", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_shadow4(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee takes a small, black towel from the stack "
		+ "of towels on the counter, dips it into a jar of Ithilduin"
		+ "-scented water, and dabs softly at your face cleansing it.\n");
		say("Zayzee takes a small, black towel from the stack of towels "
		+ "on the counter, dips it into a jar of Ithilduin-scented "
		+ "water, and dabs softly at " + QCTNAME(facee) + "'s face "
		+ "cleansing it.\n");
		set_alarm(11.5, 0.0, "morgul_shadow5", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_shadow5(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee takes a wide, clay philter from the "
		+ "counter and dips her thumb and forefinger inside.  Taking a "
		+ "pinch of the sparkling, grey-black powder within, she sprinkles "
		+ "it over your face awakening your sight into the Shadows.  As she "
		+ "begins to rub the powder into your cheeks, tendrils of shadow "
		+ "slowly protrude from your face sending a reassuring chill through "
		+ "your bones.\n");
		say("Zayzee takes a wide, clay philter from the counter and dips her "
		+ "thumb and forefinger inside.  Taking a pinch of the sparkling, "
		+ "grey-black powder within, she sprinkles it over " + QCTNAME(facee)
		+ "'s face.  As she begins to rub the powder into " + HIS(facee)
		+ " cheeks, tendrils of shadow slowly protrude from " + HIS(facee)
		+ " probing their environment.\n");
		set_alarm(16.0, 0.0, "morgul_shadow6", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_shadow6(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee takes another pinch of sparkling, grey-"
		+ "black powder from the wide, clay philter and sprinkles it over "
		+ "your face.\nSuddenly it seems as if all light has been sucked "
		+ "from the room, and for an instant a great, flaming red eye "
		+ "flashed into sight above you with a thunderous roar.\n");
		say("Zayzee takes another pinch of sparkling, grey-black powder from "
		+ "the wide, clay philter and sprinkles it over " + QCTNAME(facee)
		+ "'s face.  The waving tendrils of shadow reaching from "
		+ HIS(facee) + " face grow longer seemingly to catch the powder.\n"
		+ "For an instant you got the sense the room darkened, but it was "
		+ "probably just you blinking... and was that a flash of red upon "
		+ "the ceiling?\n");
		set_alarm(17.0, 0.0, "morgul_shadow7", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_shadow7(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee jumps back in surprise as one of the large "
		+ "tendrils of shadow over your face reaches out suddenly for her.\n"
		+ "She wraps her arms around her body for warmth as she manages a "
		+ "forced, pleasant smile.\n");
		say("Zayzee jumps back in surprise as one of the large tendrils of "
		+ "shadow over " + QCTNAME(facee) + "'s face reaches out suddenly "
		+ "for her.\nShe wraps her arms around her body for warmth as she "
		+ "manages a forced, pleasant smile.\n");
		set_alarm(18.5, 0.0, "morgul_shadow8", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_shadow8(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("Zayzee rubs her arms for warmth as she gazes with "
		+ "concern at the grasping tendrils of shadow rising from your "
		+ "face.\n");
		say("Zayzee rubs her arms for warmth as she gazes with concern at "
		+ "the grasping tendrils of shadow rising from " + QCTNAME(facee)
		+ "'s face.\n");
		command("say There, you just lay back and relax while that does "
		+ "its thing.  Take as much time as you like.  When it has finished, "
		+ "you may call an attendant over at anytime to <finish facial>.");
		set_alarm(60.0, 0.0, "morgul_shadow9", facee);
		set_alarm(15.0, 0.0, "morgul_enjoy_shadow", facee);
		set_alarm(30.0, 0.0, "morgul_enjoy_shadow", facee);
		set_alarm(45.0, 0.0, "morgul_enjoy_shadow", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_shadow9(object facee)
{
	if (facee->query_prop(FSIT))
	{
		facee->catch_msg("The waving tendrils of shadow veiling your face "
		+ "have extended to their full length.  Chills from their darkness "
		+ "ripple across your skin.  You could lay here all day in comfort.  "
		+ "When you are ready to have it completed, you may <finish facial>"
		+ ".\n");
		say(QCTNAME(facee) + "'s waving tendrils of shadow veiling "
		+ HIS(facee) + " face have extended to their full length.\nThere is "
		+ "a chill in the air.\n");
		facee->add_prop(BSIT, 5); // 5 indicates morgul shadow
		alrm = 0;
		return;
	}
	set_alarm(0.5, 0.0, "ruin_facial", facee);
}

void
morgul_enjoy_shadow(object facee)
{
	string self = one_of_list(({"As shadowy chills crackle across "
	+ "your face and neck, you feel as if you're drifting in and out of "
	+ "the realm of shadows.\nYour skin throbs with frigid energy.",
	  "The sparkling grey-black powder phases in and out amidst lengthening "
	+ "tendrils of shadow growing from your skin.\nYour face and neck chill "
	+ "rapidly.",
	  "Waves of frigid cold ripple across your skin from the sparkling, "
	+ "grey-black powder sending pleasurable jolts of shadowy energy down "
	+ "your spine and into your extremities.",
	  "Your skin begins to tingle as if protective shadows enveloped it.",
	  "You drift away in deep relaxation feeling as if tendrils from the "
	+ "Shadows lifted you away to their plane.",
	  "You can't recall the last time you felt so good as you squirm "
	+ "comfortably in your reclined pale leather chair and sigh deeply.",
	  "You think to yourself:  Mmmmmm.",
	  "You sigh to yourself as you wonder how you got by for so long without "
	+ "indulging yourself so pleasurably."}));

	string others = one_of_list(({"rasps quietly as " + HE(facee)
	+ " raises " + HIS(facee) + " arms above " + HIS(facee) + " body in "
	+ "exultation.",
	  "hisses: Yesssss.",
	  "squirms comfortably in " + HIS(facee) + " pale leather chair as "
	+ HE(facee) + " moves mysteriously beneath the folds of " + HIS(facee)
	+ "black hooded robe.",
	  "licks " + HIS(facee) + " lips dastardly.",
	  "smiles coldly and sighs darkly.",
	  "hisses: Ahhhh, Shadows guide me...",
	  "sighs in utter relaxation.",
	  "sighs pleasurably.",
	  "breathes in and out slowly in a state of deep relaxation as tendrils "
	+ "of shadow wave graspingly from " + HIS(facee) + " face.",
	  "smiles in an extremely relaxed manner.",
	  "hisses: The Shadows will set right that which is amiss."}));

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

int
finish_facial(string str)
{
	object facial;

	if (TP->query_prop(BSIT))
	{
		NF("Finish what?  Your facial?\n");
		if (!str || str != "facial")
			return 0;

		if (TP->query_prop(BSIT) == 1) // 1 indicates cucumber paste
		{
			TP->catch_msg("You wave your hand signaling to the attendant "
			+ "that you are finished with your cucumber paste facial.\n"
			+ "A white-coated attendant walks behind your chair and "
			+ "with gentle care peels the pale green poultice from your "
			+ "neck and face leaving your skin feeling unbelievably "
			+ "smooth, fresh, and positively glowing!  You feel young "
			+ "and vibrant and more awake than you've been in ages!\n");
			say(QCTNAME(TP) + " waves " + HIS(TP) + " hand signaling to an "
			+ "attendant that " + HE(TP) + " is finished with " + HIS(TP)
			+ " cucumber paste facial.\nA white-coated attendant walks "
			+ "behind " + HIS(TP) + " chair and with gentle care peels "
			+ "a pale green poultice from " + HIS(TP) + " neck and face "
			+ "leaving " + HIS(TP) + " skin looking unbelievably smooth, "
			+ "fresh, and positively glowing!\n");
			facial = clone_object(NOBLE + "obj/facial_cucumber");
			facial->move(TP);
			TP->remove_prop(BSIT);
			TP->add_prop(HAD_FACIAL, 1);
			return 1;
		}

		if (TP->query_prop(BSIT) == 2) // 2 indicates seaweed wrap
		{
			TP->catch_msg("You wave your hand signaling to the attendant "
			+ "that you are finished with your seaweed wrap facial.\n"
			+ "A white-coated attendant walks behind your chair and "
			+ "with gentle care peels the bright green seaweed wrap from "
			+ "your neck and face leaving your skin feeling unbelievably "
			+ "cool, moisturized, and positively glowing!  You feel young "
			+ "and refreshed and more sensuous than you've felt in ages!\n");
			say(QCTNAME(TP) + " waves " + HIS(TP) + " hand signaling to an "
			+ "attendant that " + HE(TP) + " is finished with " + HIS(TP)
			+ " seaweed wrap facial.\nA white-coated attendant walks "
			+ "behind " + HIS(TP) + " chair and with gentle care peels "
			+ "a bright green seaweed wrap from " + HIS(TP) + " neck and "
			+ "face leaving " + HIS(TP) + " skin looking unbelievably "
			+ "cool, moisturized, and positively glowing!\n");
			facial = clone_object(NOBLE + "obj/facial_seaweed");
			facial->move(TP);
			TP->remove_prop(BSIT);
			TP->add_prop(HAD_FACIAL, 2);
			return 1;
		}

		if (TP->query_prop(BSIT) == 3) // 3 indicates apricot scrub
		{
			TP->catch_msg("You wave your hand signaling to the attendant "
			+ "that you are finished with your apricot scrub facial.\n"
			+ "A white-coated attendant walks behind your chair and "
			+ "uses a moist towel to gently remove the remaining apricot "
			+ "finishing cream from your neck and face leaving your skin "
			+ "feeling unbelievably soft, fresh, and positively glowing!  "
			+ "You feel young and refreshed and more free than you've felt "
			+ "in ages!\n");
			say(QCTNAME(TP) + " waves " + HIS(TP) + " hand signaling to an "
			+ "attendant that " + HE(TP) + " is finished with " + HIS(TP)
			+ " apricot scrub facial.\nA white-coated attendant walks "
			+ "behind " + HIS(TP) + " chair and with a moist towel gently "
			+ "removes the remaining apricot finishing cream from " + HIS(TP)
			+ " neck and face leaving " + HIS(TP) + " skin looking "
			+ "unbelievably soft, fresh, and positively glowing!\n");
			facial = clone_object(NOBLE + "obj/facial_apricot");
			facial->move(TP);
			TP->remove_prop(BSIT);
			TP->add_prop(HAD_FACIAL, 3);
			return 1;
		}

		if (TP->query_prop(BSIT) == 4) // 4 indicates morgul fire
		{
			TP->catch_msg("You wave your hand signaling to the attendant "
			+ "that you are finished with your morgul fire facial.\n"
			+ "A white-coated attendant walks behind your chair and "
			+ "contemplates using a moist towel to wipe your face before "
			+ "using it to fan some of the smoke from your neck and face "
			+ "leaving your skin a smouldering landscape of embers that is "
			+ "positively glowing!  "
			+ "You feel stronger, refreshed, and more energized than you've "
			+ "felt in ages!\n");
			say(QCTNAME(TP) + " waves " + HIS(TP) + " hand signaling to an "
			+ "attendant that " + HE(TP) + " is finished with " + HIS(TP)
			+ " morgul fire facial.\nA white-coated attendant walks "
			+ "behind " + HIS(TP) + " chair and with a moist towel gently "
			+ "fans some of the smoke from " + HIS(TP)
			+ " neck and face leaving " + HIS(TP) + " skin a smouldering "
			+ "landscape of embers that is positively glowing!\n");
			facial = clone_object(NOBLE + "obj/facial_morgul_fire");
			facial->move(TP);
			TP->remove_prop(BSIT);
			TP->add_prop(HAD_FACIAL, 4);
			return 1;
		}

		if (TP->query_prop(BSIT) == 5) // 5 indicates morgul shadow
		{
			TP->catch_msg("You wave your hand signaling to the attendant "
			+ "that you are finished with your morgul fire facial.\n"
			+ "A white-coated attendant walks behind your chair and "
			+ "contemplates using a moist towel to wipe your face before "
			+ "it is ripped from his hand by the tendrils of shadow before "
			+ "your face and shredded to nothingness!\n"
			+ "You feel colder and hard like stone, more empowered than "
			+ "you've felt in ages!\n");
			say(QCTNAME(TP) + " waves " + HIS(TP) + " hand signaling to an "
			+ "attendant that " + HE(TP) + " is finished with " + HIS(TP)
			+ " morgul fire facial.\nA white-coated attendant walks "
			+ "behind " + HIS(TP) + " chair with a moist towel with which "
			+ "to dab at " + QTNAME(TP) + "'s face when one of the large, "
			+ "shadowy tendrils growing from " + HIS(TP) + " face snatches "
			+ "the towel from his grasp and shreds it to nothingness!\n"
			+ QCTNAME(TP) + " appears empowered with an icy cold known only "
			+ "by the stones of the furthest northern reaches.\n");
			facial = clone_object(NOBLE + "obj/facial_morgul_shadow");
			facial->move(TP);
			TP->remove_prop(BSIT);
			TP->add_prop(HAD_FACIAL, 5);
			return 1;
		}
	}
	write("What?\n");
	return 1;
}
