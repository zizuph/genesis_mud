/*
 * This shadow is used for drop items that only a certain person
 * should be able to get from a corpse.
 *
 */
inherit "/std/shadow";

#include <stdproperties.h>

string name;
object player;

public void
individual(object ob, object who)
{
    shadow_me(ob);
    player = who;
    name = who->query_real_name();
}

public int
check_seen(object for_obj)
{
    if (!objectp(for_obj))
        return shadow_who->check_seen(for_obj);

    if (for_obj == player || for_obj->query_real_name() == name)
    {
        return shadow_who->check_seen(for_obj);
    }
    return 0;
}

void
leave_env(object from, object to)
{
    shadow_who->leave_env(from, to);

    if (living(to))
    {
        remove_shadow();
    }

    if (to->query_prop(ROOM_I_IS))
    {
        remove_object();
    }
}
