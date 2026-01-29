inherit "/d/Genesis/magic/spells/bolt";

#include <ss_types.h>

int
create_spell_fire_ball(object caster, object *targets, string argument)
{
    create_spell_bolt(caster, targets, argument);

    set_spell_element(SS_ELEMENT_FIRE, 70);

    set_bolt_pen(400);
    set_bolt_desc("fire");
}

