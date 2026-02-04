inherit "/d/Liwitch/quis/open/new_spells/spell.c";
#include <ss_types.h>
 
#include "spells.h"

create_spell()
{
    set_name("spell");
    add_adj("light");

    change_prop(SPELL_AI_FORM, ({SS_FORM_ENCHANTMENT, 15}));
    change_prop(SPELL_AI_ELEMENT, ({SS_ELEMENT_AIR, 15}));
    change_prop(SPELL_AM_MATERIALS, ({"staff"}));
    change_prop(SPELL_I_CASTING_TIME, 15);
    change_prop(SPELL_I_DIFFICULTY, 5);
    change_prop(SPELL_I_MANA, 5);
    change_prop(SPELL_O_EFFECT, this_object());


}
