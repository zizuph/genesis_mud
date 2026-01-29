/*
 * Teikos
 * 
 * Create and moves a magic armour to the caster
 *
 */

#include <ss_types.h>
#include <tasks.h>

public object *teikos_target(string arg);
public void teikos_message(object caster, object target);
public string teikos_fail(); 

public void
create_spell_teikos()
{
    set_spell_element(SS_ELEMENT_EARTH, 15);
    set_spell_form(SS_FORM_DIVINATION, 20);

    set_spell_duration(600); // 10 minutes
    set_spell_time(2);
    set_spell_ingredients("rock");

    set_spell_mana(100);
    set_spell_object(TEIKOS_OBJ);
    set_find_target(teikos_target);

    set_spell_fail(teikos_fail); 

    set_spell_task(TASK_SIMPLE, 0);

    set_spell_message(teikos_message);
}


string
teikos_fail()
{
    return "You fail to reach Lady Gu with your request.\n";
}


public int teikos(string str)
{
    return cast_spell();
}

public object *teikos_target(string str)
{
   /* Can only cast it on yourself */
    if(str && str != "me" && str != "myself" && str != "")
   {
     notify_fail("You may only grant the protection upon yourself.\n");
     return 0;
   }

   /* Can only have one */
   if(present(TEIKOS_ARM, query_caster()))
   {
     write("You are already protected.\n");
     return 0;
   }

    return ({ query_caster() });
}

public void teikos_message(object caster, object *targets)
{
  tell_room(environment(caster), QCTNAME(caster) + " is suddenly surrounded "
    + "by a strange, faceted field of grey light.\n", ({ caster }));
}


