/* Mortis 12.2005
 *
 * This is the armour base for the clothing Dienya the
 * fine clothing tailor in the Plaisir district of
 * Palanthas makes.
 *
 * Maybe checkered and striped in custom_to_desc can use one_of_list.
 *
 * Could add props to clothes setting the orderer's size on creation
 * then check in the wear routine if the wearer fits inside them.
 *
 * dance gown+
 * kilt, men only, reveal no undies
 * stockings to ankle?
 *
 * 10.2014 - Added Terellian Silver Forest cold protection to fur-trimmed
 * armours based on original plans and approval to do so with Udana who
 * coded Silver Forest and introduced cold system.
 *
 * 2020-12-22 - Cotillion 
 * - Fixed armour recovery
 */


inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../../local.h"

#define MY_OWNER_NAME		"_my_owner_name"
#define MY_MAT_NAME			"_my_mat_name"
#define MY_COL_NAME			"_my_col_name"
#define MY_CUS_NAME			"_my_cus_name"
#define I_M_WEARING_IT		"_i_m_wearing_it"
#define TEREL_COLD           "_obj_cold_weather_protect"

int blown = 0;
int soiled = 0;
int adjust_weight();
string adjust_tailoredadj(string cus);
string cus, col, mat, art, me_who, for_who, recover_string, cusshort;
void add_some_names();


/* Prototypes */
string name_desc();
string material_desc();
string colour_desc();
string custom_desc();

mapping name_to_class = (["bathrobe":A_ROBE, "vest":A_ROBE,
	"dress":A_BODY | A_ARMS | A_LEGS, "frock":A_BODY | A_ARMS | A_LEGS,
	"gown":A_BODY | A_ARMS | A_LEGS, "muumuu":A_BODY | A_ARMS | A_LEGS,
	"shift":A_BODY | A_ARMS | A_LEGS, "baggy-pants":A_LEGS,
	"capris":A_LEGS, "kilt":A_LEGS, "lederhosen":A_LEGS,
	"pantaloons":A_LEGS, "pants":A_LEGS, "skirt":A_LEGS,
	"slacks":A_LEGS, "stockings":A_LEGS, "bodice":A_BODY,
	"blouse":A_BODY, "puffy-shirt":A_BODY, "pullover":A_BODY,
	"shirt":A_BODY,"sleeveless-shirt":A_BODY, "sweater":A_BODY,
	"gloves":A_HANDS, "long-gloves":A_HANDS | A_ARMS,
	"scarf":A_NECK]);

mapping name_to_desc = (["bathrobe":"bathrobe", "vest":"vest",
	"dress":"dress", "frock":"frock",
	"gown":"gown", "muumuu":"muumuu",
	"shift":"shift", "baggy-pants":"pair of baggy pants",
	"capris":"pair of capris", "kilt":"kilt",
	"lederhosen":"pair of lederhosen",
	"pantaloons":"pair of pantaloons", "pants":"pair of pants",
	"skirt":"skirt",
	"slacks":"pair of slacks", "stockings":"pair of stockings",
	"bodice":"bodice",
	"blouse":"blouse", "puffy-shirt":"puffy shirt", "pullover":"pullover",
	"shirt":"shirt", "sleeveless-shirt":"sleeveless shirt",
	"sweater":"sweater",
	"gloves":"pair of gloves", "long-gloves":"pair of long gloves",
	"scarf":"scarf"]);

