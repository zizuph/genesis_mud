/* ***************************************************************************
   NAME:       Revive (for Rose Knights)
   COST:       20+healed_hp Mana (10 fail)
   TAX:        0.4% (uses recharge technique instead of material component)
   AoE:	       caster only
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, 
               SS_AWARENESS
   STATS:      SS_WIS > random(45)

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

/*prototypes*/
public object *revive_target(string str);
public void revive_message(object caster, object *targets);
public mixed revive_success(object caster, object *targets);

void
create_spell_revive(string arg)
{
    set_element(SS_ELEMENT_LIFE, 20);
    set_form(SS_FORM_DIVINATION, 16);
    set_spell_time(6);
    set_mana_spell(R_REV_MANA);
    //set_mana_spell(R_REV_MANA_FAIL);

    set_find_target(revive_target);

    set_spell_task(R_REV_TASK);
    set_spell_message(revive_message);
    set_spell_success(revive_success);

    set_spell_object(SOBJ + "reviveobj_rose");
    set_duration(1);
}

string
revive_mutter(mixed target)
{
    return "the essence of Life flow through me, that I may heal";
}

public object *
revive_target(string str)
{
    int i;
    mixed *targ;

    if (str)
      return 0;

    return ({ query_caster() });
}

public void
revive_message(object caster, object *targets)
{
    object who = targets[0];
    int mana,mxhp,hp,healed;

    set_this_player(caster);
    write("Life energy radiates from the medal. It causes the flesh of"+
	  " your hand to tingle and then blows through you like a warm"+
	  " breeze.\n");
    say("The medal flares to light and the light runs along " + QTNAME(TP) +
	"'s arm and into " + POSSESSIVE(who) + " body.\n",({who}));
}

public mixed
revive_success(object caster, object *targets)
{
    int result;

    fail_message = "";
    if (spell_failed)
      return 0;

    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    fail_message = "Despite your best efforts, your prayer is unheard.\n";
    if ((result = TP->resolve_task(R_REV_TASK, R_REV_LIST)) <= 0)
      return 0;
    
    /* give a 50% malus if the spell wasn't rehearsed */
    if (temp_spell_availability > 0)
      result /= 2;

    reduce_spell_availability("revive");
    return result;
}

mixed
do_revive(string str)
{
    return cast_spell();
}
