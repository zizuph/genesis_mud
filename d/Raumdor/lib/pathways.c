/*
 * This is the primary file needed for automatic path following in Raumdor.
 * This is a particularly robust method, given its use of waypoints.
 *
 * Roughly speaking (as this is a work in progress), it works like so:
 * - We provide a function that takes a particular waypoint and generates an
 *   array of waypoints in order of priority. For example, if you are going to
 *   the "beach" waypoint, the only connecting waypoint (at present) would be
 *   the "road" waypoint. There are several waypoints connected to the road,
 *   e.g. "forest", "mountains", "ruins", "drakmere". Each of those may have
 *   connecting waypoints, e.g. "keep" is connected to "drakmere". Therefore
 *   you end up with a return value like:
 *     ({"beach","road","forest","mountains","ruins","drakmere","keep"})
 * - In each room we have a way to calculate which direction to go to reach the
 *   nearest waypoint(s). We step through the aforementioned array looking for
 *   the first waypoint on our list. If we are going to the "beach", we will
 *   always look for a "beach" exit first, but if we fail to find one, we will
 *   then look for the "road", and so on.
 * - For example, every room in Drakmere should be linked to the "drakmere"
 *   waypoint, which in this case would be the center of Drakmere. Every room 
 *   from the center to the west gate would provide a "road" direction.
 *   Optionally, other rooms in Drakmere could provide such a direction so long
 *   as they formed a contintinous path to the road. The "road" rooms
 *   nearest Drakmere would each have directions to the "mountains", those 
 *   in the mountains would link to the "forest", and those in the forest would
 *   link to the "beach".
 * - Consequently, completing this one path would mean that any room linked to
 *   the "road" could also lead to the beach. So long as the reverse path
 *   was maintained, any room linked to the road could also lead to Drakmere.
 *   With new areas linked to the road and the road linked to these areas, we
 *   gradualy build a robust system to navigate the entire domain.
 */

#include "defs.h"
//#include "pathways.h"
#define PATHWAY_SUCCESS     0
#define PATHWAY_NOT_FOUND   1

int autopath_alarm;
float autopath_delay;
object autopath_living;
string autopath_destination;
mapping pathways = ([
    "road": ({}),
    "beach": ({"road","forest"}),
    "forest": ({"road","beach","mountains"}),
    "mountains": ({"road","forest","plains"}),
    "plains": ({"road","mountains","drakmere"}),
    "drakmere": ({"road","plains"}),
    "keep": ({"drakmere"})
]);

string *
generate_waypoints(string waypoint)
{
    int i;
    string *waypoints = ({waypoint});
    // Note: sizeof(waypoints) will grow as this loop runs
    for (i = 0; i < sizeof(waypoints); i++)
        foreach (string candidate: pathways[waypoints[i]])
            if (member_array(candidate, waypoints) < 0)
                waypoints += ({candidate});
    return waypoints;
}

varargs mixed
get_pathway_step(string *waypoints, object room)
{
    mixed result;
    foreach (string waypoint: waypoints)
    {
        result = room->query_waypoint_direction(waypoint);
        if (result)
            break;
    }
    return result;
}

varargs int
do_pathway_step(string *waypoints, object living = this_object())
{
    mixed result = get_pathway_step(waypoints, E(living));
    if (stringp(result))
        living->command("$" + result);

    return result;
}

void
stop_autopath()
{
    remove_alarm(autopath_alarm);
}

void
do_autopath(string *waypoints, float delay, object living = this_object())
{
    mixed result = do_pathway_step(waypoints, living);
    if (!result)
        living->autopath_stopped(PATHWAY_NOT_FOUND);
    else if (result == 1)
        living->autopath_stopped(PATHWAY_SUCCESS);
    else
        return;

    stop_autopath();
}

void
autopath(string destination, float delay, object living = this_object())
{
    autopath_destination = destination;
    autopath_delay = delay;
    autopath_living = living;
    autopath_alarm = set_alarm(0.0, delay,
            &do_autopath(generate_waypoints(destination), delay, living));
}

void
resume_autopath()
{
    autopath(autopath_destination, autopath_delay, autopath_living);
}


string
query_autopath_destination()
{
    return autopath_destination;
}