mapping mat_to_desc = (["arrasene":"arrasene, a smooth cloth woven from "
	+ "wool and silk giving it great durability and warmth while "
	+ "maintaining its fine appearance.  ",
	"burlap":"burlap, a very cheap, rough, yet somewhat sturdy cloth "
	+ "more commonly seen in sacks than clothing.  Why such a highly "
	+ "regarded tailor would work with such a material may only be "
	+ "explained by her sense of humour.  ",
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
	"hemp":"hemp, a plant whose fibrous roots and stems can be woven "
	+ "into nearly unrippable cloth and remarkably strong rope.  It is "
	+ "firm and not particularly uncomfortably.  ",
	"leather":"leather that is firmer than slow cured soft leather but "
	+ "more flexible than leather hardened in boiling oil.  ",
	"linen":"linen, a stiff, woven cloth often used in formalwear, "
	+ "tablecloths, and sheets.  ",
	"organdie":"organdie, a fine, translucent cotton delicately woven and "
	+ "commonly used in scarves, light shirts and blouses, and occasionally "
	+ "bathrobes.  Placed over your eyes, you can still see through it "
	+ "somewhat, and when worn, the skin can clearly be seen beneath.  ",
	"messaline":"messaline, a soft, lightweight silk with a satin weave "
	+ "giving it a slightly glossy reflection in bright light and a shadowy "
	+ "depth in twilight.  ",
	"sackcloth":" sackcloth, a very cheap, rough material that almost "
	+ "rips by itself.  Why such a highly regarded tailor would work with "
	+ "such a material may only be explained by her sense of humour.  Why "
	+ "someone would order it is even more of a mystery.  ",
	"silk":"silk, a very light, exceptionally strong, and luxuriously soft "
	+ "cloth woven from the unraveled cocoons of moethes.  ",
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
	"crimson":"crimson", "maroon":"maroon", "pink":"pink",
	"dark-orange":"dark orange", "orange":"orange",
	"pale-yellow":"pale yellow", "yellow":"yellow",
	"forest-green":"forest green", "dark-green":"dark green", "blue":"blue",
	"pale-blue":"pale blue", "raven-blue":"raven blue", "indigo":"indigo",
	"purple":"purple", "royal-purple":"royal purple", "charcoal":"charcoal",
	"grey":"grey", "brown":"brown", "dark-brown":"dark brown",
	"beige":"beige", "tan":"tan", "coppery":"a glossy, copper hue",
	"silvery":"a gleaming silver hue", "golden":"in a lustrous, golden hue",
	"translucent-white":"a translucent white",	//Dienya only.
	"pale-grey":"a pale grey",	//Dienya only.
	"grey-green":"greyish green"]);	//Dienya only.

mapping custom_to_desc = (["alluring":"with an alluring cut",
	"billowing":"intentionally to billow in the wind",
	"buttoned":"with buttons down its front",
	"checkered":"with a white checkered pattern",
	"cuffed":"with cuffs",
	"custom-fitted":"to be custom fitted to ",
	"debonair":"in an elegant, clean cut style reminiscent of the old city "
	+ "gentlemen",
	"double-breasted":"with a stylish breastpiece that folds across the "
	+ "front where double rows of buttons along the sides fasten it snugly "
	+ "into place", // Phyllis the jeweler's guard
	"enchanting":"with attractive, well tailored lines once only seen "
	+ "on the very rich or noble",
	"formal":"in a classic and very formal cut",
	"fur-trimmed":"with a soft, gray-black fur trimming its edges",
	"gleaming":"with expert cuts that catch the light making it appear "
	+ "as if it glowed itself",
	"heavy":"with extra thick cloth",
	"jaunty":"with a sporty, athletic cut", 
	"knitted":"with custom knitting",
	"laced":"with tied laces down its front",
	"light":"with experienced tailoring to be a little lighter than normal",
	"long":"with a little extra material to be longer than normal",
	"loose":"in a stylish cut to be worn loosely",
	"low-cut":"with a low cut in the front, and is enticingly revealing",
	"noble":"in a formal yet elegant style common among the nobility",
	"paisley":"with curving teardrop shapes done with intricate patterns "
	+ "and embroidery",	// Gui the Vintner
	"plain":"to be simple and functional",
	"pleated":"with some of its material sewn brilliantly over itself at "
	+ "the edges to create a stylish, pleated cut",
	"rugged":"with reinforced seams for extra ruggedness",
	"soft":"in a texture softer than normal",
	"shaded":"stylized cuts to give it a shaded texture especially in low "
	+ "light",
	"sharp":"with edgy cuts so it stands out sharply",
	"short":"with a little less material to be short at the bottom", 
	"striped":"with white stripes",
	"tailored":"with care and patience to perfectly fit ",
	"tassled":"with tassles hanging from its ends",
	"thick":"with particularly thick material",
	"thin":"with a somewhat thinner material",
	"tight":"to fit snugly against the skin",
	"translucent":"with translucent material and is very revealing",
	"unbuttoned":"with buttons down the front that are undone and revealing",
	"unlaced":"with laces down its front that have been undone.  It is "
	+ "alluringly revealing"]);

