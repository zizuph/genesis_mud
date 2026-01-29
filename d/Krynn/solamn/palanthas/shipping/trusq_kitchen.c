/*
 * Mortis 12.2005
 *
 * Kitchen of merchant house Trusq in shipping quarter of Palanthas.
 */

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include CLOCKH

#define FOUND_CANDY_TRUSQ		"_i_found_candy_in_trusq"
#define DUMBWAITER_LOC			(SHIP + "trusq_dumb")

inherit SHIP_ROOMBASE;


object cook, indumb, *inv, *ppl;

/* Prototypes */
int enter_dumb(string str);
int pull_rope(string str);
string is_dumb_here();

string
query_to_jail()
{
	return "west";
}

void
reset_palan_room()
{
	if (!cook)
	{
		cook = clone_object(SHIP + "living/trusq_cook");
		cook->move(TO);
	}

/*	if (!(indumb = find_object(DUMBWAITER_LOC)))
	{
		DUMBWAITER_LOC->load();
		object mort = find_living("mortis");
		mort->catch_msg("hi\n");
	}*/
}

void
create_palan_room()
{
	object backdoor;

    SHORT("In the kitchen of a merchant estate");
    LONG("Dark, oak paneling lines the walls of this kitchen from "
	+ "the ground up to three feet with polished, translucent white marble "
	+ "taking over from there.  A large fireplace occupies the entire "
	+ "northwest corner of the kitchen.  " + "@@whats_cooking@@"
	+ "  The walls are lined with hanging pots, pans, cooking utensils, "
	+ "and shelves of ingredients.  " + "@@activity@@" + "\n");

	ITEM("hall", "The hall is west of here.\n");
	ITEM("kitchen", "You are in the kitchen.  Have a <look> around?\n");
	ITEM(({"wall", "walls", "panelling"}), "The bottom three feet of the "
	+ "walls in this kitchen have been paneled in wide strips of dark stained "
	+ "oak.  From there up is polished, translucent white marble.  The "
	+ "paneling and marble are separated by a wide strip of oak trim.  The "
	+ "walls are lined with hanging pots, pans, cooking utensils, and "
	+ "shelves of ingredients.  There is a dumbwaiter in the southwest "
	+ "corner above a counter.\n");
	ITEM("marble", "The marble in the kitchen is translucent white and "
	+ "polished to a gleaming shine.\n");
	ITEM("floor", "The floor is made of large blocks of translucent white "
	+ "marble and polished to a shine.\n");
	ITEM("ceiling", "The ceiling has been finished with "
	+ "translucent white marble.\n");
	ITEM("trim", "A wide strim of oak trim separates the paneling from the "
	+ "marble.\n");
	ITEM(({"pot", "pots", "pan", "pans", "cooking utensils", "utensil",
	  "utensils", "shelf", "shelves", "ingredient", "ingredients"}), "The "
	+ "walls are lined with hanging pots, pans, cooking utensils, and "
	+ "shelves of ingredients.\n");
	ITEM(({"fire", "fireplace"}), "There is a large fireplace occupying "
	+ "the entire northwest corner of the kitchen.  " + "@@whats_cooking@@"
	+ "\n");
	ITEM(({"servant", "servants"}), "White aproned servants help the cook "
	+ "prepare food here in the kitchen.\n");
	ITEM(({"egg", "eggs", "bacon", "potato", "potatoes", "chicken", "pig",
	  "lamb", "rack", "venison", "haunch", "beef", "stew", "vegetable",
	  "vegetables"}), "It looks delicious.\n");
	ITEM(({"cutting board", "board"}), "There is a cutting board on the "
	+ "east counter.  Below it is a cupboard.\n");
	ITEM("cupboard", "There is a small cupboard below the cutting board "
	+ "on the east counter.  It is filled with various jars.\n");
	ITEM(({"jar", "jars"}), "Jars of dried peas, beans, stewed tomatoes, "
	+ "and other sundry items are stored in the cupboard beneath the "
	+ "cutting board on the east counter.\n" + "@@find_candy");
	ITEM("counter", "A marble topped counter lines the walls.\n");
	ITEM("dumbwaiter", "Above the counter in the southwest corner is a "
	+ "small dumbwaiter used to send meals up to the higher floors by "
	+ "means of a rope and pulley system.  " + "@@is_dumb_here@@" + "\n");
	ITEM(({"rope", "pulley"}), "A rope within the dumbwaiter shaft hangs "
	+ "out of an opening beside the dumbwaiter allowing the dumbwaiter to "
	+ "be hoisted to the upper floors via a pulley attached high above.  "
	+ "You can pull the left rope or the right to work the dumbwaiter.\n");
	ITEM("opening", "In a small opening in the wall beside the dumbwaiter "
	+ "hangs a rope used to hoist the dumbwaiter up to the upper floors.  "
	+ "You can pull the left rope or the right to work the dumbwaiter.\n");

	add_smell("vampire", "The smells of a variety of recently prepared "
	+ "human meals is strong here.  Your fangs throb with anticipation as "
	+ "you sense hot blood pumping through a great many hearts further "
	+ "in.");
	add_smell("morgul", "The smells of a variety of recently prepared "
	+ "human meals are strong here.");
	add_smell("human", "The smells of a variety of recently prepared, "
	+ "delicious meals fill your senses.");
	add_smell("elf", "The smells of a variety of recently prepared, "
	+ "human meals fill your senses.");
	add_smell("goblin", "The smells of a variety of recently prepared, "
	+ "mostly burnt meals fill your senses.");
	add_smell("dwarf", "The smells of a variety of recently prepared, "
	+ "delicious meals fill your senses.");
	add_smell("hobbit", "The smells of a variety of recently prepared, "
	+ "delicious meals fill your senses, but what's that sweet smell "
	+ "coming from the cupboard beneath the cutting board?  Candy?!?");
	add_smell("gnome", "The smells of a variety of recently prepared, "
	+ "delicious meals fill your senses.");
	add_smell("minotaur", "The smells of a variety of recently prepared, "
	+ "human meals fill your senses.  Now if you can only find a pot "
	+ "big enough for a human.");
	add_smell("halfhuman", "The smells of a variety of recently prepared, "
	+ "delicious meals fill your senses.");
	add_smell("halfelf", "The smells of a variety of recently prepared, "
	+ "delicious meals fill your senses.");
	add_smell("orc", "The smells of a variety of recently prepared, "
	+ "burnt meals fill your nostrils.  You wonder if you can find a pot "
	+ "big enough for manstew.");
	add_smell("hobgoblin", "The smells of a variety of recently prepared, "
	+ "delicious meals fill your senses.");
	add_smell("kender", "The smells of a variety of recently prepared, "
	+ "delicious meals fill your senses, but what's that sweet smell "
	+ "coming from the cupboard beneath the cutting board?  Candy?!?");
	add_smell("drow", "The smells of a variety of recently prepared, "
	+ "human meals fill your senses.");
	add_smell("noldor", "The smells of a variety of recently prepared, "
	+ "human meals fill your senses.");
	add_smell("uruk", "The smells of a variety of recently prepared, "
	+ "burnt meals fill your nostrils.  You wonder if you can find a pot "
	+ "big enough for manstew.");
	add_smell("presence", "A lot of food has been prepared here recently, "
	+ "but it's hard to enjoy in your present state.");
	add_smell("unknown", "A lot of food has been prepared here recently, "
	+ "but what the heck race are you?!?  Why not mail Krynn for fun?");

	CMD(({"dumbwaiter"}), "view", "@@view_dumb");

	backdoor = clone_object(SHIP + "doors/trusq_backdoor2");
	backdoor->move(TO);

	EXIT(SHIP + "trusq_hall", "west", 0, 0);

	reset_palan_room();
	DUMBWAITER_LOC->teleledningsanka();
}

