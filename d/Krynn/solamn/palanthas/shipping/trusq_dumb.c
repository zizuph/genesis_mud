/*
 * Mortis 12.2005
 *
 * Dumbwaiter of merchant house Trusq in shipping quarter of Palanthas.
 *
 * EDITED:  The difficulty of Find and Remove Traps checks was based
 * on the assumption that krynn thieves had a skill level of 50.  It is
 * actually 40 which meant a master thief got slashed by the trap more
 * often than disarming it.  Difficulty has been lowered in accordance
 * with my original intention.
 *
 * Mortis 01.2008
 */

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include CLOCKH

#define TRUSQ_FLOOR1			(SHIP + "trusq_kitchen")
#define TRUSQ_FLOOR2			(SHIP + "trusq_priv_office")
#define TRUSQ_FLOOR3			(SHIP + "trusq_priv_guardroom")
#define TRUSQ_FLOOR4			(SHIP + "trusq_master")
#define TRUSQ_DUMB_TRAP			"_i_found_trusq_dumbwaiter_trap"

inherit SHIP_ROOMBASE;

int myfloor = 1, fopen2 = 1, fopen3 = 1, fopen4 = 1, canpick2, canpick3,
	canpick4, trapped = 1;

/* Prototypes */
int pull_rope(string str);
int exit_dumb(string str);
string dumb_loc();

void
reset_palan_room()
{
	fopen2 = 1;
	fopen3 = 1;
	fopen4 = 1;
	trapped = 1;
}

void
create_palan_room()
{
    SHORT("In the dumbwaiter of a merchant estate");
    LONG("This small, cubicle dumbwaiter is paneled in cedarwood and barely "
	+ "large enough for an acrobat or little person to contort themselves "
	+ "into.  A rope hangs down the dumbwaiter shaft that you can barely "
	+ "reach, and there is a small opening on the north side to exit.  "
	+ "@@dumb_loc@@" + "\n");

	ITEM(({"wall", "walls", "panelling", "cedar", "cedarwood", "floor",
	  "ceiling"}), "The panels of the dumbwaiter are covered in aromatic, "
	+ "fresh cedarwood.\n");
	ITEM("dumbwaiter", "You are in the dumbwaiter.  Have a <look> aroudn?\n");
	ITEM(({"rope", "pulley"}), "A rope within the dumbwaiter shaft hangs "
	+ "just within reach of the opening in the north panel allowing the "
	+ "dumbwaiter to be hoisted to the upper floors via a pulley attached "
	+ "high above.  You can pull the left rope or the right to work the "
	+ "dumbwaiter.\n");
	ITEM("opening", "There is an opening in the dumbwaiter's north panel.  "
	+ "Through it, you may exit or go out.  You may also <view opening> to "
	+ "peer out.  " + "@@dumb_loc@@" + "\n");

	add_smell("vampire", "The smell of fresh cedarwood is strong here.  "
	+ "Your fangs throb with anticipation as you sense hot blood pumping "
	+ "through a great many hearts closeby.");
	add_smell("morgul", "The smell of fresh cedarwood is strong here.");
	add_smell("human", "The smell of fresh cedarwood is strong here.");
	add_smell("elf", "The smell of fresh cedarwood is strong here.");
	add_smell("goblin", "The smell of fresh cedarwood is strong here.");
	add_smell("dwarf", "The smell of fresh cedarwood is strong here.");
	add_smell("hobbit", "The smell of fresh cedarwood is strong here.");
	add_smell("gnome", "The smell of fresh cedarwood is strong here.");
	add_smell("minotaur", "The smell of fresh cedarwood is strong here.");
	add_smell("halfhuman", "The smell of fresh cedarwood is strong here.");
	add_smell("halfelf", "The smell of fresh cedarwood is strong here.");
	add_smell("orc", "The smell of fresh cedarwood is strong here.");
	add_smell("hobgoblin", "The smell of fresh cedarwood is strong here.");
	add_smell("kender", "The smell of fresh cedarwood is strong here.");
	add_smell("drow", "The smell of fresh cedarwood is strong here.");
	add_smell("noldor", "The smell of fresh cedarwood is strong here.");
	add_smell("uruk", "The smell of fresh cedarwood is strong here.");
	add_smell("presence", "It smells of cedarwood here, "
	+ "but it's hard to enjoy in your present state.");
	add_smell("unknown", "It smells of fresh cedarwood here, "
	+ "but what the heck race are you?!?  Why not mail Krynn for fun?");

	CMD(({"opening"}), "view", "@@view_opening");

	reset_palan_room();
}

