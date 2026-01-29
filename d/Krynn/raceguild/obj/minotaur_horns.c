/*
 * Navarre, Minotaur horns.
 *
 * 2010/03/22 Last update
 * 2011/10/12 Lavellan - Fixed MAGIC_AM_MAGIC
 */
inherit "/std/armour";

#include "/d/Krynn/common/defs.h"

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define DEFAULT_AC 5

void
create_armour()
{
    set_name("_minotaur_ac_horns_");
    set_short("Minotaur horns");
    set_long("These are some fine minotaur horns.");
    set_no_show();
    set_af(this_object());
    set_ac(DEFAULT_AC);
    set_at(A_MAGIC);
    set_shield_slot(({A_HEAD}));

    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    //add_prop(MAGIC_AM_MAGIC, ({"enchantment", 100}));
    add_prop(MAGIC_AM_MAGIC, ({100, "enchantment"}));
    add_prop(OBJ_S_WIZINFO, "The object represent the horns of the minotaurs.");
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
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to) || !living(to))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
}

void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
}

public string
query_recover()
{
  return 0;
}


