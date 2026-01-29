/* ***************************************************************************
   NAME:       Revive (for Sword Knights)
   COST:       20+healed_hp Mana, ( 10 fail) (SELF),
               40+healed_hp Mana, ( 10 fail) (OTHERS)
   TAX:        0.5% (uses recharge technique instead of material component)
   CLASS:      H (heal)
   AoE:	       caster/target       
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, 
               SS_AWARENESS
   STATS:      SS_WIS
   DESC:       Success heals target ~1/5 of lost hp
   REQUIRED:   Knight of Sword

               Grace October 1994  
	       ~Aridor, 07/95
*************************************************************************** */

#define S_REV_MANA 20 /* mininum mana reduced. real mana ist subtracted
		       * according to hp restored
		       */
#define S_REV_MANA_FAIL 10
#define S_REV_TASK    (TASK_ROUTINE)
#define S_REV_LIST    ({SS_ELEMENT_LIFE, \
                      SS_FORM_DIVINATION, \
		      SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		      SKILL_WEIGHT, 50, TS_WIS})

/*FORMULA: life + divination + spellcraft/2 + wis/2
 */

void
create_spell_revive(string arg)
{
    set_spell_element(SS_ELEMENT_LIFE, 25);
    set_spell_form(SS_FORM_DIVINATION, 22);
    set_spell_time(6);
    set_spell_mana_needed(S_REV_MANA);
    set_spell_mana_fail(S_REV_MANA_FAIL);
    set_spell_allow_no_targets();
    set_spell_area_function("my_area_of_effect");
}

string
revive_mutter(mixed target)
{
    if (target)
      return "the essence of Life flow through " + target + ", that you may heal";
    return "the essence of Life flow through me, that I may heal";
}

mixed
do_revive(string str)
{
    int mana, hp, healed, mxhp;
    object who;

    if (!targets || !sizeof(targets))
      who = TP;
    else if (sizeof(targets) > 1)
      return "You can cast this spell only on one thing at a time.\n";
    else
      who = targets[0];

    reduce_spell_availability("revive");

    if (TP->resolve_task(S_REV_TASK, S_REV_LIST) <= 0)
      {
	  write("Despite your best efforts, your prayer is unheard.\n");
	  TP->add_mana(- S_REV_MANA_FAIL);
	  /* remove previous line if there is mudlib support for it. */
	  return 1;
      }
    
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    mana = TP->query_mana();
    mxhp = who->query_max_hp();
    hp = who->query_hp();

    healed = MIN((mxhp - hp) / 3, mana / 2);
    /*find_player("rastlin")->catch_msg("" + mana + " " + mxhp + " " + hp + 
				     " " + healed + "\n");*/
    find_player("aridor")->catch_msg("Mana: " + mana + " MXHP:" + mxhp + " HP:" +
				     hp + " HEAL:" + healed + "\n");
    /* give a 50% malus if the spell wasn't rehearsed */
    if (temp_spell_availability > 0)
      healed = healed / 2;

    write("Life energy radiates from the medal. It causes the flesh of"+
	  " your hand to tingle and then blows through you like a warm"+
	  " breeze." + (who == TP ? "" : " The light then continues along " +
			"your arm into " + who->query_the_name(TP)) + ".\n");
    say("The medal flares to light and the light runs along " + QTNAME(TP) +
	"'s arm and into " + QTNAME(who) + ".\n",({who,TP}));
    if (who != TP)
      who->catch_msg("The medal flares to light and the light runs along " +
		     TP->query_the_name(who) +
		     "'s arm and into you. You feel immediately better.\n");
    else
      write("You feel better immediately.\n");
    who->heal_hp(healed);

    healed = -healed/6 + S_REV_MANA;
    TP->add_mana(healed);
    return 1;
}
