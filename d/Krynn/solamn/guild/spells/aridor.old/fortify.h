/* ***************************************************************************
   NAME:       Fortify
   COST:       100 Mana (10 fail)
   TAX:        0.5% (uses recharge technique instead of material component)
   CLASS:      
   AoE:	       caster only
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, 
               SS_AWARENESS
   STATS:      SS_WIS, SS_INT
   DESC:       Success clones a magical shield to Knight
   REQUIRED:   Knight of Sword or Rose

               Grace October 1994  
	       ~Aridor, 07/95
*************************************************************************** */

#define FORTIFY_MANA 100
#define FORTIFY_MANA_FAIL 10
#define FORTIFY_TASK    (TASK_DIFFICULT)
#define FORTIFY_LIST    ({SS_FORM_DIVINATION, \
			    SKILL_WEIGHT, 10, SS_FORM_ENCHANTMENT, \
			    SKILL_WEIGHT, 70, SS_ELEMENT_LIFE, \
			    SKILL_WEIGHT, 60, SS_SPELLCRAFT, \
			    TS_WIS })

/*FORMULA: divination + 0.1*encahntment + 0.7*life + 0.6*spellcraft + wis
 */

void
create_spell_fortify(string arg)
{
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_DIVINATION, 50);
    set_spell_time(9);
    set_spell_mana_needed(FORTIFY_MANA);
    set_spell_mana_fail(FORTIFY_MANA_FAIL);
    set_spell_dont_allow_one_target();
    set_spell_allow_no_targets();
}

string
fortify_mutter(mixed target)
{
    return "may the spirit of Paladine protect me";
}

mixed
do_fortify()
{
    int level, dur;
    object shieldobj;
    
    if (present("shieldobj", TP))
      return "This prayer is already in operation!\n";
    
    reduce_spell_availability("fortify");

    if (random(TP->query_stat(SS_WIS)) < random(30))
      return "You begin to pray but lose concentration.\n";
    
    if (TP->resolve_task(FORTIFY_TASK,FORTIFY_LIST) <= 0)
      {
	  TP->add_mana(- FORTIFY_MANA_FAIL);
	  /* remove previous line if there is mudlib support for it. */
	  write("Despite your best efforts, your prayer is unheard.\n");
	  return 1;
      }
    
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    seteuid(getuid(TO));
    
    level = TP->query_knight_level();
    shieldobj = clone_object(OBJ + "shieldobj_new");
    dur = 50 + random(TP->query_stat(SS_INT)) + (level * 20) -
      temp_spell_availability/40;
    shieldobj->set_duration(dur > 10 ? dur : 10);
                                                           
    shieldobj->move(TO);
    TP->wear_arm(shieldobj);
    write("You feel the power of Paladine's protection shielding you.\n");
    return 1;
}


