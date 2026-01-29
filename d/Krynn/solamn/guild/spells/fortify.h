/* **************************************************************************
   NAME:       Fortify
   TAX:        0.5% (uses recharge technique instead of material component)
   AoE:	       caster only
   DESC:       Success clones a magical shield to Knight
   REQUIRED:   Knight of Sword or Rose
*************************************************************************** */

#define FORTIFY_OBJECT    (SOBJ + "shieldobj")
#define FORTIFY_MANA      100
#define FORTIFY_MANA_FAIL 10
#define FORTIFY_TASK      (TASK_DIFFICULT)
#define FORTIFY_LIST      ({ SS_FORM_DIVINATION, \
                             SKILL_WEIGHT, 70, SS_ELEMENT_LIFE, \
			     SKILL_WEIGHT, 70, SS_SPELLCRAFT, \
                             TS_WIS })

/* prototypes */
public void fortify_message(object caster, object *targets);
public mixed fortify_success(object caster, object *targets);
public object *fortify_target(string str);


void
create_spell_fortify(string arg)
{
    set_element(SS_ELEMENT_LIFE, 20);
    set_form(SS_FORM_DIVINATION, 50);

    set_spell_time(9);

    set_mana_spell(FORTIFY_MANA);
    /*set_mana_spell_fail(FORTIFY_MANA_FAIL);*/
    set_spell_object(FORTIFY_OBJECT);

    set_find_target(fortify_target);

    set_spell_task(FORTIFY_TASK);
    
    set_spell_message(fortify_message);
    set_spell_success(fortify_success);
}

string
fortify_mutter(mixed target)
{
    return "may the spirit of Paladine protect me";
}

public object *
fortify_target(string str)
{
    if (str && str != "me" && str != "myself")
      return 0;

    return ({ query_caster() });
}

public void
fortify_message(object caster, object *targets)
{
    caster->catch_msg("You feel the power of Paladine's protection " +
		      "shielding you.\n");
}

public mixed
fortify_success(object caster, object *targets)
{
    int result;

    fail_message = "";
    if (spell_failed)
      return 0;

    if (caster->query_prop(KNIGHT_I_DEVOTION) < caster->query_age() + 200)
      caster->add_prop(KNIGHT_I_DEVOTION, caster->query_age() + 200);
    
    fail_message = "You begin to pray but lose concentration.\n";
    if (random(caster->query_stat(SS_WIS)) < random(30))
      return 0;
    
    fail_message = "This prayer is already in operation!\n";
    if (present("shieldobj", caster))
      return 0;
    
    fail_message = "Despite your best efforts, your prayer is unheard.\n";
    if ((result = caster->resolve_task(FORTIFY_TASK,FORTIFY_LIST)) <= 0)
      return 0;

    set_duration(result + 120);
    reduce_spell_availability("fortify");
    return result;
}

mixed
do_fortify(string str)
{
    return cast_spell();
}
