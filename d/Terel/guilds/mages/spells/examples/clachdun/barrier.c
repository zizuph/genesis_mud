#include "spells.h"
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_INHERIT;

void
barrier(object caster, object *targets, int *resist, int result)
{
    setuid(); seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets,
      resist, result);
    // The object takes care of the messages
}

void
create_barrier(object caster, object *targets, string args)
{
    config_default_spell();
    set_spell_mana(100);
    set_spell_time(2);
    set_spell_form(SS_FORM_CONJURATION, 70);
    set_spell_element(SS_ELEMENT_WATER, 50);
    set_spell_effect(barrier);
    set_spell_object(SPELL_OBJ_DIR + "barrier");

}
