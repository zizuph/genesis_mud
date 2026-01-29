/* 
 * Outside Kirk's hq on Jems Court.
 *
 * Mortis 05.2006
 * 
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <ss_types.h>

#define FOUND_BRIX_WALL_INFO		"_found_brix_wall_info"

inherit MONKS_BASE;

string
query_to_jail()
{
	return "west";
}

object hood1, hood2, hood3;

void
reset_palan_room()
{
	if (!hood1)
	{
		hood1 = clone_object(MONKS + "living/brix_ganger_low");
		hood1->move(TO);
	}

	if (!hood2)
	{
		hood2 = clone_object(MONKS + "living/brix_ganger_low");
		hood2->move(TO);
	}

	if (!hood3)
	{
		hood3 = clone_object(MONKS + "living/brix_ganger_hacardus");
		hood3->move(TO);
	}
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Jems court curves in an oval around this shadowy "
	+ "backstreet running west further into the court.  Before you to the "
	+ "east is a run-down, two-story house.  Row upon row of the backs of "
	+ "tightly packed houses are all you can see in this housing district.  "
	+ "The street is dusty and littered with debris.  The street cleaners "
	+ "must not come here.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Jems court and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn, dusty marble of Jems court and its buildings lights "
	+ "up in the midday sun.  Only occasionally do you notice people or "
	+ "aesthetics quickly passing through." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The worn, dusty marble of Jems court catches the "
	+ "last rays of the sun appearing to glow in a dull fashion "
	+ "as travellers and the occasional maroon robed aesthetics make their "
	+ "way about the court." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Jems court amplifying the yellow glow of the street lamps.  "
	+ "A few poorly dressed people still make their way about at "
	+ "this hour some stumbling in from the west." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On a backstreet at the center of Jems court in the southwest "
	+ "housing district of the aesthetics quarter in front of a two-story, "
	+ "run-down house to the east");
    LONG("@@get_time_desc@@");

	ITEM(({"court", "jems court", "jems", "housing district", "houses"}),
	  "A large housing district unfolds around you to the east and "
	+ "west.  The houses are densely arranged around Jems court, a long "
	+ "oval of a street.  Though mostly well-worn marble, portions of the "
	+ "street have been replaced with beige, clay bricks while some blocks "
	+ "are missing entirely and are potholes of dirt and muck.  The houses "
	+ "are smaller than most in the city.  Several are two-stories, but a "
	+ "good deal are only one.  Marble isn't uncommon here, but it's no "
	+ "more prevalent than brick and wood.  Street lamps are not arranged "
	+ "so orderly in this part of the city either.\n");
	ITEM("house", "Any house in particular?  North?  South?  East?  "
	+ "West?\n");
	ITEM(({"north house", "south house"}), "\n");
	ITEM(({"east house", "run-down house", "two-story"}), "A run-down, "
	+ "two-story house is before you to the east.  It is built from tan "
	+ "bricks with old, gray mortar and an aging, wood shingled roof.  It "
	+ "is covered with chalk graffiti.\n");
	ITEM(({"graffiti", "chalk graffiti"}), "Chalk graffiti covers the "
	+ "run-down, two-story house to the east running the gamut from "
	+ "poorly spelled profanity to obscene stick figures to knives and "
	+ "skulls." + "@@wall_aware@@" + "\n");
	ITEM(({"wall", "walls"}), "The walls of the run-down, two-story "
	+ "house to the east are covered in chalk graffiti.\n");
	ITEM(({"debris", "litter"}), "Bottles, broken glass, broken old wooden "
	+ "shingles, and a rusted bar or cap of metal here and there litter the "
	+ "alleys and walkways between the houses in this backstreet.  The "
	+ "street cleaners must not come here for some reason.\n");

	add_smell("vampire", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.  The scent of blood is weak here, but "
	+ "grows strong inside the house to the east.");
	add_smell("morgul", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.");
	add_smell("human", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.");
	add_smell("elf", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  The ghastly combination turns your stomach.");
	add_smell("goblin", "The air is filled with the smells of old booze, "
	+ "smoke, and piss.  It reminds you of home.");
	add_smell("dwarf", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.");
	add_smell("hobbit", "The air is tainted with the smells of stale alcohol "
	+ "and urine, but the leaf smoke in the air makes your nose twitch "
	+ "curiously.");
	add_smell("gnome", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  By human standards this must be acceptable, "
	+ "but your gnomish nose tells you the air quality has been compromised "
	+ "to dangerous levels.");
	add_smell("minotaur", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.");
	add_smell("halfhuman", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.");
	add_smell("halfelf", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.  It is rather unpleasant.");
	add_smell("orc", "The air is filled with the smells of old booze, "
	+ "smoke, and piss.  It reminds you of home.");
	add_smell("hobgoblin", "The air is filled with the smells of old booze, "
	+ "smoke, and piss.  Filthy but welcoming in a homely sort of way.");
	add_smell("kender", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  Gross!");
	add_smell("drow", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  These surface dwellers live like pigs.");
	add_smell("noldor", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  The revolting combination sickens you.");
	add_smell("uruk", "The air is filled with the smells of old booze, "
	+ "smoke, and piss.  Filthy but welcoming in a homely sort of way.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "air filled with the smells of a human back alley.");
	add_smell("unknown", "You smell the air rich with the smells of a human "
	+ "back alley, but what the heck race are you?  Why not mail Krynn for "
	+ "fun?");

	clone_object(MONKS + "doors/brix_kirk_door_out")->move(TO);
	
	EXIT(MONKS + "alley054", "west", 0, 0);

	reset_palan_room();
}

void
init()
{
    ::init();
    ADD("climb_wall", "climb");
}

string
wall_aware()
{
	string seeledge;

	if (TP->query_skill(SS_AWARENESS) > 21 + random(6)) // Skill 110
	{	
		TP->add_prop(FOUND_BRIX_WALL_INFO, 1);
		seeledge = "  The walls themselves are nicked and damaged from blows "
		+ "all over making them easier to climb if one were so inclined.";
	}

	else
		seeledge = "";

	return seeledge;
}

int
climb_wall(string str)
{
	if (TP->query_prop(FOUND_BRIX_WALL_INFO) == 1 )
	{
		NF("Climb up to what?\n");
		if (!str)
			return 0;

		if (!parse_command(str, ({}), "[up] [to] 'roof' / 'walls' / 'wall'"))
			return 0;

		if (TP->query_skill(SS_CLIMB) < 31 + random(4))
		{
			write("You try to climb up to the roof but slip and fall!\n"
			+ "You just can't seem to make it.  Maybe you need climbing "
			+ "assistance of some sort?\n");
			say(QCTNAME(TP) + " " + one_of_list(({"tries to climb up the "
			+ "walls of the run-down house to the east but slips, falls, and "
			+ "lands on " + HIS(TP) + " butt in a heap on the street.",
			  "lays flat against the wall of the run-down house to the east "
			+ "and humps it impotently in a failed attempt to scale it, "
			+ "or so you guess.",
			  "pounds " + HIS(TP) + " fists against the nicked walls of the "
			+ "run-down house to the east in a feeble attempt to climb it.",
			  "sighs as " + HE(TP) + " wishes " + HE(TP) + " had a rope"
			+ "."})) + "\n");
			return 1;
		}

		write("Using the missing chunks and nicks as handholds, you "
		+ "successfully climb onto the sagging roof of the two-story, "
		+ "run-down house to the east.\n"); 
		TP->move_living("climbing up onto the roof of the two-story, "
		+ "run-down house to the east", MONKS + "brix_kirk_roof", 1, 0);
		return 1;
	}
	
	NF("What?\n");
	return 0;
}