mapping custom_to_strut = (["alluring":"slowly and appealingly",
	"billowing":"boldly into the wind",
	"buttoned":"primly",
	"checkered":"comically",
	"cuffed":"stylishly",
	"custom-fitted":"fetchingly",
	"debonair":"like a refined and sophisticated gentleperson",
	"double-breasted":"with bold confidence",
	"enchanting":"enamoringly, catching and holding your attention",
	"formal":"in a classic, prim style",
	"fur-trimmed":"luxuriously",
	"gleaming":"glowingly",
	"heavy":"thumpingly along",
	"jaunty":"with a sporty, springy step", 
	"knitted":"nicely",
	"laced":"fashionably",
	"light":"hoppingly",
	"long":"swishingly",
	"loose":"freely",
	"low-cut":"in a revealing, attractive manner",
	"noble":"in a formal yet elegant style",
	"plain":"about",
	"paisley":"in a far out way",
	"pleated":"with refined style",
	"rugged":"confidently",
	"soft":"gently",
	"shaded":"in the edges between shadows and light",
	"sharp":"with refinement",
	"short":"revealingly",
	"sporty":"in a sporty manner",
	"striped":"stripingly",
	"tailored":"comfortably",
	"tassled":"swingingly",
	"thick":"largely",
	"thin":"lightly",
	"tight":"with measured, appealing strides",
	"translucent":"about in a very revealing fashion",
	"unbuttoned":"in a casually revealing style",
	"unlaced":"in an alluringly inviting style"]);

mapping custom_to_short = (["alluring":"alluring ",
	"billowing":"billowing ",
	"buttoned":"buttoned ",
	"checkered":"checkered ",
	"cuffed":"cuffed ",
	"custom-fitted":"custom fitted ",
	"debonair":"debonair ",
	"double-breasted":"double-breasted ",
	"enchanting":"enchanting ",
	"formal":"formal ",
	"fur-trimmed":"fur-trimmed ",
	"gleaming":"gleaming ",
	"heavy":"heavy ",
	"jaunty":"jaunty ", 
	"knitted":"knitted ",
	"laced":"laced ",
	"light":"light ",
	"long":"long ",
	"loose":"loose ",
	"low-cut":"low-cut ",
	"noble":"noble ",
	"plain":"",
	"paisley":"paisley ",
	"pleated":"pleated ",
	"rugged":"rugged ",
	"soft":"soft ",
	"shaded":"shaded ",
	"sharp":"sharp ",
	"short":"short ",
	"sporty":"sporty ",
	"striped":"striped ",
	"tailored":"tailored ",
	"tassled":"tassled ",
	"thick":"thick ",
	"thin":"thin ",
	"tight":"tight ",
	"translucent":"translucent ",
	"unbuttoned":"unbuttoned ",
	"unlaced":"unlaced "]);

void
create_armour()
{
	// seteuid(getuid());  Needed?

	set_ac(6);

    add_prop(OBJ_M_NO_SELL, 1);
}

