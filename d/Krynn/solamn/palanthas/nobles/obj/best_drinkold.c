/* Mortis 12.2005
 *
 * This is the drink base for the drinks served in the
 * Mer-cantile cafe in the Plaisir district of Palanthas.
 *
 * Reduce alcohol amount by 25 with each sip.
 */


inherit "/std/object";
inherit "/lib/keep";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../../local.h"

#define MY_FLA1_NAME			"_my_fla1_name"
#define MY_FLA2_NAME			"_my_fla2_name"
#define MY_DRI_NAME				"_my_dri_name"
#define I_M_THE_BEST_DRINK		"_i_m_the_best_drink"
#define LIKED_BY_MORGULSFIRE	"_liked_by_morgulsfire"
#define LIKED_BY_MORGULSDEATH	"_liked_by_morgulsdeath"
#define LIKED_BY_ELVES			"_liked_by_elves"
#define LIKED_BY_HUMANS			"_liked_by_humans"
#define LIKED_BY_DWARVES		"_liked_by_dwarves"
#define LIKED_BY_GNOMES			"_liked_by_gnomes"
#define LIKED_BY_SHORTIES		"_liked_by_shorties"
#define HATED_BY_HARSHES		"_hated_by_harshes"

int sips = 10 + random(3);
int topwhip = 0;
int topcream = 0;
int topsugar = 0;
int topcinna = 0;
int tophoney = 0;

/* Prototypes */
string name_desc();
string recover_string;
string *command_array;
string adjfla1, adjfla2, namedri;
string make_shortdri(string dri, string dfull);
string make_shortfla(string fla1, string fla2);
string sipbase = "";
string cofrace;
string race_smell();
string race_smell_do();
string race_sip();
string race_sip_do();
void sippin_cof();

mapping drink_desc_values = (["flavour":({"aromatic", "black",
	"caramel", "chocolate", "cinnamon", "dark", "eggnog",
	"fresh", "hazelnut", "hot", "iced", "light", "mocha", 
	"peppermint", "plain", "pumpkin", "steaming", "toffeenut", "vanilla"}),
	"flavour2":({"aromatic", "black", "caramel", "chocolate", "cinnamon",
	"dark", "eggnog", "fresh", "hazelnut", "hot", "iced", "light", "mocha", 
	"peppermint", "plain", "pumpkin", "steaming", "toffeenut", "vanilla"}),
	"drink":({"apple-cider", "cafe-misto", "cappucino", "espresso", "latte"}),
	"coffee":({"harad", "mer-cafe", "shoikan", "tantallon-peaberry",
	"tradewind"}), "tea":({"black", "green", "herbal"})]);

mapping drink_to_name = (["apple-cider":"apple-cider",
	"cafe-misto":"cafe-misto", "cappuccino":"cappuccino",
	"espresso":"espresso","latte":"latte", "harad":"harad coffee",
	"mer-cafe":"Mer-cafe coffee", "shoikan":"Shoikan coffee",
	"tantallon-peaberry":"Tantallon-peaberry coffee",
	"tradewind":"Tradewind coffee", "black":"black tea",
	"green":"green tea", "herbal":"herbal tea"]);

mapping drink_to_realname = (["apple-cider":"apple-cider",
	"cafe-misto":"cafe-misto", "cappuccino":"cappuccino",
	"espresso":"espresso","latte":"latte", "harad":"coffee",
	"mer-cafe":"coffee", "shoikan":"coffee",
	"tantallon-peaberry":"coffee",
	"tradewind":"coffee", "black":"tea", "green":"tea",
	"herbal":"tea"]);

mapping name_to_desc = (["apple-cider":"fresh-pressed apple cider and a "
	+ "secret blend of spices.  It is a greenish brown and wisps of steam "
	+ "rise from it.",
	"cafe-misto":"rich, full-bodied Mer-cantile espresso combined with hot "
	+ "water for the Palanthian alternative to conventional-style brewed "
	+ "coffee.",
	"cappuccino":"rich, full-bodied Mer-cantile espresso in a small amount "
	+ "of steamed milk, with a deep layer of foam. With less milk than a "
	+ "latte, the classic and complex cappuccino offers a stronger espresso "
	+ "flavour and luxurious texture.",
	"espresso":"a fresh espresso shot that forms three layers: the aromatic "
	+ "cream, the billowing body, and the dark, intense heart.  Smooth and "
	+ "versatile espresso roast is the soul of the Mer-cantile with a rich "
	+ "flavour, lingering aroma and caramel-like sweetness.",
	"latte":"rich, full-bodied Mer-cantile espresso in steamed milk lightly "
	+ "topped with foam.",
	"harad":"the small dry beans of the arid Harad slopes and imported "
	+ "from Middle-Earth to Krynn through Palanthas.  It provides a unique, "
	+ "earthy, and dry tasting flavour found nowhere else.",
	"mer-cafe":"a blend of beans hand selected by the brewmaster of the "
	+ "Mer-cantile cafe in Palanthas for their rich, smooth drinkability.",
	"shoikan":"very dark, almost black, roasted beans local to Palanthas "
	+ "and named for the dark grove surrounding the Tower of High Sorcery "
	+ "that makes it famous.  It makes a very dark, rich coffee and is very "
	+ "strong.",
	"tantallon-peaberry":"small, unique folded bean native to the high "
	+ "slopes of Tantallon.  Its flavour is noted for its warmth and hint "
	+ "of fruits and berries.",
	"tradewind":"a blend imported by the Tradewind Coffee Company of "
	+ "Palanthas.  This season it is noted for its "
	+ one_of_list(({"light colour and hint of berries.", "medium darkness "
	+ "and hint of nuts", "smooth elegance and floral aroma."})),
	"black":"the fully dried, fermented leaf of the Camellia Sinensis.  "
	+ "Black teas have a red amber color when brewed from the tea trees "
	+ "grown outside of Palanthas and cured by the master tea houses.",
	"green":"the same leaves as black teas, only the unoxidized tea leaves "
	+ "are steamed to stop the oxidation process, thus yielding a green and "
	+ "vegetative brew.  It is grown outside of Palanthas and prepared by "
	+ "the master tea houses.",
	"herbal":"flowers, fruit peels, roots, bark, berries, herbs and spices "
	+ "and prepared by the elven masters of the tea houses in Palanthas."]);

