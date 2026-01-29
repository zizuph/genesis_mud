/*
 * A healing spell
 * It is called from Rastlin's magic book.
 * 1994 by Rastlin.
 */
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

void
create_spell_heal(string arg)
{
    set_spell_element(SS_ELEMENT_FIRE, 20);
    set_spell_time(5);
    set_spell_mana_needed(10);
    set_spell_form(SS_FORM_ABJURATION, 10);
}

public void
heal_message(object attacker, object enemy)
{
    write("You cast healing.\n");
    say(QCTNAME(attacker) + " heals someone.\n", ({attacker}));
}

mixed
do_healing(string arg)
{
    heal_message(this_player(), targets[0]);
    
    targets[0]->set_hp(targets[0]->query_hp() + 20);
    return 1;
}