void
set_armour_data(string data)
{
    seteuid(getuid());

    string* txt = explode(data,"&&");
    for_who = txt[0];
    cus = txt[1];
    col = txt[2];
    mat = txt[3];
    art = txt[4];
	string at = name_to_class[art];
	int weight = adjust_weight();
	string tailoredadj = adjust_tailoredadj(cus);
	me_who = for_who;
	cusshort = custom_to_short[cus];

	add_prop(MY_OWNER_NAME, for_who);
	add_prop(MY_MAT_NAME, mat);
	add_prop(MY_COL_NAME, col);
	add_prop(MY_CUS_NAME, cus);
	add_prop(OBJ_I_WEIGHT, weight);
    add_prop(TEREL_COLD, "@@how_furry"); // +1 Terel Cold prot per body part
    
    set_name(art);
	add_adj(cus);
    add_adj(col);
	add_adj(mat);
	set_short(cusshort + col + " " + mat + " " + art);
    set_long("Tailored with exquisite precision and patient care, this "
	+ "@@name_desc@@" + " has been sewn from " + "@@material_desc@@"
	+ "The " + "@@name_desc@@" + " has been dyed " + "@@colour_desc@@"
	+ " and finished " + "@@custom_desc@@" + ".  Stitched inside the "
	+ art + "'s border is an elfwyr tag.\n");
	set_at(at);
	set_keep(1);

	// Generic to all clothes:
	add_adj(tailoredadj);
	add_some_names();

	recover_string = data;

}

/* Returns +1 point of Terellian Silver Forest cold protection per
 * body part covered if fur-trimmed. */
int
how_furry()
{
    int cprot;

    if (cus != "fur-trimmed")
    { return 0; }

    switch(art)
    {
        case "long-gloves":
            cprot = 2;
            break;
        case "dress":
        case "frock":
        case "gown":
        case "shift":
        case "muumuu":
            cprot = 3;
            break;
        default:
            cprot = 1;
    }
    return cprot;
}

string name_desc()
{
	string ndesc = "";
	string nname = TO->query_name();

	ndesc = name_to_desc[nname];

	return ndesc;
}

string material_desc()
{
	string mdesc = "";
	string mname = TO->query_prop(MY_MAT_NAME);

	mdesc = mat_to_desc[mname];

	return mdesc;
}

string colour_desc()
{
	string cdesc = "";
	string cname = TO->query_prop(MY_COL_NAME);

	cdesc = colour_to_desc[cname];

	return cdesc;
}

string custom_desc() // new its wearer string
{
	string cudesc = "its wearer";
	string cuname = TO->query_prop(MY_CUS_NAME);
	cudesc = custom_to_desc[cuname];

	if (cuname == "tailored" || cuname == "custom-fitted")
	{
		return cudesc + C(me_who);
	}

	return cudesc;
}

int
adjust_weight()
{	
	int afactor, mfactor, weight;

	if (IN_ARRAY(art, ({"bathrobe", "dress", "frock", "gown", "muumuu",
		"shift"})))
	{ afactor = 3; }

	if (IN_ARRAY(art, ({"vest", "baggy-pants", "capris", "kilt",
		"lederhosen", "pantaloons", "pants", "skirt", "slacks",
		"stockings", "bodice", "blouse", "puffy-shirt", "pullover",
		"shirt", "sweater"})))
	{ afactor = 2; }

	if (IN_ARRAY(art, ({"sleeveless-shirt", "gloves", "long-gloves",
		"scarf"})))
	{ afactor = 1; }

	if (IN_ARRAY(mat, ({"burlap", "sackcloth", "hemp"})))
	{ mfactor = 8; }

	if (IN_ARRAY(mat, ({"cotton", "linen", "organdie", "wool"})))
	{ mfactor = 6; }

	if (IN_ARRAY(mat, ({"arrasene", "dupion", "suede", "silk",
		"messaline"})))
	{ mfactor = 4; }

	if (IN_ARRAY(mat, ({"cashmyr", "swansdown"})))
	{ mfactor = 5; }

	if (IN_ARRAY(mat, ({"elfwyr"})))
	{ mfactor = 1; }

	return weight = afactor * mfactor * 25;
}