string sdesc = one_of_list(({"Written on the outside of the cup is a "
	+ "Mer-cantile saying:  Sometimes when we turn around, we must look "
	+ "behind to see where we are going.", "A quote is written on the "
	+ "outside of the cup, \"Life is like a coin.  You can spend it however "
	+ "you like, but you can spend it only once.  And sometimes, machines "
	+ "will not take it, and you try over and over, but it just keeps "
	+ "spitting it out.\" -Igblat, Vendorlord of Mt. Nevermind.", "Written "
	+ "on the outside of the cup is a quote, \"Life is like a coin.  You can "
	+ "spend it however you like, but you can only spend it once unless your "
	+ "religion offers refunds.\" - Quebyas the Aesthetic.", "Written on the "
	+ "outside of the cup is, \"Time will tell.\"  - Didelith of Calia.",
	  "Written on the outside of the cup is, \"Everything has beauty, but "
	+ "not everyone sees it.\"  - Guinevere of the Dragon Order.", "A quote "
	+ "is written on the outside of the cup, \"Patience is a virtue, and "
	+ "we're all sinners.\"  - Hektor of Calia.", "A quote is written on the "
	+ "outside of the cup, \"I am disinclined to acquiesce to your "
	+ "request.\"  - Wulfhere of the Red Dragonarmy.", "On the side of the "
	+ "cup is a saying, \"I've always felt that my whole life was some kind "
	+ "of dream and sometimes wondered whose it was and whether they were "
	+ "enjoying it.\"  -Gub of the Dragon Order.", "On the side of the "
	+ "cup is written, \"Yesterday we obeyed kings and bent our necks "
	+ "before emperors. But today we kneel only to truth.\"  - Saioran "
	+ "of the Blue Dragonarmy.", "On the side of the cup is a "
	+ "saying, \"Do or Do not.  There is no try.\"  -Peldor, Knight of "
	+ "Solamnia.", "Written on the cup's side is, \"There is no good or "
	+ "evil.  There is only a point of view.\"  - Peldor, Knight of Solamnia.",
	  "On the side of the cup is written, \"I never think of the future.  "
	+ "It comes soon enough.\"  - Wulfhere of the Red Dragonarmy.",  "A "
	+ "saying is written on the cup's side, \"What you risk reveals what you "
	+ "value.\"  - Wulfhere of the Red Dragonarmy.", "On the cup's side "
	+ "is a saying, \"Flattery is like cologne water, to be smelt of, "
	+ "not swallowed.\"  - Wulfhere of the Red Dragonarmy.", "A saying "
	+ "is written on the outside of the cup, \"To avoid criticism do "
	+ "nothing, say nothing, be nothing.\"  - Wulfhere of the Red "
	+ "Dragonarmy.", "On the cup's side is a quote, \"Roam abroad in the "
	+ "world, and take thy fill of its enjoyments before the day shall "
	+ "come when thou must quit it for good.\"  - Wulfhere of the Red "
	+ "Dragonarmy.", "On the cup's side is a quote, \"You know the very "
	+ "powerful and the very stupid have one thing in common. They don't "
	+ "alter their views to fit the facts, they alter the facts to fit "
	+ "their views, which can be uncomfortable if you happen to be one of "
	+ "the facts that needs altering.\"  - An unknown doctor.", "A saying "
	+ "is written on the cup's side, \"A new idea is delicate.  It can be "
	+ "killed by a sneer or a yawn.  It can be stabbed to death by a joke "
	+ "or worried to death by a frown on the right person's brow.\"  - "
	+ "Greneth of the Dragon Order.", "On the cup's side is a quote, \" "
	+ "I can picture in my mind a world without war, a world without hate, "
	+ "and I can picture us attacking that world, because they'd never "
	+ "expect it.\"  - Greneth of the Dragon Order.", "Quoted on the side "
	+ "of the cup is, \"The world is a dangerous place not because of "
	+ "those who do evil, but because of those who look on and do nothing.\""
	+ "  - Greneth of the Dragon Order.", "The cup's side bears the quote, "
	+ "\"I am not afraid of tomorrow, for I have seen yesterday, and I love "
	+ "today.\"  - Rugogold of Ithilien.",
	  "\"No one can make you feel inferior without your consent.\"  "
	+ "- Xerxes of Calia.",
	  "\"The greatest discovery of any generation is that a human being can "
	+ "alter his life by altering his attitude.\"  - Gub of the Dragon "
	+ "Order.",
	  "\"They may forget what you said, but they will never forget how you "
	+ "made them feel.\"  - Gub of the Dragon Order.",
	  "\"In the middle of difficulty lies opportunity.\"  - Gub of the "
	+ "Dragon Order.",
	  "If you pick up a starving dog and make him prosperous, he will not "
	+ "bite you.  That is the principal difference between a dog and a "
	+ "man.\"  - Gub of the Dragon Order.",
	  "\"I am ready to meet Lars, but whether Lars is prepared for the "
	+ "great ordeal of meeting me is another matter.\"  - Wyork the "
	+ "Necromancer.",
	  "\"It is a thousand times better to have common sense without "
	+ "education than to have education without common sense.\"  - "
	+ "Guinevere of the Dragon Order.",
	  "\"Whatever women do they must do twice as well as men to be thought "
	+ "half as good.  Luckily, this is not difficult.\"  - Guinevere of "
	+ "the Dragon Order.",
	  "\"Well behaved women rarely make history.\"  - Guinevere of the "
	+ "Dragon Order.",
	  "\"Do not look back in anger or forward in fear, but around in "
	+ "awareness.\"  - Guinevere of the Dragon Order.",
	  "\"Great ideas often receive violent opposition from mediocre minds.\""
	+ "  - Guinevere of the Dragon Order.",
	  "\"The distance between insanity and genius is measured only by "
	+ "success.\"  - Guinevere of the Dragon Order.",
	  "\"If we could see the miracle of a single flower, our whole life "
	+ "would change.\"  - Guinevere of the Dragon Order.",
	  "\"When everything is new, can anything be a surprise?\"  - "
	+ "Mersereau the Mercenary.",
	  "\"There's no point in being grown-up if you can't be childish "
	+ "sometimes.\"  - Mersereau the Mercenary.",
	  "\"If heroes don't exist, it is necessary to invent them;  good for "
	+ "public morale.\"  - Mersereau the Mercenary.",
	  "\"Grinding oppression of the masses is the only policy that pays "
	+ "dividends.\"  - Mersereau the Mercenary.",
	  "\"Have you noticed how people's intellectual curiosity declines "
	+ "sharply the moment they start waving pitchforks about?\"  - "
	+ "Mersereau the Mercenary.",
	  "\"First things first, but not necessarily in that order.\"  - "
	+ "Mersereau the Mercenary.",
	  "\"Time reveals everything.\"  - Mersereau the Mercenary.",
	  "\"Never guess, unless you have to.  There's enough uncertainty in "
	+ "the world as it is.\"  - Mersereau the Mercenary.",
	  "\"I never think twice about anything;  takes too much time.\"  - "
	+ "Mersereau the Mercenary.",
	  "\"False modesty is the refuge of the incompetent.\"  - Mersereau "
	+ "the Mercenary.",
	  "\"Small though it is, the human brain can be quite effective when "
	+ "used properly.\"  - Mersereau the Mercenary.",
	  "\"You can judge a man by the quality of his enemies.\"  - Mersereau "
	+ "the Mercenary.",
	  "\"Courage isn't just a matter of not being afraid. It's being "
	+ "afraid and doing what you have to do anyway.\"  - Mersereau the "
	+ "Mercenary.",
	  "\"A straight line may be the shortest distance between two points, "
	+ "but it is by no means the most interesting.\"  - Mersereau the "
	+ "Mercenary.",
	  "\"Answers are easy. It's asking the right questions which is hard.\"  "
	+ "- Mersereau the Mercenary.",
	  "\"To the rational mind nothing is inexplicable, only unexplained.\"  "
	+ "- Mersereau the Mercenary.",
	  "\"Sleep is for tortoises!\"  - Mersereau the Mercenary.",
	  "\"A risk shared is a risk doubled.\"  - Mersereau the Mercenary."}));

