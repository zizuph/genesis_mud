inherit "/d/Genesis/newmagic/spell";

#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>

#define CHANGING_OBJ "/d/Earthsea/guilds/roke/spells/altera_obj"
#define CHANGING_DURATION 900.0

public object *
spell_target_special(object caster, string str)
{
  object target, mimick;
  object *oblist = allocate(2);
  
  if (!strlen(str) || 
      !parse_command(str, all_inventory(caster) +
		     all_inventory(environment(caster)), 
		     "[at] / [on] [the] %o [into] %o", target,
		     mimick))
    {
      caster->catch_tell("What do you wish to cast changing on and into " +
			 "what?\n");
      return ({});
    }
  
  if (!objectp(target))
    {
      caster->catch_tell("Invalid target.\n");
      return ({});
    }
  if (!objectp(mimick))
    {
      caster->catch_tell("Invalid to change into.\n");
      return ({});
    }
  oblist[0] = target;
  oblist[1] = mimick;
  if (oblist[0] == oblist[1])
    {
      caster->catch_tell("The target and change target cannot be the same.\n");
      return ({});
    }
  return oblist;
}

public void
create_spell()
{
  set_spell_name("altera");
  set_spell_desc("Change a being or object into another being or object.");
  set_spell_target(spell_target_special);
  set_spell_time(4);
  set_spell_mana(200);
  set_spell_task(TASK_ROUTINE);
  set_spell_element(SS_ELEMENT_WATER, 60);
  set_spell_form(SS_FORM_ENCHANTMENT, 60);
  set_spell_object(CHANGING_OBJ);

  ::create_spell();
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
  object spell_obj;
  
  if (random(100) < resist[0])
    {
      caster->catch_tell("You complete the spell, but the spell of " +
			 "changing seems to " +
			 "have no effect.\n");
      return;
    }
  if (!objectp(targets[0]) ||
      !objectp(targets[1]))
    {
      caster->catch_tell("Something is horribly awry and the spell " +
			 "of changing does not take effect.\n");
      return;
    }
  setuid();
  seteuid(getuid());
  if (living(targets[0]))
    {
      if (targets[0] == caster)
	{
	  caster->catch_msg("Your spell of changing takes effect and " +
			    "you slowly mangles into ");
	}
      else
	{
	  caster->catch_msg("Your spell of changing takes effect and " +
			    QTNAME(targets[0]) + 
			    " slowly mangles into ");
	}
      tell_room(environment(caster),
		"Suddenly " + QTNAME(targets[0]) + " slowly mangles into ",
		({caster, targets[0]}));
      if (caster != targets[0])
	{
	  targets[0]->catch_msg("Suddenly you slowly mangles into ");
	}
    }
  else
    {
      caster->catch_msg("Your spell of changing takes effect and " +
			LANG_THESHORT(targets[0]) + 
			" slowly mangles into ");
      tell_room(environment(caster),
		"Suddenly " + LANG_THESHORT(targets[0]) + 
		" slowly mangles into ",
		caster);
    }

  if (living(targets[1]))
    {
      if (caster != targets[1])
	{
	  caster->catch_msg(QNAME(targets[1]) + ".\n");
	}
      tell_room(environment(caster),
		QNAME(targets[1]) + ".\n", 
		({caster, targets[1]}));
      targets[1]->catch_msg("you.\n");
    }
  else
    {
      caster->catch_msg(LANG_ASHORT(targets[1]) + ".\n");
      tell_room(environment(caster),
		LANG_ASHORT(targets[1]) + ".\n", caster);
    }
  spell_obj = clone_object(CHANGING_OBJ);
  spell_obj->set_spell_effect_target(targets[0]);
  spell_obj->set_spell_effect_name(gSpell_name);
  spell_obj->set_spell_effect_desc("transformation");
  spell_obj->set_spell_effect_element(gElement_skill);
  spell_obj->set_spell_effect_form(gForm_skill);
  spell_obj->set_spell_effect_power((caster->query_skill(gElement_skill) +
				     caster->query_skill(gForm_skill) + 
				     gElement_needed +
				     gForm_needed) / 4);
  spell_obj->set_spell_effect_caster(caster);
  if (!spell_obj->set_mimick(targets[1]))
    {
      caster->catch_tell("Something is horribly awry and the spell " +
			 "of changing does not take effect.\n");
      return;
    }
  spell_obj->set_duration(itof((caster->query_skill(gElement_skill) +
				caster->query_skill(gForm_skill))) / 
			  itof(gElement_needed + gForm_needed) * 
			  CHANGING_DURATION);
  spell_obj->setup_spell_effect();
}