string
adjust_tailoredadj(string cus)
{
	if (cus == "tailored")
	{
		return "special";
	}
	return "tailored";
}

void
add_some_names()
{
	if (art == "bathrobe")
	{
		add_name("robe");
		add_adj("bath");
	}
	if (art == "baggy-pants")
	{
		add_name("pants");
		add_adj("baggy");
	}
	if (art == "puffy-shirt")
	{
		add_name("shirt");
		add_adj("puffy");
	}
	if (art == "sleeveless-shirt")
	{
		add_name("shirt");
		add_adj("sleeveless");
	}
	if (art == "long-gloves")
	{
		add_name("gloves");
		add_adj("long");
	}
	if (cus == "custom-fitted")
		add_adj(({"custom", "fitted"}));
	if (cus == "low-cut")
		add_adj(({"low", "cut"}));
	if (cus == "dark-orange")
		add_adj(({"dark", "orange"}));
	if (cus == "pale-yellow")
		add_adj(({"pale", "yellow"}));
	if (cus == "forest-green")
		add_adj(({"forest", "green"}));
	if (cus == "dark-green")
		add_adj(({"dark", "green"}));
	if (cus == "pale-blue")
		add_adj(({"pale", "blue"}));
	if (cus == "raven-blue")
		add_adj(({"raven", "blue"}));
	if (cus == "royal-purple")
		add_adj(({"royal", "purple"}));
	if (cus == "dark-brown")
		add_adj(({"dark", "brown"}));
}

void
init()
{
	/* One(?) overriding emote per article. */
    ::init();
    ADA("bow");
	ADA("curtsey");
	ADA("wiggle");
	ADA("strut");
	ADA("gesture");
	ADA("fart");
	ADA("clench");

	ADD("exa_tag", "exa");
	ADD("exa_tag", "examine");
}

int exa_tag(string arg)
{
	string whose = TO->query_prop(MY_OWNER_NAME);

	if (strlen(arg) && !parse_command(arg, ({}), "[the] [elfwyr] 'tag' "))
    {
        return 0; // the player used syntax we don't agree with 
    }
	
	write("The stitching on the elfwyr tag is so small as to be barely "
	+ "visible to the unaided eye.  Embroidered on the little, white tag in "
	+ "silver thread are the words:\n"
	+ "\"Dienya's fine clothing of Palanthas\"\n"
	+ "\"Tailored for " + C(whose) + "\"\n");
	return 1;
}

/* Overriding emote 'bow' for females, wearing certain articles
 * with a certain custom adjective.
 */
int bow()
{
	int gender = TP->query_gender();
	string adj = TO->query_prop(MY_CUS_NAME);
	string article = TO->query_name();
	string oshort = short();

  if (TO->query_worn())
  {
	if (gender == G_FEMALE 
		&& IN_ARRAY(adj, ({"alluring", "low-cut", "translucent", "unbuttoned", "unlaced"}))
		&& IN_ARRAY(article, ({"bath-robe", "dress", "gown", "blouse", "bodice"})))
	{
		write("You lean forward slowly in a bow giving onlookers "
		+ "ample time to peek down your " + oshort + ".\n");
		say(QCTNAME(TP) + " bows slowly, gazing into your eyes, her "
		+ oshort + one_of_list(({" giving you a glimpse of the curvaceous "
		+ "crest of her breasts.", " opening to provide a view of the "
		+ "upper mounds of her breasts.", " displaying a revealing glimpse "
		+ "of the upper hemisphere of her enticingly curving globes.",
		  " allowing you a peek within, the crest of her breasts jiggling "
		+ "a little as she slowly rises.", " affording you a glimpse of "
		+ "the crest of her supple breasts."})) + "\n");
		return 1;
	}
	  return 0;
  }
	return 0;
}

/* Overriding emote 'curtsey' for anyone wearing a certain article.
 */
