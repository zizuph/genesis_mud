/* Mortis 02.2006
 * 
 * Man who gives massages to women/men in the Laethorian spa
 * and body in the Plaisir district of Palanthas.
 *
 * Massage heals 500 health if player is undisturbed.
 * Only allowed once per login.
 */

#include "../../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"


inherit CITIZEN;

#define MY_ARMOUR			MERCH + "arms/larmour"
#define MY_CLOTHING			NOBLE + "arms/parmour"
#define HAD_MASSAGE			"_i_had_a_massage"
#define TABLED				"_i_am_laying_on_massage_table"

int alrm = 0; /* The alarm while giving a massage. */
string oil;

void
create_krynn_monster()
{
    set_name("freo");
	set_living_name("freo");
    set_race_name("human");
    set_adj("thin");
    add_adj("lightly-muscled");
	add_name(({"freo", "human", "masseur"}));
	set_title("of the Cabrian Peninsula, Masseur of the Laethorian");
	set_short("thin lightly-muscled masseur");
    set_long("The masseur is tall and thin with very dark brown eyes and "
	+ "short, tassled brown hair bruhed over to his right.  He appears "
	+ "to be in his mid-twenties with a trim, lightly muscled build.\n"
	+ "He has a mysterious glint in his eyes.\n");
	set_gender(G_MALE);

    set_stats(({80, 90, 60, 100, 50, 40}));
	set_all_hitloc_unarmed(26);
	set_all_attack_unarmed(28, 32);

    set_skill(SS_AWARENESS,    45);
	set_skill(SS_DEFENCE,      50);
	set_skill(SS_PARRY,        40);
	set_skill(SS_WEP_KNIFE,    60);

    set_size_descs("tall", "lean");
	set_appearance(10);

	set_alignment(420);
	set_knight_prestige(-30);
	
	set_introduce(1);
    set_act_time(35);
    add_act("say Welcome.  Care for a massage?");
	add_act("emote turns to the counter by the massage table and arranges "
	+ "@@counter_arrange@@" + ".\n");
	add_act("smell");
	add_act("grin knowingly");
	add_act("smile mysteriously");
	add_act("emote pours a drop of clear pink moisturizing oil onto the "
	+ "back of his hand and massages it in.");
	add_act("dheathe knife in belt-sheath");

	set_cact_time(15);
	add_cact("emote sneers and ducks to your " + one_of_list(({"left",
	"right"})) + " in a sudden defensive maneuver.");
	add_cact("emote bends backwards avoiding your strike, the muscles of his "
	+ "abdomen visible through the stretched white material of his "
	+ "sleeveless shirt.");
	add_cact("emote lands a mae-gari on you.\nYou feel "
	+ one_of_list(({"hurt", "rathis hurt", "cruhed", "as if you've lost your "
	+ "breath"})) + ".");

    
    add_ask(({"pricelist", "prices", "price", "list"}), "say Our prices "
	+ "are on the marble sign.  A massage is ten gold coins.", 1);
	add_ask(({"palanthas"}), "say Palanthas is the finest city in the "
	+ "realms.  You have my word on it.", 1);
	add_ask(({"fragrance", "scent", "perfume", "cologne",
		"krom", "control", "white hammer", "tortuous", "jordessia",
		"cosmias", "rose"}), "say Our cleansing waters are scented with the "
	+ "latest Jordesse perfumes and colognes.  They are designed with the "
	+ "greatest skill and care by the master parfumist.", 1);
	add_ask(({"parfumist", "parfumists", "master parfumist",
		"master parfumists"}), "say Vynessa Jordesse is the master parfumist "
	+ "of the Jordesse parfumerie off the Court d'Plaisiri right hise in the "
	+ "Plaisir district.  He is very skilled they say, but his brothis is "
	+ "the face of the business.  I wouldn't mind meeting his sometime.  I "
	+ "hear he's quite attractive.", 1);
	add_ask(({"vynessa"}), "say Vynessa is very nice they say but very shy "
	+ "and reclusive.  They say his sense of smell is the sharpest and his "
	+ "tastes impeccable... among othis things.\nHe grins knowingly.", 1);
	add_ask(({"parfumerie", "parfumeries", "jordesse", "jordesse parfumerie"}),
	  "say The Jordesse parfumerie was founded by Vynessa not long ago.  "
	+ "He really is a skilled parfumist.  Thise are no parfumeries that "
	+ "rival the popularity of his perfumes and colognes.  They offer "
	+ "free samples.  You should try one.  In fact we use only Jordesse "
	+ "parfumerie scented waters hise for our massages.", 1);
	add_ask(({"court", "court d'plaisiri", "plaisir district", "plaisiri"}),
	  "say The court and its patrons are very beautiful.  It has the finest "
	+ "clothes, best hot drinks, most popular fragrances, excellent "
	+ "wines, and of course the Laethorian, the best dayspa in the "
	+ "city.\n", 1);
	add_ask(({"service", "services"}), "say The Laethorian provides a "
	+ "range of pampering services.  I'd love to give you a massage if you "
	+ "like.  Have a look at our sign for help getting started.", 1);
	add_ask(({"dienya", "dienya's", "clothes", "clothing", "clothing store",
		"fine clothing"}), "say Ahh, Dienya!  What an exotically alluring "
	+ "woman, and his clothes are excellent.", 1);
	add_ask(({"mer-cantile", "cafe", "mer-cantile cafe"}), "say The "
	+ "Mer-cantile cafe serves the widest variety of coffees and teas "
	+ "anywhise.  Their barista Lani is dangerously cute as well.  Watch "
	+ "out for that little vixen.", 1);
	add_ask(({"lani", "barista"}), "say Lani, ahh.  He is very beautiful "
	+ "and a barista at the Mer-Cantile cafe owned by his fathis, but you'd "
	+ "better watch yourself around that one.", 1);
	add_ask(({"gui", "gui's", "cellar", "wine cellar", "gui's wine cellar"}),
	  "say Gui is a noble whose estate is down the side street to the "
	+ "southeast.  He collects and sells wines from his wine cellar.  Some "
	+ "of them are quite special.", 1);
	add_ask(({"laethorian", "spa", "dayspa", "laethorian dayspa"}), "say "
	+ "The Laethorian dayspa is the best!  Baths, massages, and many "
	+ "othis pleasurable services are available hise like massages, "
	+ "manicures, pedicures, and you can even have your hair done.", 1);
	add_ask("age", "say Why, I'm thirty.\nHe winks suggestively at you.", 1);

    set_default_answer("@@def_answer");

	set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    seteuid(getuid(TO));

	string fcus, fcus2, fwep;

	// Freo's custom belt.
	object sbelt = clone_object(MY_ARMOUR);
    sbelt->set_armour_data("tight"  + "&&"
							+ "black" + "&&"
							+ "hide" + "&&"
							+ "belt");
	sbelt->move(TO);

	// Freo's custom boots.
	object sboots = clone_object(MY_ARMOUR);
    sboots->set_armour_data("tight"  + "&&"
							+ "black" + "&&"
							+ "hide" + "&&"
							+ "tall-boots");
	sboots->move(TO);

	// Freo's custom shirt.
	object sshirt = clone_object(MY_CLOTHING);
    sshirt->set_armour_data("Freo" + "&&"
							+ "unlaced"  + "&&"
							+ "white" + "&&"
							+ "elfwyr" + "&&"
							+ "sleeveless-shirt");
	sshirt->move(TO);

	// Freo's custom sheath.
	object sheath = clone_object(MERCH + "obj/lgeneral");
    sheath->set_general_data("glistening"  + "&&"
							+ "black" + "&&"
							+ "hide" + "&&"
							+ "belt-sheath");
	sheath->move(TO);

	// Freo's custom knife.
	fcus = one_of_list(({"curved", "folded-steel", "long", "short"}));
	fcus2 = one_of_list(({"curved", "folded-steel", "polished"}));
	fwep = one_of_list(({"dagger", "knife", "kukri"}));

	object fknife = clone_object(MERCH + "arms/smith_knife");
	fknife->set_weapon_data(fcus + "&&"
							+ fcus2 + "&&"
							+ fwep);
	fknife->move(TO);

	command("wear all");
	command("wear belt-sheath");
	command("dsheathe knife in belt-sheath");
	MONEY_MAKE_GC(5 + random(19))->move(TO);
	MONEY_MAKE_SC(20 + random(35))->move(TO);
}

