/*
 * Mortis 03.2006 
 *
 * The business mgr's office in merchant house Trusq.
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <ss_types.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

#define VIEWSTREET				(SHIP + "alley201")
#define DUMBWAITER_LOC			(SHIP + "trusq_dumb")

inherit SHIP_ROOMBASE;

int sackhere;
object acc1, indumb, *inv, *ppl;

/* Prototypes */
int enter_dumb(string str);
int pull_rope(string str);
string is_dumb_here();
string desk_search();

void
reset_palan_room()
{
	if (!acc1)
	{
		acc1 = clone_object(SHIP + "living/trusq_manager");
		acc1->move(TO);
	}

	if (random(5) == 1)
		sackhere = 0;
}

void
create_palan_room()
{
	object offdoor;

    SHORT("A private office in a merchant estate");
    LONG("Dark, oak paneling lines the walls of this private office from "
	+ "the ground up to three feet with polished, translucent white marble "
	+ "taking over from there.  The office contains a desk, filing cabinet, "
	+ "a few ferns, and a closed cupboard opening into a dumbwaiter.\n");

	ITEM("office", "You are in the office.  Have a <look> around?\n");
	ITEM(({"wall", "walls", "panelling"}), "The bottom three feet of the "
	+ "walls in this room have been paneled in wide strips of dark stained "
	+ "oak.  From there up is polished, translucent white marble.  The "
	+ "paneling and marble are separated by a wide strip of oak trim.\n");
	ITEM("marble", "The marble in the room is translucent white and "
	+ "polished to a gleaming shine.\n");
	ITEM("floor", "The floor is made of large sheets of translucent white "
	+ "marble and polished to a shine.\n");
	ITEM("ceiling", "The ceiling has been finished with translucent white "
	+ "marble.\n");
	ITEM("trim", "A wide strim of oak trim separates the paneling from the "
	+ "marble.\n");
	ITEM(({"stairs", "staircase"}), "A large staircase with oak railing "
	+ "is west of here.\n");
	ITEM(({"cabinet", "file", "files", "paperwork", "papers", "paper"}),
	  "The office contains an ornate oak desk, a tall filing cabinet, and "
	+ "has neatly arranged paperwork here and there.\n");
	ITEM("desk", "@@desk_search");
	ITEM(({"fern", "ferns"}), "A row of three ferns sits beneath the the "
	+ "window in the east wall.  They are well-watered with dark soil in "
	+ "their clay pots.\n");
	ITEM(({"soil", "pot", "pots"}), "Dark soil fills the clay pots of the "
	+ "ferns resting below the east window.\n");
	ITEM(({"window", "east window"}), "The window in the east wall looks "
	+ "out onto a side street below the estate.  You may peer out it with "
	+ "<view street>.\n");
	ITEM(({"dumbwaiter", "cupboard"}), "Above the desk in the southwest "
	+ "corner covered by cupboard doors with a latch is a small dumbwaiter "
	+ "used to send meals up to the higher floors by means of a rope "
	+ "and pulley system.  " + "@@is_dumb_here@@" + "\n");
	ITEM(({"rope", "pulley"}), "A rope within the dumbwaiter shaft hangs "
	+ "out of an opening beside the dumbwaiter allowing the dumbwaiter to "
	+ "be hoisted to the upper floors via a pulley attached high above.  "
	+ "You can pull the left rope or the right to work the dumbwaiter.\n");
	ITEM("opening", "In a small opening in the wall beside the dumbwaiter "
	+ "hangs a rope used to hoist the dumbwaiter up to the upper floors.  "
	+ "You can pull the left rope or the right to work the dumbwaiter.\n");

	add_smell("vampire", "The air is clean, but you smell ink and old, dry "
	+ "paper here.  Your fangs throb with anticipation as you sense hot "
	+ "blood pumping through a great many hearts closeby.");
	add_smell("morgul", "The air is clean, but you smell ink and old, dry "
	+ "paper here.  The ink is quality and the paper well-kept.");
	add_smell("human", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("elf", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("goblin", "The air is clean, but you smell old, dry things "
	+ "here.");
	add_smell("dwarf", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("hobbit", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("gnome", "The air is clean, but you detect ink and old, dry "
	+ "paper here.  The ink is quality and the paper well-kept.");
	add_smell("minotaur", "The air is clean, but you smell ink and old, dry "
	+ "paper here.  The smell of man is thick here.");
	add_smell("halfhuman", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("halfelf", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("orc", "The smell of old, dry things in the sterile air cannot "
	+ "mask the scent of so much manflesh in this place.");
	add_smell("hobgoblin", "The clean air would indicate humans keep this "
	+ "place well tended.  You smell ink and paper here.");
	add_smell("kender", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("drow", "The sterile air here would indicate the place is "
	+ "clean by human standards.  You detect the smells of ink and old, dry "
	+ "paper eaherest.");
	add_smell("noldor", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("uruk", "The smell of old, dry things in the sterile air "
	+ "cannot mask the scent of so much manflesh in this place.");
	add_smell("presence", "You don't pick up much in your current state.");
	add_smell("unknown", "The air is clean and smells of ink and paper, but "
	+ "what the heck race are you?!?  Why not mail Krynn for fun?");

	CMD(({"dumbwaiter"}), "view", "@@view_dumb");
	CMD(({"street"}), "view", "@@view_street");

	offdoor = clone_object(SHIP + "doors/trusq_office_door2");
	offdoor->move(TO);

	reset_palan_room();
	DUMBWAITER_LOC->teleledningsanka();
}

string
desk_search()
{
	string sackcol = one_of_list(({"brown", "mottled-brown", "grey", "blue"}));
	object sackh;

	if (sackhere == 0 && TP->query_skill(SS_AWARENESS) > 20 + random(21))
	{
		sackh = clone_object(MERCH + "obj/lgeneral");
		sackh->set_general_data("plain" + "&&" + sackcol + "&&"
								+ "leather" + "&&" + "sack");
		sackh->move(TP);
		sackhere = 1;
		return "The oak desk is ornately carved with neat stacks of papers "
		+ "arranged upon it and several drawers beneath.  In one of them, "
		+ "you find a " + sackh->short() + " and pick it up!\n";
	}

	return "The oak desk is ornately carved with neat stacks of papers "
	+ "arranged upon it and several drawers beneath.\n";
}

string
is_dumb_here()
{
	if (indumb->what_floor() == 2)
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
	if (indumb->what_floor() != 2)
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
	if (indumb->what_floor() != 2)
		return 0;

	NF("There is already someone inside the dumbwaiter!  This must be a "
	+ "popular hangout.\n");
	if (sizeof(ppl) > 0)
		return 0;

	if (TP->query_skill(SS_ACROBAT) >= 15 + random(16) ||
		dumbrace == "hobbit" || dumbrace == "kender" || dumbrace == "gnome")
	{
		write("You unlatch the cupboard doors, open them, and contort "
		+ "yourself inside the dumbwaiter.\n");
		TP->move_living("unlatches the cupboard doors and squeezes inside "
		+ "the dumbwaiter in the southwest corner", SHIP + "trusq_dumb", 1, 0);
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
		indumb->add_floor();

		if (indumb->what_floor() == 2)
			tell_room(E(TP), "The dumbwaiter arrives at this floor.\n");
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
		indumb->subtract_floor();

		if (indumb->what_floor() == 2)
			tell_room(E(TP), "The dumbwaiter arrives at this floor.\n");

		return 1;
	}

	write("Which rope did you want to pull?  The left or right one?\n");
	return 1;
}

int
view_street()
{
	/* This function returns an equivalent of 'look' from alley201
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWSTREET->long());
	target = find_object(VIEWSTREET);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write(one_of_list(({"From above you can make out ",
						"You believe you spot ",
						"Your eyes come across "}))
						+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write(one_of_list(({"Down below you see ",
						"You notice below ",
						"Down below you spy "}))
						+ desc + " in the side street.\n");
 
	return 1;
}
