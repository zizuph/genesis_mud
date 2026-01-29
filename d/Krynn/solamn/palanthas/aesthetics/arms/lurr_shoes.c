/* 
 * Mortis 04.2006
 *
 * This is the foot base for the boots, heels, sandals, shoes,
 * and slippers that Lurr Bramous cobbles in the Aesthetics
 * quarter of Palanthas.
 *
 */
inherit "/d/Krynn/solamn/palanthas/obj/crafted_armour";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include "../../local.h"

inherit "/lib/commands";

int value, weight, volume;
string cus, col, mat, art, cusmore, colmore,
	matlong, collong, artmore, soundmore, ndesc2, cusshort,
	nameshort, matfull;

/* Prototypes */
void add_some_names();
int adjust_value();
int adjust_weight();
int adjust_volume();
int set_the_ac();

mapping name_to_desc = (["boots":"pair of boots", "heels":"pair of high-heels",
	"sandals":"pair of sandals", "shoes":"pair of shoes",
	"slippers":"pair of slippers"]);

mapping name_to_desc2 = (["boots":"pair of boots has a sturdy sole and heel, "
	+ "comes up to your calves, and",
	"heels":"pair of high-heels is firm but flexible with a pointed heel "
	+ "pushing the heel of the foot up and giving the body a provocative "
	+ "posture.  It",
	"sandals":"pair of sandals has a flexible sole and straps that keep the "
	+ "foot and ankle in place and supported.  It",
	"shoes":"pair of shoes",
	"slippers":"pair of low-topped, soft soled slippers wraps around the "
	+ "foot comfortably and"]);

mapping name_to_short = (["boots":"boots", "heels":"high-heels",
	"sandals":"sandals", "shoes":"shoes", "slippers":"slippers"]);

mapping mat_to_desc = (["alligator":"alligator skin, its dark, emerald plates "
	+ "firm but supple and polished smooth.  ",
	"arrasene":"arrasene, a smooth cloth woven from wool and silk giving it "
	+ "great durability and warmth while maintaining its fine appearance.  ",
	"bear":"black bear skin, a thick, bushy, coarse-haired fur.  ",
	"canvas":"canvas, heavy, coarse, closely woven fabric of hemp and flax, "
	+ "often used in tents and sails.  ",
	"cashmyr":"cashmyr, a soft twilled fabric made of very fine goat's "
	+ "wool from the mountains east of Palanthas.  It is unmatched for "
	+ "its soft feel, rich warmth, and rarity making it very expensive.  ",
	"cotton":"delicately woven Dargaard cotton, a soft, durable, and "
	+ "plentiful cloth that is airy and comfortable.  ",
	"deer":"deerskin, a tough yet supple tanned leather.  ",
	"dupion":"dupion, a cloth of coarse silk noted for its protection "
	+ "from abrasions and resistance to tearing.  Though coarse, the "
	+ "silk is soft and light.  ",
	"elfwyr":"elfwyr, a fabric so light and delicate to the touch that "
	+ "it can hardly be felt when worn.  Elfwyr is the rarest of materials "
	+ "in Palanthas and rarely seen in the possession of any but the "
	+ "elven nobility of a select few reclusive clans.  The secrets of "
	+ "its production are virtually unknown.  ",
	"ermine":"ermine, the unbelievably soft white fur of the northern "
	+ "ermine's winter coat.  It has small black spots spaced out upon "
	+ "it.  ",
	"fox":"fox fur, an indulgently fine, reddish fur.  ",
	"hard":"leather boiled in oil, hardening it into form fitting plates.  ",
	"hide":"rhinocerous hide, a thick, nearly impenetrable hide that is "
	+ "much lighter than metal armour.  ",
	"leather":"leather that is firmer than slow cured soft leather but "
	+ "more flexible than leather hardened in boiling oil.  ",
	"linen":"linen, a stiff, woven cloth often used in formalwear, "
	+ "tablecloths, and sheets.  ",
	"lizard":"stiff, green lizardskin, darker on the back and growing "
	+ "lighter towards the front and down the arms.  ",
	"mink":"mottled white, black, and brown mink fur.  It is incredibly soft "
	+ "and not only looks rich, but feels decadent against your skin.  ",
	"messaline":"messaline, a soft, lightweight silk with a satin weave "
	+ "giving it a slightly glossy reflection in bright light and a shadowy "
	+ "depth in twilight.  ",
	"organdie":"organdie, a fine, translucent cotton delicately woven and "
	+ "commonly used in scarves, light shirts and blouses, and occasionally "
	+ "bathrobes.  Placed over your eyes, you can still see through it "
	+ "somewhat, and when worn, the skin can clearly be seen beneath.  ",
	"rabbit":"soft, white rabbit fur.  ",
	"sable":"deeply rich, black sable fur.  ",
	"silk":"silk, a very light, exceptionally strong, and luxuriously soft "
	+ "cloth woven from the unraveled cocoons of moethes.  ",
	"snake":"smoothly polished, scaly green snakeskin.  ",
	"soft":"This leather is slow cured to be both soft to the touch "
	+ "and protective  .",
	"studded":"leather, expertly cured for a soft feel while remaining "
	+ "highly protective.  Inch diameter studs, their two inch diameter "
	+ "steel plates hidden beneath the leather, stick out every few inches "
	+ "giving the armour strong protections without great weight.  ",
	"suede":"suede, a very soft, textured leather.  Suede must be "
	+ "painstakingly cured and worked to be so desirable.  As such it is "
	+ "expensive.  ",
	"swansdown":"swansdown, a heavy napped, cotton flannel often used by "
	+ "outdoor travellers and highly regarded for its breathe-ability, "
	+ "durability, and silky softness.  It is a specialty of the Dresnos "
	+ "shipping company who keeps their source well guarded.  ",
	"terrycloth":"terrycloth, a pile fabric of cotton with uncut loops on "
	+ "both sides often used to make bath towels and bath robes.  ",
	"wool":"wool, a thick, coarse cloth woven from sheephair.  It is well "
	+ "regarded for its heat retention and comfort when not worn directly "
	+ "upon sensitive skin.  "]);

