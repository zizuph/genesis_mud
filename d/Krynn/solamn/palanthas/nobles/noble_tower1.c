/* Mortis 12.2005 
 * Smells of what's below and guards above
 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_ROOMBASE;

string
query_to_jail()
{
  return "north";
}

object guard1, guard2;

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "Wide, polished oak floorboards run flat against the "
	+ "curved, translucent white marble of this perfectly circular ground "
	+ "floor of a Palanthas guard tower.  Grey, stone stairs curve along "
	+ "the wall leading up to the second floor and down to the cellar.  The "
	+ "ceiling is over a dozen feet high.  Outside the doorway to the "
	+ "north ";  // ...continued in TIMEOFDAY description.
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += road + "the clean marble of the street and buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains.\n";
	break;

    case TOD_DAY:
	desc += road + "the clean marble of the street and "
	+ "buildings gleams in the midday sun as people travel to and from "
	+ "the piers filling the street with the noisy murmurings of their "
	+ "daily business.\n";
	break;

    case TOD_TWILIGHT:
	desc += road + "the translucent marble of the street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the "
	+ "street.\n";
    break;

    case TOD_NIGHT:
	desc += road + "the moon and stars shed pale light across the "
	+ "translucent marble of the street amplifying the yellow glow "
	+ "of the street lamps.  A  few people still make their way about "
	+ "at this hour.\n";
    break;

    default:
	break;
    }
    return desc;
}

void
reset_palan_room()
{
	if (!guard1)
		guard1 = clone_object(LIV + "city_guard");
		guard1->move(TO);
	if (!guard2)
		guard2 = clone_object(LIV + "city_guard");
		guard2->move(TO);
}

void
create_palan_room()
{
    SHORT("The ground floor of a Palanthas guard tower");
    LONG("@@get_time_desc@@");

	ITEM(({"short tower", "short marble tower", "marble tower"}), "You're "
	+ "inside a tower of translucent, white marble rising at least forty "
	+ "feet into the air.  Why not have a <look> around?\n");
	ITEM(({"floor", "floorboard", "floorboards"}), "The floor must be "
	+ "heavily reinforced and the oak floorboards exceptionally sturdy for "
	+ "there is neither give nor creak when trod upon.  The floorboards are "
	+ "long, wide, and of smoothly polished oak.\n");	
	ITEM(({"wall", "walls"}), "Built entirely of large, translucent white "
	+ "marble blocks, the walls are at least two feet thick and polished to "
	+ "a reflective shine.  At the cardinal points of the tower are hung "
	+ "banners displaying the symbol of the current Lord Constable of "
	+ "Palanthas, " + "@@constable_symbol@@" + "\n");
	ITEM(({"banner", "banners", "symbol"}), "Hung on the walls at the four "
	+ "cardinal points are banners bearing the symbol of the current Lord "
	+ "Constable of Palanthas, " + "@@constable_symbol@@" + "\n");
	ITEM("ceiling", "Thick, wide boards of polished oak reinforced with "
	+ "small, triangular wall supports form a high ceiling and the floor of "
	+ "the level above.  It is at around fourteen feet high, tall enough "
	+ "for most weapons to stand upright.  An iron chain suspends a large, "
	+ "oil lamp providing indoor light.\n");
	ITEM(({"large oil lamp", "ceiling lamp", "oil lamp", "large lamp"}),
	  "Hanging from a two foot, iron chain in the center of the ceiling is "
	+ "a large, oil lamp shedding steady light in the room.\n");
	ITEM("stairs", "Stairs of rough, grey, stone lead up to the second floor "
	+ "and down into the cellar.\n");
	ITEM("grey stone", "Neatly cut but left rough for traction, the grey "
	+ "stone of the stairs contrasts with the translucent white of the "
	+ "marble walls.\n");
	ITEM("cellar", "The stairs leading down into the cellar curve out of "
	+ "sight along the wall below offering little view of what's below.\n");

	EXIT(NOBLE + "n17", "north", 0, 0);
	EXIT("/d/Krynn/clubs/pkc/club1", "southwest", 0, 0);
	EXIT(NOBLE + "noble_tower1_2", "up", 0, 0);
	EXIT(NOBLE + "noble_tower1_0", "down", 0, 0);

	reset_palan_room();
}

