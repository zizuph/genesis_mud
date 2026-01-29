/* 
 * Dienya's fine clothing store in the north of
 * the Court d'Plaisiri in the Nobles quarter.
 *
 * Mortis 12.2005
 *
 */

/* #pragma strict_types */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

inherit NOBLE_ROOMBASE;

#define VIEWSOUTH			(NOBLE + "nplaza")

mapping name_mat_to_info = (["articles":"Hanging on the sample racks is an "
	+ "example of a bathrobe, vest, dress, frock, gown, muumuu, shift, "
	+ "baggy-pants, capris, kilt, lederhosen, pantaloons, pants, skirt, "
	+ "slacks, stockings, bodice, blouse, puffy-shirt, pullover, shirt, "
	+ "sleeveless-shirt, sweater, gloves, long-gloves, and a scarf.",
	"bathrobe":"Of the kind frequently seen in the finest inns catering to "
	+ "the nobility, this plush bathrobe has a thick, folded collar "
	+ "encircling the neck and tapering down the chest to its belt, a thick "
	+ "fold of material running through beltloops on the hips.  It's the "
	+ "perfect robe to don at night, after a bath, or lounging about with "
	+ "coffee on a lazy morning.",
	"vest":"Exquisite tailoring has gone into the tailoring of this stylish "
	+ "vest.  It would fit comfortably over any shirt made here.",
	"dress":"Dienya can tailor dresses in any style from elegant to "
	+ "revealing to formal.  Extensive and careful sewing goes into each "
	+ "one making them a unique work of art.",
	"frock":"A pretty style of dress, this frock has a frill around its "
	+ "shoulder straps and is short and puffy on the legs.",
	"gown":"This exquisitely detailed and painstakingly created gown is "
	+ "luxuriously elegant, the perfect attire for ball, the symphony, "
	+ "a dinner party, or a night out on the streets of the noble "
	+ "quarter.",
	"muumuu":"What's this thing doing here?  Larger than the tents of "
	+ "common foot soldiers, this muumuu has obviously been designed for "
	+ "the morbidly obese, those whose obesity has reached a point "
	+ "beyond which any normal person clothing is capable of covering "
	+ "them.  The muumuu is little more than an enormous sheet with holes "
	+ "for the body and arms and a gaping hole through which it is hung "
	+ "over the body.  What is Dienya doing making these?",
	"shift":"A simple garment often worn by those seeking a simple "
	+ "lifestyle or comfortable bed attire,  a shift is a very simple, "
	+ "sleeveless dress with no cinching about the waist.  Even articles "
	+ "such as this shift still receive the dedicated attention to quality "
	+ "and detail always apparent in Dienya's work.",
	"baggy-pants":"This pair of baggy pants has been ingeniously sewn and "
	+ "tailored to be pleated below the waist, baggy around the thighs and "
	+ "taper down around the ankles.  It is stylish, adventurous, and "
	+ "dashing.",
	"capris":"These tapered and styled pants end around the knees and are "
	+ "very popular in hot climes and around water.",
	"kilt":"Is this a skirt?  No, kilts are commonly worn by men in foreign "
	+ "lands like Khalakhor, men who do not like their kilts being referred "
	+ "to as skirts.  These bold men wear nothing beneath their pleated "
	+ "kilts.",
	"lederhosen":"Strangely common in often cold, northern climes, these "
	+ "shorts are often made from leather and always worn with suspenders.  "
	+ "Dienya includes matching suspenders with each pair.  They are quite "
	+ "fetching and very popular at beer festivals.",
	"pantaloons":"Usually tight fitting, pantaloons extend from the waist "
	+ "to the calf where suspension straps secure them below the feet.  "
	+ "They are renowned for staying in place (and keeping everything in "
	+ "place) even during strenuous activity and commonly worn during "
	+ "certain athletic and horse riding events.",
	"pants":"A simple article of clothing elsewhere, Dienya makes every "
	+ "pair of pants with consummate skill and attention to detail.  They "
	+ "can be tailored to any variety and extend from the waist to "
	+ "somewhere around the ankles depending on taste.",
	"skirt":"Worn about the waist (commonly on women), Dienya tailors these "
	+ "to fit your curves perfectly, comfortably, and in the latest "
	+ "attractive and appealing styles.  They can be as short and low-cut "
	+ "or long and formal as desired.",
	"slacks":"A more formal and pleated variety of pants, Dienya's slacks "
	+ "are refined, stylish, and possessive of a quality unmatched by most "
	+ "tailors.",
	"stockings":"Though worn over the feet as well as the legs, stockings "
	+ "can fit under footwear.  They are worn tightly against the skin and "
	+ "rise up alluringly to the hips, and sometimes above, though most "
	+ "prefer to affix them to a garter belt with straps.",
	"bodice":"Extending from the waist, where it is worn tight, up to just "
	+ "below the shoulders, this bodice covers the chest, pushing one's "
	+ "bust up appealingly while appearing to thin the waist.  Though "
	+ "commonly laced from behind, especially alluring varieties reveal "
	+ "a tad extra by placing them in front.",
	"blouse":"A woman's shirt worn loosely about the chest and arms, Dienya "
	+ "can tailor them to be as stylish or provocative as desired.  Her "
	+ "attention to detail and the latest trends makes them very attractive "
	+ "and desirable (as well as their wearers at times).",
	"puffy-shirt":"Blatantly flamboyant and coutured, the puffy-shirt is "
	+ "no mere shirt.  The extravagant billow of its puffy sleeves is "
	+ "matched only by the delicacy of its frilly neck piece and front "
	+ "opening.  They are very popular among the noble youth, artists, "
	+ "and buccaneers.",
	"pullover":"This loose article is a specialty of Dienya's, a mix "
	+ "between a shirt and a sweater, and is very sporty.  Worn like a "
	+ "shirt, it has no front opening and is pulled on over the head "
	+ "like a sweater.  Its high, soft collar can be folded over, and "
	+ "its neckhole can be opened further or tightened with buttons or "
	+ "laces.",
	"shirt":"Not a common article at Dienya's, her shirts are tailored "
	+ "to be as varied as the customers who order them.  The variety of "
	+ "styles and feels to the shirts is unmatched in the city.",
	"sleeveless-shirt":"Usually worn on the snug side, this simple "
	+ "shirt has no sleeves and a wide neckpiece giving its shoulders "
	+ "the appearance of straps.  They're a good chest covering on hot "
	+ "days especially if you intend to be active.",
	"sweater":"Dienya's sweaters are warm and renowned as attractive "
	+ "and utilitous.  They're nice to have on crisp days and chilly "
	+ "nights.",
	"gloves":"There's no glove so comfortable as a tailored one, and "
	+ "at that Dienya is the best.  She can make a pair in any style "
	+ "or custom you desire.",
	"long-gloves":"These comfortable, masterfully tailored gloves "
	+ "cover the hands and extend up the arm as far as is desired and "
	+ "in any style whether tight or loose.",
	"scarf":"These simple strips of cloth wrapped around the neck "
	+ "become artistic and creative scarves in the hands of a tailor like "
	+ "Dienya.  Especially prevalent in the cold months, they are "
	+ "popular striped and checkered and go far to keeping one's neck "
	+ "warm.",
	"materials":"Hanging on the sample rack are examples of the varieties "
	+ "of materials Dienya works with:  arrasene, burlap, cashmyr, cotton, "
	+ "dupion, elfwyr, hemp, linen, organdie, messaline, sackcloth, "
	+ "silk, suede, swansdown, and wool.",
	"arrasene":"Arrasene is a smooth cloth woven from "
	+ "wool and silk giving it great durability and warmth while "
	+ "maintaining its fine appearance.",
	"burlap":"Burlap is a very cheap, rough, yet somewhat sturdy cloth "
	+ "more commonly seen in sacks than clothing.  Why such a highly "
	+ "regarded tailor would work with such a material may only be "
	+ "explained by her sense of humour.",
	"cashmyr":"Cashmyr is a soft twilled fabric made of very fine goat's "
	+ "wool from the mountains east of Palanthas.  It is unmatched for "
	+ "its soft feel, rich warmth, and rarity making it very expensive.  ",
	"cotton":"Delicately woven Dargaard cotton is a soft, durable, and "
	+ "plentiful cloth that is airy and comfortable.",
	"dupion":"Dupion is a cloth of coarse silk noted for its protection "
	+ "from abrasions and resistance to tearing.  Though coarse, the "
	+ "silk is soft and light.",
	"elfwyr":"Elfwyr is a fabric so light and delicate to the touch that "
	+ "it can hardly be felt when worn.  Elfwyr is the rarest of materials "
	+ "in Palanthas and rarely seen in the possession of any but the "
	+ "elven nobility of a select few reclusive clans.  The secrets of "
	+ "its production are virtually unknown.",
	"hemp":"Hemp is a plant whose fibrous roots and stems can be woven "
	+ "into nearly unrippable cloth and remarkably strong rope.  It is "
	+ "firm and not particularly uncomfortable.",
	"linen":"Linen is a stiff, woven cloth often used in formalwear, "
	+ "tablecloths, and sheets.",
	"organdie":"Organdie is a fine, translucent cotton delicately woven and "
	+ "commonly used in scarves, light shirts and blouses, and occasionally "
	+ "bathrobes.  Placed over your eyes, you can still see through it "
	+ "somewhat, and when worn, the skin can clearly be seen beneath.  ",
	"messaline":"Messaline is a soft, lightweight silk with a satin weave "
	+ "giving it a slightly glossy reflection in bright light and a shadowy "
	+ "depth in twilight.",
	"sackcloth":" Sackcloth is a very cheap, rough material that almost "
	+ "rips by itself.  Why such a highly regarded tailor would work with "
	+ "such a material may only be explained by her sense of humour.  Why "
	+ "someone would order it is even more of a mystery.  ",
	"silk":"Silk is a very light, exceptionally strong, and luxuriously soft "
	+ "cloth woven from the unraveled cocoons of moethes.  ",
	"suede":"Suede, a very soft, textured leather.  Suede must be "
	+ "painstakingly cured and worked to be so desirable.  As such it is "
	+ "expensive.",
	"swansdown":"Swansdown is a heavy napped, cotton flannel often used by "
	+ "outdoor travellers and highly regarded for its breathe-ability, "
	+ "durability, and silky softness.  It is a specialty of the Dresnos "
	+ "shipping company who keeps their source well guarded.  ",
	"wool":"Wool is a thick, coarse cloth woven from sheephair.  It is well "
	+ "regarded for its heat retention and comfort when not worn directly "
	+ "upon sensitive skin."]);