string
whats_cooking()
{
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	return "A skillet of eggs, bacon, and shredded potatoes is sizzling over "
	+ "the fire this morning.";
	break;

    case TOD_DAY:
	return "At the moment there is a " + one_of_list(({"chicken", "pig",
	  "rack of lamb", "venison haunch"})) + " roasting on a spit over the "
	+ "fire.";
	break;

    case TOD_TWILIGHT:
	return "A pot of thick brown, roast beef stew and vegetables is bubbling "
	+ "over the fire this evening.";
    break;

    case TOD_NIGHT:
	return "There is nothing cooking over the fire at night.";
    break;

    default:
	break;
	}
}

string
activity()
{
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	return "The cooks and servants are hustling about this morning.";
	break;

    case TOD_DAY:
	return "The cooks and servants are busy today.";
	break;

    case TOD_TWILIGHT:
	return "The cook is busy cooking for dinner.";
    break;

    case TOD_NIGHT:
	return "There isn't much cooking so it's fairly quiet.";
    break;

    default:
	break;
	}
}

string
find_candy()
{
	if (TP->query_prop(FOUND_CANDY_TRUSQ))
		return "You already found candy here.  There's nothing left for "
		+ "you!\n";

	if (TP->query_skill(SS_AWARENESS) >= 15 + random(21))
	{
		TP->add_prop(FOUND_CANDY_TRUSQ, 1);
		clone_object(SHIP + "obj/trusq_candy_jar")->move(TP);
		return "You find a jar of gum drops and pick it up!\n";
	}

	return "You don't spot any of interest.";
}

