
 /*
  *
  * Thanatos (Check Killer) spell for the Elemental Worshippers of Calia
  * by Jaacar   August 7th, 1996
  *
  */

#include <ss_types.h>
#include <cmdparse.h>
#include <wa_types.h>
#include <macros.h>
#include <tasks.h>
#include <formulas.h>
#include <stdproperties.h>

public object *thanatos_target(string arg);
public void thanatos_message(object caster, object *target);
public string thanatos_fail();

public void
create_spell_thanatos()
{
    set_spell_element(SS_ELEMENT_EARTH, 15);
    set_spell_form(SS_FORM_DIVINATION, 15);
    set_spell_time(1);
    set_spell_ingredients("rock");
    set_spell_mana(36);
    set_find_target(thanatos_target);
    set_spell_message(thanatos_message);
    set_spell_fail(thanatos_fail);
    set_spell_task(TASK_SIMPLE,0);
}

public int
thanatos(string str)
{
    return cast_spell();
}

public int
thanatos_access(object ob)
{
    return pointerp(ob->query_prop(CORPSE_AS_KILLER));
}

public object *
thanatos_target(string str)
{
    object *list;

    if (sizeof(query_caster()->query_weapon(-1)))
    {
        write("You cannot use the power of Thanatos while wielding "+
            "a weapon!\n");
        return 0;
    }
    if (query_caster()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write("You cannot use the power of Thanatos while gagged!\n");
        return 0;
    }
    
    if (!str || !strlen(str))
    {
        write("Call the powers of Thanatos on what?\n");
        return 0;
    }
    list = CMDPARSE_ONE_ITEM(str, "thanatos_access","thanatos_access");
    if (sizeof(list) >1)
    {
        write("You cannot call the powers of Thanatos upon "+
            " more than one corpse at the same time!\n");
        return 0;
    }
    else if (!sizeof(list))
    {
        write("You find no such corpse here.\n");
        return 0;
    }
    return list;
}

public void
thanatos_message(object caster, object *target)
{
    string *mesg;
    
    mesg = target[0]->query_prop(CORPSE_AS_KILLER);
    caster->catch_msg("You summon the powers of Lady Gu upon "+
        target[0]->short()+" and divine it was slain by "+
        LANG_ADDART(mesg[1])+".\n");
    tell_room(environment(caster),QCTNAME(caster)+" kneels briefly "+
        "before "+target[0]->short()+" and prays.\n",
        caster);
}

public string
thanatos_fail()
{
    return "You fail to reach Lady Gu with your request.\n";
}

