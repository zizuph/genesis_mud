inherit "/d/Ansalon/guild/dknights/spells/bolt_std"; 

#include <ss_types.h> 

public varargs int 
config_spell(object caster, object *targets, string argument) 
{ 
    ::config_spell(caster, targets, argument); 

    set_spell_element(SS_ELEMENT_FIRE, 0); 
    set_bolt_pen(800); 
    set_bolt_desc("fire"); 
    return 0; 
}

