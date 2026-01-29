inherit "/d/Genesis/newmagic/spells/bolt";

#include <ss_types.h>

public varargs int
config_spell(object caster, object *targets, string argument)
{
    ::config_spell(caster, targets, argument);

    set_spell_element(SS_ELEMENT_FIRE, 60);

    set_bolt_pen(800);
    set_bolt_desc("fire");

    return 0;
}