string
dumb_loc()
{
	string forlong = "";

	switch (myfloor)
	{
		case 1:
			forlong = "Presently the opening looks out into the kitchen.";
			break;
		case 2:
			forlong = "Presently the opening looks out onto closed "
			+ "cupboard doors.";
			break;
		case 3:
			forlong = "Presently the opening looks out onto a small, "
			+ "closed wooden door.";
			break;
		case 4:
			forlong = "Presently the opening looks out onto a closed "
			+ "steel panel.";
			break;
		default:
			break;
	}
	return forlong;
}

int
what_floor()
{
	return myfloor;
}

string
cupboard_doors()
{
	return "A pair of small cupboard doors covers the dumbwaiter's north "
	+ "opening.  They are latched from the outside.  Unless you're a skilled "
	+ "lockpick or have a very flat knife, there's no way to <unlatch> the "
	+ "doors.";
}

string
wooden_door()
{
	return "A small wooden door covers the dumbwaiter's north opening.  It "
	+ "has been locked from the outside.  The keyhole is very small on this "
	+ "side making the lock almost impossible to open from in here, but you "
	+ "might be able to <pop> it.";
}

string
steel_panel()
{
	return "A sturdy steel panel covers the dumbwaiter's north opening.  It "
	+ "has been locked from the outside.";
}

int
unlatch_cupboard(string str)
{
	NF("What?\n");
	if (canpick2 != 1)
		return 0;

	NF("Unlatch what?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[the] 'door' / 'cupboard' / 'doors'"))
		return 0;

	NF("The latch is already out of place leaving the cupboard doors "
	+ "unlocked.\n");
	if (fopen2 == 0)
		return 0;

	if (present("flatknife"))
	{
		write("You slip the blade of your flatknife between the cupboard "
		+ "doors and knock the latch up out of place allowing you to "
		+ "exit here.\n");
		fopen2 = 0;
		return 1;
	}

	if (TP->query_skill(SS_OPEN_LOCK) >= 18 + random(15))
	{
		write("Using your lock picking skills, you manage to knock the latch "
		+ "up out of place allowing you to exit here.\n");
		fopen2 = 0;
		return 1;
	}
	
	write("Using your rudimentary lock picking skills, you fail to unlatch "
	+ "the cupboard doors preventing you from exiting here.\n");
	return 1;
}

int
pop_door(string str)
{
	NF("What?\n");
	if (canpick3 != 1)
		return 0;

	NF("Pop what?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[the] 'door' / 'lock'"))
		return 0;

	NF("The lock on the door has already been popped leaving it "
	+ "unlocked.\n");
	if (fopen3 == 0)
		return 0;

	if (TP->query_skill(SS_OPEN_LOCK) >= 30 + random(11))
	{
		write("You hear a satisfying \"Clunk\" from the small, wooden "
		+ "door's lock indicating you may now exit here.\n");
		fopen3 = 0;
		return 1;
	}

	write("Using your basic lock picking skills, you fail to unlock the "
	+ "small, wooden door that prevents you from exiting here.\n");
	return 1;
}

