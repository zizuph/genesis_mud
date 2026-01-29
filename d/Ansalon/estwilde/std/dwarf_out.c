#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AOR_FILE

#define CREATE "create_dwarf_room"
#define RESET "reset_dwarf_room"

string
tod_descr1()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "It is night in Iron Delving. ";
	break;
    case TOD_DAWN:
	str = "It is morning in Iron Delving. ";
	break;
    case TOD_DAY:
	str = "It is day in Iron Delving. ";
	break;
    case TOD_TWILIGHT:
	str = "It is evening in Iron Delving. ";
	break;
    }
    return str;
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
    call_other(TO, CREATE);

    remove_item("moons");
    remove_item("lunitari");
    remove_item("solinari");
    remove_item("sun");
}

/*
* This function is called from the main Krynn room.
*/
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}