int curtsey()
{
	string article = TO->query_name();
	string oshort = short();

  if (TO->query_worn())
  {
	if (IN_ARRAY(article, ({"frock", "muumuu", "shift", "kilt", "skirt"})))
	{
		write("Holding wide the edges of your " + oshort + " you perform "
		+ "a polite curtsey.\n");
		say(QCTNAME(TP) + " holds wide the edges of " + HIS(TP) + " "
		+ oshort + " as " + HE(TP) + " curtseys politely.\n");
		return 1;
	}
	  return 0;
  }
	return 0;
}

/* Overriding emote 'wiggle' for anyone wearing A_LEGS clothing.
 */
int wiggle()
{
	int atype = TO->query_at();
	string oshort = short();

  if (TO->query_worn())
  {
	if (atype == A_LEGS)
	{
		write("You wiggle your behind with " + one_of_list(({"consummate "
		+ "skill", "practiced ease", "a twist", "frantic haste", "daring do",
		"no regard for safety", "a jiggle"})) + " in your " + oshort + ".\n");
		say(QCTNAME(TP) + " wiggles " + HIS(TP) + " behind "
		+ one_of_list(({"with excessive jiggling", "making an embarassing "
		+ "squeaking noise accompanied by an odd odour", "with no regard for "
		+ "safety", "with a twist", "with disturbing ease", "with skillful "
		+ "ease", "with frantic haste", "in a daring maneuver", "with "
		+ "hypnotic gyrations"})) + " in " + HIS(TP) + " " + oshort + ".\n");
		return 1;
	}
	  return 0;
  }
	return 0;
}

/* Overriding emote for all clothing types using the custom adjective to
 * describe the strut.
 */
int strut()
{
	string strut = "";
	string oshort = short();
	string nstrut = TO->query_prop(MY_CUS_NAME);

	if (TO->query_worn())
	{
		strut = custom_to_strut[nstrut];

		write("You strut " + strut + " in your " + oshort + ".\n");
		say(QCTNAME(TP) + " struts " + strut + " in " + HIS(TP) + " "
		+ oshort + ".\n");
		return 1;
	}
	return 0;
}

/* Overriding emote for glove wearers allowing them to 'gesture' something up
 * to 32 characters.
 */
int gesture(string arg)
{
	string article = TO->query_name();
	string oshort = short();
	string gest;

  if (TO->query_worn())
  {
	if (article == "gloves" || article == "long-gloves")
	{
		if (strlen(arg) > 32)
		{
			write("That's a bit much to gesture at once.  You may want to learn "
			+ "sign language for that type of application.\n");
			say(QCTNAME(TP) + " gestures bizarrely with " + HIS(TP) + " "
			+ oshort + ".\n");
			return 1;
		}

		if (!strlen(arg))
		{ gest = ""; }

		else gest = arg + " ";

		write("You gesture " + gest + "with your " + oshort + ".\n");
		say(QCTNAME(TP) + " gestures " + gest + "with " + HIS(TP) + " "
		+ oshort + ".\n");

		return 1;
	}
	  return 0;
  }
	return 0;
}

/* Overriding emote for 'fart'.  If a harsh race + pants, hole is blown out
 * the seat of the pants.  If it's dress-like, billows out.  Both stink.
 * Also adds to the short and long when blown out.
 */
