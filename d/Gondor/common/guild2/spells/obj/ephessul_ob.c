/*
 * /d/Gondor/common/guild2/spells/obj/ephessul_ob.c
 *
 * This is an object that is cloned into a player to protect him
 * against the Sul-Ambar Cloud and to raise his resistance to 
 * poisoning.
 * It is used with the 'ephessul' spell of the MOrgul Mages.
 *
 * Olorin, 19-jan-1994
 * Revision history:
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

void    end_warning();
void    end_ephessul();

int     a_warn = 0,
        a_end = 0;

void
create_object()
{
    set_name("Morgul_Ephessul_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    add_prop(MAGIC_I_RES_POISON, 100);
    add_prop(MAGIC_I_RES_MAGIC,  100);
    add_prop(MAGIC_I_RES_MAGIC,   50);
    add_prop(OBJ_I_RES_POISON,   100);
    add_prop(OBJ_I_RES_MAGIC,    100);
    add_prop(OBJ_I_RES_MAGIC,     50);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    set_no_show();
}

int
query_time()
{
    return ftoi(get_alarm(a_end)[2]);
}

string
wizinfo()
{
    return "The spellobject for the 'ephessul' spell of the Morgul Mages.\n" +
        "Protection against the 'sulambar' cloud and resistance against poison.\n" +
        "MAGIC_I_RES_POISON : 40% additive,\n" +
        "MAGIC_I_RES_MAGIC  : 40% additive,\n" +
        "MAGIC_I_RES_AIR    : 60% non-additive.\n" +
        "The effect will end in " +query_time()+ " seconds.\n";
}

void
set_time(int i)
{
    object player;
    int    time;

    if (!living(player = ENV(TO)) || (i < 1))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
    time = i;

    player->add_prop(MORGUL_I_SULAMBAR_RES,
        player->query_prop(MORGUL_I_SULAMBAR_RES) + 1);

    player->add_magic_effect(TO);

    if (a_end && sizeof(get_alarm(a_end)))
        return;

    if (time > 20)
        a_warn = set_alarm(itof(time - 20), 0.0, end_warning);

    a_end = set_alarm(itof(time), 0.0, end_ephessul);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (objectp(from) && living(from))
    {
        from->remove_magic_effect(TO);

        from->add_prop(MORGUL_I_SULAMBAR_RES,
            from->query_prop(MORGUL_I_SULAMBAR_RES)-1);
    }
}

void
end_ephessul()
{
    object player;

    if (!objectp(player = ENV(TO)))
        set_alarm(0.0, 0.0, remove_object);

    if (!living(player))
        set_alarm(0.0, 0.0, remove_object);

    player->catch_msg("You feel the power of the Windfence disappearing.\n"
        + "You are not protected anymore!\n");
        set_alarm(0.0, 0.0, remove_object);
}

void
end_warning()
{
    object  player;

    if (!objectp(player = ENV(TO)))
        return;

    if (!living(player))
        return;

    player->catch_msg("You feel that the Windfence will disappear soon.\n");
    return;
}

mixed
query_magic_protection(string prop, object who = previous_object())
{
    object  player = ENV(TO);

    if (who == player)
    {
        switch (prop)
        {
        case MAGIC_I_RES_POISON:    return ({ 40,  1 });
        case MAGIC_I_RES_MAGIC:     return ({ 40,  1 });
        case MAGIC_I_RES_AIR:       return ({ 60,  0 });
        }
    }

    return ::query_magic_protection(prop, who);
}