mapping name_to_sipbase = (["apple-cider":"the fresh-pressed taste of apple "
	+ "cider and a secret blend of spices.",
	"cafe-misto":"the taste of a rich, full-bodied Mer-cantile espresso "
	+ "combined with hot water for the Palanthian alternative to "
	+ "conventional-style brewed coffee.",
	"cappuccino":"the taste of a rich, full-bodied Mer-cantile espresso "
	+ "in a small amount of steamed milk, with a deep layer of foam.  "
	+ "It has a strong espresso flavour and luxurious texture.",
	"espresso":"a fresh espresso taste formed by three layers: the aromatic "
	+ "cream, the billowing body, and the dark, intense heart.  It has a "
	+ "rich flavour, lingering aroma and caramel-like sweetness.",
	"latte":"the rich, full-bodied taste of Mer-cantile espresso in steamed "
	+ "milk lightly topped with foam.",
	"harad":"a unique, earthy, and dry tasting flavour found nowhere else "
	+ "but the arid slopes of the Harad.",
	"mer-cafe":"a rich, smooth drinkability.",
	"shoikan":"very dark, almost black, roasted bean taste.  It is very "
	+ "strong.",
	"tantallon-peaberry":"a warmth and hint of fruits and berries.",
	"tradewind":"a smoothly elegant, floral aroma with a hint of nuts.",
	"black":"the classic, leafy flavour of a good red amber brew.",
	"green":"a green and vegetative tea leaf flavour.",
	"herbal":"the stimulating flavours of flowers, fruit peels, roots, "
	+ "bark, berries, herbs and spices prepared by the elven brewmasters."]);


void
create_object()
{
    add_name("drink");
	add_pname("drinks");
	add_name("cup");
	add_pname("cups");


    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_M_NO_SELL, 1);

    seteuid(getuid());
}

