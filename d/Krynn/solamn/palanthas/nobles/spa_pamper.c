/* 
 * Facials, manicures, pedicures, and styles hair.
 * Laethorian Spa and Body
 *
 * Pamperer gives facials.
 *
 * Mortis 01.2006
 *
 * Check out stand logic.
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

inherit NOBLE_ROOMBASE;

object pamperer;

string *stinkers = (({"wraith", "goblin", "hobgoblin", "minotaur", "orc",
	"uruk"}));

string
query_to_jail()
{
  return "east";
}

void
reset_palan_room()
{
	if (!pamperer)
	{
		pamperer = clone_object(NOBLE + "living/pamperer");
		pamperer->arm_me();
		pamperer->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("Pamper room of Laethorian Spa and Body");
    LONG("The pampering room of the Laethorian dayspa is bright and clean "
	+ "with tall, silver braziers burning in each of its four corners.  The "
	+ "place is completely done in polished, translucent white marble.  "
	+ "Along the north wall are pale leather chairs.  Beside each one is a "
	+ "counter containing jars, poultices, and towels.  Open doorways lead "
	+ "west and south to adjoining rooms, and a white sign hangs from the "
	+ "ceiling.\n");

	ITEM(({"spa", "dayspa"}), "The spa is quiet and clean.  Have a <look> "
	+ "around.\n");
	ITEM(({"brazier", "braziers", "silver brazier", "silver braziers", "fire",
		"fires"}), "Tall, silver braziers stand in the four corners of this "
	+ "foyer.  Small fires burn in each, their light reflecting off the "
	+ "polished marble of the ceiling and shedding even light across the "
	+ "floor and walls.\n");
	ITEM(({"corner", "corners"}), "Standing in each of the corners and "
	+ "providing light are tall, silver braziers.\n");
	ITEM(({"wall", "walls", "ceiling", "floor", "floors"}), "The floor, "
	+ "walls and ceiling are of translucent white marble polished to a "
	+ "gleaming shine.\n");
	ITEM(({"sign", "white sign"}), "Hung from the ceiling is a sign.  Upon "
	+ "it, written in the old style, are instructions in black lettering.\n");
	ITEM(({"chair", "chairs", "pale leather chair", "pale leather chairs",
		"pale chair", "pale chairs", "leather chair", "leather chairs"}),
	  "A row of pale, cream coloured leather chairs lines the north wall.  "
	+ "They are rather long with fold out legrests, headrests, and a lever "
	+ "on their side allowing them to recline.  Beside each is a counter "
	+ "containing jars, poultices, and a stack of small towels.  Have a seat "
	+ "in one if you're here for a facial.\n");
	ITEM(({"lever", "levers"}), "There is a brass handled lever on the side "
	+ "of each chair to activate the chair's reclining feature.\n");
	ITEM(({"counter", "counters", "jar", "jars", "poultice", "poultices",
		"towel", "towels", "stack"}), "Beside each pale leather chair along "
	+ "the north wall is a marble topped counter.  Rows of jars containing "
	+ "skin creams, poultices of green herbal essences, and stacks of small "
	+ "folded white towels are arranged neatly on each counter.\n");

    add_smell("vampire", "The air here is cool, clean, and flooded with "
	+ "scents subduing the scent of human blood.  The smell of herbs and "
	+ "stimulants is strong here.");
    add_smell("morgul", "The air here is cool, clean, and filled with the "
	+ "smells of stimulants and herbal blends.");
    
	add_smell("human", "The air here is cool and clean and filled with the "
	+ "smells of invigorating herbal blends.");
	add_smell("elf", "The air here is cool, clean, and fragrant with the "
	+ "smells of a blend of stimulating, fresh herbs.");
	add_smell("goblin", "The stink of mixed up herbs floods the cool air "
	+ "here.");
	add_smell("dwarf", "The air here is cool and clean.  From the east there "
	+ "is a very sterile odour of recent cleaning while here you pick up the "
	+ "strong smells of invigorating herbal blends.");
	add_smell("hobbit", "Strong herbal blends here make your head spin as "
	+ "you experience the cool, fragrant air.");
	add_smell("gnome", "The air here is cool and clean.  You detect "
	+ "quality, sterile cleaning fluids faintly to the east, but they are "
	+ "weak compared to the smell of blends of herb stimulants here.");
	add_smell("minotaur", "The cool air here is filled with an odd blend of "
	+ "herbs that make your nose twitch.");
	add_smell("halfhuman", "The air here is cool and clean and filled with the "
	+ "smells of invigorating herbal blends.");
	add_smell("halfelf", "The air here is cool and clean and filled with the "
	+ "smells of invigorating herbal blends.");
	add_smell("orc", "The scent of manflesh tainted with herbal blends is "
	+ "strong here.");
	add_smell("hobgoblin", "The air here is clean and cool.  The smells of "
	+ "stimulating herbal blends is strong here.");
	add_smell("kender", "Ahh!  The scents of exciting herbal blends waft "
	+ "around your nose pleasantly here.");
	add_smell("drow", "The air here is refreshingly cool and filled with the "
	+ "smells of stimulants and herbal blends.");
	add_smell("noldor", "The air here is cool, clean, and fragrant with the "
	+ "smells of a blend of stimulating, fresh herbs, quite unexpected from "
	+ "a human establishment.");

	EXIT(NOBLE + "spa", "east", 0, 0);
	EXIT(NOBLE + "spa_hair", "south", "@@place_closed", 0);
	EXIT(NOBLE + "spa_nails", "west", 0, 0);
	
	CMD("sign", "read", "@@read_sign");
	CMD("sign", "mread", "@@mread_sign");

	reset_palan_room();
}

int
place_closed()
{
	write("To be opened in the near future.\n");
	return 1;
}

void 
init()
{    
    ::init();
    ADD("action_sit", "sit");
	ADD("action_stand", "stand");
	ADD("pull_lever", "pull");
	ADD("push_lever", "push");
}

public int
read_sign()
{
	string signfile = NOBLE + "obj/spapamper.txt";

	if (TP->query_guild_name_occ() == "Morgul Mages")
		signfile = NOBLE + "obj/spapamper_morgul.txt";

	say(QCTNAME(TP) + " studies the white sign hanging from the ceiling.\n");
	write("The sign reads...\n");
	cat(signfile, 1, 50);

	return 1;
}

public int
mread_sign()
{
	string signfile = NOBLE + "obj/spapamper.txt";

	if (TP->query_guild_name_occ() == "Morgul Mages")
		signfile = NOBLE + "obj/spapamper_morgul.txt";

	say(QCTNAME(TP) + " studies the white sign hanging from the ceiling.\n");
	write("The sign reads...\n");
	TP->more(read_file(signfile, 1, 50000));


	return 1;
}

int
pull_lever(string str)
{
	if (!str)
	{
		TP->catch_msg("What would you like to pull?  A lever on the "
		+ "side of one of the pale leather chairs?\n");
		return 1;
	}

	if(parse_command(str, ({}),
	"[the] [a] 'lever' [along] [on] [by] [the] [left] [of] [the] [chair]"))
	{
		if (TP->query_prop(FSIT))
		{
			write("You pull on the lever again, but it is already up as far as "
			+ "it will go.  You are welcome to push the lever to sit back up.\n");
			return 1;
		}
		
		if (TP->query_prop(TSIT))
		{
			write("You pull on the lever along the left side of your pale "
			+ "leather chair.  The back reclines allowing your head to rest "
			+ "comfortably on the headrest, and the legrest swivels up to "
			+ "elevate your legs.  Ahhhhh!\n");
			say(QCTNAME(TP) + " pulls the lever along the side of " + HIS(TP)
			+ " pale leather chair.  The chair's back reclines, and its "
			+ "legrest swivels up to elevate " + HIS(TP) + " legs.\n"
			+ C(HE(TP)) + " goes ahhhhh.\n");
			TP->remove_prop(TSIT);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			TP->add_prop(FSIT, 1);
			TP->add_prop(LIVE_S_EXTRA_SHORT, " is reclining in a pale "
			+ "leather chair");
			return 1;
		}
		write("The lever only works if you're sitting in one of the pale "
		+ "leather chairs.\n");
		return 1;
	}
	write("Pull your what?!?  Right here?  In front of everyone???  No, "
	+ "you reconsider and decide against it.\n");
	return 1;
}

int
push_lever(string str)
{
	if (!str)
	{
		TP->catch_msg("What would you like to push?  A lever on the "
		+ "side of one of the pale leather chairs?\n");
		return 1;
	}

	if(parse_command(str, ({}),
	"[the] [a] 'lever' [along] [on] [by] [the] [left] [of] [the] [chair]"))
	{
		if (TP->query_prop(TSIT))
		{
			write("You push the lever, but it is already down as far as "
			+ "it will go.  You are welcome to pull the lever if you would "
			+ "like to recline, however.\n");
			return 1;
		}
		
		if (TP->query_prop(FSIT))
		{
			write("You push the lever along the left side of your pale "
			+ "leather chair.  The back sits back up straight, and the "
			+ "legrest swivels down returning the chair to its normal "
			+ "configuration.\n");
			say(QCTNAME(TP) + " pushes the lever along the side of " + HIS(TP)
			+ " pale leather chair.  The chair's back sits back up straight, "
			+ "and its legrest swivels down returning the chair to its "
			+ "normal configuration.\n");
			TP->remove_prop(FSIT);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			TP->add_prop(TSIT, 1);
			TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting in a pale "
			+ "leather chair.");
			return 1;
		}
		write("The lever only works if you're sitting in one of the pale "
		+ "leather chairs.\n");
		return 1;
	}
	write("Push your what?!?  Right here?  In front of everyone???  No, "
	+ "you reconsider and decide against it.\n");
	return 1;
}

int 
action_sit(string str)
{
	if(TP->query_prop(TSIT))
	{
		write("You are already sitting in one of the pale leather chairs.  "
		+ "How do you propose to sit in two places at once?\n");
		return 1;
	}

	if (TP->query_prop(FSIT))
	{
		write("Not only are you already sitting in one of the pale leather "
		+ "chairs, but you are also comfortably reclined.  How many more "
		+ "chairs do you need at once?!?\n");
		return 1;
	}
 
	if (!str)
	{
		TP->catch_msg("Where would you like to sit?  In one of the pale "
		+ "leather chairs along the north wall?\n");
		return 1;
	}
           
	if(parse_command(str, ({}),
	"[in] [on] [the] [a] 'chair' [along] [at] [by] [the] [a] [north] [wall]"))
	{
		TP->catch_msg("You sit down in one of the pale leather chairs along "
		+ "the north wall.  They're quite comfortable, and the lever on its "
		+ "left side is easily within reach.\n");
		say(QCTNAME(TP) + " sits down in one of the pale leather chairs "
		+"along the north wall.\n");
		TP->add_prop(TSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting in a pale leather "
		+ "chair");
		return 1;
	}

	else
	{
		TP->catch_msg("Where would you like to sit?  In one of the pale "
		+ "leather chairs along the north wall?\n");
		return 1;
	}
	return 1;
}

int 
action_stand(string str)
{
	int i, j, k;
	string strace = QRACE(TP);

	if(str == "up" || !str)
	{
		if (TP->query_prop(BSIT))
		{
			TP->remove_prop(BSIT);
			TP->catch_msg("You wipe your face mostly clean with a small, white "
			+ "towel from the stack on the counter to your right.\n");
			say(QCTNAME(TP) + " wipes " + HIS(TP) + " face mostly clean with a "
			+ "small, white towel from the stack on the counter to " + HIS(TP)
			+ " right.\n");
		}

		if(TP->query_prop(TSIT))
		{
			TP->catch_msg("You stand up from your pale leather chair.\n");
			say(QCTNAME(TP) + " stands up from " + HIS(TP) + " pale leather "
			+ "chair.\n");
			TP->remove_prop(TSIT);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			
			for(i=0,j=sizeof(stinkers);i<j;i++)
			{
				k = member_array(strace, stinkers);
				if (k == -1)
				{
					write("A white-coated attendant arrives from the east.\n"
					+ "The white-coated attendant smiles at you as he dusts "
					+ "off your pale leather chair.\nThe white-coated "
					+ "attendant leaves east.\n");
					say("A white-coated attendant arrives from the east.\n"
					+ "The white-coated attendant smiles at " + QCTNAME(TP)
					+ " as he dusts off " + HIS(TP) + " pale leather chair.\n"
					+ "The white-coated attendant leaves east.\n");
					return 1; /* Not in stinkers list. */
				}
			}

			write("A white face-masked attendant in a white coat arrives "
			+ "from the east.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes your pale leather "
			+ "chair with a wet, cleaning towel.\nThe face-masked white-"
			+ "coated attendant leaves stumbling east.\n");
			say("A white face-masked attendant in a white coat arrives "
			+ "from the east.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes " + QCTNAME(TP) + "'s "
			+ "pale leather chair with a wet, cleaning towel.\nThe face-"
			+ "masked white-coated attendant leaves stumbling east.\n");
			return 1;
		}

		if (TP->query_prop(FSIT))
		{
			TP->catch_msg("You push the lever on the left of your pale leather "
			+ "to sit back up before standing to leave.\n");
			say(QCTNAME(TP) + " pushes the lever on the left of " + HIS(TP)
			+ " pale leather chair before " + HE(TP) + " stands to leave.\n");
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			TP->remove_prop(FSIT);
			
			for(i=0,j=sizeof(stinkers);i<j;i++)
			{
				k = member_array(strace, stinkers);
				if (k == -1)
				{
					write("A white-coated attendant arrives from the east.\n"
					+ "The white-coated attendant smiles at you as he dusts "
					+ "off your pale leather chair.\nThe white-coated "
					+ "attendant leaves east.\n");
					say("A white-coated attendant arrives from the east.\n"
					+ "The white-coated attendant smiles at " + QCTNAME(TP)
					+ " as he dusts off " + HIS(TP) + " pale leather chair.\n"
					+ "The white-coated attendant leaves east.\n");
					return 1; /* Not in stinkers list. */
				}
			}

			write("A white face-masked attendant in a white coat arrives "
			+ "from the east.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes your pale leather "
			+ "chair with a wet, cleaning towel.\nThe face-masked white-"
			+ "coated attendant leaves stumbling east.\n");
			say("A white face-masked attendant in a white coat arrives "
			+ "from the east.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes " + QCTNAME(TP) + "'s "
			+ "pale leather chair with a wet, cleaning towel.\nThe face-"
			+ "masked white-coated attendant leaves stumbling east.\n");
			return 1;
		}
		TP->catch_msg("You would need to sit first.\n");
		return 1;

		if (TP->query_prop(BSIT))
		{
			TP->catch_msg("You push the lever on the left of your pale leather "
			+ "to sit back up before standing to leave.\n");
			say(QCTNAME(TP) + " pushes the lever on the left of " + HIS(TP)
			+ " pale leather chair before " + HE(TP) + " stands to leave.\n");
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			TP->remove_prop(BSIT);
			
			for(i=0,j=sizeof(stinkers);i<j;i++)
			{
				k = member_array(strace, stinkers);
				if (k == -1)
				{
					write("A white-coated attendant arrives from the east.\n"
					+ "The white-coated attendant smiles at you as he dusts "
					+ "off your pale leather chair.\nThe white-coated "
					+ "attendant leaves east.\n");
					say("A white-coated attendant arrives from the east.\n"
					+ "The white-coated attendant smiles at " + QCTNAME(TP)
					+ " as he dusts off " + HIS(TP) + " pale leather chair.\n"
					+ "The white-coated attendant leaves east.\n");
					return 1; /* Not in stinkers list. */
				}
			}

			write("A white face-masked attendant in a white coat arrives "
			+ "from the east.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes your pale leather "
			+ "chair with a wet, cleaning towel.\nThe face-masked white-"
			+ "coated attendant leaves stumbling east.\n");
			say("A white face-masked attendant in a white coat arrives "
			+ "from the east.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes " + QCTNAME(TP) + "'s "
			+ "pale leather chair with a wet, cleaning towel.\nThe face-"
			+ "masked white-coated attendant leaves stumbling east.\n");
			return 1;
		}
		TP->catch_msg("You would need to sit first.\n");
		return 1;
	}
	TP->catch_msg("Stand?  Stand up?\n");
	return 1;
}

