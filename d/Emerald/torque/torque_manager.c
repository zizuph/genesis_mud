#pragma strict_types
#pragma no_clone
#pragma no_shadow

#include "torque.h"
#include "torque_desc.c"

#define TORQUE_DATA_FILE(owner) \
    (TORQUE_LOG + "torques/" + owner[0..0] + "/" + owner)

#define TORQUE_DATA_DESC "desc"
#define TORQUE_DATA_DATE "date"

static object *torques = ({});

private nomask void
create()
{
    setuid();
    seteuid(getuid());
}

public void
register_torque(object torque)
{
    torques |= ({ torque });
}

public void
unregister_torque(object torque)
{
    torques -= ({ torque });
}

public object *
get_torques()
{
    torques -= ({ 0 });
    return torques + ({});
}

public varargs object *
get_active_torques(object request_torque)
{
    return filter(get_torques() - ({ request_torque }),
        &->query_torque_active(request_torque));
}

public string
get_torque_desc(mixed owner)
{
    mapping data;

    if (objectp(owner))
    {    
        owner = owner->query_real_name();
    }

    data = restore_map(TORQUE_DATA_FILE(owner));
    return data[TORQUE_DATA_DESC];
}

public void
set_torque_desc(mixed owner, string desc)
{
    mapping data;

    if (objectp(owner))
    {    
        owner = owner->query_real_name();
    }

    data = restore_map(TORQUE_DATA_FILE(owner));
    data[TORQUE_DATA_DESC] = desc;
    save_map(data, TORQUE_DATA_FILE(owner));
}

public int
get_torque_date(mixed owner)
{
    mapping data;

    if (objectp(owner))
    {    
        owner = owner->query_real_name();
    }

    data = restore_map(TORQUE_DATA_FILE(owner));
    return data[TORQUE_DATA_DATE];
}

public varargs void
set_torque_date(mixed owner, int date = time())
{
    mapping data;

    if (objectp(owner))
    {    
        owner = owner->query_real_name();
    }

    data = restore_map(TORQUE_DATA_FILE(owner));
    data[TORQUE_DATA_DATE] = date;
    save_map(data, TORQUE_DATA_FILE(owner));
}
    
public void
remove_object()
{
    if (sizeof(torques))
    {
        throw("Cannot remove manager while torques are registered.  " +
              "Use Destruct -D to override.\n");
    }

    destruct();
}