void
set_drink_data(string data)
{
    string* txt = explode(data,"&&");
    string fla1 = txt[0];
    string fla2 = txt[1];
    string dri = txt[2];
	string dfull = drink_to_realname[dri];
	string shortdri = make_shortdri(dri, dfull);
	string shortfla = make_shortfla(fla1, fla2);

	recover_string = data;

	add_prop(MY_DRI_NAME, dri);
	add_prop(MY_FLA1_NAME, fla1);
	add_prop(MY_FLA2_NAME, fla2);

    set_name(dri);
	set_pname(dri + "s");
	add_name(dfull);
	add_adj(fla1);
    add_adj(fla2);
	add_adj(dri);
	set_short("cup of " + shortfla + " " + shortdri);
    set_long("Served in a tall, white cup, this "
	+ "@@name_desc@@" + " has been brewed from " + "@@brew_desc@@" + "  "
	+ sdesc + "\n");

	command_array = TO->query_names();
	adjfla1 = TO->query_prop(MY_FLA1_NAME);
	adjfla2 = TO->query_prop(MY_FLA2_NAME);
	namedri = drink_to_name[TO->query_prop(MY_DRI_NAME)];
	sipbase = name_to_sipbase[dri];

	/* The following sets props in the drink based on drink type and
	 * flavours.  The props determine whether a race will like it or
	 * not.
	 * -Vamps don't get anything out of any type/flavour.  Same result.
	 * -Morguls have 1) Cinnamon "enhances" fire.  2) Shoikan - death(?)
	 * -Presence is bad form to enjoy, etc.
	 * -Elves go nuts for vanilla, green/herbal teas.
	 * -Humans + 1/2's like aromatic.
	 * -Dwarves like iced, shoikan, and espresso.
	 * -Gnomes like all espresso-based drinks.
	 * -Hobbits/Kender like caramel, toffeenut, peppermint, pumpkin
	 * -Gob/hobgob/mino/orc/uruk hate all but shoikan, black tea, harad,
	 *  espresso, cafe-misto.
	 */

	if (fla1 == "cinnamon" || fla2 == "cinnamon")
		{ add_prop(LIKED_BY_MORGULSFIRE, 1); }
	if (dri == "shoikan")
		{ add_prop(LIKED_BY_MORGULSDEATH, 1); }
	if (fla1 == "vanilla" || fla2 == "vanilla" || dri == "green" ||
		dri == "herbal")
		{ add_prop(LIKED_BY_ELVES, 1); }
	if (fla1 == "aromatic" || fla2 == "aromatic")
		{ add_prop(LIKED_BY_HUMANS, 1); }
	if (fla1 == "iced" || fla2 == "iced" || dri == "shoikan" ||
		dri == "espresso")
		{ add_prop(LIKED_BY_DWARVES, 1); }
	if (parse_command(dri, ({}), "'cafe-misto' / 'cappuccino' / 'latte' / 'espresso'"))
		{ add_prop(LIKED_BY_GNOMES, 1); }
	if (parse_command(fla1, ({}), "'caramel' / 'toffeenut' / 'peppermint' / 'pumpkin'") ||
		parse_command(fla2, ({}), "'caramel' / 'toffeenut' / 'peppermint' / 'pumpkin'"))
		{ add_prop(LIKED_BY_SHORTIES, 1); }
	if (!parse_command(dri, ({}), "'shoikan' / 'black' / 'harad' / 'espresso' / 'cafe-misto'"))
		{ add_prop(HATED_BY_HARSHES, 1); }

}

string name_desc()
{
	string ndesc = "";
	string nname = TO->query_name();

	ndesc = drink_to_name[nname];

	return ndesc;
}

string brew_desc()
{
	string bdesc = "";
	string bname = TO->query_prop(MY_DRI_NAME);

	bdesc = name_to_desc[bname];

	return bdesc;
}

string make_shortdri(string dri, string dfull)
{
	if (dri == dfull)
	{
		return dri;
	}
	return dri + " " + dfull;
}

string make_shortfla(string fla1, string fla2)
{
	if (fla1 == fla2)
	{
		return fla1;
	}
	return fla1 + " " + fla2;
}

void
init()
{
	/* One(?) overriding emote per article. */
    ::init();
    ADA("smell");
	ADA("sip");
	ADA("drink");
}

int
smell(string str)
{
	int i, j, k;
	cofrace = QRACE(TP);

    NF("Smell what?\n");

    if (!str)
	return 0;

	for(i=0,j=sizeof(command_array);i<j;i++)
	{
		k = member_array(str, command_array);
		if (k == -1)
		{
			return 0; /*invalid name*/
		}
	}

    write("You lift the " + namedri + " to your nose and smell "
	+ "its " + adjfla1 + " " + adjfla2
	+ " aroma.  " + race_smell() + "\n");
    tell_room(E(TP), QCTNAME(TP)+ " raises a " + short() + " to "
	+ HIS(TP) + " nose smelling its aroma.  " + race_smell_do() + "\n",
		({TO, TP}));

    return 1;
}

int
sip(string str)	//Reduces intox by 5, max once per 30-35 seconds
{
	int i, j, k;
	int alco, newalco;
	cofrace = QRACE(TP);
	alco = TP->query_intoxicated();

	NF("Sip what?\n");

    if (!str)
	return 0;

	for(i=0,j=sizeof(command_array);i<j;i++)
	{
		k = member_array(str, command_array);
		if (k == -1)
		{
			return 0; /*invalid name*/
		}
	}

	if (TP->drink_soft(6, 0))
	{
	TP->drink_soft(6, 0);

    write("Your eyelids lower slowly as the " + adjfla1 + " " + adjfla2
	+ " flavours in the " + namedri + " flow past your lips accompanied by "
	+ sipbase + "  " + race_sip() + "\n");
    tell_room(E(TP), QCTNAME(TP) + "'s eyelids lower slowly as " + HE(TP)
	+ " takes a sip of the " + short() + ".  " + race_sip_do()
	+ "\n", ({TO, TP}));
	sips--;

	if (TP->query_prop("last_sip_time") < time())
	{
		if (alco > 0)
		{
			newalco = alco - 5;
			if (newalco > 0 && newalco < 6)
			{
				newalco = 0;
			}
			TP->set_intoxicated(newalco);
			TP->add_prop("last_sip_time", time() + 30 + random(6));
		}
	}

	if (sips <= 0) 	{ sippin_cof(); }

	}

	else write("You are full and cannot drink any more.\n");

    return 1;
}

