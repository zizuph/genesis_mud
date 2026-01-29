/*
 * Cure Light injury
 * 
 * This spell will heal a npc/player.
 * The amount if hp gained will be in the ranger 100-500 based
 * on the result.
 */

#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>

public object *cure_target(string str);
public void cure_message(object caster, object target);

public void
create_spell_cure()
{
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_TRANSMUTATION, 25);
    set_spell_time(3);
    set_spell_mana(100);
    set_find_target(cure_target);
    set_spell_message(cure_message);
    set_spell_task(TASK_SIMPLE, 0);
}

public int
cure_light(string str)
{
    return cast_spell();
}

public int
heal_access(object ob)
{
    if (!living(ob) || ob->query_ghost())
        return 0;
    return 1;
}

public object *
cure_target(string str)
{
    object *list;
    string str2;

    if (!str)
    {
        write("Cure who?\n");
	return 0;
    }

    if ((str == "me") || (str == "myself"))
        return ({ query_caster() });

    list = CMDPARSE_ONE_ITEM(str, "heal_access", "heal_access");
    if (sizeof(list) > 1)
    {
        str2 = COMPOSITE_LIVE(list);
        write(break_string("Be specific, you can't cure " + str2 +
                    " at the same time.\n",76));
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
cure_message(object caster, object *targets)
{
    if (caster == targets[0])
    {
        tell_object(caster, "You can feel how the magic power travels " +
                "through your body, curing some of your wounds.\n");

        tell_room(environment(caster), QCTNAME(caster) + " shivers " +
              "slightly.\n", ({ caster }) );
 
        return;
    }

    targets[0]->catch_msg(QCTNAME(caster) + " touches your forhead and " +
		"you can feel how a strange force travels " +
		"through your body, curing some of your wounds.\n");

    tell_room(environment(caster), QCTNAME(caster) + " touches " +
	      LANG_POSS(QCTNAME(targets[0])) + " forhead.\n", 
	      ({ caster, targets[0] }) );
 
    caster->catch_msg("You " +
		"body of " + QTNAME(targets[0]) + ", curing some of " +
		targets[0]->query_possessive() + " wounds.\n");
}