int
pick_steel(string str)
{
	int dmg = -100 - random(250);

	NF("What?\n");
	if (canpick4 != 1)
		return 0;
	
	NF("Pick what?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[the] 'door' / 'panel' / 'lock'"))
		return 0;

	NF("The lock has already been picked leaving the panel unlocked.\n");
	if (fopen4 == 0)
		return 0;

	NF("You move to pick the lock on the steel panel but stop short "
	+ "as you remember it's trapped.  Oh, that's right.  Better disarm "
	+ "it.\n");
	if (trapped == 1 && TP->query_prop(TRUSQ_DUMB_TRAP))
		return 0;

	if (trapped == 1 && TP->query_skill(SS_FR_TRAP) >= 17 + random(25))
	{
		write("You stop short as you notice a trip switch on this side of "
		+ "the keyhole.  The steel panel is trapped!\n");
		TP->add_prop(TRUSQ_DUMB_TRAP, 1);
		return 1;
	}

	if (trapped == 1 && TP->query_prop(TRUSQ_DUMB_TRAP) == 0)
	{
		write("Your stomach drops as you hear the \"Slitch\" of a blade "
		+ "loosing from its trap catch as you ineptly trigger a trip "
		+ "switch guarding this side of the keyhole.  A curved blade "
		+ "flashes out as it swipes in a semi-circle from in between the "
		+ "top of the steel panel and the dumbwaiter slashing your hands "
		+ "badly as it spins back up out of sight.\nYou feel your ability "
		+ "to use your hands dextrously diminish.\n");

		TP->set_skill_extra(SS_OPEN_LOCK, 
        (TP->query_skill_extra(SS_OPEN_LOCK) - 10));
		TP->heal_hp(dmg);

		if (TP->query_hp() <= 0)
			TP->do_die(E(TO));
		
		return 1;
	}

	if (trapped == 0 && TP->query_skill(SS_OPEN_LOCK) >= 40 + random(16))
	{
		write("You hear a satisfying \"Click\" from the steel panel's "
		+ "lock indicating you may now exit here.\n");
		fopen4 = 0;
		return 1;
	}

	write("Your lock picking skills are not up to the task.  You fail to "
	+ "pick the lock on the steel panel.\n");
	return 1;
}

int
disarm_trap(string str)
{
	int dmg = -100 - random(200);

	NF("What?\n");
	if (canpick4 != 1)
		return 0;

	if (TP->query_prop(TRUSQ_DUMB_TRAP) == 0)
		return 0;

	NF("Disarm what?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[the] 'trap'"))
		return 0;

	NF("The blade trap is already disarmed.\n");
	if (trapped != 1)
		return 0;

	if (TP->query_skill(SS_FR_TRAP) >= 20 + random(23))
	{
		write("You hit the trip switch on this side of the keyhole and jerk "
		+ "your hand back to avoid the swipe of the curved blade that arcs "
		+ "down from between the top of the steel panel and the dumbwaiter "
		+ "as you pin the trip switch effectively disarming the trap from "
		+ "springing again... for a while.\n");
		trapped = 0;
		return 1;
	}

	write("Your stomach drops as you hear the \"Slitch\" of a blade "
	+ "loosing from its trap catch as you ineptly trigger a trip "
	+ "switch guarding this side of the keyhole.  A curved blade "
	+ "flashes out as it swipes in a semi-circle from in between the "
	+ "top of the steel panel and the dumbwaiter slashing your hands "
	+ "badly as it spins back up out of sight.\nYou feel your ability "
	+ "to use your hands dextrously diminish slightly.\n");

	TP->set_skill_extra(SS_OPEN_LOCK, 
       (TP->query_skill_extra(SS_OPEN_LOCK) - 5));
	TP->heal_hp(dmg);

	if (TP->query_hp() <= 0)
		TP->do_die(E(TO));
		
	return 1;
}

int
add_floor()
{
	myfloor++;

	if (myfloor > 4)
		myfloor = 4;

	switch (myfloor)
	{
		case 2:
			ITEM(({"door", "cupboard", "doors"}), "@@cupboard_doors@@" + "\n");
			canpick2 = 1;
			canpick3 = 0;
			canpick4 = 0;
			break;
		case 3:
			remove_item("door");
			ITEM(({"door"}), "@@wooden_door@@" + "\n");
			canpick2 = 0;
			canpick3 = 1;
			canpick4 = 0;
			break;
		case 4:
			remove_item("door");
			ITEM(({"door", "panel", "steel panel"}), "@@steel_panel@@" + "\n");
			canpick2 = 0;
			canpick3 = 0;
			canpick4 = 1;
			break;
		default:
			break;
	}

	return myfloor;
}

