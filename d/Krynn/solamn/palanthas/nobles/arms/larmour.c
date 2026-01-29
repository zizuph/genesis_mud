/* Mortis 12.2005
 *
 * This is the armour base for the leather armour Daronius
 * crafts in the Arms district of Palanthas.
 *
 * Could add props to armours setting the orderer's size on creation
 * then check in the wear routine if the wearer fits inside them.
 *
 */


inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include "../../local.h"

inherit "/cmd/std/command_driver";

#define POINT_DIRECTIONS ({ "up", "down", "north", "south", "west", "east", \
    "northwest", "southwest", "northeast", "southeast" })

int weight, volume, value;
string recover_string, cus, col, mat, art, at, cusmore, colmore, matmore,
	matlong, collong, artmore, soundmore, ndesc2, strut, cusshort;

int blown = 0;
int soiled = 0;
int adjust_weight(string which);
int set_my_ac();

/* Prototypes */
void add_some_names();

mapping name_to_class = (["suit":A_BODY | A_ARMS | A_LEGS,
	"coat":A_BODY | A_ARMS, "greaves":A_LEGS, "leggings":A_LEGS,
	"breastplate":A_BODY, "cuirasse":A_BODY, "vest":A_BODY,
	"bracers":A_ARMS, "pauldrons":A_ARMS, "sleeves":A_ARMS,
	"gloves":A_HANDS, "armet":A_NECK, "cap":A_HEAD, "helmet":A_HEAD,
	"boots":A_FEET, "tall-boots":A_FEET | A_LEGS, "belt":A_WAIST,
	"liner":A_ROBE]);

mapping name_to_desc = (["suit":"full suit of armour", "coat":"coat of armour",
	"greaves":"pair of greaves", "leggings":"pair of leggings",
	"breastplate":"breastplate", "cuirasse":"cuirasse", "vest":"vest",
	"bracers":"pair of bracers", "pauldrons":"set of pauldrons",
	"sleeves":"pair of sleeves", "gloves":"pair of gloves", "armet":"armet",
	"cap":"cap", "helmet":"helmet", "boots":"pair of boots",
	"tall-boots":"pair of tall boots", "belt":"belt", "liner":"liner"]);

mapping name_to_desc2 = (["suit":"suit consists of a shirt with "
	+ "reinforced chest and back plates with a series of integrated, "
	+ "buckled straps up each side along the ribs for keeping it snug.  "
	+ "The sleeves end in similarly strapped and buckled bracers with a "
	+ "stiff pauldron over the weapon arm angled to protect the shoulder "
	+ "and neck.  Leather leggings continue down from the shirt with "
	+ "buckled straps down the outside of the thighs and calves keeping "
	+ "the stiff thigh guards and greaves in place.  The suit feels "
	+ "fairly protective for having no metal but the light steel of its "
	+ "buckles.  It is light and supple enough for good maneuverability and ",
	"coat":"coat is long-sleeved ending in stiff bracers with tie straps "
	+ "along the inside.  The coat opens down the front with a series of "
	+ "buckled straps across the opening for cinching it closed.  Stiff "
	+ "plates reinforce the back, each breast, and shoulders, but the "
	+ "coat remains comfortably loose, fairly protective, and light and "
	+ "supple enough for good maneuverability.  It ",
	"greaves":"greaves are stiff with buckled straps wrapping around the "
	+ "back of the calves.  A set of similar, stiff thigh guards comes "
	+ "with them.  The pair ", 
	"leggings":"leggings extend from the waist to the ankles with buckled "
	+ "straps down the outside of the thighs and calves keeping their "
	+ "protective padding in place.  Though strapped down snugly, they "
	+ "feel easy to maneuver in.  The pair ",
	"breastplate":"breastplate encompasses all of the chest and back in two "
	+ "firm plates joined along the sides and shoulders with buckled "
	+ "straps and ", 
	"cuirasse":"cuirasse form fits to your chest and back when worn "
	+ "revealing the outline of your form.  It consists of two firm plates "
	+ "joined together along the sides and shoulders with buckled straps "
	+ "and ", 
	"vest":"vest is a form fitting, seamless chest and back armour pulled "
	+ "on over the head.  For its protection it is light and supple "
	+ "enough for freedom of movement and maneuverability and ",
	"bracers":"bracers are stiff with buckled straps securing them snugly "
	+ "along the inside of the forearm and comes with a pair of bicep bands "
	+ "for upper arm protection.  The pair ", 
	"pauldrons":"pauldrons are stiff pads buckle-strapped over the shoulders "
	+ "and angled to protect the shoulder and neck.  The pad worn over the "
	+ "weapon arm is longer with a piece strapped around the bicep while "
	+ "the other pad worn over the shield arm is shorter to avoid "
	+ "interfering with a shield.  The set ",
	"sleeves":"sleeves are worn snug at their cuffed wrists and shoulders "
	+ "where they end in buckled straps that wrap behind the back to keep "
	+ "them on securely.  The set is loose and padded in between the "
	+ "wrists and shoulders and ", 
	"gloves":"gloves are snug, form fitting, and flare out an inch over "
	+ "the wrists.  The pair ", 
	"armet":"armet is a circular protective guard hung over the shoulders "
	+ "with a section that sticks up two inches around the neck and "
	+ "buckled straps and ties keeping it closed down the back.  It ",
	"cap":"cap has a buckled band that wraps around the forehead to keep its "
	+ "loose, padded top on and side guards that hang down in front "
	+ "of the ears.  It ", 
	"helmet":"helmet has a hardened pointed top, flared neck guard, stiff "
	+ "nose guard, and wide protective straps pulled down in front of the "
	+ "ears and under the chin to keep it on.  It ", 
	"boots":"boots have stiff, sturdy soles and buckled straps on their "
	+ "outside rising from the ankles up the calves to keep them snug "
	+ "over armour.  They are both protective and supple for ease of "
	+ "maneuverability.  The pair ",
	"tall-boots":"tall boots have stiff, sturdy soles and buckled straps "
	+ "on their outside rising from the ankles to midway up the thighs.  "
	+ "Though snug, they are supple and comfortable for ease of "
	+ "maneuverability while remaining protective.  The pair ", 
	"belt":"belt has a light steel buckle, is reinforced along the front "
	+ "and sides for tying pouches, and ", 
	"liner":"liner looks as if it needs to be attached within the folds "
	+ "of a cloak or robe for added protection.  It "]);

