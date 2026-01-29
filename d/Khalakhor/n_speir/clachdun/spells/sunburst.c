#include "spells.h"
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_INHERIT;

void
sunburst(object caster, object *targets, int *resist, int result)
{
    setuid(); seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets,
      resist, result);
    caster->catch_tell("You finish your spell pattern and a tiny orb "+
      "appears within your hand.  You then complete the spell by "+
      "throwing the orb on the ground where it explodes in a flash of "+
      "brilliant light, leaving behind a blazing fire "+
      "which burns as brightly as the sun.\n");
    tell_room(targets[0], QCTNAME(caster) +" finishes "+HIS_HER(caster)+
      "  pattern and tiny orb appears within "+HIS_HER(caster)+" hand.  "+
      capitalize(HE_SHE(caster))+" then throws the orb at the ground "+
      "where it explodes in a flash a brilliant light, leaving behind a fire "+
      "which blazes as brightly as the sun.\n", caster);
}

void
create_sunburst(object caster, object *targets, string args)
{
    config_default_spell();
    set_spell_mana(20);
    set_spell_task(TASK_SIMPLE);
    set_spell_time(2);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_element(SS_ELEMENT_FIRE, 30);
    set_spell_effect(sunburst);
    set_spell_object(SPELL_OBJ_DIR + "sunburst");
}
