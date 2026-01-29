
 /* Kataraktas spell for the Elemental Worshippers of Calia
  * 
  * by Jaacar, September 10th, 1996
  * 
  */ 

#include <ss_types.h>
#include <tasks.h>

public void *kataraktas_target(string arg);
public void kataraktas_message(object caster, object target);
public string kataraktas_fail();

public void
create_spell_kataraktas()
{
    set_spell_element(SS_ELEMENT_WATER,25);
    set_spell_form(SS_FORM_DIVINATION,30);
    set_spell_ingredients("water vial");

    set_spell_duration(120); // 2 minutes
    set_spell_time(5);

    set_spell_mana(30);
    set_spell_object(WEIRD);
    set_find_target(kataraktas_target);

    set_spell_task(TASK_ROUTINE,0);
    set_spell_fail(kataraktas_fail);

    set_spell_message(kataraktas_message);
}

public int
kataraktas(string str)
{
    return cast_spell();
}

public object
*kataraktas_target(string str)
{
    /* Can only be cast here */
    if (str && str != "here" && str != "")
    {
        notify_fail("You may only use the power of Kataraktas here.\n");
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
kataraktas_message(object caster, object *targets)
{
    tell_room(environment(caster), QCTNAME(caster)+" throws down "+
        "a small vial of water.\n",({caster}));
    tell_object(caster,"You throw down a small vial of water.\n");
}

public string
kataraktas_fail()
{
    return "You fail to reach Lord Diabrecho with your request.\n";
}
