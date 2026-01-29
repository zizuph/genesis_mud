/* ***************************************************************************
   NAME:       Storm
   TAX:        1.5% (uses recharge technique instead of material component)
   AoE:	       environment of caster only
   DESC:       Success clones a stormcould to the environment of the Knight
   REQUIRED:   Knight of Sword

	       ~Aridor, 09/95
*************************************************************************** */

#define STORM_OBJECT    SOBJ + "stormcloud"
#define STORM_MANA      100
#define STORM_MANA_FAIL 10
#define STORM_TASK    (TASK_DIFFICULT)
#define STORM_LIST    ({SS_FORM_DIVINATION, \
                        SKILL_WEIGHT, 70, SS_ELEMENT_LIFE, \
			SKILL_WEIGHT, 70, SS_SPELLCRAFT, \
                        SKILL_WEIGHT, 30, TS_WIS, \
			SKILL_WEIGHT, 50, TS_DIS, \
		        SKILL_WEIGHT, 50, TS_STR })

/* prototypes */
public void storm_message(object caster, object *targets);
public mixed storm_success(object caster, object *targets);
public object *storm_target(string str);


void
create_spell_storm(string arg)
{
    set_element(SS_ELEMENT_LIFE, 30);
    set_form(SS_FORM_DIVINATION, 50);
    set_spell_time(15);

    set_mana_spell(STORM_MANA);
    //set_mana_spell_fail(STORM_MANA_FAIL);

    set_spell_object(STORM_OBJECT);

    set_find_target(storm_target);

    set_spell_task(STORM_TASK);
    
    set_spell_message(storm_message);
    set_spell_success(storm_success);
}

string
storm_mutter(mixed target)
{
    return "may the wrath of Kiri-Jolith descend upon mine enemy";
}

public object *
storm_target(string str)
{
    if (str)
      return 0;

    return ({ E(query_caster()) });
}

public void
storm_message(object caster, object *targets)
{
    tell_room(E(caster),
	      "Suddenly, giant stormclouds draw together above you.\n");
}

public mixed
storm_success(object caster, object *targets)
{
    int result;

    fail_message = "";
    if (spell_failed)
      return 0;

    if (caster->query_prop(KNIGHT_I_DEVOTION) < caster->query_age() + 200)
      caster->add_prop(KNIGHT_I_DEVOTION, caster->query_age() + 200);
    
    fail_message = "You begin to pray but lose concentration.\n";
    if (random(caster->query_stat(SS_DIS)) < random(30))
      return 0;
    
    fail_message = "This prayer will only work outside.\n";
    if (E(caster)->query_prop(ROOM_I_INSIDE))
      return 0;

    fail_message = "This prayer is already in operation here!\n";
    if (present("stormcloud", E(caster)))
      return 0;
    
    fail_message = "Despite your best efforts, your prayer is unheard.\n";
    if ((result = caster->resolve_task(STORM_TASK,STORM_LIST)) <= 0)
      return 0;

    /* give a 75% malus if the spell wasn't rehearsed */
    if (temp_spell_availability > 0)
      result /= 4;

    reduce_spell_availability("storm");
    
    seteuid(getuid(this_object()));
    write_file("/d/Krynn/solamn/guild/log/stormspell",
	       "STORM: " + caster->query_name() +  " P: " + result + "\n");

    set_duration(result + 75);
    return result;
}

mixed
do_storm(string str)
{
    return cast_spell();
}
