inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

#define _DEBUG 1


#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <state_desc.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <state_desc.h>
#include <living_desc.h>

static object mimicked;
static int target_is_living = 0;
static int str_extra;
static int dex_extra;
static int con_extra;
static int *aids;
static int *hids;
static int *m_aids;
static int *m_hids;
static string presentation;
static string saved_short;
static int have_to_reset = 0;
static float duration = 120.0;

#if _DEBUG
object wiz = find_player("ckrik");
#endif

varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
  /* Cache a copy of the title of the target if it's living
   */
  if (living(spell_target))
    {
      presentation = spell_target->query_presentation();
    }
  /* Cache a copy of the short
   */
  if (living(spell_target))
    {
      saved_short = spell_target->query_nonmet_name();
    }
  else
    {
      saved_short = spell_target->short();
    }

  if (!shadow_me(spell_target))
    {
#if _DEBUG
      spell_target->catch_msg("Your spell failed, cannot shadow.\n");
#endif
      return 0;
    }
  spell_target->add_prop(LIVE_I_NEVERKNOWN,
			 spell_target->query_prop(LIVE_I_NEVERKNOWN) + 1);
  set_alarm(duration, 0.0, dispel_spell_effect);
  return 1;
}

public void set_duration(float sec)
{
  duration = sec;
}

