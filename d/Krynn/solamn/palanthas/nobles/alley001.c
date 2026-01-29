/* Mortis 11.2005 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Between the buildings to the south is the equestrian "
	+ "field of the Solamnian Livery, the northern stable of which you "
	+ "glimpse between the buildings to the southwest.  The alley continues "
	+ "west to more side streets.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of this side street and its buildings "
	+ "reflects the pale purple hues in the sky above as the sun's morning "
	+ "rays light up the clouds.  A cool, misty breeze stirs the air." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of this side street and its buildings "
	+ "gleams in the midday sun overhead.  A few people pass through here "
	+ "at this time of day, but it is not a busy thoroughfare."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of this side street's buildings catches "
	+ "the last rays of the setting sun appearing to glow of its own accord.  "
	+ "Shadows climb slowly up the buildings on the east side of the street, "
	+ "and a cool breeze stirs the air." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of this side street and its buildings amplifying the yellow glow of "
	+ "the street lamps.  A cool, night breeze stirs the air.  Very few "
	+ "people pass through this alley at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("An alley in the nobles quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"stable", "stables", "longhouse"}), "The stable longhouse runs "
	+ "north from the livery manor house.  It's as large as a barn but much "
	+ "longer.  It is the only wooden building in the noble district built "
	+ "a generation ago when this estate changed hands.  A run of fenced "
	+ "corridors extends down the length of the stables for bringing horses "
	+ "to and from it in an orderly fashion.\n");

	EXIT(NOBLE + "alley002", "west", 0, 0);
	EXIT(NOBLE + "liv_ent", "south", 0, 0);

}
