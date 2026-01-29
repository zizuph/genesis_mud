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
}

void
engulf_hit(object enemy)
{
}

int
invoke_fire()
{
    weaken_elemental();
    return 1;
}

int
invoke_water()
{
    strengthen_elemental();
    return 1;
}
