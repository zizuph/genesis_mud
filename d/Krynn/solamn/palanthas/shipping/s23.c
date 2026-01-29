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
	string road = " To your north you can make your way to the dry docks " +
        "of Palanthas, where shipwrights create the great vessels that " +
        "sail the seas of Ansalon.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Landing street and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains. "
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
	+ "of Landing street amplifying the yellow glow of the street lamps. "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

int
enter_dock()
{
    write("You walk towards the dry dock of Palanthas.\n");
    return 0;
/*
    if (TP->query_wiz_level())
    {
        write("You walk towards the dry dock of Palanthas.\n");
        return 0;
    }
    write("The dry docks of Palanthas are currently closed for repairs.\n");
    return 1;
*/
}

void
create_palan_room()
{
    SHORT("On Landing street before the dry docks of Palanthas");
    LONG("@@get_time_desc@@");

    add_item(({"dry dock", "dry docks"}),
        "To your north are the dry docks of Palanthas, where ships are " +
        "built and repaired by master shipwrights.\n");

    EXIT(SHIP + "s24", "northeast", 0, 0);
    EXIT(SHIP + "s22", "southwest", 0, 0);
    EXIT("/d/Ansalon/guild/mariner/dry_dock", "north", "@@enter_dock", 0);

}