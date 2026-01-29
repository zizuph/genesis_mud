/* Mortis 12.2005 
 *
 */

#include "../local.h"
#include CLOCKH

inherit SHIP_BASE;

string
query_to_jail()
{
  return "southwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Landing street and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of wood, tar, and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The well-worn marble of Landing street and its buildings "
	+ "gleams in the midday sun as people travel to and from the piers "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Landing street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as merchants, sailors, and dockhands make their way about the street."
	+ road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Landing street amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Landing street outside the Guild of Mariners");
    LONG("@@get_time_desc@@To your southeast stands the venerable " +
       "hall of the Guild of Mariners, where prospective sailors " +
       "come to enlist their services, and old seadogs share " +
       "long tales of their adventures at sea.\n");

    add_item(({"hall","guild","guild of mariners","mariners guild"}),
       "To your southeast overlooking the harbour is the venerable " +
       "guild of Mariners.\n");
    add_item(({"harbour"}),
       "To your northwest you have a good view of the harbour of " +
       "Palanthas.\n");

    EXIT(SHIP + "s23", "northeast", 0, 0);
    EXIT("/d/Ansalon/guild/mariner/mariner_joinroom", 
        "southeast", "@@enter_guild", 0);
    EXIT(SHIP + "s11", "southwest", 0, 0);

}

int
enter_guild()
{
    write("You pass through the doors of the Guild of Mariners.\n");
    return 0;
/*
    if (TP->query_wiz_level())
    {
        write("You pass through the doors of the Guild of Mariners.\n");
        return 0;
    }

    write("The doors to the Guild of Mariners are currently closed " +
        "and barred.\n");
    return 1;
*/
}