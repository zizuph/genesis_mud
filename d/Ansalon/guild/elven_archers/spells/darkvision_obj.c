inherit "/d/Genesis/newmagic/spell_effect_object";

#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Ansalon/guild/elven_archers/guild.h"

#define ELF_VISION "_ansalon_archers_elf_vision"

varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
    set_spell_effect_desc("darkvision");

    spell_target->add_prop(LIVE_I_SEE_DARK, 
        (int)spell_target->query_prop(LIVE_I_SEE_DARK) + 1);
    spell_target->add_prop(ELF_VISION, 1);

    set_alarm(300.0, 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    if (spell_target)
    {
        spell_target->catch_tell("You feel your vision return to normal.\n");
        spell_target->add_prop(LIVE_I_SEE_DARK,
            (int)spell_target->query_prop(LIVE_I_SEE_DARK) - 1);
        spell_target->remove_prop(ELF_VISION);
    }

    remove_spell_effect_object();

    return 1;
}