object dienya;

string
query_to_jail()
{
  return "south";
}


void
reset_palan_room()
{
	if (!dienya)
	{
	dienya = clone_object(NOBLE + "living/dienya");
	dienya->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("Dienya's fine clothing store");
    LONG("Inside, this shop is spacious with a high ceiling and windows "
	+ "looking south upon the court.  Rows of racks are arranged throughout "
	+ "the store filled with exceptionally fine shirts, pants, dresses, "
	+ "robes, skirts, and even gloves and scarves.  There is a counter "
	+ "along the east wall behind which is hung a marble sign.  Stairs "
	+ "by the counter lead up to a closed, palewood door.\n");

	ITEM(({"plaza", "court"}), "The court is busy at all hours providing "
	+ "pleasurable services in the nobles quarter.  You can view it from "
	+ "the windows south.\n");
	ITEM(({"large two-story shop", "north shop", "two-story shop",
	  "large shop"}), "This shop in the north of the Court d'Plaisiri is "
	+ "large and spacious with a high ceiling.  Have a <look> around.\n");
	ITEM(({"ivy", "pillars", "ivy entwined pillars"}), "Six tall, marble "
	+ "pillars chiseled simply in the old style rise before the shop "
	+ "up to its second story just outside.  Vines of cultured ivy spiral "
	+ "up them, their leaves gently waving in the breeze.\n");
	ITEM(({"rack", "racks", "clothes", "clothing", "shirts", "pants",
		   "dresses", "robes", "skirts", "gloves", "scarves"}), "A wide "
	+ "variety of fine clothing hangs from polished, steel racks all "
	+ "throughout the store.  You may <peruse> it if you like.\n");
	ITEM("counter", "The counter along the east wall is covered with "
	+ "neatly arranged spindles of thread, needles, bolts of cloth, and "
	+ "patterns all for tailoring the finest clothing.  Behind it on "
	+ "the wall is a large, marble sign, a stool, and a dye press.\n");
	ITEM(({"thread", "spindles", "spindle", "needle", "needles", "bolts",
		   "cloth", "patterns"}), "Arranged neatly atop the counter along "
	+ "the east wall are spindles of thread, needles, bolts of cloth, and "
	+ "patterns all for tailoring the finest clothing.\n");
	ITEM("ceiling", "The ceiling high above is polished, translucent "
	+ "marble.\n");
	ITEM(({"window", "windows"}), "Along the south wall are windows "
	+ "peering out through the ivy-wrapped pillars in front of the "
	+ "store.  You can <view the plaza> from them.\n");
	ITEM(({"door", "palewood door"}), "Made of a very pale coloured wood, "
	+ "the door at the top of the stairs appears well-crafted and sturdy.\n");
	ITEM(({"sign", "marble sign"}), "A wide marble trimmed sign hung "
	+ "behind the counter.  You may <read sign> if you like.\n");
	ITEM(({"sample rack", "samples", "sample"}), "The sample rack contains "
	+ "samples of all materials available as well as the various articles of "
	+ "clothing tailored by Dienya.  You may <check materials>, <check "
	+ "articles>, or <check name> of a type of material or article of "
	+ "clothing (like <check silk> or <check gloves> for example).\n");
	ITEM("stool", "There is a wooden stool behind the counter for the tailor "
	+ "to use while working.\n");
	ITEM(({"press", "dye press"}), "The dye press is a strangely simple "
	+ "device considering the metalwork is engraved \"Product of Mt. "
	+ "Nevermind\".  A lever presses the contents of a container of dye into "
	+ "cloth inside the press producing an evenly dyed finished product.\n");
	ITEM("lever", "The lever on the dye press is a simple, wooden handle.\n");

	EXIT(NOBLE + "fineclothing2", "stairs", "@@up_stairs", 0);
	EXIT(NOBLE + "nplaza", "south", 0, 0);
	
	CMD(({"clothing", "clothes", "rack", "racks"}),({"peruse"}),
		  "@@peruse_clothing");
	CMD(({"plaza", "the plaza", "court", "the court"}), "view",
		  "@@view_plaza");
	CMD("sign", "read", "@@read_sign");
	CMD("sign", "mread", "@@mread_sign");

	reset_palan_room();
}

int
up_stairs() 
{ 
  write("The palewood door at the top of the stairs is barred shut from "
  + "the other side.\n"); 
  return 1; 
}

peruse_clothing() 
{
	write("You casually peruse the racks of clothing throughout the store.  "
	+ "The quality is exceptional and variety unmatched.  You find a sample "
	+ "rack containing samples of materials available and each type of "
	+ "article tailored by Dienya.  You may examine it.  You may also "
	+ "<check> anything in the shop.\n");
	say(QCTNAME(TP) + " casually peruses the racks of clothing throughout "
	+ "the store.\n");
	return "";
}

view_plaza()
{
	/* This function returns an equivalent of 'look' from nplaza
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWSOUTH->long());
	target = find_object(VIEWSOUTH);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write("Through the ivy-wrapped pillars out the windows along the "
		+ "south wall, you can make out " + desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the court you see " + desc + ".\n");

	say(QCTNAME(TP) + " gazes out the windows along the south wall.\n");
 
	return 1;
}

public int
read_sign()
{
	say(QCTNAME(TP) + " studies the marble sign behind the counter.\n");
	write("The sign reads...\n");
	cat(NOBLE + "arms/fineclothes.txt", 1, 55);

	return 1;
}

public int
mread_sign()
{
	string file = NOBLE + "arms/fineclothes.txt";

	say(QCTNAME(TP) + " studies the marble sign behind the counter.\n");
	write("The sign reads...\n");
	TP->more(read_file(file, 1, 50000));


	return 1;
}

void
init()
{
    ::init();

	ADA("check");
}

int
check(string str)
{
	int k;
	string check = "";
	
	if (!str)
	{
		write("Check what?  Materials?  Articles?  A specific material or "
		+ "article of clothing?  You may want to <read sign>, too.\n");
		return 1;
	}

	if (check = name_mat_to_info[str])
	{
		write("You check out the " + str + ".  " + check + "\n");
		say(QCTNAME(TP) + " checks out the " + str + ".\n");
		return 1;
	}
	write("That is not a valid material or article of clothing.  Use "
	+ "<check materials> for a list of materials and <check articles> "
	+ "for a list of clothing you can order (or <read sign> even).\n");

	return 1;
}
