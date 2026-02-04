#include "spells.h"
#include <composite.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_BOLT;
inherit SPELL_INHERIT;

public void
desc_bolt_cast(object caster, object *targets)
{
    caster->catch_tell("You finish tracing the words for "+
      "intense heat and flame, conjuring a wave of fire, which "+
      "you send out at "+FO_COMPOSITE_ALL_LIVE(targets, caster)+
      ".\n");
    targets->catch_msg(QCTNAME(caster) + " completes tracing "+
      HIS_HER(caster) + " pattern within the air and a blazing flame "+
      "surrounds "+HIM_HER(caster)+".  Suddenly the flame radiates outwards "+
      "at you as a massive wave of fire and destruction.\n");
    caster->tell_watcher(QCTNAME(caster) + " completes tracing "+
      HIS_HER(caster) + " pattern within the air and a blazing flame "+
      "surrounds "+HIM_HER(caster)+".  Suddenly the flame radiates outwards "+
      "towards "+QCOMPLIVE+" as a massive wave of fire and "+
      "destruction.\n", targets);
}

public void
desc_bolt_damage(object caster, object target, mixed *result)
{
    string how;

    switch (result[3])
    {
    case 0..60:
	how = "barely singed";
	break;
    case 61..125:
	how = "singed";
	break;
    case 126..200:
	how = "somewhat burnt";
	break;
    case 201..300:
	how = "burnt";
	break;
    case 301..425:
	how = "badly burnt";
	break;
    case 426..600:
	how = "horribly burnt";
	break;
    default:
	how = "nearly burnt to a crisp";
	break;
    }
    target->catch_tell("You feel "+how+" from the wave of flames.\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
      how + " from your wave of flames.\n");
    caster->tell_watcher(QCTNAME(target) + " appears " + how +
      " from the wave of flames.\n", target);
    if (caster->query_wiz_level())
	caster->catch_tell("DAMAGE:  " + result[3] + "\n");
}

int
config_spell(object caster, object *targets, string argument)
{
    ::config_spell(caster, targets, argument);
    config_default_spell();
    set_bolt_desc("fire");
    set_spell_name("flamewave");
    set_spell_desc("Summon a massive wave of flames at your enemies");
    set_spell_target(my_spell_target_non_team_members);

    set_spell_time(5);
    set_spell_mana(150);
    set_spell_element(SS_ELEMENT_FIRE, 75);
    set_spell_form(SS_FORM_CONJURATION, 90);
    set_bolt_pen(834);
    set_spell_resist(spell_resist);
    set_spell_offensive(1); 
}

public int
try_to_hit(object caster, object target)
{
    // No chance to dodge this spell
    return 1;
}
