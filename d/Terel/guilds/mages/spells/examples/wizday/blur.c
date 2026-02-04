#include "spells.h"
#include <macros.h>
#include <composite.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_LIB;
inherit SPELL_INHERIT;

void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    if (targets[0]->query_avatar_blured() || random(100) < resist[0])
    {
	caster->catch_tell("Your spell fizzles and fails to take form.\n");
	return;
    }
    caster->catch_tell("You finish focusing on the words of power for air "+
      "and protection.  With a simple gesture of your hand you place the "+
      "newly conjured barrier of air upon "+(targets[0] == caster ? "yourself"
	: targets[0]->query_the_name(caster))+".\n");
    if (caster != targets[0])
    {
	targets[0]->catch_tell(caster->query_The_name(targets[0]) +" finishes "+
	  "tracing "+HIS_HER(caster)+" pattern and with a simple "+
	  "gesture of "+HIS_HER(caster)+" hand a near invisible "+
	  "barrier of air surrounds you.\n");
    }
    tell_room(ENV(targets[0]), QCTNAME(caster) + " finishes "+
      "tracing "+HIS_HER(caster)+" pattern and with a simple "+
      "gesture of "+HIS_HER(caster)+" hand a near invisible "+
      "barrier of air surrounds "+
      (targets[0] == caster ? HIM_HER(caster) + "self" : QTNAME(targets[0]))
      +".\n", (({caster}) + targets));
    setuid(); seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets,
      resist, result);
}

int
config_spell(object caster, object *targets, string args)
{
    set_spell_name("blur");
    set_spell_desc("Distort ones image.");
    set_spell_target(spell_target_one_present_living);    

    config_default_spell();
    set_spell_mana(60);
    set_spell_time(4);
    set_spell_form(SS_FORM_CONJURATION, 50);
    set_spell_element(SS_ELEMENT_AIR, 60);
    set_spell_object(SPELL_OBJ_DIR + "blur");
    set_spell_resist(spell_resist_beneficial);
    return 0;
}