mapping mat_to_desc = (["hard":"leather boiled in oil, hardening it into "
	+ "form fitting plates.  ",
	"hide":"rhinocerous hide, a thick, nearly impenetrable hide that is "
	+ "much lighter than metal armour.  ",
	"soft":"leather, slow cured to be both soft to the touch "
	+ "and protective.  ",
	"leather":"leather that is firmer than slow cured soft leather but "
	+ "more flexible than leather hardened in boiling oil.  ",
	"soft":"This leather is slow cured to be both soft to the touch "
	+ "and protective.",
	"studded":" leather, expertly cured for a soft feel while remaining "
	+ "highly protective.  Inch diameter studs, their two inch diameter "
	+ "steel plates hidden beneath the leather, stick out every few inches "
	+ "giving the armour strong protections without great weight.  ",
	"suede":"suede, a very soft, textured leather.  Suede must be "
	+ "painstakingly cured and worked to not only be so desirable but "
	+ "protective as well.  As such it is expensive.  "]);

mapping colour_to_desc = (["black":"black", "white":"white",
	"charcoal":"charcoal", "grey":"grey", "brown":"brown",
	"mottled-brown":"mottled brown", "crimson":"crimson", "maroon":"maroon",
	"yellow":"yellow", "forest-green":"forest green",
	"mottled-green":"mottled green", "olive-green":"olive green",
	"blue":"blue", "raven-blue":"raven blue",
	"silvery":"a lustrous silver hue"]);

mapping custom_to_desc = (["dark":"with texturing to be darker than usual",
	"fur-trimmed":"with a soft, gray-black fur trimming its edges",
	"glistening":"with a glisteningly smooth surface that catches and "
	+ "reflects the light",
	"heavy":"with an extra thick inner lining of swansdown",
	"light":"with experienced molding to be a little lighter than normal",
	"noble":"in a formal yet elegant style common among the nobility",
	"ornate":"with an ornate series of swirling, raised lines down its "
	+ "length that curl into spirals at their ends",
	"plain":"to be simple and functional",
	"rich":"with an especially rich texture",
	"soft":"in a texture softer than normal",
	"skin-tight":"to lay perfectly tight, preferably right against the skin, "
	+ "in a custom fit achieved only by master craftsmen.  It is lined with "
	+ "ultra-thin and luxurious elfwyr for exceptional comfort and follows "
	+ "every curve of your body it covers",
	"supple":"to be especially supple for its material, allowing its wielder "
	+ "full grace in movement and practically no hinderance in "
	+ "maneuverability", 
	"thick":"with particularly thick material",
	"thin":"with a somewhat thinner material",
	"tight":"to fit snugly against your body"]);

