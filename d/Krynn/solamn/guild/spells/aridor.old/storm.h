/* ***************************************************************************
   NAME:       Storm
   COST:       300 Mana (30 fail)
   TAX:        1.5% (uses recharge technique instead of material component)
   CLASS:      
   AoE:	       environment of caster only
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, 
   STATS:      SS_WIS, SS_DIS, SS_STR
   DESC:       Success clones a stormcould to the environment of the Knight
   REQUIRED:   Knight of Sword

               Grace October 1994  
	       ~Aridor, 07/95
*************************************************************************** */

#define STORM_MANA 100
#define STORM_MANA_FAIL 10
#define STORM_TASK    (TASK_DIFFICULT)
#define STORM_LIST    ({SS_FORM_DIVINATION, \
                        SKILL_WEIGHT, 70, SS_ELEMENT_LIFE, \
			SKILL_WEIGHT, 70, SS_SPELLCRAFT, \
                        SKILL_WEIGHT, 30, TS_WIS, \
			SKILL_WEIGHT, 50, TS_DIS, \
		        SKILL_WEIGHT, 50, TS_STR })

/*FORMULA: divination + 0.7*life + 0.7*spellcraft + 0.3*wis + 0.5*dis + 0.5*str
 */

void
create_spell_storm(string arg)
{
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_DIVINATION, 60);
    set_spell_time(15);
    set_spell_mana_needed(STORM_MANA);
    set_spell_mana_fail(STORM_MANA_FAIL);
    set_spell_dont_allow_one_target();
    set_spell_allow_no_targets();
}

string
storm_mutter(mixed target)
{
    return "may the wrath of Kiri-Jolith be seen and heard";
}

mixed
do_storm()
{
    int level, dur;
    object cloud;
    
    if (present("stormcloud", E(TP)))
      return "This prayer is already in operation here!\n";
 
    if (E(TP)->query_prop(ROOM_I_INSIDE) == 1)
      return "This prayer is only possible outside!\n";
   
    reduce_spell_availability("storm");

    if (random(TP->query_stat(SS_DIS)) < random(30))
      return "You begin to pray but lose concentration.\n";
    
    if (TP->resolve_task(STORM_TASK,STORM_LIST) <= 0)
      {
	  TP->add_mana(- STORM_MANA_FAIL);
	  /* remove previous line if there is mudlib support for it. */
	  write("Despite your best efforts, your prayer is unheard.\n");
	  return 1;
      }
    
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    seteuid(getuid(TO));
    
    level = TP->query_knight_level();
    cloud = clone_object(OBJ + "stormcloud");
    dur = 50 + random(TP->query_stat(SS_DIS)) + (level * 20) -
      temp_spell_availability/60;
    cloud->set_duration(dur > 10 ? dur : 10);
    cloud->set_strength(TP->query_stat(SS_STR) + (level * 20) -
			temp_spell_availability/100);
    cloud->move(E(TP));
    tell_room(E(TP),"Suddenly, giant stormclouds draws together above you.\n");
    cloud->start_cloud();
    return 1;
}
