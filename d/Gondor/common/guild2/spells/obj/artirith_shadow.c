/*
 * /d/Gondor/common/guild2/spells/obj/artirith_shadow.c
 *
 * This is an object that is cloned into a player to make
 * him or her into a shadow.
 * It is used with the 'artirith' spell of the Morgul Mages.
 *
 * Olorin, 01-nov-1994
 * Revision history:
 */
#pragma strict_types

inherit "/std/shadow";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

#define ARTIRITH_OB_NAME "Morgul_Spell_Obj_Artirith"

void    end_artirith();
void    end_warning();

int     alarm_id_end,
        alarm_id_warning;

int
query_artirith_time()
{
    return ftoi(get_alarm(alarm_id_end)[2]);
}

string
artirith_wizinfo()
{
    return "The spell object for the 'artirith' spell of the Morgul Mages.\n"
        +  "The effect will end in " +query_artirith_time()+ " seconds.\n";
}

void
set_time(int i)
{
    int     time;
    object  ob;

    if (i < 1)
    {
        set_alarm(0.0, 0.0, remove_shadow);
        return;
    }

    time = i;

    shadow_who->add_prop(LIVE_I_SEE_DARK,
       shadow_who->query_prop(LIVE_I_SEE_DARK) + 5);
    shadow_who->add_prop(LIVE_I_SEE_INVIS,
       shadow_who->query_prop(LIVE_I_SEE_INVIS) + 5);
    shadow_who->add_prop(OBJ_I_INVIS, shadow_who->query_prop(OBJ_I_INVIS) + 5);

    FIX_EUID;
    ob = clone_object(MORGUL_SPELL_OBJS + "artirith_ob");
    ob->set_shadow_obj(TO);
    ob->add_name(ARTIRITH_OB_NAME);
    if (ob->move(shadow_who))
        ob->move(shadow_who, 1);

    alarm_id_warning = set_alarm(itof(time - 15), 0.0, end_warning);
    alarm_id_end = set_alarm(itof(time), 0.0, end_artirith);
}

void
end_artirith()
{
    int     dummy;
    object  obj;

    if (sizeof(get_alarm(alarm_id_end)))
        remove_alarm(alarm_id_end);
    alarm_id_end = 0;

    if (sizeof(get_alarm(alarm_id_warning)))
        remove_alarm(alarm_id_warning);
    alarm_id_warning = 0;

    tell_room(ENV(shadow_who), "A dark cloud appears out of nowhere.\n",
        shadow_who);

    dummy = shadow_who->query_prop(LIVE_I_SEE_DARK)-5;
    if (dummy)
        shadow_who->add_prop(LIVE_I_SEE_DARK, dummy);
    else
        shadow_who->remove_prop(LIVE_I_SEE_DARK);

    dummy = shadow_who->query_prop(LIVE_I_SEE_INVIS)-5;
    if (dummy)
        shadow_who->add_prop(LIVE_I_SEE_INVIS, dummy);
    else
        shadow_who->remove_prop(LIVE_I_SEE_INVIS);

    dummy = shadow_who->query_prop(OBJ_I_INVIS)-5;
    if (dummy)
        shadow_who->add_prop(OBJ_I_INVIS, dummy);
    else
        shadow_who->remove_prop(OBJ_I_INVIS);

    shadow_who->catch_msg("You return from the realm of the shadows!\n");

    tell_room(ENV(shadow_who), "The dark cloud consolidates, and "
      + QNAME(shadow_who) + " steps out of it.\n", shadow_who);

    if (!objectp(obj = present(ARTIRITH_OB_NAME, shadow_who)))
        shadow_who->catch_msg("BUG: Artirith spell object not removed! Please inform Olorin!\n");
    else
        obj->remove_object();
    set_alarm(0.0, 0.0, remove_shadow);
}

void
stop_effect()
{
    remove_alarm(alarm_id_end);
    set_alarm(0.0, 0.0, end_artirith);
}

public void
attack_object(object ob)
{
    shadow_who->catch_msg("You cannot fight while you are in "
      + "the realm of the shadows, so you materialize again.\n");
    set_alarm(0.0, 0.0, stop_effect);
    shadow_who->attack_object(ob);
}

void
end_warning()
{
    shadow_who->catch_msg(
        "You feel that you will soon return from the realm of the shadows.\n");
}

public int query_artirith_active() { return 1; }