public mixed
sippin_cof()
{
	TP->catch_msg("You turn up the cup and the last drop falls on "
	+ "your tongue.\n");
	tell_room(E(TP), QCTNAME(TP) + " turns up " + HIS(TP) + " " + short()
	+ " allowing the last drop to fall on " + HIS(TP) + " tongue.\n",
		({TO, TP}));
	TO->remove_object();
}

int
drink(string str)
{
	int i, j, k;

	if (!str)
	return 0;

	for(i=0,j=sizeof(command_array);i<j;i++)
	{
		k = member_array(str, command_array);
		if (k == -1)
		{
			return 0; /*invalid name*/
		}
	}

	if (sips > 0 && adjfla1 != "iced" && adjfla2 != "iced")
	{
		TP->catch_msg("You try to drink too much at once and end up burning "
		+ "the tip of your tongue most painfully.\n");
		tell_room(E(TP), QCTNAME(TP) + " cries out in pain as " + PRONOUN(TP)
		+ " burns " + HIS(TP) + " tongue trying to drink a " + short()
		+ " too quickly:  Nooooo!  Why?!?" + "\n", ({TO, TP}));
		return 1;
	}
	TP->catch_msg("You try to drink too much at once and end up freezing the "
	+ "tip of your tongue most painfully.\n");
	tell_room(E(TP), QCTNAME(TP) + " cries out in pain as " + PRONOUN(TP)
	+ " freezes " + HIS(TP) + " tongue trying to drink a " + short()
	+ " too quickly:  Nooooo!  Why?!?" + "\n", ({TO, TP}));
	return 1;

}

string
race_smell()
{

	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "Though hot, there is no blood in this drink.";
	}

	if (TP->query_guild_name_occ() == "Morgul Mages" &&
		query_prop(LIKED_BY_MORGULSFIRE) == 1)
	{
		return "The smell of cinnamon is strong in this drink.  It may "
		+ "enhance elemental magic from the sphere of flame and fire.";
	}

	if (TP->query_guild_name_occ() == "Morgul Mages" &&
		query_prop(LIKED_BY_MORGULSDEATH) == 1)
	{
		return "The smell of death is strong in this drink.  It may "
		+ "enhance death magic and related spheres of power.";
	}

	if (TP->query_guild_name_race() == "Noldor of Imladris" ||
		cofrace == "elf" || cofrace == "drow")
	{
		if (query_prop(LIKED_BY_ELVES) == 1)
		{
		return "As you breathe in the vapors, you feel a strangely "
		+ "pleasant warmth spread through you.";
		}
	}

	if (parse_command(cofrace, ({}), "'human' / 'half-human' / 'half-elf'"))
	{
		if (query_prop(LIKED_BY_HUMANS) == 1)
		{
		return "As you breathe in the aromatic vapors, you feel a strangely "
		+ "pleasant warmth spread through you.";
		}
	}

	if (cofrace == "hobbit" || cofrace == "kender")
	{
		if (query_prop(LIKED_BY_SHORTIES) == 1)
		{
		return "As you breathe in the sweet vapors, you feel a strangely "
		+ "pleasant warmth spread through you.";
		}
	}

	if (cofrace == "dwarf" && query_prop(LIKED_BY_DWARVES) == 1)
	{
		return "As you breathe in the rich vapors, you feel a strangely "
		+ "pleasant warmth spread through you.";
	}

	if (cofrace == "gnome" && query_prop(LIKED_BY_GNOMES) == 1)
	{
		return "As you breathe in the rich espresso vapors, you feel a "
		+ "strangely pleasant warmth spread through you.";
	}

	if (parse_command(cofrace, ({}), "'goblin' / 'hobgoblin' / 'orc' / "
		+ "'uruk' / 'minotaur'"))
	{
		if (query_prop(HATED_BY_HARSHES) == 0)
		{
		return "As you breathe in the dark vapors, you feel a not "
		+ "unpleasant warmth spread through you.";
		}
	}

	switch(cofrace)
	{

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
	case "wraith":
		return "This is a fine cup of " + namedri + ".";
	break;

	case "elf":
	case "noldor":
	case "drow":
		return "Surprisingly, this is not a bad cup of " + namedri + ".";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "This cup of " + namedri + " has been tended to by a skilled "
	    + "barista at every stage of its life.  Its flavours are well worth "
		+ "further scrutinization.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "Something is definitely wrong... are the humans trying to "
		+ "poison you with this brew?";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	default:
		return "Your race is unknown.  Why not mail Krynn for fun?";
	break;
	}
}

