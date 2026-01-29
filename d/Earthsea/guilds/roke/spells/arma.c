inherit "/d/Genesis/newmagic/spell";

#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>

#define ROKE_I_HAS_ARMA "_roke_i_has_arma"
#define ARMA_OBJ "/d/Earthsea/guilds/roke/spells/arma_obj"
#define ARMA_DURATION 420.0
/* Initial mana cost, you also pay 10 per minute */
#define MANA_COST 50

public void
create_spell()
{
  set_spell_name("arma");
  set_spell_desc("Create a globe of force enveloping you.");
  set_spell_target(spell_target_caster);
  set_spell_time(3);
  set_spell_mana(MANA_COST);
  set_spell_task(TASK_ROUTINE);
  set_spell_resist_task(TASK_FORMIDABLE);
  set_spell_element(SS_ELEMENT_AIR, 60);
  set_spell_form(SS_FORM_CONJURATION, 60);
  set_spell_object(ARMA_OBJ);

  ::create_spell();
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
  object spell_obj;
  
  if (random(100) < resist[0])
    {
      caster->catch_msg("You complete the spell, but the no enveloping " +
			"force materializes.\n");
      return;
    }
  if (caster->query_prop(ROKE_I_HAS_ARMA))
    {
      caster->catch_msg("You already have a globe of light " +
			"enveloping you.\n");
      return;
    }
  setuid();
  seteuid(getuid());
  spell_obj = clone_object(ARMA_OBJ);
  spell_obj->set_spell_effect_target(caster);
  spell_obj->set_spell_effect_name(gSpell_name);
  spell_obj->set_spell_effect_desc("globe of force");
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
			  ARMA_DURATION);
  spell_obj->set_ac((caster->query_skill(gElement_skill) +
		     caster->query_skill(gForm_skill) +
		     caster->query_stat(SS_INT) +
		     caster->query_stat(SS_WIS) +
		     (caster->query_npc() ? 100 : 
		      caster->query_skill(SS_OCCUP))) / 30);
  spell_obj->move(caster);
  spell_obj->setup_spell_effect();
  say(QCTNAME(caster) + " raises " + caster->query_possessive() + 
      " arm and a globe of light envelops " + 
      caster->query_objective() + ".\n");
  caster->catch_msg("You raise your arm and a globe of light envelops you.\n");
}