mapping colour_to_desc = (["black":"black", "white":"white",
	"charcoal":"charcoal", "grey":"grey", "brown":"brown",
	"dark-brown":"dark brown", "beige":"beige", "tan":"tan",
	"mottled-brown":"mottled brown", "crimson":"crimson", "maroon":"maroon", 
	"pink":"pink", "red":"red", "ruby-red":"ruby red", 
	"dark-orange":"dark orange", "orange":"orange",
	"pale-yellow":"pale yellow", "yellow":"yellow",
	"forest-green":"forest green", "dark-green":"dark green", 
	"mottled-green":"mottled green", "olive-green":"olive green", 
	"green":"green", "emerald-green":"emerald green", "blue":"blue",
	"pale-blue":"pale blue", "raven-blue":"raven blue", 
	"sapphire-blue":"sapphire blue", "indigo":"indigo", "violet":"violet", 
	"purple":"purple", "royal-purple":"royal purple",
	"coppery":"coppery", "golden":"golden", "silvery":"silvery"]);

mapping colour_to_full = (["black":"black", "white":"white",
	"charcoal":"charcoal", "grey":"grey", "brown":"brown",
	"dark-brown":"dark brown", "beige":"beige", "tan":"tan",
	"mottled-brown":"mottled brown", "crimson":"crimson", "maroon":"maroon", 
	"pink":"pink", "red":"red", "ruby-red":"ruby red", 
	"dark-orange":"dark orange", "orange":"orange",
	"pale-yellow":"pale yellow", "yellow":"yellow",
	"forest-green":"forest green", "dark-green":"dark green", 
	"mottled-green":"mottled green", "olive-green":"olive green", 
	"green":"green", "emerald-green":"emerald green", "blue":"blue",
	"pale-blue":"pale blue", "raven-blue":"raven blue", 
	"sapphire-blue":"sapphire blue", "indigo":"indigo", "violet":"violet", 
	"purple":"purple", "royal-purple":"royal purple",
	"coppery":"a reflective coppery hue", "golden":"a gleaming golden hue",
	"silvery":"a lustrous silver hue"]);

