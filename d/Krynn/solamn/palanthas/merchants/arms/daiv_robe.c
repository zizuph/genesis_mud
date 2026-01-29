/* 
 * Mortis 04.2006
 *
 * This is the armour base for the robes & coats Daiv Temasis
 * crafts in the Merchants quarter of Palanthas.
 *
 */

inherit "/d/Krynn/solamn/palanthas/obj/crafted_armour";
inherit "/lib/commands";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include "../../local.h"

#define HAVE_LINER			"_i_have_a_daronius_liner"
#define LINERABLE			"_i_can_receive_a_daronius_liner"


int value;
string cus, col, mat, art, cusmore, colmore,
	matlong, collong, artmore, soundmore, ndesc2, cusshort, linermod,
	lincus, lincol, linmat;

/* Prototypes */
void add_some_names();
int adjust_value();
int set_the_ac();
int add_liner_long(string lcus, string lcol, string lmat);

mapping name_to_desc = (["robe":"robe", "coat":"coat"]);

mapping name_to_desc2 = (["robe":"robe flows ebulliently about you as if in "
	+ "a breeze and ",
	"coat":"fits elegantly upon you and "]);

mapping mat_to_desc = (["alligator":"alligator skin, its dark, emerald plates "
	+ "firm but supple and polished smooth.  ",
	"arrasene":"arrasene, a smooth cloth woven from wool and silk giving it "
	+ "great durability and warmth while maintaining its fine appearance.  ",
	"cashmyr":"cashmyr, a soft twilled fabric made of very fine goat's "
	+ "wool from the mountains east of Palanthas.  It is unmatched for "
	+ "its soft feel, rich warmth, and rarity making it very expensive.  ",
	"cotton":"delicately woven Dargaard cotton, a soft, durable, and "
	+ "plentiful cloth that is airy and comfortable.  ",
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
	"linen":"linen, a stiff, woven cloth often used in formalwear, "
	+ "tablecloths, and sheets.  ",
	"lizard":"stiff, green lizard skin, darker on the back and growing "
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
	"snake":"smoothly polished, scaly green snake skin.  ",
	"suede":"suede, a very soft, textured leather.  Suede must be "
	+ "painstakingly cured and worked to be so desirable.  As such it is "
	+ "expensive.  ",
	"swansdown":"swansdown, a heavy napped, cotton flannel often used by "
	+ "outdoor travellers and highly regarded for its breathe-ability, "
	+ "durability, and silky softness.  It is a specialty of the Dresnos "
	+ "shipping company who keeps their source well guarded.  ",
	"wool":"wool, a thick, coarse cloth woven from sheephair.  It is well "
	+ "regarded for its heat retention and comfort when not worn directly "
	+ "upon sensitive skin.  "]);

mapping colour_to_desc = (["black":"black", "white":"white",
	"charcoal":"charcoal", "grey":"grey", "brown":"brown",
	"dark-brown":"dark brown", "beige":"beige", "tan":"tan",
	"crimson":"crimson", "maroon":"maroon", "pink":"pink",
	"dark-orange":"dark orange", "orange":"orange",
	"pale-yellow":"pale yellow", "yellow":"yellow",
	"forest-green":"forest green", "dark-green":"dark green", "blue":"blue",
	"pale-blue":"pale blue", "raven-blue":"raven blue", "indigo":"indigo",
	"purple":"purple", "royal-purple":"royal purple",
	"coppery":"coppery", "golden":"golden", "silvery":"silvery"]);

mapping colour_to_full = (["black":"black", "white":"white",
	"charcoal":"charcoal", "grey":"grey", "brown":"brown",
	"dark-brown":"dark brown", "beige":"beige", "tan":"tan",
	"crimson":"crimson", "maroon":"maroon", "pink":"pink",
	"dark-orange":"dark orange", "orange":"orange",
	"pale-yellow":"pale yellow", "yellow":"yellow",
	"forest-green":"forest green", "dark-green":"dark green", "blue":"blue",
	"pale-blue":"pale blue", "raven-blue":"raven blue", "indigo":"indigo",
	"purple":"purple", "royal-purple":"royal purple",
"coppery":"reflective coppery hue", "golden":"gleaming golden hue",
"silvery":"lustrous silver hue"]);

