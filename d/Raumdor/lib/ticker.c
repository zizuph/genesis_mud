/* An alternative to a timer. Rather than do calculations for every
 * registered object for a fixed period (e.g. 10 seconds), this combines
 * objects with the same repeat delay into one alarm. It also works for more
 * than just room tells, since it uses a callback. 
 *
 * 2018 Malus
 */
#pragma no_clone
#pragma strict_types

private static int count = 0;
private static mapping alarms = ([]),
                       index = ([]),
                       registered = ([]);

private void
tick(float repeat)
{
    function *callbacks = registered[repeat];
    if (!callbacks)
        return;
    callbacks -= ({0});
    if (!sizeof(callbacks))
    {
        m_delkey(registered, repeat);
        remove_alarm(alarms[repeat]);
        m_delkey(alarms, repeat);
        return;
    }
    foreach (function callback: callbacks)
        callback();
}

/*
 * Function Name: register
 * Description:   Register a callback
 * Arguments:     float repeat: How often to repeat the callback
 *                function callback: The function to call
 * Returns:       (int) The id used to unregister this callback
 */
public int
register(float repeat, function callback)
{
    int id = ++count;
    if (repeat <= 0.0)
        throw("repeat_delay must not be <= 0");
    if (member_array(callback, registered[repeat]) >= 0)
        throw("callback already registered");
    if (!registered[repeat])
        registered[repeat] = ({});
    registered[repeat] += ({callback});
    index[id] = ({repeat, callback});
    if (!get_alarm(alarms[repeat]))
        alarms[repeat] = set_alarm(repeat, repeat, &tick(repeat));
    return id;
}

/*
 * Function Name: unregister
 * Description:   Unregister a callback
 * Arguments:     int id: The id obtained from register()
 * Returns:       void
 */
public void
unregister(int id)
{
    mixed values = index[id];
    registered[values[0]] -= ({values[1]});
    m_delkey(index, id);
}

/*
 * Function Name: query_registered
 * Description:   Get the registered callbacks, indexed by repeat delay.
 *                Intended for debugging.
 * Arguments:     
 * Returns:       mapping of ([float: *function])
 */
public mixed
query_registered()
{
    return secure_var(registered);
}
