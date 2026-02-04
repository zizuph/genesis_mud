#include "spells.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>

inherit "/d/Genesis/newmagic/spells/jolt";
inherit SPELL_INHERIT;

public int
config_spell(object caster, object *targets, string args)
{
    config_default_spell();
    ::config_spell(caster, targets, args);

    set_spell_name("jolt");
    set_spell_desc("Distrupt anothers casting of a spell");
    set_spell_target(my_spell_target_one_valid_enemy);

    set_spell_mana(65);
    set_spell_element(SS_ELEMENT_DEATH, 60);
    set_spell_form(SS_FORM_ABJURATION, 60);
    set_spell_offensive(1);

    return 0;
}

void
desc_casting(object caster, object *targets)
{
    caster->catch_tell("You complete your tracing of the runes for "+
      "disruption and death, focusing your magic into "+
      targets[0]->query_the_possesive_name(caster)+" body, in an "+
      "attempt to break "+HIS_HER(targets[0])+" concentraition.\n");
    targets[0]->catch_tell(caster->query_the_name(targets[0])+
      " finishes "+HIS_HER(caster)+" pattern, then reaches towards you!  "+
      "A strange pluse of energy flows through your body, "+
      "leaving you with a tingling sensation throughout your body.\n");
    caster->tell_watcher(QCTNAME(caster) + " finishes "+
      " tracing "+HIS_HER(caster)+" pattern, then reaches towards "+
      QTNAME(targets[0])+", sending a tiny spark of energy "+
      "through "+HIM_HER(targets[0])+".\n", targets);
}
