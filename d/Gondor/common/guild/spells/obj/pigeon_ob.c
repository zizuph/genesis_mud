/*
 * A spell object for the 'whistle' spell.
 */
#pragma strict_types

inherit "/std/spells.c";
inherit "/d/Gondor/common/guild/spells/spell_funs.c";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"

#define SP_SUMM_MANA 10
#include "/d/Gondor/common/guild/spells/pigeon.c"

public void
create_spells()
{
    set_name("Pigeon_Spell_Object");
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
    add_spell("whistle", "do_whistle_spell", "Summon a carrier pigeon");
}

public int
query_skill_needed()
{
    return 15;
}

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if (!living(dest)) 
        set_alarm(1.0, 0.0, remove_object);
}

