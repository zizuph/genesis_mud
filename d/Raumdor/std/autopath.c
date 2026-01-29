#include "defs.h"

inherit STD_DIR + "routine";

mapping pathways = ([
    "road": ({}),
    "beach": ({"road","forest"}),
    "forest": ({"road","beach","mountains"}),
    "mountains": ({"road","forest","plains"}),
    "plains": ({"road","mountains","drakmere"}),
    "drakmere": ({"road","plains"}),
    "keep": ({"drakmere"})
]);

object live;
string destination,
       *waypoints;

void
set_destination(string str)
{
    destination = str;
}

void
generate_waypoints()
{
    waypoints = ({});
    if (!destination)
        return;
    waypoints = ({destination});
    // Note: sizeof(waypoints) will grow as this loop runs
    for (int i = 0; i < sizeof(waypoints); i++)
        foreach (string candidate: pathways[waypoints[i]])
            if (member_array(candidate, waypoints) < 0)
                waypoints += ({candidate});
}

mixed
get_autopath_step()
{
    mixed result;
    foreach (string waypoint: waypoints)
    {
        result = E(live)->query_waypoint_direction(waypoint);
        if (result)
            break;
    }
    return result;
}

public void
routine()
{
    object here;
    mixed step;

    if (!live)
    {
        stop(STATUS["FAILURE"]);
        return;
    }

    step = get_autopath_step();
    if (stringp(step))
    {
        here = E(live);
        live->command("$" + step);
        if (here == E(live))
            interrupt(STATUS["BLOCKED"]);
    }
    else if (!step)
        interrupt(STATUS["ERROR"]);
    else
        stop(STATUS["SUCCESS"]);
}

public void
set_live(object o)
{
    live = o;
}

public void
resume()
{
    ::start();
}

public void
start()
{
    generate_waypoints();
    ::start();
}
