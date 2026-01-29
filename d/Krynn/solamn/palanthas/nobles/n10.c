/* Mortis 11.2005
 * Alleys into the heart?
 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

#define MINSTREL "/d/Terel/guilds/minstrels/living/travelling_repairer"

object wguard, minstrel;

string
query_to_jail()
{
	return "north";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the west is the nobles park, its high, green "
	+ "hedges broken only by a bough arch through which a white gravel "
	+ "path enters.  Through the buildings, you spot to the east a noble "
	+ "estate.  Palanthas Circle curves south towards Knight's High "
	+ "road and north where it intersects with Nobles' Way.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Palanthas Circle and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Palanthas Circle and its buildings "
	+ "gleams in the midday sun as people walk about the intersection "
	+ "filling the streets with the gentle murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Palanthas Circle and its buildings "
	+ "catches the last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle and its buildings amplifying the yellow glow of the "
	+ "street lamps.  A few people still make their way about at this hour."
	+ road;
    break;

    default:
	break;
    }
    return desc;
}

void
reset_palan_room()
{
    if (!wguard)
    {
        wguard = clone_object(LIV + "city_guard_wander");
        wguard->set_monster_home(NOBLE + "n10");
        wguard->set_restrain_path(NOBLE);
        wguard->set_random_move(55);
        wguard->move(TO);
    }

    if(!objectp(minstrel))
    {
        minstrel = clone_object(MINSTREL);
        minstrel->move(TO, 1);
    }
}

void 
create_palan_room()
{
    SHORT("On Palanthas Circle east of the nobles park in the "
	+ "heart of the nobles district");
    LONG("@@get_time_desc@@");

	ITEM(({"estates", "estate", "noble estate", "noble estates"}),
	  "Through the buildings to the east can be seen one of the "
	+ "larger noble estates among the other marble buildings.\n");
	ITEM(({"hedge", "hedges", "bush", "bushes"}), "You see a tall hedge of "
	+ "well tended and cultured bushes trimmed and squared off on all sides "
	+ "and rising over ten feet to your west.  A bough of green arcs above "
	+ "the white gravel path leading through the hedge.  It is too dense to "
	+ "peer through.\n");
	ITEM("bough", "Likely a cultivated bush limb, it is a smoothly trimmed "
	+ "arc of green above the entryway through the hedges into the park.\n");
	ITEM("park", "It is the nobles park of Palanthas.  You catch the sparkle "
	+ "of a jet of water above the hedge from within the park.\n");
	ITEM("path", "A path of translucent white marble gravel leads west from "
	+ "here through the hedges into the park.\n");
	
	add_smell("vampire", "Misty air blowing south off the bay mingles here "
	+ "with the smells of lush, wet greenery to the west and noble dwellings "
	+ "to the east where the scent of blood catches your attention.");
    add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the smell of greenery to your west.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of lush greenery to the west and perfumes to the east.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the scent of lush greenery, flowers, and water from the park through "
	+ "the hedge to the west and the smells of a noble human dwelling to the "
	+ "east.");
	add_smell("goblin", "The fresh smells of dirt and green things from the "
	+ "west mix here with misty air blowing south off the bay.");
	add_smell("dwarf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of greenery to your west.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the fresh smells of a lush green park through the hedges to "
	+ "your west and a human estate to the east which, judging by the "
	+ "perfumes, must be a lovely place.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor are the smells of plant life and "
	+ "flowing water to the west and human dwelling odours to the "
	+ "east.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the lush, wet scents of green growing things to the west and "
	+ "man house smells to the east.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the smell of lush greenery to the west and the hint of perfumes "
	+ "to the east.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the not unfamiliar smells of human perfumes from the estates to "
	+ "your east and lush, wet greenery with a hint of flowers to your west.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the smells of human estates to the east and water, dirt, and "
	+ "plants to your west.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a well to do estate to the east and a lush park "
	+ "through the hedges to your west.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the fresh smells of a lush green park through the hedges to "
	+ "your west and a human estate to the east which, judging by the "
	+ "perfumes, must be a lovely place.");
	add_smell("noldor", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a human cultured park through the hedges to your "
	+ "west.  From the east comes the typical smell of a noble human estate.");
	add_smell("unknown", "You smell the park to your west and estate to the "
	+ "east, but your race is unknown to the immortals!  Please mail "
	+ "Krynn with your race.");

	EXIT(NOBLE + "park", "west", 0, 0);
	EXIT(NOBLE + "er3", "north", 0, 0);
	EXIT(NOBLE + "n11", "south", 0, 0);

	reset_palan_room();
}