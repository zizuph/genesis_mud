
 /* Choma spell for the Elemental Worshippers of Calia
  * 
  * by Jaacar, September 10th, 1996
  * 
  * Modifications by Maniac 12/10/96
  * 
  */ 

#include <ss_types.h>
#include <tasks.h>

public void *choma_target(string arg);
public void choma_message(object caster, object target);
public string choma_fail(); 

public void
create_spell_choma()
{
    set_spell_element(SS_ELEMENT_EARTH,30);
    set_spell_form(SS_FORM_DIVINATION,30);

    set_spell_duration(600); // 10 minutes
    set_spell_time(5);
    set_spell_ingredients("rock");

    set_spell_mana(45);
    set_spell_object(GOLEM);
    set_find_target(choma_target);

    set_spell_task(TASK_ROUTINE, 0);

    set_spell_fail(choma_fail); 

    set_spell_message(choma_message);
}

public int
choma(string str)
{
    return cast_spell();
}

public object
*choma_target(string str)
{
    /* Can only be cast here */
    if (str && str != "here" && str != "")
    {
        notify_fail("You may only use the power of Choma here.\n");
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
choma_message(object caster, object *targets)
{
    tell_room(environment(caster), QCTNAME(caster)+" throws down "+
        "a rock.\n",({caster}));
    tell_object(caster,"You throw down a rock.\n");
}


public string
choma_fail()
{
    return "You fail to reach Lady Gu with your request.\n";
}

