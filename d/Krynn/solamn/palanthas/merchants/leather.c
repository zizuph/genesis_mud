/* 
 * The leather worker in the Arms district of the merchants quarter
 * of Palanthas.  Crafts leather armour, packs, scabbards, and
 * holsters.
 *
 * add_ask hobbitskin for daronius, animal oil also
 *
 * Mortis 01.2006
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

#define VIEWWEST				(MERCH + "m11")
#define NUM	sizeof(MONEY_TYPES)

object daronius;

// Packs, armours, leathers.
mapping name_arm_to_info = (["suit":"The suit consists of a shirt with "
	+ "reinforced chest and back plates with a series of integrated, "
	+ "buckled straps up each side along the ribs for keeping it snug.  "
	+ "The sleeves end in similarly strapped and buckled bracers with a "
	+ "stiff pauldron over the weapon arm angled to protect the shoulder "
	+ "and neck.  Leather leggings continue down from the shirt with "
	+ "buckled straps down the outside of the thighs and calves keeping "
	+ "the stiff thigh guards and greaves in place.  The suit feels "
	+ "fairly protective for having no metal but the light steel of its "
	+ "buckles.  It is light and supple enough for good maneuverability.",
	"coat":"The coat is long-sleeved ending in stiff bracers with tie straps "
	+ "along the inside.  The coat opens down the front with a series of "
	+ "buckled straps across the opening for cinching it closed.  Stiff "
	+ "plates reinforce the back, each breast, and shoulders, but the "
	+ "coat remains comfortably loose, fairly protective, and light and "
	+ "supple enough for good maneuverability.",
	"greaves":"The greaves are stiff with buckled straps wrapping around the "
	+ "back of the calves.  A set of similar, stiff thigh guards comes "
	+ "with them.", 
	"leggings":"The leggings extend from the waist to the ankles with buckled "
	+ "straps down the outside of the thighs and calves keeping their "
	+ "protective padding in place.  Though strapped down snugly, they "
	+ "feel easy to maneuver in.",
	"breastplate":"The breastplate encompasses all of the chest and back in "
	+ "two firm plates joined along the sides and shoulders with buckled "
	+ "straps.", 
	"cuirasse":"The cuirasse form fits to your chest and back when worn "
	+ "revealing the outline of your form.  It consists of two firm plates "
	+ "joined together along the sides and shoulders with buckled straps.",
	"vest":"The vest is a form fitting, seamless chest and back armour pulled "
	+ "on over the head.  For its protection it is light and supple "
	+ "enough for freedom of movement and maneuverability.",
	"bracers":"The bracers are stiff with buckled straps securing them snugly "
	+ "along the inside of the forearm and comes with a pair of bicep bands "
	+ "for upper arm protection.", 
	"pauldrons":"Pauldrons are stiff pads buckle-strapped over the shoulders "
	+ "and angled to protect the shoulder and neck.  The pad worn over the "
	+ "weapon arm is longer with a piece strapped around the bicep while "
	+ "the other pad worn over the shield arm is shorter to avoid "
	+ "interfering with a shield.",
	"sleeves":"The sleeves are worn snug at their cuffed wrists and shoulders "
	+ "where they end in buckled straps that wrap behind the back to keep "
	+ "them on securely.  The set is loose and padded in between the "
	+ "wrists and shoulders.", 
	"gloves":"The gloves are snug, form fitting, and flare out an inch over "
	+ "the wrists.", 
	"armet":"The armet is a circular protective guard hung over the shoulders "
	+ "with a section that sticks up two inches around the neck and "
	+ "buckled straps and ties keeping it closed down the back.",
	"cap":"cap has a buckled band that wraps around the forehead to keep its "
	+ "loose, padded top on and side guards that hang down in front "
	+ "of the ears.", 
	"helmet":"The helmet has a hardened pointed top, flared neck guard, stiff "
	+ "nose guard, and wide protective straps pulled down in front of the "
	+ "ears and under the chin to keep it on.", 
	"boots":"The boots have stiff, sturdy soles and buckled straps on their "
	+ "outside rising from the ankles up the calves to keep them snug "
	+ "over armour.  They are both protective and supple for ease of "
	+ "maneuverability.",
	"tall-boots":"The tall boots have stiff, sturdy soles and buckled straps "
	+ "on their outside rising from the ankles to midway up the thighs.  "
	+ "Though snug, they are supple and comfortable for ease of "
	+ "maneuverability while remaining protective.", 
	"belt":"The belt has a light steel buckle, and is reinforced along the "
	+ "front and sides for tying pouches.", 
	"liner":"The liner looks as if it needs to be attached within the folds "
	+ "of a cloak or robe for added protection.",
	"backpack":"With a pair of padded shoulder straps " // Packs start here.
	+ "as well as a waist strap, this pack sits comfortably snug against "
	+ "your back and is capable of carrying a great many items safely with "
	+ "<fill> and <empty> for easy use.",
	"belt-pouch":"Requiring a belt to be worn on, this flat rectangular "
	+ "pouch protects even delicate and arcane contents safely with an "
	+ "additional inner layer of silk.  You may <fill> and <empty> it.",
	"knapsack":"With a pair of padded shoulder straps "
	+ "as well as a waist strap, this pack sits comfortably snug against "
	+ "your back and is capable of carrying a great many items safely with "
	+ "<fill> and <empty> for easy use.", 
	"lootsack":"The long lootsack has a wide, drawstringed mouth that is "
	+ "easy to <sackloot> with allowing you to dump a corpse's contents "
	+ "directly within and either <empty> them or <sackdump> them onto the "
	+ "ground.", 
	"rucksack":"With a pair of padded shoulder straps "
	+ "as well as a waist strap, this pack sits comfortably snug against "
	+ "your back and is capable of carrying a great many items safely with "
	+ "<fill> and <empty> for easy use.",
	"sack":"This quality sack has a sturdy leather drawstring and can hold "
	+ "quite a bit with <fill> and <empty>.", 
	"saddlebag":"Designed to allow you to <drape saddlebag on horse>, this "
	+ "large pack is capable of carrying a great many items safely with "
	+ "<fill/empty saddlebag on horse>.", 
	"satchel":"Larger than a pouch, this flat rectangular satchel has a "
	+ "padded strap for wearing over the shoulder and slung across the "
	+ "chest to keep it in place at the hip.  Its additional inner layer "
	+ "of silk protects even delicate and arcane contents.  You may <fill> "
	+ "and <empty> it.",
	"thigh-pouch":"A pair of comfortable straps buckle this flat rectangular "
	+ "pouch snugly along the outside of the thigh where you may easily "
	+ "<fill> and <empty> it.  An additional inner layer of silk protects "
	+ "even delicate and arcane contents safely.", 
	"bandeleria":"A shoulder buckled strap keeps the bandeleria slung "
	+ "across the chest where a dozen knives or more can be stored with "
	+ "<dsheathe/fill> and retrieved easily with <ddraw/empty>.",
	"back-holster":"The adjustable loop rests over the back where it can "
	+ "store a large weapon such as an axe, club, polearm, or bow with "
	+ "<dholster> and keep it within reach until ready for use with <ddraw>.", 
	"belt-sheath":"Requiring a belt to be worn on, this sheath has been "
	+ "designed to <dsheathe> a knife and <ddraw> back out easily.", 
	"boot-sheath":"Slipped inside a boot, this sheath conceals a knife "
	+ "with <dsheathe> and can <ddraw> it back out.",
	"forearm-sheath":"A pair of comfortable straps buckle this sheath "
	+ "snugly along the outside of the forearm where it holds a knife "
	+ "with <dsheath> and can <ddraw> it back easily.",
	"scabbard":"Requiring a belt to be worn on, it has been designed to "
	+ "<dsheathe> a sword and <ddraw> it back out again.", 
	"side-holster":"The adjustable loop rests over the hip where it can "
	+ "store a large weapon such as an axe or a club with <dholster> "
	+ "and keep it within reach until ready for use with <ddraw>.",
	"thigh-sheath":"A pair of comfortable straps buckle this sheath snugly "
	+ "along the outside of the thigh where you may <dsheathe> a knife and "
	+ "<ddraw> it back out easily.",
	"wrist-sheath":"A pair of comfortable straps buckle this sheath "
	+ "snugly inside the forearm where it is difficult to spot.  It "
	+ "holds a knife with <dsheath> and can <ddraw> it back out unseen "
	+ "by a dextrous wearer.",
	"hard":"This is leather boiled in oil, hardening it into "
	+ "form fitting plates.",
	"hide":"This is rhinocerous hide, a thick, nearly impenetrable hide "
	+ "that is much lighter than metal armour.",
	"leather":"This leather is firmer than slow cured soft leather but "
	+ "more flexible than leather hardened in boiling oil.",
	"soft":"This leather is slow cured to be both soft to the touch "
	+ "and protective.",
	"studded":"This leather is expertly cured for a soft feel while remaining "
	+ "highly protective.  Inch diameter studs, their two inch diameter "
	+ "steel plates hidden beneath the leather, stick out every few inches "
	+ "giving the armour strong protections without great weight.",
	"suede":"Suede is a very soft, textured leather.  Suede must be "
	+ "painstakingly cured and worked to not only be so desirable but "
	+ "protective as well.  As such it is expensive."]);

string
query_to_jail()
{
  return "west";
}

void
reset_palan_room()
{
	if (!daronius)
	{
		daronius = clone_object(MERCH + "living/daronius");
		daronius->move(TO);
	}
}

void
create_palan_room()
{
    config_default_trade();

    SHORT("Arms district leather worker shop");
    LONG("On the translucent marble blocked walls of this large shop are hung "
	+ "a great many varieties of pieces of leather armour, sheets of leather, "
	+ "and leather packs of all sizes.  A wide fireplace is situated against "
	+ "the east wall where a cauldron of oil bubbles, and a few angled "
	+ "tables are arranged nearby where cutting tools and shaped leather are "
	+ "arrayed.  By the door in the west is a window looking out onto the "
	+ "cul-de-sac of Emptoris Row, and a marble sign hangs above the "
	+ "fireplace.\n");

	ITEM(({"plaza", "court", "cul-de-sac"}), "Through the window, you could "
	+ "take a look at the cul-de-sac of Emptoris.\n");
	ITEM(({"window", "windows"}), "An open window is set into the west wall "
	+ "of the shop affording a good view of the cul-de-sac of Emptoris Row "
	+ "outside and stirring the air with a cool breeze.  You may "
	+ "<view court> to have a look.\n");
	ITEM("ceiling", "The shop is two stories with an oak beamed ceiling "
	+ "from which hang iron lanterns.  Stairs spiral up into the northeast "
	+ "corner, and a black brick chimney from the wide fireplace rises "
	+ "through it along the east wall.\n");
	ITEM(({"stairs", "staircase"}), "A small, spiraling flight of stairs "
	+ "rises to the second floor in the northeast of the shop, but there "
	+ "is a chain blocking customers from climbing it.\n");
	ITEM("chain", "A sturdy, iron chain bars access to the stairs in the "
	+ "northeast of the room.  Did you want to try to <break chain>?\n");
	ITEM(({"lantern", "lanterns", "iron lanterns"}), "Large iron-framed "
	+ "lanterns with paper panels hang from the oak beams of the ceiling.\n");
	ITEM("floor", "The floor of the shop is comprised of large, "
	+ "translucent marble blocks polished and clean despite the traffic of "
	+ "large numbers of customers each day.\n");
	ITEM("wall", "Which wall do you want to examine?  North, east, south, or "
	+ "west?\n");
	ITEM("walls", "The walls of the shop are comprised of translucent "
	+ "marble blocks.  They are clean and polished.\n");
	ITEM("north wall", "Hanging from hooks upon the north wall are leather "
	+ "packs of great many varieties and sizes.  You may <peruse general> if "
	+ "you like or <check> individual varieties.\n");
	ITEM("east wall", "Along the east wall is a spiral staircase in the "
	+ "northeast and a wide fireplace in the center where a cauldron "
	+ "bubbles.\n");
	ITEM("south wall", "The exit door and a window are set into the "
	+ "south wall.  Through them you may enter or view the cul-de-sac of "
	+ "Emptoris Row outside.\n");
	ITEM("west wall", "The west wall is filled with an assortment of the "
	+ "master smith's weaponry.  Above the display is a marble sign beneath "
	+ "which are five small signs.\n");
	ITEM(({"oil", "cauldron"}), "A very large, iron cauldron of oil bubbles "
	+ "and boils over the fire in the fireplace set in the east wall.  This "
	+ "is where the leather worker boils leather to harden it into armour.\n");
	ITEM(({"block", "blocks", "marble blocks"}), "Large blocks of marble were "
	+ "used in the construction of the shop.  They are translucent white like "
	+ "most marble in the city and kept clean and daily polished.\n");
	ITEM(({"fire", "fireplace", "chimney", "brick chimney", "black chimney",
	  "black brick chimney"}), "A fire burns in the wide fireplace in the "
	+ "east wall upon which boils a very large cauldron of oil.  A black "
	+ "brick chimney rises against the east wall and into the ceiling "
	+ "above it.\n");
	ITEM(({"tool", "tools", "leather", "models", "model"}), "Cutting tools, "
	+ "armour shaping models, and shaped leather pieces are arrayed on the "
	+ "angled tables in the room.\n");
	ITEM("hooks", "Hooks on the north wall hold various leather packs for "
	+ "sale.\n");
	ITEM(({"rack", "racks"}), "Oak racks on the south wall hold varieties of "
	+ "many leather armour types as examples of what the leather worker has "
	+ "available for order.  You may <peruse armours> or <check> on a "
	+ "particular type.\n");
	ITEM(({"table", "tables"}), "Oak tables, angled for cutting leather, "
	+ "hold a variety of cutting tools, models, and pieces of leather.  They "
	+ "are arranged near the fireplace.\n");
	ITEM(({"armour", "armours"}), "A vast assortment of the leather worker's "
	+ "armours adorns the south wall.  You may peruse them if you wish.\n");
	ITEM("leather", "The air is thick with the rich smell of new leather.  "
	+ "It's everywhere in this shop, hanging in sheets, on cutting tables, "
	+ "fashioned into packs hanging on the north wall and armours on the "
	+ "south.\n");
	ITEM(({"sign", "marble sign", "signs"}), "A marble sign hangs on the east "
	+ "wall above the fireplace.  You may read or mread it.  Below it is "
	+ "another marble sign.  To check them out you may read sign, then read "
	+ "general.\n");
	ITEM("door", "An open door leads west into the cul-de-sac of Emptoris "
	+ "row and the Arms district.\n");

	set_tell_time(240);

	add_tell("@@get_tell_time@@" + "\n");

	add_smell("vampire", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "oil for boiling leather.  The scent of blood is weak here.");
	add_smell("morgul", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "oil for boiling leather.  Could this oil be used for boiling "
	+ "hobbitskin into armour?");
	add_smell("human", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "oil for boiling leather.");
	add_smell("elf", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "oil for boiling leather.  You wonder what manner of oil it is.");
	add_smell("goblin", "The air is thick with the mouth-watering, rich "
	+ "smells of new leather and from the cauldron in the fireplace comes "
	+ "the smell of oil for boiling leather.  You don't know which to try "
	+ "first as your stomach growls hungrily, urging you to action.");
	add_smell("dwarf", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "oil for boiling leather.  The smells bring back faint memories of "
	+ "gearing for battle but lack the tang of metal for which you yearn.");
	add_smell("hobbit", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "oil for boiling leather.  Nothing pleasant to eat or drink reaches "
	+ "your nose here, but the packs look nicely capable of holding such "
	+ "items.");
	add_smell("gnome", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "oil for boiling leather.  Quite an industrial, little human business, "
	+ "this leather working shop.");
	add_smell("minotaur", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "oil for boiling leather.  The smell brings back unpleasant memories of "
	+ "the last time your goose was cooked.");
	add_smell("halfhuman", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "oil for boiling leather.");
	add_smell("halfelf", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "oil for boiling leather.");
	add_smell("orc", "The air is thick with the mouth-watering, rich "
	+ "smells of new leather and from the cauldron in the fireplace comes "
	+ "the smell of oil for boiling leather.  You don't know which to try "
	+ "first as your stomach growls hungrily, urging you to action.");
	add_smell("hobgoblin", "The air is thick with the mouth-watering, rich "
	+ "smells of new leather and from the cauldron in the fireplace comes "
	+ "the smell of oil for boiling leather.  You don't know which to try "
	+ "first as your stomach growls hungrily, urging you to action, but "
	+ "you remind yourself that's not what you're here for.");
	add_smell("kender", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "oil for boiling leather.  You wonder what else you could boil in the "
	+ "cauldron of oil?  Socks?  Candy?  Apples?");
	add_smell("drow", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "oil for boiling leather reminding you strongly of preparations for "
	+ "battle.");
	add_smell("noldor", "The air is thick with the rich smells of new "
	+ "leather and from the cauldron in the fireplace comes the smell of "
	+ "animal oil for boiling leather.  Not the most pleasant oil odour.");
	add_smell("uruk", "The air is thick with the mouth-watering, rich "
	+ "smells of new leather and from the cauldron in the fireplace comes "
	+ "the smell of oil for boiling leather.  Human leather might just make "
	+ "a decent meal if not decent armour.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "air thick with the rich smells of new leather.");
	add_smell("unknown", "You smell the air rich with the smells of new "
	+ "leather, but what the heck race are you?  Why not mail "
	+ "Krynn for fun?");

	EXIT(MERCH + "m11", "west", 0, 0);
	
	CMD(({"armour", "armours"}), ({"peruse"}), "@@peruse_arm");
	CMD(({"general", "pack", "packs"}), "peruse", "@@peruse_general");
	CMD(({"plaza", "the plaza", "court", "the court", "cul-de-sac"}), "view",
		  "@@view_plaza");
	CMD(({"sign", "marble sign"}), "read", "@@read_sign");
	CMD(({"sign", "marble sign"}), "mread", "@@mread_sign");
	CMD(({"general", "pack", "packs", "item", "items"}),
		"read", "@@read_general");
	CMD(({"general", "pack", "packs", "item", "items"}),
		"mread", "@@mread_general");
	CMD(({"chain", "chains"}), "break", "@@break_chain");

	reset_palan_room();
}

peruse_arm() 
{
	write("You carefully peruse the armours on the wall.  There is a "
	+ "wide variety of types and styles.  You can take a closer look "
	+ "at any of them with <check>.\n");
	say(QCTNAME(TP) + " carefully peruses the samples of leather armour on "
	+ "the south wall.\n");
	return "";
}

peruse_general()
{
	write("You casually peruse the general items on the wall.  There is a "
	+ "wide variety of goods.  You can take a closer look at any of them with "
	+ "<check>.\n");
	say(QCTNAME(TP) + " casually peruses the general items on the north "
	+ "wall.\n");
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

	write(VIEWWEST->long());
	target = find_object(VIEWWEST);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write("Out the window along the west wall, you can make out "
	+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the court you see " + desc + ".\n");

	say(QCTNAME(TP) + " gazes out the window along the west wall.\n");
 
	return 1;
}

public int
read_sign()
{
	say(QCTNAME(TP) + " studies the marble sign on the east wall.\n");
	write("The sign reads...\n");
	cat(MERCH + "obj/leather_sign.txt", 1, 50);

	return 1;
}

public int
mread_sign()
{
	string file = MERCH + "obj/leather_sign.txt";

	say(QCTNAME(TP) + " studies the marble sign on the east wall.\n");
	write("The sign reads...\n");
	TP->more(read_file(file, 1, 50000));


	return 1;
}

public int
read_general()
{
	say(QCTNAME(TP) + " studies the general sign on the east wall.\n");
	write("The sign reads...\n");
	cat(MERCH + "obj/leather_sign_packs.txt", 1, 50);

	return 1;
}

public int
mread_general()
{
	string file = MERCH + "obj/leather_sign_packs.txt";

	say(QCTNAME(TP) + " studies the general sign on the east wall.\n");
	write("The sign reads...\n");
	TP->more(read_file(file, 1, 50000));

	return 1;
}

int
break_chain()
{
	int bcrand = random(4);

	if (bcrand == 0)
	{
		write("You attempt to break the chain.\nAfter a convoluted series of "
		+ "thwarted grappling maneuvers you find yourself deep within its "
		+ "grip.\nThe chain breaks you!\n");
		say(QCTNAME(TP) + " attempts to break the chain barring acess to the "
		+ "stairs.\nAfter a convoluted series of thwarted grappling maneuvers "
		+ HE(TP) + " manages to get " + HIMSELF(TP) + " wrapped deep within "
		+ "the chain's grip.\nSadness overtakes " + QTNAME(TP) + ".\n");
		return 1;
	}

	if (bcrand == 1)
	{
		write("The chain will not break try as you might to force it!\nYou "
		+ "try another tactic: Let's just be friends instead, ok chain?\n"
		+ "Nothing happens.\n");
		say(QCTNAME(TP) + " beseeches the chain barring access to the stairs "
		+ "to be " + HIS(TP) + " friend and " + one_of_list(({"stand "
		+ "aside", "play nicely", "STOP IT"})) + ".\n");
		return 1;
	}

	if (bcrand == 2)
	{
		write("Accursed chain!  It still will not break!\nWhy is it doing "
		+ "this to you?!?\n");
		say(QCTNAME(TP) + " cries out to the chain barring access to the "
		+ "stairs:  " + one_of_list(({"Stop harassing me, ok!?!", "Why are "
		+ "you doing this to me?!?", "Don't you realize who I am!?!"}))
		+ "\n");
		return 1;
	}

	write("You try to break the chain only to find the task is "
	+ "impossible.  Nooooooo!\n");
	say(QCTNAME(TP) + " rails against the power of the chain barring "
	+ "access to the stairs as " + HE(TP) + " cries out:  Noooooooo!  "
	+ "Father, why?!?\n");
	return 1;
}

void
help_my_friend()
{
	set_alarm(6.0, 0.0, "help_my_friend2");
}

void
help_my_friend2()
{
	if (daronius)
		daronius->assist_friend();
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
		write("Check what?  Some of the sample armour on the south wall?  "
		+ "The packs on the north wall?  You may want to peruse them first "
		+ "or even <read sign>.\n");
		return 1;
	}

	if (check = name_arm_to_info[str])
	{
		write("You check out the " + str + ".  " + check + "\n");
		say(QCTNAME(TP) + " checks out the " + str + ".\n");
		return 1;
	}
	write("That is not a valid sample of leather work.  Peruse the packs or "
	+ "armours first or even <read sign>.\n");

	return 1;
}

string
get_tell_time()
{
	string ttell = "";
	
	if (random(3) == 1)
	{
		ttell += one_of_list(({"The cauldron of oil on the fireplace pops "
		+ "and bubbles gurblingly.", "A breeze rustles the packs on the "
		+ "north wall as their leather creaks.", "A breeze from the "
		+ "window by the door rustles and creaks the armours hanging on "
		+ "the south wall."}));
		return ttell;
	}

    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	ttell += one_of_list(({"The chain across the stairs sways to and fro on "
	+ "a misty morning breeze.", "A misty morning breeze drifts in through "
	+ "the window beside the door on the west wall.", one_of_list(({"An "
	+ "aesthetic", "A pair of aesthetics", "A group of aesthetics"}))
	+ " walks in and peruses the packs on the north wall."}));

	break;

    case TOD_DAY:
	ttell += one_of_list(({"A warm breeze drifts in through the window "
	+ "beside the door on the west wall.", "The clouds overhead outside "
	+ "drift by sending shafts of golden light in through the window "
	+ "beside the door.", one_of_list(({"A group of young boys",
	  "A young boy", "A pair of young boys"})) + " walks in and gazes at "
	+ "the armour hung upon the south wall in awe before leaving.",
	  "The chain across the stairs sways to and fro on a warm afternoon "
	+ "breeze."}));

	break;

    case TOD_TWILIGHT:
	ttell += one_of_list(({"A cool evening breeze drifts in through the "
	+ "window beside the door on the south wall.", "A tall woman with an "
	+ "all too knowing smirk lights a few small lamps around the smithy as "
	+ "night approaches.", "The chain across the stairs sways to and fro "
	+ "on a cool evening breeze."}));

    break;

    case TOD_NIGHT:
	ttell += one_of_list(({"A cool, refreshing night breeze drifts in "
	+ "through the window beside the door on the south wall.", "The "
	+ "clouds overhead outside drift by sending rays of silver "
	+ "starlight in through the window beside the door.", "Outside in the "
	+ "night darkened cul-de-sac, a constable peers in through the window "
	+ "by the door nodding as he passes on.", "A cloaked figure leaves "
	+ "quietly out the door into the night.", "A cool night breeze drifts in "
	+ "through the window beside the door on the west wall.", "The "
	+ "clouds overhead outside drift by sending rays of pale moonlight in "
	+ "through the window beside the door.", "The chain across the stairs "
	+ "sways to and fro on a cool, refreshing night breeze."}));

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
