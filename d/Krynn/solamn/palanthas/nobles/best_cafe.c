/* 
 * The Mer-Cantile cafe in the east of 
 * the Court d'Plaisiri in the Nobles quarter.
 *
 * Mortis 12.2005
 *
 * Add chess board here.  Perhaps full size, battle chess in park.
 *
 * Gave room a disposal bin and peace ward by request of players to have
 * a room in which to negotiate with other guilds. Mortis 9.2014
 *
 * 
 * 2018-12-01 - Cotillion
 * - /cmd/std/command_driver -> /lib/commands
 * - Fixed runtime when someone sitting linkdied
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

inherit "/lib/commands";
inherit NOBLE_ROOMBASE;
inherit "/lib/trade";

#define VIEWWEST			(NOBLE + "nplaza")
#define CAFE				(NOBLE + "best_cafe")
#define NUM	sizeof(MONEY_TYPES)
#define WSIT				"_i_am_a_sitting_wizard"
#define LAPSIT				"_i_am_sitting_in_a_lap"
#define HAVELAP				"_i_have_a_lap_sitter"

int move_item(mixed arg); 
int test;

object bcbarista, chess, dbin;

string
query_to_jail()
{
  return "west";
}


void
reset_palan_room()
{
	if (!bcbarista)
	{
		bcbarista = clone_object(NOBLE + "living/bcbarista");
		bcbarista->move(TO);
	}

	if (!dbin)
	{
		dbin = clone_object(OBJ + "disposal_bin");
		dbin->move(TO);
	}

	if (!chess)
	{
		chess = clone_object(OBJ + "chess");
		chess->move(TO);
	}
}

void
create_palan_room()
{
    config_default_trade();
    
    SHORT("Mer-Cantile cafe");
    LONG("Inside, this cafe is cozy and wide running north to south with "
	+ "windows looking west upon the court.  Small tables and chairs fill "
	+ "the cafe with a few by the counter and windows.  There is a counter "
	+ "along the east wall behind which is hung a blackboard sign, and a "
	+ "black-enameled wooden condiment station by the window.  The air is "
	+ "rich with the smells of coffee.\nA Peace Ward glows above the "
	+ "blackboard.\n");

	ITEM(({"peaceward", "ward", "peace ward"}), "A High Sorcery rune has "
	+ "been inscribed in silver above the blackboard sign. It glows with a "
	+ "soft, reassuring light. It is a Peace Ward preventing fighting in "
	+ "this cafe so that negotiations and other disputes may be resolved "
	+ "here safely.\n");
	ITEM(({"plaza", "court"}), "The court is busy at all hours providing "
	+ "pleasurable services in the nobles quarter.  You can view it from "
	+ "the windows west.\n");
	ITEM(({"sign", "blackboard", "blackboard sign"}), "A wide, blackboard "
	+ "sign extends behind the counter.  Coloured chalk has been used to "
	+ "list available blends and pastries as well as decoratively trim it.  "
	+ "You may read it.\n");
	ITEM(({"counter", "case"}), "A tall counter stretches north and south "
	+ "along the east wall.  Behind it, the barista serves customers.  The "
	+ "front of the counter is a glass case displaying a variety of "
	+ "pastries you may peruse.  Several brewing apparati line the brewing "
	+ "counter behind this one against the east wall.\n");
	ITEM(({"apparati", "apparatus"}), "A row of shiny, polished steel tubes "
	+ "full of brewing coffee and tea line the brewing counter behind the "
	+ "front counter.\n");
	ITEM(({"pastry", "pastries"}), "Try perusing them.\n");
	ITEM(({"stool", "stools", "chairs", "chair", "tables", "table",
		"furniture"}), "Simple but sturdy wooden furniture in a curved, "
	+ "modern style.  You notice a silver table by the window.\n");
	ITEM(({"window", "windows"}), "Wide windows run the length of the "
	+ "cafe affording a good view of the Court d'Plaisir outside.  You "
	+ "may <view court> to have a look.\n");
	ITEM(({"station", "condiment station", "black-enameled station",
		   "wooden station", "black-enameled wooden condiment station"}),
	  "An elegant, round, black-enameled, wooden station stands by the "
	+ "window filled with free condiments for your beverage.  There is "
	+ "whipped cream, cream, sugar, honey, and cinnamon!  You may "
	+ "<add (condiment) to (drink)> here.\n");
	ITEM(({"whipped cream", "cream", "sugar", "honey", "cinnamon",
		   "condiment", "condiments"}), "Fresh cream and whipped cream, "
	+ "granulated white sugar, warm thick honey, and fine powdered "
	+ "cinnamon are all available at the black-enameled condiment "
	+ "station by the window.\n");
	ITEM("silver table", "There is a simple, round table of lustrous "
	+ "silver by the window.  Around it are several plush leather seats.\n");
	ITEM(({"seat", "seats", "plush seat", "plush leather seat",
		"plush leather seats", "leather seat", "leather seats"}), "There "
	+ "are several plush leather seats arrayed around the silver table "
	+ "by the window.  Their soft, pale brown leather looks especially "
	+ "comfortable, and their cushions are deep and pillowy.\n");

	add_prop(ROOM_M_NO_ATTACK, "The cafe is protected by a peace ward. Your "
	+ "spirit is rebuffed.\n");

	add_smell("vampire", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and fragrant teas fill your senses along with hints of cinnamon, "
	+ "cream, chocolate, vanilla, and all kinds of floral and herbal "
	+ "flavours underlying it all.  Through it all you barely make out "
	+ "the scent of young blood here.");
	add_smell("morgul", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and fragrant teas fill your senses.  Hints of cinnamon, cream, "
	+ "chocolate, vanilla, and all kinds of floral and herbal flavours "
	+ "underlie it all accompanied by the buttery richness of a variety of "
	+ "pastries and cookies in the glass display counter.  Nothing "
	+ "hobbit-based unfortunately.");
	add_smell("human", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and fragrant teas fill your senses.  Hints of cinnamon, cream, "
	+ "chocolate, vanilla, and all kinds of floral and herbal flavours "
	+ "underlie it all accompanied by the buttery richness of all sorts of "
	+ "pastries and cookies in the glass display counter.");
	add_smell("elf", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and mouth-wateringly fragrant herbal and green teas fill your senses.  "
	+ "Hints of cinnamon, cream, chocolate, delicious vanilla, and all kinds "
	+ "of stimulating floral and herbal flavours underlie it all accompanied "
	+ "by the buttery richness of all sorts of pastries and cookies in the "
	+ "glass display counter, but through it all, the fragrance of those "
	+ "teas stays attractively strong.");
	add_smell("goblin", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and fragrant teas fill your senses though only the really dark ones "
	+ "seem like they aren't poisoned.  Hints of cinnamon, cream, "
	+ "chocolate, vanilla, and all kinds of floral and herbal flavours "
	+ "underlie it all accompanied by the buttery richness of all sorts of "
	+ "pastries and cookies in the glass display counter.");
	add_smell("dwarf", "The aromas of fresh coffee, enticingly rich espresso "
	+ "drinks, and fragrant teas fill your senses.  Hints of cinnamon, "
	+ "cream, chocolate, vanilla, and all kinds of floral and herbal "
	+ "flavours underlie it all accompanied by the buttery richness of all "
	+ "sorts of pastries and cookies in the glass display counter.  Some "
	+ "of the darker drinks and coffees stood out in particular though.");
	add_smell("hobbit", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and fragrant teas fill your senses.  Hints of cinnamon, cream, "
	+ "chocolate, vanilla, and especially caramel, toffeenut, peppermint "
	+ "and pumpkin, plus all kinds of floral and herbal flavours "
	+ "underlie it all accompanied by the buttery richness of all sorts of "
	+ "exciting, tempting pastries and cookies in the glass display "
	+ "counter.");
	add_smell("gnome", "The aromas of fresh coffee, enticingly rich espresso "
	+ "drinks, and fragrant teas fill your senses.  Hints of cinnamon, "
	+ "cream, chocolate, vanilla, and all kinds of floral and herbal "
	+ "flavours underlie it all accompanied by the buttery richness of all "
	+ "sorts of pastries and cookies in the glass display counter.  Those "
	+ "espresso based drinks stood out in particular though.");
	add_smell("minotaur", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and fragrant teas fill your massive nostrils though only the really "
	+ "dark ones seem like they aren't poisoned.  Hints of cinnamon, cream, "
	+ "chocolate, vanilla, and all kinds of floral and herbal flavours "
	+ "underlie it all accompanied by the buttery richness of all sorts of "
	+ "pastries and cookies in the glass display counter.");
	add_smell("halfhuman", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and fragrant teas fill your senses.  Hints of cinnamon, cream, "
	+ "chocolate, vanilla, and all kinds of floral and herbal flavours "
	+ "underlie it all accompanied by the buttery richness of all sorts of "
	+ "pastries and cookies in the glass display counter.");
	add_smell("halfelf", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and especially the fragrant teas fill your senses.  Hints of cinnamon, "
	+ "cream, chocolate, vanilla, and all kinds of floral and herbal flavours "
	+ "underlie it all accompanied by the buttery richness of all sorts of "
	+ "pastries and cookies in the glass display counter.");
	add_smell("orc", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and fragrant teas fill your nostrils though only the really dark ones "
	+ "seem like they aren't poisoned.  Hints of cinnamon, cream, "
	+ "chocolate, vanilla, and all kinds of floral and herbal flavours "
	+ "underlie it all accompanied by the buttery richness of all sorts of "
	+ "pastries and cookies in the glass display counter.");
	add_smell("hobgoblin", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and fragrant teas fill your nostrils though only the really dark ones "
	+ "seem like they aren't poisoned.  Hints of cinnamon, cream, "
	+ "chocolate, vanilla, and all kinds of floral and herbal flavours "
	+ "underlie it all accompanied by the buttery richness of all sorts of "
	+ "pastries and cookies in the glass display counter.");
	add_smell("kender", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and fragrant teas fill your senses.  Hints of cinnamon, cream, "
	+ "chocolate, vanilla, and especially caramel, toffeenut, peppermint "
	+ "and pumpkin, plus all kinds of floral and herbal flavours "
	+ "underlie it all accompanied by the buttery richness of all sorts of "
	+ "exciting, tempting pastries and cookies in the glass display "
	+ "counter.");
	add_smell("drow", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and mouth-wateringly fragrant herbal and green teas fill your senses.  "
	+ "Hints of cinnamon, cream, chocolate, delicious vanilla, and all kinds "
	+ "of stimulating floral and herbal flavours underlie it all accompanied "
	+ "by the buttery richness of all sorts of pastries and cookies in the "
	+ "glass display counter, but through it all, the fragrance of those "
	+ "teas stays attractively strong.");
	add_smell("noldor", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and mouth-wateringly fragrant herbal and green teas fill your senses.  "
	+ "Hints of cinnamon, cream, chocolate, delicious vanilla, and all kinds "
	+ "of stimulating floral and herbal flavours underlie it all accompanied "
	+ "by the buttery richness of all sorts of pastries and cookies in the "
	+ "glass display counter, but through it all, the fragrance of those "
	+ "teas stays attractively strong.");
	add_smell("presence", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and fragrant teas have little effect on you in this state.");
	add_smell("unknown", "The aromas of fresh coffee, rich espresso drinks, "
	+ "and fragrant teas fill your senses.  Hints of cinnamon, cream, "
	+ "chocolate, vanilla, and all kinds of floral and herbal flavours "
	+ "underlie it all accompanied by the buttery richness of all sorts of "
	+ "pastries and cookies in the glass display counter.  By the way, what "
	+ "the heck race are you?!?  Why not mail Krynn for fun?");

	EXIT(NOBLE + "nplaza", "west", 0, 0);
	
	CMD(({"display", "case", "pastry", "pastries"}),({"peruse"}),
		  "@@peruse_case");
	CMD(({"plaza", "the plaza", "court", "the court"}), "view",
		  "@@view_plaza");
	CMD(({"sign", "blackboard", "blackboard sign"}), "read", "@@read_sign");
	CMD(({"sign", "blackboard", "blackboard sign"}), "mread", "@@mread_sign");

	reset_palan_room();
}

peruse_case() 
{
	write("You carefully peruse the glass case of pastries beneath the "
	+ "counter.  Anyone who loves sugary treats will be in heaven here.  "
	+ "There are muffins, scones, cookies, muffins, rolls, croissants, and "
	+ "biscotti all delectably decorated and laid out on frilly napkins.\n");
	say(QCTNAME(TP) + " carefully peruses the glass case of pastries beneath "
	+ "the counter.\n");
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
	write("Through the wide windows along the west wall, you can make out "
	+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the court you see " + desc + ".\n");

	say(QCTNAME(TP) + " gazes out the windows along the west wall.\n");
 
	return 1;
}

public int
read_sign()
{
    setuid();
    seteuid(getuid());
    
	say(QCTNAME(TP) + " studies the blackboard sign behind the counter.\n");
	write("The sign reads...\n");
	cat(NOBLE + "obj/bestcoffees.txt", 1, 50);

	return 1;
}

public int
mread_sign()
{
    setuid();
    seteuid(getuid());
    
	string file = NOBLE + "obj/bestcoffees.txt";

	say(QCTNAME(TP) + " studies the blackboard sign behind the counter.\n");
	write("The sign reads...\n");
	TP->more(read_file(file, 1, 50000));


	return 1;
}

void 
init()
{    
    ::init();
//	ADA("check");
    ADD("action_sit", "sit");
	ADD("action_stand", "stand");
    ADD("order", "buy");
	ADD("add_condiment", "add");
}

int 
action_sit(string str)
{
	object tp1 = TP;

	if(TP->query_prop(TSIT))
	{
		write("But you are already sitting by a table! How do you "
		+ "expect to sit in two places at once?\n");
		return 1;
	}
           
	if(TP->query_prop(FSIT))
	{
		write("But you are already sitting by the window! How do you "
		+ "expect to sit in two places at once?\n");
		return 1;
	}
           
	if(TP->query_prop(BSIT))
	{
		write("But you are already sitting by the counter! How do you "
		+ "expect to sit in two places at once?\n");
		return 1;
	}

	if(TP->query_prop(LAPSIT))
	{
		write("But you are already sitting in someone's lap! How do you "
		+ "expect to sit in two places at once?\n");
		return 1;
	}

	if (TP->query_prop(WSIT))
	{
		write("You are an honoured guest, but the ability to sit in two "
		+ "places at once is beyond even your power.\n");
		return 1;
	}

	if (!str)
	{
		TP->catch_msg("Where would you like to sit?  By the window, the "
		+ "counter, or around a table?\n");
		if (TP->query_wiz_level())
		{
			TP->catch_msg("As an illustrious visitor, you may sit at the "
			+ "silver table.\n");
		}
		return 1;
	}
           
	if(parse_command(str, ({}),
	"[around] [at] [in] [by] [the] [a] 'table' / 'chair' [around] [at] [in] [by] [the] [a] [table]"))
	{
		TP->catch_msg("You sit down in one of the comfortable chairs "
		+"near a table.\n");
		say(QCTNAME(TP) + " sits down in one of the comfortable looking "
		+"chairs near a table.\n");
		TP->add_prop(TSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting near a table");
		return 1;
	}
        
	if(str == "around window" | str == "around the window" | str == "by window" | str == "by the window" | str == "window" | str == "chair around window" | str == "in chair around window" | str == "in a chair around the window" | str == "chair by window" | str == "in chair by window" | str == "in a chair by the window") 
	{
		TP->catch_msg("You sit down in one of the comfortable chairs "
		+ "near the window.\n");
		say(QCTNAME(TP) + " sits down in one of the comfortable looking "
		+ "chairs near the window.\n");
		TP->add_prop(FSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting near the window");
		return 1;
	}
	
	if(parse_command(str, ({}),
	"[around] [at] [on] [by] [the] [a] 'stool' / 'counter' [around] [at] [by] [the] [a] [counter]"))
	{
		TP->catch_msg("You sit down on one of the stools at the counter.\n");
		say(QCTNAME(TP) + " sits down on a stool at the counter.\n");
		TP->add_prop(BSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting at the counter");
		return 1;
	}

	if (parse_command(str, ({}),
	"[around] [at] [in] [on] [by] [the] [a] 'seat' / 'silver' [around] [at] [by] [the] [a] [silver] [table]"))
	{
		if (TP->query_wiz_level())
		{
			TP->catch_msg("You relax into one of the plush leather seats "
			+ "at the silver table by the window, sinking slowly into its "
			+ "comfortable cushion.\n");
			say(QCTNAME(TP) + " relaxes into one of the plush leather "
			+ "seats at the silver table by the window, sinking slowly "
			+ "into its comfortable cushion.\n");
			TP->add_prop(WSIT, 1);
			TP->add_prop(LIVE_S_EXTRA_SHORT, " is relaxing in a plush "
			+ "leather seat at the silver table by the window");
			return 1;
		}
		TP->catch_msg("No, no, no.  The seats at the silver table by the "
		+ "window are reserved for very important visitors.\n");
		return 1;
	}

	object *inv, *ppl, target, lapobj;

	target = find_object(CAFE);
	inv = all_inventory(target);
	ppl = FILTER_LIVE(inv);
	string lapstr = "";
	string temp_lap;    // Person who has someone in their lap.
	string temp_sitter; // Person who is sitting in someone's lap.

	if(sscanf(str, "in lap of %s", lapstr) == 1)
	{
		lapobj = find_player(lapstr);
		temp_lap = TP->query_real_name();
		temp_sitter = lapobj->query_real_name();

		if (IN_ARRAY(lapobj, ppl))
		{
			if (lapobj->query_prop(TSIT))
			{
				tp1->catch_msg("You lower yourself onto " + QTNAME(lapobj)
				+ "'s lap and wiggle in comfortably.\n");
				lapobj->catch_msg(QCTNAME(TP) + " lowers " + HIMSELF(TP)
				+ " onto your lap and wiggles " + HIMSELF(TP) + " in "
				+ "comfortably.\n");
				say(QCTNAME(TP) + " lowers " + HIMSELF(TP) + " onto "
				+ QTNAME(lapobj) + "'s lap and wiggles " + HIMSELF(TP)
				+ " in comfortably.\n", (({lapobj, tp1})));
				TP->add_prop(LAPSIT, temp_sitter);
				TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting in "
				+ QTNAME(lapobj) + "'s lap");
				lapobj->remove_prop(LIVE_S_EXTRA_SHORT);
				lapobj->add_prop(HAVELAP, temp_lap);
				lapobj->add_prop(LIVE_S_EXTRA_SHORT, " is sitting near a "
				+ "table with " + QTNAME(TP) + " in " + HIS(TP) + " lap");
				return 1;
			}
			if (lapobj->query_prop(FSIT))
			{
				tp1->catch_msg("You lower yourself onto " + QTNAME(lapobj)
				+ "'s lap and wiggle in comfortably.\n");
				lapobj->catch_msg(QCTNAME(TP) + " lowers " + HIMSELF(TP)
				+ " onto your lap and wiggles " + HIMSELF(TP) + " in "
				+ "comfortably.\n");
				say(QCTNAME(TP) + " lowers " + HIMSELF(TP) + " onto "
				+ QTNAME(lapobj) + "'s lap and wiggles " + HIMSELF(TP)
				+ " in comfortably.\n", (({lapobj, tp1})));
				TP->add_prop(LAPSIT, temp_sitter);
				TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting in "
				+ QTNAME(lapobj) + "'s lap");
				lapobj->remove_prop(LIVE_S_EXTRA_SHORT);
				lapobj->add_prop(HAVELAP, temp_lap);
				lapobj->add_prop(LIVE_S_EXTRA_SHORT, " is sitting near the "
				+ "window with " + QTNAME(TP) + " in " + HIS(TP) + " lap");
				return 1;
			}
			if (lapobj->query_prop(BSIT))
			{
				tp1->catch_msg("You lower yourself onto " + QTNAME(lapobj)
				+ "'s lap and wiggle in comfortably.\n");
				lapobj->catch_msg(QCTNAME(TP) + " lowers " + HIMSELF(TP)
				+ " onto your lap and wiggles " + HIMSELF(TP) + " in "
				+ "comfortably.\n");
				say(QCTNAME(TP) + " lowers " + HIMSELF(TP) + " onto "
				+ QTNAME(lapobj) + "'s lap and wiggles " + HIMSELF(TP)
				+ " in comfortably.\n", (({lapobj, tp1})));
				TP->add_prop(LAPSIT, temp_sitter);
				TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting in "
				+ QTNAME(lapobj) + "'s lap");
				lapobj->remove_prop(LIVE_S_EXTRA_SHORT);
				lapobj->add_prop(HAVELAP, temp_lap);
				lapobj->add_prop(LIVE_S_EXTRA_SHORT, " is sitting at the "
				+ "counter with " + QTNAME(TP) + " in " + HIS(TP) + " lap");
				return 1;
			}
			if (lapobj->query_prop(WSIT))
			{
				tp1->catch_msg("You lower yourself onto " + QTNAME(lapobj)
				+ "'s lap and wiggle in comfortably.\n");
				lapobj->catch_msg(QTNAME(TP) + " lowers " + HIMSELF(TP)
				+ " onto your lap and wiggles " + HIMSELF(TP) + " in "
				+ "comfortably.\n");
				say(QCTNAME(TP) + " lowers " + HIMSELF(TP) + " onto "
				+ QTNAME(lapobj) + "'s lap and wiggles " + HIMSELF(TP)
				+ " in comfortably.\n", (({lapobj, tp1})));
				TP->add_prop(LAPSIT, temp_sitter);
				TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting in "
				+ QTNAME(lapobj) + "'s lap");
				lapobj->remove_prop(LIVE_S_EXTRA_SHORT);
				lapobj->add_prop(HAVELAP, temp_lap);
				lapobj->add_prop(LIVE_S_EXTRA_SHORT, " is relaxing in a plush "
				+ "leather seat at the silver table by the window with "
				+ QTNAME(TP) + " in " + HIS(TP) + " lap");
				return 1;
			}
			if (lapobj->query_prop(LAPSIT))
			{
				TP->catch_msg(QCTNAME(lapobj) + " is already sitting in someone's "
				+ "lap.  Sorry.\n");
				return 1;
			}
			if (lapobj->query_prop(HAVELAP))
			{
				TP->catch_msg(QCTNAME(lapobj) + " already has someone in "
				+ HIS(lapobj) + " lap.  Sadness.\n");
				return 1;
			}
			tp1->catch_msg(QCTNAME(lapobj) + " isn't sitting down.  Maybe you "
			+ "could ask " + HIM(lapobj) + " to sit down so you could enjoy "
			+ HIS(lapobj) + " lap.\n");
			lapobj->catch_msg(QCTNAME(TP) + " looks at your lap with an odd "
			+ "glint in " + HIS(TP) + " eye.\n");
			say(QCTNAME(TP) + " looks at " + QTNAME(lapobj) + "'s lap with an "
			+ "odd glint in " + HIS(TP) + " eye.\n", (({lapobj, tp1})));
			return 1;
		}
		TP->catch_msg(C(lapstr) + " who?  There's no " + C(lapstr)
		+ " here that wants you in their lap.\n");
		return 1;
	}

	else
	{
		TP->catch_msg("Where would you like to sit?  By the window, the counter, "
		+ "or around a table?  Or did you want to <sit in lap of someone>?\n");
		if (TP->query_wiz_level())
		{
			TP->catch_msg("As an illustrious visitor, you may sit at the "
			+ "silver table.\n");
		}
		return 1;
	}
        
	return 1;
}

int 
action_stand(string str)
{
	if(str == "up" || !str)
	{
		if (TP->query_prop(HAVELAP))
		{
			string who_sits = TP->query_prop(HAVELAP);
			object tp3 = TP;
			object lapsit = find_player(who_sits);

			tp3->catch_msg("You push " + QTNAME(lapsit) + " off your lap "
			+ "with a slap on the bottom as you stand up.\n");
			lapsit->catch_msg(QCTNAME(TP) + " pushes you off " + HIS(TP)
			+ " lap with a slap on your bottom as " + HE(TP) + " stands "
			+ "up.\n");
			say(QCTNAME(TP) + " pushes " + QTNAME(lapsit) + " off " + HIS(TP)
			+ " lap with a slap on " + HIS(lapsit) + " bottom as " + HE(TP)
			+ " stands up.\n", (({lapsit, tp3})));
			tp3->remove_prop(HAVELAP);
			tp3->remove_prop(LIVE_S_EXTRA_SHORT);
			lapsit->remove_prop(LAPSIT);
			lapsit->remove_prop(LIVE_S_EXTRA_SHORT);
			if (lapsit->query_prop(TSIT))
				lapsit->remove_prop(TSIT);
			if (lapsit->query_prop(FSIT))
				lapsit->remove_prop(FSIT);
			if (lapsit->query_prop(BSIT))
				lapsit->remove_prop(BSIT);
			if (lapsit->query_prop(WSIT))
				lapsit->remove_prop(WSIT);
			return 1;
		}
		if(TP->query_prop(TSIT))
		{
			TP->catch_msg("You stand up and leave the table.\n");
			say(QCTNAME(TP) + " stands up from the table.\n");
			TP->remove_prop(TSIT);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			return 1;
		}
                
		if(TP->query_prop(FSIT))
		{
			TP->catch_msg("You stand up and move away from the window.\n");
			say(QCTNAME(TP) + " stands up and moves away from the window.\n");
			TP->remove_prop(FSIT);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			return 1;
		}
                
		if(TP->query_prop(BSIT))
		{
			TP->catch_msg("You stand up from your stool at the counter.\n");
			say(QCTNAME(TP) + " stands up from a stool at the counter.\n");
			TP->remove_prop(BSIT);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			return 1;
		}

		if (TP->query_prop(WSIT))
		{
			TP->catch_msg("You rise from your plush leather seat at the "
			+ "silver table by the window.  The leather cushion slowly "
			+ "reassumes its original shape.\n");
			say(QCTNAME(TP) + " rises from " + HIS(TP) + " plush leather "
			+ "seat at the silver table by the window.  The leather cushion "
			+ "slowly reassumes its original shape.\n");
			TP->remove_prop(WSIT);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			return 1;
		}
		if (TP->query_prop(LAPSIT))
		{
			string whose_lap = TP->query_prop(LAPSIT);
			object tp2 = TP;
			object lappee = find_player(whose_lap);

			tp2->catch_msg("You hop up from your comfy spot on "
			+ QTNAME(lappee) + "'s lap with a knowing smile on your lips.\n");
			lappee->catch_msg(QCTNAME(TP) + " hops up from your lap with a "
			+ "knowing smile on " + HIS(TP) + " lips.\n");
			say(QCTNAME(TP) + " hops up from " + QTNAME(lappee) + "'s lap "
			+ "with a knowing smile on " + HIS(TP) + " lips.\n",
				(({lappee, tp2})));
			tp2->remove_prop(LAPSIT);
			tp2->remove_prop(LIVE_S_EXTRA_SHORT);
			lappee->remove_prop(HAVELAP);
			if (lappee->query_prop(TSIT))
				lappee->add_prop(LIVE_S_EXTRA_SHORT, " is sitting near a table");
			if (lappee->query_prop(FSIT))
				lappee->add_prop(LIVE_S_EXTRA_SHORT, " is sitting near the "
				+ "window");
			if (lappee->query_prop(BSIT))
				lappee->add_prop(LIVE_S_EXTRA_SHORT, " is sitting by the counter");
			if (lappee->query_prop(WSIT))
				lappee->add_prop(LIVE_S_EXTRA_SHORT, " is relaxing in a plush "
				+ "leather seat at the silver table by the window");
			return 1;
		}
	}
        
	else
	{
		TP->catch_msg("Stand?  Stand up?\n");
		return 1;
	}
	TP->catch_msg("You would need to sit first.\n");
	return 1;
}

void leave_inv(object ob, object to)
{
	::leave_inv(ob, to);    
        
	if(!objectp(to) || !objectp(ob))
		return;
                
	if (TP->query_prop(HAVELAP) && find_player(TP->query_prop(HAVELAP)))
	{
		string who_sits = TP->query_prop(HAVELAP);
		object tp3 = TP;
		object lapsit = find_player(who_sits);

		tp3->catch_msg("You push " + QTNAME(lapsit) + " off your lap "
		+ "with a slap on the bottom as you stand up and leave.\n");
		lapsit->catch_msg(QCTNAME(TP) + " pushes you off " + HIS(TP)
		+ " lap with a slap on your bottom as " + HE(TP) + " stands "
		+ "up and leaves.\n");
		say(QCTNAME(TP) + " pushes " + QTNAME(lapsit) + " off " + HIS(TP)
		+ " lap with a slap on " + HIS(lapsit) + " bottom as " + HE(TP)
		+ " stands up and leaves.\n", (({lapsit, tp3})));
		tp3->remove_prop(HAVELAP);
		tp3->remove_prop(LIVE_S_EXTRA_SHORT);
		lapsit->remove_prop(LAPSIT);
		lapsit->remove_prop(LIVE_S_EXTRA_SHORT);
		if (lapsit->query_prop(TSIT))
			lapsit->remove_prop(TSIT);
		if (lapsit->query_prop(FSIT))
			lapsit->remove_prop(FSIT);
		if (lapsit->query_prop(BSIT))
			lapsit->remove_prop(BSIT);
		if (lapsit->query_prop(WSIT))
			lapsit->remove_prop(WSIT);
	}

	if(TP->query_prop(TSIT))
	{
		TP->catch_msg("You stand up from the table before leaving.\n");
		say(QCTNAME(TP) + " stands up from the table as "+ HE(TP)
		+ " leaves.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		TP->remove_prop(TSIT);
	}
          
	if(TP->query_prop(FSIT))
	{
		TP->catch_msg("You stand up from your spot near the window before "
		+ "leaving.\n");
		say(QCTNAME(TP) + " stands up from " + HIS(TP) + " spot at the "
		+ "window as " + HE(TP) +" leaves.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);            
		TP->remove_prop(FSIT);
	}
        
	if(TP->query_prop(BSIT))
	{
		TP->catch_msg("You stand up from the counter before leaving.\n");        
		say(QCTNAME(TP) + " stands up from the counter as " + HE(TP)
		+ " leaves.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		TP->remove_prop(BSIT);
	}

	if (TP->query_prop(WSIT))
	{
		TP->catch_msg("You rise from your plush leather seat at the "
		+ "silver table by the window.  The leather cushion slowly "
		+ "reassumes its original shape.\n");
		say(QCTNAME(TP) + " rises from " + HIS(TP) + " plush leather "
		+ "seat at the silver table by the window.  The leather cushion "
		+ "slowly reassumes its original shape.\n");
		TP->remove_prop(WSIT);
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
	}

	if (TP->query_prop(LAPSIT))
	{
		string whose_lap = TP->query_prop(LAPSIT);
		object tp2 = TP;
		object lappee = find_player(whose_lap);

		tp2->catch_msg("You hop up from your comfy spot on "
		+ QTNAME(lappee) + " with a knowing smile on your lips as you "
		+ "leave.\n");
		lappee->catch_msg(QCTNAME(TP) + " hops up from your lap with a "
		+ "knowing smile on " + HIS(TP) + " lips as " + HE(TP) + " leaves.\n");
		say(QCTNAME(TP) + " hops up from " + QTNAME(lappee) + "'s lap "
		+ "with a knowing smile on " + HIS(TP) + " lips as " + HE(TP)
		+ " leaves.\n", (({lappee, tp2})));
		tp2->remove_prop(LAPSIT);
		tp2->remove_prop(LIVE_S_EXTRA_SHORT);
		lappee->remove_prop(HAVELAP);
		if (lappee->query_prop(TSIT))
			lappee->add_prop(LIVE_S_EXTRA_SHORT, " is sitting near a table");
		if (lappee->query_prop(FSIT))
			lappee->add_prop(LIVE_S_EXTRA_SHORT, " is sitting near the "
			+ "window");
		if (lappee->query_prop(BSIT))
			lappee->add_prop(LIVE_S_EXTRA_SHORT, " is sitting by the counter");
		if (lappee->query_prop(WSIT))
			lappee->add_prop(LIVE_S_EXTRA_SHORT, " is relaxing in a plush "
			+ "leather seat at the silver table by the window");
	}
}

/*int
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
		return 1;
	}
	write("That is not a valid material or article of clothing.  Use "
	+ "<check materials> for a list of materials and <check articles> "
	+ "for a list of clothing you can order (or <read sign> even).\n");

	return 1;
}*/

