/* 
 * Roof of Kirk's hq off Jems Court.
 *
 * Mortis 06.2006
 * 
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <ss_types.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

#define VIEWEAST			(MONKS + "brix_kirk_alley")
#define VIEWWEST			(MONKS + "alley055")

inherit MONKS_BASE;

void
reset_palan_room()
{
}

nomask public string
get_time_desc()
{
    string desc = "";
	string roof = "  The steep roof of this dilapidated, old house is "
	+ "sagging heavily, its aged, grey wooden shingles cracking and "
	+ "falling out of place.  The backstreet of Jems court stretches out "
	+ "before you to the west, your high vantage point offering you a "
	+ "commanding view.  Jems court curves in an oval around this shadowy "
	+ "backstreet of which you are at the east end.\n";
	
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Jems court and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze." + roof;
	break;

    case TOD_DAY:
	desc += "The worn, dusty marble of Jems court and its buildings lights "
	+ "up in the midday sun.  Only occasionally do you notice people or "
	+ "aesthetics quickly passing through down below." + roof;
	break;

    case TOD_TWILIGHT:
	desc += "The worn, dusty marble of Jems court catches the "
	+ "last rays of the sun appearing to glow in a dull fashion "
	+ "as travellers and the occasional maroon robed aesthetics make their "
	+ "way about the court below." + roof;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Jems court amplifying the yellow glow of the street lamps.  "
	+ "A few poorly dressed people still make their way about at "
	+ "this hour some stumbling in down below." + roof;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On the roof of a dilapidated, crumbling gang house");
    LONG("@@get_time_desc@@");

	ITEM("house", "Any house in particular?  You're on a house.  Why not "
	+ "have a <look> around or even check out the view?\n");
	ITEM(({"shingles", "shingle", "roof", "rooftop"}), "The aged, grey wooden "
	+ "shingles of the roof are warped and creak when walked upon.  You spot "
	+ "a rope handled trapdoor sawed into the northeast corner.\n");
	ITEM("trapdoor", "Sawed directly through the roof in the northeast "
	+ "corner with a knotted length of rope stuck through an eye for a "
	+ "handle is a trapdoor.  You notice the wooden shingles surrounding it "
	+ "look too old and dilapidated to support much weight.\n");
	ITEM(({"view", "court", "street", "streets", "backstreet", "alley"}),
	  "From your vantage point atop the dilapidated, old roof rows upon rows "
	+ "of the rooftops of tightly packed houses stretch out before you.  You "
	+ "can take a closer look at the backstreet below you to the west with "
	+ "<view court>.  With all the nicks and blows that have landed upon the "
	+ "walls of this house, you could probably climb down to the west.  "
	+ "There is a small, dark alley on the east side of the house you could "
	+ "check out with <view east>.\n");
	ITEM(({"small dark alley", "small alley", "dark alley", "east alley"}),
	  "You could try to take a closer look with <view east> or possibly "
	+ "climb down with some sort of climbing aid, rope, or great skill.\n");

	add_smell("vampire", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.  The scent of blood is stronger "
	+ "here.");
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

	CMD(({"east", "e"}), "view", "@@view_east");
	CMD(({"west", "w", "court"}), "view", "@@view_west");
	CMD(({"trapdoor", "trap door", "rope", "handle", "rope handle"}),
		({"enter", "pull"}), "@@use_trapdoor");

	reset_palan_room();
}

void
init()
{
    ::init();
    ADA("climb");
}

int
view_east()
{
	/* This function returns an equivalent of 'look' from brix_kirk_alley
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWEAST->long());
	target = find_object(VIEWEAST);
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
						+ desc + " in the alley.\n");
 
	return 1;
}

int
view_west()
{
	/* This function returns an equivalent of 'look' from alley055
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
	write(one_of_list(({"From above you can make out ",
						"You believe you spot ",
						"Your eyes come across "}))
						+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write(one_of_list(({"Down below you see ",
						"You notice below ",
						"Down below you spy "}))
						+ desc + " outside the house.\n");
 
	return 1;
}

int
use_trapdoor()
{
	write("You lift the trapdoor's rope handle with a wood-straining "
	+ "CREEEEAK, and climb down through it.\n");
	say(QCTNAME(TP) + " lifts the trapdoor's rope handle with a wood-"
	+ "straining CREEEEAK, and disappears as " + HE(TP) + " climbs down "
	+ "through it.\n");
	TP->move_living("climbing through the trapdoor in a flurry of "
	+ "thick, grey dust", MONKS + "brix_kirk_hq", 0, 0);
	return 1;
}

int
climb(string str)
{
	NF("Climb down where?  To the west or east?\n");
	if (!str)
		return 0;

	if (parse_command(str, ({}), "[down] [to] [the] 'west' / 'court'"))
	{
		if (TP->query_skill(SS_CLIMB) < 31 + random(4))
		{
			int dmg;

			write("You try to climb off to the roof to the west but slip "
			+ "and fall!\n");
			say(QCTNAME(TP) + " tries to climb off the roof to the west but "
			+ "slips and falls!\n");
			TP->command("scream");
			TP->move_living("falling off the roof of the two-story house",
				MONKS + "alley055", 1, 0);

			dmg = 100 + random(50) - TP->query_skill(SS_ACROBAT);
			TP->heal_hp(dmg);

			if (TP->query_hp() <= 0)
				TP->do_die(E(TO));

			return 1;
		}

		write("Using the missing chunks and nicks as handholds, you "
		+ "successfully climb down off the sagging roof of the two-story, "
		+ "run-down house.\n"); 
		TP->move_living("climbing down to the west off the roof of the "
		+ "two-story house", MONKS + "alley055", 1, 0);
		return 1;
	}

	if (parse_command(str, ({}), "[down] [to] [the] [small] [dark] 'east' / 'alley'"))
	{
		if (TP->query_skill(SS_CLIMB) < 38 + random(4))
		{
			int dmg;

			write("You try to climb off to the roof to the east but slip "
			+ "and fall!\n");
			say(QCTNAME(TP) + " tries to climb off the roof to the east but "
			+ "slips and falls!\n");
			TP->command("scream");
			TP->move_living("falling off the roof of the two-story house",
				MONKS + "brix_kirk_alley", 1, 0);

			dmg = 100 + random(50) - TP->query_skill(SS_ACROBAT);
			TP->heal_hp(dmg);

			if (TP->query_hp() <= 0)
				TP->do_die(E(TO));

			return 1;
		}

		write("Using the missing chunks and nicks as handholds, you "
		+ "successfully climb down off the sagging roof of the two-story, "
		+ "run-down house into the small, dark alley to the east.\n"); 
		TP->move_living("climbing down to the east off the roof of the "
		+ "two-story house", MONKS + "brix_kirk_alley", 1, 0);
		return 1;
	}

	return 0;
}
