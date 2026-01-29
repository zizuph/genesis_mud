/* Mortis 12.2005 
 * Alleys sw to vantage point atop building next to E. great merchant house.
 */

#include "../local.h"
#include CLOCKH

inherit SHIP_BASE;

string
query_to_jail()
{
  return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Trade road leads north through the shipping district to "
	+ "the city gates and bay and south to Inner Circle street past which a "
	+ "grove of well cultivated trees grows.  Through the buildings to "
	+ "the northwest you see Bulwark Round with its great estates and to "
	+ "southeast winds Lotelis Avenue.  The white tower of the palatial "
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
    SHORT("On Trade road south of Palanthas Circle");
    LONG("@@get_time_desc@@");

	ITEM(({"city gates", "city gate", "n gate", "n gates", "north gate",
		   "north gates", "north city gates"}), "A large metal gate.\n");
	ITEM(({"tree", "trees", "grove"}), "A great grove of well cultivated "
	+ "oaks, birches, poplars, and cedar grows to the south, their rich, "
	+ "green leaves rustle softly in the breeze off the bay.  It is "
	+ "forbidden by law to enter this palatial wood unbidden.\n");

	EXIT(SHIP + "tr3", "north", 0, 0);
	EXIT(ROOM + "tr1", "south", 0, 0);

}