public int set_mimick(object target)
{
  int i, to_alter;
  object tcombat;
  object mcombat;
  mixed *data;
  object *effects;

  if (shadow_double("/d/Earthsea/guilds/roke/spells/altera_obj",
		    spell_target))
    {
      /* Dispel the old one before we let another take effect */
      effects = spell_target->query_magic_effects();
      for (i = 0; i < sizeof(effects); i++)
	{
	  if (effects[i]->query_spell_effect_name() == "altera" &&
	      effects[i] != this_object())
	    {
	      effects[i]->dispel_spell_effect(this_object());
	      break;
	    }
	}
    }
  mimicked = target;
  
  /* Copy physical attributes if both mimicked and target
   * are living.
   */
  if (living(mimicked) && living(spell_target))
    {
      /* Affect only physical attributes */
      str_extra = mimicked->query_stat(SS_STR) -
	spell_target->query_stat(SS_STR) + 
	spell_target->query_stat_extra(SS_STR);
      spell_target->set_stat_extra(SS_STR, str_extra);
      dex_extra = mimicked->query_stat(SS_DEX) -
	spell_target->query_stat(SS_DEX) +
	spell_target->query_stat_extra(SS_DEX);
      spell_target->set_stat_extra(SS_DEX, dex_extra);
      con_extra = mimicked->query_stat(SS_CON) -
	spell_target->query_stat(SS_CON) +
	spell_target->query_stat_extra(SS_CON);
      spell_target->set_stat_extra(SS_CON, con_extra);
      /* Handle transformations for
       *
       * humanoid --> non-humanoid
       * non-humanoid --> non-humanoid
       * non-humanoid --> humanoid 
       */
      if (!mimicked->query_humanoid()  ||
	  (mimicked->query_humanoid() && !spell_target->query_humanoid()))
	{  
	  have_to_reset = 1;
	  if (spell_target->query_humanoid())
	    {
	      spell_target->command("unwield all");
	      /* Check for stuck weapons, if anything's stuck
	       * fail the spell
	       */
	      if (sizeof(spell_target->query_weapon(-1)))
		{
#if _DEBUG
		  spell_target->catch_msg("Your spell fails, cannot " +
					  "unwield.\n");
#endif
					
		  dispel_spell_effect();
		  return 0;
		}
	      spell_target->command("remove all");
	      /* Check for stuck armours as well
	       */
	      if (sizeof(spell_target->query_armour(-1)))
		{
#if _DEBUG
		  spell_target->catch_msg("Your spell fails, cannot " +
					  "remove armour.\n");
#endif
		  dispel_spell_effect();
		  return 0;
		}
	    }
	  /* Fun stuff here
	   * Alter the attack and hitloc to look and feel the same
	   * as the mimick
	   */
	  /* Save all the previous hitlocs and attacks */
	  tcombat = spell_target->query_combat_object();
	  aids = tcombat->query_attack_id();
	  hids = tcombat->query_hitloc_id();
	  mcombat = mimicked->query_combat_object();
	  m_aids = mcombat->query_attack_id();
	  m_hids = mcombat->query_hitloc_id();
	  /* Warning: Begin ugly HACK!!!!---------------------------> */
	  if (spell_target->query_combat_file() == 
	      "/std/combat/chumlock" ||
	      spell_target->query_combat_file() ==
	      "/std/combat/chumanoid")
	    {
	      /* Since players are locked, just recycle the
	       * aids and hids and alter the look and feel
	       * We'll also restrict to unarmed combat
	       * elsewhere by masking wield() and wear()
	       */
	      for (i = 0; i < sizeof(aids) && i < sizeof(m_aids); i++)
		{
		  data = mcombat->query_attack(m_aids[i]);
		  if (sizeof(data) >= 4)
		    {
		      /* We use the target's unarmed skill
		       * because this spell only recreates
		       * the targets physical attributes
		       * and not the mental and knowledge
		       * attributes
		       */
		      tcombat->cb_add_attack(data[0], data[1], data[2], 
			      data[3], aids[i],
			      spell_target->query_skill(SS_UNARM_COMBAT));
		    }
		  else
		    {
		      /* Serious bug here */
		      /* Fix me: Log this */
		      spell_target->catch_msg("You've encountered a " +
					      "critical bug, " +
					      "please contact an Earthsea " +
					      "wizard or write a bug " +
					      "report.\n");
#if _DEBUG
		      spell_target->catch_msg("Exit at altering attack\n");
#endif
		      dispel_spell_effect();
		      return 0;
		    }
		}
	      /* Disable all extra attacks for now */
	      for (;i < sizeof(aids); i++)
		{
		  data = tcombat->query_attack(aids[i]);
		  if (sizeof(data) >= 4)
		    {
		      tcombat->cb_add_attack(data[0], data[1], data[2],
					     0, aids[i],
					     data[4]);
		    }
		  else
		    {
		      /* Serious bug here */
		      /* Fix me: Log this */
		      spell_target->catch_msg("You've encountered a " +
					      "critical bug, " +
					      "please contact an Earthsea " +
					      "wizard or write a bug " +
					      "report.\n");
#if _DEBUG
		      spell_target->catch_msg("Exit at disabling attack\n");
#endif
		      dispel_spell_effect();
		      return 0;
		    }
		}
	      /* Alter the hit locations */
	      for (i = 0; i < sizeof(hids) && i < sizeof(m_hids); i++)
		{
		  data = mcombat->query_hitloc(m_hids[i]);
		  if (sizeof(data) >= 3)
		    {
		      tcombat->cb_add_hitloc(data[0], data[1], data[2], 
					     hids[i]);
		    }
		  else
		    {
		      /* Serious bug here */
		      /* Fix me: Log this */
		      spell_target->catch_msg("You've encountered a " +
					      "critical bug, " +
					      "please contact an Earthsea " +
					      "wizard or write a bug " +
					      "report.\n");
		      dispel_spell_effect();
#if _DEBUG
		      spell_target->catch_msg("Exit at altering hitlocs\n");
#endif
		      return 0;
		    }
		}
	      /* Disable all extra hit locations for now */
	      for (;i < sizeof(hids); i++)
		{
		  data = tcombat->query_hitloc(hids[i]);
		  if (sizeof(data) >= 3)
		    {
		      tcombat->cb_add_hitloc(data[0], 0, "disabled hitloc",
					     hids[i]);
		    }
		  else
		    {
		      /* Serious bug here */
		      /* Fix me: Log this */
		      spell_target->catch_msg("You've encountered a " +
					      "critical bug, " +
					      "please contact an Earthsea " +
					      "wizard or write a bug " +
					      "report.\n");
#if _DEBUG
		      spell_target->catch_msg("Exit at disabling hitlocs\n");
#endif
		      dispel_spell_effect();
		      return 0;
		    }
		}
	    }
	  /* Warning: End ugly HACK!!!! -------------------------------> */
	  else
	    {
	      /* Target is not a player or locked, we can do as we
	       * wish...hehe
	       */
	      /* Remove all attacks */
	      for (i = 0; i < sizeof(aids); i++)
		{
		  tcombat->cb_remove_attack(aids[i]);
		}
	      for (i = 0; i < sizeof(m_aids); i++)
		{
		  data = mcombat->query_attack(m_aids[i]);
		  if (sizeof(data) >= 4)
		    {
		      /* We use the target's unarmed skill
		       * because this spell only recreates
		       * the targets physical attributes
		       * and not the mental attributes
		       */
		      tcombat->cb_add_attack(data[0], data[1], data[2], 
			    data[3], m_aids[i],
			    spell_target->query_skill(SS_UNARM_COMBAT));
		    }
		  else
		    {
		      /* Serious bug here */
		      /* Fix me: Log this */
		      spell_target->catch_msg("You've encountered a " +
					      "critical bug, " +
					      "please contact an Earthsea " +
					      "wizard or write a bug " +
					      "report.\n");
#if _DEBUG
		      spell_target->catch_msg("Exit at adding attack\n");
#endif
		      dispel_spell_effect();
		      return 0;
		    }
		}
	      /* Remove the hit locations */
	      for (i = 0; i < sizeof(hids); i++)
		{
		  tcombat->cb_remove_hitloc(hids[i]);
		}
	      for (i = 0; i < sizeof(m_hids); i++)
		{
		  data = mcombat->query_hitloc(m_hids[i]);
		  if (sizeof(data) >= 3)
		    {
		      tcombat->cb_add_hitloc(data[0], data[1], data[2], 
					     m_hids[i]);
		    }
		  else
		    {
		      /* Serious bug here */
		      /* Fix me: Log this */
		      spell_target->catch_msg("You've encountered a " +
					      "critical bug, " +
					      "please contact an Earthsea " +
					      "wizard or write a bug " +
					      "report.\n");
#if _DEBUG
		      spell_target->catch_msg("Exit at adding hitloc\n");
#endif
		      dispel_spell_effect();
		      return 0;
		    }
		}
	    }
	}
    }
  return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
  int i;
  object tcombat;

  if (!shadow_who)
    {
      remove_spell_effect_object();
      return 1;
    }
  if (dispeller->query_spell_effect_name() != "altera")
    {
      shadow_who->catch_msg("The spell of changing fades.\n");
      if (objectp(mimicked))
	{
	  tell_room(environment(shadow_who), 
		    capitalize(LANG_ADDART(saved_short)) + 
		    " emerges from the mangled form of " + 
		    "the " + mimicked->query_nonmet_name() + 
		    ".\n", shadow_who);
	}
      else
	{
	  tell_room(environment(shadow_who), 
		    capitalize(LANG_ADDART(saved_short)) + 
		    " emerges from the mangled form of " +
		    "a non-descript ooze.\n", shadow_who);
	}
    }
  shadow_who->set_stat_extra(SS_STR, 
			       shadow_who->query_stat_extra(SS_STR) -
			       str_extra);
  shadow_who->set_stat_extra(SS_DEX, 
			       shadow_who->query_stat_extra(SS_DEX) - 
			       dex_extra);
  shadow_who->set_stat_extra(SS_CON,
			       shadow_who->query_stat_extra(SS_CON) -
			       con_extra);
  /* Restore hitlocs and attack to previous state */
  if (have_to_reset)
    {
      if (shadow_who->query_combat_file() != "/std/combat/chumlock" &&
	  shadow_who->query_combat_file() != "/std/combat/chumanoid")
	{
	  tcombat = shadow_who->query_combat_object();
	  for (i = 0; i < sizeof(m_aids); i++)
	    {
	      tcombat->cb_remove_attack(m_aids[i]);
	    }
	  for (i = 0; i < sizeof(m_hids); i++)
	    {
	      tcombat->cb_remove_hitloc(m_hids[i]);
	    }
	}
      for (i = 0; i < sizeof(aids); i++)
	{
	  shadow_who->cr_reset_attack(aids[i]);
	}
      for (i = 0; i < sizeof(hids); i++)
	{
	  shadow_who->cr_reset_hitloc(hids[i]);
	}
    }
  if (shadow_who->query_prop(LIVE_I_NEVERKNOWN) > 1)
    {
      shadow_who->add_prop(LIVE_I_NEVERKNOWN,
			   shadow_who->query_prop(LIVE_I_NEVERKNOWN) - 1);
    }
  else
    {
      shadow_who->remove_prop(LIVE_I_NEVERKNOWN);
    }
  remove_spell_effect_object();
  return 1;
}

