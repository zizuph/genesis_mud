inherit "/d/Genesis/newmagic/spellcasting";

#include <macros.h>

void
create()
{
    if (!IS_CLONE)
    {
        return;
    }

    add_spell("/d/Emerald/vamp/spells/summon_shade");
    add_spell("/d/Emerald/vamp/spells/fortitude");
    add_spell("/d/Emerald/vamp/spells/dark_aura");
    add_spell("/d/Emerald/vamp/spells/blind");
    add_spell("/d/Emerald/vamp/spells/perception");
    add_spell("/d/Emerald/vamp/spells/unseen");
    add_spell("/d/Emerald/vamp/spells/obfuscate");
    add_spell("/d/Emerald/vamp/spells/dash");
}

public object
mkspells(mixed for_whom)
{
    object spells;

    setuid();
    seteuid(getuid());
    
    if (stringp(for_whom))
    {
        for_whom = find_player(for_whom);
    }

    if (!for_whom)
    {
        return 0;
    }

    spells = clone_object(MASTER_OB(this_object()));
    spells->add_spell_object(for_whom);
    return spells;
}
