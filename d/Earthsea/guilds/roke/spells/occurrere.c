inherit "/d/Genesis/newmagic/spell";

#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>

#define COUNTER_OBJ "/d/Earthsea/guilds/roke/spells/occurrere_obj"
#define COUNTER_DURATION 600.0

public void
create_spell()
{
  set_spell_name("occurrere");
  set_spell_desc("Counter spell that temporarily strips target of " +
		 "magic.");
  set_spell_target(spell_target_one_other_present_living);
  set_spell_time(6);
  set_spell_mana(300);
  set_spell_task(TASK_DIFFICULT);
  set_spell_resist_task(TASK_DIFFICULT);
  set_spell_element(SS_ELEMENT_WATER, 80);
  set_spell_form(SS_FORM_ABJURATION, 80);
  set_spell_object(COUNTER_OBJ);
  set_spell_offensive(1);

  ::create_spell();
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
  object spell_obj;
  
  if (random(100) < resist[0])
    {
      caster->catch_msg("You complete the spell, but the " +
			"counter-spell seems to " +
			"have no effect.\n");
      return;
    }
  setuid();
  seteuid(getuid());
  spell_obj = clone_object(COUNTER_OBJ);
  spell_obj->set_spell_effect_target(targets[0]);
  spell_obj->set_spell_effect_name(gSpell_name);
  spell_obj->set_spell_effect_desc("counter spell");
  spell_obj->set_spell_effect_element(gElement_skill);
  spell_obj->set_spell_effect_form(gForm_skill);
  spell_obj->set_spell_effect_power((caster->query_skill(gElement_skill) +
				     caster->query_skill(gForm_skill) + 
				     gElement_needed +
				     gForm_needed) / 4);
  spell_obj->set_spell_effect_caster(caster);
  spell_obj->set_duration(itof((caster->query_skill(gElement_skill) +
				caster->query_skill(gForm_skill))) / 
			  itof(gElement_needed + gForm_needed) * 
			  COUNTER_DURATION);
  spell_obj->setup_spell_effect();
  tell_room(environment(caster), 
	    "The magical powers of " + QTNAME(targets[0]) +
	    " seems to fizzle away.\n", targets[0]);
  targets[0]->catch_msg("Your magical powers fizzle away.\n");
}
