inherit "/d/Liwitch/quis/open/new_spells/spell.c";
inherit "/d/Liwitch/quis/open/new_spells/spell_effect.c";
#include <ss_types.h>
 
#include "spells.h"

create_spell()
{
    set_name("spell");
    add_adj("bless");

    change_prop(SPELL_AI_FORM, ({SS_FORM_ENCHANTMENT, 15}));
    change_prop(SPELL_AI_ELEMENT, ({SS_ELEMENT_LIFE, 15}));
    change_prop(SPELL_AM_MATERIALS, 0);
    change_prop(SPELL_I_CASTING_TIME, 15);
    change_prop(SPELL_I_DIFFICULTY, 5);
    change_prop(SPELL_I_MANA, 5);
    change_prop(SPELL_O_EFFECT, this_object());


}
