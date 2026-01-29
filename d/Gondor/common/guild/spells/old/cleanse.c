#pragma save_binary

#include "/sys/tasks.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#define SP_CLEANSE_MANA 80
#define SP_CLEANSE_INGR ({ "_cleanse_spell_herb_" })			  
#define STAND_DIR "/d/Gondor/common/guild/spells/"

object *
test_for_herb(object tp, object pl)
{
  object herb, poison, *obj_arr;
  string htype,ptype,p;
  int n, esf_roll;
  obj_arr = all_inventory(pl);
  while (n<sizeof(obj_arr))
    {
      if (function_exists("create_poison_effect",obj_arr[n])) 
	{
	  ptype = obj_arr[n]->query_poison_type();
	  if (present("_herb_for_"+ptype+"_cleanse",tp) || 
	      present("_herb_athelas_",tp))
	    {
	      herb = present("_herb_for_"+ptype+"_cleanse",tp);
        if (!herb) herb = present("_herb_athelas_",tp);
	      poison = obj_arr[n];
          }
	}
      n++;
    }
  return ({ herb, poison });
}

mixed
do_cleanse_spell(string person)
{
  object tp, env, *ob_arr, *ingr_arr, *objs, patient, poison, herb;
  int i, power, esf_roll, is_wiz, success, strength, fighting;
  string fail, herbstr, p_type;
  tp = this_player();
  is_wiz = tp->query_wiz_level();
  if (tp->query_attack()) fighting = 1;
  if (tp->query_ghost())
    {
      write("You are unable to do that in your present condition.\n");
      return 1;
    }
  power = tp->query_skill(SS_FORM_CONJURATION) + 
    tp->query_skill(SS_ELEMENT_LIFE);
  if (!person)
    {
      write("Cleanse who?\n");
      return 1;
    }
  person = lower_case(person);
  env = environment(tp);
  if (person == "me" || person == tp->query_real_name())
    {
      if (!tp->query_company())
	{
	  write("You do not feel strong enough to cast this spell on yourself.\n");
	  return 1;
	}
      patient = tp;
    }
  else
    if (!present(person,env))
      {
	write("That person is not here.\n");
	return 1;
      }
  if (!patient)
    patient = present(person,env);
  if (!present("poison",patient))
    {
      if (patient == tp) write("You sense that you are not poisoned.\n");
      else
	write("You quickly find out that that person is not poisoned.\n");
      return 1;
    }
  if (patient->query_ghost())
    {
      write("That person is beyond your help now.\n");
      return 1;
    }
  if (!is_wiz)
    if (!present("_herb_athelas_",tp) || !test_for_herb(tp,patient))
      {
	write("You don't have the herbs you need to cleanse that person!\n");
	return 1;
      }
  objs = test_for_herb(tp,patient);
  poison = objs[1];
  p_type = poison->query_poison_type();
  herb = objs[0];
  if (tp->query_mana() < SP_CLEANSE_MANA)
    return "You feel too weak to cast this spell.\n";
  ingr_arr = ({ herb });
  esf_roll = random(SP_CLEANSE_MANA/3 * (1+fighting));
  if (esf_roll > power)
    {
      esf(esf_roll/(1+sizeof(ingr_arr)) - power, SP_CLEANSE_MANA);
      lose_random_ingr(ingr_arr);
      return 1;
    }
  if ((success = tp->resolve_task(TASK_ROUTINE,
     ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, SKILL_WEIGHT, 90,
        SKILL_AVG, TS_INT, TS_WIS, SKILL_END,
	  SS_FORM_ABJURATION, SS_ELEMENT_LIFE }) )) <= 0)
    {
      tp->catch_msg("Your tongue fails to phrase the prayer, and the spell goes astray!\n");
      tell_room(env,QCTNAME(tp)+" fails to phrase "+tp->query_possessive()+
		" chant correctly.\n",tp);
      lose_random_ingr(ingr_arr);
      return 1;
    }
  if (!herb) herbstr = "Vala Este, the Healer";
  else herbstr = herb->short();
  if (patient != tp)
    {
      tell_room(env,BSN(QCTNAME(tp)+" uses the virtues of the "+herbstr+
	" to try to cleanse the poison from "+QTNAME(patient)+"'s blood."),
		({ tp, patient }));
      patient->catch_msg(BSN(QCTNAME(tp)+" calls for the virtues of the "+
	herbstr+" to try to cleanse the poison from your blood."));
      tp->catch_msg("You call upon the virtues of the "+herbstr+"\n"+
	" to try to cleanse the poison from "+QTNAME(patient)+"'s blood.\n");
      if (is_wiz) tp->catch_msg("The spells strength was "+success+".\n");
      if (poison->cure_poison(({ poison->query_poison_type() }),success) != 1)
	{
	  tp->catch_msg("You fear the poison was stronger than your spell.\n");
	  patient->catch_msg("You fear the poison was too strong for the cure.\n");
	}
      else tp->catch_msg("The spell seems to have some effect.\n");
    }
  else
    {
      tp->catch_msg(BSN("You call upon the virtues of the "+
        herbstr+" to cleanse your blood from the poison."));
      tell_room(env,BSN(QCTNAME(tp)+" uses the powers of the "+herbstr+" to try "+
       	"to cleanse "+tp->query_possessive()+" blood from the poison."),tp);
      if (is_wiz) tp->catch_msg("The spells strength was "+success+".\n");
      if (poison->cure_poison(({ poison->query_poison_type() }),success) != 1)
	{
	  tp->catch_msg("You fear the spell was not strong enough to cure the poison.\n");
	}
    }
  if (!is_wiz)
    {
      tp->add_mana(-SP_CLEANSE_MANA);
      remove_ingr(ingr_arr);
    }
  return 1;
}
