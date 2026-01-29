
/* Mortis 07.2005 */
/* Vitwitch 08/2020 included exit to HERBTRAIL */ 

#include "../local.h"
#include CLOCKH

#define VINGAARD_HERBTRAIL_NTH "/d/Krynn/solamn/vin_herbtr/vinherbtr1"

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "west";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the west is city of Palanthas.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Nobles' Way "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Nobles' Way "
	+ "gleams in the midday sun." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Nobles' Way "
	+ "catches the last rays of the sun appearing to glow of its own "
	+ "accord." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Nobles' Way."
	+ road;
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

    SHORT("On the east road outside Palanthas");
    LONG("@@get_time_desc@@");

    gate = clone_object(NOBLE_DOOR + "city_egate2.c");
    gate->move(TO);

    add_exit(VINGAARD_HERBTRAIL_NTH,"upward",0,5);

    reset_palan_room();

}
