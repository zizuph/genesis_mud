/*
 * A Flame Blade spell
 * It is called from Rastlin's magic book.
 * 1994 by Rastlin.
 */
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

void
create_spell_flame(string arg)
{
    set_spell_element(SS_ELEMENT_FIRE, 20);
    set_spell_time(5);
    set_spell_mana_needed(10);
    set_spell_form(SS_FORM_ABJURATION, 10);
    set_spell_area_function("pre_find_target");
    set_spell_duration(30);
}

object *
pre_find_target(string str)
{
    object ob;

    ob = present(str, environment(query_caster()));
    
    return ({ ob });
}

public void
flame_message(object attacker)
{
    attacker->catch_msg("You cast flame blade.\n");
    tell_room(environment(attacker), QCTNAME(attacker) + " points at"
     + " the weapon.\n It starts to glow.\n", ({attacker}));
}

mixed
do_flame(string arg)
{
    object ob;
    int result, power;

    result = spell_calc_result(query_caster());

    if (result <= 0)
    {
        call_other(this_object(), spell_fail_cast);
        return;
    }

    power = spell_calc_power(query_caster(), result);

    ob = clone_object("/d/Krynn/rastlin/open/spells/obj/ob_flame");
    ob->move_spell(targets[0], power);

    flame_message(query_caster());

    return 1;
}



