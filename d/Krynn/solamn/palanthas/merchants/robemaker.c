/* 
 * The robe merchant in the merchants quarter of Palanthas.
 * Sells custom robes and coats that can be fitted with the
 * armoured linings from the leather worker Daronius.
 *
 * Mortis 04.2006
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <living_desc.h>
#include <cmdparse.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include <money.h>
#include <files.h>
#include <formulas.h>

inherit MERCH_ROOMBASE;
inherit "/lib/trade";

#define VIEWSOUTH				(MERCH + "wr4")
#define NUM	sizeof(MONEY_TYPES)

object daiv;

// Robes, coats, and materials.
mapping name_arm_to_info = (["robe":"They are available in a variety "
	+ "of the latest styles, patterns, and lengths.  You are sure to find "
	+ "one to your tastes.",
	"coat":"They are a popular style to order with furs, the coats available "
	+ "are sturdy, stylish, and elegant.",
	"alligator":"Its dark, emerald plates are firm but supple and polished "
	+ "smooth.",
	"arrasene":"It is a smooth cloth woven from wool and silk giving it "
	+ "great durability and warmth while maintaining its fine appearance.",
	"cashmyr":"It is a soft twilled fabric made of very fine goat's "
	+ "wool from the mountains east of Palanthas and is unmatched for "
	+ "its soft feel, rich warmth, and rarity making it very expensive.  ",
	"cotton":"It is a delicately woven Dargaard cotton, a soft, durable, and "
	+ "plentiful cloth that is airy and comfortable.  ",
	"dupion":"It is a cloth of coarse silk noted for its protection "
	+ "from abrasions and resistance to tearing.  Though coarse, the "
	+ "silk is soft and light.  ",
	"elfwyr":"It is a fabric so light and delicate to the touch that "
	+ "it can hardly be felt when worn.  Elfwyr is the rarest of materials "
	+ "in Palanthas and rarely seen in the possession of any but the "
	+ "elven nobility of a select few reclusive clans.  The secrets of "
	+ "its production are virtually unknown.  ",
	"ermine":"It is the unbelievably soft white fur of the northern "
	+ "ermine's winter coat.  It has small black spots spaced out upon "
	+ "it.  ",
	"fox":"It is an indulgently fine, reddish fur from foxes.  ",
	"linen":"It is a stiff, woven cloth often used in formalwear, "
	+ "tablecloths, and sheets.  ",
	"lizard":"It is a stiff, green lizard skin, darker on the back and "
	+ "growing lighter towards the front and down the arms.  ",
	"mink":"It is a mottled white, black, and brown mink fur.  It is "
	+ "incredibly soft and not only looks rich, but feels decadent against "
	+ "your skin.  ",
	"messaline":"It is a soft, lightweight silk with a satin weave "
	+ "giving it a slightly glossy reflection in bright light and a shadowy "
	+ "depth in twilight.  ",
	"organdie":"It is a fine, translucent cotton delicately woven and "
	+ "commonly used in scarves, light shirts and blouses, and occasionally "
	+ "bathrobes.  Placed over your eyes, you can still see through it "
	+ "somewhat, and when worn, the skin can clearly be seen beneath.  ",
	"rabbit":"It is soft, white rabbit fur.  ",
	"sable":"It is deeply rich, black sable fur.  ",
	"silk":"It is a very light, exceptionally strong, and luxuriously soft "
	+ "cloth woven from the unraveled cocoons of moethes.  ",
	"snake":"It is smoothly polished, scaly green snake skin.  ",
	"suede":"It is a very soft, textured leather.  Suede must be "
	+ "painstakingly cured and worked to be so desirable.  As such it is "
	+ "expensive.  ",
	"swansdown":"It is a heavy napped, cotton flannel often used by "
	+ "outdoor travellers and highly regarded for its breathe-ability, "
	+ "durability, and silky softness.  It is a specialty of the Dresnos "
	+ "shipping company who keeps their source well guarded.  ",
	"wool":"It is a thick, coarse cloth woven from sheephair.  It is well "
	+ "regarded for its heat retention and comfort when not worn directly "
	+ "upon sensitive skin.  "]);

string
query_to_jail()
{
	return "south";
}

void
reset_palan_room()
{
	if (!daiv)
	{
		daiv = clone_object(MERCH + "living/daiv");
		daiv->move(TO);
	}
}

void
create_palan_room()
{
    config_default_trade();

    SHORT("Robe merchant shop in the merchants quarter");
    LONG("Robes and coats in stylized poses have been pinned high up on the "
	+ "translucent marble blocked walls of this high-ceilinged, large shop.  "
	+ "Circular racks of all varieties of robes and coats are arranged "
	+ "throughout the shop, and there is an oak-topped counter along the "
	+ "north wall.  Behind the counter is a great marble sign and a "
	+ "staircase leading up.  By the door in the south is a window looking "
	+ "out onto Merchants' Way.\n");

	ITEM(({"street", "way", "merchants' way", "merchants way"}), "Through "
	+ "the window, you could take a look at the street outside, Merchants' "
	+ "Way.\n");
	ITEM(({"window", "windows"}), "An open window is set into the south wall "
	+ "of the shop affording a good view of the street outside, Merchants' "
	+ "Way.  You may <view street> to have a look.\n");
	ITEM("ceiling", "The ceiling is two stories above you with an oak beamed "
	+ "surface from which hang yellow, paper lanterns on long, thin chains.  "
	+ "A staircase climbs up into the north beneath the marble sign.\n");
	ITEM(({"stairs", "staircase"}), "A flight of stairs rises in the north "
	+ "behind the counter to what would be the third floor taking into "
	+ "account how high the ceiling is on this first floor.\n");
	ITEM(({"chain"}), "Long thin chains suspend yellow paper lanterns from "
	+ "the oak beams of the ceiling high above.\n");
	ITEM(({"lantern", "lanterns", "paper lanterns", "yellow lanterns"}),
	  "Yellow, paper lanterns shed warm, even light about the large shop from "
	+ "their perches at the ends of long, thin chains hanging from the oak "
	+ "beams of the ceiling high above.\n");
	ITEM("floor", "The floor of the shop is comprised of large, "
	+ "translucent marble blocks cleaned and polished to a reflective "
	+ "shine.\n");
	ITEM("wall", "Which wall do you want to examine?  North, east, south, or "
	+ "west?\n");
	ITEM("walls", "The walls of the shop are comprised of translucent "
	+ "marble blocks.  They are clean and polished.\n");
	ITEM(({"east wall", "west wall"}), "Pinned high up on the east and west "
	+ "walls are robes and coats in stylized, action poses.  There is a "
	+ "window on each wall but they have been boarded up and nailed shut.  "
	+ "Someone must be particular about their privacy.\n");
	ITEM("south wall", "The exit door and a window are set into the "
	+ "south wall.  Through them you may enter or view the street outside, "
	+ "Merchants' Way <view street>.\n");
	ITEM("north wall", "A great marble sign hangs above a counter on the "
	+ "north wall.  Below it is a staircase rising to the next floor.\n");
	ITEM(({"block", "blocks", "marble blocks"}), "Large blocks of marble were "
	+ "used in the construction of the shop.  They are translucent white like "
	+ "most marble in the city and kept clean and daily polished.\n");
	ITEM(({"rack", "racks"}), "Robes and coats are arranged on hangars on "
	+ "shiny steel, circular racks throughout the large shop.  You may "
	+ "<peruse robes> or <check> on a particular article of clothing or "
	+ "material.\n");
	ITEM(({"sign", "marble sign", "great sign"}), "A great, marble sign "
	+ "hangs behind the counter on the north wall.  You may read or mread "
	+ "it.\n");
	ITEM("door", "An open door leads south onto Merchants' Way and the "
	+ "merchants quarter.\n");

	set_tell_time(240);

	add_tell("@@get_tell_time@@" + "\n");

	add_smell("vampire", "The air is fragrant with the smells of new, "
	+ "unworn clothing.  The scent of blood is weak here.");
	add_smell("morgul", "The air is fragrant with the smells of new, "
	+ "unworn clothing.");
	add_smell("human", "The air is fragrant with the smells of new, "
	+ "unworn clothing.");
	add_smell("elf", "The air is fragrant with the smells of new, "
	+ "unworn clothing and human dyes.");
	add_smell("goblin", "The air is fragrant with the smells of new, "
	+ "unworn clothing, fur, and reptilian skins.");
	add_smell("dwarf", "The air is fragrant with the smells of new, "
	+ "unworn clothing.");
	add_smell("hobbit", "The air is fragrant with the smells of new, "
	+ "unworn clothing.");
	add_smell("gnome", "The air is fragrant with the smells of new, "
	+ "unworn clothing and human dyes.");
	add_smell("minotaur", "The air is fragrant with the smells of new, "
	+ "unworn clothing, fur, and reptilian skins.");
	add_smell("halfhuman", "The air is fragrant with the smells of new, "
	+ "unworn clothing.");
	add_smell("halfelf", "The air is fragrant with the smells of new, "
	+ "unworn clothing.");
	add_smell("orc", "The air is fragrant with the smells of new, "
	+ "unworn clothing, fur, and reptilian skins.");
	add_smell("hobgoblin", "The air is fragrant with the smells of new, "
	+ "unworn clothing, human dyes, fur, and reptilian skins.");
	add_smell("kender", "The air is fragrant with the smells of new, "
	+ "unworn clothing.");
	add_smell("drow", "The air is fragrant with the smells of new, "
	+ "unworn clothing and human dyes.");
	add_smell("noldor", "The air is fragrant with the smells of new, "
	+ "unworn clothing and human dyes.");
	add_smell("uruk", "The air is fragrant with the smells of new, "
	+ "unworn clothing, fur, and reptilian skins.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "smells of new clothes.");
	add_smell("unknown", "You smell the air fragrant with the smells of new "
	+ "clothes, but what the heck race are you?  Why not mail "
	+ "Krynn for fun?");

	EXIT(MERCH + "wr4", "south", 0, 0);
	EXIT(MERCH + "not", "up", "@@place_closed", 0);
	
	CMD(({"robes", "coats"}), ({"peruse"}), "@@peruse_robes");
	CMD(({"way", "street", "merchants way", "merchants' way"}), "view",
		  "@@view_plaza");
	CMD(({"sign", "marble sign"}), "read", "@@read_sign");
	CMD(({"sign", "marble sign"}), "mread", "@@mread_sign");

	reset_palan_room();
}

int
place_closed()
{
	write("You climb the high staircase to the next level but find a door "
	+ "with eleven locks, bolts, and guard-chains preventing access.  "
	+ "Someone must really be concerned with security.\n");
	say(QCTNAME(TP) + " climbs the high staircase in the north to the next "
	+ "level but returns a moment later with a dejected look.\n");
	return 1;
}

peruse_robes() 
{
	write("You carefully peruse the robes and coats on the racks.  There is "
	+ "a wide variety of types and styles.  You can take a closer look "
	+ "at any of the articles of clothing or materials with <check>.\n");
	say(QCTNAME(TP) + " casually peruses the robes and coats arranged on "
	+ "the racks about the store.\n");
	return "";
}

view_plaza()
{
	/* This function returns an equivalent of 'look' from wr4
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
	write("Out the window along the south wall, you can make out "
	+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the street you see " + desc + ".\n");

	say(QCTNAME(TP) + " gazes out the window along the south wall.\n");
 
	return 1;
}

public int
read_sign()
{
	say(QCTNAME(TP) + " studies the great, marble sign on the north wall.\n");
	write("The sign reads...\n");
	cat(MERCH + "obj/robe_sign.txt", 1, 50);

	return 1;
}

public int
mread_sign()
{
	string file = MERCH + "obj/robe_sign.txt";

	say(QCTNAME(TP) + " studies the great, marble sign on the north wall.\n");
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
		write("Check what?  The robes or coats arranged through the shop?  "
		+ "You may want to peruse them first or even <read sign>.\n");
		return 1;
	}

	if (check = name_arm_to_info[str])
	{
		write("You check out the " + str + ".  " + check + "\n");
		say(QCTNAME(TP) + " checks out the " + str + ".\n");
		return 1;
	}
	write("That is not a valid sample of robe, coat, or material.  Peruse "
	+ "them first or even <read sign>.\n");

	return 1;
}

int
daiv_delay()
{
	if (daiv)
	{
		string daivact = one_of_list(({"shudder", "peer nerv", "emote bites "
		+ "his nails fervently.", "shout Tre'Gannin!  I know you're there!",
		"say Tre'Gannin?  Hello?  Who's there?", "emote flashes his eyes "
		+ "left and right suddenly.", "emote shivers as he clutches himself "
		+ "saying:  It... It's cold... sso cold.", "say Did you see that?!?  "
		+ "Well did you???"}));

		daiv->command(daivact);
	}
	return 1;
}

string
get_tell_time()
{
	string ttell = "";
	
	if (random(4) == 1)
	{
		ttell += one_of_list(({"As the clouds pass by outside, their "
		+ "shadows drift across the racks of clothing."}));

		set_alarm(1.0, 0.0, "daiv_delay");

		return ttell;
	}

    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	ttell += one_of_list(({"A misty morning breeze drifts in through "
	+ "the window beside the door on the south wall.", one_of_list(({"An "
	+ "aesthetic", "A pair of aesthetics", "A group of aesthetics"}))
	+ " walks in and peruses the robes on the racks."}));

	break;

    case TOD_DAY:
	ttell += one_of_list(({"A warm breeze drifts in through the window "
	+ "beside the door on the south wall.", "The clouds overhead outside "
	+ "drift by sending shafts of golden light in through the window "
	+ "beside the door.", one_of_list(({"A group of young boys",
	  "A young boy", "A pair of young boys"})) + " walks in and gazes at "
	+ "the coats hung upon the racks in awe before leaving.",
	  "The robes and coats on the racks sway to and fro on a warm afternoon "
	+ "breeze"}));

	break;

    case TOD_TWILIGHT:
	ttell += one_of_list(({"A cool evening breeze drifts in through the "
	+ "window beside the door on the south wall.", "A young boy with a "
	+ "tousled mop of hair lights the paper lamps around the shop as "
	+ "night approaches.", "The robes and coats on the racks sway to and fro "
	+ "on a cool evening breeze."}));

    break;

    case TOD_NIGHT:
	ttell += one_of_list(({"A cool, refreshing night breeze drifts in "
	+ "through the window beside the door on the south wall.", "The "
	+ "clouds overhead outside drift by sending rays of silver "
	+ "starlight in through the window beside the door.", "Outside in the "
	+ "night darkened street, a constable peers in through the window "
	+ "by the door nodding as he passes on.", "A cloaked figure leaves "
	+ "quietly out the door into the night.", "A cool night breeze drifts in "
	+ "through the window beside the door on the south wall.", "The "
	+ "clouds overhead outside drift by sending rays of pale moonlight in "
	+ "through the window beside the door.", "The robes and coats on the "
	+ "racks sway to and fro on a cool, refreshing night breeze."}));

	break;

    default:
	break;
    }
    return ttell;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}
