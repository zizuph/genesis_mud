#pragma strict_types
#pragma no_clone
#pragma no_shadow
#pragma no_inherit

#include "/d/Emerald/sys/weather.h"

private mixed *fronts = ({});
private int next_front_time;

void
save()
{
    setuid();
    seteuid(getuid());
    save_object(WEATHER_SAVE_FILE);
}

void
mkfront()
{
}

void
update_fronts()
{
    if (!next_front_time || (time() >= next_front_time))
    {
        /* New front around every 2 hours */
        next_front_time =
            time() + random(1800) + random(1800) + random(1800) + random(1800);
        mkfront();
        save();
    }
}

nomask void
create()
{
    setuid();
    seteuid(getuid());
    restore_object(WEATHER_SAVE_FILE);
    update_fronts();
}
