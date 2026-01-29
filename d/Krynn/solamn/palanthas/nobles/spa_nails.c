/* 
 * Manicurist gives manicures and pedicures.
 *
 * Mortis 01.2006
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <money.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

inherit NOBLE_ROOMBASE;

#define NAIL_MASTER				(NOBLE + "spa_nails")
#define NAILSTYLE_SUBLOC		"nails"
#define NAILSTYLE_SHADOW		(NOBLE + "nails/nails_shadow")
#define NAILSTYLE_CMDSOUL		(NOBLE + "nails/nails_cmdsoul")

mapping nail_desc_values_nice = (["length":({"chewed-down", "long",
	"moderate", "modest", "nubby", "short", "trimmed", "very-short",
	"very-long"}),
	"style":({"brittle", "curled", "curling", "curved", "curving",
	"enameled", "filed", "glossy", "manicured", "metallic", "natural",
	"painted", "pointed", "shaded", "sharpened", "sparkling", "straight",
	"thick", "two-toned"}),
	"colour":({"black", "onyx", "shadowy", "white", "ivory", "natural",
	"copper", "gold", "silver", "red", "pink", "ruby", "orange",
	"yellow", "yellowed", "green", "emerald", "jade", "blue", "night",
	"opal", "indigo", "violet", "purple"}),
	"nail":({"nails"})]);

mapping nail_desc_values_harsh = (["length":({"chewed-down", "long",
	"moderate", "modest", "nubby", "short", "trimmed", "very-short",
	"very-long"}),
	"style":({"brittle", "broken", "cracked", "curled", "curling", "curved",
	"curving", "enameled", "filed", "glossy", "hooked", "jagged",
	"metallic", "painted", "pointed", "rotting", "serrated", "shaded",
	"sharpened", "sparkling", "splintered", "straight", "thick", "torn",
	"two-toned"}),
	"colour":({"black", "onyx", "shadowy", "white", "ivory", "natural",
	"copper", "gold", "silver", "red", "pink", "ruby", "orange", "yellow",
	"yellowed", "green", "emerald", "jade", "blue", "night", "opal",
	"indigo", "violet", "purple", "bone"}),
	"nail":({"nails", "nail-claws", "claws"})]);

mapping nail_desc_values_undead = (["length":({"chewed-down", "long",
	"moderate", "modest", "nubby", "short", "trimmed", "very-short",
	"very-long"}),
	"style":({"bloody", "brittle", "broken", "cracked", "curled", "curling", 
	"curved", "curving", "enameled", "filed", "glass", "glossy", "hooked", 
	"icy", "manicured", "metallic", "natural", "painted", "pointed", 
	"recurving", "rotting","serrated", "sharpened", "shaded", "sparkling", 
	"straight", "thick", "thin", "two-toned"}),
	"colour":({"black", "onyx", "shadowy", "white", "ivory", "natural",
	"copper", "gold", "silver", "red", "pink", "ruby", "orange", "yellow",
	"yellowed", "green", "emerald", "jade", "blue", "night", "opal",
	"indigo", "violet", "purple", "bone", "glass"}),
	"nail":({"nails", "nail-claws", "claws", "talons"})]);


object manicurist;

string *nail_desc = ({"length", "style", "colour", "nail"});
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
	if (!manicurist)
	{
		manicurist = clone_object(NOBLE + "living/manicurist");
		manicurist->arm_me();
		manicurist->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("Manicure room of Laethorian Spa and Body");
    LONG("The manicuring room of the Laethorian dayspa is bright and clean "
	+ "with tall, silver braziers burning in each of its four corners.  The "
	+ "place is completely done in polished, translucent white marble.  "
	+ "Along the west wall are pale leather chairs.  Beside each one is a "
	+ "counter containing manicuring utensils, towels, and a stool.  An open "
	+ "doorway leads east to the pampering room, and a white sign hangs from "
	+ "the ceiling.\n");

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
	  "A row of pale, cream coloured leather chairs lines the west wall.  "
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

	EXIT(NOBLE + "spa_pamper", "east", 0, 0);
	
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
	ADA("order");
	ADD("remove_nails", "undo");
}

int
remove_nails(string str)
{
	NF("Undo what?\n");
	if (!str)
		return 0;

	if (str == "nails")
	{
		object shadow = TP->query_subloc_obj(NAILSTYLE_SUBLOC);

		shadow->destruct_nail_shadow();
		TP->remove_autoshadow(NAILSTYLE_SHADOW);
		TP->remove_subloc(NAILSTYLE_SUBLOC);
		if (TP->query_wiz_level())
		{
			TP->catch_msg("You will have to remove the autoshadow "
			+ "and cmdsoul yourself if they are present.\n"); 
		}
		TP->catch_msg("Tildee dips your fingers in a Qui'ren solvent "
		+ "bowl and removes your manicure.\n");
		say(QCTNAME(TP) + " dips " + HIS(TP) + " fingers in a bowl of "
		+ "a clear liquid and has " + HIS(TP) + " manicure removed.\n");
		return 1;
    }
}

mapping compute_all_necessary_nail_data(string *argdata, string pers)
{
	int typ1, i, j, k;
	mapping order;
	order = (["length":"","style":"","colour":"","nail":""]);

	if (pers == "undead")
	{
		for(i=0,j=sizeof(nail_desc);i<j;i++)
		{
			k = member_array(argdata[i],nail_desc_values_undead[nail_desc[i]]);
			if (k == -1)
				{
				manicurist->command("say I'm sorry, but " + argdata[i]
				+ " is not an available " + nail_desc[i] + " choice for you.");
				return (["nail":""]); /*invalid nail*/
				}
			order[nail_desc[i]] = nail_desc_values_undead[nail_desc[i]][k];
		}
		return order;
	}

	if (pers == "harsh")
	{
		for(i=0,j=sizeof(nail_desc);i<j;i++)
		{
			k = member_array(argdata[i],nail_desc_values_harsh[nail_desc[i]]);
			if (k == -1)
				{
				manicurist->command("say I'm sorry, but " + argdata[i]
				+ " is not an available " + nail_desc[i] + " choice for you.");
				return (["nail":""]); /*invalid nail*/
				}
			order[nail_desc[i]] = nail_desc_values_harsh[nail_desc[i]][k];
		}
		return order;
	}

	if (pers == "nice")
	{
		for(i=0,j=sizeof(nail_desc);i<j;i++)
		{
			k = member_array(argdata[i],nail_desc_values_nice[nail_desc[i]]);
			if (k == -1)
				{
				manicurist->command("say I'm sorry, but " + argdata[i]
				+ " is not an available " + nail_desc[i] + " choice for you.");
				return (["nail":""]); /*invalid nail*/
				}
			order[nail_desc[i]] = nail_desc_values_nice[nail_desc[i]][k];
		}
		return order;
	}

	return order;
}

