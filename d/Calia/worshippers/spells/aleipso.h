
 /*
  * Aleipso (Heal) Spell for the Elemental Worshippers of Calia
  * by Jaacar
  * July 23rd, 1996
  */

#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>

public object *aleipso_target(string str);
public void aleipso_message(object caster, object target);
public string aleipso_fail();

public void
create_spell_aleipso()
{
    set_spell_element(SS_ELEMENT_WATER, 15);
    set_spell_form(SS_FORM_DIVINATION, 20);
    set_spell_time(5);
    set_spell_ingredients("cladina");
    set_spell_mana(100);
    set_find_target(aleipso_target);
    set_spell_message(aleipso_message);
    set_spell_task(TASK_SIMPLE,0);
    set_spell_fail(aleipso_fail);
}

public int
aleipso(string str)
{
    return cast_spell();
}

public int
aleipso_access(object ob)
{
    if (!living(ob) || ob->query_ghost())
        return 0;
    return 1;
}

public object *
aleipso_target(string str)
{
    object *list;
    if ((!str) || (str == "") || (str == "me") || (str == "myself"))
        return ({ query_caster() });
    list = CMDPARSE_ONE_ITEM(str, "aleipso_access","aleipso_access");
    if (sizeof(list) >1)
    {
        write("You cannot call the powers of Aleipso upon "+
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
aleipso_message(object caster, object *targets)
{
    int gstat;
    int heal;
    object poison;
    if (caster == targets[0])
    {
        tell_object(caster, "You feel the power of Lord Diabrecho racing "+
            "throughout your body, healing some of your wounds.\n");
        tell_room(environment(caster), QCTNAME(caster) + " glows "+
            "briefly.\n", ({ caster }));
        gstat = caster->query_base_stat(SS_LAYMAN);
        heal=(100+(gstat/2));
        if (heal > 200) heal = 200;
        caster->heal_hp(heal);
        if (objectp(poison=present("poison",caster)))
        {
            if (gstat > 40) gstat = 40;
            if (poison->query_type() != "standard")
                poison->cure_poison(({"all"}),(random(25)+gstat));
            else
                poison->cure_poison(({"standard"}),(random(15)+gstat));
        }
        return;
    }
    targets[0]->catch_msg(QCTNAME(caster)+" mumbles some strange words, "+
        "then briefly grasps your shoulder firmly.  You feel a wave of "+
        "energy flowing throughout your body.  When it has "+
        "passed, you notice some of your wounds have been healed.\n");
    tell_room(environment(caster), QCTNAME(caster)+" grasps "+
        LANG_POSS(QCTNAME(targets[0]))+" shoulder briefly.\n",
        ({ caster, targets[0] }));
    caster->catch_msg("You incant the arcane words of Aleipso, and grasp "+
        QTNAME(targets[0])+"'s shoulder briefly, healing some of "+
        targets[0]->query_possessive()+" wounds.\n");
        gstat = caster->query_base_stat(SS_LAYMAN);
        heal=(100+(gstat/2));
        if (heal > 200) heal = 200;
        targets[0]->heal_hp(heal);
        if (gstat > 40) gstat = 40;
        if (objectp(poison=present("poison",targets[0])))
        {
            if (caster->query_stat(SS_INT) > targets[0]->query_stat(SS_INT))
            {
                if (poison->query_type() != "standard")
                    poison->cure_poison(({"all"}),(random(25)+gstat));
                else
                    poison->cure_poison(({"standard"}),(random(15)+gstat));
            }
        }
}

public string
aleipso_fail()
{
    return "You fail to reach Lord Diabrecho with your request.\n";
}
