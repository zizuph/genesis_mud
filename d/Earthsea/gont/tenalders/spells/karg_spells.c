#pragma strict_types

inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";

#include <macros.h>

private string spell_verb;

public void
create_object()
{
    if(!IS_CLONE)
    {
      return;
    }

    setuid();
    seteuid(getuid());
    add_prop(OBJ_I_INVIS, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();

    set_name("_karg_spells_");   /* A name for the object. */

    /* Now we add the spells. */  
    add_spell("/d/Earthsea/gont/tenalders/spells/fireball");
}

public void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    add_spell_object(env);
}

public void
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
