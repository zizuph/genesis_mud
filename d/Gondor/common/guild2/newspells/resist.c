#include "spells.h"
#include <tasks.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit (GENESIS_SPELL_DIR + "resist");

public int
spell_resist_poison( object caster, object target,
                     int element, int difficulty )
{
    int res;

    res = max(0, min(100, target->resolve_task( difficulty,
        ({
            SKILL_WEIGHT, 40, SS_FORM_ABJURATION,
            SKILL_WEIGHT, 40, element,
            SKILL_WEIGHT, 20, SS_SPELLCRAFT,
            SKILL_WEIGHT, 40, TS_INT,
            SKILL_WEIGHT, 40, TS_WIS,
            SKILL_WEIGHT, 20, TS_DIS
         }) )));

    res += combine_resistances(target,
		({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_POISON }));

    return min(res, 100);
}

public int
weapon_spell_resist( object caster, object weapon, int element,
                     int difficulty)
{
    int res;

    if (element == SS_ELEMENT_DEATH)
    {
        res = weapon->query_prop(OBJ_I_RES_DEATH);
    }
    else
    {
        res = weapon->query_prop(OBJ_I_RES_FIRE);
        res += weapon->query_prop(OBJ_I_RES_MAGIC);
    }

    res = 2 * res / 3;
    return res;
}

