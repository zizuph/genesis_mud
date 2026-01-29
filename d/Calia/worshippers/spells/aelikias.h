
 /*
  *
  * Aelikias (Check Age) spell for the Elemental Worshippers of Calia
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

public object *aelikias_target(string arg);
public void aelikias_message(object caster, object *target);
public string aelikias_fail();

public void
create_spell_aelikias()
{
    set_spell_element(SS_ELEMENT_FIRE, 15);
    set_spell_form(SS_FORM_DIVINATION, 15);
    set_spell_time(1);
    set_spell_ingredients("chicory");
    set_spell_mana(36);
    set_find_target(aelikias_target);
    set_spell_message(aelikias_message);
    set_spell_fail(aelikias_fail);
    set_spell_task(TASK_SIMPLE,0);
}

public int
aelikias(string str)
{
    return cast_spell();
}

public int
aelikias_access(object ob)
{
    if (!living(ob) || ob->query_ghost())
        return 0;
    return 1;
}

public object *
aelikias_target(string str)
{
    object *list;

    if (sizeof(query_caster()->query_weapon(-1)))
    {
        write("You cannot use the power of Aelikias while wielding "+
            "a weapon!\n");
        return 0;
    }
    if (query_caster()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write("You cannot use the power of Aelikias while gagged!\n");
        return 0;
    }
    
    if ((!str) || (str == "me") || (str == "myself"))
        return ({ query_caster() });
    list = CMDPARSE_ONE_ITEM(str, "aelikias_access","aelikias_access");
    if (sizeof(list) >1)
    {
        write("You cannot call the powers of Aelikias upon "+
            " more than one person at the same time!\n");
        return 0;
    }
    else if (!sizeof(list))
    {
        write("You find no such living creature.\n");
        return 0;
    }
    return list;
}

public void
aelikias_message(object caster, object *target)
{
    string mesg;
    int days;

    days = target[0]->query_age() / (30*60*24);

    switch(days)
    {
    case 0:
        mesg = "less than one day"; break;
    case 1..4:
        mesg = "less than five days"; break;
    case 5..9:
        mesg = "less than ten days"; break;
    case 10..14:
        mesg = "less than fifteen days"; break;
    case 15..19:
        mesg = "less than twenty days"; break;
    case 20..24:
        mesg = "less than twenty-five days"; break;
    case 25..29:
        mesg = "less than thirty days"; break;
    case 30..34:
        mesg = "less than thirty-five days"; break;
    case 35..39:
        mesg = "less than fourty days"; break;
    case 40..44:
        mesg = "less than fourty-five days"; break;
    case 45..49:
        mesg = "less than fifty days"; break;
    case 50..59:
        mesg = "less than sixty days"; break;
    case 60..69:
        mesg = "less than seventy days"; break;
    case 70..79:
        mesg = "less than eighty days"; break;
    case 80..89:
        mesg = "less than ninety days"; break;
    case 90..99:
        mesg = "less than one hundred days"; break;
    default:
        mesg = "at least one hundred days"; break;
    }
    
    if (caster->query_skill(SS_CARVED) == ALL_FLAGS)
    {
        caster->catch_msg("You summon the powers of Lord Pyros upon "+
            capitalize(target[0]->query_real_name())+" and divine "+
            target[0]->query_pronoun()+" is "+mesg+" old.\n");
    }
    else
    {
        caster->catch_msg("You summon the powers of Lord Pyros upon "+
            QTNAME(target[0])+" and divine "+target[0]->query_pronoun()+
            " is "+mesg+" old.\n");
    }
}

public string
aelikias_fail()
{
    return "You fail to reach Lord Pyros with your request.\n";
}

