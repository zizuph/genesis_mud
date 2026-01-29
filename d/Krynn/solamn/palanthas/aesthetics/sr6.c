/* Mortis 12.2005 
 * Smells?
 */

#include "../local.h"
#include CLOCKH

#define HERBTRAIL_START "/d/Krynn/solamn/pal_herbtr/palherbtr1"

inherit MONKS_BASE;

string
query_to_jail()
{
  return "north";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Aesthetics Row leads north towards Palanthas Circle "
	+ "in the heart of the quarter and south out the southern city gates.  "
	+ "Old Circle curves along the inside of the city wall to the east "
	+ "and west.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Aesthetics Row and its buildings "
	+ "glows in pale orange hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of morning cooking and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Aesthetics Row and its buildings "
	+ "gleams in the midday sun as people travel about the Aesthetics "
	+ "quarter filling the street with the murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Aesthetics Row catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as various citizens and maroon-robed monks make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Aesthetics Row amplifying the yellow glow of the street lamps.  "
	+ "A few people and maroon-robed monks still make their way about at this "
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

void create_palan_room()
{
	object gate;

    SHORT("On Aesthetics Row outside the southern city gates");
    LONG("@@get_time_desc@@");

	ITEM(({"gate", "gates", "s gate", "s gates", "southern gate",
		   "southern gates"}), "A large metal gate.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to your north.  Its massive width "
	+ "of large block panels of polished, translucent marble extends far to "
	+ "your west and east as it curves around the city in a "
	+ "perfect arc.  The wall is in good repair.\n");


/*	EXIT(MONKS + "w15", "east", 0, 0);
	EXIT(MONKS + "w16", "west", 0, 0);*/

    gate = clone_object(MONKS + "doors/city_sgate2.c");
	gate->move(TO);

        add_exit(HERBTRAIL_START,"clockwise",0);

	reset_palan_room();

}
