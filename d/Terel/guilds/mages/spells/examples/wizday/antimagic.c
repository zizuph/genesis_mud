#include "spells.h"
#include <macros.h>
#include <composite.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_LIB;
inherit SPELL_INHERIT;

void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    if (random(100) < resist[0] || 
      targets[0]->query_avatar_antimagic())
    {
	caster->catch_tell("Your spell fizzles into nothingness.\n");
	return;
    }

    caster->catch_tell("You finish tracing the runes for "+
      "displacement and imprissonment, creating an orb "+
      "which floats overhead of "+
      targets[0]->query_the_name(caster)+" which negates "+
      "all elemental protection on "+HIM_HER(targets[0])+".\n");
    targets[0]->catch_tell(caster->query_The_name(targets[0]) +
      " finishes completing "+HIS_HER(caster)+" pattern, summoning "+
      "a strange cystaline orb which floats above your head, making you "+
      "feel more vulnerable to elemental attacks.\n");
    caster->tell_watcher(QCTNAME(caster) + " finishes completing "+
      HIS_HER(caster) + " pattern, summoning a strange "+
      "crystaline orb which now floats above "+QTNAME(targets[0])+
      " head.\n", ({caster, targets[0]}));
    setuid(); seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets,
      resist, result);
}

int
config_spell(object caster, object *targets, string args)
{
    config_default_spell();

    set_spell_name("antimagic");
    set_spell_desc("Negate the magical protection of a living");
    set_spell_target(my_spell_target_one_valid_enemy);

    set_spell_time(8);
    set_spell_mana(70);
    set_spell_object(SPELL_OBJ_DIR + "antimagic");
    set_spell_form(SS_FORM_ABJURATION, 65);
    set_spell_element(SS_ELEMENT_EARTH, 80);

    // This spell is fairly easy to resist.
    set_spell_resist_task(TASK_ROUTINE + 150);
    set_spell_task(TASK_ROUTINE - 150);
    set_spell_resist(spell_resist);
    set_spell_offensive(1);
}
