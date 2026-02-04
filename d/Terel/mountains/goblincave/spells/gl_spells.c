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
    set_no_show();
    add_spell("/d/Terel/mountains/goblincave/spells/iceshard");


    add_prop(OBJ_M_NO_DROP,"Oddly enough, you can't seem to "+
        "do that.\n");
    add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
        "for you to simply give it away.\n");
    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
    add_prop(OBJ_M_NO_STEAL, 1);

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