mapping custom_to_desc = (["alluring":"with an alluring cut",
	"buckled":"with buckles to secure it in place",
	"buttoned":"with buttons down its front",
	"comfortable":"with expert fitting and padding to be exceptionally "
	+ "comfort",
	"common":"in the plain style frequently seen among working commoners",
	"dainty":"with dainty styling",
	"dark":"with texturing to be darker than usual",
	"delicate":"with delicate styling",
	"elegant":"in an elegant, clean cut style reminiscent of the old city",
	"enchanting":"with attractive, well tailored lines once only seen "
	+ "on the very rich or noble",
	"formal":"with a high collar and very formal cut",
	"glistening":"with a well polished, glistening sheen",
	"heavy":"with a thick inner lining of extra material",
	"hot":"to be edgy, stylish, and very sexy",
	"jaunty":"with sporty styling for a swift look",
	"laced":"with tied laces down its front",
	"light":"with efficient styling to be a little lighter than normal",
	"long":"with a little extra material to be longer than normal, nearly "
	+ "touching the ground",
	"loose":"in a stylish cut to be worn loosely",
	"noble":"in a formal yet elegant style common among the nobility",
	"open-toed":"with no front material covering the toes",
	"ornate":"with an arcane series of swirling, black stitching down its "
	+ "edges that curl ornately at their ends",
	"padded":"with soft padding for silence and comfort",
	"plain":"to be simple and functional",
	"quiet":"with soft padding to be quiet and comfortable",
	"rugged":"with extra material in a more rugged style for durability",
	"sensual":"with soft, sensual curves and styling",
	"sensuous":"with soft, sensuous curves and styling",
	"shiny":"with a well polished, shining sheen",
	"short":"with a little less material to be shorter than normal, only "
	+ "coming down past the knees",
	"silent":"with soft padding to be silent and comfortable",
	"skin-tight":"to lay perfectly tight, preferably right against the skin, "
	+ "in a custom fit achieved only by skilled cobblers.  It is lined with "
	+ "ultra-thin and luxurious elfwyr for exceptional comfort and follows "
	+ "every curve of your foot",
	"soft":"in a texture softer than normal",
	"sparkling":"with a well polished, sparkling sheen",
	"steel-toed":"with steel reinforcement inside around the toes to keep "
	+ "them from being crushed",
	"steel-tipped":"with polished steel reinforcement outside at the toe "
	+ "for crush protection and kicking power",
	"strapped":"with sturdy straps to keep it in place",
	"sturdy":"with extra material in a sturdier style for durability",
	"supple":"to be especially supple for its material, allowing its wielder "
	+ "full grace in movement and practically no hinderance in "
	+ "maneuverability", 
	"thick":"with particularly thick material",
	"thin":"with a somewhat thinner material",
	"tight":"to fit snugly against your body",
	"translucent":"with translucent material and is very revealing",
	"unbuttoned":"with buttons down the front that are undone and revealing",
	"unlaced":"with laces down its front that have been undone.  It is "
	+ "alluringly revealing"]);

