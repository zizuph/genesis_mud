#pragma strict_types
#pragma save_binary
#pragma no_inherit
#pragma no_clone
 
#include <macros.h>

// Save every fifth time we do a weather change.
#define SAVE_INTERVAL 1
 
// We will change the entire weather scheme every 10-15 minutes.
// How often we change single ones depends on number of regions
// players occupy, but this system should ensure each region gets
// reset at max 15 minute cycles. (Assuming players occupy it)
 
#define WEATHER_CYCLE_TIME(i) (itof((600 + random(300)) / (i)))
 
private void do_next_weather();
private void do_weather(string weather_region);
private void save_it(int always = 0);
 
private mapping weather_regions = ([]);
private string *change_order = ({});
 
static int save_counter = 0,
           weather_alarm = 0;
 
/*
 * Function name: create
 * Description:   load the save file of this object on creation.
 */
public void
create()
{
    if (weather_alarm)
        return;
    setuid();
    seteuid(getuid());
    restore_object(MASTER);
    do_next_weather();
}
 
/*
 * Function name: add_weather_region
 * Description:   add a weather region to the regions mapping
 * Arguments:     region_name - a unique name to identify this
 *                    region by. e.g. 'Minas Tirith'
 *                server - the name of the local weather server
 *                    for that region. Note that several regions
 *                    can have the same weather server!
 *                precip - an array of ints describing chance of
 *                    various types of precipitation. The individual
 *                    servers should make some decision about what
 *                    each type means, this file does not do that.
 *                    The array is given as follows:
 *                    ({ % chance of precipitation 0,
 *                       % chance of precipitation 1 + previous,
 *                       % chance of precipitation 2 + all previous, ... })
 *                    So if you have ({ 30, 50, 100 }), you have
 *                    a 30% chance for 0, 20% for 1, and 50% for 2.
 *                    Using: ({ 30, 20, 100 }) will _never_ give
 *                    precipitation type 1. (useful if you want to skip
 *                    it in some weather server!)
 *                    ({ 30, 100, 50 }) will never be above 1.
 *                    Any number of precipitation types can be given.
 * Returns:       1 if the region was added.
 */
public int
add_weather_region(string region_name, string server, int *precip)
{
    if (member_array(region_name, m_indices(weather_regions)) != -1)
        return 0;
    weather_regions[region_name] = ({ server, 0, precip });
    change_order = ({ region_name }) + change_order;
    save_it(1);
    return 1;
}
 
/*
 * Function name: remove_weather_region
 * Description:   Removes a region from the weather server.
 * Arguments:     region_name - the name of the region.
 * Returns:       1 if removed.
 */
public int
remove_weather_region(string region_name)
{
    int i;
    if (!weather_regions[region_name])
        return 0;
    weather_regions = m_delete(weather_regions, region_name);
    i = member_array(region_name, change_order);
    if (i != -1)
        change_order = exclude_array(change_order, i, i);
    save_it(1);
    return 1;
}
 
/*
 * Function name: do_weather
 * Description:   find all players in our region, and call the regional
 *                weather server with that information, and the new and
 *                old weather types.
 * Arguments:     region_name - the name of the region.
 */
private void
do_weather(string region_name)
{
    object *u;
    int *tmp_precip;
    int new_weather = 0, tmp, i = 0, j;
 
    u = filter(users(), &operator(==)(region_name) @ &->query_weather_region()
        @ environment); // This neat little thing (I love functions!)
                        // returns all players in a room which returns
                        // 'region_name' in query_weather_region
    if (sizeof(u))
    {
        tmp = random(100);
        tmp_precip = weather_regions[region_name][2];
        j = sizeof(tmp_precip);
        for ( ; i < j, tmp > tmp_precip[i] ; i++, new_weather++)
            ;
        tmp = weather_regions[region_name][1];
        weather_regions[region_name][1] = new_weather;
        set_alarm(0.0, 0.0, &(weather_regions[region_name][0])->
            change_weather(u, new_weather, tmp)); // Use an alarm to avoid
                                                 // too_long_eval
    }
 
    tmp = member_array(region_name, change_order);
    if (i != -1)
    {
        // Add this region as the last one to have its weather changed.
        change_order = exclude_array(change_order, tmp, tmp);
        change_order += ({ region_name });
    }
    do_next_weather();
}
 
/*
 * Function name: do_next_weather
 * Description:   flow control function for alarms -- make sure we
 *                aren't updating empty (of players) regions, and
 *                make sure we update the occupied regions in a
 *                reasonable amount of time.
 *                If nobody is in any weather region, don't bother
 *                to calculate new weather! Just try again later.
 */
private void
do_next_weather()
{
    string *tmp, *tmp_change_order;
    int i;
 
    // Filter out all regions which have no players in them now.
    tmp = map(users(), &->query_weather_region() @ environment);
    tmp_change_order = filter(change_order, &operator(!=)(-1) @
        &member_array(, tmp));
 
    i = sizeof(tmp_change_order);
    if (!i)
    {
        weather_alarm = set_alarm(WEATHER_CYCLE_TIME(1), 0.0,
            do_next_weather);
        return;
    } // Skip all code in do_weather() if no regions.
 
    weather_alarm = set_alarm(WEATHER_CYCLE_TIME(i), 0.0,
        &do_weather(tmp_change_order[0]));
    save_it();
    return;
}
 
/*
 * Function name: manual_set_weather
 * Description:   Set the weather type for a region by hand, in case
 *                servers want to control the weather more strictly.
 * Arguments:     region_name - the name of the region.
 *                new_weather - the new value for the weather.
 * N.B.:          Only the server for a region may call this.
 */
public void
manual_set_weather(string region_name, int new_weather)
{
    if (!weather_regions[region_name])
        return;
    if (file_name(previous_object()) != weather_regions[region_name][0])
        return;
    weather_regions[region_name][1] = new_weather;
}
 
/*
 * Function name: query_weather
 * Description:   get the weather for a region
 * Arguments:     region_name - the name of the region.
 * Returns:       the weather type or -1 if no such region.
 */
public int
query_weather(string region_name)
{
    if (!weather_regions[region_name])
        return -1;
    return weather_regions[region_name][1];
}
 
/*
 * Function name: save_it
 * Description:   periodically save the weather, so it does not start
 *                the same on every reboot.
 * Arguments:     always - if 1, will always save. Otherwise, saves
 *                    based on SAVE_INTERVAL
 */
private void
save_it(int always = 0)
{
    if ((++save_counter >= SAVE_INTERVAL) || always)
    {
        save_counter = 0;
        setuid();
        seteuid(getuid());
        save_object(MASTER);
    }
}
 
/*
 * We don't want people messing with this object.
 */
public int
query_prevent_shadow()
{
    return 1;
}
