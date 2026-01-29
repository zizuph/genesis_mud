
 /* Stous spell for the Elemental Worshippers of Calia
  * 
  * by Jaacar, September 10th, 1996
  *
  * Modified by Quintas June 3, 2003
  *   Added FEATHER define and changed set_spell_ingredients
  *   FEATHER also defined in Anemos and feather.c
  *
  */ 

#include <ss_types.h>
#include <tasks.h>

#define FEATHER "_worshipper_feather_id_"

public void *stous_target(string arg);
public void stous_message(object caster, object target);
public string stous_fail(); 

public void
create_spell_stous()
{
    set_spell_element(SS_ELEMENT_AIR,20);
    set_spell_form(SS_FORM_DIVINATION,30);
    set_spell_ingredients(FEATHER);

    set_spell_duration(360); // 6 minutes
    set_spell_time(5);

    set_spell_mana(45);
    set_spell_object(SPIRIT);
    set_find_target(stous_target);

    set_spell_fail(stous_fail); 

    set_spell_task(TASK_SIMPLE+50,0);

    set_spell_message(stous_message);
}

public int
stous(string str)
{
    return cast_spell();
}

string
stous_fail()
{
    return "You fail to reach Lady Aeria with your request.\n"; 
}

public object
*stous_target(string str)
{
    /* Can only be cast here */
    if (str && str != "here" && str != "")
    {
        write("You may only use the power of Stous here.\n");
        return 0;
    }

    /* Can only have one summoned creature */
    if (query_caster()->query_prop(WOR_CREATURE_SUMMONED))
    {
        write("You may only summon one creature at a time!\n");
        return 0;
    }
    return ({ query_caster() });
}

public void
stous_message(object caster, object *targets)
{
    tell_room(environment(caster), QCTNAME(caster)+" throws a "+
        "feather into the air.\n",({caster}));
    tell_object(caster,"You throw a feather into the air.\n");
}