mapping custom_to_short = (["alluring":"alluring ",
	"buckled":"buckled ",
	"buttoned":"buttoned ",
	"comfortable":"comfortable ",
	"common":"common ",
	"dainty":"dainty ",
	"dark":"dark ",
	"delicate":"delicate ",
	"elegant":"elegant ",
	"enchanting":"enchanting ",
	"formal":"formal ",
	"glistening":"glistening ",
	"heavy":"heavy ",
	"hot":"hot ",
	"jaunty":"jaunty ",
	"laced":"laced ",
	"light":"light ",
	"long":"long ",
	"loose":"loose ",
	"noble":"noble ",
	"open-toed":"open-toed ",
	"ornate":"ornate ",
	"padded":"padded ",
	"plain":"",
	"quiet":"quiet ",
	"rugged":"rugged ",
	"sensual":"sensual ",
	"sensuous":"sensuous ",
	"shiny":"shiny ",
	"short":"short ",
	"silent":"silent ",
	"skin-tight":"skin-tight ",
	"soft":"soft ",
	"sparkling":"sparkling ",
	"steel-toed":"steel-toed ",
	"steel-tipped":"steel-tipped ",
	"strapped":"strapped ",
	"sturdy":"sturdy ",
	"supple":"supple ", 
	"thick":"thick ",
	"thin":"thin ",
	"tight":"tight ",
	"translucent":"translucent ",
	"unbuttoned":"unbuttoned ",
	"unlaced":"unlaced "]);

mapping mat_to_sound = (["alligator":"creaking firmly",
	"arrasene":"flowing silently",
	"cashmyr":"swishing silently",
	"cotton":"rustling quietly",
	"dupion":"swishing quietly",
	"elfwyr":"fluttering silently",
	"ermine":"rustling softly",
	"fox":"rustling softly",
	"linen":"rustling stiffly",
	"lizard":"creaking stiffly",
	"mink":"rustling softly",
	"messaline":"rustling silently",
	"organdie":"flowing silently",
	"sable":"rustling softly",
	"silk":"flowing silently",
	"snake":"creaking in a supple manner",
	"suede":"rustling quietly",
	"swansdown":"flowing silently",
	"wool":"rustling quietly",
	"hard":"creaking tightly",
	"hide":"creaking stiffly",
	"leather":"creaking firmly",
	"soft":"creaking softly",
	"studded":"creaking menacingly",
	"suede":"rustling quietly"]);

mapping mat_to_full = (["alligator":"alligator",
	"arrasene":"arrasene",
	"bear":"bear",
	"canvas":"canvas",
	"cashmyr":"cashmyr",
	"cotton":"cotton",
	"deer":"deerskin",
	"dupion":"dupion",
	"elfwyr":"elfwyr",
	"ermine":"ermine",
	"fox":"fox fur",
	"hard":"hard leather",
	"hide":"hide",
	"leather":"leather",
	"linen":"linen",
	"lizard":"lizardskin",
	"mink":"mink",
	"messaline":"messaline",
	"organdie":"organdie",
	"rabbit":"rabbit fur",
	"sable":"sable",
	"silk":"silk",
	"snake":"snakeskin",
	"soft":"soft leather",
	"studded":"studded leather",
	"suede":"suede",
	"swansdown":"swansdown",
	"terrycloth":"terrycloth",
	"wool":"wool"]);


void
create_armour()
{
	set_at(A_FEET);
    
}

void
set_footwear_data(string data)
{
    seteuid(getuid());

    string* txt = explode(data,"&&");
    cus = txt[0];
    col = txt[1];
    mat = txt[2];
    art = txt[3];
	value = adjust_value();

	artmore = name_to_desc[art];
	ndesc2 = name_to_desc2[art];
	nameshort = name_to_short[art];
	matlong = mat_to_desc[mat];
	matfull = mat_to_full[mat];
	soundmore = mat_to_sound[mat];
	collong = colour_to_desc[col];
	colmore = colour_to_full[col];
	cusmore = custom_to_desc[cus];
	cusshort = custom_to_short[cus];
	weight = adjust_weight();
	volume = adjust_volume();

	recover_string = data;

	set_the_ac();
	set_am(({0, -1, 1}));

	add_prop(OBJ_I_VALUE, value);
 	add_prop(OBJ_I_WEIGHT, weight);
	add_prop(OBJ_I_VOLUME, volume);


	set_name(art);
	add_adj(cus);
    add_adj(col);
	add_adj(mat);
	// Generic to all armours:
	add_name("pair");
	add_pname("pairs");
	add_adj("lurr");
	add_some_names();
	set_keep(1);

	set_short(cusshort + collong + " pair of " + matfull + " " + nameshort);
	set_pshort(cusshort + collong + " pairs of " + matfull + " " + nameshort);
    set_long("Cobbled in the latest style with noticeable quality, this "
	+ ndesc2 + " has been crafted from " + matlong + "The " + artmore
	+ " has been dyed " + colmore + " and finished " + cusmore
	+ ".  Stamped on the bottom of the " + artmore + " is a small stamp.\n");
}

