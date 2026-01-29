/* Mortis 11.2005
 * Park smells?
 */

#include "../local.h"
#include CLOCKH

inherit MONKS_BASE;

object wguard;

string
query_to_jail()
{
  return "northeast";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  This side street is within sight of the main city gates "
	+ "to the southeast and curves northeast towards its intersection with "
	+ "Knight's High road and southeast towards Old Circle and the city "
	+ "wall.  Through a few buildings to your west a worn, marble path leads "
	+ "to a water spraying fountain surrounded by bushes.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The translucent marble of this side street "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The translucent marble of this side street "
	+ "appears mostly white in the midday sun as people travel along the way "
	+ "filling the street with the murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of this side street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as citizens and maroon robed aesthetics make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of this side street amplifying the yellow glow of the street lamps.  "
	+ "A few people and maroon robed aesthetics still make their way about at "
	+ "this hour." + road;
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
		wguard->set_monster_home(MONKS + "a22");
		wguard->set_restrain_path(MONKS);
		wguard->set_random_move(55);
		wguard->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("Southwest of Knight's High Road by the traveller's fountain");
    LONG("@@get_time_desc@@");

	ITEM(({"gate", "gates", "southeastern gate", "southeastern gates",
		   "se gate", "se gates", "southeast gate", "southeast gates",
		   "main city gate", "main city gates", "city gate", "city gates",
		   "main gate", "main gates"}), "A large metal gate.\n");
	ITEM("fountain", "To the west, a worn, marble path leads to the "
	+ "traveller's fountain, an area of respit for visitors to the city as "
	+ "well as those setting off along the southeast road to the High "
	+ "Clerist's tower and Solamnia.\n");
	ITEM(({"bush", "bushes"}), "Low, green bushes surround a grassy area "
	+ "with a fountain to your west.\n");

	EXIT(NOBLE + "ser6", "northeast", 0, 0);
	EXIT(MONKS + "w11", "southeast", 0, 0);
	EXIT(MONKS + "apark", "west", "@@park_closed", 0);

	reset_palan_room();
}

int
park_closed()
{
	write("Park not yet open.\n");
	return 1;
}
