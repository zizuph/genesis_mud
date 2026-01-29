/* ***************************************************************************
   NAME:       Encourage (for Sword Knights)
   COST:       20+healed_hp Mana, (20 fail) (SELF),
               40+healed_hp Mana, (20 fail) (OTHERS)
   TAX:        0.3% (uses recharge technique instead of material component)
   AoE:	       caster/target       
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, 
               SS_AWARENESS
   STATS:      SS_WIS
   DESC:       Success encourages (raises DIS) of target by 2-10 points.
   REQUIRED:   Knight of Sword

               Grace October 1994  
	       ~Aridor, 07/95
*************************************************************************** */

#define ENCOURAGE_MANA 40
#define ENCOURAGE_MANA_FAIL 20
#define ENCOURAGE_TASK    (TASK_DIFFICULT)
#define ENCOURAGE_LIST    ({SS_ELEMENT_LIFE, \
			  SS_FORM_DIVINATION, \
			  SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
			  SKILL_WEIGHT, 50, TS_WIS})

/*FORMULA: life + divination + spellcraft/2 + wis/2
 */

void
create_spell_encourage(string arg)
{
    set_spell_element(SS_ELEMENT_LIFE, 25);
    set_spell_form(SS_FORM_DIVINATION, 22);
    set_spell_time(5);
    set_spell_mana_needed(ENCOURAGE_MANA);
    set_spell_mana_fail(ENCOURAGE_MANA_FAIL);
    set_spell_allow_no_targets();
    set_spell_area_function("my_area_of_effect");
}

string
encourage_mutter(mixed target)
{
    if (target)
      return "the strength of Paladine flow through " + target + ", that you " +
	"may be more encouraged";
    return "the strength of Paladine flow through me, that I may be more " +
      "encouraged";
}

mixed
do_encourage(string str)
{
    int amt;
    object who;

    if (!targets || !sizeof(targets))
      who = TP;
    else if (sizeof(targets) > 1)
      return "You can cast this spell only on one thing at a time.\n";
    else
      who = targets[0];

    reduce_spell_availability("encourage");

    if ((dur = TP->resolve_task(ENCOURAGE_TASK, ENCOURAGE_LIST)) <= 0)
      {
	  write("Despite your best efforts, your prayer is unheard.\n");
	  TP->add_mana(ENCOURAGE_MANA - ENCOURAGE_MANA_FAIL);
	  /* remove previous line if there is mudlib support for it. */
	  return 1;
      }
    
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    seteuid(getuid(TO));

    amt = TP->query_stat(SS_INT) / 10;
    if (amt > 10) amt = 10;

    /* give a 25% malus if the spell wasn't rehearsed */
    if (temp_spell_availability > 0)
      amt = amt * 3 / 4;

    if (dur < 20) dur = 20;

    write("Life energy radiates from the medal. It causes the flesh of"+
	  " your hand to tingle and then blows through you like a warm"+
	  " breeze." + (who == TP ? "" : " The light then continues along " +
			"your arm into " + who->query_the_name(TP)) + ".\n");
    say("The medal flares to light and the light runs along " + QTNAME(TP) +
	"'s arm and into " + QTNAME(who) + ".\n",({who,TP}));

    who->add_tmp_stat(SS_INT, amt, dur);
    set_alarm(itof(F_INTERVAL_BETWEEN_HP_HEALING * dur), 0.0,
	      "announce_end_encourage", who);
    
    if (who != TP)
      who->catch_msg("The medal flares to light and the light runs along " +
		     TP->query_the_name(who) +
		     "'s arm and into you. You feel immediately better.\n");
    else
      {
	  write("You feel better immediately.\n");
	  TP->add_mana(20);
      }
    return 1;
}

void
announce_end_encourage(object who)
{
    who->catch_msg("You feel Paladine's encouragement withdraw again.\n");
}
