inherit "/d/Emerald/ctower/npc/elemental";

#include <stdproperties.h>
#include <ss_types.h>

void
create_elemental()
{
    set_element("water");

    set_skill(SS_ELEMENT_WATER, 100);

    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_WATER, 100);

    set_stats(({ 100, 90, 70, 120, 120, 120 }));

    set_all_attack_unarmed(30, 30);
    set_all_hitloc_unarmed(40);
}

void
engulf_hit(object enemy)
{
}


int
invoke_fire()
{
    return 1;
}
