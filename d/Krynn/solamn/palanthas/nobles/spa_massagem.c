/* 
 * Massages by women.  Different for men/women.
 * Laethorian Spa and Body
 *
 * Mortis 02.2006
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <cmdparse.h>

#define TABLED				"_i_am_laying_on_massage_table"

inherit NOBLE_ROOMBASE;

int ontable = 0; // Only one person on the table at a time.
string *stinkers = (({"wraith", "goblin", "hobgoblin", "minotaur", "orc",
	"uruk"}));
object masseus;

// Prototypes
void off_table();

string
query_to_jail()
{
	return "south";
}

void
reset_palan_room()
{
	if (!masseus)
	{
		off_table();

		masseus = clone_object(NOBLE + "living/masseus");
		masseus->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("Men's massage chamber of a dayspa");
    LONG("The massage chamber of the Laethorian dayspa is clean and softly "
	+ "lit with tall, silver braziers burning low in each of its four "
	+ "corners.  The room is completely done in polished, translucent white "
	+ "marble.  In the center of the room is a white leather cushioned "
	+ "massage table.  Beside it on the north wall is a counter containing "
	+ "jars of exotic oils and a stack of towels while a row of leather "
	+ "chairs line the west wall.  An arched doorway leads south to the "
	+ "massage foyer, and a marble sign hangs on the east wall.\n");

	ITEM(({"spa", "dayspa"}), "The spa is quiet and clean.  Have a <look> "
	+ "around.\n");
	ITEM(({"parlour", "chamber"}), "The chamber is quiet and clean.  Your "
	+ "footsteps  echo softly here.  Have a <look> around.\n");
	ITEM(({"brazier", "braziers", "silver brazier", "silver braziers", "fire",
		"fires"}), "Tall, silver braziers stand in the four corners of this "
	+ "foyer.  Low fires burn in each, their glowing light reflecting off the "
	+ "polished marble of the ceiling and shedding soft light across the "
	+ "floor and walls.\n");
	ITEM(({"corner", "corners"}), "Standing in each of the corners and "
	+ "providing light are tall, silver braziers.\n");
	ITEM(({"wall", "walls", "ceiling", "floor", "floors"}), "The floor, "
	+ "walls and ceiling are of translucent white marble polished to a "
	+ "gleaming shine.\n");
	ITEM(({"sign", "marble sign"}), "Hung on the east wall is a marble sign.  "
	+ "Upon it, written in the old style, are instructions in black lettering "
	+ ".\n");
	ITEM(({"chair", "chairs", "pale leather chair", "pale leather chairs",
		"pale chair", "pale chairs", "leather chair", "leather chairs"}),
	  "A row of pale, cream coloured leather chairs lines the west wall.  "
	+ "They are rather long with fold out legrests, headrests, and a lever "
	+ "on their side allowing them to recline..\n");
	ITEM(({"lever", "levers"}), "There is a brass handled lever on the side "
	+ "of each chair to activate the chair's reclining feature.\n");
	ITEM(({"massage table", "table"}), "A tall table covered in white "
	+ "leather cushions with separate sections for the head, body, and legs "
	+ "sits in the center of the room.  It is custom designed to support the "
	+ "proper posture of a patron laying face down upon it in great comfort.  "
	+ "Beside it against the north wall is a counter topped with jars of oils "
	+ "and a stack of white towels.  You may <lay> down upon it if you're "
	+ "here for a massage.\n");
	ITEM(({"counter", "counters", "jar", "jars", "oil", "oils",
		"towel", "towels", "stack"}), "Beside the massage table against "
	+ "the north wall is a marble topped counter.  Rows of jars containing "
	+ "skin creams, jars of exotic massage oils, and stacks of small "
	+ "folded white towels are arranged neatly upon it.  You may take one of "
	+ "the towels with <unfold towel> if you want to get a massage.  Beside "
	+ "the counter is a white hamper.\n");
	ITEM(({"white hamper", "hamper"}), "A white painted metal hamper sits "
	+ "beside the counter against the north wall.  It contains used towels "
	+ "that people have returned.\n");

    add_smell("vampire", "The air here is cool, clean, and flooded with "
	+ "smells subduing the scent of human blood.  The smell of fragrant oils "
	+ "fills the air.");
    add_smell("morgul", "The air here is cool and clean.  The smell of "
	+ "fragrant oils fills the air.");
    
	add_smell("human", "The air here is cool and clean.  The smell of "
	+ "fragrant oils fills the air.");
	add_smell("elf", "The air here is cool and clean.  The smell of "
	+ "fragrant and exotic oils fills the air.");
	add_smell("goblin", "The air here is cool and clean.  The smell of "
	+ "fragrant oils fills the air and is not particularly appetizing "
	+ "despite your mouth watering.");
	add_smell("dwarf", "The air here is cool and clean.  The smell of "
	+ "fragrant oils fills the air.");
	add_smell("hobbit", "The air here is cool and clean.  The smell of "
	+ "fragrant oils fills the air.  How pleasant.");
	add_smell("gnome", "The air here is cool and clean.  The smell of "
	+ "exotic, fragrant oils commonly used by humans in massaging fills the "
	+ "air.");
	add_smell("minotaur", "Soapy, fragrant oils and odours designed to mask "
	+ "the scent of humans flood the cool, clean air here.");
	add_smell("halfhuman", "The air here is cool and clean.  The smell of "
	+ "fragrant oils fills the air.");
	add_smell("halfelf", "The air here is cool and clean.  The smell of "
	+ "fragrant oils fills the air.");
	add_smell("orc", "The scent of manflesh tainted with flowery oils, "
	+ "floods your nostrils here.");
	add_smell("hobgoblin", "The air here is cool and clean.  The smell of "
	+ "fragrant oils fills the air.");
	add_smell("kender", "Hmm!  The scents of fragrant oils waft in "
	+ "pleasantly about the air here.  These humans must really know how "
	+ "to enjoy themselves.");
	add_smell("drow", "The air here is cool and clean.  The smell of "
	+ "bizarrely fragrant oils fills the air.");
	add_smell("noldor", "The air here is cool and clean.  The smell of "
	+ "fragrant and exotic oils fills the air.");

	EXIT(NOBLE + "spa_massage", "south", "@@towel_thief", 0);
	
	CMD("sign", "read", "@@read_sign");
	CMD("sign", "mread", "@@mread_sign");

	reset_palan_room();
}

void 
init()
{    
    ::init();
    ADD("action_sit", "sit");
	ADD("action_stand", "stand");
	ADD("pull_lever", "pull");
	ADD("push_lever", "push");
	ADA("lay");
	ADA("unfold");
}

public int
read_sign()
{
	say(QCTNAME(TP) + " studies the marble sign hanging on the east wall.\n");
	write("The sign reads...\n");
	cat(NOBLE + "obj/spamassagem.txt", 1, 50);

	return 1;
}

public int
mread_sign()
{
	string file = NOBLE + "obj/spamassagem.txt";

	say(QCTNAME(TP) + " studies the marble sign hanging on the east wall.\n");
	write("The sign reads...\n");
	TP->more(read_file(file, 1, 50000));


	return 1;
}

void
off_table()
{
	ontable = 0;
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
	if (TP->query_prop(TABLED))
	{
		write("You are already laying down on the massage table.  How do you "
		+ "expect to sit in a chair at the same time?\n");
		return 1;
	}

	if (TP->query_prop(TSIT))
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
		+ "leather chairs along the west wall?\n");
		return 1;
	}
           
	if(parse_command(str, ({}),
	"[in] [on] [the] [a] 'chair' [along] [at] [by] [the] [a] [west] [wall]"))
	{
		TP->catch_msg("You sit down in one of the pale leather chairs along "
		+ "the west wall.  They're quite comfortable, and the lever on its "
		+ "left side is easily within reach.\n");
		say(QCTNAME(TP) + " sits down in one of the pale leather chairs "
		+"along the west wall.\n");
		TP->add_prop(TSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting in a pale leather "
		+ "chair");
		return 1;
	}

	else
	{
		TP->catch_msg("Where would you like to sit?  In one of the pale "
		+ "leather chairs along the west wall?\n");
		return 1;
	}
	return 1;
}

int
lay(string str)
{
	string armname;
	object *armours;

	if (TP->query_prop(TABLED))
	{
		write("You are already laying face down on the massage table.  How "
		+ "did you think you were going to lay down again?  With magic?\n");
		return 1;
	}

	if (TP->query_prop(TSIT))
	{
		write("You are already sitting in one of the pale leather chairs.  "
		+ "How do you propose to lay and sit in two places at once?\n");
		return 1;
	}

	if (TP->query_prop(FSIT))
	{
		write("Not only are you already sitting in one of the pale leather "
		+ "chairs, but you are also comfortably reclined.  How many more "
		+ "things to lay on do you need at once?!?\n");
		return 1;
	}

	NF("Lay down on what?  The massage table?\n");
	if (!str)
		return 0;
	
	if (!parse_command(str, ({}), "[face] [down] [on] [the] [massage] 'table'"))
		return 0;

	NF("There is already someone laying on the table.  You'll have to wait "
	+ "your turn.\n");
	if (ontable == 1)
		return 0;

	NF("You need to be wearing only a towel from the counter before you can "
	+ "get a massage.\n");
	
	armours = TP->query_armour(-1);

	if (sizeof(armours) != 1)
		return 0;

	armname = armours[0]->query_name();

	if (armname == "towel")
	{
		write("You lay face down on the massage table in your short white "
		+ "towel.  Its white leather cushions are warm and support perfect "
		+ "posture in your body comfortably.\nAhhhhh.\n");
		say(QCTNAME(TP) + " lays face down on the massage table in " + HIS(TP)
		+ " short white towel.\n" + HE(TP) + " sighs comfortably.\n");
		TP->add_prop(TABLED, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT, " is laying down on the massage "
		+ "table");
		ontable = 1;
		return 1;
	}
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

		if (TP->query_prop(TABLED))
		{
			TP->catch_msg("You hop up from the comfortable massage table.\n");
			say(QCTNAME(TP) + " hops up from the comfortable massage "
			+ "table.\n");
			TP->remove_prop(TABLED);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			ontable = 0;

			for(i=0,j=sizeof(stinkers);i<j;i++)
			{
				k = member_array(strace, stinkers);
				if (k == -1)
				{
					write("A white-coated attendant arrives from the south.\n"
					+ "The white-coated attendant smiles at you as he dusts "
					+ "off the massage table.\nThe white-coated "
					+ "attendant leaves south.\n");
					say("A white-coated attendant arrives from the south.\n"
					+ "The white-coated attendant smiles at " + QCTNAME(TP)
					+ " as he dusts off the massage table.\n"
					+ "The white-coated attendant leaves south.\n");
					return 1; /* Not in stinkers list. */
				}
			}

			write("A white face-masked attendant in a white coat arrives "
			+ "from the south.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes the massage table "
			+ "with a wet, cleaning towel.\nThe face-masked white-"
			+ "coated attendant leaves stumbling south.\n");
			say("A white face-masked attendant in a white coat arrives "
			+ "from the south.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes the massage table "
			+ "with a wet, cleaning towel.\nThe face-masked white-coated "
			+ "attendant leaves stumbling south.\n");
			return 1;
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
					write("A white-coated attendant arrives from the south.\n"
					+ "The white-coated attendant smiles at you as he dusts "
					+ "off your pale leather chair.\nThe white-coated "
					+ "attendant leaves south.\n");
					say("A white-coated attendant arrives from the south.\n"
					+ "The white-coated attendant smiles at " + QCTNAME(TP)
					+ " as he dusts off " + HIS(TP) + " pale leather chair.\n"
					+ "The white-coated attendant leaves south.\n");
					return 1; /* Not in stinkers list. */
				}
			}

			write("A white face-masked attendant in a white coat arrives "
			+ "from the south.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes your pale leather "
			+ "chair with a wet, cleaning towel.\nThe face-masked white-"
			+ "coated attendant leaves stumbling south.\n");
			say("A white face-masked attendant in a white coat arrives "
			+ "from the south.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes " + QCTNAME(TP) + "'s "
			+ "pale leather chair with a wet, cleaning towel.\nThe face-"
			+ "masked white-coated attendant leaves stumbling south.\n");
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
					write("A white-coated attendant arrives from the south.\n"
					+ "The white-coated attendant smiles at you as he dusts "
					+ "off your pale leather chair.\nThe white-coated "
					+ "attendant leaves south.\n");
					say("A white-coated attendant arrives from the south.\n"
					+ "The white-coated attendant smiles at " + QCTNAME(TP)
					+ " as he dusts off " + HIS(TP) + " pale leather chair.\n"
					+ "The white-coated attendant leaves south.\n");
					return 1; /* Not in stinkers list. */
				}
			}

			write("A white face-masked attendant in a white coat arrives "
			+ "from the south.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes your pale leather "
			+ "chair with a wet, cleaning towel.\nThe face-masked white-"
			+ "coated attendant leaves stumbling south.\n");
			say("A white face-masked attendant in a white coat arrives "
			+ "from the south.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes " + QCTNAME(TP) + "'s "
			+ "pale leather chair with a wet, cleaning towel.\nThe face-"
			+ "masked white-coated attendant leaves stumbling south.\n");
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
					write("A white-coated attendant arrives from the south.\n"
					+ "The white-coated attendant smiles at you as he dusts "
					+ "off your pale leather chair.\nThe white-coated "
					+ "attendant leaves south.\n");
					say("A white-coated attendant arrives from the south.\n"
					+ "The white-coated attendant smiles at " + QCTNAME(TP)
					+ " as he dusts off " + HIS(TP) + " pale leather chair.\n"
					+ "The white-coated attendant leaves south.\n");
					return 1; /* Not in stinkers list. */
				}
			}

			write("A white face-masked attendant in a white coat arrives "
			+ "from the south.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes your pale leather "
			+ "chair with a wet, cleaning towel.\nThe face-masked white-"
			+ "coated attendant leaves stumbling south.\n");
			say("A white face-masked attendant in a white coat arrives "
			+ "from the south.\nThe face-masked white-coated attendant makes "
			+ "strained gagging noises as he sterilizes " + QCTNAME(TP) + "'s "
			+ "pale leather chair with a wet, cleaning towel.\nThe face-"
			+ "masked white-coated attendant leaves stumbling south.\n");
			return 1;
		}
		TP->catch_msg("You would need to sit first.\n");
		return 1;
	}
	TP->catch_msg("Stand?  Stand up?\n");
	return 1;
}

