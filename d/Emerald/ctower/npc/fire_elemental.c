inherit "/d/Emerald/ctower/npc/elemental";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

void
create_elemental()
{
    set_element("fire");
    set_opposing_element("water");

    set_skill(SS_ELEMENT_FIRE, 100);

    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_FIRE, 100);

    set_strong_stats(({ 160, 250, 150, 100, 100, 300 }));
    set_stats(({ 80, 120, 70, 120, 120, 120 }));
}

void
engulf_hit(object enemy)
{
    enemy->catch_msg(query_The_name(enemy) + " blasts you with a " +
        "bolt of fire!\n");
    tell_watcher(QCTNAME(this_object()) + " blasts " + QTNAME(enemy) + 
       " with a bolt of fire!\n", enemy);

    enemy->hit_me(400, MAGIC_DT, this_object(), -1);

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_object());
    }
}

int
invoke_water()
{
    weaken_elemental();
    return 1;
}

int
invoke_fire()
{
    strengthen_elemental();
    return 1;
}