mapping custom_to_desc = (["billowing":"with stylized edges to billow in the "
	+ "wind",
	"buttoned":"with buttons down its front",
	"dark":"with texturing to be darker than usual",
	"formal":"with a high collar and very formal cut",
	"heavy":"with a thick inner lining of extra material",
	"laced":"with tied laces down its front",
	"light":"with efficient styling to be a little lighter than normal",
	"long":"with a little extra material to be longer than normal, nearly "
	+ "touching the ground",
	"loose":"in a stylish cut to be worn loosely",
	"noble":"in a formal yet elegant style common among the nobility",
	"ornate":"with an arcane series of swirling, black stitching down its "
	+ "edges that curl ornately at their ends",
	"plain":"to be simple and functional",
	"short":"with a little less material to be shorter than normal, only "
	+ "coming down past the knees",
	"soft":"in a texture softer than normal",
	"thick":"with particularly thick material",
	"thin":"with a somewhat thinner material",
	"translucent":"with translucent material and is very revealing",
	"unbuttoned":"with buttons down the front that are undone and revealing",
	"unlaced":"with laces down its front that have been undone.  It is "
	+ "alluringly revealing"]);

mapping custom_to_short = (["billowing":"billowing ",
	"buttoned":"buttoned ",
	"dark":"dark ",
	"formal":"formal ",
	"heavy":"heavy ",
	"laced":"laced ",
	"light":"light ",
	"long":"long ",
	"loose":"loose ",
	"noble":"noble ",
	"ornate":"ornate ",
	"plain":"",
	"short":"short ",
	"soft":"soft ",
	"thick":"thick ",
	"thin":"thin ",
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
	"wool":"rustling quietly"]);

mapping colour_to_full = (["black":"black", "white":"white",
	"charcoal":"charcoal", "grey":"grey", "brown":"brown",
	"mottled-brown":"mottled brown", "crimson":"crimson", "maroon":"maroon",
	"yellow":"yellow", "forest-green":"forest green",
	"mottled-green":"mottled green", "olive-green":"olive green",
	"blue":"blue", "raven-blue":"raven blue",
	"silvery":"silvery"]);


void
create_armour()
{
	set_at(A_ROBE);
    
 	add_prop(OBJ_I_WEIGHT, 700 + random(201));
	add_prop(OBJ_I_VOLUME, 650 + random(176));
}

void
set_armour_data(string data)
{
    seteuid(getuid());

    string* txt = explode(data,"&&");
    cus = txt[0];
    col = txt[1];
    mat = txt[2];
    art = txt[3];
	linermod = txt[4];
	value = adjust_value();
    lincus = txt[5];
    lincol = txt[6];
    linmat = txt[7];

	artmore = name_to_desc[art];
	ndesc2 = name_to_desc2[art];
	matlong = mat_to_desc[mat];
	soundmore = mat_to_sound[mat];
	collong = colour_to_desc[col];
	colmore = colour_to_full[col];
	cusmore = custom_to_desc[cus];
	cusshort = custom_to_short[cus];

	recover_string = data;

	set_the_ac();
	set_am(({0, -1, 1}));

	add_prop(OBJ_I_VALUE, value);
	add_prop(LINERABLE, 1);

	set_name(art);
	add_adj(cus);
    add_adj(col);
	add_adj(mat);
	// Generic to all armours:
	add_adj("daiv");
	add_some_names();
	set_keep(1);

	set_short(cusshort + collong + " " + mat + " " + name_to_desc[art]);
    set_long("Finished in the latest style with grand quality, this "
	+ artmore + " has been crafted from " + matlong + "The " + ndesc2
	+ "has been dyed " + colmore + " and finished " + cusmore
	+ ".  Sewn inside the " + art + "'s collar is a small logo.\n");

	add_liner_long(lincus, lincol, linmat);
}

