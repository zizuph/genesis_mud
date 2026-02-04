inherit "/d/Terel/mountains/goblincave/spells/flurry";
#include <ss_types.h>
 
public varargs int
config_spell(object caster, object *targets, string argument)
{  
    ::config_spell(caster, targets, argument);

    set_spell_element(SS_ELEMENT_WATER, 60);

    set_bolt_desc("ice");
    
    set_bolt_pen(800);

    return 0;
}