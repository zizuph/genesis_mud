/* ***************************************************************************
   NAME:       Radiance
   TAX:        0.2% * 1.5 (no material component + no rehearsing) = 0.3%
   AoE:	       caster only
   DESC:       Success creates a light object.
   REQUIRED:   Knight of Sword or Knight of Rose

               Grace October 1994  
	       ~Aridor, 07/95, 09/95
*************************************************************************** */

#define RADIANCE_MANA     15   /*(Same for failure and success)*/
#define RADIANCE_TASK     (TASK_ROUTINE)
#define RADIANCE_LIST     ({SKILL_AVG, SS_ELEMENT_LIFE, SS_ELEMENT_FIRE, SKILL_END,\
			  SS_FORM_DIVINATION,\
			  SS_SPELLCRAFT, \
			  TS_WIS})

/*prototypes*/
public object *radiance_target(string str);
public void radiance_message(object caster, object *targets);
public mixed radiance_success(object caster, object *targets);


void
create_spell_radiance(string arg)
{
    set_element(SS_ELEMENT_LIFE, 10);
    set_form(SS_FORM_DIVINATION, 8);

    set_spell_time(4);

    set_mana_spell(RADIANCE_MANA);
    /*set_mana_spell_fail(RADIANCE_MANA);*/
    set_spell_object(SOBJ + "lightobj");

    set_find_target(radiance_target);

    set_spell_task(RADIANCE_TASK);

    set_spell_message(radiance_message);
    set_spell_success(radiance_success);
}

string
radiance_mutter(mixed target)
{
    return "shed light unto me";
}

public object *
radiance_target(string str)
{
    if (str)
      return 0;

    return ({ query_caster() });
}

public void
radiance_message(object caster, object *targets)
{
    set_this_player(caster);
    write("Your prayer is heard and your medal begins to glow.\n");
    say(QCTNAME(TP) + "'s medal begins to glow!\n");
    
}

public mixed
radiance_success(object caster, object *targets)
{
    int result;

    fail_message = "";
    if (spell_failed)
      return 0;

    fail_message = "That prayer is already in operation.\n";
    if (P("lightobj",caster))
      return 0;

    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    fail_message = "Despite your best efforts, your prayer is unheard.\n";
    if ((result = TP->resolve_task(RADIANCE_TASK, RADIANCE_LIST)) <= 0)
      return 0;

    /* Use the result as duration, ignore it as the power value */
    set_duration(result * 3);

    return result;
}

mixed
do_radiance(string str)
{
    return cast_spell();
}
