inherit "/std/object";
inherit "/d/Genesis/magic/spell_effect_object";

#include "../guild.h"
#include <stdproperties.h>

void
create_object()
{
    set_no_show();
    add_prop(OBJ_I_LIGHT, 1);
    set_name(RI_OBJECT);
    set_spell_effect_desc("light");
    add_prop(OBJ_M_NO_GET, 1);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
}

void
start()
{
    ::start();
    move(spell_caster, 1);
    set_alarm(800.0, 0.0, dispel_spell_effect);
}

varargs public int
dispel_spell_effect(object dispeller)
{
    object env;
    int l;

    if (spell_caster)
    {
        spell_caster->catch_msg("The power of your Ri spell fades.\n");

        env = environment(spell_caster);

        if ((l = env->query_prop(OBJ_I_LIGHT)) > 1)
	{
            tell_room(env, "The area dims slightly.\n");
	}
        else if (l < 1)
	{
            tell_room(env, "The darkness deepens.\n");
	}
        else
	{
            tell_room(env, "The area suddenly goes dark.\n");
	}
    }

    remove_spell_effect_object();
    return 1;
}

public void
remove_spell_effect_object()
{
    spell_target->remove_magic_effect(this_object());
    remove_object();
}
