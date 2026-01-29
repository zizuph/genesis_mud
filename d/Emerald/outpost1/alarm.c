#include "defs.h"

public int alarm_active;
public object *notify_me = ({});

public void
activate_alarm()
{
    if (!alarm_active)
    {
        alarm_active = 1;
        notify_me -= ({ 0 });
        notify_me->alarm_activated();
    }
}

public void
deactivate_alarm()
{
    if (alarm_active)
    {
        alarm_active = 0;
        notify_me -= ({ 0 });
        notify_me->alarm_deactivated();
    }
}

public void
add_notify(object ob)
{
    notify_me += ({ ob });

    if (alarm_active)
    {
        set_alarm(0.0, 0.0, &ob->alarm_activated());
    }
}

public int
query_enemy(object who)
{
    object env = environment(who);

    if (!env || !wildmatch(OUTPOST1_DIR + "*", file_name(env)))
    {
        return 0;
    }

    if (who->query_kot_member())
    {
        return 0;
    }

    return 1;
}
    
public object *
query_enemies()
{
    return filter(users(), query_enemy);
}
