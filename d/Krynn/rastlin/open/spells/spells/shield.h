/*
 * A protecting force field.
 * It is called from Rastlin's magic book.
 * 1994 by Rastlin.
 */
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

void
create_spell_firewall(string arg)
{
    set_spell_element(SS_ELEMENT_FIRE, 20);
    set_spell_time(2);
    set_spell_mana_needed(10);
    set_spell_form(SS_FORM_ABJURATION, 10);
    set_spell_duration(30);
    set_spell_protect();
}

mixed
do_shield(string arg)
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
    
    seteuid(getuid());

    ob = clone_object("/d/Krynn/rastlin/open/spells/obj/ob_shield");
    ob->move_spell(query_targets()[0], power);
    
    return 1;
}





