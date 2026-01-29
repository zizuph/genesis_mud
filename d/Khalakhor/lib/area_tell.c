/* File         : /d/Khalakhor/lib/area_tells.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : April 1st 1999
 * Purpose      : A lib file to be used with a large area of
 *                rooms in order to generate messages for the
 *                area
 * Related Files: ~Khalakhor/coding/areas/area_tell_guide.txt
 * Comments     : See the above file to see how this works.
 * Modifications:
 */

private static int Alarm_id;

/* Function name: stop_area_tells
 * Description  : Stops producing messages for your area
 */
public void
stop_area_tells()
{
    remove_alarm(Alarm_id);
    Alarm_id = 0;
}

/* Function name: filter_for_messages_hook
 * Description  : A hook in which you are to define the conditions 
 *                of wether or not a player recieves a tell from 
 *                this object.
 * Arguments    : object player: The player we are testing.
 * Returns      : 1 if acceptable player.
 *                0 if not acceptable
 */
public int
filter_for_messages_hook(object player)
{
    return 0;
}

/* Function name: generate_messages_hook
 * Description  : a hook which you are to define that is 
 *                responsible for the messages that players
 *                are to recieve.
 * Returns      : a string of what message or tell you 
 *                wish players to recieve.
 */
public string
generate_messages_hook()
{
    return "";
}
    
/* Function name: produce_area_tells
 * Description  : The function responsible for generating 
 *                the area tells.
 */
public void
produce_area_tells()
{
    object *players;

    players = filter(users(), filter_for_messages_hook);

    if (!sizeof(players))
    {
        stop_area_tells();
        return;
    }
    players->catch_tell(generate_messages_hook());
    set_alarm(300.0 + itof(random(300)), 0.0, produce_area_tells);
}

/* Function name: start_area_tells
 * Description  : used to start producing tells to an area.
 */
public void
start_area_tells()
{
    if (Alarm_id)
        return;
    Alarm_id = set_alarm(itof(10 + random(10)) ,0.0, produce_area_tells);
}
