inherit "/std/armour.c";



#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 50
#define STAT_DIS 5
#define STAT_STR 0
#define STAT_CON 2

static int chunks_of_flesh = 0;


string
flesh_desc();

void
create_armour()
{
  set_name("platemail");
  set_pname("platemails");

  set_adj("blackened");
  set_adj("spiked");

  set_short("blackened spiked platemail");
  set_pshort("blackened spiked platemails");

  set_long("A blackened platemail. Blackened to make it look terrifying, " +
	   "this platemail offers quite a lot of protection. Heavily " +
	   "reinforced and sturdily constructed, it would take quite a " +
           "lot to penetrate this armour. The protruding spikes covering " +
	   "the entire armour are long and sharp protecting the wearer " +
	   "like the porcupine and his coat. These spikes must be long " +
	   "than an arm. They can " +
	   "probably really hurt someone.@@flesh_desc@@" +
	   "A commander's emblem " +
	   "decorates the the front of the armour.\n");

  set_af(this_object());
  set_ac(ARMOUR_CLASS);
  set_at(A_BODY || A_ARMS || A_LEGS);
  set_am( ({1,0,1}) );
  
  add_prop(OBJ_I_WEIGHT, 9600 + (random(50) -  25));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(100) +
	   1000);

}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}

int
wear()
{
  shadow->shadow_me(this_player());
  if(this_player()->query_stat(STAT_DIS) < 55)
    {
      this_player()->catch_msg("An eerie presence glows " +
			       "from within the armour. " +
			       "You decide it is better " +
			       "to not mess with it.\n");
      this_player()->command("drop blacken spiked platemail");
      return 0;
    }
  else if((this_player()->query_stat(STAT_STR < 80)) ||
	  (this_player()->query_stat(STAT_CON < 80)))
    {
      write("A loud voice yells: Fool!  You are not worthy, " +
	    "you weak pathetic flea!\n");
      return 0;
    }
  else
    {
      this_player()->catch_msg("Despite having misgivings, " +
			       "you decide to wear the armour " +
			       "over your shoulders. A " +
			       "presence within the armour " +
			       "seems to have accepted you.\n");
      write("A servile voice says: Master, we are now one!\n");
      return 1;
    }
}
  
int
remove()
{
  this_player->remove_shadow();
  return 1;
}


hit_me(int wcpen, int dt, object attacker, int attack_id, 
       int target_hitloc = -1)
{
  mixed dam_lvl;
  ::shadow->hit_me();
  dam_lvl = attacker->hit_me(wcpen, W_IMPALE, this_object, 0, attack_id);

  if (dam_lvl[0] <= 0)
    return 0;

  if (dam_lvl < 20)
    {
      attacker->catch_msg("You hurt yourself " +
		     "slightly as you hit the spikes of " +
		     "the blackened spiked platemail.\n");
      query_worn()->catch_msg(QCTNAME(attacker) + " hurts " +
			      attacker->query_objective() + "self " +
			      "slightly as " +
			      attacker->query_pronoun() +
			      " hits the spikes of the blackened " +
			      "spiked platemail.\n");
      attacker->tell_watcher(QCTNAME(attacker) + " hurts " +
			attacker->query_objective() + "self " +
			"slightly as " +
			attacker->query_pronoun() +
			" hits the spikes of the blackened " +
			"spiked platemail.\n", attacker);
    }
  else if (dam_lvl >= 20 && dam_lvl < 40)
    { 
      attacker->catch_msg("You " +
		     "begin to trickle blood as the spikes " +
		     "of the blackened spiked platemail pierce " +
		     "into you.\n");
      query_worn()->catch_msg(QCTNAME(attacker) +
			      " begins to trickle blood as the spikes " +
			      "of the blackened spiked platemail pierce " +
			      "into " + attacker->query_objective() + ".\n");
      attacker->tell_watcher(QCTNAME(attacker) +
			"begins to trickle blood as the spikes " +
			"of the blackened spiked platemail pierce " +
			"into " + attacker->query_objective + ".\n", attacker);
    }
  else if (dam_lvl >= && dam_lvl < 60)
    {
      attacker->catch_msg("The spikes of the blackened spiked platemail " +
		     "punch holes in you as you strike the armour.\n");
      query_worn()->catch_msg("The spikes of the blackened spiked " +
			      "platemail punche holes in " +
			      QCTNAME(attacker) + " as " +
			      attacker->query_pronoun + " strikes the " +
			      "armour.\n");
      attacker->tell_watcher("The spikes of the blackened spiked " +
			"platemail punche holes in " +
			QCTNAME(attacker) + " as " +
			attacker->query_pronoun + " strikes the " +
			"armour.\n", attacker);
  else if (dam_lvl >= 60)
    {
      ++chunks_of_flesh;
      attacker->command("scream");
      attacker->catch_msg(QCTNAME(query_worn()) + " grins at you as you " +
		     "scream in agony while a chunk of " +
		     "your flesh is ripped away from you.\n");
      query_worn()->catch_msg("You grin at " + QCTNAME(attacker) +
			      " as " + QCTNAME(attacker) +
			      " screams in agony while a chunk of " +
			      attacker->query_possessive() + 
			      " flesh is " +
			      "ripped away from " + 
			      attacker->query_objective()+ ".\n");
      attacker->tell_watcher(QCTNAME(query_worn()) + " grins at " + 
			QCTNAME(attacker) +
			" as " + QCTNAME(attacker) +
			" screams in agony while a chunk of " +
				 attacker->query_possessive + " flesh is " +
			"ripped away from " + 
			attacker->query_objective, attacker);
    }
  
  hits++;
  if (F_ARMOUR_CONDITION_WORSE(hits, arm_ac, likely_cond))
    {
      hits = 0;
      set_condition(query_condition() + 1);
    }
  
  return 0;
  
}

flesh_desc()
{
  switch(chunks_of_flesh)
    {
    case 0:
      return " ";
      break;
    case 1:
      return " A chunk of flesh is stuck on the spikes. ";
      break;
    case 2..4:
      return " A couple chunks of flesh decorate the spikes. ";
      break;
    case 5..10:
      return " The spikes are littered with chunks of flesh. ";
      break;
    default:
      return " The entire armour is bloodied with chunks of flesh. ";
    }
}



