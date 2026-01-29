/* ***************************************************************************
   /d/Krynn/solamn/guild/obj/speed.h
         
   NAME:       Speed
   COST:       30 Mana
   TAX:        1.0 
   CLASS:      III 
   AoE:	       self
   TASK:       routine
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_ENCHANTMENT, 
               SS_LANGUAGE
   STATS:      TS_WIS, TS_DEX
   DESC:       Success makes player faster in combat (10-33)
   REQUIRED:   Knight of Rose, no magical objects wielded
*  FREQ:       rare
   DURATION:   1.5 to 5.0 minutes
    
               Grace October 1994   
               Thanks to Olorin for help, guidance, and code.
*************************************************************************** */  

#define SPEED_MANA        50   
#define SPEED_MANA_FAIL   25
#define SPEED_TASK     (TASK_FORMIDABLE)
#define SPEED_LIST     ({SKILL_AVG, SS_ELEMENT_LIFE, SS_FORM_ENCHANTMENT, \
                       SKILL_END, SKILL_AVG, SS_SPELLCRAFT, SS_LANGUAGE, \
                       SKILL_END, TS_WIS, TS_DEX})
// FORMULA: (average(life,enchantment) + average(spellcraft,language) + 
// 100*wis)/100

void
create_spell_speed(string arg)
{
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_ENCHANTMENT, 20);
    set_spell_time(11);
    set_spell_mana_needed(SPEED_MANA);
    set_spell_mana_fail(SPEED_MANA_FAIL);
    set_spell_dont_allow_one_target();
    set_spell_allow_no_targets();
}

string
speed_mutter(mixed target)
{
    return "grant me zealous fervor";
}

mixed
do_speed(string str)
{
    object  pl = this_player();
    int     result;
    object speed;

    if (member_array(1,pl->query_weapon(-1)->query_prop(OBJ_I_IS_MAGIC_WEAPON)) > -1)
      return "You cannot cast this spell while wielding a magical weapon!\n";
    
    if (member_array(1,pl->query_armour(-1)->query_prop(OBJ_I_IS_MAGIC_ARMOUR)) > -1)
      return "You cannot cast this spell while wearing a magical armour!\n";

    
    if (present("_solamn_speed_obj", pl))
      { 
	  write("\nIn his wisdom Paladine denies your request. Pushing " +
		"yourself to greater speed would surely cause your heart "+
		"to burst!\n");
	  return 1;
      }
    
    if (result = (pl->resolve_task(SPEED_TASK, SPEED_LIST <= 0)))
      {
	  pl->add_mana(SPEED_MANA - SPEED_MANA_FAIL);
	  write("Despite your best efforts, your prayer is unheard.\n");
	  return 1;
      }
    
    if (result < 30)
      result = 30;
    else if (result > 100)
      result = 99;
    
    seteuid(getuid());
    speed = clone_object("/d/Krynn/solamn/guild/obj/speedo.c");
    speed->set_dur(result * 3);     /* 1.5 - 5.0 mins */
    speed->set_quick(result / 3);        /*  10 - 33  */
    speed->move(pl);
    
    tell_room(E(pl), QCTNAME(pl) + "begins to move with unhurried quickness.\n", pl);
    pl->catch_msg("Paladine has granted your prayer, enhancing your quick" +
		  "ness.\n");
    return 1;
}
