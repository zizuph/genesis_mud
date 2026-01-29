inherit "/std/shadow";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

int     strength = 5,
        alarm_id;

mixed
query_prop(string prop)
{
    mixed ret;
    ret = shadow_who->query_prop(prop);

    if (prop != LIVE_I_SEE_DARK)
        return ret;
    else if (ENV(shadow_who)->query_prop(ROOM_I_INSIDE))
        return (ret + strength);
    else
        return ret;
}

void
set_strength(int i)
{
    strength = i;
    if (strength > 5)
        strength = 5;
}

void
end_mortirio()
{
    string  mess;

    shadow_who->catch_msg(
        "You feel that your vision becomes normal again.\n");
    if (objectp(shadow_who))
    {
        mess = " stop glowing like red coals.\n";

        tell_room(ENV(shadow_who), ({
            shadow_who->query_name()+"'s eyes" + mess,
            "The eyes of the "+shadow_who->query_nonmet_name()+mess, ""}),
            shadow_who, shadow_who);
    }
    set_alarm(0.0, 0.0, remove_shadow);
}

void
set_duration(int i)
{
    if (alarm_id)
        remove_alarm(alarm_id);
    alarm_id = set_alarm(itof(i), 0.0, end_mortirio);
}

int
query_mortirio_active()
{
    return 1;
}

float
query_mortirio_time_left()
{
    mixed   arr;

    if (alarm_id && sizeof(arr = get_alarm(alarm_id)))
        return arr[2];
    return -1.0;
}

