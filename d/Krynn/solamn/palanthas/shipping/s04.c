/* Mortis 12.2005 
 * Smells through shipping
 * npc idea: gravel raker
 */

#include "../local.h"
#include CLOCKH

inherit SHIP_BASE;

string
query_to_jail()
{
  return "northwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  The warehouses of the professional warehouse district "
	+ "are all you can make out northwards, and a great, four-story, marble "
	+ "estate is to the south.  Bulwark Round curves northwest to its "
	+ "intersection with Palanthas Circle and east towards another estate.  "
	+ "The great white tower of the palace far to the southeast is still "
	+ "visible above the buildings from this distance.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Bulwark Round and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains.  The air is rich with the smells of wood, tar, and coffee "
	+ "borne on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The well-worn marble of Bulwark Round and its buildings "
	+ "gleams in the midday sun as people travel to and from the piers "
	+ "filling the street with the noisy murmurings of their daily "
	+ "business.  A cool, salty breeze blows south off the bay." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Bulwark Round catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers, sailors, and dockhands make their way about the "
	+ "street.  A misty, salty breeze blows south off the bay." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Bulwark Round amplifying the yellow glow of the street lamps.  "
	+ "A few dock workers still make their way about at this hour.  "
	+ "A cool, salty breeze blows south off the bay." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Bulwark Round south of the warehouses of Palanthas Circle");
    LONG("@@get_time_desc@@");

	ITEM(({"estate", "four-story estate", "marble estate", "great estate"}),
	  "One of the largest buildings in the shipping quarter, a great, four-"
	+ "story, marble estate is south at the end of a wide, gravel street.  "
	+ "Its ancient, copper roof has weathered green ages ago.\n");
	ITEM(({"roof", "ancient copper roof", "ancient roof", "copper roof"}),
	  "The roof of the great estate to the south has been done in copper "
	+ "that long ago weathered to green.  It is covered with tall, thin "
	+ "gargoyles, a few of which have copper accoutrements.\n");
	ITEM(({"accoutrement", "accoutrements", "copper accoutrement",
		   "copper accoutrements"}), "Copper accoutrements, long ago "
	+ "weathered green, such as collars, face masks, and spiked manacles "
	+ "adorn the gargoyles atop the roof of the southern estate.\n");
	ITEM(({"gravel", "gravel street", "wide gravel street", "wide street"}),
	  "Small piece, crushed marble has been raked perfectly level on the "
	+ "wide street leading south from Bulwark Round to a great, four-story "
	+ "estate.\n");

	EXIT(SHIP + "s03", "east", 0, 0);
	EXIT(SHIP + "mery", "south", "@@merch_closed", 0);
	EXIT(SHIP + "s05", "northwest", 0, 0);

}

int
merch_closed()
{
	write("The doors are not open to the public at this time.\n");
	return 1;
}
