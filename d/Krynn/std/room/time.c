/*
 * The time function used by the command 'time'
 */

#include "/d/Krynn/common/clock/clock.h"

public int
check_time()
{
    if (query_prop(ROOM_I_INSIDE))
    {
	if (query_prop(ROOM_I_NO_TIME))
	  write("You have no way to even estimate the time of the day here.\n");
	else
	  write(GET_TIME_INSIDE);
    }
    else
    {
        if(query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
        {
            write("You guess it is " +GET_TIME_STRING+ " by studying the " +
                "light streaming through the water, however cannot estimate " +
                "the time more precisely.\n");
	    tell_room(environment(this_player()), QCTNAME(this_player()) + 
		  " studies the light coming through the water from above, " +
                  "trying to estimate the time of the day.\n", this_player());
        }
        else
        {
            write(GET_TIME_OUTSIDE);
	    tell_room(environment(this_player()), QCTNAME(this_player()) + 
		  " studies the sky, trying to estimate the time of " +
		  "the day.\n", this_player());
        }
    }
    return 1;
}