/*
 * Function name: order
 * Description:   The buyer orders a drink
 * Arguments:     str - name of drink and possibly description on
 * how to pay and get the change
 */

int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;
    
    NF("The barista is not here to fix your order.\n");
    if (!bcbarista || !P(bcbarista, TO))
      return 0;
    
    NF("Buy what?\n");
    if (!str)
      return 0;
    
    /* Has the player defined how payment will be done and what change
	 *to get back? */  
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
      {
	  /* Well, maybe player has defined how payment will be done atleast? */
	  str3 = "";
	  if (sscanf(str, "%s with %s", str1, str2) != 2)
	    {
		str2 = "";
		str1 = str;
	    }
      }
    
    if (sscanf(str1, "%d %s", num, str1) != 2)
      num = 1;

    if (num == 0)
      num = 1;

	if (parse_command(str1, ({}), "[apricot] [currant] 'scone' / 'scones' "))
	{
		name = "apricot_scone";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[black] [and] [white] 'cookie' / 'cookies' "))
	{
		name = "bwcookie";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[blueberry] 'muffin' / 'muffins' "))
	{
		name = "blueberry_muffin";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[butter] 'croissant' / 'croissants' [with] [apricot] [apricots]"))
	{
		name = "butter_croissant";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[caramel] [pecan] [sticky] 'roll' / 'rolls' "))
	{
		name = "caramel_roll";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[choc] [chocolate] [cream] [cheese] 'muffin' / 'muffins' "))
	{
		name = "choc_muffin";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[choc] [chocolate] [hazelnut] 'biscotti' / 'biscottis' "))
	{
		name = "choc_biscotti";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[cinnamon] [chip] 'scone' / 'scones' "))
	{
		name = "cinnamon_scone";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[cinnamon] 'roll' / 'rolls' "))
	{
		name = "cinnamon_roll";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[cranberry] [orange] 'muffin' / 'muffins' "))
	{
		name = "cranberry_muffin";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[crumb] 'cake' / 'cakes' "))
	{
		name = "crumb_cake";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[dark] [choc] [chocolate] [graham] 'cookie' / 'cookies' "))
	{
		name = "dark_cookie";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[oatmeal] [raisin] 'cookie' / 'cookies' "))
	{
		name = "oatmeal_cookie";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[rasp] [raspberry] [cream] [cheese] 'muffin' / 'muffins' "))
	{
		name = "raspberry_muffin";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[raspberry] 'scone' / 'scones' "))
	{
		name = "raspberry_scone";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[short] [bread] [shortbread] [chess] 'cookie' / 'cookies' "))
	{
		name = "shortbread_cookie";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[spice] [apple] 'torte' / 'tortes' "))
	{
		name = "spice_torte";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[vanilla] [almond] 'biscotti' / 'biscottis' "))
	{
		name = "vanilla_biscotti";
		price = num * 96;
	}

	else if (parse_command(str1, ({}), "[white] [choc] [chocolate] [macadamia] 'nut' / 'nuts' / 'cookie' / 'cookies' "))
	{
		name = "white_cookie";
		price = num * 96;
	}

	else
	{
		write("Smiling politely the barista says:  I don't understand what you "
		+ "want to buy.\n");
		return 1;
	}

	if (num > 10)
      {
	  NF("The staff is good but can only fix a maximum of 10 items at a "
	  + "time.\n");
	  return 0;
      }
    
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("The barista fixes your order.\n");
    
    return move_item(({name, num, TP}));
}

int
move_item(mixed arg)
{
    object drink, ob;
    string file, name;
    int i, num;
    
    name = arg[0];
    num = arg[1];
    ob = arg[2];
    
    for (i = 0; i < 10; i++)
      {
	  num--;
	  file = NOBLE + "obj/" + name;
	  drink = clone_object(file);
	  
	  if (!test && (drink->move(ob)))
	    {
		ob->catch_msg("You drop the " + drink->short() +
			      " on the floor.\n");
		say(QCTNAME(ob) + " drops a " + drink->short() + 
		    " on the floor.\n", ob);
		drink->move(TO);
	    } 
	  else if (!test) 
	    {
		if (num == 0)
		  {
		      if (arg[1] > 1)
			{
			    ob->catch_msg("You get some " + drink->plural_short() +
					  ".\n");
			    say(QCTNAME(ob) + " buys some " + drink->plural_short() +
				".\n", ob);
			}
		      else 
			{
			    ob->catch_msg("You get " + drink->short() + ".\n");
			    say(QCTNAME(ob) + " buys " + drink->short() + ".\n", ob);
			}
		  }
	    }
	  else 
	    {
		say(QCTNAME(ob) + " seems to be estimating something.\n", ob);
		return 1;
	    }
	  if (num < 1)
	    break;
      }
    
    if (num > 0)
      set_alarm(1.0, 0.0, &move_item(({name, num, ob})));
    return 1;
}

int
add_condiment(string str)
{
	object *drink;
	string cond, drinkname;

	NF("Try add condiment to drink.\n");
	if (!str)
		return 0;

	NF("Add what condiment to what drink?\n");

	if (sscanf(str, "%s to %s", cond, drinkname) != 2)
		return 0;

	if (!(drink = FIND_STR_IN_OBJECT(drinkname, TP)) || !sizeof(drink))
		return 0;

	if (parse_command(drinkname, ({}), "'apple-cider' / 'cafe-misto' / "
		+ "'cappuccino' / 'espresso' / 'latte' / 'harad' / 'mer-cafe' / "
		+ "'shoikan' / 'tantallon-peaberry' / 'tradewind' / 'black' / "
		+ "'green' / 'herbal' / 'drink' / 'cup' / 'tea' / 'coffee'"))
	{
		if (cond == "whipped cream")
		{
			drink->condiment_whip();
			return 1;
		}
		if (cond == "cream")
		{
			drink->condiment_cream();
			return 1;
		}
		if (cond == "cinnamon")
		{
			drink->condiment_cinna();
			return 1;
		}
		if (cond == "sugar")
		{
			drink->condiment_sugar();
			return 1;
		}
		if (cond == "honey")
		{
			drink->condiment_honey();
			return 1;
		}
		return 0;
	}
	return 0;
}