/***** Shadows for description related functions *****/

public varargs string short(object target)
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return "";
    }
  if (living(mimicked))
    {
      return mimicked->query_nonmet_name();
    }
  else
    {
      return mimicked->short();
    }
}

public varargs string plural_short(object for_obj)
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return "";
    }
  return mimicked->plural_short(for_obj);
}

public varargs string
long(mixed for_obj)
{
  string res, text;
  object eob;
  string *sublocs;
  int i;
  
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return "";
    }
  if (!living(mimicked))
    {
      return mimicked->long(0, for_obj);
    }

  if (!objectp(for_obj))
    {
      for_obj = this_player();
    }
  
  if (for_obj == shadow_who)
    {
      res = "You are " + LANG_ADDART(mimicked->query_nonmet_name()) +  
	", presenting yourself as:\n" + presentation + ".\n";
      text = mimicked->query_long();
      if (strlen(text))
	{
	  res += text;
	}
    }
  else
    {
      res = mimicked->query_long();
      if (!stringp(res) &&
	  !functionp(res))
        {
	  if (!(mimicked->short(for_obj)))
	    return "";
	  else
	    res =  capitalize((string)mimicked->query_pronoun()) + " is " +
	      LANG_ADDART(mimicked->query_nonmet_name()) + ".\n";
	  if (mimicked->query_ghost())
            {
	      if (mimicked->notmet_me(for_obj))
		return LD_NONMET_GHOST(mimicked);
            }
        }
    }
  res += mimicked->show_scar(for_obj);
  /*
  res += shadow_who->show_sublocs(for_obj);
  */
  /* Fix me: for health, width/height sublocs */

  sublocs = mimicked->query_sublocs();
  for (i = 0; i < sizeof(sublocs); i++)
    {
      switch(sublocs[i])
	{
	case "_soul_cmd_extra":
	  text = shadow_who->query_prop(LIVE_S_SOULEXTRA);
	  if (strlen(text))
	    {
	      res += (((for_obj == shadow_who) ? "You are " :
		       (capitalize(mimicked->query_pronoun()) + " is ")) + 
		      text + ".\n");
	    }
	  break;
	case "_subloc_misc_extra":
	  eob = mimicked->query_subloc_obj("_subloc_misc_extra");
	  text = eob->show_subloc_size(mimicked, for_obj);
	  if (strlen(text))
	    {
	      res += ((for_obj == shadow_who) ? "You are" :
		      (capitalize(mimicked->query_pronoun()) + " is")) +
		text;
	    }
	  if (for_obj == shadow_who)
	    {
	      /* First person */
	      text = eob->show_subloc_looks(mimicked, mimicked);
	    }
	  else
	    {
	      /* Third person */
	      text = eob->show_subloc_looks(mimicked, shadow_who);
	    }
	  if (strlen(text))
	    {
	      res += text;
	    }
	  eob = shadow_who->query_subloc_obj("_subloc_misc_extra");
	  if (shadow_who->query_attack())
	    {
	      text = eob->show_subloc_fights(shadow_who, for_obj);
	      if (strlen(text))
		{
		  res += (((for_obj == shadow_who) ? "You are" :
			   (capitalize(mimicked->query_pronoun()) + " is")) + 
			  text);
		}
	    }
	  text = eob->show_subloc_health(shadow_who, for_obj);
	  if (strlen(text))
	    {
	      res += (((for_obj == shadow_who) ? "You are " :
		       (capitalize(mimicked->query_pronoun()) + 
			" seems to be ")) + 
		      text + ".\n");
	    }
	  break;
	case "wielded":
	case "worn_a":
	case "held":
#if _DEBUG_X
	  res += ">> " + sublocs[i] + " << ";
#endif
	  eob = shadow_who->query_subloc_obj(sublocs[i]);
	  res += eob->show_subloc(sublocs[i], shadow_who,
				  for_obj);
	  break;
	default:
	  eob = mimicked->query_subloc_obj(sublocs[i]);
	  if (shadow_who == for_obj)
	    {
	      /* First person */
	      res += eob->show_subloc(sublocs[i], mimicked, mimicked);
	    }
	  else
	    {
	      /* This alway be in third person */
	      res += eob->show_subloc(sublocs[i], mimicked, shadow_who);
	    }
	  break;
	}
    }

  return res;
}

