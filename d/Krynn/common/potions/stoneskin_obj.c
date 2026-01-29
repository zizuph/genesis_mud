/*
 * Vencar november 2003 - Project day in Palanthas (tm)
 *
 * The armour object behind the stoneskin potion.
 *
 * Thanks to the AOE team for the original usage in the
 * wizday file:
 *
 * /d/Genesis/ateam/aoe/events/wizday/obj/ring_arm.c
 *
 */
inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

#include "potion_defs.h"
/* local define of strengths, prices etc */

int time;

void
set_duration(int i)
{
    time = i;
}

void
create_armour()
{
    set_name("_stoneskin_armour");
    set_no_show();
    set_af(this_object());
    set_ac(STONE_POTION_AC);
    set_at(A_MAGIC);
    set_shield_slot(({A_HEAD,A_TORSO, A_R_ARM, A_L_ARM, A_LEGS}));

    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 100}));
    add_prop(OBJ_S_WIZINFO, "The object behind the " +
       "stoneskin potion");
}

mixed
remove(object ob)
{
    return 1;
}

mixed
wear(object ob)
{
    return 1;
}

varargs void
remove_broken(int silent = 0)
{
    return;
}

int
set_condition(int cond)
{
    return 1;
}

void
end_effect()
{


    E(TO)->remove_arm(TO);
    E(TO)->catch_msg("You feel your skin returning to normal.\n");
    say(QCTNAME(E(TO)) + "'s skin returns to normal.\n");
    set_alarm(0.0, 0.0, remove_object);

}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to) || !living(to))
    {
    set_alarm(0.0, 0.0, remove_object);
    return;
    }

    to->catch_msg("You feel your skin hardens and turn into stone!\n");
    say(QCTNAME(to) + "'s skin hardens into stone.\n");
    set_alarm(itof(time), 0.0, end_effect);
}

void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);

}


