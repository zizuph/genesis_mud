
 /* Psotia spell for the Elemental Worshippers of Calia
  * 
  * by Jaacar, September 10th, 1996
  * 
  * Modifications by Maniac 112/10/96
  */ 

#include <ss_types.h>
#include <tasks.h>

public void *psotia_target(string arg);
public void psotia_message(object caster, object target);
public string psotia_fail(); 

public void
create_spell_psotia()
{
    set_spell_element(SS_ELEMENT_FIRE,25);
    set_spell_form(SS_FORM_DIVINATION,30);
    set_spell_ingredients("fireweed");

    set_spell_duration(300);  // 5 Minutes
    set_spell_time(5);

    set_spell_mana(35);
    set_spell_object(DJINNI);
    set_find_target(psotia_target);

    set_spell_task(TASK_SIMPLE+50,0);

    set_spell_fail(psotia_fail); 

    set_spell_message(psotia_message);
}

public int
psotia(string str)
{
    return cast_spell();
}

public object
*psotia_target(string str)
{
    if (environment(query_caster())->query_prop(ROOM_UNDER_WATER))
    {
        write("You cannot use the power of Psotia underwater!\n");
        return 0;
    }
    if (environment(query_caster())->query_prop(ROOM_IN_WATER))
    {
        write("You cannot use the power of Psotia in water!\n");
        return 0;
    }
    /* Can only be cast here */
    if (str && str != "here" && str != "")
    {
        notify_fail("You may only use the power of Psotia here.\n");
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
psotia_message(object caster, object *targets)
{
    tell_room(environment(caster), QCTNAME(caster)+" places something "+
        "on the ground.\n",({caster}));
    tell_object(caster,"You place the fireweed on the ground in front of you.\n");
}

public string
psotia_fail()
{
    return "You fail to reach Lord Pyros with your request.\n";
}

