inherit "/d/Emerald/ctower/npc/elemental";

#include <stdproperties.h>
#include <ss_types.h>

void
create_elemental()
{
    set_element("fire");

    set_skill(SS_ELEMENT_FIRE, 100);

    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_FIRE, 100);

    set_stats(({ 80, 120, 70, 120, 120, 120 }));

    set_all_attack_unarmed(40, 40);
    set_all_hitloc_unarmed(40);
}

void
engulf_hit(object enemy)
{
}

int
invoke_water()
{
    return 1;
}
