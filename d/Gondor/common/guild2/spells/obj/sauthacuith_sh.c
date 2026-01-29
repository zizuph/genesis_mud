/*
 * /d/Gondor/common/guild2/obj/sauthacuith_sh.c
 *
 * The shadow will make the corresponding shadow disappear
 * on logout, npc death, destruct (npc and pc).
 * This does not work on player death, since player death does not
 * remove shadows, and this does not work for Destruct -D. The problem
 * with player death was reported to AoM and AoC on 31-Aug-1997.
 *
 * Olorin, 29-Aug-1997
 */
#pragma strict_types

inherit "/std/shadow.c";

#include <ss_types.h>

#include "/d/Gondor/defs.h"

static int     Alarm = 0,
               Drain = 0;
static object  Other;

public object query_sauthacuith_other() { return Other; }

public nomask void 
set_sauthacuith_drain(int amount, object from) 
{
    if (!Drain)
    {
        Drain = amount;
	Other = from;
    }
}

public void
remove_sauthacuith_shadow(object who)
{
    if (objectp(who) && (who != Other))
    {
	shadow_who->remove_sauthacuith_shadow(who);
	return;
    }

    if (Alarm && remove_alarm(Alarm))
    {
	Alarm = 0;
	remove_shadow();
    }
}

/*
 * Function name: remove_shadow
 * Description:   End the drain.
 *                1. Called from the alarm.
 *                2. Called when the effect is ended in some other way.
 *                3. Called from remove_sauthacuith_shadow.
 */
public nomask void 
remove_shadow() 
{
    // Tell the other shadow to destruct.
    if (objectp(Other))
	Other->remove_sauthacuith_shadow(TO);

    Alarm = 0;
    shadow_who->set_stat_extra(SS_CON, shadow_who->query_stat_extra(SS_CON) - Drain);
    if (Drain < 0)
	shadow_who->catch_msg("You feel more vigorous.\n");
    else
	shadow_who->catch_msg("You feel less vigorous.\n");
    ::remove_shadow();
}

public void
remove_object()
{
    shadow_who->remove_object();
    remove_shadow();
}

public float
query_sauthacuith_duration()
{
    mixed    arr;

    if (!Alarm || !sizeof(arr = get_alarm(Alarm)))
	return -1.0;
    return arr[2];
}

public nomask void 
set_sauthacuith_duration(int duration) 
{
    int     old_max,
	    old_hp,
	    new_hp;

    if (!Drain || !objectp(Other) || (Alarm && sizeof(get_alarm(Alarm))))
        return;
    Alarm = set_alarm(itof(duration), 0.0, remove_shadow);

    old_max = shadow_who->query_max_hp();
    old_hp  = shadow_who->query_hp();
    // Increase the stat:
    shadow_who->set_stat_extra(SS_CON, shadow_who->query_stat_extra(SS_CON) + Drain);
    // Adjust hitpoints according to the changed stat value:
    new_hp  = shadow_who->query_max_hp() * old_hp / old_max;
    shadow_who->heal_hp(new_hp - old_hp);

    FIX_EUID;
    log_file("sauthacuith", sprintf("%15s: %+3d %5d secs, hp: %5d %+5d (%s).\n",
				    shadow_who->query_name(),
				    Drain, duration,
				    new_hp, new_hp - old_hp,
				    ctime(time())));

    if (Drain < 0)
	shadow_who->catch_msg("You feel less vigorous.\n");
    else
	shadow_who->catch_msg("You feel more vigorous.\n");
}

public int
query_sauthacuith_shadow()
{
    return 1;
}