mapping custom_to_strut= (["dark":"darkly with foreboding",
	"fur-trimmed":"luxuriously",
	"glistening":"glisteningly",
	"heavy":"thumpingly along",
	"light":"hoppingly",
	"noble":"in a formal yet elegant style",
	"ornate":"with a flourished, complex step",
	"plain":"about",
	"rich":"wealthily",
	"soft":"gently",
	"skin-tight":"sensuously",
	"supple":"smoothly",
	"thick":"largely",
	"thin":"lightly",
	"tight":"with measured, appealing strides"]);

mapping custom_to_short = (["dark":"dark ",
	"fur-trimmed":"fur-trimmed ",
	"glistening":"glistening ",
	"heavy":"heavy ",
	"light":"light ",
	"noble":"noble ",
	"ornate":"ornate ",
	"plain":"",
	"rich":"rich ",
	"soft":"soft ",
	"skin-tight":"skin-tight ",
	"supple":"supple ",
	"thick":"thick ",
	"thin":"thin ",
	"tight":"tight "]);

mapping mat_to_sound = (["hard":"creaking tightly",
	"hide":"creaking stiffly",
	"leather":"creaking firmly",
	"soft":"creaking softly",
	"studded":"creaking menacingly",
	"suede":"rustling quietly"]);

mapping mat_to_full = (["hard":"hard leather",
	"hide":"hide",
	"leather":"leather",
	"soft":"soft leather",
	"studded":"studded leather",
	"suede":"suede"]);

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
}

void
set_armour_data(string data)
{
    seteuid(getuid());

	int the_ac;
    string* txt = explode(data,"&&");
    cus = txt[0];
    col = txt[1];
    mat = txt[2];
    art = txt[3];
	at = name_to_class[art];
	weight = adjust_weight("weight");
	volume = adjust_weight("volume");
	value = adjust_weight("value");

	artmore = name_to_desc[art];
	ndesc2 = name_to_desc2[art];
	matlong = mat_to_desc[mat];
	matmore = mat_to_full[mat];
	soundmore = mat_to_sound[mat];
	collong = colour_to_desc[col];
	colmore = colour_to_full[col];
	cusmore = custom_to_desc[cus];
	cusshort = custom_to_short[cus];
	strut = custom_to_strut[cus];

	the_ac = set_my_ac();
	set_ac(the_ac);
	set_am(({1, 0, -1}));
	set_at(at);
    
 	add_prop(OBJ_I_WEIGHT, weight);
	add_prop(OBJ_I_VOLUME, volume);
	add_prop(OBJ_I_VALUE, value);

	set_name(art);
	add_adj(cus);
    add_adj(col);
	add_adj(mat);
	// Generic to all armours:
	add_adj("daronius");
	add_some_names();
	set_keep(1);
	set_af(TO);

	set_short(cusshort + colmore + " " + matmore + " " + name_to_desc[art]);
    set_long("Finished with masterful quality and detailed attention, this "
	+ artmore + " has been crafted from " + matlong + "The " + ndesc2
	+ "has been dyed " + collong + " and finished " + cusmore
	+ ".  Pressure stamped into the " + art + "'s inside border is a "
	+ "circular seal.\n");

	recover_string = data;
}

int
set_my_ac()
{
	int acx = 15;

	switch(art)
	{
		case "cap":
		case "helmet":
			acx = 22;
			break;
		case "armet":
			acx = 23;
			break;
		case "breastplate":
		case "cuirasse":
		case "vest":
			acx = 30;
			break;
		case "suit":
			acx = 28;
			break;
		case "coat":
			acx = 29;
			break;
		case "bracers":
		case "pauldrons":
		case "sleeves":
			acx = 23;
			break;
		case "belt":
			acx = 15;
			break;
		case "gloves":
			acx = 15;
			break;
		case "greaves":
		case "leggings":
		case "tall-boots":
			acx = 24;
			break;
		case "boots":
			acx = 23;
			break;
		default:
			acx = 15;
	}
	return acx;
}

