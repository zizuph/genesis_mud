#pragma save_binary

#include "/sys/tasks.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#define SP_HEAL_MANA 60
#define SP_HEAL_INGR ({ "_heal_spell_herb_" })
#define STAND_DIR "/d/Gondor/common/guild/spells/"

/*
 * Function name:   do_heal_spell
 * Decription:	    Cast the healing spell.
 * Returns:	    1 if spell was cast, 0 otherwise.
 */
mixed
do_heal_spell(string person)
{
  object tp, env, *ob_arr, *ingr_arr, obj, patient;
  int i, power, is_wiz, success;
  string fail;
  if (!person) {
    write("Heal who?\n");
    return 1;
  }
  person = lower_case(person);
  tp = this_player();
  env = environment(tp);
  is_wiz = tp->query_wiz_level();
  if (person == "myself" || person == "me"
    || person == tp->query_real_name()) {
    if (!tp->query_company())
      {
	write("You may not cast this spell on yourself.\n");
	return 1;
      }
    patient = tp;
  }
  else
    if (!present(person,env)) {
      write("That person is not here.\n");
      return 1;
    }
  if (!patient)
    patient = present(person,env);
  if (patient->query_hp() == F_MAX_HP(patient->query_stat(SS_CON))) {
    if (patient == tp) write("You don't need any healing.\n");
    else write("That person does not need healing.\n");
    return 1;
  }
  if (patient->query_ghost()) {
    write("That person is beyond your help now.\n");
    return 1;
  }
  if (fail = check_player(tp, SP_HEAL_INGR, SP_HEAL_MANA))
    return fail;
  
  /* Get the object array of all ingredients */
  ingr_arr = find_ingr(SP_HEAL_INGR, tp);
  
  /* Let's see if the player can cope with the task... */
  if (!is_wiz &&
      (success = tp->resolve_task(TASK_ROUTINE,
       ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT,
       SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END,
            SS_FORM_CONJURATION, SS_ELEMENT_LIFE }) )) <= 0)
    {
      tp->catch_msg("You fail to cast the spell correctly.\n");
      tell_room(environment(tp), QCTNAME(tp) + " fails to cast a spell "
		+ "correctly.\n", tp);
      lose_random_ingr(ingr_arr);
      return 1;
    }
  if (patient != tp) {
    tell_room(env,QCTNAME(tp)+" calls upon the magical healing virtue of a\n"+
	      "red flower to heal "+QTNAME(patient)+".\n",({ tp, patient }));
    tp->catch_msg("You call upon the magical healing virtue of the red flower "+
		  "to\nimprove "+QTNAME(patient)+"'s health.\n");
  }
  else {
    tell_room(env,QCTNAME(tp)+" calls upon the ancient Valar to heal "+
	      tp->query_objective()+"self.\n");
    tp->catch_msg("You call upon the power of the god Orome to heal you.\n");
  }
  /* Finally start casting the spell */
  patient->set_hp(patient->query_hp() + 5 
    + (F_PENMOD(20,(tp->query_stat(SS_OCCUP)*20/100 
    + tp->query_skill(SS_ELEMENT_LIFE)*20/100 
    + tp->query_skill(SS_SPELLCRAFT)*20/100))));
  if (patient != tp)
    patient->catch_msg("You feel healthier as "+QTNAME(tp)+" casts a healing spell on you.\n");
  else tp->catch_msg("You feel healthier!\n");
  /* Make him/her pay for it */
  /* And remove the ingredients */
  if (!is_wiz)
    {
      if (!tp->query_company() || tp == patient) remove_ingr(ingr_arr);
      tp->add_mana(-SP_HEAL_MANA);
    }
  tell_room(env, QCTNAME(tp) + " casts a spell successfully.\n", tp);
  tp->catch_msg("You cast the spell successfully.\n");
  
  return 1;
}
