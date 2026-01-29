/*
 *    The base for the inner city outside rooms.
 *
 *    o_inner_city_base.c
 *    -------------------
 *
 *    Coded .........: 97/07/04
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

void
add_item_templesquare()
{
    add_item(({"square","temple square"}),
      "The Temple Square is a large open area surrounding the Temple of " +
      "Takhisis. The square is paved with large black stones, similar " +
      "in texture to the temple itself.\n");
    add_item(({"stones","black stones"}),"The black stones that make " +
      "up the square are similar in texture to the Temple of " +
      "Takhisis. @@stones_al_desc@@\n");
    remove_item(({"temple","temple of takhisis"}));
    add_item(({"temple","temple of takhisis"}),
      "The twisted and deformed Temple of Takhisis rises from the center " +
      "of the Temple Square like a dark claw. An aura of evil surrounds " +
      "the hideous temple.\n");
    add_item(({"aura","aura of evil"}),"You cannot see it, but you feel it " +
      "in the marrow of your bones. @@aura_al_desc@@\n");
}

string
aura_al_desc()
{
    if (TP->query_alignment() > 400)
	return "You are repulsed by the malignant evil.";
    else if (TP->query_alignment() < 400)
	return "The malignant evil resonates in your soul, giving you " +
	"a sense of belonging here.";
    else
	return "";
}

void
add_item_citywalls()
{
    add_item(({"walls","wall","city walls","city wall"}),
      "The city walls loom large on both sides of the street.\n");
}

/* street1 - description of the main street (The Queen's Way) */
void
add_item_street1()
{
    add_item(({"street","main street","queen's way"}),
      "The street is evenly paved with black stones, similar in " +
      "texture to the Temple of Takhisis that looms high in the " +
      "very center of the city.\n");
    add_item(({"stones","black stones"}),"The black stones that make " +
      "up the streets are similar in texture to the Temple of " +
      "Takhisis. @@stones_al_desc@@\n");
}

string
stones_al_desc()
{
    if (TP->query_alignment() > 200)
	return "The stones are slick and treacherous to walk.";
    else if (TP->query_alignment() < 200)
	return "The stones are rough, but easy to walk on.";
    else
	return "";
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
    add_item(({"temple","temple of takhisis"}),
      "The dark temple of Takhisis looms in the center of the city, " +
      "surrounded by an aura of evil. Black, spiky protrusions on " +
      "the temple gives it an appearance of a cancerous growth rather " +
      "than a thing built by men.\n");

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
