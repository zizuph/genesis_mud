/* The center of the city of Palanthas.
   Mortis 07.2005 */

#pragma strict_types

#include "../local.h"
#include CLOCKH

inherit CITY_BASE;

string get_time_desc()
{
    string desc = "";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of the streets and buildings of the Palatial "
	+ "Plaza glows in pale purple hues as the sun peeks above the mountains. "
	+ "The air is rich with the smells of morning cooking and coffee borne "
	+ "on a cool, misty breeze from the bay.\n";
	break;
    case TOD_DAY:
	desc += "The pristine marble of the streets and buildings of the Palatial "
	+ "Plaza gleams in the midday sun as merchants, bureaucrats, "
	+ "and shoppers fill the plaza with the noisy murmurings of their "
	+ "daily business.\n";
	break;
    case TOD_TWILIGHT:
	desc += "The translucent marble of the streets and buildings of the Palatial "
	+ "Plaza catches the last rays of the sun appearing to glow of its own accord "
	+ "as the evening crowd comes out to walk and dine mingling with the "
	+ "remaining shoppers and merchants.\n";
	break;
    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of the streets and buildings of the Palatial Plaza amplifying the "
	+ "yellow glow of the street lamps.  Merchants and revelers still make "
	+ "their way about at this hour.\n";
	break;
    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    set_short("The Palatial Plaza of Palanthas");
    set_long("@@get_time_desc@@");
}