int
adjust_weight(string which)
{	
	int wei, vol, val;

	switch(art)
	{
		case "cap":
		case "helmet":
			wei = 550;
			vol = 475;
			val = 288;
			break;
		case "armet":
		case "liner":
			wei = 450;
			vol = 400;
			val = 216;
			break;
		case "breastplate":
		case "cuirasse":
		case "vest":
			wei = 2750;
			vol = 1500;
			val = 504;
			break;
		case "suit":
			wei = 3775;
			vol = 3125;
			val = 936;
			break;
		case "coat":
			wei = 3050;
			vol = 2450;
			val = 648;
			break;
		case "bracers":
		case "pauldrons":
		case "sleeves":
			wei = 750;
			vol = 375;
			val = 288;
			break;
		case "belt":
			wei = 250;
			vol = 125;
			val = 144;
			break;
		case "gloves":
			wei = 275;
			vol = 140;
			val = 216;
			break;
		case "greaves":
		case "leggings":
			wei = 925;
			vol = 575;
			val = 360;
			break;
		case "tall-boots":
			wei = 1375;
			vol = 1025;
			val = 576;
			break;
		case "boots":
			wei = 650;
			vol = 425;
			val = 288;
			break;
		default:
			wei = 1111;
			vol = 1111;
			val = 100;
	}

	if (which == "volume")
	{
		vol = vol - 40;
		vol = vol + random(80);
		return vol;
	}
	if (which == "value")
	{
		val = val - 25;
		val = val + random(50);
		return val;
	}

	wei = wei - 50;
	wei = wei + random(100);
	return wei;
}

void
add_some_names()
{
	if (art == "suit")
		add_adj(({"full"}));
	if (art == "tall-boots")
	{
		add_name(({"boots"}));
		add_adj(({"tall"}));
	}
	if (col == "mottled-brown")
		add_adj(({"mottled", "brown"}));
	if (col == "forest-green")
		add_adj(({"forest", "green"}));
	if (col == "olive-green")
		add_adj(({"olive", "green"}));
	if (col == "mottled-green")
		add_adj(({"mottled", "green"}));
	if (col == "raven-blue")
		add_adj(({"raven", "blue"}));
	if (cus == "fur-trimmed")
		add_adj(({"fur", "trimmed"}));
	if (cus == "skin-tight")
		add_adj(({"skin", "tight"}));
	return;
}

int
wear()
{
	if (art == "liner")
	{
		write("You'll need to find someone who can work that into a "
		+ "cloak or robe, friend.\n");
		return -1;
	}

	return 0;
}

void
init()
{
    ::init();
    ADA("bow");
	ADA("curtsey");
	ADA("flex");
	ADA("wiggle");
	ADA("strut");
	ADA("gesture");
	ADA("fart");
	ADA("clench");
	ADA("pose");
	ADA("stretch");
	ADA("help");

	ADD("exa_seal", "exa");
	ADD("exa_seal", "examine");
}

int exa_seal(string arg)
{
	if (strlen(arg) && !parse_command(arg, ({}), "[the] [circular] 'seal' "))
    {
        return 0; // the player used syntax we don't agree with 
    }
	
	write("Stamped into the tanned material with an indention press while "
	+ "it was still fresh is a circular seal with a pair of fourteen point "
	+ "antlers above \"Palanthas\" written in the old style.  Try <help "
	+ "daronius>.\n");
	return 1;
}

/* Overriding emote 'bow' while wearing certain articles.
 */
