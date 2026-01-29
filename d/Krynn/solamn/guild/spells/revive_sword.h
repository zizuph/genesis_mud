/* ***************************************************************************
   NAME:       Revive (for Sword Knights)
   COST:       20+healed_hp Mana, ( 10 fail) (SELF),
               40+healed_hp Mana, ( 10 fail) (OTHERS)
   TAX:        0.5% (uses recharge technique instead of material component)
   AoE:	       caster/target       
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, 
               SS_AWARENESS
   STATS:      SS_WIS

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

/*prototypes*/
public object *revive_target(string str);
public void revive_message(object caster, object *targets);
public mixed revive_success(object caster, object *targets);

void
create_spell_revive(string arg)
{
    set_element(SS_ELEMENT_LIFE, 25);
    set_form(SS_FORM_DIVINATION, 22);
    set_spell_time(6);
    set_mana_spell(S_REV_MANA);
    //set_mana_spell_fail(S_REV_MANA_FAIL);
    //set_spell_area_function("my_area_of_effect");

    set_find_target(revive_target);

    set_spell_task(S_REV_TASK);
    set_spell_message(revive_message);
    set_spell_success(revive_success);

    set_spell_object(SOBJ + "reviveobj");
    set_duration(1);
}

string
revive_mutter(mixed target)
{
    if (target)
      return "the essence of Life flow through " + target + ", that you may heal";
    return "the essence of Life flow through me, that I may heal";
}

public object *
r_no_target_message()
{
    write("Revive who?\n");
    return 0;
}

public object *
revive_target(string str)
{
    int i;
    mixed *targ;

    if (!str)
      return ({ query_caster() });

    if (str == "me" || str == "myself")
      return ({ query_caster() });

    if (!parse_command(str,E(query_caster()),"[the] %l",targ))
      return r_no_target_message();
    
    i = targ[0];
    if (i==0)
      return r_no_target_message(); /*targ[1..]; can only cast on one person*/
    if (i<0)
      return targ[-i..-i];
    return targ[1..1]; /* actually targ[1..i], but we only want one person */
}

public void
revive_message(object caster, object *targets)
{
    object who = targets[0];
    int mana,mxhp,hp,healed;

    set_this_player(caster);
    write("Life energy radiates from the medal. It causes the flesh of"+
	  " your hand to tingle and then blows through you like a warm"+
	  " breeze" + (who == TP ? "" : ". The light then continues along " +
			"your arm into " + who->query_the_name(TP)) + ".\n");
    say("The medal flares to light and the light runs along " + QTNAME(TP) +
	"'s arm and into " + QTNAME(who) + ".\n",({who,TP}));
}

public mixed
revive_success(object caster, object *targets)
{
    int result;

    fail_message = ""; /* Fail message is printed elsewhere */
    if (spell_failed)
      return 0;

    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    fail_message = "Despite your best efforts, your prayer is unheard.\n";
    if ((result = TP->resolve_task(S_REV_TASK, S_REV_LIST)) <= 0)
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
