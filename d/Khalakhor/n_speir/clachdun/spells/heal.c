#include "spells.h"
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_INHERIT;

void
heal(object caster, object *targets, int *resist, int result)
{
    int skill;

    if (random(100) < resist[0])
    {
	caster->catch_tell(targets[0]->query_The_name(caster) +" resists your "+
	  "attempt to heal "+HIM_HER(targets[0])+".\n");
	return;
    }
    caster->catch_tell("You finish your weave and you feel yourself "+
      "engulfed by your own life energy... you can feel it tingling "+
      "upon your fingertips.  Glancing towards the wounded "+
      (targets[0]->notmet_me(caster) ? targets[0]->query_nonmet_name() :
	targets[0]->query_met_name()) +" you grasp "+
      HIS_HER(targets[0])+" shoulders releasing a part of your "+
      "life force within "+HIM_HER(targets[0])+".\n");
    targets[0]->catch_tell(caster->query_The_name(targets[0]) +
      " finishes "+HIS_HER(caster)+" intricate pattern and a soft "+
      "wonderous glow surrounds "+HIM_HER(caster)+".  "+
      capitalize(HE_SHE(caster))+" then turns and grasps your shoulders "+
      "making you feel healthier than before.\n");
    caster->tell_watchers(QCTNAME(caster)+" finishes "+HIS_HER(caster)+
      "intricate pattern and a soft wonderous glow surrounds "+
      HIM_HER(caster)+".  "+capitalize(HE_SHE(caster))+" then turns "+
      "and grasps "+LANG_POSS(QTNAME(targets[0]))+" shoulders "+
      "which transfers the glow to "+HIM_HER(targets[0])+
      ", which then fades quicky away leaving "+QTNAME(targets[0])+
      " healthier than before.\n", targets);
    skill = caster->query_skill(SS_ELEMENT_LIFE);
    caster->heal_hp(-skill);
    targets->heal_hp(skill * (3 + random(4)));
}

void
create_heal(object caster, object *targets, string args)
{
    config_default_spell();
    set_spell_mana(70);
    set_spell_time(10);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_element(SS_ELEMENT_LIFE, 50);
    set_spell_effect(heal);
    set_spell_resist(spell_resist_beneficial);
}
