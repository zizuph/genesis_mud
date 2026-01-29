/**********************************************************************
 * - fireplace1.c                                                    - *
 * -                                                                - *
 * - Created by Damaris@Genesis 08/2006                             - *
 **********************************************************************/

#pragma strict_types
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Raumdor/sys/basic.h"

int
stoke_fire(string str)
{
	if((str == "the fire") || (str == "fire") || (str == "logs") || (str == "the logs"))
	{
		write("You request for the attendent to stoke up the "+
		"fire.\n"+
		"The attendent takes the poker and stokes up the fire "+
		"in the fireplace."+
		"\nThe fire burns more brightly.\n");
		/* This what others in room see. */
		say(QCTNAME(TP)+" makes a request of the attendent.\n"+
		"The attendent takes the poker and stokes up the fire "+
		"in the fireplace."+
		"\nThe fire burns more brightly.\n");
		return 1;
	}
	else
	{
		notify_fail("Stoke what? Stoke the fire perhaps?\n");
		return 0;
	}

}
int
ask_attend(string str)
{
	if((str == "stoke fire") || (str == "stoke logs") || (str == "attendent stoke fire") || (str == "stoke the fire") || (str == "attendent stoke logs") || (str == "stoke the logs"))
	{
		write("You request for the attendent to stoke up "+
		"the fire.\n"+
		"The attendent takes the poker and stokes up the fire "+
		"in the fireplace."+
		"\nThe fire burns more brightly.\n");
		/* This what others in room see. */
		say(QCTNAME(TP)+" makes a request of the attendent.\n"+
		"The attendent takes the poker and stokes up the fire "+
		"in the fireplace."+
		"\nThe fire burns more brightly.\n");
		return 1;
	}
	if((str == "log on fire") || (str == "put log") || (str == "attendent more logs") || (str == "log on fire") || (str == "attendent logs") || (str == "put logs"))
	{
		write("You request for the attendent to put a log "+
		"on the fire.\n"+
		"The attendent puts another log on the fire "+
		"in the fireplace."+
		"\nThe fire burns more brightly.\n");
		/* This what others in room see. */
		say(QCTNAME(TP)+" make a request of the attendent.\n"+
		"The attendent puts another log the fire "+
		"in the fireplace."+
		"\nThe fire burns more brightly.\n");
		return 1;
	}
	else
	{
		notify_fail("What do you want the attendent to do? Put log on fire or stoke fire?\n");
		return 0;
	}

}

int
log_fire(string str)
{
	if((str == "the fire") || (str == "fire") || (str == "logs") || (str == "the logs") || (str == "log on fire") ||(str == "logs on fire"))
	{
		write("You request for the attendent to put a log "+
		"on the fire.\n"+
		"The attendent puts another log on the fire "+
		"in the fireplace."+
		"\nThe fire burns more brightly.\n");
		/* This what others in room see. */
		say(QCTNAME(TP)+" make a request of the attendent.\n"+
		"The attendent puts another log the fire "+
		"in the fireplace."+
		"\nThe fire burns more brightly.\n");
		return 1;
	}
	else
	{
		notify_fail("Put what? Put log on fire perhaps?\n");
		return 0;
	}

}

int
extinguish_fire(string str)
{
	if((str == "the fire") || (str == "fire"))
	{
		write("You try to extinguish the fire in the fireplace "+
		"but fail.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" tries to extinguish the fire in the "+
		"fireplace but fails.\n");
		return 1;
	}
	else
	{
		notify_fail("Extinguish what? Extinguish the fire "+
		"perhaps?\n");
		return 0;
	}
}

public void
init_fire()
{
	add_action(stoke_fire, "stoke");
	add_action(log_fire, "put");
	add_action(extinguish_fire, "extinguish");
	add_action(ask_attend, "request");
}