int
unfold(string str)
{
	object tow, *towels;

    setuid();
    seteuid(getuid());
    
	NF("Unfold what?  A towel from the counter?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[a] 'towel' [from] [the] [counter]"))
		return 0;

	towels = FIND_STR_IN_OBJECT("_laethorian_massage_towel", TP);

	NF("You already have a towel.  What are you trying to do?  Stockpile "
	+ "them?\n");
	if (sizeof(towels) != 0)
		return 0;

	write("You pick up towel from the counter against the north wall and "
	+ "unfold it.  It is ready to wear now.\n");
	say(QCTNAME(TP) + " picks up a towel from the counter against the north "
	+ "wall and unfolds it.\n");
	
	tow = clone_object(NOBLE + "arms/massage_towel");
	tow->move(TP);

	return 1;
}

int
towel_thief()
{
	object *towels = FIND_STR_IN_OBJECT("_laethorian_massage_towel", TP);

	if (sizeof(towels) != 0)
	{
		if (masseus)
		{
			masseus->command("say Please return your massage towel "
			+ "before leaving, " + QNAME(TP) + ".\n");
			return 1;
		}
		write("An attendant asks you to please return your massage towel "
		+ "before leaving.\n");
		say("An attendant asks " + QTNAME(TP) + " to return " + HIS(TP)
		+ " towel before leaving.\n");
		return 1;
	}
	return 0;
}