string
race_smell_do()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return C(HE(TP)) + " turns " + HIS(TP) + " nose up in disinterest "
		+ "at the drink.";
	}

	if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		if (query_prop(LIKED_BY_MORGULSFIRE) == 1)
		{
		return C(HIS(TP)) + " eyes light up with a fire of their own as "
		+ HE(TP) + " broods deep in thought.";
		}
		if (query_prop(LIKED_BY_MORGULSDEATH) == 1)
		{
		return C(HIS(TP)) + " smiles with a cold from beyond the grave as "
		+ HE(TP) + " broods deep in thought.";
		}
		return QCTNAME(TP) + " raises an eyebrow as " + HE(TP) + " broods "
		+ "deep in thought.";
	}

	if (TP->query_guild_name_race() == "Noldor of Imladris" ||
		cofrace == "elf" || cofrace == "drow")
	{
		if (query_prop(LIKED_BY_ELVES) == 1)
		{
		return C(HIS(TP)) + "'s face flushes red momentarily as " + HE(TP)
		+ " breathes in slowly, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids.";
		}
	}

	if (cofrace == "human" || cofrace == "half-human" ||
		cofrace == "half-elf")
	{
		if (query_prop(LIKED_BY_HUMANS) == 1)
		{
		return C(HIS(TP)) + " face flushes red momentarily as " + HE(TP)
		+ " breathes in slowly, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids.";
		}
	}

	if (cofrace == "dwarf" && query_prop(LIKED_BY_DWARVES) == 1)
	{
		return C(HIS(TP)) + " cheeks flush red momentarily as " + HE(TP)
		+ " breathes in slowly, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids.";
	}

	if (cofrace == "gnome" && query_prop(LIKED_BY_GNOMES) == 1)
	{
		return C(HIS(TP)) + " nose flushes red momentarily as " + HE(TP)
		+ " breathes in slowly, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids.";
	}

	if (cofrace == "hobbit" || cofrace == "kender" &&
		query_prop(LIKED_BY_SHORTIES) == 1)
	{
		return C(HIS(TP)) + " cheeks flush red momentarily as " + HE(TP)
		+ " breathes in slowly, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids.";
	}

	if (cofrace == "goblin" || cofrace == "hobgoblin" ||
		cofrace == "minotaur" || cofrace == "orc" || cofrace == "uruk")
	{
		if (query_prop(HATED_BY_HARSHES) == 1)
		{
		return C(HIS(TP)) + " lips peel back in a growl " + HE(TP)
		+ " sniffs and snorts vehemently, " + HIS(TP) + " eyes narrowing "
		+ "harshly at " + HIS(TP) + " cup of " + namedri + ".";
		}
	}

	switch(cofrace)
	{

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
	case "wraith":
		return C(HE(TP)) + " closes " + HIS(TP) + " eyes for a moment "
		+ "as " + HIS(TP) + " eyebrows rise a tad.";
	break;

	case "elf":
	case "noldor":
	case "drow":
		return C(HE(TP)) + " nods slightly as " + HE(TP)
		+ " closes " + HIS(TP) + " eyes for a moment, "
		+ HIS(TP) + " " + one_of_list(({"left", "right"})) + " eyebrow "
		+ "rising a tad.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return C(HE(TP)) + " closes " + HIS(TP) + " eyes for a moment "
		+ "and smiles, obviously enjoying " + HIMSELF(TP) + ".";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return C(HE(TP)) + " squints one eye and stares thoughtfully "
		+ "down at the cup with " + HIS(TP) + " other.";
	break;

	case "presence":
		return C(HE(TP)) + " displays little expression from the "
		+ "experience.";
	break;

	default:
		return "What the heck race is this person?  Why not mail Krynn "
		+ "for fun?";
	break;
	}
}

string
race_sip()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "Despite containing no blood whatsoever, you put on a "
		+ "good show of sipping the coffee anyway.  That's the spirit!";
	}

	if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		if (query_prop(LIKED_BY_MORGULSFIRE) == 1)
		{
		return "You feel the fiery cinnamon essence spilling into you, "
		+ "filling your lungs with the enhanced powers of flame and "
		+ "fire.";
		}
		if (query_prop(LIKED_BY_MORGULSDEATH) == 1)
		{
		return "You feel the dark, otherworldly essence spilling into you,"
		+ " imbuing your aura with the enhancing powers of death and beyond.";
		}
	}

	if (TP->query_guild_name_race() == "Noldor of Imladris" ||
		cofrace == "elf" || cofrace == "drow") 
	{
		if (query_prop(LIKED_BY_ELVES) == 1)
		{
		return "An unexpectedly strange but pleasant warmth spreads through "
	    + "your body overcoming your composure for a moment.  Ahhhhh.";
		}
	}

	if (cofrace == "human" || cofrace == "half-human" ||
		cofrace == "half-elf")
	{
		if (query_prop(LIKED_BY_HUMANS) == 1)
		{
		return "An unexpectedly strange but pleasant warmth spreads through "
	    + "your body overcoming your composure for a moment.  Mmm, very nice.";
		}
	}

	if (cofrace == "dwarf" && query_prop(LIKED_BY_DWARVES) == 1)
	{
		return "An unexpectedly strange but pleasant warmth spreads through "
	    + "your body overcoming your composure for a moment.  Ermm, that was "
		+ "good.";
	}

	if (cofrace == "hobbit" || cofrace == "kender")
	{
		if (query_prop(LIKED_BY_SHORTIES) == 1)
		{
		return "An unexpectedly strange but pleasant warmth spreads through "
	    + "your body overcoming your composure for a moment.  Ooo, you "
		+ "shiver that was so good.";
		}
	}

	if (cofrace == "goblin" || cofrace == "hobgoblin" ||
		cofrace == "minotaur" || cofrace == "orc" || cofrace == "uruk")
	{
		if (query_prop(HATED_BY_HARSHES) == 1)
		{
		return "Bleh!  P'tooey!  What poisons are these you've been served?";
		}
	}

	switch(cofrace)
	{

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
	case "wraith":
		return one_of_list(({"This is indeed a quality " + namedri + ".",
	      "The barista of the Mer-Cantile knows her brewing.",
		  "This " + namedri + " alone leaves you "
		+ "impressed with Palanthas' brewing.",
		  "Ahh, how pleasant!"}));
	break;

	case "elf":
	case "noldor":
	case "drow":
		return one_of_list(({"This is a not altogether poor " + namedri + ".",
	      "The barista of the Mer-Cantile must have some brewing knowledge.",
		  "This " + namedri + " does not leave you wary "
		+ "of Palanthas' brewing.",
		  "Hmm, not bad."}));
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "What splendid flavours are these!  Oh, joyous the day "
		+ "you discovered this fancy brew.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "Hmm, that's a solid " + namedri + ".";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	default:
		return "Your race is unknown.  Why not mail Krynn for fun?";
	break;
	}
}