void
add_some_names()
{
	if (col == "dark-brown")
		add_adj(({"dark", "brown"}));
	if (col == "dark-orange")
		add_adj(({"dark", "orange"}));
	if (col == "pale-yellow")
		add_adj(({"pale", "yellow"}));
	if (col == "forest-green")
		add_adj(({"forest", "green"}));
	if (col == "dark-green")
		add_adj(({"dark", "green"}));
	if (col == "pale-blue")
		add_adj(({"pale", "blue"}));
	if (col == "raven-blue")
		add_adj(({"raven", "blue"}));
	if (cus == "royal-purple")
		add_adj(({"royal", "purple"}));
	return;
}

int
adjust_value()
{
    int price, mfactor, afactor;

	if (IN_ARRAY(art, ({"robe"})))
	{ afactor = 4; }

	if (IN_ARRAY(art, ({"coat"})))
	{ afactor = 3; }

	if (IN_ARRAY(mat, ({"cotton", "linen", "organdie", "wool"})))
	{ mfactor = 3; }

	if (IN_ARRAY(mat, ({"arrasene", "dupion", "suede", "silk",
		"messaline", "snake", "lizard", "alligator", "rabbit"})))
	{ mfactor = 5; }

	if (IN_ARRAY(mat, ({"cashmyr", "swansdown"})))
	{ mfactor = 9; }

	if (IN_ARRAY(mat, ({"fox", "sable", "mink", "ermine"})))
	{ mfactor = 12; }

	if (IN_ARRAY(mat, ({"elfwyr"})))
	{ mfactor = 18; }

	price = 1 + afactor * mfactor * 150;
    return price / 2 - 10 + random(20); 
}

int
set_the_ac()
{
	if (linermod == "on" || TO->query_prop(HAVE_LINER) == "on")
	{
		add_prop(HAVE_LINER, "on");
		recover_string = cus + "&&" + col + "&&" + mat + "&&" + art + "&&"
						 + "on";
		set_ac(15);
		return 1;
	}
	set_ac(7);
	return 1;
}

int
add_liner_long(string lcus, string lcol, string lmat)
{
	if (TO->query_prop(HAVE_LINER) == "on")
	{
		set_long(query_long() + "It has been lined with " + lcus + lcol
		+ " " + lmat + " for added protection.\n");
		recover_string = cus + "&&" + col + "&&" + mat + "&&" + art + "&&"
						 + "on" + "&&" + lcus + "&&" + lcol + "&&" + lmat;
		return 1;
	}
	return 1;
}

void
init()
{
    ::init();
    ADA("bow");
	ADA("curtsey");
	ADA("fart");
	ADA("pose");
	ADA("stretch");
	ADA("help");

	ADD("exa_logo", "exa");
	ADD("exa_logo", "examine");
}

int exa_logo(string arg)
{
	if (strlen(arg) && !parse_command(arg, ({}), "[the] [small] 'logo' "))
    {
        return 0; // the player used syntax we don't agree with 
    }
	
	write("Sewn inside the collar is the Temasis logo, a maroon robe blowing "
	+ "in a breeze upon a brown shield.  Try <help daiv>.\n");
	return 1;
}

/* Overriding emote 'bow' while wearing certain articles.
 */
int bow(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "gloriously", 0);
	oblist = parse_this(how[0], "[to] %l");

	if (TO->query_worn() && IN_ARRAY(art, ({"robe", "coat"})))
	{
		if (!sizeof(oblist))
		{ 
			write("You bow" + how[1] + ", the " + cusshort + mat
			+ " of your " + colmore + " " + artmore + " " + soundmore
			+ ".\n");
			allbb(" bows" + how[1] + ", the " + cusshort + mat
			+ " of " + HIS(TP) + " " + colmore + " " + artmore + " "
			+ soundmore + ".");
			return 1;
		}

		actor("You bow to", oblist, how[1] + ", the " + cusshort
		+ mat + " of your " + colmore + " " + artmore + " " + soundmore
		+ ".");
		target(" bows to you" + how[1] + ", the " + cusshort + mat
		+ " of " + HIS(TP) + " " + colmore + " " + artmore + " " + soundmore
		+ ".", oblist);
		all2act(" bows to", oblist, how[1] + ", the " + cusshort
		+ mat + " of " + HIS(TP) + " " + colmore + " " + artmore + " "
		+ soundmore + "."); 
		return 1;
	}
	return 0;
}

