#include "spells.h"
#include <composite.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_BOLT;
inherit SPELL_INHERIT;

void
desc_bolt_damage(object caster, object target, mixed *result)
{
    string how;

    switch (result[3])
    {
    case 0..50:
	how = "barely frostbitten";
	break;
    case 51..100:
	how = "slightly frostbitten";
	break;
    case 101..150:
	how = "somewhat frostbitten";
	break;
    case 151..200:
	how = "frostbitten";
	break;
    case 201..250:
	how = "very frostbitten";
	break;
    case 251..300:
	how = "extremely frostbitten";
	break;
    default:
	how = "chilled to the bone";
	break;
    }
    target->catch_tell("You feel " + how + " from the impact of the "+
      "ice bolt.\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
      how + " from the impact of the ice bolt.\n");
    if (caster->query_wiz_level())
	caster->catch_tell("DAMAGE:  "+result[3]+"\n");
    caster->tell_watcher(QCTNAME(target) + " appears " + how + 
      " from the impact of the cold bolt.\n",target);

}

void
desc_bolt_cast(object caster, object *targets)
{
    caster->catch_tell("You finish tracing the words for "+
      "bitter cold and destruction and conjure a bolt "+
      "of ice, which you hurl at "+FO_COMPOSITE_ALL_LIVE(targets, caster)+".\n");
    targets->catch_msg(QCTNAME(caster) +" finishes tracing "+
      HIS_HER(caster) + " pattern when a flaming blue orb appears "+
      "within "+HIS_HER(caster)+" hand.  Taking a firm grasp "+
      "on the orb "+HE_SHE(caster)+" takes aim at you and hurls "+
      "it in your direction.\n");
    caster->tell_watcher(QCTNAME(caster) +" finishes tracing "+
      HIS_HER(caster)+" pattern and a flaming blue orb appears within "+
      HIS_HER(caster)+" hand.  Taking a firm grasp of the orb "+
      HE_SHE(caster)+" then takes aim at "+QCOMPLIVE+" and hurls it in "+
      (sizeof(targets) > 1 ? "their" : HIS_HER(targets[0])) +
      " direction.\n", targets);
}

int
config_spell(object caster, object *targets, string arg)
{
    ::config_spell(caster, targets, arg);

    set_bolt_desc("ice");
    set_spell_target(my_spell_target_one_valid_enemy);

    config_default_spell();
    set_spell_time(6);
    set_spell_mana(85);
    set_spell_element(SS_ELEMENT_WATER, 60);
    set_spell_form(SS_FORM_CONJURATION, 75);
    set_bolt_pen(969);
    set_spell_resist(spell_resist_cold);
}

public int
try_to_hit(object caster, object target)
{
    // No chance to dodge this spell.
    return 1;
}