string
perstype(object pers)
{
	string persrace = QRACE(pers);

	if (pers->query_guild_name_occ() == "Vampires of Emerald" || pers->query_guild_name_occ() == "Morgul Mages")
	{
		return "undead";
	}

	if (parse_command(persrace, ({}), "'orc' / 'uruk' / 'goblin' / 'hobgoblin'"))
	{
		return "harsh";
	}

	return "nice";
}

int
order(string str)
{
	string *argdata, persontype;
	mapping my_order;

/*    if (alrm == 1)
	{
		manicurist->command("say I am already with a customer.  If you "
		+ "could wait a minute, I will be right with you.");
		return 1;
	}*/
	if (!manicurist)
	{
		NF("The manicurist is not here to serve you.\n");
		return 0;
	}

    NF(C(query_verb()) + " what?\n");
    if (!str)
      return 0;

    /* syntax is: 'order <length> <style> <colour> <nail>' */
	argdata = explode(str," ");
    NF(C(query_verb()) + " <length> <style> <colour> <nail>.\n");
    if(sizeof(argdata) != 4)
	{ return 0; }

	persontype = perstype(TP);

	my_order = compute_all_necessary_nail_data(argdata, persontype);

    if (my_order["nail"] != "")
	{
		set_alarm(0.0, 0.0, "finished_nails",
		TP, my_order["length"],	my_order["style"], my_order["colour"],
		my_order["nail"]);
		write("You request your nails be done.\n");
		say(QCTNAME(TP) + " requests " + HIS(TP) + " nails be done.\n");

      return 1;
	}
    NF("You failed to have your nails done.\n");
    return 0;
}