public varargs mixed query_name(int arg)
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return;
    }
  if (!living(mimicked))
    {
      return "The " + mimicked->short();
    }
  if (arg)
    {
      return mimicked->query_real_name();
    }
  else
    {
      return mimicked->query_name();
    }
}

public string query_met_name()
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return "";
    }
  if (!living(mimicked))
    {
      return "the " + mimicked->short();
    }
  return mimicked->query_nonmet_name();
}

public string query_nonmet_name()
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return "";
    }
  if (!living(mimicked))
    {
      return "the " + mimicked->short();
    }
  return mimicked->query_nonmet_name();
}

public string query_Met_name()
{
  return capitalize(query_met_name());
}

public varargs string
query_art_name(object pobj)
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return "";
    }
  return LANG_ART(mimicked->short(pobj));
}

public varargs string
query_Art_name(object pobj)
{
  string desc = query_art_name(pobj);
  
  /* Capitalize the right character if the description starts with ( or [. */
  if (wildmatch("[\\[(]*", desc))
    {
      return desc[..0] + capitalize(desc[1..]);
    }
  
  return capitalize(desc);
}

public varargs string
query_art_possessive_name(object pobj)
{
  return LANG_POSS(query_art_name(pobj));
}

public varargs string
query_Art_possessive_name(object pobj)
{
  return LANG_POSS(query_Art_name(pobj));
}
public varargs string
query_the_name(object pobj)
{
  string pre = "", aft = "";
  
  if (!objectp(pobj))
    pobj = previous_object(-1);
  
  if (!CAN_SEE(pobj, shadow_who) || !CAN_SEE_IN_ROOM(pobj))
    return LD_SOMEONE;
  if (shadow_who->query_prop(OBJ_I_HIDE))
    {
      pre = "[";
      aft = "]";
    }
  if (shadow_who->query_prop(OBJ_I_INVIS))
    {
      pre = "(";
      aft = ")";
    }
 
  if (shadow_who->notmet_me(pobj))
    return pre + LD_THE + " " + query_nonmet_name() + aft;
  else
    return pre + query_met_name() + aft;
}

