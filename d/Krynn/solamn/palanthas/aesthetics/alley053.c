/* 
 * Mortis 05.2006
 * 
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit MONKS_BASE;

string
query_to_jail()
{
	return "north";
}

int h4 = random(3);
object hood1, hood2, hood3, hood4;

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
		hood3 = clone_object(MONKS + "living/brix_ganger_low");
		hood3->move(TO);
	}

	if (h4 == 1)
	{
		if (!hood4)
		{
			hood4 = clone_object(MONKS + "living/brix_ganger_low");
			hood4->move(TO);
		}
	}
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Jems court curves in an oval around this shadowy "
	+ "backstreet running east further into the court and sloping west "
	+ "down into a tunnel.  Row upon row of the backs of tightly packed "
	+ "houses are all you can see in this housing district.  The street is "
	+ "dusty and littered with debris.  The street cleaners must not come "
	+ "here.\n";
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
	+ "housing district of the aesthetics quarter");
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
	ITEM("house", "Any house in particular?  North?  South?\n");
	ITEM(({"north house", "northern house"}), "A small, two-story house "
	+ "is to your north.  It is built from tan bricks with old, gray "
	+ "mortar and an aging, wood shingled roof.  Its backdoor is boarded "
	+ "shut.\n");
	ITEM(({"south house", "southern house"}), "A small, two-story house "
	+ "is to your south.  It is built from tan bricks with crumbling, gray "
	+ "mortar and an aging, wood shingled roof.\n");
	ITEM(({"debris", "litter"}), "Bottles, broken glass, broken old wooden "
	+ "shingles, and a rusted bar or cap of metal here and there litter the "
	+ "alleys and walkways between the houses in this backstreet.  The "
	+ "street cleaners must not come here for some reason.\n");
	ITEM("tunnel", "To the west the backstreet slopes down into a tunnel "
	+ "beneath the streets.\n");

	add_smell("vampire", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.  The scent of blood is weak here.");
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

	EXIT(MONKS + "a12", "north", 0, 0);
	EXIT(MONKS + "a13", "northeast", 0, 0);
	EXIT(MONKS + "alley054", "east", 0, 0);
	EXIT(MONKS + "a20", "south", 0, 0);
	EXIT(MONKS + "alley052", "west", 0, 0);

	reset_palan_room();
}
