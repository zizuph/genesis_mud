/* ***************************************************************************
   NAME:       Radiance (for Sword & Rose Knights)
   COST:       5 Mana
   TAX:        0.2% * 1.5 (no material component + no rehearsing) = 0.3%
   CLASS:      
   AoE:	       caster only
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_ELEMENT_FIRE,
               SS_FORM_ENCHANTMENT
   STATS:      SS_WIS
   DESC:       Success creates a light object.
   REQUIRED:   Knight of Sword or Knight of Rose

               Grace October 1994  
	       ~Aridor, 07/95
*************************************************************************** */

#define RADIANCE_MANA     5   /*(Same for failure and success)*/
#define RADIANCE_TASK     (TASK_ROUTINE)
#define RADIANCE_LIST     ({SKILL_AVG, SS_ELEMENT_LIFE, SS_ELEMENT_FIRE, SKILL_END,\
			    SS_FORM_ENCHANTMENT,\
			    SS_SPELLCRAFT, \
			    TS_WIS})
/* FORMULA: (fire+life)/2 + enchantment + spellcraft + wis
*/

void
create_spell_radiance(string arg)
{
    set_spell_element(SS_ELEMENT_FIRE, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 8);
    set_spell_time(4);
    set_spell_mana_needed(RADIANCE_MANA);
    set_spell_mana_fail(RADIANCE_MANA);
    set_spell_allow_no_targets();
    set_spell_dont_allow_one_target();
}

string
radiance_mutter(mixed target)
{
    return "shed light unto me";
}

mixed
do_radiance(string arg)
{
    object ob;
    int level, result;
    
    if (result = (TP->resolve_task(RADIANCE_TASK, RADIANCE_LIST) <= 0))
      {
	  write("Despite your best efforts, your prayer is unheard.\n");
	  return 1;
      }
    
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    write("Your prayer is heard and your medal begins to glow.\n");
    say(QCTNAME(TP) + "'s medal begins to glow!\n");
    
    seteuid(getuid(TO));
    level = TP->query_knight_level();
    ob = clone_object(OBJ + "lightobj");
    ob->set_duration(random(TP->query_stat(SS_INT) * 2) +
		     random(level * 20) + 245);
    ob->move(TP);
    
    return 1;
}
