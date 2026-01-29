/* Mortis 11.2005
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

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
	string road = "  Old Circle runs northeast to the main city gates on "
	+ "Knight's High road and southwest along the curve of the city wall "
	+ "into the Aesthetics quarter.  The city wall towers above you to the "
	+ "southeast.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Old Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Old Circle and its buildings lights up "
	+ "in the midday sun as people and maroon robed aesthetics travel "
	+ "throughout the Aesthetics quarter filling the street with the "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The worn marble of Old Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers and maroon robed aesthetics make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Old Circle amplifying the yellow glow of the street lamps.  "
	+ "A few people and maroon robed aesthetics still make their way about at "
	+ "this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Old Circle southwest of the main city gates in the southeast "
	+ "of the city");
    LONG("@@get_time_desc@@");

	ITEM(({"gate", "gates", "southeastern gate", "southeastern gates",
		   "se gate", "se gates", "southeast gate", "southeast gates",
		   "main gates", "main city gates", "main gate", "main city gate"}),
	  "A large metal gate.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the southeast.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot dark grey rock which comprises "
	+ "its core.  The wall is in decent shape.\n");

	EXIT(NOBLE + "ser7", "northeast", 0, 0);
	EXIT(MONKS + "w12", "southwest", 0, 0);
	EXIT(MONKS + "a22", "northwest", 0, 0);

}
