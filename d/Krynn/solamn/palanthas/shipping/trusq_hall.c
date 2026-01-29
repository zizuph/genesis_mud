/* Mortis 02.2006
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

#define TRUSQ_HALL				SHIP + "trusq_hall"
#define LAPSIT					"_i_am_sitting_in_a_lap"
#define HAVELAP					"_i_have_a_lap_sitter"
#define FOUND_FIREPLACE_HOLE	"_i_found_trusq_fireplace_hole"

inherit SHIP_ROOMBASE;

string
query_to_jail()
{
  return "north";
}

void
reset_palan_room()
{
}

void
create_palan_room()
{
    SHORT("In a large hall of a merchant estate");
    LONG("Dark, oak paneling lines the walls of this large hall from "
	+ "the ground up to three feet with polished, translucent white marble "
	+ "taking over from there.  A wide strip of oak trim separates the "
	+ "paneling from the marble, and arranged upon it are vases of "
	+ "flowers, statuettes, and busts.  The hall stretches south where a "
	+ "long dining table and chairs are arranged.  Hanging on the south "
	+ "wall above the fireplace is a great tapestry, and you believe you "
	+ "see stairs to the west.\n");

	ITEM("foyer", "The foyer is north of here.\n");
	ITEM("hall", "You are in the hall.  Have a <look> around?\n");
	ITEM(({"wall", "walls", "panelling"}), "The bottom three feet of the "
	+ "walls in this hall have been paneled in wide strips of dark stained "
	+ "oak.  From there up is polished, translucent white marble.  The "
	+ "paneling and marble are separated by a wide strip of oak trim.\n");
	ITEM("marble", "The marble in the hall is translucent white and "
	+ "polished to a gleaming shine.\n");
	ITEM("floor", "The floor is made of large blocks of translucent white "
	+ "marble and polished to a shine.\n");
	ITEM("ceiling", "The ceiling has been finished with "
	+ "translucent white marble.\n");
	ITEM("trim", "A wide strim of oak trim separates the paneling from the "
	+ "marble.  Arranged upon it are vases of flowers, statuettes, and "
	+ "busts.\n");
	ITEM(({"vase", "vases", "flower", "flowers", "statuette", "statuettes",
		"bust", "busts"}), "Artfully arranged upon the wide strip of oak "
	+ "trim circling the room along the walls are glazed white and grey "
	+ "vases of roses, sunflowers, and lilies, small marble statuettes of "
	+ "nude athletes in sporting poses, and marble busts of a middle-aged "
	+ "bearded man and a lovely woman with a stern face.\n");
	ITEM(({"table", "chair", "chairs"}), "Arranged at the south end of the "
	+ "hall is a long, dark, wooden dining table with tall-backed, soft "
	+ "black leather cushioned, wooden chairs.\n");
	ITEM("tapestry", "A wide tapestry is hung high on the south wall.  It "
	+ "is very old and slightly faded, but you can still make out a scene "
	+ "of a man and woman sailing, then entering a white building and "
	+ "enjoying swimming, massages, and physical catering.  They are "
	+ "together in each scene.  In the corners of the tapestry is a "
	+ "symbol, a pair of gold balls each hanging from chains on opposite "
	+ "sides of a pronged balance.\n");
	ITEM("symbol", "It is the symbol of merchant house Trusq, a pair of "
	+ "gold balls each hanging from chains on opposite sides of a pronged "
	+ "balance.  The symbol is on the four corners of the tapestry hung "
	+ "high on the south wall.\n");
	ITEM(({"fire", "fireplace"}), "A brick fireplace is set into the south "
	+ "wall of the room providing warmth on cold nights." + "@@exa_fire@@"
	+ "\n");
	ITEM(({"ash", "ashes"}), "Ashes from spent fires lay scattered in the "
	+ "fireplace.\n");
	ITEM("vent", "@@exa_vent");

	add_smell("vampire", "The air is clean and fragranced with the scents of "
	+ "freshly cut roses, sunflowers, and lilies.  Your fangs throb with "
	+ "anticipation as you sense hot blood pumping through a great many "
	+ "hearts further in as you ignore the smells of food from the east.");
	add_smell("morgul", "The air is clean and fragranced with the scents of "
	+ "fresh flowers.  The smells of food cooking waft in from the east.");
	add_smell("human", "The air is clean and fragranced with the scents of "
	+ "fresh flowers.  The smells of food cooking waft in from the east.");
	add_smell("elf", "The air is clean and fragranced with the scents of "
	+ "freshly cut roses, sunflowers, and lilies.  There is human food "
	+ "being cooked to the east.");
	add_smell("goblin", "The air is odourless except for the sickly smells "
	+ "of flowery things, but even those cannot mask the smells of fresh "
	+ "food to the east.");
	add_smell("dwarf", "The air is clean and fragranced with the scents of "
	+ "fresh flowers.  Mouth-watering food is being cooked nearby to the "
	+ "east.");
	add_smell("hobbit", "The air here is clean in an indoor sort of way and "
	+ "fragranced with the scents of fresh roses, sunflowers, and lilies.  "
	+ "The smells of food cooking is strong to the east.  The kitchen!");
	add_smell("gnome", "The air is clean, not stale, and fragranced with the "
	+ "scents of fresh flowers.  Human food can be smelled from what is "
	+ "likely a kitchen to the east.");
	add_smell("minotaur", "The scent of flowers in the clean air coupled "
	+ "with food cooking in the east cannot mask the smells of man here.");
	add_smell("halfhuman", "The air is clean and fragranced with the scents of "
	+ "fresh flowers.  The smells of food cooking waft in from the east.");
	add_smell("halfelf", "The air is clean and fragranced with the scents of "
	+ "fresh flowers.  The smells of human food cooking waft in from the "
	+ "east.");
	add_smell("orc", "The scent of flowers in the sterile air cannot mask "
	+ "the scent of so much manflesh in this place.  The smells of food "
	+ "being cooked waft in from the east.");
	add_smell("hobgoblin", "The clean air would indicate humans keep this "
	+ "place well tended.  You smell fresh flowers here as well.  There "
	+ "must be a kitchen to the east as the smells of food being cooked "
	+ "are coming from that direction.");
	add_smell("kender", "The air here is nice and clean and fragranced with "
	+ "the scents of fresh flowers, but what really wriggles your nose is "
	+ "the smell of food being cooked in what can only be a kitchen to "
	+ "the east!");
	add_smell("drow", "The sterile air here would indicate the place is "
	+ "clean by human standards.  You detect the scents of freshly cut, "
	+ "overworld flowers, and to the east waft the smells of human food "
	+ "being prepared.");
	add_smell("noldor", "The air is clean by human standards and fragranced "
	+ "with the scents of freshly cut roses, sunflowers, and lilies.  Human "
	+ "food is being cooked in a kitchen to the east.");
	add_smell("uruk", "The scent of flowers in the sterile air cannot mask "
	+ "the scent of so much manflesh in this place.  Human food is being "
	+ "prepared to the east as well.");
	add_smell("presence", "You don't pick up much in your current state.");
	add_smell("unknown", "The air is clean and fragranced with flowers, but "
	+ "what the heck race are you?!?  Why not mail Krynn for fun?");

	EXIT(SHIP + "trusq_foyer", "north", 0, 0);
	EXIT(SHIP + "trusq_kitchen", "east", 0, 0);
	EXIT(SHIP + "trusq_stairs", "west", 0, 0);

	reset_palan_room();
}

string
exa_fire()
{
	if (TP->query_prop(FOUND_FIREPLACE_HOLE) == 1)
		return "  Behind the ash in the back of the fireplace is a vent "
		+ "where smoke from the fires rises through here and up the "
		+ "chimney.";

	if (TP->query_skill(SS_AWARENESS) > 20 + random(20))
	{
		TP->add_prop(FOUND_FIREPLACE_HOLE, 1);
		return "  You discover a large vent behind the ash in the back of "
		+ "the fireplace where smoke from the fires rises through here and "
		+ "up the chimney.";
	}
	return "";
}

string
exa_vent(string str)
{
	if (TP->query_prop(FOUND_FIREPLACE_HOLE) != 1)
		return "You find no " + str + ".\n";

	return "If you were small enough, or able to contort your body into "
	+ "acrobatic positions, you might be able to crawl into the vent in the "
	+ "back of the fireplace.  It's pretty filthy though.\n";
}

void 
init()
{    
    ::init();
    ADD("action_sit", "sit");
	ADD("action_stand", "stand");
	ADD("crawl_vent", "crawl");
}

int 
action_sit(string str)
{
	object tp1 = TP;

	if(TP->query_prop(TSIT))
	{
		write("But you are already sitting by the table! How do you "
		+ "expect to sit in two places at once?\n");
		return 1;
	}
           
	if(TP->query_prop(LAPSIT))
	{
		write("But you are already sitting in someone's lap! How do you "
		+ "expect to sit in two places at once?\n");
		return 1;
	}

	if (!str)
	{
		TP->catch_msg("Where would you like to sit?  In a chair around the "
		+ "table?\n");
		return 1;
	}
           
	if(parse_command(str, ({}),
	"[around] [at] [in] [by] [the] [a] 'table' / 'chair' [around] [at] [in] [by] [the] [a] [table]"))
	{
		TP->catch_msg("You sit down in one of the tall-backed chairs "
		+"near the table.\n");
		say(QCTNAME(TP) + " sits down in one of the tall-backed "
		+"chairs near the table.\n");
		TP->add_prop(TSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting near the table");
		return 1;
	}
        
	object *inv, *ppl, target, lapobj;

	target = find_object(TRUSQ_HALL);
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
		TP->catch_msg("Where would you like to sit?  In a chair around a "
		+ "table?  Or did you want to <sit in lap of someone>?\n");
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
				lappee->add_prop(LIVE_S_EXTRA_SHORT, " is sitting near the table");
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
                
	if (TP->query_prop(HAVELAP))
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
	}

	if(TP->query_prop(TSIT))
	{
		TP->catch_msg("You stand up from the table before leaving.\n");
		say(QCTNAME(TP) + " stands up from the table as "+ HE(TP)
		+ " leaves.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		TP->remove_prop(TSIT);
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
			lappee->add_prop(LIVE_S_EXTRA_SHORT, " is sitting near the table");
	}
}

int
crawl_vent(string str)
{
	string ventrace = QRACE(TP);

	NF("What?\n");
	if (TP->query_prop(FOUND_FIREPLACE_HOLE) != 1)
		return 0;

	NF("Crawl into what?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[in] [into] [the] 'vent' [in] [the] [back] [of] [the] [fireplace]"))
		return 0;

	if (TP->query_skill(SS_ACROBAT) >= 15 + random(6) ||
		ventrace == "hobbit" || ventrace == "kender" || ventrace == "gnome")
	{
		write("You crawl through the ash to the vent in the back of the "
		+ "fireplace and squeeze your way inside.\n");
		TP->move_living("crawls through the ash in the fireplace and "
		+ "disappears into a vent", SHIP + "trusq_chimney1", 1, 0);
		return 1;
	}

	write("You can't quite contort yourself to fit inside the vent, strain "
	+ "as you might.  You'd need an acrobat or a midget to fit inside that "
	+ "thing!\n");
	say(QCTNAME(TP) + " crawls through the ash in the fireplace and tries "
	+ "to squeeze " + HIS(TP) + " way in deeper.\n");
	return 1;
}
