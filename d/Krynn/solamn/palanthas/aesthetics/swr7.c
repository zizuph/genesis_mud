/* Mortis 12.2005 
 * Housing smells?
 */

#include "../local.h"
#include CLOCKH

inherit MONKS_BASE;

string
query_to_jail()
{
  return "northeast";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Vingaard road heads northeast between the merchant "
	+ "quarter to the northwest and aesthetics quarter to the southeast "
	+ "and through the city gates leads out of the city.  Old Circle "
	+ "curves along the inside of the city wall to the northwest and "
	+ "southeast.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Vingaard road and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The dusty marble of Vingaard road and its buildings "
	+ "gleams somewhat in the midday sun as people travel to and from the "
	+ "plaza filling the street with the noisy murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The dusty, translucent marble of Vingaard road catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the dusty, "
	+ "translucent marble of Vingaard road amplifying the yellow glow of "
	+ "the street lamps.  A few people still make their way about at this "
	+ "hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
reset_palan_room()
{
 
}

void
create_palan_room()
{
	object gate;

    SHORT("On Vingaard northeast of the southwestern city gates");
    LONG("@@get_time_desc@@");

	ITEM(({"south court", "jems court", "jems", "housing district", "houses"}),
		"A large housing district unfolds before you to the east.  "
	+ "They are densely arranged arround Jems court, a long oval of a "
	+ "street between Aesthetics Row and Vingaard road.  Though almost "
	+ "entirely well-worn marble, portions of the street have been "
	+ "replaced with beige, clay bricks.  The houses are smaller than "
	+ "most in the city.  Several are two-stories, but a good deal are "
	+ "only one.  Marble isn't uncommon here, but it's as prevalent as "
	+ "brick and wood.  Street lamps are not arranged so orderly in this "
	+ "part of the city either.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the southwest.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot dark grey rock which comprises "
	+ "its core.  The wall is in decent repair.\n");

	EXIT(MONKS + "swr6", "northeast", 0, 0);
	EXIT(MONKS + "w19", "southeast", 0, 0);
	EXIT(MERCH + "w20", "northwest", 0, 0);

	gate = clone_object(MONKS + "doors/city_swgate1.c");
	gate->move(TO);

	reset_palan_room();

}