void
finished_nails(object for_who, string len, string sty, string col, string nai)
{
    string gren = NAILSTYLE_SHADOW + ":" + len + "," + sty + "," + col + "," + nai;

	if (!MONEY_ADD(for_who, -864))
	{
		manicurist->command("say I'm sorry, but you're a little short on "
		+ "cash.");
		return;
	}

	manicurist->command("introduce myself");
	object shadow = for_who->query_subloc_obj(NAILSTYLE_SUBLOC);

	if (shadow)
	{
		for_who->catch_msg("Tildee redoes your nails.\n");
		say("Tildee redoes " + QCTNAME(for_who) + "'s nails.\n");
	}

    if (!shadow)
    {
		shadow = clone_object(NAILSTYLE_SHADOW);
		if (!shadow->shadow_me(for_who))
		{
			shadow->destruct_nail_shadow();
			manicurist->command("say Gosh, what happened?  I couldn't do your "
			+ "nails.");
			return;
		}
		for_who->catch_msg("Tildee does your nails.\n");
		say("Tildee does " + QCTNAME(for_who) + "'s nails.\n");
		for_who->add_autoshadow(gren);
		for_who->add_subloc(NAILSTYLE_SUBLOC, shadow);
	}

	shadow->set_nailstyle(len, sty, col, nai);
	shadow->set_length(len);
	shadow->set_style(sty);
	shadow->set_nails_colour(col);
	shadow->set_nail(nai);
	shadow->add_nail_commands();
	for_who->remove_autoshadow(NAILSTYLE_SHADOW);
	for_who->add_autoshadow(gren);

    for_who->catch_msg("You pay six gold coins.\n");
    say(QCTNAME(for_who) + " pays six gold coins to have " + HIS(for_who)
	+ " nails done.\n");

    if (for_who->query_wiz_level()) { 
        for_who->catch_msg("Since you are a wizard, you will have to do " +
          "the following if you want to keep your nail shadow " +
          "and have nail emote commands.\n" + 
          "First: Call @" + for_who->query_real_name() + " add_autoshadow " + 
          gren + "\nSecond: Call @" + for_who->query_real_name() + " add_cmdsoul " +
          NOBLE + "nails/nails_cmdsoul" + "\n"); 
     }

	for_who->catch_msg("\nType `help nail' for nail emote details.\n");
}

public int
read_sign()
{
	string manirace = QRACE(TP);

	say(QCTNAME(TP) + " studies the white sign hanging from the ceiling.\n");
	if (TP->query_guild_name_occ() == "Vampires of Emerald" || TP->query_guild_name_occ() == "Morgul Mages")
	{
		write("The letters on the sign morph before your eyes to read...\n");
		cat(NOBLE + "obj/spa_manicure_undead.txt", 1, 50);
		return 1;
	}

	if (parse_command(manirace, ({}), "'goblin' / 'hobgoblin' / 'orc' / 'uruk'"))
	{
		write("The letters on the sign morph before your eyes to read...\n");
		cat(NOBLE + "obj/spa_manicure_harsh.txt", 1, 50);
		return 1;
	}

	write("The letters on the sign morph before your eyes to read...\n");
	cat(NOBLE + "obj/spa_manicure_nice.txt", 1, 50);
	return 1;
}

public int
mread_sign()
{
	string file_nice = NOBLE + "obj/spa_manicure_nice.txt";
	string file_harsh = NOBLE + "obj/spa_manicure_harsh.txt";
	string file_undead = NOBLE + "obj/spa_manicure_undead.txt";
	string manirace = QRACE(TP);

	say(QCTNAME(TP) + " studies the white sign hanging from the ceiling.\n");
	if (TP->query_guild_name_occ() == "Vampires of Emerald" || TP->query_guild_name_occ() == "Morgul Mages")
	{
		write("The sign reads...\n");
		TP->more(read_file(file_undead, 1, 50000));
		return 1;
	}

	if (parse_command(manirace, ({}), "'goblin' / 'hobgoblin' / 'orc' / 'uruk'"))
	{
		write("The sign reads...\n");
		TP->more(read_file(file_harsh, 1, 50000));
		return 1;
	}

	write("The sign reads...\n");
	TP->more(read_file(file_nice, 1, 50000));
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
			+ HE(TP) + " goes ahhhhh.\n");
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
			+ "leather chair");
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
