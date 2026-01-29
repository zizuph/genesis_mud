/*
 *    The base for the outer city outside rooms.
 *
 *    o_outer_city_base.c
 *    -------------------
 *
 *    Coded .........: 97/06/26
 *    By ............: Ashlar
 *
 *    Latest update .: 97/08/18
 *    By ............: Ashlar
 *
 *
 *    Notes ..:
 *
 *    Changes :
 *
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AOR_FILE

#include "clone_npc.c"

#define CREATE "create_neraka_room"
#define RESET  "reset_neraka_room"


string extra_long_descr = "";
string quarter = "";

string
query_quarter()
{
    return quarter;
}

void
set_quarter(string q)
{
    quarter = q;
}

string
season()
{
    string str;

    switch(GET_SEASON)
    {
        case SPRING:
            str = "It is spring here, but the bleak, barren "+
            "mountain landscape shows no sign of it. ";
        break;
        case SUMMER:
            str = "The warm summer winds blow gently against "+
            "your face, slightly lifting the bleakness of this "+
            "landscape. ";
        break;
        case AUTUMN:
            str = "The autumn chilly winds begin to pick up "+
            "here in the mountains. ";
        break;
        case WINTER:
            str = "Winter in the Khalkist mountains is very cold "+
            "and harsh, and Neraka is no exception. The cold winds "+
            "bite at your face. ";
        break;
    }

    return str;
}


string
tod_short_descr()
{
    string str;

    switch(GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
            str = "It is night in the city of Neraka. ";
        break;
        case TOD_DAWN:
            str = "It is morning in the city of Neraka. ";
        break;
        case TOD_DAY:
            str = "It is day in the city of Neraka. ";
        break;
        case TOD_TWILIGHT:
            str = "It is evening in the city of Neraka. ";
        break;
    }

    return str;
}


string
tod_long_descr()
{
    string str;

    switch(GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
            str = "Dark shadows creep out of the corners and alleyways. ";
        break;
        case EARLY_MORNING:
            str = "The light from the rising sun begins to diminish "+
            "the long, dark shadows of the night. ";
        break;
        case MORNING:
        case NOON:
        case AFTERNOON:
            str = "The cold, steel-grey sky does little to lift the "+
            "atmosphere of this bleak mountain city. ";
        break;
        case EVENING:
            str = "The sky darkens, and the shadows begin to grow "+
            "longer as the night approaches. ";
        break;
    }

    return str;
}


void
set_extra_long(string str)
{
    extra_long_descr = str;
}


string
long_descr()
{
    string str;

    str = tod_short_descr() + tod_long_descr()
      + extra_long_descr + " " + season() + "\n";

    return str;
}

/* Common add_items */

void add_item_dirtroad()
{
    add_item(({"roads","road","dirt road"}),
        "There are puddles of mud in some spots, " +
        "while rocks and other debris are in others. The road looks old " +
        "and well-used.\n");
    add_item(({"puddles","puddles of mud","mud"}),
        "Some large, some small, these muddy puddles " +
        "form from the occasional rain that falls here.\n");
    add_item("dirt","Dirt is the foundation of the road, and it's " +
        "everywhere.\n");
}

void add_item_sidewalks()
{
    add_item(({"wooden sidewalks","sidewalks"}), "The sidewalks are " +
        "constructed of wooden boards, raised a few decimeters above " +
        "the ground.\n");
    add_item(({"boards","wooden boards","board","wooden board"}),
        "The boards have a weathered, well-used look that suggests they " +
        "have been used for quite some time.\n");
}

void add_item_camp()
{
    add_item(({"camp", "army camp" }),
        "The camp consists mostly of canvas tents erected in irregular " +
        "patterns, with dirt roads winding between the tents.\n");
    add_item(({"tents","canvas tents"}),
        "The tents are made of black canvas, and looks big enough to " +
        "house four or five soldiers.\n");
    add_item("tent","The tent is made of black canvas, and looks big " +
        "enough to house four or five soldiers.\n");
}

void add_item_buildings()
{
    add_item(({"building","buildings","shacks"}),
        "The buildings are haphazard " +
        "shacks thrown together from whatever building material that " +
        "was available at the time.\n");
}

void add_item_market(string what)
{
    add_item(({what,"market " + what}),
        "The " + what + " is rather small and paved with stone in most " +
        "places. There are some small shops and merchant stalls " +
        "surrounding the " + what + ". Various merchants and troops wander " +
        "around, perusing the displays.\n");
    add_item("merchants","The area is crowded with merchants of all " +
        "kinds. People crowd around the stalls and shops, looking and " +
        "buying.\n");
    add_item("shops","The shops line the market "+what+", with wooden " +
        "sidewalks in front of them.\n");
    add_item("troops","The troops seem to be " + capitalize(query_quarter()) +
        " Dragonarmy troops, judging from their attire.\n");
    add_item("stalls","The many different stalls offer delights of " +
        "the mind or body for those who are not so particular.\n");
}

void
set_neraka_hide(mixed hide)
{
    if (intp(hide))
        add_prop(ROOM_I_HIDE, hide);
}

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */

nomask public void
create_krynn_room()
{
    add_item("mountains","The great Khalkis mountains surround this "+
    "valley on all sides. They stretch into the pale grey sky, twisting "+
    "and turning like the spine of some demon.\n");

    set_long("@@long_descr");

    call_other(TO, CREATE);
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}