public varargs string
query_The_name(object pobj)
{
  string desc = query_the_name(pobj);
  
  /* Capitalize the right character if the description starts with ( or [. */
  if (wildmatch("[\\[(]*", desc))
    {
      return desc[..0] + capitalize(desc[1..]);
    }
  
  return capitalize(desc);
}

public varargs string
query_the_possessive_name(object pobj)
{
    return LANG_POSS(query_the_name(pobj));
}

public varargs string
query_The_possessive_name(object pobj)
{
    return LANG_POSS(query_The_name(pobj));
}

public varargs mixed query_adj(int arg)
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return "";
    }
  return mimicked->query_adj();
}

public string query_presentation()
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return "";
    }

  return presentation;
}

public int query_humanoid()
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return 0;
    }
  if (living(mimicked))
    {
      return mimicked->query_humanoid();
    }
  return shadow_who->query_humanoid();
}


public int query_gender()
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return 0;
    }
  if (living(mimicked))
    {
      return mimicked->query_gender();
    }
  return 2;
}

public string
query_gender_string()
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return 0;
    }
  if (living(mimicked))
    {
      return mimicked->query_gender_string();
    }
  return "neuter";
}

public string
query_pronoun()
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return 0;
    }
  if (living(mimicked))
    {
      return mimicked->query_pronoun();
    }
  return "it";
}

