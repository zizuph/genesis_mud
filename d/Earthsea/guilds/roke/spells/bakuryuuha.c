#include <ss_types.h>
#include <macros.h>
#include <formulas.h>

inherit "/d/Genesis/newmagic/spells/bolt";

#define MANA_COST 150
#define VORTEX_BASE_PEN 60

public object *
target_enemies_in_team(object caster, string str)
{
  object *a;
  object *result;
  object attack;
  int i, j;
  
  if (strlen(str))
    {
      result = spell_target_one_other_present_living(caster, str);
      if (!sizeof(result))
	{
	  return ({});
	}
    }
  else
    {
      attack = caster->query_attack();
      if (!objectp(attack))
	{
	  caster->catch_msg("Target enemies in who's team?\n");
	  return ({});
	}
      result = ({attack});
    }
  a = result & all_inventory(environment(caster));
  if (!sizeof(a))
    {
      caster->catch_msg("There are no enemies to cast the spell upon\n");
      return ({});
    }
  return a;
}

public void
create_bolt()
{
  set_spell_time(8);
  set_spell_mana(MANA_COST);
  set_spell_element(SS_ELEMENT_AIR, 75);
  set_spell_form(SS_FORM_CONJURATION, 55);
  set_spell_target(target_enemies_in_team);
  set_spell_name("bakuryuuha");
  set_spell_desc("Direct lacerating magewind vortices at a team of enemies.");
}

public varargs int
config_spell(object caster, object *targets, string arg)
{
  if (caster->query_npc())
    {
      set_spell_ingredients(0);
    }
  else
    {
      //set_spell_ingredients( ({ "sea kelp" }) );
      set_spell_ingredients(0);
    }
}

void
desc_bolt_damage(object caster, object target, mixed *result)
{
  int i, j;
  object *weps;
  string *exits;
  string *exit_cmds;

  switch(result[0])
    {
    case 0:
      caster->catch_msg(QCTNAME(target) + " seems unaffected by your " +
			"magewind.\n");
      target->catch_msg("You are unaffected by " + QTNAME(caster) +
			"'s magewind.\n");
      caster->tell_watcher(QCTNAME(target) + " seems unaffected by " +
			   QTNAME(caster) + "'s magewind.\n", target);
      break;
    case 1..5:
      caster->catch_msg(QCTNAME(target) + " seems mildly lacerated " +
			"by the howling burst of magewind.\n");
      target->catch_msg("You are mildly lacerated by the howling " +
			"burst of magewind.\n");
      caster->tell_watcher(QCTNAME(target) + " seems mildly lacerated " +
			   "by the howling burst of magewind.\n", target);
      break;
    case 6..10:
      caster->catch_msg("A vortex consumes " +
			QTNAME(target) + " and violently lacerates " +
			target->query_objective() + ".\n");
      target->catch_msg("A vortex consumes you and " +
			"violently lacerates you.\n");
      caster->tell_watcher("A vortex consumes " +
			   QTNAME(target) + " and violently lacerates " +
			   target->query_objective() + ".\n", target);
      break;
    case 11..20:
      caster->catch_msg("Shearing vortices strike " + QTNAME(target) +
			" and severely lacerate " + 
			target->query_objective() + ".\n");
      target->catch_msg("Shearing vortices strike you and severely " +
			"lacerate you.\n");
      caster->tell_watcher("Shearing vortices strike " + QTNAME(target) +
			   " and severely lacerate " + 
			   target->query_objective() + 
			   ".\n", target);
      break;
    case 21..40:      
      caster->catch_msg("Your burst of magewind shears at " +
			QTNAME(target) + " and nearly tears " +
			target->query_objective() + " apart.\n");
      target->catch_msg(QCTNAME(caster) + "'s burst of magewind shears at " +
			"you and nearly tears you apart.\n");
      caster->tell_watcher(QCTNAME(caster) + "'s burst of magewind " +
			   "shears at " + QTNAME(target) + 
			   " and nearly tears " +
			   target->query_objective() + " apart.\n", target);
      break;
    default:
      caster->catch_msg("Your powerful vortices " +
			"strip flesh away from " + QTNAME(target) +
			".\n");
      target->catch_msg(QCTNAME(caster) + "'s powerful vorticies " +
			"strip flesh away from you.\n");
      caster->tell_watcher(QCTNAME(caster) + "'s powerful " +
			   "vorticies strip flesh away from " +
			   QTNAME(target) + ".\n");
      break;
    }
  if (result[0] > 30 && !target->query_prop("_ranger_i_not_disarm"))
    {
      weps = target->query_weapon(-1);
      exits = environment(target)->query_exit_rooms();
      exit_cmds = environment(target)->query_exit_cmds();
      for (i = 0; i < sizeof(weps); i++)
	{
	  /* Chance for making the target's weapon fly to a random room */
	  if (random(result[0]) >= 30)
	    { 
	      target->unwield(weps[i]);
	      if (sizeof(exits))
		{
		  j = random(sizeof(exits));
		  weps[i]->move(exits[j]);
		  tell_room(exits[j], 
			    capitalize(LANG_ADDART(weps[i]->query_short())) +
			    " is carried in by a strong wind.\n");
		  target->catch_msg("You're forced to let go of your " +
				    weps[i]->query_short() +
				    " and the magewind carries " +
				    "it " + exit_cmds[j] + ".\n");
		  say(QCTNAME(target) + "lets go of " +
		      target->query_possessive() + " " +
		      weps[i]->query_short() + " and " +
		      "the magewind carries it " +
		      exit_cmds[j] + ".\n");
		}
	      else
		{
		  weps[i]->move(environment(target));
		  target->catch_msg("You're forced to let go of your " +
				    weps[i]->query_short() +
				    " and the magewind drops it " +
				    "on the ground.\n");
		  say(QCTNAME(target) + "lets go of " +
		      target->query_possessive() + " " +
		      weps[i]->query_short() + " and " +
		      "the magewind drops it " +
		      "on the ground.\n");
		}
	    }
	}
    }
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
  int i, pen;
  mixed hitresult;

  say("The air around you suddenly stirrs into action and " +
      "gather into violent vortices.\n");
  caster->catch_msg("You concentrate and stirr the air into violent " +
		    "vortices.\n");
  for (i = 0; i < sizeof(targets); i++)
    {
      pen = F_PENMOD(VORTEX_BASE_PEN + random(20), 
		     (caster->query_skill(SS_ELEMENT_AIR) +
		      caster->query_skill(SS_ELEMENT_WATER) +
		      caster->query_skill(SS_FORM_CONJURATION) +
		      caster->query_stat(SS_WIS) +
		      caster->query_stat(SS_INT)) / 4 +
		     (caster->query_npc() ? 100 : 
		      caster->query_skill(SS_OCCUP)));
      /* Modified by spellcraft */
      pen -= (100 - caster->query_skill(SS_SPELLCRAFT)) * pen / 100;
      pen -= targets[i]->query_magic_res(MAGIC_I_RES_AIR) * pen / 200;
      hitresult = do_bolt_damage(caster, targets[i], pen);
      desc_bolt_damage(caster, targets[i], hitresult);
      if (targets[i]->query_hp() <= 0)
	{
	  targets[i]->do_die(caster);
	}
    }
}