string
is_dumb_here()
{
	if (indumb->what_floor() == 1)
		return "The dumbwaiter is presently here.  You may look inside it "
		+ "with <view dumbwaiter>.";
	else
		return "The dumbwaiter is at present not on this floor.";
}

int
view_dumb()
{
	/* This function returns an equivalent of 'look' from trusq_dumb
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *obs;
    string desc;

	NF("The dumbwaiter is not here so you cannot look inside it.\n");
	if (indumb->what_floor() != 1)
		return 0;

	write(DUMBWAITER_LOC->long());
	indumb = find_object(DUMBWAITER_LOC);
	inv = all_inventory(indumb);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write(one_of_list(({"You see "}))
						+ desc + " laying there.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write(one_of_list(({"You can make out "}))
						+ desc + " in the dumbwaiter.\n");
 
	return 1;
}

void 
init()
{
    ::init();
	ADD("enter_dumb", "enter");
	ADD("pull_rope", "pull");
}

int
enter_dumb(string str)
{
	string dumbrace = QRACE(TP);
	
	indumb = find_object(DUMBWAITER_LOC);
	inv = all_inventory(indumb);
	ppl = FILTER_LIVE(inv);

	NF("What?\n");
	if (!str)
		return 0;

	NF("Enter what?  The future?  Have patience.\n");
	if (!parse_command(str, ({}), "[the] [dumb] 'waiter' / 'dumbwaiter'"))
		return 0;

	NF("The dumbwaiter is not on this floor.\n");
	if (indumb->what_floor() != 1)
		return 0;

	NF("There is already someone inside the dumbwaiter!  This must be a "
	+ "popular hangout.\n");
	if (sizeof(ppl) > 0)
		return 0;

	if (TP->query_skill(SS_ACROBAT) >= 15 + random(16) ||
		dumbrace == "hobbit" || dumbrace == "kender" || dumbrace == "gnome")
	{
		write("You contort yourself inside the dumbwaiter.\n");
		TP->move_living("squeezes inside the dumbwaiter in the southwest "
		+ "corner", SHIP + "trusq_dumb", 1, 0);
		return 1;
	}

	write("You can't quite contort yourself to fit inside the dumbwaiter, "
	+ "strain as you might.  You'd need an acrobat to fit inside that "
	+ "thing!\n");
	say(QCTNAME(TP) + " strains to fit inside the dumbwaiter in the "
	+ "southwest corner but can't quite make it.\n");
	return 1;
}

int
pull_rope(string str)
{
	indumb = find_object(DUMBWAITER_LOC);
	inv = all_inventory(indumb);
	ppl = FILTER_LIVE(inv);

	NF("What?\n");
	if (!str)
		return 0;

	NF("Pull " + str + "?  Right here?  Are you mad?!?\n");
	if (!parse_command(str, ({}), "[the] [left] [right] 'rope'"))
		return 0;

	if (parse_command(str, ({}), "[the] [right] 'rope'"))
	{
		NF("The dumbwaiter is too heavy!  Pulling the right rope has no "
		+ "effect.\n");
		if (sizeof(ppl) > 1)
			return 0;

		NF("The dumbwaiter has reached the top and can go no further.  "
		+ "Pulling the right rope has no effect.\n");
		if (indumb->what_floor() == 4)
			return 0;
		
		write("You pull the right rope, and the dumbwaiter rises to the "
		+ "next floor.\n");
		say(QCTNAME(TP) + " pulls the right rope in the southwest corner "
		+ "and hoists the dumbwaiter to the next floor.\n");
		tell_room(DUMBWAITER_LOC, "The dumbwaiter is hoisted up to the "
		+ "next floor.\n");
		indumb->add_floor();
		return 1;
	}

	if (parse_command(str, ({}), "[the] [left] 'rope'"))
	{
		NF("The dumbwaiter has reached the bottom and can go no further.  "
		+ "Pulling the left rope has no effect.\n");
		if (indumb->what_floor() == 1)
			return 0;
		
		write("You pull the left rope, and the dumbwaiter lowers to the "
		+ "next floor.\n");
		say(QCTNAME(TP) + " pulls the left rope in the southwest corner "
		+ "and lowers the dumbwaiter to the next floor.\n");
		tell_room(DUMBWAITER_LOC, "The dumbwaiter is lowered to the "
		+ "next floor.\n");
		indumb->subtract_floor();

		if (indumb->what_floor() == 1)
			tell_room(E(TP), "The dumbwaiter arrives in the southwest "
			+ "corner.\n");

		return 1;
	}

	write("Which rope did you want to pull?  The left or right one?\n");
	return 1;
}
