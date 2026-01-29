/*
 *    The outside base file for the city of Neraka.
 *
 *    o_room_base.c
 *    -------------
 *
 *    Coded .........: 96/11/18
 *    By ............: Sarr
 *
 *    Latest update .: 97/06/13
 *    By ............: Ashlar
 *
 *
 *    Notes ..:
 *
 *    Changes : Added a set_neraka_hide() function.
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

#define CREATE "create_neraka_room"
#define RESET  "reset_neraka_room"


string extra_long_descr = "";


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