string
race_sip_do()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return C(HE(TP)) + " pretends to sip " + HIS(TP) + " " + short()
		+ ", smiling as " + HE(TP) + " lets it dribble down "
		+ HIS(TP) + " chin.";
	}

	if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		if (query_prop(LIKED_BY_MORGULSFIRE) == 1)
		{
		return C(HIS(TP)) + " eyes throb briefly with a red glow as "
		+ HE(TP) + " smiles " + one_of_list(({"knowingly",
		"with fiery intensity", "grimly", "surreptitiously", "mystically",
		"slightly", "slowly"})) + " from within " + HIS(TP) + " hooded black "
		+ "robes.";
		}
		if (query_prop(LIKED_BY_MORGULSDEATH) == 1)
		{
		return C(HIS(TP)) + " aura darkens visibly and an icy chill sucks "
		+ "the heat from the air as " + HE(TP) + " smiles "
		+ one_of_list(({"slowly", "coldly", "grimly", "icily", "gravely",
		"surreptitiously", "mystically"})) + " from " + "within " + HIS(TP)
		+ " hooded black robes.";
		}
	}

	if (TP->query_guild_name_race() == "Noldor of Imladris" ||
		cofrace == "elf" || cofrace == "drow")
	{
		if (query_prop(LIKED_BY_ELVES) == 1)
		{
		return C(HIS(TP)) + " face flushes red momentarily as " + HE(TP)
		+ " exhales, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids as " + HE(TP) + one_of_list(({
		  " shudders and moans quietly.",
		  " rubs " + HIS(TP) + " hand slowly down " + HIS(TP) + " stomach.",
		  " squeezes " + HIS(TP) + " legs together.",
		  " rubs " + HIS(TP) + " neck and shoulders and goes:  Mmmmmm.",
		  " licks " + HIS(TP) + " lips slowly and luxuriantly."}));
		}
	}

	if (cofrace == "human" || cofrace == "half-human" ||
		cofrace == "half-elf")
	{
		if (query_prop(LIKED_BY_HUMANS) == 1)
		{
		return C(HIS(TP)) + " face flushes red momentarily as " + HE(TP)
		+ " breathes in slowly, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids as " + HE(TP) + one_of_list(({
		" smiles and goes:  Yeah.",
		" rubs " + HIS(TP) + " stomach, squeezing it slowly.",
		" runs " + HIS(TP) + " fingers through " + HIS(TP) + " hair.",
		" mumbles under " + HIS(TP) + " breath:  Ahh, that feels so good.",
		" mutters to " + HIMSELF(TP) + ":  Oh yeah.",
		" whispers:  Oh please... yes."}));
		}
	}

	if (cofrace == "dwarf" && query_prop(LIKED_BY_DWARVES) == 1)
	{
		return C(HIS(TP)) + " cheeks flush red momentarily as " + HE(TP)
		+ " breathes in slowly, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids as " + HE(TP) + one_of_list(({
		" strokes " + HIS(TP) + " beard sensuously.",
		" clutches at " + HIS(TP) + " beard whimpering sporadically.",
		" grunts under " + HIS(TP) + " breath:  Uhhnk, that's the stuff.",
		" gyrates one of " + HIS(TP) + " legs out of control."}));
	}

	if (cofrace == "gnome" && query_prop(LIKED_BY_GNOMES) == 1)
	{
		return C(HIS(TP)) + " nose flushes red momentarily as " + HE(TP)
		+ " breathes in slowly, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids as " + HE(TP) + one_of_list(({
		" blows white hot steam out " + HIS(TP) + " ears and sighs "
		+ "contentedly.",
		" chitters like a squirrel, " + HIS(TP) + " eyebrows bouncing "
		+ "up and down.",
		" gyrates " + HIS(TP) + " hips back and forth with alarming speed "
		+ "and precision.",
		" gyrates " + HIS(TP) + " hips uncontrollably before sputtering to a "
		+ "stop and sighing:  Oooo, yeah."}));
	}

	if (cofrace == "hobbit" || cofrace == "kender")
	{
		if (query_prop(LIKED_BY_SHORTIES) == 1)
		{
		return C(HIS(TP)) + " cheeks flush red momentarily as " + HE(TP)
		+ " breathes in slowly, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids as " + HE(TP) + one_of_list(({
		" slides " + HIS(TP) + " hand between " + HIS(TP) + " legs and "
		+ "squeezes " + HIS(TP) + " thighs together tightly.",
		" giggles:  Ooo, mmm, yes!",
		" swirls " + HIS(TP) + " tongue around his lips uncontrollably.",
		" curls up into a ball, massaging " + HIS(TP) + " feet sensuously.",
		" sighs:  Ooo, don't ever stop."}));
		}
	}

	if (cofrace == "goblin" || cofrace == "hobgoblin" ||
		cofrace == "minotaur" || cofrace == "orc" || cofrace == "uruk")
	{
		if (query_prop(HATED_BY_HARSHES) == 1)
		{
		return C(HIS(TP)) + " lips peel back in a growl as " + HE(TP)
		+ one_of_list(({
		" spits out a glob of brown spittle in disgust and horror!",
		" cries out, \"I've been poisoned!\" as " + namedri + " dribbles "
		+ "down " + HIS(TP) + " chin.",
		" groans and clutches " + HIS(TP) + " stomach, "
		+ "hurling brown glek on " + HIS(TP) + " shoes.",
		" gags and dry-heaves over and over."}));
		}
	}

	switch(cofrace)
	{

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
	case "wraith":
		return C(HE(TP)) + " closes " + HIS(TP) + " eyes for a moment "
		+ "as " + HE(TP) + " breaks a half smile, nodding.";
	break;

	case "elf":
	case "noldor":
	case "drow":
		return C(HE(TP)) + " tilts " + HIS(TP) + " head to the side for "
		+ "a moment as " + HE(TP) + " almost smiles and nods slightly.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return C(HE(TP)) + " closes " + HIS(TP) + " eyes for a moment "
		+ "and giggles, obviously enjoying " + HIMSELF(TP) + ".";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return C(HE(TP)) + " grunts throatily and snorts once.";
	break;

	case "presence":
		return C(HE(TP)) + " displays little expression from the "
		+ "experience.";
	break;

	default:
		return "What the heck race is this person?  Why not mail Krynn "
		+ "for fun?";
	break;
	}
}

