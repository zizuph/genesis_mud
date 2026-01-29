/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_BASE;

string
query_to_jail()
{
    return "west";
}

nomask public string
get_time_desc()
{
    string desc = "";
    string road = " A massive marble stairway rises to the east leading into "
    + "the tower.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    desc += "You stand within the great pillared entranceway of the Tower of "
    + "Arms. Its clean marble glows in " + one_of_list(({"pale purple ",
       "soft pink ", "pale orange ", "grey and pink "})) + "hues as the sun "
    + "peeks above the mountains in the east. The air is rich with the smells "
    + "of morning cooking and coffee borne on a cool, misty breeze." + road;
    break;

    case TOD_DAY:
    desc += "You stand within the great pillared entranceway of the Tower of "
    + "Arms. Its marble is polished and gleaming in the sunlight pouring in "
    + "from the west. The smells of oiled leather and metal fill the air."
    + road;
    break;

    case TOD_TWILIGHT:
    desc += "You stand within the great pillared entranceway of the Tower of "
    + "Arms. Its translucent marble catches the last rays of the sun and seems "
    + "to glow of its own accord." + road;
    break;

    case TOD_NIGHT:
    desc += "You stand within the great pillared entranceway of the Tower of "
    + "Arms. The moon and stars shed pale light across its translucent marble "
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
    SHORT("The great entrance of the Tower of Arms");
    LONG("@@get_time_desc@@");

    ITEM(({"wood", "woods", "north wood", "north woods", "thick wood",
           "thick woods"}), "A thick wood of trees stands to your "
    + "north. They are the Gallant Field Woods and home to the "
    + "constabulary of Palanthas, the Palanthian Guard. Their Tower of "
    + "Arms rises ominously above you.\n");
    ITEM(({"short tower", "short marble tower", "marble tower"}), "A tower "
    + "of translucent, white marble rises at least forty feet into the air "
    + "to the northwest, higher than nearly all of the buildings in this "
    + "section of the merchant quarter. Chiseled into the marble above its "
    + "entryway is, \"Palanthas Guard Tower\".\n");
    ITEM(({"ceiling", "grill", "portcullis"}), "Set into the ceiling is an "
    + "iron grill through which the guards above may attack invaders with "
    + "impunity. The spear like tips of a raised iron portcullis protrude "
    + "above the landing at the top of the great marble stairs east.\n");
    ITEM("floor", "It is smoothly polished, translucent white marble.\n");
    ITEM(({"stair", "stairs", "flight", "flights", "flight of stairs",
           "stairway"}), "A massive stairway rises to the east. The steps "
    + "are worn but still nearly perfect and smooth. They have recently "
    + "been polished and gleam beautifully.\n");

    EXIT(TOA + "toa02", "east", 0, 0);
    EXIT(MERCH + "m05", "west", 0, 0);

}