void
add_some_names()
{
	if (col == "dark-brown")
		add_adj(({"dark", "brown"}));
	if (col == "mottled-brown")
		add_adj(({"mottled", "brown"}));
	if (col == "ruby-red")
		add_adj(({"ruby", "red"}));
	if (col == "dark-orange")
		add_adj(({"dark", "orange"}));
	if (col == "pale-yellow")
		add_adj(({"pale", "yellow"}));
	if (col == "forest-green")
		add_adj(({"forest", "green"}));
	if (col == "dark-green")
		add_adj(({"dark", "green"}));
	if (col == "mottled-green")
		add_adj(({"mottled", "green"}));
	if (col == "olive-green")
		add_adj(({"olive", "green"}));
	if (col == "emerald-green")
		add_adj(({"emerald", "green"}));
	if (col == "pale-blue")
		add_adj(({"pale", "blue"}));
	if (col == "raven-blue")
		add_adj(({"raven", "blue"}));
	if (col == "sapphire-blue")
		add_adj(({"sapphire", "blue"}));
	if (cus == "royal-purple")
		add_adj(({"royal", "purple"}));

	if (mat == "hard")
		add_adj("leather");
	if (mat == "soft")
		add_adj("leather");
	if (mat == "studded")
		add_adj("leather");
	if (mat == "fox")
		add_adj("fur");
	if (mat == "rabbit")
		add_adj("fur");
	if (mat == "sable")
		add_adj("fur");
	if (mat == "mink")
		add_adj("fur");
	if (mat == "ermine")
		add_adj("fur");
	if (mat == "deer")
		add_adj(({"deerskin", "skin"}));
	if (mat == "bear")
		add_adj(({"bearskin", "skin"}));
	if (mat == "lizard")
		add_adj(({"lizardskin", "skin"}));
	if (mat == "snake")
		add_adj(({"snakeskin", "skin"}));
	return;
}

int
adjust_value()
{
    int price, mfactor, afactor;

	if (IN_ARRAY(art, ({"boots"})))
	{ afactor = 4; }

	if (IN_ARRAY(art, ({"shoes", "high-heels"})))
	{ afactor = 3; }

	if (IN_ARRAY(art, ({"sandals", "slippers"})))
	{ afactor = 2; }

	if (IN_ARRAY(mat, ({"canvas", "cotton", "linen", "organdie", 
		"terrycloth", "wool"})))
	{ mfactor = 3; }

	if (IN_ARRAY(mat, ({"hard", "hide", "leather", "soft", "studded"})))
	{ mfactor = 4; }

	if (IN_ARRAY(mat, ({"arrasene", "bear", "deer", "dupion", "suede", "silk",
		"messaline", "snake", "lizard", "alligator", "rabbit"})))
	{ mfactor = 5; }

	if (IN_ARRAY(mat, ({"cashmyr", "swansdown"})))
	{ mfactor = 9; }

	if (IN_ARRAY(mat, ({"fox", "sable", "mink", "ermine"})))
	{ mfactor = 12; }

	if (IN_ARRAY(mat, ({"elfwyr"})))
	{ mfactor = 18; }

	price = 1 + afactor * mfactor * 40;
    return price / 2 - 10 + random(20); 
}

