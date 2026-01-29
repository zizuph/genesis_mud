/* ***************************************************************************
   NAME:       Revive (for Rose Knights)
   COST:       20+healed_hp Mana (10 fail)
   TAX:        0.4% (uses recharge technique instead of material component)
   CLASS:      H (heal)
   AoE:	       caster only
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, 
               SS_AWARENESS
   STATS:      SS_WIS > random(45)
   DESC:       Success heals caster ~1/6 of lost hp
   REQUIRED:   Knight of Rose

               Grace October 1994  
	       ~Aridor, 07/95
*************************************************************************** */

#define R_REV_MANA 20 /* minimum mana reduced. real mana is subtracted according
		       * to hp restored
		       */
#define R_REV_MANA_FAIL 10
#define R_REV_TASK    (TASK_ROUTINE)
#define R_REV_LIST    ({SS_ELEMENT_LIFE, \
                      SKILL_WEIGHT, 80, SS_FORM_DIVINATION, \
		      SKILL_WEIGHT, 40, SS_SPELLCRAFT, \
		      SKILL_WEIGHT, 40, TS_WIS})

/*FORMULA: life + 0.8*divination + 0.4*spellcraft + 0.4*wis
 */


void
create_spell_revive(string arg)
{
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_DIVINATION, 16);
    set_spell_time(6);
    set_spell_mana_needed(R_REV_MANA);
    set_spell_mana_fail(R_REV_MANA_FAIL);
    set_spell_allow_no_targets();
    set_spell_dont_allow_one_target();
}

string
revive_mutter(mixed target)
{
    return "the essence of Life flow through me, that I may heal";
}

mixed
do_revive(string arg)
{
    int mana, healed, hp, mxhp, is_a_wiz = TP->query_wiz_level();

    reduce_spell_availability("revive");

    if (random(TP->query_stat(SS_WIS)) < random(45))
      return "You begin to pray but lose concentration.\n";
    
    if (TP->resolve_task(R_REV_TASK,R_REV_LIST) <= 0)
      {
	  write("Despite your best efforts, your prayer is unheard.\n");
	  TP->add_mana(- R_REV_MANA_FAIL);
	  /* remove previous line if there is mudlib support for it. */
	  return 1;
      }
    
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    mana = TP->query_mana();
    mxhp = TP->query_max_hp();
    hp = TP->query_hp();
    healed = MIN((mxhp - hp) / 3, mana / 2);
    /*find_player("rastlin")->catch_msg("" + mana + " " + mxhp + " " + hp + 
				     " " + healed + "\n");*/
    find_player("aridor")->catch_msg("Mana: " + mana + " MXHP:" + mxhp + " HP:" +
				     hp + " HEAL:" + healed + "\n");
    /* give a 50% malus if the spell wasn't rehearsed */
    if (temp_spell_availability > 0)
      healed = healed / 2;

    write("Life energy radiates from the medal. It causes the flesh of"+
	  " your palm to tingle and then ruffles through you like the gentle"+
	  " fingers of a warm hand.\n");
    TP->heal_hp(healed);

    healed = -healed/5 + R_REV_MANA;
    TP->add_mana(healed);
    TP->catch_msg("You feel better immediately.\n");
    return 1;
}

