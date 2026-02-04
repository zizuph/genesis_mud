/* Spell to be used with the goblinlord.c 
 * Tomas  -- May 2000
*/


inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";

#include <macros.h>

void
create_object()
{
    if (!IS_CLONE)
    {
        return;
    }

    set_name("spells");
    add_spell("/d/Terel/mountains/goblincave/spells/swarm");
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    add_spell_object(env);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}
