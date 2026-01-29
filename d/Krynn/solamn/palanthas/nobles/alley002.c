/* Mortis 11.2005 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the south is the stable of the Solamnian Livery.  "
	+ "The alley wraps around it heading southwest to Inner Circle street "
	+ "and east to more side streets.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of this side street and its buildings "
	+ "reflects the pale purple hues in the sky above as the sun's morning "
	+ "rays light up the clouds.  A cool, misty breeze blows gently "
	+ "from the northwest." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of this side street and its buildings "
	+ "gleams in the midday sun overhead.  A few people pass through here "
	+ "at this time of day, but it is not a busy thoroughfare.  A warm "
	+ "breeze from the northwest stirs the air." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of this side street's buildings catches "
	+ "the last rays of the setting sun appearing to glow of its own accord.  "
	+ "Shadows climb slowly up the buildings on the east side of the street, "
	+ "and a cool breeze from the northwest stirs the air." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of this side street and its buildings amplifying the yellow glow of "
	+ "the street lamps.  A cool, night breeze blows gently from the "
	+ "northwest.  Very few people pass through this alley at this hour."
	+ road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("An alley north of a stable");
    LONG("@@get_time_desc@@");

	ITEM(({"nw alley", "northwest alley"}), "A narrow alley leads northwest "
	+ "between great, marble buildings to a flight of stairs along the side "
	+ "of the building to its left.\n");

	ITEM(({"stairs", "flight", "flight of stairs"}), "The flight of stairs "
	+ "climbing along the building to its left is built of slabs of "
	+ "translucent marble with a burnished, wrought iron handrail.  It is "
	+ "in fact two flights of stairs with a short landing between them.  "
	+ "You cannot see what it is they lead to, but they are heading in the "
	+ "direction of Scholar's Walk.\n");

	ITEM(({"stable", "stables", "longhouse"}), "The stable longhouse runs "
	+ "north from the livery manor house.  It's as large as a barn but much "
	+ "longer.  It is the only wooden building in the noble district built "
	+ "a generation ago when this estate changed hands.  A run of fenced "
	+ "corridors extends down the length of the stables for bringing horses "
	+ "to and from it in an orderly fashion.\n");

	ITEM(({"livery", "solamnian livery", "house", "manor", "manor house"}),
	  "The two-story manor house is an old, translucent marble building "
	+ "whose grounds were converted ages ago to accomodate the field, "
	+ "wood-fenced corral, and stables.  Below its roof is a band of "
	+ "chiselings, and along its edge are a good many crouching gargoyles."
	+ "  Atop the steep sloped, marble tiled roof is a cupola, its copper "
	+ "roof turned green with weathering long ago.  An oversized copper "
	+ "door leads into the house, its ornate stylings still bright from "
	+ "frequent polishing.\n");

	add_alley("nw", "northwest", NOBLE + "alley005");

	EXIT(NOBLE + "alley001", "east", 0, 0);
	EXIT(ROOM + "ic3", "southwest", 0, 0);

}