int
adjust_weight()
{
    int the_weight, mfactor, afactor;

	if (IN_ARRAY(art, ({"boots"})))
	{ afactor = 4; }

	if (IN_ARRAY(art, ({"shoes", "sandals"})))
	{ afactor = 3; }

	if (IN_ARRAY(art, ({"slippers", "high-heels"})))
	{ afactor = 2; }


	if (IN_ARRAY(mat, ({"hard", "hide", "leather", "soft", "studded", "suede",
		"lizard", "deer", "canvas", "bear", "alligator"})))
	{ mfactor = 8; }

	if (IN_ARRAY(mat, ({"terrycloth", "wool", "fox", "sable", "mink", 
		"ermine", "rabbit"})))
	{ mfactor = 6; }

	if (IN_ARRAY(mat, ({"linen", "cashmyr", "swansdown", "snake"})))
	{ mfactor = 5; }

	if (IN_ARRAY(mat, ({"cotton"})))
	{ mfactor = 3; }

	if (IN_ARRAY(mat, ({"silk", "messaline", "organdie", "arrasene", 
		"dupion"})))
	{ mfactor = 2; }

	if (IN_ARRAY(mat, ({"elfwyr"})))
	{ mfactor = 1; }

	the_weight = 1 + afactor * mfactor * 25 + random(20);
    return the_weight; 
}

int
adjust_volume()
{
    int the_vol;

	if (IN_ARRAY(art, ({"boots"})))
	{ the_vol = 450 + random(100); }

	if (IN_ARRAY(art, ({"shoes", "slippers"})))
	{ the_vol = 325 + random(75); }

	if (IN_ARRAY(art, ({"sandals", "high-heels"})))
	{ the_vol = 275 + random(50); }

    return the_vol; 
}

int
set_the_ac()
{
	int the_ac;

	if (IN_ARRAY(art, ({"boots"})))
	{ the_ac = 24; }

	if (IN_ARRAY(art, ({"shoes", "slippers"})))
	{ the_ac = 21; }

	if (IN_ARRAY(art, ({"high-heels", "sandals"})))
	{ the_ac = 18; }

	set_ac(the_ac);
	return 1;
}

void
init()
{
    ::init();
	ADA("pose");
	ADA("help");

	ADD("exa_stamp", "exa");
	ADD("exa_stamp", "examine");
}

int exa_stamp(string arg)
{
	if (strlen(arg) && !parse_command(arg, ({}), "[the] [small] [circular] 'stamp' "))
    {
        return 0; // the player used syntax we don't agree with 
    }
	
	write("Stamped on the bottom of the " + artmore + " is a small, "
	+ "circular symbol of three diagonal stripes above \"PALANTHAS\" written "
	+ "in the old style.  Try <help lurr>.\n");
	return 1;
}

/* New emote 'pose' for anyone wearing one of these armours.
 */
int pose(string str)
{
	string *how;
	how = parse_adverb_with_space(str, "magnificently", 0);

	if (TO->query_worn())
	{
		write("With hands on hips you pose" + how[1] + " in your " + artmore
		+ ", their " + cusshort + colmore + " " + matfull + " " + soundmore
		+ ".\n");
		say("With hands on hips " + QTNAME(TP) + " poses" + how[1] + " in "
		+ HIS(TP) + " " + artmore + ", their " + cusshort + colmore + " " 
		+ matfull + " " + soundmore	+ ".\n");
		return 1;
	}
	return 0;
}

int
help(string str)
{
	if (!str || str != "lurr")
		return 0;

	write("You may do the following in your Lurr Bramous footwear:\n"
	+ "pose <adj>                 - Strike a pose in your lurr footwear.\n"
	+ "\n");
	return 1;
}

string
arm_condition_desc()
{
    string str;

    if (query_prop(OBJ_I_BROKEN))
        return "It has been shredded to pieces.\n";

    switch(condition - repair)
    {
        case 0:
            str = "is in pristine condition";
            break;
        case 1:
        case 2:
            str = "is a little disheveled";
            break;
        case 3:
        case 4:
            str = "has ripped in a few places";
            break;
        case 5:
        case 6:
        case 7:
            str = "is torn up badly";
            break;
        default:
            str = "has almost been torn to shreds";
            break;
    }

    return "It looks like it " + str + ".\n";
}

/* For crafted armour base */
void
set_armour_data(string str)
{
    set_footwear_data(str);
}

