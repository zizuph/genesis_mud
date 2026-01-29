/* spell_test.c
 *
 * This is a simple example of a spellcasting object.
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

    setuid();
    seteuid(getuid());

    set_name("spells");
    
    add_spell("/d/Genesis/newmagic/examples/spells/ice_bolt");
    add_spell("/d/Genesis/newmagic/spells/identify");
    add_spell("/d/Genesis/newmagic/spells/invisibility");
    add_spell("/d/Genesis/newmagic/examples/spells/heal");

    add_spell(clone_object("/d/Genesis/newmagic/spells/tell"));
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

public void
remove_object()
{
    /* Remove any cloned instances of spells that are registered with this
     * spellcasting object so that they aren't sitting around just taking up
     * memory.  You can either call remove_object() in the spells yourself,
     * or use the utility function cleanup_spells() to do it.
     */
    cleanup_spells();
    ::remove_object();
}
