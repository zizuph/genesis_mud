#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit         AOR_FILE

#define CREATE "create_balifor_room"
#define RESET "reset_balifor_room"

string
tod_descr1()
{
    string          str;
    switch (GET_TIMEOFDAY) {
    case TOD_NIGHT:
	str = "It is night on the coast of Balifor. ";
	break;
    case TOD_DAWN:
	str = "It is morning on the coast of Balifor. ";
	break;
    case TOD_DAY:
	str = "It is day on the coast of Balifor. ";
	break;
    case TOD_TWILIGHT:
	str = "It is evening on the coast of Balifor. ";
	break;
    }
    return str;
}

string
wharf()
{
    return "The wooden wharf creaks, as the current of the Bay causes it " +
    "to sway slightly.\n";
}
string
break_water()
{
    return "The Breakwater is a stone wall built around the harbor " +
    "that extends down to the sea floor to protect the Port " +
    "City of Balifor from the tide of the Bay. There is a " +
    "wall on both the southern and northern sides of the " +
    "city. They angle towards each other, creating the only " +
    "entrance to the Harbor.\n";
}

string
steppes()
{
    return "Barren rolling steppes rise behind the sheltered Cove " +
    "Port Balifor.\n";
}

string
season_descr()
{
    string          str;
    switch (GET_SEASON) {
    case SPRING:
	str = "A cool spring breeze sweeps off the Bay " +
	"of Balifor. ";
	break;
    case SUMMER:
	str = "A cool " +
	"but humid wind sweeps in from the Bay. ";
	break;
    case AUTUMN:
	str = "A chilly wind rolls in from the Bay and " +
	"a light rain drizzles. ";
	break;
    case WINTER:
	str = "An icy wind comes rolling off the Bay, and " +
	"the sky is " +
	"overcast with storm clouds. ";
	break;
    }
    return str;
}


/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks weather or not
 * the room should be reseted. The function returns TRUE if there should be a
 * reset.
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
    call_other(TO, CREATE);

    set_tell_time(160);
    add_tell("A cool breeze comes off the Bay of Balifor and sweeps "
      + "up the streets of the city.\n");
    start_room_tells();
}


nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}
