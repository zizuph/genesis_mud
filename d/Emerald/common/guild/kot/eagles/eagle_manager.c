#pragma strict_types
#pragma no_clone
#pragma no_shadow

#include "../guild.h"
#include <stdproperties.h>

#define SAVE_FILE (KOT_LOG_DIR + "eagles")

#define COST_PER_LEVEL (12 * 12 * 12 * 20)

#define DESTS_ARR_DEST     0
#define DESTS_ARR_PRIORITY 1
#define DESTS_ARR_LAT      2
#define DESTS_ARR_LONG     3

#define ONE_WEEK (60 * 60 * 24 * 7)

static mapping dests = ([
    "telberin": ({ "/d/Emerald/telberin/eagle_landing", 1, 5, 30 }),
    "southern docks" : ({ "/d/Emerald/lake/eagle_landing", 1, 0, 0 }),
    "telseron" : ({ "/d/Emerald/telseron/eagle_landing", 2, -30, 0 }),
]);

static object *eagles = ({});

#ifdef DONATIONS_REQUIRED
int donations = 0;
int level_open = 0;
int last_update = 0;

public void
save()
{
    setuid();
    seteuid(getuid());
    save_object(SAVE_FILE);
}
#endif

public string
query_destination(string name)
{
    return dests[name][DESTS_ARR_DEST];
}

public string
query_destination_name(string fname)
{
    int i;
    string *names = m_indices(dests);

    for (i = 0; i < sizeof(names); i++)
    {
        if (dests[names[i]][DESTS_ARR_DEST] == fname)
	{    
            return names[i];
	}
    }

    return 0;
}

public string *
query_destination_names()
{
    return m_indices(dests);
}

public string *
query_open_destination_names()
{
#ifdef DONATIONS_REQUIRED
    return m_indices(filter(dests, 
        &operator(<=)(, level_open) @ &operator([])(, DESTS_ARR_PRIORITY)));
#else
    return query_destination_names();
#endif
}

public string
query_open_destination(string name)
{
#ifdef DONATIONS_REQUIRED
    if (pointerp(dests[name]) &&
        (dests[name][DESTS_ARR_PRIORITY] <= level_open)
#else
    if (pointerp(dests[name]))
#endif
    {
        return dests[name][DESTS_ARR_DEST];
    }

    return 0;
}

#ifdef DONATIONS_REQUIRED
public void
add_donation(mixed v)
{
    if (objectp(v))
    {
        donations += v->query_prop(OBJ_I_VALUE);
    }
    else if (intp(v))
    {
        donations += v;
    }

    save();
}
#endif

public float
query_destination_time(string name1, string name2)
{
    int x1, x2, y1, y2, delta_x, delta_y;
    mixed *arr;

    if (!pointerp(arr = dests[name1]))
    {
        x1 = y1 = 5;
    }
    else
    {
        x1 = arr[DESTS_ARR_LAT];
        y1 = arr[DESTS_ARR_LONG];
    }

    if (!pointerp(arr = dests[name2]))
    {
        x2 = y2 = 5;
    }
    else
    {
        x2 = arr[DESTS_ARR_LAT];
        y2 = arr[DESTS_ARR_LONG];
    }

    delta_x = x1 - x2;
    delta_y = y1 - y2;

    return pow(itof(delta_x * delta_x + delta_y * delta_y), 0.5);
}

public object *
query_eagles()
{
    return (eagles -= ({ 0 }));
}

public void
register_eagle(object eagle)
{
    eagles += ({ eagle });
}

#ifdef DONATIONS_REQUIRED
public void
create()
{
    setuid();
    seteuid(getuid());
    restore_object(SAVE_FILE);

    if ((time() - last_update) > ONE_WEEK)
    {
        level_open = donations / COST_PER_LEVEL;
        donations -= COST_PER_LEVEL * level_open;
        last_update = time();
        save();
    }
}
#endif
