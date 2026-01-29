/*
 * skin.c
 *
 * Used in several monsters
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>

#define LEFTOVER_DECAY_TIME 180.0

float timeleft;
int alarmid;

void
create_object()
{
    timeleft = LEFTOVER_DECAY_TIME;

    add_prop("_skin_by_gresolle", 1);  /* why? dunno... */
}

void
leftover_init(string organ, string race)
{
    set_name(organ);
    set_short(organ);
    set_adj(race);
    set_long("This is a " + organ + " from " + LANG_ADDART(race) + ".\n");

    add_prop(OBJ_I_WEIGHT, previous_object()->query_prop(OBJ_I_WEIGHT) / 50);
    add_prop(OBJ_I_VOLUME, previous_object()->query_prop(OBJ_I_VOLUME) / 1000);

    timeleft = LEFTOVER_DECAY_TIME;
}

void
decay_fun()
{
    tell_room(E(TO), "The " + short () +
              " decays and leaves nothing behind.\n");
    remove_object();
}

void
enter_env(object dest, object old)
{
    mixed *m;
    if (!dest)
        return;

    if (alarmid)
    {
        m = get_alarm(alarmid);
        if (pointerp(m))
            timeleft = m[2];
        alarmid = 0;
    }
    if (function_exists("create_container", dest) == ROOM_OBJECT)
	alarmid = set_alarm(timeleft, 0.0, decay_fun);
}
