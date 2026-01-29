/*
 * File: /d/Gondor/common/guild2/ticker.c
 *
 * The orginal concept and implementation by Chmee
 *
 * This object is a sort of clock measuring the time the game is on.
 * Its advantage is that it can measure the length of the previous
 * game from reboot to armageddon or crash.
 * If you want to restart ticker manualy you need to:
 * 1. Call ~Godor/common/guild2/ticker start_ticker
 * 2. replace ticker.o with one with the correct tick value
 * 3. Call ~Godor/common/guild2/ticker query_ticker
 *
 * -- Toby, 11th-Sept-2007, change game_length from 26hrs to 17hrs 
 *                          making the scoreboard (60 spots) keep 
 *                          track of 1.41 months worth of activity.
 *                          (Previous was 2.1 months)
 */

inherit "/std/object.c";

#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

int ticker;
static int alarm = 0;

nomask public int start_ticker( void );
nomask public int query_ticker( void );
nomask public void tick( void );
nomask public int query_alarm( void );

/*
 * Function name: start_ticker
 * Description  : Initializes the ticker.
 * Return values: The return value is the id of the alarm or 0 if
 *                the alarm is already started.
 */
nomask public int start_ticker( void )
{
    setuid();
    seteuid( getuid() );
    ticker = 0;
    save_object( TICKER );
    if (alarm == 0)
    {
        alarm = set_alarm( TICKER_LENGTH, TICKER_LENGTH, tick);
    }   
    return alarm;
}

/*
 * Function name: tick
 * Description  : Increases the ticker and saves its value. Also updates
 *                the disk copy of the IDLENESS roster (idleness.o) if the
 *                system requests such update.
 */
nomask public void tick( void )
{
    ticker++;
    save_object( TICKER );
    if (IDLENESS->query_udate())
    {
        IDLENESS->remote_save( IDLENESS );
        IDLENESS->reset_update();
    }

    // Switch the idleness system to a new game every 17 hours
    if((ticker * ftoi(TICKER_LENGTH)) >= 61200)
    {
        IDLENESS->start_idling();
    }

    return;
}

/*
 * Function name: query_ticker
 * Description  : Reads the current value of the ticker and returns it.
 */
nomask public int query_ticker( void )
{
    setuid();
    seteuid( getuid() );
    
    restore_object( TICKER );
    return ticker;
}

/*
 * Function name: query_alarm
 * Description  : Returns the id of tick alarm.
 */
nomask public int query_alarm( void )
{
    return alarm;
}
