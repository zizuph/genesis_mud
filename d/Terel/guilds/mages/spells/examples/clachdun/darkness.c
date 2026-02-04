#include "spells.h"
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_INHERIT;

void
darkness(object caster, object *targets, int *resist, int result)
{
    setuid(); seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets,
      resist, result);
    caster->catch_tell("As you finish your pattern you invoke a billowing cloud "+
      "darkness which absorbs all light from the area.\n");
    tell_room(targets[0], QCTNAME(caster) +" finishes "+HIS_HER(caster)+
      " pattern a rolling mist of darkness which absorbs all traces of light.\n", caster);
}

void
create_darkness(object caster, object *targets, string args)
{
    config_default_spell();
    set_spell_mana(20);
    set_spell_task(TASK_SIMPLE);
    set_spell_time(2);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_effect(darkness);
    set_spell_object(SPELL_OBJ_DIR + "darkness");
}
