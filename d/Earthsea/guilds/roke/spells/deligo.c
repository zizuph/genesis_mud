inherit "/d/Genesis/newmagic/spell";

#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>

#define ROKE_I_HAS_DELIGO "_roke_i_has_deligo"
#define DELIGO_OBJ "/d/Earthsea/guilds/roke/spells/deligo_obj"
#define DELIGO_DURATION 120.0
#define MANA_COST 50

public void
create_spell()
{
  set_spell_name("deligo");
  set_spell_desc("Bind target to slow its movement.");
  set_spell_target(spell_target_one_present_living);
  set_spell_time(3);
  set_spell_mana(MANA_COST);
  set_spell_task(TASK_ROUTINE);
  set_spell_resist_task(TASK_FORMIDABLE);
  set_spell_element(SS_ELEMENT_EARTH, 50);
  set_spell_form(SS_FORM_ENCHANTMENT, 40);
  set_spell_object(DELIGO_OBJ);
  set_spell_offensive(1);

  ::create_spell();
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
  object spell_obj;
  
  if (random(100) < resist[0])
    {
      caster->catch_msg("The spell is ineffective and fizzles away.\n");
      return;
    }
  if (caster->query_prop(ROKE_I_HAS_DELIGO))
    {
      caster->catch_msg(QCTNAME(targets[0]) + 
			" is already bound by your spell.\n");
      return;
    }
  setuid();
  seteuid(getuid());
  spell_obj = clone_object(DELIGO_OBJ);
  spell_obj->set_spell_effect_target(targets[0]);
  spell_obj->set_spell_effect_name(gSpell_name);
  spell_obj->set_spell_effect_desc("binding");
  spell_obj->set_spell_effect_element(gElement_skill);
  spell_obj->set_spell_effect_form(gForm_skill);
  spell_obj->set_spell_effect_power((caster->query_skill(gElement_skill) +
				     caster->query_skill(gForm_skill) + 
				     gElement_needed +
				     gForm_needed) / 4);
  spell_obj->set_spell_effect_caster(caster);
  spell_obj->set_slow((caster->query_skill(gElement_skill) +
		       caster->query_skill(gForm_skill)) / 4);
  spell_obj->set_duration(itof((caster->query_skill(gElement_skill) +
				caster->query_skill(gForm_skill))) / 
			  itof(gElement_needed + gForm_needed) * 
			  DELIGO_DURATION);
  spell_obj->move(targets[0]);
  spell_obj->setup_spell_effect();
  say(QCTNAME(caster) + " extends " + caster->query_possessive() + 
      " arm towards " + QTNAME(targets[0]) + " and " +
      targets[0]->query_pronoun() + 
      " visibly slows as if hindered by invisible ties.\n",
      targets);
  targets[0]->catch_msg(QCTNAME(caster) + " extends " + 
			caster->query_possessive() + 
			" arm towards you and " +
			"your movement slows as if hindered " +
			"by invisible ties.\n");
  caster->catch_msg("You extend your arm towards " + 
		    QTNAME(targets[0]) + " and " +
		    targets[0]->query_pronoun() + " visibly slows as " +
		    "your spell of binding takes effect.\n");
}