/* Overriding emote 'curtsey' for anyone wearing a certain article.
 */
int curtsey(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "elegantly", 0);
	oblist = parse_this(how[0], "[to] %l");

	if (TO->query_worn() && IN_ARRAY(art, ({"robe", "coat"})))
	{
		if (!sizeof(oblist))
		{ 
			write("You curtsey" + how[1] + ", the " + cusshort
			+ mat + " of your " + colmore + " " + artmore + " "
			+ soundmore + ".\n");
			allbb(" curtseys" + how[1] + ", the " + cusshort
			+ mat + " of " + HIS(TP) + " " + colmore + " " + artmore
			+ " " + soundmore + ".");
			return 1;
		}

		actor("You curtsey to", oblist, how[1] + ", the " + cusshort
		+ mat + " of your " + colmore + " " + artmore + " " + soundmore
		+ ".");
		target(" curtseys to you" + how[1] + ", the " + cusshort
		+ mat + " of " + HIS(TP) + " " + colmore + " " + artmore + " "
		+ soundmore + ".", oblist);
		all2act(" curtseys to", oblist, how[1] + ", the " + cusshort
		+ mat + " of " + HIS(TP) + " " + colmore + " " + artmore + " "
		+ soundmore + "."); 
		return 1;
	}
	return 0;
}

/* Overriding emote for 'fart'.  If a harsh race + pants, hole is blown out
 * the seat of the pants.  If it's dress-like, billows out.  Both stink.
 * Also adds to the short and long when blown out.
 */
int fart()
{
	string oshort = short();

  if (TO->query_worn())
  {
	if (IN_ARRAY(art, ({"robe", "coat"})))
	{
		write("You look around hoping no one's looking as you try to "
		+ "quietly let out a large fart you've let build up.\n"
		+ "The back of your " + oshort + " billows out conspicuously.\n");
		say(QCTNAME(TP) + " looks around and, confident no one is watching, "
		+ "lets out a fart accompanied by a squelchy, squeaking noise.\n"
		+ "The back of " + HIS(TP) + " " + oshort + " billows out "
		+ "conspicuously.\n");
		return 1;
	}

	  return 0;
  }
	return 0;
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
		+ ", its " + cusshort + colmore + " " + mat + " " + soundmore
		+ ".\n");
		say("With hands on hips " + QTNAME(TP) + " poses" + how[1] + " in "
		+ HIS(TP) + " " + artmore + ", its " + cusshort + collong + " " 
		+ mat + " " + soundmore	+ "\n.");
		return 1;
	}
	return 0;
}

/* Overriding emote 'stretch' for anyone wearing these armours.
 */
int stretch(string str)
{
	string *how;
/*	string bod = TP->query_prop(WEIGHTDESC);  If anyone ever makes someone's
	width bloody queryable, this can be uncommented and string bod used to
	describe someone's body in this emote. */
	string bod = "timeworn";
	how = parse_adverb_with_space(str, one_of_list(({"osmodiusly",
		"retandently"})), 0);

	if (TO->query_worn())
	{
		write("You stretch your " + bod + " body out" + how[1] + " in your "
		+ artmore + ", its " + cusshort + colmore + " " + mat + " "
		+ soundmore + ".\n");
		say(QCTNAME(TP) + " stretches " + HIS(TP) + " " + bod + " body out"
		+ how[1] + " in " + HIS(TP) + " " + artmore + ", its " + cusshort
		+ colmore + " " + mat + " " + soundmore	+ ".\n");
		return 1;
	}
	return 0;
}

int
help(string str)
{
	if (!str || str != "daiv")
		return 0;

	write("You may do the following in your Daiv Temasis robes and coats:\n"
	+ "bow <adj> to <person>      - Perform a bow in your robe.\n"
	+ "curtsey <adj> to <person>  - Curtsey in your robe.\n"
	+ "fart                       - Completely harmless.  Please try.\n"
	+ "pose <adj>                 - Strike a pose in your Daiv armour.\n"
	+ "stretch <adj>              - Stretch it out.\n"
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

