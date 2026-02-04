inherit "/d/Genesis/newmagic/spells/harm";

#include <ss_types.h>

public varargs int
config_spell(object caster, object *targets, string argument)
{
    ::config_spell(caster, targets, argument);

    set_spell_element(SS_ELEMENT_DEATH, 60);

    set_harm_pen(600);
    set_spell_desc("swarm");
    set_spell_time(2);
    

    return 0;
}
