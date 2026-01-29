/*
 * i_room_base.c
 *
 */
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Inherit the Ansalon room */
inherit AR_FILE

/*
 * Change these two XXX to the proper name
 */
#define CREATE "create_kalaman_room"
#define RESET "reset_kalaman_room"

string
query_house_long(int floor)
{
   switch ( floor )
   {
     case HOUSE_LIVING:
       return "You stand in one of the houses in the poor districts of " +
         "Kalaman. Nothing in this house could hint that you are in "    +
         "one of the riches and busies ports of Ansalon. The furniture " +
         "is sparse and what does exist is of inferior quality and "     +
         "most of them are homemade. There is a staircase that leads "   +
         "to the upper levels of the house and a simple wooden door "    +
         "that leads to the kitchen area. Next to the kitchen door "     +
         "stands a wooden cupboard. A huge homemade dirty rug covers "   +
         "the simple wooden plank that make up the floor of this type "  +
         "of house. On the wall that faces the street a large bookcase " +
         "stands and beside it is a small window that gives a clear "    +
         "view of the street outside.";
       break;
     case HOUSE_HALLWAY:
       return "You stand in a simple hallway in one of the houses in "   +
         "the poor district of Kalaman.";
     case HOUSE_KITCHEN:
       return "You stand just past the doorway inside the kitchen.";
     default:
       return "This is a simple room inside one of the commoners house " +
         "in the city of Kalaman in Ansalon.";
  }
}

string
query_house_short(int floor)
{
  switch ( floor )
  {
     case HOUSE_LIVING:
       return "The livingroom";
       break;
     case HOUSE_HALLWAY:
       return "The hallway";
       break;
     case HOUSE_KITCHEN:
       return "In the kitchen";
       break;
     default:
       return "A room inside the house";
  }
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
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}
