/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_BASE;

string
query_to_jail()
{
  return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
    string road = " An archway leads south into the tower.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    desc += "You stand upon the great outdoor field of the Tower of Arms. The "
    + "Its green grass glows in " + one_of_list(({"pale purple ",
       "soft pink ", "pale orange ", "grey and pink "})) + "hues as the sun "
    + "peeks above the mountains in the east. The air is rich with the smells "
    + "of morning cooking and coffee borne on a cool, misty breeze." + road;
    break;

    case TOD_DAY:
    desc += "You stand upon the great outdoor field of the Tower of Arms. The "
    + "grass of the field is bright green in the sunlight pouring in. The "
    + "smell of fresh cut grass fills the air." + road;
    break;

    case TOD_TWILIGHT:
    desc += "You stand upon the great outdoor field of the Tower of Arms. The "
    + "Its green grass catches the last rays of the sun and seems "
    + "to glow of its own accord." + road;
    break;

    case TOD_NIGHT:
    desc += "You stand upon the great outdoor field of the Tower of Arms. The "
    + "moon and stars shed pale light across its translucent marble "
    + "amplifying the yellow glow of the street lamps." + road;
    break;

    default:
    break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("The great field of the Tower of Arms");
    LONG("@@get_time_desc@@");

    ITEM("grass", "The grass is rich green, freshly cut, and well tended. "
    + "It is often the surface for great tournaments and duels.\n");
    ITEM(({"arch", "archway"}), "The archway is marble and leads south "
    + "into the Tower of Arms. Chiseled above it is, \"Palanthas Guard "
    + "Tower\".\n");
    ITEM(({"wood", "woods", "north wood", "north woods", "thick wood",
           "thick woods"}), "A thick wood of trees surrounds you to the "
    + "north. These are the Gallant Field Woods and home to the "
    + "constabulary of Palanthas, the Palanthian Guard. Their Tower of "
    + "Arms rises ominously above you.\n");
    ITEM(({"short tower", "short marble tower", "marble tower"}), "A tower "
    + "of translucent, white marble rises at least forty feet into the air "
    + "to the south, higher than nearly all of the buildings in this "
    + "section of the merchant quarter. Chiseled into the marble above its "
    + "entryway is, \"Palanthas Guard Tower\".\n");

    EXIT(TOA + "toa04", "south", 0, 0);
}