int fart()
{
	string article = query_name();
	string oshort = short();
	string frace = QRACE(TP);
	string fcdesc = one_of_list(({"brown", "green", "brownish green",
	"blackish green", "sickly green", "wet brown"}));
	string fdesc = "A " + fcdesc + "-tinged hole has "
	+ "ruptured out of the seat of these " + article + ".\n";
	string fdesc2 = "There is a moist, " + fcdesc + " spot in the seat of "
	+ "these " + article + ".\n";

  if (TO->query_worn())
  {
	if (IN_ARRAY(frace, ({"goblin", "hobgoblin", "orc", "minotaur", "uruk"}))
		&& blown == 0
		&& IN_ARRAY(article, ({"baggy-pants", "capris", "lederhosen",
		"pantaloons", "pants", "slacks", "stockings"})))
	{
		write("You bite down and grunt as you force a fart out your ass.\n"
		+ "PFFFFFLLLTTT!!!  Ohp!  The seat of your " + oshort + " ruptures "
		+ "sending a cloud of " + fcdesc + "-tinged gas into the air.\n"
		+ "Oops.\n");
		say(QCTNAME(TP) + " goes \"Ohhhhp!\" as " + HE(TP) + " forces a "
		+ "fart out " + HIS(TP) + " ass with a loud PFFFFFLLLTTT!!!\n"
		+ QCTNAME(TP) + "'s eyes grow wide in surprise as the seat of "
		+ HIS(TP) + " " + oshort + " ruptures sending a cloud of " + fcdesc
		+ "-tinged, " + one_of_list(({"maggot-gagging", "putrid", "moist",
		  "ass", "death", "bowel"})) + "gas into the air.\n"
		+ QCTNAME(TP) + " goes oops and wipes the sweat off " + HIS(TP)
		+ " brow.  Typical " + frace + ".\n");
		blown = 1;
		TO->set_long(query_long() + fdesc);
		TO->set_short("ass-ruptured " + oshort);
		return 1;
	}

	if (!IN_ARRAY(frace, ({"goblin", "hobgoblin", "orc", "minotaur", "uruk"}))
		&& soiled == 0
		&& IN_ARRAY(article, ({"baggy-pants", "capris", "lederhosen",
		"pantaloons", "pants", "slacks", "stockings"})))
	{
		write("You bare down and force a fart out your butt with a "
		+ "loud \"Pooot\"");
		say(QCTNAME(TP) + " squints up " + HIS(TP) + " face with obvious "
		+ "strain as " + HE(TP) + " forces a fart out " + HIS(TP) + " butt "
		+ "with a loud \"Pooot\"");
		if (!random(9))
		{
			write(" followed by a sloppy, wet, squirting noise!  Uh oh!  "
			+ "Better check your " + oshort);
			say(" followed by a sloppy, wet, squirting noise!  "
			+ QCTNAME(TP) + " better check " + HIS(TP) + " " + oshort
			+ " after that one");
			if (soiled == 0)
			{
				TO->set_long(query_long() + fdesc2);
				TO->set_short("butt-soiled " + oshort);
				soiled = 1;
			}
		}
		write(".\n");
		say(".\n");
		return 1;
	}

	if (IN_ARRAY(article, ({"bathrobe", "dress", "frock", "shift", "muumuu",
		"kilt", "skirt"})))
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

/* New emote for glove wearers.  May need to make add_cmd_item so it cycles
 * through all clothing in case not being first in a list of Dienya clothing
 * ruins it.
 */
int clench()
{
	string oshort = short();
	string article = TO->query_name();
	string mat = TO->query_prop(MY_MAT_NAME);

	if (IN_ARRAY(article, ({"gloves", "long-gloves"})))
	{
		if (TO->query_worn())
		{
		write("You clench your fists in your " + article + ", their "
		+ mat + " creaking under the strain.\n");
		say(QCTNAME(TP) + " clenches " + HIS(TP) + " fists in " + HIS(TP)
		+ " " + article + ", their " + mat + " creaking under the strain.\n");
		return 1;
		}
		write("You need to be wearing your " + oshort + " first.\n");
		return 1;
	}
	return 0;	// No msg if not gloves.
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

string
query_recover()
{
	return ::query_recover() + "|PA|" + recover_string + "|";
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
    ::init_recover(arg);

    string foobar, data;
    if (sscanf(arg, "%s|PA|%s|%s", foobar, data, foobar)) 
    {
        set_armour_data(data);
    } else {
        /* Support for legacy recovery strings */
	set_armour_data(arg);
    }
}