void leave_inv(object ob, object to)
{
	::leave_inv(ob, to);   

	int i, j, k;
	string strace = QRACE(TP);
        
	if(!objectp(to) || !objectp(ob))
		return;

	if (TP->query_prop(TABLED))
	{
		TP->remove_prop(TABLED);
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		TP->catch_msg("You hop up from the massage table before leaving.\n");
		say(QCTNAME(TP) + " hops up from the massage table before leaving.\n");

		for(i=0,j=sizeof(stinkers);i<j;i++)
		{
			k = member_array(strace, stinkers);
			if (k == -1)
			{
				write("A white-coated attendant arrives from the south.\n"
				+ "The white-coated attendant smiles at you as he dusts "
				+ "off the massage table.\nThe white-coated "
				+ "attendant leaves south.\n");
				say("A white-coated attendant arrives from the south.\n"
				+ "The white-coated attendant smiles at " + QCTNAME(TP)
				+ " as he dusts off the massage table.\n"
				+ "The white-coated attendant leaves south.\n");
				return; /* Not in stinkers list. */
			}
		}
		write("A white face-masked attendant in a white coat arrives "
		+ "from the south.\nThe face-masked white-coated attendant makes "
		+ "strained gagging noises as he sterilizes the massage table "
		+ "with a wet, cleaning towel.\nThe face-masked white-"
		+ "coated attendant leaves stumbling south.\n");
		say("A white face-masked attendant in a white coat arrives "
		+ "from the south.\nThe face-masked white-coated attendant makes "
		+ "strained gagging noises as he sterilizes the massage table "
		+ "with a wet, cleaning towel.\nThe face-masked white-coated "
		+ "attendant leaves stumbling south.\n");
	return;
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
				write("A white-coated attendant arrives from the south.\n"
				+ "The white-coated attendant smiles at you as he dusts "
				+ "off your pale leather chair.\nThe white-coated "
				+ "attendant leaves south.\n");
				say("A white-coated attendant arrives from the south.\n"
				+ "The white-coated attendant smiles at " + QCTNAME(TP)
				+ " as he dusts off " + HIS(TP) + " pale leather chair.\n"
				+ "The white-coated attendant leaves south.\n");
				return; /* Not in stinkers list. */
			}
		}
		write("A white face-masked attendant in a white coat arrives "
		+ "from the south.\nThe face-masked white-coated attendant makes "
		+ "strained gagging noises as he sterilizes your pale leather "
		+ "chair with a wet, cleaning towel.\nThe face-masked white-"
		+ "coated attendant leaves stumbling south.\n");
		say("A white face-masked attendant in a white coat arrives "
		+ "from the south.\nThe face-masked white-coated attendant makes "
		+ "strained gagging noises as he sterilizes " + QCTNAME(TP) + "'s "
		+ "pale leather chair with a wet, cleaning towel.\nThe face-"
		+ "masked white-coated attendant leaves stumbling south.\n");
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
				write("A white-coated attendant arrives from the south.\n"
				+ "The white-coated attendant smiles at you as he dusts "
				+ "off your pale leather chair.\nThe white-coated "
				+ "attendant leaves south.\n");
				say("A white-coated attendant arrives from the south.\n"
				+ "The white-coated attendant smiles at " + QCTNAME(TP)
				+ " as he dusts off " + HIS(TP) + " pale leather chair.\n"
				+ "The white-coated attendant leaves south.\n");
				return; /* Not in stinkers list. */
			}
		}

		write("A white face-masked attendant in a white coat arrives "
		+ "from the south.\nThe face-masked white-coated attendant makes "
		+ "strained gagging noises as he sterilizes your pale leather "
		+ "chair with a wet, cleaning towel.\nThe face-masked white-"
		+ "coated attendant leaves stumbling south.\n");
		say("A white face-masked attendant in a white coat arrives "
		+ "from the south.\nThe face-masked white-coated attendant makes "
		+ "strained gagging noises as he sterilizes " + QCTNAME(TP) + "'s "
		+ "pale leather chair with a wet, cleaning towel.\nThe face-"
		+ "masked white-coated attendant leaves stumbling south.\n");
		return;
	}
}
