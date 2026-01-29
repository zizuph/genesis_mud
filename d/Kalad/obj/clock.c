/*
   /d/Kalad/lib/clock.c

   Kalad's clock, rings the bell every hour.
   By Ashbless w/advice from Olorin, Cedric, and Ellesar.

   Code updated by Fysix, Oct 1997
 */
#pragma strict_types
#pragma save_binary
#pragma no_inherit
#pragma no_clone
#pragma no_shadow

#include "/d/Kalad/sys/paths.h"

#define RAIN_INTERVAL 1080.0
#define HOUR_INTERVAL 600.0

static int  Time,
Rain,
Initialized = 0;

// --- Prototypes ---
public void new_rain();
public void new_hour();
public void ring_bell();
public int  query_in_kalad(object player);

/* Function name: new_rain
 * Description:   
 */
public void
new_rain()
{
    set_alarm(RAIN_INTERVAL, 0.0, new_rain);
    Rain = random(3);
}

/* Function name: new_hour
 * Description:   New hour.
 */
public void
new_hour()
{
    set_alarm(HOUR_INTERVAL, 0.0, new_hour);

    Time += 1;
    if (Time >= 25)
	Time = 1;

    ring_bell();
}

// Initialize the clock object
public void
create()
{
    if (Initialized)
	return;

    Time = 7;

    // Start the alarm sequence
    set_alarm(5.0, 0.0, new_hour);
    set_alarm(2.0, 0.0, new_rain);

    Initialized = 1;
}

/* Function name: query_hour
 * Description:   What is the time?
 * Returns:       int 1..12
 */
public int
query_hour()
{
    return (Time > 12) ? Time - 12 : Time;
}

/* Function name: ring_bell_to_player
 * Description:   Ring bell to player in Kalad.
 * Arguments:     object player
 *                int hour
 */
public void
ring_bell_to_player(object player, int hour)
{
    switch (environment(player)->query_hear_bell())
    {
    case 1 :
	tell_object(player,
	  "You can faintly hear a bell toll " +
	  hour + " time" + (hour != 1 ? "s.\n" : ".\n"));
	break;
    case 2 :
	tell_object(player,
	  "You can hear a bell toll " +
	  hour + " time" + (hour != 1 ? "s.\n" : ".\n"));
	break;
    case 3 :
	tell_object(player,
	  "From nearby, you hear a bell clang loudly " +
	  hour + " time" + (hour != 1 ? "s.\n" : ".\n"));
	break;
    case 4 :
	tell_object(player,
	  "The deafening sound of a bell ringing " +
	  hour + " time" + (hour != 1 ? "s, " : ", ") + 
	  "nearly knocks\n you to your feet and " +
	  "leaves your head ringing.\n");
	break;
    }
}

/* Function name: ring_bell
 * Description:   Ring the bell in Kalad.
 */
public void
ring_bell()
{
    int hour;
    object *player;

    hour = query_hour();

    // Filter all players who are in kalad
    player = filter(filter(users(), &query_in_kalad()),
      &->query_hear_bell() @ &environment());

    map(player, &ring_bell_to_player(, hour));
}

/* Function name: query_time
 * Description:   What is the time in Kalad?
 * Returns:       int time in hours 1..24
 */
public int
query_time()
{
    return Time;
}

/* Function name: query_in_kalad
 * Description:   Is a player in Kalad?
 * Arguments:     object player
 * Returns:       int 1 if he is in Kalad.
 */
public int
query_in_kalad(object player)
{
    if (!environment(player))
	return 0;

    return environment(player)->query_domain() == DOMAIN;
}

/* Function name: query_raining
 * Description:   Is it raining?
 * Returns:       int
 */
public int
query_raining()
{
    return Rain;
}

/* Function name: query_day
 * Description:   Is it day in here?
 * Returns:       int 1 if day, 0 if night
 */
public int
query_day()
{
    return (Time > 6 && Time < 22) ? 1 : 0;
}

/* Function name: query_alarms
 * Description:   What alarms are running? Used by Dump alarms.
 * Returns:       mixed
 */
public mixed
query_alarms()
{
    return get_all_alarms();
}
