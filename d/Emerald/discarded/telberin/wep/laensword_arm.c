#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void 
create_armour()
{
    set_name("laensword_arm");
    set_no_show();

    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); 
    add_prop(OBJ_S_WIZINFO, "This is magic armour cloned by the " +
        "light-laen longsword, /d/Emerald/telberin/wep/laensword.c\n");

    set_likely_break(0);

    set_ac(5);
    set_am(({ -4, 2, 2 }));

    set_at(A_MAGIC);
    set_af(this_object());

    set_shield_slot(({ A_BODY, A_L_ARM, A_R_ARM }));
}

void
add_laensword_armour(object who, int ac = 10)
{
    object tp = this_player();

    move(who, 1);

    set_ac(ac);

    set_this_player(who);

    if (stringp(who->wear_arm(this_object())))
    {
        remove_object();
        set_this_player(tp);
        return;
    }

    set_this_player(tp);

    set_lock();
}

void
remove_laensword_armour()
{
    remove_object();
}

int
query_recover()
{
    return 0;
}

/* Unforunately, a lot of armour breaking routines don't
 * check likely_break == 0, so this is needed.
 */
varargs void
remove_broken(int silent = 0)
{
    return;
}
