/* Mortis 12.2005 
 *
 */

#include "../local.h"
#include CLOCKH

inherit SHIP_BASE;

string
query_to_jail()
{
  return "south";
}

void
reset_palan_room()
{
 
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Trade road leads south through the city gates into "
	+ "the shipping quarter of Palanthas.  Landing street runs northwest "
	+ "and east from here to the piers.  The white tower of the palatial "
	+ "plaza at city center is visible even from here.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Trade road and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of wood, tar, and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The well-worn marble of Trade road and its buildings "
	+ "gleams in the midday sun as people travel to and from the piers "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Trade road catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as merchants, sailors, and dockhands make their way about the street."
	+ road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Trade road amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
	object gate;

    SHORT("On Trade road and Landing street");
    LONG("@@get_time_desc@@");

	EXIT(SHIP + "s12", "east", 0, 0);
	EXIT(SHIP + "s15", "northwest", 0, 0);

	gate = clone_object(SHIP + "doors/city_ngate2.c");
	gate->move(TO);

	reset_palan_room();

}