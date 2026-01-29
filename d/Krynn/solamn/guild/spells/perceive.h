/* ***************************************************************************
   NAME:       Perceive
   TAX:        0.25 (uses recharge technique instead of material component)
   AoE:	       object/target
   DESC:       Success gives MAGIC_AM_ID_INFO
   REQUIRED:   Knight of Sword (Rose, too??) not in combat.

               Grace October 1994   
               Thanks to Olorin for help, guidance, and code.
               Modifications: ~Aridor, 07/95, 09/95
*************************************************************************** */

#define PER_TARG     ({ SKILL_MAX, "@@query_prop|" + MAGIC_I_RES_IDENTIFY + "@@", \
			  "@@query_prop|" + OBJ_I_RES_IDENTIFY + "@@", SKILL_END})
#define PER_MANA     30
#define PER_TASK     (TASK_DIFFICULT) /*+100*/
#define PER_LIST     ({SS_AWARENESS, \
                     SKILL_WEIGHT, 50, SS_FORM_DIVINATION, \
                     SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
                     TS_WIS})

/*prototypes*/
public object *perceive_target(string str);
public void perceive_message(object caster, object *targets);
public mixed perceive_success(object caster, object *targets);


void
create_spell_perceive()
{
    set_element(SS_ELEMENT_LIFE, 20);
    set_form(SS_FORM_DIVINATION, 18);
    set_spell_time(6);
    set_mana_spell(25);
    //set_mana_spell_fail(25);
    //set_spell_area_function("my_area_of_effect");

    set_find_target(perceive_target);

    set_spell_task(PER_TASK);
    set_spell_message(perceive_message);
    set_spell_success(perceive_success);
    set_spell_object(SOBJ + "perceiveobj");
    set_duration(1);
}

string
perceive_mutter(mixed target)
{
    return "reveal unto me the secret nature of " + target;
}

public object *
p_no_target_message()
{
    write("Perceive who or what?\n");
    return 0;
}

public object *
perceive_target(string str)
{
    int i;
    mixed targ;

    if (!str)
      return p_no_target_message();

    if (!parse_command(str,E(query_caster()),"[the] %o",targ))
      return p_no_target_message();
    
    return ({ targ });
}

public void
perceive_message(object caster, object *targets)
{
    set_this_player(caster);
    write("Your prayer is heard.\n");
    say(QCTNAME(TP) + "'s prayer is heard and " + LANG_THESHORT(targets[0]) +
	"glows briefly.\n");
    
}

public mixed
perceive_success(object caster, object *targets)
{
    int result;

    fail_message = "";
    if (spell_failed)
      return 0;

    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    fail_message = "You are too distracted by the combat to cast this spell.\n";
    if (caster->query_attack())
      return 0;
    
    fail_message = "Despite your best efforts, your prayer is unheard.\n";
    if ((result = caster->resolve_task(PER_TASK, PER_LIST,
				       targets[0], PER_TARG)) <= 0)
      return 0;

    //result *= 10;
    reduce_spell_availability("perceive");
    if (result > 75)
      result = 75;
    if (temp_spell_availability > 0)
      result /= 2;

    return result;
}

mixed
do_perceive(string str)
{
    return cast_spell();
}
