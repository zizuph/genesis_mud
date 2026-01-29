/* ***************************************************************************
   /d/Krynn/solamn/guild/obj/perceive_spell.h
         
   NAME:       Perceive
   COST:       30 Mana
   TAX:        0.25 (uses recharge technique instead of material component)
   CLASS:      I (information)
   AoE:	       object/target
   TASK:       routine (was: simple)
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, 
               SS_AWARENESS
   STATS:      TS_WIS
   DESC:       Success gives MAGIC_AM_ID_INFO
   REQUIRED:   Knight of Sword (Rose, too??) not in combat.
   
               Grace October 1994   
               Thanks to Olorin for help, guidance, and code.
               ~Aridor, 07/95
*************************************************************************** */

#define PER_TARG     ({MAGIC_I_RES_IDENTIFY})
#define PER_MANA     30
#define PER_TASK     (TASK_DIFFICULT + 100)
#define PER_LIST     ({SS_AWARENESS, \
                     SKILL_WEIGHT, 50, SS_FORM_DIVINATION, \
                     SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
                     TS_WIS})
/*FORMULA: awareness + (divination+spellcraft)/2 + wis
 */

void
create_spell_perceive()
{
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_DIVINATION, 18);
    set_spell_time(6);
    set_spell_mana_needed(25);
    set_spell_mana_fail(25);
    set_spell_area_function("my_area_of_effect");
}

string
perceive_mutter(mixed target)
{
    return "reveal unto me the secret nature of " + target;
}

mixed
do_perceive(string str)
{

    object  targ;
    string  info = "";
    int     result, i;
    mixed   magic_str, prop;
    
    if (TP->query_attack())
      return "You are too distracted by the combat to cast this " +
	"spell.\n";

    if (!strlen(str))
      return "Which item do you wish to test for magic?\n";
    
    if (sizeof(targets) > 1)
      return "You can cast this spell only on one thing at a time.\n";
    targ = targets[0];
    
    if (TP->query_mana() < PER_MANA)
      return "You are too mentally exhausted to attempt this spell.\n";
    
    if (stringp(prop = targ->query_prop(OBJ_M_NO_MAGIC)))
      return prop;

    /* what is this for?? 
    else if (prop)
      return PER_MANA;
      */
    
    reduce_spell_availability("perceive");
    
    result = TP->resolve_task(PER_TASK, PER_LIST, targ, PER_TARG);
    if (result <= 0)
      {
	  write("Despite your best efforts, your prayer is unheard.\n");
	  TP->add_mana(-(PER_MANA));
	  return 1;
      }

    /*
     *  Allows for restriction of MAGIC_AM_ID_INFO to players 
     * Huh? what is that supposed to do?????
    if (result < 25)
      result = 25;
    if (result > 75)
      result = 75;
    result *= 2;
    */
    /* ok, we need some limits, that's for sure. */
    if (result > 75)
      result = 75;

    /* give a malus if the spell wasn't rehearsed */
    if (temp_spell_availability > 0)
      result /= 2;
    
    magic_str = targ->query_prop(MAGIC_AM_ID_INFO);
    for (i = 0; i < sizeof(magic_str); i += 2)
      if (magic_str[i + 1] <= result)
	info += magic_str[i];
    
    if (strlen(info))
      write(info);
    else
      {
	  write("A trickle of energy flows into the medal and withdraws.\n " +
		"You feel certain that the " + check_call(targ->short()) + " is "+
		"what it appears to be, and nothing more.\n");
      }

    TP->add_mana(-(PER_MANA));
    return 1;
}
