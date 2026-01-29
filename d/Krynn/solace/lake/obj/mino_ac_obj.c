/*
 * What         : _mino_ac_obj
 * Used by      : Minotaur chieftain Kadez in the Toron minotaur village
 *                near Crystalmir Lake.
 *                /d/Krynn/solace/lake/npc
 * Description  : A cheat object to provide head armour to minotaurs wearing
 *                the "decorated iron champron". Object is cloned when the
 *                champron is weared and removed when the champron is.
 *                of head AC.
 * Made by      : Cherek, Feb 2007
 */

inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
    set_name("_mino_ac_for_helm");
    set_short("_mino_helmet");
    set_adj(({"mino","helmet"}));
    set_af(TO);
    set_long("You shouldn't be able to see this.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "A magical object for the minotaur helm.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 20, "abjured" }) );
    add_prop(MAGIC_AM_ID_INFO, ({
        "Work around to let the minotaur helm give a little AC.\n", 1}) );
    set_no_show();
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    set_default_armour(5, A_MAGIC);
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
remove_myself(object user)
{
    int head_ac;
    wearer = user;
    if (!wearer)
    {
        return 0;
    }
    wearer->remove_arm(TO);

    // Note that this calls the setup in the race minotaur shadow.
    // Its necessary because the remove_arm mess up the natural ac
    // on the head.
    wearer->setup_things();

    return 1;
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    wearer = dest;
    wearer->wear_arm(TO);
}

void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    remove_myself(old);
}

int *query_shield_slots()
{
    return ({ A_HEAD });
}

string
query_recover()
{
  return 0;
}
