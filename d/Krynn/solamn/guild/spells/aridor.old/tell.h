/* ***************************************************************************
   NAME:       Tell
   COST:       20 Mana (5 fail)
   TAX:        0.5% (uses recharge technique instead of material component)
   CLASS:      
   AoE:	       caster only
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, 
               SS_AWARENESS, SS_LANGUAGE
   STATS:      SS_WIS, SS_INT
   DESC:       Success tells another knight a message
   REQUIRED:   Knight of Sword or Rose

               Grace October 1994  
	       ~Aridor, 08/95
*************************************************************************** */

#define TELL_MANA 100
#define TELL_MANA_FAIL 40
#define TELL_TASK    (TASK_ROUTINE + 100)
#define TELL_LIST    ({SKILL_WEIGHT, 50, SS_FORM_DIVINATION, \
		       SKILL_WEIGHT, 70, SS_LANGUAGE, \
                       SKILL_WEIGHT, 50, SS_ELEMENT_LIFE, \
		       SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
                       SKILL_WEIGHT, 70, TS_WIS, \
		       SKILL_WEIGHT, 70, TS_INT})

void
create_spell_tell(string arg)
{
    set_spell_element(SS_ELEMENT_LIFE, 5);
    set_spell_form(SS_FORM_DIVINATION, 13);
    set_spell_time(3);
    set_spell_mana_needed(TELL_MANA);
    set_spell_mana_fail(TELL_MANA_FAIL);
    set_spell_dont_allow_one_target();
    set_spell_allow_no_targets();
}

string
tell_mutter(mixed target)
{
    return "communicate with " + target;
}

mixed
do_tell()
{
    int level;
    object shieldobj;
    
    if (present("shieldobj", TP))
      return "This prayer is already in operation!\n";
    
    reduce_spell_availability("fortify");

    if (random(TP->query_stat(SS_WIS)) < random(30))
      return "You begin to pray but lose concentration.\n";
    
    if (TP->resolve_task(FORTIFY_TASK,FORTIFY_LIST) <= 0)
      {
	  TP->add_mana(FORTIFY_MANA - FORTIFY_MANA_FAIL);
	  /* remove previous line if there is mudlib support for it. */
	  write("Despite your best efforts, your prayer is unheard.\n");
	  return 1;
      }
    
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    seteuid(getuid(TO));
    
    level = TP->query_knight_level();
    shieldobj = clone_object(OBJ + "shieldobj_new");
    shieldobj->set_duration(50 + random(TP->query_stat(SS_INT)) + (level * 20));
                                                           
    shieldobj->move(TO);
    TP->wear_arm(shieldobj);
    write("You feel the power of Paladine's protection shielding you.\n");
    return 1;
}