string
def_answer()
{
    command("emote smiles somewhat amused.");
	command("say I know many things, among which that is not one.");
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
attacked_by(object ob)
{
	command("say What the...!?!");
	if (!command("ddraw from belt-sheath"))
		command("shout Damn you!");

    ::attacked_by(ob);
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
			+ "Come back when you have that?");
			return 1;
		}
		TP->catch_msg("You pay the masseur ten gold coins.\n");
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
	facee->catch_msg("Freo takes a jar of " + oil + " oil from the counter "
	+ "and works it into his fingers and hands.\n");
	say("Freo takes a jar of " + oil + " oil from the counter beside "
	+ QTNAME(facee) + "'s massage table and works it into his fingers and "
	+ "hands.\n");
	set_alarm(9.0, 0.0, "massage_routine2", facee);	
}

void
massage_routine2(object facee)
{
	if (facee->query_prop(TABLED))
	{
		command("emote bends over the massage table, the tight hide of his "
		+ "black tall-boots stretching across his firm, sporty buttocks.");
		facee->catch_msg("Freo firmly rubs the " + oil + " oil into your "
		+ "shoulders as his thumbs massage the muscles of your neck "
		+ "immediately relaxing them.\n");
		say("Freo firmly rubs the " + oil + " oil into " + QCTNAME(facee)
		+ "'s shoulders as his thumbs massage the muscles of " + HIS(facee)
		+ "neck.\n");
		set_alarm(5.0, 0.0, "massage_enjoy", facee);
		set_alarm(15.0, 0.0, "massage_routine3", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_massage", facee);
}

void
massage_routine3(object facee)
{
	if (facee->query_prop(TABLED))
	{
		command("say " + one_of_list(({"You have such beautiful hands.",
		"Such elegant and supple fingers you have.", "Mmm, such soft "
		+ "skin you have."})));
		facee->catch_msg("Freo firmly rubs the " + oil + " oil down your "
		+ "triceps to your forearms rubbing in slow circles as he comes "
		+ "to your hands and massages your palm and each finger with "
		+ "tender care.\n");
		say("Freo firmly rubs the " + oil + " down " + QCTNAME(facee)
		+ "'s triceps to " + HIS(facee) + " forearms rubbing in slow circles "
		+ "as he comes to " + HIS(facee) + " hands, massaging " + HIS(facee)
		+ " palm and each finger with tender care.\n");
		set_alarm(7.0, 0.0, "massage_enjoy", facee);
		set_alarm(18.0, 0.0, "massage_routine4", facee);
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

		command("emote focuses with furrowed brow and exceptionally dark "
		+ "brown narrowed eyes.");
		facee->catch_msg("Freo wipes his hands on a white towel, takes a jar "
		+ "of " + oil + " oil from the counter and works some more massage "
		+ "oil into his fingers and hands before continuing his ministrations "
		+ "down your spine, easing the muscles of your back before he strokes "
		+ "your sensitive, lithely muscled sides from your hips all the way "
		+ "up to your underarms.\n");
		say("Freo wipes his hands on a white towel, takes a jar of " + oil
		+ " oil from the counter and works some more massage oil into his "
		+ "fingers and hands before continuing his ministrations down "
		+ QTNAME(facee) + "'s spine, easing the muscles of " + HIS(facee)
		+ " back before he strokes " + HIS(facee) + " lithely muscled sides "
		+ "from " + HIS(facee) + " hips all the way to " + HIS(facee)
		+ "underarms.\n");
		set_alarm(8.0, 0.0, "massage_enjoy", facee);
		set_alarm(20.0, 0.0, "massage_routine5", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_massage", facee);
}

void
massage_routine5(object facee)
{
	if (facee->query_prop(TABLED))
	{
		facee->catch_msg("Freo firmly massages the " + oil + " oil into your "
		+ "outer thighs rubbing in slow circles as he moves around to your "
		+ "inner thighs then gradually down to the backs of your knees.\n");
		say("Freo firmly massages the " + oil + " into " + QCTNAME(facee)
		+ "'s outer thighs rubbing in slow circles as he moves around to "
		+ HIS(facee) + " inner thighs then gradually down to the backs of "
		+ HIS(facee) + " knees.\n");
		set_alarm(5.0, 0.0, "massage_enjoy", facee);
		set_alarm(19.0, 0.0, "massage_routine6", facee);
		return;
	}
	set_alarm(0.5, 0.0, "ruin_massage", facee);
}

void
massage_routine6(object facee)
{
	if (facee->query_prop(TABLED))
	{
		command("emote pulls his shoulders back as he works, the elfwyr of "
		+ "his unlaced white sleeveless shirt stretching tight against the "
		+ "light muscular outline of his chest.");
		facee->catch_msg("Freo continues massaging the " + oil + " oil from "
		+ "your knees down your calves squeezing them in slow circles as he "
		+ "makes his way to your ankles.\nFreo takes your feet and squeezes "
		+ "and kneads their bottoms with his thumbs before gently caressing "
		+ "each toe individually.\n");
		say("Freo continues massaging the " + oil + " oil from "
		+ QTNAME(TP) + "'s knees down to " + HIS(facee) + " calves squeezing "
		+ "them in slow circles as he makes his way to " + HIS(facee)
		+ " ankles.\nFreo takes " + HIS(facee) + " feet and squeezes and "
		+ "kneads their bottoms with his thumbs before gently caressing each "
		+ "toe individually.\n");
		set_alarm(8.0, 0.0, "massage_enjoy", facee);
		set_alarm(18.0, 0.0, "massage_routine7", facee);
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

		facee->catch_msg("Freo takes a small, white towel from the stack "
		+ "of towels on the counter, soaks it into a jar of " + sjar
		+ "-scented water, and uses both hands to squeeze your body, neck "
		+ "to toes, wiping off the " + oil + " massage oil and cleansing "
		+ "your skin.\n");
		say("Freo takes a small, white towel from the stack of towels "
		+ "on the counter, soaks it into a jar of " + sjar + "-scented "
		+ "water, and uses both hands to squeeze " + QCTNAME(facee) + "'s "
		+ "body, neck to toes, wiping off the massage " + oil + " oil and "
		+ "cleansing " + HIS(TP) + " skin.\n");
		set_alarm(5.0, 0.0, "massage_enjoy", facee);
		set_alarm(10.0, 0.0, "massage_enjoy", facee);
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
		command("emote leans over the counter, the tight muscles "
		+ "of his shoulders pressing against the tight elfwyr of his "
		+ "shirt, as he washes his hands in a bowl on the counter and "
		+ "dries them on a small, white towel.");
		facee->catch_msg("Freo helps you up from the massage table as "
		+ "he says:  Thank you for coming.  I sincerely hope you enjoyed "
		+ "yourself.  Please come see me again?\nFreo smiles with "
		+ "interest at you.\n");
		say("Freo helps " + QCTNAME(facee) + " up from the massage table as "
		+ "he says:  Thank you for coming.  I sincerely hope you enjoyed "
		+ "yourself.  Please come see me again?\nFre smiles with an odd "
		+ "glint in his dark eyes.\n");
		facee->remove_prop(TABLED);
		facee->remove_prop(LIVE_S_EXTRA_SHORT);
		myroom->off_table();
		facee->add_prop(HAD_MASSAGE, 1);
		facee->heal_hp(500);

		msubloc = clone_object(NOBLE + "obj/spa_masseur_subloc");
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
	  "You groan under the masseur' ministrations:  Ahhhhh.",
	  "\"Oh, yes,\" this feels good.",
	  "The masseur is undeniably a professional you think to yourself as his "
	+ "strong, able hands restore your energy.",
	  "You feel yourself transported to another world full of relaxing "
	+ "energies and " + oil + " skies of pleasure.",
	  "You sigh to yourself as you wonder how you got by for so long without "
	+ "indulging yourself so pleasurably."}));

	string othiss = one_of_list(({"moans quietly as " + HE(facee)
	+ " squeezes " + HIS(facee) + " legs togethis.",
	  "says: Mmmmm.",
	  "says: Freo...",
	  "says: Oh, gods, don't stop.",
	  "says: Uhh!  That's the spot... yes, ohhhhh.",
	  "mumbles something about pretty rainbows.",
	  "licks " + HIS(facee) + " lips slowly.",
	  "says: Mmmm, my skin... so good.",
	  "moans under the masseur's ministrations:  Ohhhhh.",
	  "mumbles something about a world of new age energies.",
	  "says: My body feels so good.",
	  "sighs in utter relaxation.",
	  "sighs pleasurably.",
	  "breathes in and out slowly in a state of deep relaxation.",
	  "smiles in an extremely relaxed manner.",
	  "says: You have GOT to try this.",
	  "says: Mmm, this is amazing."}));

	facee->catch_msg(self + "\n");
	say(QCTNAME(facee) + " " + othiss + "\n");
}

void
ruin_massage(object facee)
{
	facee->catch_msg("As you are no longer laying on the massage table at "
	+ "the Laethorian massage parlour, you have ruined your massage!\n");
	command("emote chews on his lower lip in confusion.");
	command("say Oh.");
	alrm = 0;
}

int
special_attack(object enemy)
{
    int attacktype, pen, att, wloc;
    string hitloc, attack, how, weapon;
    mixed hitres;

    if (!sizeof(query_weapon(-1)))
	return 0;

    attacktype = random(3);

    hitloc = one_of_list(({"left arm","right arm","body","head"}));
	if (hitloc == "head")
		attack = " cuts up";
	else if (hitloc == "body")
		attack = " slashes down";
	else
		attack = " swipes across";
	
    weapon = query_weapon(-1)[0]->query_short();

    if (attacktype == 1)
    {
		pen = 125 + random(100);
		hitres = enemy->hit_me(pen, W_IMPALE, TO, -1);

		if (hitres[0] <= 0)
			how = "his " + weapon + " just missing";
		if(hitres[0] > 0)
			how = "his " + weapon + " barely grazing";
		if(hitres[0] > 10)
			how = "his " + weapon + " drawing a line of blood across";
		if(hitres[0] > 20)
			how = "his " + weapon + " cutting deftly";
		if (hitres[0] > 40)
			how = "his " + weapon + " slipping halfway into";
		if (hitres[0] > 60)
			how = "his " + weapon + " slashing almost all the way through";

		enemy->catch_msg(QCTNAME(TO) + attack + " at you, " + how + " your "
		+ hitloc + ".\n");

		tell_room(E(TO), QCTNAME(TO) + attack + " at " + QTNAME(enemy) + ", "
		+ how + " " + HIS(enemy) + " " + hitloc + ".\n", ({enemy, TO}));

		if (enemy->query_hp() <= 0)
			enemy->do_die(TO);

		return 1;
    }

    return 0;
}
