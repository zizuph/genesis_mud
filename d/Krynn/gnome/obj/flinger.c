inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include "../local.h"
 
#include <stdproperties.h> 	/* All prop definitions */
#include <cmdparse.h>		/* The FIND_STR_IN_OBJECT macro */
#include <macros.h>		/* QCTNAME and QTNAME macro */

create_object()
{
    set_name("gnomeflinger");
    add_name("catapult");
    set_short("steam-powered gnomeflinger");
    set_long(BS("Stairs being the uninteresting and primitive devices " +
	"they are, gnomes have perfected the use of catapults, or " +
	"'gnomeflingers' as a method of moving from one floor in their " +
	"caverns to another. This is a new prototype being tested. " +
	"Just say or shout which floor (of 3) you want to go to. The " +
	"foreman will take care of the rest. Enjoy your flight...", 70));
    add_prop(OBJ_I_LIGHT, 0);
    add_prop(OBJ_I_WEIGHT, 7000000);
    add_prop(OBJ_I_VOLUME, 10000000);
    add_prop(OBJ_I_VALUE, 0);
}
 
fling(object who, string floor)
{
    int destination;

    destination = 0;
    if ((floor == "first") || (floor == "1\n"))
	destination = 1;
    else if ((floor == "second") || (floor == "2\n"))
	destination = 2;
    else if ((floor == "third") || (floor == "3\n"))
	destination = 3;

    if (!destination)
    {
    	//who->catch_msg("Valid formats are: first/second/third floor, or floor 1/2/3.\n");
    	return 0;
    }

    who->catch_msg("You are ushered into the 'PerfectlySafeAndComfortable" +
		   "DepartureSeatWhichIHaveJustMadeSomeModificationsToAndI" +
		   "HopeYouEnjoyItItsReallyQuiteMarvelous...\n");
    who->move_living("up onto the gnomeflinger", TDIR + "flingroom");
    tell_room(E(who),QCTNAME(who) + " climbs up onto the gnomeflinger.",({who}));
    set_alarm(2.0,0.0,"commence", who, destination);
    return 1;
}

commence(object who, int num)
{
    call_other(TDIR + "flingroom", "phase1", who, num);
}