void leave_inv(object ob, object to)
{
	::leave_inv(ob, to);   

	int i, j, k;
	string strace = QRACE(TP);
        
	if(!objectp(to) || !objectp(ob))
		return;

	if (TP->query_prop(BSIT))
	{
		TP->remove_prop(BSIT);
		TP->catch_msg("You wipe your face mostly clean with a small, white "
		+ "towel from the stack on the counter to your right.\n");
		say(QCTNAME(TP) + " wipes " + HIS(TP) + " face mostly clean with a "
		+ "small, white towel from the stack on the counter to " + HIS(TP)
		+ " right.\n");
	}
                
	if(TP->query_prop(TSIT))
	{
		TP->catch_msg("You stand up from your pale leather chair before "
		+ "leaving.\n");
		say(QCTNAME(TP) + " stands up from " + HIS(TP) + " pale leather "
		+ "chair before " + HE(TP) + " leaves.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		TP->remove_prop(TSIT);

		for(i=0,j=sizeof(stinkers);i<j;i++)
		{
			k = member_array(strace, stinkers);
			if (k == -1)
			{
				write("A white-coated attendant arrives from the east.\n"
				+ "The white-coated attendant smiles at you as he dusts "
				+ "off your pale leather chair.\nThe white-coated "
				+ "attendant leaves east.\n");
				say("A white-coated attendant arrives from the east.\n"
				+ "The white-coated attendant smiles at " + QCTNAME(TP)
				+ " as he dusts off " + HIS(TP) + " pale leather chair.\n"
				+ "The white-coated attendant leaves east.\n");
				return; /* Not in stinkers list. */
			}
		}
		write("A white face-masked attendant in a white coat arrives "
		+ "from the east.\nThe face-masked white-coated attendant makes "
		+ "strained gagging noises as he sterilizes your pale leather "
		+ "chair with a wet, cleaning towel.\nThe face-masked white-"
		+ "coated attendant leaves stumbling east.\n");
		say("A white face-masked attendant in a white coat arrives "
		+ "from the east.\nThe face-masked white-coated attendant makes "
		+ "strained gagging noises as he sterilizes " + QCTNAME(TP) + "'s "
		+ "pale leather chair with a wet, cleaning towel.\nThe face-"
		+ "masked white-coated attendant leaves stumbling east.\n");
		return;
	}

	if (TP->query_prop(FSIT))
	{
		TP->catch_msg("You push the lever on the left of your pale leather "
		+ "to sit back up before standing to leave.\n");
		say(QCTNAME(TP) + " pushes the lever on the left of " + HIS(TP)
		+ " pale leather chair before " + HE(TP) + " stands to leave.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		TP->remove_prop(FSIT);

		for(i=0,j=sizeof(stinkers);i<j;i++)
		{
			k = member_array(strace, stinkers);
			if (k == -1)
			{
				write("A white-coated attendant arrives from the east.\n"
				+ "The white-coated attendant smiles at you as he dusts "
				+ "off your pale leather chair.\nThe white-coated "
				+ "attendant leaves east.\n");
				say("A white-coated attendant arrives from the east.\n"
				+ "The white-coated attendant smiles at " + QCTNAME(TP)
				+ " as he dusts off " + HIS(TP) + " pale leather chair.\n"
				+ "The white-coated attendant leaves east.\n");
				return; /* Not in stinkers list. */
			}
		}

		write("A white face-masked attendant in a white coat arrives "
		+ "from the east.\nThe face-masked white-coated attendant makes "
		+ "strained gagging noises as he sterilizes your pale leather "
		+ "chair with a wet, cleaning towel.\nThe face-masked white-"
		+ "coated attendant leaves stumbling east.\n");
		say("A white face-masked attendant in a white coat arrives "
		+ "from the east.\nThe face-masked white-coated attendant makes "
		+ "strained gagging noises as he sterilizes " + QCTNAME(TP) + "'s "
		+ "pale leather chair with a wet, cleaning towel.\nThe face-"
		+ "masked white-coated attendant leaves stumbling east.\n");
		return;
	}
}
