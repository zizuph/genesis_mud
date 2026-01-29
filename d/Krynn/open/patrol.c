/*
 * patrol.c
 * 
 * 950424 by Rastlin
 *
 * Updated 16.12.1998 by Milan
 * Updated 10.5.1999 by Milan
 * It is not possible to use string VBFC anymore. Only functions are
 * accepted as VBFC. Fixed problem with double call to VBFC.
 * (see header of function set_patrol_path() )
 */

static int gPathpos = -1, gMovetime = 15;
static mixed gPath = ({ });
static int gAlarm_patrol;
static int gLoop = 1;

/*
 * Function:	set_patrol_path
 * Arguments:	path - An array of string and integers.
 * Description:	Set the command path the NPC should follow.
 *		The elements in the array should be
 *		 string   - commands to be executed
 *		 integer  - delay value to next command
 *		 function - will be executed. If result is string it is used as
 *			command. Integer result is used as delay value. Other
 *			results are ignored.
 *		 other types are ignored.
 * Example:	set_patrol_path(({"n", "unlock door", 3, "open door", "n",
 *			"close door", 4, "lock door", "n", &check_endpath() }));
 * 		This means that it will take 3 seconds from that the door
 *		has been unlocked until the NPC opens the door and that it will
 *		take 4 seconds until the NPC locks it after that it has been closed.
 *		At the end we call function check_endpath() that can for example
 *		make sure our NPC arrived at desired destination.
 */
public void
set_patrol_path(mixed path)
{
    gPath = path;
}

/*
 * Function:	query_patrol_path
 * Description:	Return the command sequence
 * Returns:	mixed
 */
public mixed
query_patrol_path() { return gPath; }

/*
 * Function:	patrol_heartbeat
 * Description:	This functions executes patrol commands.
 */
static void
patrol_heartbeat()
{
    int time, i;
    mixed cmdres;

    if (!sizeof(gPath))
	return; /* no commands to execute */

    /* wait with patrol, fight first */
    if (this_object()->query_attack())
    {
	time = gMovetime + random(10);
	gAlarm_patrol = set_alarm(itof(time), 0.0, patrol_heartbeat);
	return;
    }

    /* move on with patrol */
    if (++gPathpos >= sizeof(gPath))
    {
	gPathpos = 0;
	if (!gLoop)
	    return; /* we have reached the end */
    }

    cmdres = gPath[gPathpos];
    
    /* resolve function VBFC first */
    if (functionp(cmdres))
    {
	cmdres = this_object()->check_call(cmdres);
    }

    /* integer meand delay */
    if (intp(cmdres))
    {
	gAlarm_patrol = set_alarm(itof(cmdres), 0.0, patrol_heartbeat);
	return;
    }

    /* string - execute command */
    if (stringp(cmdres))
    {
	command(cmdres);
    
	/* check the next in order - if integer use it as delay */
	if ((i = gPathpos + 1) >= sizeof(gPath))
	{
	    i = 0;
	    if (!gLoop)
		return; /* again at end */
	}
	if (intp(cmdres = gPath[i]))
	{
	    gPathpos = i;
	    gAlarm_patrol = set_alarm(itof(cmdres), 0.0, patrol_heartbeat);
	    return;
	}
    }
    /* O.K. use the standard delay */
    time = gMovetime + random(10);
    gAlarm_patrol = set_alarm(itof(time), 0.0, patrol_heartbeat);
    return;
}

/*
 * Function:	set_patrol_loop
 * Description:	Enable looping of the patrol path again. This is probably
 *              rarely used, since you have to stop the loop first :)
 */
public void
set_patrol_loop()
{
    gLoop = 1;
}

/*
 * Function:	disable_patrol_loop
 * Description:	Disable the looping of the patrol path. The patrol will stop
 *              when it reaches the end of the path. You can call this either
 *              from the create_* function to make it use the patrol just once
 *              and then stop, or call it at any time later on and the patrol
 *              will stop when it next reaches the end.
 */
public void
disable_patrol_loop()
{
    gLoop = 0;
}

/*
 * Function:	set_patrol_time
 * Arguments:	i - The delay in seconds
 * Description: Set the number of seconds it will delay between two moves.
 *		The real delay number will be i + random(10) seconds.
 */
public void
set_patrol_time(int i)
{
    gMovetime = i;
}

/*
 * Function:	query_patrol_time
 * Description: Return the delay time in seconds.
 * Returns:	An integer.
 */
public int
query_patrol_time() { return gMovetime; }

/*
 * Function:	stop_patrol
 * Description:	This will stop the patrol until it is started again.
 */
public void
stop_patrol()
{
    if (gAlarm_patrol)
	remove_alarm(gAlarm_patrol);
}

/*
 * Function:	start_patrol
 * Description: This will start the patroling
 */
public void
start_patrol()
{
    stop_patrol();
    gAlarm_patrol = set_alarm(itof(gMovetime + random(10)), 0.0, patrol_heartbeat);
}