public string
query_possessive()
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return 0;
    }
  if (living(mimicked))
    {
      return mimicked->query_possessive();
    }
  return "it's";
}

public string
query_objective()
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return 0;
    }
  if (living(mimicked))
    {
      return mimicked->query_objective();
    }
  return "it";
}

public int
notmet_me(object obj)
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return 0;
    }
  return 1;
}

public void
appraise_object(int num)
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return;
    }
  write("\n" + long(this_player()) + "\n");
  write("You estimate the weight is about " +
      shadow_who->appraise_weight(num) + "\n");
}

/***** Shadows for object manipulation by foreign object ******/
public string *
parse_command_id_list()
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return ({});
    }
  return mimicked->parse_command_id_list();
}

public string *
parse_command_plural_id_list()
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return ({});
    }
  return mimicked->parse_command_plural_id_list();
}

public string *
parse_command_adjectiv_id_list()
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return ({});
    }
  return mimicked->parse_command_adjectiv_id_list();
}
/***** Changes for movement *****/


/***** Changes for combat *****/
public string
cr_attack_desc(int aid)
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return "";
    }
  /* Humanoids */
  if ((shadow_who->query_combat_file() == 
       "/std/combat/chumlock" ||
       shadow_who->query_combat_file() ==
       "/std/combat/chumanoid") && living(mimicked) &&
      !mimicked->query_humanoid())
    {
      switch(aid)
	{
	case W_RIGHT:
	  if (sizeof(m_aids) > 0)
	    {
	      return mimicked->cr_attack_desc(m_aids[0]);
	    }
	  break;
	case W_LEFT:
	  if (sizeof(m_aids) > 1)
	    {
	      return mimicked->cr_attack_desc(m_aids[1]);
	    }
	  break;
	case W_BOTH:
	  if (sizeof(m_aids) > 2)
	    {
	      return mimicked->cr_attack_desc(m_aids[2]);
	    }
	  break;
	case W_FOOTR:
	  if (sizeof(m_aids) > 3)
	    {
	      return mimicked->cr_attack_desc(m_aids[3]);
	    }
	  break;
	case W_FOOTL:
	  if (sizeof(m_aids) > 4)
	    {
	      return mimicked->cr_attack_desc(m_aids[4]);
	    }
	  break;
	}
      return "disabled attack"; /* should never show up in combat */
    }
  if (living(mimicked))
    {
      return mimicked->cr_attack_desc(aid);
    }
  return shadow_who->cr_attack_desc(aid);
}

public mixed
wield(object weapon)
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return "As you try to wield the " + weapon->query_short() +
	"your body returns to normal.\n";
    }
  /* We only let humanoid forms wield */
  if (mimicked->query_humanoid())
    {
      return shadow_who->wield(weapon);
    }
  return "You can't wield a thing in this body form.\n";
}

public mixed
wear_arm(object arm)
{
  if (!objectp(mimicked))
    {
      /* The object copied no longer exists */
      dispel_spell_effect();
      return "As you try to wear the " + arm->query_short() +
	"your body returns to normal.\n";
    }
  /* We only let humanoid forms wear armour */
  if (mimicked->query_humanoid())
    {
      return shadow_who->wear_arm(arm);
    }
  return "You can't wear a thing in this body form.\n";
}

/***** Special safe guards for remove *****/
static void remove_spell_effect_object()
{
  if (calling_function(0) != "dispel_spell_effect")
    {
#if _DEBUG
      wiz->catch_msg("remove_spell_effect_object() called from " +
		     calling_function(0));
#endif
      /* Fix me: Log this since anything calling this is
       * probably malicious
       */
    }
  ::remove_spell_effect_object();
}