int bow(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "lithely", 0);
	oblist = parse_this(how[0], "[to] %l");

	if (TO->query_worn() && IN_ARRAY(art, ({"suit", "coat", "breastplate",
		"cuirasse", "vest"})))
	{
		if (!sizeof(oblist))
		{ 
			write("You bow" + how[1] + ", the " + cusshort + matmore
			+ " of your " + colmore + " " + artmore + " " + soundmore
			+ ".\n");
			allbb(" bows" + how[1] + ", the " + cusshort + matmore
			+ " of " + HIS(TP) + " " + colmore + " " + artmore + " "
			+ soundmore + ".");
			return 1;
		}

		actor("You bow to", oblist, how[1] + ", the " + cusshort
		+ matmore + " of your " + colmore + " " + artmore + " " + soundmore
		+ ".");
		target(" bows to you" + how[1] + ", the " + cusshort + matmore
		+ " of " + HIS(TP) + " " + colmore + " " + artmore + " " + soundmore
		+ ".", oblist);
		all2act(" bows to", oblist, how[1] + ", the " + cusshort
		+ matmore + " of " + HIS(TP) + " " + colmore + " " + artmore + " "
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
	how = parse_adverb_with_space(str, "smoothly", 0);
	oblist = parse_this(how[0], "[to] %l");

	if (TO->query_worn() && IN_ARRAY(art, ({"suit", "coat", "breastplate",
		"cuirasse", "vest", "leggings", "tall-boots", "greaves"})))
	{
		if (!sizeof(oblist))
		{ 
			write("You curtsey" + how[1] + ", the " + cusshort
			+ matmore + " of your " + colmore + " " + artmore + " "
			+ soundmore + ".\n");
			allbb(" curtseys" + how[1] + ", the " + cusshort
			+ matmore + " of " + HIS(TP) + " " + colmore + " " + artmore
			+ " " + soundmore + ".");
			return 1;
		}

		actor("You curtsey to", oblist, how[1] + ", the " + cusshort
		+ matmore + " of your " + colmore + " " + artmore + " " + soundmore
		+ ".");
		target(" curtseys to you" + how[1] + ", the " + cusshort
		+ matmore + " of " + HIS(TP) + " " + colmore + " " + artmore + " "
		+ soundmore + ".", oblist);
		all2act(" curtseys to", oblist, how[1] + ", the " + cusshort
		+ matmore + " of " + HIS(TP) + " " + colmore + " " + artmore + " "
		+ soundmore + "."); 
		return 1;
	}
	return 0;
}

/* Overriding emote 'wiggle' for anyone wearing A_LEGS armour.
 */
int wiggle(string str)
{
	string *how;
	how = parse_adverb_with_space(str, "excitedly", 0);

	if (TO->query_worn() && IN_ARRAY(art, ({"suit", "leggings", "greaves",
		"tall-boots"})))
	{
		write("You wiggle your behind" + how[1] + " with "
		+ one_of_list(({"consummate skill", "practiced ease", "a twist",
			"frantic haste", "daring do", "no regard for safety", 
			"a jiggle"})) + ", the " + cusshort + matmore
		+ " of your " + colmore + " " + artmore + " " + soundmore + ".\n");
		allbb(" wiggles " + HIS(TP) + " behind" + how[1] + " "
		+ one_of_list(({"with excessive jiggling", "making an embarassing "
		+ "squeaking noise accompanied by an odd odour", "with no regard "
		+ "for safety", "with a twist", "with disturbing ease", "with "
		+ "skillful ease", "with frantic haste", "in a daring maneuver",
		  "with hypnotic gyrations"})) + ", the " + cusshort + matmore
		+ " of " + HIS(TP) + " " + colmore + " " + artmore + " " + soundmore
		+ ".");
		return 1;
	}
	return 0;
}

/* Overriding emote 'flex' for anyone wearing A_ARMS armour.
 */
int flex(string str)
{
	string *how;
	string flexhow = "with catlike strength";
	if (TP->query_gender() == 0)
		flexhow = "with vein popping strength";
	how = parse_adverb_with_space(str, flexhow, 0);

	if (TO->query_worn() && IN_ARRAY(art, ({"suit", "sleeves", "bracers",
		"pauldrons"})))
	{
		write("You raise your arms and flex your biceps" + how[1] + ", the "
		+ cusshort + matmore + " of your " + colmore + " " + artmore
		+ " " + soundmore + " at the strain.\n");
		allbb(" raises " + HIS(TP) + " arms and flex " + HIS(TP) + " biceps"
		+ how[1] + ", the " + cusshort + matmore + " of " + HIS(TP) + " "
		+ colmore + " " + artmore + " " + soundmore + " at the strain.");
		return 1;
	}
	return 0;
}

/* Overriding emote for all armour types using the custom adjective to
 * describe the strut.
 */
int strut(string str)
{
	string *how;
	strut = custom_to_strut[cus];
	how = parse_adverb_with_space(str, strut, 0);
	if (TO->query_worn())
	{
		write("You strut" + how[1] + ", the " + cusshort + colmore
		+ " " + matmore + " of your " + artmore + " " + soundmore + ".\n");
		say(QCTNAME(TP) + " struts" + how[1] + ", the " + cusshort
		+ colmore + " " + matmore + " of " + HIS(TP) + " "
		+ artmore + " " + soundmore + ".\n");
		return 1;
	}
	return 0;
}

/* Overriding emote for glove wearers allowing them to 'gesture' something up
 * to 32 characters.
 */
int gesture(string arg)
{
	string gest;
	string oshort = short();

  if (TO->query_worn())
  {
	if (art == "gloves")
	{
		if (strlen(arg) > 32)
		{
			write("That's a bit much to gesture at once.  You may want to "
			+ "learn sign language for that type of application.\n");
			return 1;
		}

		if (!strlen(arg))
		{ gest = custom_to_strut[cus]; }

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
	string oshort = short();
	string frace = QRACE(TP);
	string fcdesc = one_of_list(({"brown", "green", "brownish green",
	"blackish green", "sickly green", "wet brown"}));
	string fdesc = "A " + fcdesc + "-tinged hole has "
	+ "ruptured out of the seat of this " + artmore + ".\n";
	string fdesc2 = "There is a moist, " + fcdesc + " spot in the seat of "
	+ "this " + artmore + ".\n";

  if (TO->query_worn())
  {
	if (IN_ARRAY(frace, ({"goblin", "hobgoblin", "orc", "minotaur", "uruk"}))
		&& blown == 0
		&& IN_ARRAY(art, ({"baggy-pants", "capris", "lederhosen",
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
		&& IN_ARRAY(art, ({"leggings", "suit", "tall-boots"})))
	{
		write("You bare down and force a fart out your butt with a "
		+ "loud \"Pooot\"");
		say(QCTNAME(TP) + " squints up " + HIS(TP) + " face with obvious "
		+ "strain as " + HE(TP) + " forces a fart out " + HIS(TP) + " butt "
		+ "with a loud \"Pooot\"");
		if (!random(19))
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

	if (IN_ARRAY(art, ({"greaves", "belt", "coat"})))
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

	if (IN_ARRAY(art, ({"gloves"})))
	{
		if (TO->query_worn())
		{
			write("You clench your fists in your " + art + ", their "
			+ cusshort + colmore + " " + matmore + " " + soundmore
			+ " under the strain.\n");
			say(QCTNAME(TP) + " clenches " + HIS(TP) + " fists in " + HIS(TP)
			+ " " + art + ", their " + cusshort + colmore + " " + matmore
			+ soundmore + " under the strain.\n");
			return 1;
		}
		write("You need to be wearing your " + oshort + " first.\n");
		return 1;
	}
	return 0;	// No msg if not gloves.
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
		+ ", its " + cusshort + colmore + " " + matmore + " " + soundmore
		+ ".\n");
		say("With hands on hips " + QTNAME(TP) + " poses" + how[1] + " in "
		+ HIS(TP) + " " + artmore + ", its " + cusshort + colmore + " " 
		+ matmore + " " + soundmore	+ "\n.");
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
	width fucking queryable, this can be uncommented and string bod used to
	describe someone's body in this emote. */
	string bod = "timeworn";
	how = parse_adverb_with_space(str, one_of_list(({"osmodiusly", strut})), 0);

	if (TO->query_worn())
	{
		write("You stretch your " + bod + " body out" + how[1] + " in your "
		+ artmore + ", its " + cusshort + colmore + " " + matmore + " "
		+ soundmore + ".\n");
		say(QCTNAME(TP) + " stretches " + HIS(TP) + " " + bod + " body out"
		+ how[1] + " in " + HIS(TP) + " " + artmore + ", its " + cusshort
		+ colmore + " " + matmore + " " + soundmore	+ "\n.");
		return 1;
	}
	return 0;
}

int
help(string str)
{
	if (!str || str != "daronius")
		return 0;

	write("You may do the following in certain Daronius crafted armours:\n"
	+ "bow <adj> to <person>      - Perform a bow in your armour.\n"
	+ "clench                     - Clench your hands with special creaking.\n"
	+ "curtsey <adj> to <person>  - Curtsey in your armour.\n"
	+ "fart                       - Do not under any circumstances try this.\n"
	+ "flex <adj>                 - Flex your mighty muscle.\n"
	+ "gesture                    - A mysterious gesture of power in the \n"
	+ "                             right \"hands\".\n"
	+ "pose <adj>                 - Strike a pose in your Daronius armour.\n"
	+ "stretch <adj>              - It is time.  Time to stretch that is.\n"
	+ "strut <adj>                - Strut in your armour.\n"
	+ "wiggle <adj>               - Wiggle without regard for safety.\n"
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

string
query_recover()
{
	return MASTER + ":" + recover_string;
}

void
init_recover(string arg)
{
    ::init_keep_recover(arg);
	set_armour_data(arg);
}
