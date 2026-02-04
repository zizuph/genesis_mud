#include "spells.h"
#include <macros.h>
#include <composite.h>
#include "/d/Terel/include/Terel.h"

inherit SPELL_LIB;
inherit SPELL_INHERIT;

void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    /*
    if (random(100) < resist[0] || 
      targets[0]->query_mage_antimagic())
    {
	caster->catch_tell("Your spell fizzles into nothingness.\n");
	return;
    }
*/
    caster->catch_tell("You finish tracing the runes for "+
      "displacement and imprisonment casting a complex web of "+
      "sparkling light over " +
      targets[0]->query_the_name(caster)+" which negates "+
      "all elemental protection on "+HIM_HER(targets[0])+".\n");
    targets[0]->catch_tell(caster->query_The_name(targets[0]) +
      " finishes completing "+HIS_HER(caster)+" pattern, "+
      "covering you in a complex sparkling web of white light, making you "+
      "feel more vulnerable to elemental attacks.\n");
    caster->tell_watcher(QCTNAME(caster) + " finishes completing "+
      HIS_HER(caster) + " pattern, forming a complex sparkling web over "+QTNAME(targets[0])+
      ".\n", ({caster, targets[0]}));
    
    setuid(); seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets,
      resist, result);
}


int
config_spell(object caster, object *targets, string args)
{

    set_spell_name("static");
    set_spell_desc("Negate the magical protection of a living");
    set_spell_target(spell_target_one_present_living);

    set_spell_time(5);
    set_spell_mana(50);
    set_spell_object(SPELL_OBJ_DIR + "static");
    set_spell_form(SS_FORM_ABJURATION, 65);
    set_spell_element(SS_ELEMENT_AIR, 80);

    // This spell is fairly easy to resist.
 //   set_spell_resist_task(TASK_ROUTINE + 150);
 //   set_spell_task(TASK_ROUTINE - 150);
    set_spell_resist(spell_resist);
    set_spell_offensive(1);
}