int
condiment_whip()
{
	if (topwhip == 1)
	{
		write("There is already whipped cream on the " + short() + ".  There "
		+ "just isn't room for more.\n");
		say(QCTNAME(TP) + " pretends " + HE(TP) + " didn't just squirt "
		+ "whipped cream all over the condiment station as " + HE(TP)
		+ " tried to add even more whipped cream to " + HIS(TP) + " already "
		+ "topped " + short() + ".\n");
		return 1;
	}
	topwhip = 1;
	write("You squirt whipped cream on top of your " + short() + " as high "
	+ "as it will go!\n");
	say(QCTNAME(TP) + " squirts whipped cream on top of " + HIS(TP) + " "
	+ short() + ".\n");
	TO->set_long(long() + "It is topped with a squirted spiral of whipped "
	+ "cream.\n");
	return 1;
}

int
condiment_cream()
{
	if (topcream == 1)
	{
		write("Yeah!  You pour even more fresh cream into your " + short()
		+ ".  You just can't get enough of that stuff!\n");
		say(QCTNAME(TP) + " pretends to pour more fresh cream into "
		+ HIS(TP) + " already full " + short() + " but instead manages "
		+ "to spill it all over the condiment station.\n");
		return 1;
	}
	topcream = 1;
	write("Your pour just the right amount of fresh cream into your "
	+ short() + " and stir it with a spoon from the condiment station.\n");
	say(QCTNAME(TP) + " pours fresh cream into " + HIS(TP) + " " + short()
	+ " and stirs it with a spoon from the condiment station.\n");
	TO->set_long(long() + "Fresh cream has been added and stirred in.\n");
	return 1;
}

int
condiment_sugar()
{
	if (topsugar == 1)
	{
		write("Can't get enough sugar!  You continue to dump heaping "
		+ "spoonfuls of sugar into your " + short() + ".\n");
		say(QCTNAME(TP) + " flings sugar all over the counter as " + HE(TP)
		+ " pretends " + HE(TP) + " can't get enough sugar and tries "
		+ "to dump it into " + HIS(TP) + " " + short() + ".\n");
		return 1;
	}
	topsugar = 1;
	write("You spoon just the right amount of sugar into your " + short()
	+ " and stir it with a spoon from the condiment station.\n");
	say(QCTNAME(TP) + " spoons sugar into " + HIS(TP) + " " + short()
	+ " and stirs it with a spoon from the condiment station.\n");
	TO->set_long(long() + "It has been sweetened with sugar and stirred.\n");
	return 1;
}

int
condiment_cinna()
{
	if (topcinna == 1)
	{
		write("Can't get enough cinnamon!  You continue to dump heaping "
		+ "spoonfuls of cinnamon into your " + short() + ".\n");
		say(QCTNAME(TP) + " flings cinnamon all over the counter as " + HE(TP)
		+ " pretends " + HE(TP) + " can't get enough cinnamon and tries "
		+ "to look cool dumping it into " + HIS(TP) + " " + short() + ".\n");
		return 1;
	}
	topcinna = 1;
	write("You spoon just the right amount of cinnamon into your " + short()
	+ " and stir it with a spoon from the condiment station.\n");
	say(QCTNAME(TP) + " spoons cinnamon into " + HIS(TP) + " " + short()
	+ " and stirs it with a spoon from the condiment station.\n");
	TO->set_long(long() + "Extra cinnamon has been added and stirred in.\n");
	return 1;
}

int
condiment_honey()
{
	if (tophoney == 1)
	{
		write("Can't get enough honey!  You continue to squirt heaping "
		+ "amounts of honey into your " + short() + ".\n");
		say(QCTNAME(TP) + " squirts honey all over the counter as " + HE(TP)
		+ " pretends " + HE(TP) + " can't get enough honey and tries "
		+ "to squirt it into " + HIS(TP) + " " + short() + ".\n");
		return 1;
	}
	tophoney = 1;
	write("You squirt just the right amount of honey into your " + short()
	+ " and stir it with a spoon from the condiment station.\n");
	say(QCTNAME(TP) + " squirts honey into " + HIS(TP) + " " + short()
	+ " and stirs it with a spoon from the condiment station.\n");
	TO->set_long(long() + "It has been sweetened with honey and stirred.\n");
	return 1;
}

string
query_recover()
{
	return MASTER + ":" + recover_string;
}

void
init_recover(string arg)
{
    ::init_keep_recover(arg);
	set_drink_data(arg);
}