int
subtract_floor()
{
	myfloor--;

	if (myfloor < 1)
		myfloor = 1;

	switch (myfloor)
	{
		case 1:
			remove_item("door");
			canpick2 = 0;
			canpick3 = 0;
			canpick4 = 0;
			break;
		case 2:
			remove_item("door");
			ITEM(({"door", "cupboard", "doors"}), "@@cupboard_doors@@" + "\n");
			canpick2 = 1;
			canpick3 = 0;
			canpick4 = 0;
			break;
		case 3:
			remove_item("door");
			ITEM(({"door"}), "@@wooden_door@@" + "\n");
			canpick2 = 0;
			canpick3 = 1;
			canpick4 = 0;
			break;
		default:
			break;
	}

	return myfloor;
}

int
view_opening()
{
	/* This function returns an equivalent of 'look' from whichever
	 * floor it is on most importantly without any supporting code
	 * from the target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	if (myfloor == 1)
	{
		write(TRUSQ_FLOOR1->long());
		target = find_object(TRUSQ_FLOOR1);
		inv = all_inventory(target);
		obs = FILTER_SHOWN(FILTER_DEAD(inv));
		ppl = FILTER_LIVE(inv);

		if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
		write(one_of_list(({"From within you can make out "}))
							+ desc + " on the floor.\n");

		if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
		write(one_of_list(({"Outside you see "}))
							+ desc + " in the kitchen.\n");
	 
		return 1;
	}

	if (myfloor == 2)
	{
		if (fopen2 == 1)
		{
			write("The cupboard doors are latched closed.  You cannot see "
			+ "out.\n");
			return 1;
		}

		write("You crack the cupboard doors open enough to peek out.\n");
		write(TRUSQ_FLOOR2->long());
		target = find_object(TRUSQ_FLOOR2);
		inv = all_inventory(target);
		obs = FILTER_SHOWN(FILTER_DEAD(inv));
		ppl = FILTER_LIVE(inv);

		if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
		write(one_of_list(({"From within you can make out "}))
							+ desc + " on the floor.\n");

		if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
		write(one_of_list(({"Outside you see "}))
							+ desc + " in the office.\n");
	 
		return 1;
	}

	if (myfloor == 3)
	{
		if (fopen3 == 1)
		{
			write("The small wooden door is locked and closed.  You cannot "
			+ "see out.\n");
			return 1;
		}
		
		write("You crack the small wooden door open enough to peek out.\n");
		write(TRUSQ_FLOOR3->long());
		target = find_object(TRUSQ_FLOOR3);
		inv = all_inventory(target);
		obs = FILTER_SHOWN(FILTER_DEAD(inv));
		ppl = FILTER_LIVE(inv);

		if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
		write(one_of_list(({"From within you can make out "}))
							+ desc + " on the floor.\n");

		if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
		write(one_of_list(({"Outside you see "}))
							+ desc + " in the bedroom.\n");
	 
		return 1;
	}

	if (myfloor == 4)
	{
		if (fopen4 == 1)
		{
			write("The steel panel is locked and closed.  You cannot see "
			+ "out.\n");
			return 1;
		}

		write("You slide the steel panel open enough to peek out.\n");
		write(TRUSQ_FLOOR4->long());
		target = find_object(TRUSQ_FLOOR4);
		inv = all_inventory(target);
		obs = FILTER_SHOWN(FILTER_DEAD(inv));
		ppl = FILTER_LIVE(inv);

		if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
		write(one_of_list(({"From within you can make out "}))
							+ desc + " on the floor.\n");

		if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
		write(one_of_list(({"Outside you see "}))
							+ desc + " in the suite.\n");
	 
		return 1;
	}

}

void 
init()
{
    ::init();
	ADD("exit_dumb", "out");
	ADD("exit_dumb", "exit");
	ADD("pull_rope", "pull");
	ADD("unlatch_cupboard", "unlatch");
	ADD("pop_door", "pop");
	ADD("pick_steel", "pick");
	ADD("disarm_trap", "disarm");
}

int
exit_dumb(string str)
{
	if (myfloor == 1)
	{
		write("You squeeze your way back out of the dumbwaiter.\n");
		TP->move_living("squeezes out of the dumbwaiter in the southwest "
		+ "corner", SHIP + "trusq_kitchen", 0, 0);
		return 1;
	}

	if (myfloor == 2)
	{
		if (fopen2 == 1)
		{
			write("The cupboard doors are latched shut.  You cannot get "
			+ "out.\n");
			return 1;
		}
		write("You push the cupboard doors open and squeeze your way back "
		+ "out of the dumbwaiter.\n");
		TP->move_living("squeezes out of the dumbwaiter",
			SHIP + "trusq_priv_office", 0, 0);
		return 1;
	}

	if (myfloor == 3)
	{
		if (fopen3 == 1)
		{
			write("The small wooden door is locked shut.  You cannot get "
			+ "out.\n");
			return 1;
		}
		write("You push the small woodrn door open and squeeze your way "
		+ "back out.\n");
		TP->move_living("squeezes out of the dumbwaiter",
			SHIP + "trusq_priv_guardroom", 0, 0);
		return 1;
	}

	if (myfloor == 4)
	{
		if (fopen4 == 1)
		{
			write("The steel panel is locked and shut.  You cannot get "
			+ "out.\n");
			return 1;
		}
		write("You slide the steel panel open and squeeze your way back "
		+ "out.\n");
		TP->move_living("squeezes out of the dumbwaiter",
			SHIP + "trusq_master", 0, 0);
		return 1;
	}

	write("Where the heck are you?!?  You better reorient and fast!\n");
	return 1;
}

int
pull_rope(string str)
{
	object *obs, *ppl;
	
	obs = all_inventory(TO);
	ppl = FILTER_LIVE(obs);

	NF("What?\n");
	if (!str)
		return 0;

	NF("Pull " + str + "?  Right here?  Are you mad?!?\n");
	if (!parse_command(str, ({}), "[the] [left] [right] 'rope'"))
		return 0;

	if (parse_command(str, ({}), "[the] [right] 'rope'"))
	{
		NF("The dumbwaiter has reached the bottom and can go no further.  "
		+ "Pulling the right rope has no effect.\n");
		if (myfloor == 1)
			return 0;
		
		write("You pull the right rope, and the dumbwaiter lowers to the "
		+ "next floor.\n");
		say(QCTNAME(TP) + " pulls the right rope and lowers the dumbwaiter to "
		+ "the next floor.\n");
		subtract_floor();
		if (myfloor == 1)
			tell_room(E(TP), "The dumbwaiter arrives at the bottom.\n");
		return 1;
	}

	if (parse_command(str, ({}), "[the] [left] 'rope'"))
	{
		NF("The dumbwaiter is too heavy!  Pulling the left rope has no "
		+ "effect.\n");
		if (sizeof(ppl) > 1)
			return 0;

		NF("The dumbwaiter has reached the top and can go no further.  "
		+ "Pulling the left rope has no effect.\n");
		if (myfloor == 4)
			return 0;
		
		write("You pull the left rope, and the dumbwaiter raises to the "
		+ "next floor.\n");
		say(QCTNAME(TP) + " pulls the left rope and hoists the dumbwaiter "
		+ "to the next floor.\n");
		add_floor();
		if (myfloor == 4)
			tell_room(E(TP), "The dumbwaiter arrives at the top.\n");
		return 1;
	}

	write("Which rope did you want to pull?  The left or right one?\n");
	return 1;
}
