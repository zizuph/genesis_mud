inherit "/d/Genesis/magic/spells/bolt";

#include <ss_types.h>

int
create_spell_ice_bolt(object caster, object *targets, string argument)
{
    create_spell_bolt(caster, targets, argument);

    set_spell_element(SS_ELEMENT_WATER, 60);

    set_bolt_pen(800);
    set_bolt_desc("ice");
}

