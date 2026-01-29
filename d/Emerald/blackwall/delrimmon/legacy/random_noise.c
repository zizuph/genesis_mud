/*
 * /d/Gondor/common/lib/random_noise.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * Inherit this to provide random "atmospheric" messages to a room:
 *	A sudden gust of wind swirls the dust around your feet.
 *	An owl hoots softly in the distance.
 *	Far overhead, a hawk circles silently.
 *	 ...
 *
 * In your init() routine, you must call
 *	init_random_noise();
 *  
 * You must provide the code for the routine 
 *	public int
 *	random_noise()
 * It should write the message (if any) and return 1 if the messages
 * should continue, or 0 if there should be no more messages.
 *
 * Optionally, you may call:
 *	public void
 *	set_noise_interval(int interval, int variation)
 * where interval is the alarm interval between messages, and
 * variation is a random interval to be added to the minimum -- that is,
 * the message alarms will be set for itof(interval + random(variation)).
 * the default interval is 120 and the default variation is 60.
 *
 * see /d/Gondor/common/doc/examples/room_noise.c for a simple example.
 *
 */

#pragma strict_types

#include <filter_funs.h>


#define		DEFAULT_INTERVAL	120
#define		MIN_INTERVAL	 	  5

static int	Noise_interval = DEFAULT_INTERVAL,
		Noise_variation = (DEFAULT_INTERVAL / 2),
		Noise_alarm;

public void		init_random_noise();
public int		random_noise();
public void		make_noise();
public varargs void	set_noise_interval(int interval, int variation);

/*
 * Function name:	random_noise
 * Description	:	write your messages here
 * Returns	:	int -- 1 if message alarms should continue,
 *			       0 if not.
 */
public int
random_noise()
{
    return 0;
} /* random_noise */


/*
 * Function name:	init_random_noise
 * Description	:	if entering player is interactive, set alarm
 */
public void
init_random_noise()
{
    int	i;

    if (Noise_interval &&
	!Noise_alarm &&
	interactive(this_player()))
    {
	if (Noise_variation > 0)
	{
	    i = Noise_interval + random(Noise_variation);
	}
	else
	{
	    i = Noise_interval;
	}
	Noise_alarm = set_alarm(itof(i), 0.0, make_noise);
    }
} /* init_random_noise */


/*
 * Function name:	set_noise_interval
 * Description	:	set the interval and variation between alarms
 * Arguments	:	int interval -- the minimum interval between
 *				noise alarms
 *			int variation -- (optional) a random variation
 *				to be added to the minimum interval
 * The time between alarms will be:
 *	interval + random(variation)
 * If interval is <= 0, the noise alarms will be turned off.
 * If variation is not provided, or if it is < 0, a variation of
 * (interval/2) will be used.
 */
public varargs void
set_noise_interval(int interval, int variation = -1)
{
    if (interval <= 0)
    {
	if (Noise_alarm)
	{
	    remove_alarm(Noise_alarm);
	    Noise_alarm = 0;
	}
	Noise_interval = Noise_variation = 0;
    }
    else
    {
	if (interval < MIN_INTERVAL)
	{
	    interval = MIN_INTERVAL;
	}
	Noise_interval = interval;
	if (variation >= 0)
	{
	    Noise_variation = variation;
	}
	else
	{
	    Noise_variation = (interval / 2);
	}
    }
} /* set_noise_interval */


/*
 * Function name:	make_noise
 * Description	:	noise alarm has fired -- if there are any
 *			interactives here, call random_noise() to
 *			issue a message and, if return from random_noise()
 *			is non-zero, reschedule the alarm.
 */
public void
make_noise()
{
    int	i;
    if (sizeof(FILTER_PLAYERS(all_inventory(this_object()))) &&
	random_noise())
    {
	if (Noise_variation > 0)
	{
	    i = Noise_interval + random(Noise_variation);
	}
	else
	{
	    i = Noise_interval;
	}
	Noise_alarm = set_alarm(itof(i), 0.0, make_noise);
    }
    else
    {
	Noise_alarm = 0;
    }
} /* make_noise */

