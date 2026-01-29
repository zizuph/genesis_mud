/*
 * Ckrik 9/2003
 * Chain-lightning spell for the Wizards of Roke
 *
 */

inherit "/d/Genesis/newmagic/spells/bolt";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <formulas.h>

#define STUN_OBJECT "/d/Earthsea/lib/stun"
#define MAX_CHAINS 4
#define MANA_COST 50
#define FULMENATI_BASE_PEN 50

public object *
chain_lightning_target(object caster, string str)
{
  object *a;
  object *result;
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
      result = ({});
    }
  a = (object *)caster->query_enemy(-1) &
    all_inventory(environment(caster));
  if (sizeof(a))
    {
      for (i = sizeof(result); i < MAX_CHAINS; i++)
	{
	  j = random(sizeof(a));
	  if (sizeof(result) > 0)
	    {
	      /* No target can be hit twice consecutively */
	      if (result[sizeof(result) - 1] == a[j])
		{
		  continue;
		}
	    }
	  result += ({a[j]});
	}
    }
  if (!sizeof(result))
    {
      caster->catch_msg("There are no enemies to cast the spell upon\n");
      return ({});
    }
  return result;
}

public void
create_bolt()
{
  set_spell_time(7);
  set_spell_mana(MANA_COST);
  set_spell_task(TASK_ROUTINE);
  set_spell_element(SS_ELEMENT_AIR, 55);
  set_spell_form(SS_FORM_CONJURATION, 45);
  set_spell_target(chain_lightning_target);
  set_bolt_desc("lightning");
  set_spell_name("fulmenati");
  set_spell_desc("Summon lightning directed at target and arc to " +
		 "nearby enemies.");
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
      set_spell_ingredients( ({ "sea kelp" }) );
    }
}

public int
attempt_to_arc(int number)
{
  int i;
  int prob = 100;
  /* Lightning is impossible to dodge when first directed at target */
  for (i = 0; i < number; i++)
    {
      prob = prob * 3 / 4;
    }
  if (random(100) < prob)
    {
      return 1;
    }
  return 0;
}

void
desc_bolt_damage(object caster, object target, mixed *result)
{
  object stun;
  string damage;

  switch(result[0])
    {
    case 0:
      damage = "unaffected";
      break;
    case 1..3:
      damage = "mildly shocked";
      break;
    case 4..10:
      damage = "somewhat shocked";
      break;
    case 11..15:
      damage = "twitching uncontrollably";
      break;
    case 16..40:      
      damage = "smoldering heavily";
      break;
    default:
      damage = "glowing brightly";
      break;
    }
  caster->catch_msg("Your lightning bolt leaves " + QTNAME(target) +
		    " " + damage + ". ");
  target->catch_msg(QCTPNAME(caster) + " lightning bolt leaves you " +
		    damage + ". ");
  caster->tell_watcher(QCTPNAME(caster) + " lightning bolt leaves " +
		       QTNAME(target) +
		       " " + damage + ". ", target);
  /* Stun player */
  if (result[0] > 15 && target->query_hp() > 0)
    {
      setuid();
      seteuid(getuid());
      stun = clone_object(STUN_OBJECT);
      stun->move(target);
      stun->stun_player(result[0] / 2);
      switch(result[0])
	{
	case 16..30:
	  caster->catch_msg(capitalize(target->query_pronoun()) + 
			    " seems stunned.");
	  target->catch_msg("You are stunned.");
	  caster->tell_watcher(capitalize(target->query_pronoun()) + 
			       " seems stunned.",
			       target);
	  break;
	case 31..60:
	  caster->catch_msg(capitalize(target->query_pronoun()) + 
			    " seems rather stunned.");
	  target->catch_msg("You are rather stunned.");
	  caster->tell_watcher(capitalize(target->query_pronoun()) + 
			       " seems rather stunned.",
			       target);
	  break;
	default:
	  caster->catch_msg(capitalize(target->query_pronoun()) + 
			    " seems very stunned.");
	  target->catch_msg("You are very stunned.");
	  caster->tell_watcher(capitalize(target->query_pronoun()) + 
			       " seems very stunned.",
			       target);
	  break;
	}
    }
  caster->catch_msg("\n");
  target->catch_msg("\n");
  caster->tell_watcher("\n", target);
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
  int i, pen;
  mixed *hitresult;

  caster->catch_msg("You extend your arm towards " +
		    QTNAME(targets[0]) + 
		    " and a bolt of blue lightning shoots out " +
		    "from your fingers.\n");
  targets[0]->catch_msg(QCTNAME(caster) + " extends " +
			caster->query_possessive() + " arm towards you " +  
			"and a bolt of blue lightning shoots out " +
			"from " + caster->query_possessive() + " fingers.\n");
  caster->tell_watcher(QCTNAME(caster) + " extends " +
		       caster->query_possessive() + " arm towards " + 
		       QTNAME(targets[0]) + 
		       " and a bolt of blue lightning shoots out " +
		       "from " + caster->query_possessive() + " fingers.\n",
		       targets[0]);
  for (i = 0; i < sizeof(targets); i++)
    {
      if (!attempt_to_arc(i))
        {
	  caster->catch_msg("Your lightning bolt misses " + 
			    QTNAME(targets[i]) + ".\n");
	  targets[i]->catch_msg(QCTNAME(caster) + "'s lightning bolt misses " +
			       "you.\n");
	  caster->tell_watcher(QCTNAME(caster) + "'s lightning bolt misses " +
			       QTNAME(targets[i]) + ".\n",
			       targets[i]);
	  break;
	}
      pen = F_PENMOD(FULMENATI_BASE_PEN + random(15), 
		     caster->query_skill(SS_ELEMENT_AIR) +
		     caster->query_skill(SS_FORM_CONJURATION) +
		     (caster->query_npc() ? 100 : 
		      caster->query_skill(SS_OCCUP)));
      /* Modified by spellcraft */
      pen -= (100 - caster->query_skill(SS_SPELLCRAFT)) * pen / 100;
      pen -= targets[i]->query_magic_res(MAGIC_I_RES_ELECTRICITY) * pen / 100;
      hitresult = do_bolt_damage(caster, targets[i], pen);
      desc_bolt_damage(caster, targets[i], hitresult);
      if (targets[i]->query_hp() <= 0)
	{
	  targets[i]->do_die(caster);
	}
      if (i < sizeof(targets) - 1)
	{
	  caster->catch_msg("The lightning bolt arcs towards " +
			    QTNAME(targets[i+1]) + ".\n");
	  targets[i+1]->catch_msg("The lightning bolt arcs towards " +
				  "you.\n");
	  caster->tell_watcher("The lightning bolt arcs towards " +
			       QTNAME(targets[i+1]) + ".\n",
			       targets[i+1]);
	}
    }
}

