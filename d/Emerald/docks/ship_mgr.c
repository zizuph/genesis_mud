#include "defs.h"

#define SHIPLINE_DOCK     0
#define SHIPLINE_SHIP     1
#define SHIPLINE_STATUS   2
#define SHIPLINE_TIME     3
#define SHIPLINE_ARR_SIZE 4

static mapping shiplines = ([]);
static object *listeners = ({});

public void
add_shipline(string name, mixed dock)
{
    mixed *arr = allocate(SHIPLINE_ARR_SIZE);

    if (objectp(dock))
    {
	dock = file_name(dock);
    }

    arr[SHIPLINE_DOCK]   = dock;
    arr[SHIPLINE_SHIP]   = 0;
    arr[SHIPLINE_STATUS] = STATUS_UNKNOWN;
    arr[SHIPLINE_TIME]   = time();
    shiplines[name] = arr;
}

void
create()
{
}

public void
register(object ob)
{
    listeners += ({ ob });
}

public void
unregister(object ob)
{
    listeners -= ({ ob });
}

public string *
query_shiplines()
{
    return m_indices(shiplines);
}

public object
query_ship(string line)
{
    mixed *arr = shiplines[line];

    if (!arr)
    {
        return 0;
    }

    return arr[SHIPLINE_SHIP];
}

public object
query_captain(string line)
{
    object ship = query_ship(line);

    if (!ship)
    {
        return 0;
    }

    return ship->query_captain();
}

public int
query_price(string line)
{
    object captain = query_captain(line);

    if (!captain)
    {
        return -1;
    }

    return captain->query_price();
}

public void
dock_ship(object ship, string dock)
{
    mixed *arr;

    arr = shiplines[dock];

    if (!arr)
    {
        add_shipline(dock, environment(ship));
        arr = shiplines[dock];
    }

    arr[SHIPLINE_SHIP]   = ship;
    arr[SHIPLINE_STATUS] = STATUS_DOCKED;
    arr[SHIPLINE_TIME]   = time();

    listeners -= ({ 0 });
    listeners->ship_docked(dock);
}

public void
undock_ship(object ship, string dock)
{
    mixed *arr = shiplines[dock];
    if (!arr)
    {
        return;
    }

    arr[SHIPLINE_STATUS] = STATUS_UNDOCKED;
    arr[SHIPLINE_TIME]   = time();

    listeners -= ({ 0 });
    listeners->ship_undocked(dock);
}

public int
query_ship_docked(string line)
{
    mixed *arr = shiplines[line];

    if (!arr)
    {
        return 0;
    }

    return arr[SHIPLINE_STATUS] == STATUS_DOCKED;
}

public int
query_ship_status(string line)
{
    mixed *arr = shiplines[line];

    if (!arr)
    {
        return 0;
    }

    return arr[SHIPLINE_STATUS];
}

public int
query_trip_length(string line)
{
    object ship = query_ship(line);
    int i, t, *stops;

    if (!ship)
    {
        return 0;
    }

    stops = ship->query_time_between_stops();
    for (i = 0, t = 0; i < sizeof(stops); t += stops[i++]) ;

    return t * ship->query_callout_fq();
}

public int
check_ticket_purchaser(object purchaser, string line)
{
    return 1;
}

public void
remove_object()
{
    if (sizeof(listeners))
    {
        throw("Cannot destruct while objects are registered.  " +
            "Use Destruct -D to override.\n");
    }

    destruct();
}
