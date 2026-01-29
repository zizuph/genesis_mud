inherit "/d/Emerald/ctower/npc/elemental";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

void
create_elemental()
{
    set_element("air");
    set_opposing_element("earth");

    set_long("The air elemental is barely visible.  Only the " +
        "particles of dust whirling about it give the indication " +
        "of a humanoid form.\n");

    set_skill(SS_ELEMENT_AIR, 100);

    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_AIR, 100);

    set_strong_stats(({ 150, 300, 100, 100, 100, 300 }));
    set_weak_stats(({ 75, 150, 75, 100, 100, 150 }));
}

void
engulf_hit(object enemy)
{
    enemy->catch_tell(query_The_name(enemy) + " blasts you with " +
        "a gust of air, nearly knocking you off of your feet!\n");
    tell_watcher(QCTNAME(this_object()) + " blasts " + QTNAME(enemy) +
        "with a gust of air, nearly knocking " + enemy->query_objective() +
        " off of " + enemy->query_possessive() + " feet!\n", enemy);

    enemy->add_attack_delay(10);
}

int
invoke_earth()
{
    weaken_elemental();
    return 1;
}

int
invoke_air()
{
    strengthen_elemental();
    return 1;
}
