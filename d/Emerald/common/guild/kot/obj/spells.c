inherit "/std/object";
inherit "/d/Genesis/magic/spellcasting";

#include "../guild.h"

#include <tasks.h>
#include <ss_types.h>
#include <stdproperties.h>

public int create_spell_ri(object caster, object *targets, string argument);

void
create_object()
{
    set_no_show();
    set_name("Order of Telan-Ri spells");
    add_spell("ri", "Bring light to your surroundings", create_spell_ri);
    add_prop(OBJ_M_NO_GET, 1);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_DROP, 1);
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

public int
create_spell_ri(object caster, object *targets, string argument)
{
    set_spell_time(8);
    set_spell_mana(10);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_CONJURATION, 5);
    set_spell_ingredients(({ CRYSTAL_OBJECT }));
    return 0;
}    

public void
ri(object caster, object *targets, int *resist, int result)
{
    object env;
    int l;

    if (present(RI_OBJECT, caster))
    {
        caster->catch_tell("You already have a \"Ri\" spell in effect.\n");
        return;
    }

    caster->catch_tell("Your prayer to Telan-Ri is answered.\n");

    env = environment(caster);

    if ((l = env->query_prop(OBJ_I_LIGHT)) < 0)
    {
        tell_room(env, "The darkness fades slightly.\n");
    }
    else if (l > 0)
    {
        tell_room(env, "The area brightens slightly.\n");
    }
    else
    {
        tell_room(env, "The darkness in the area lifts.\n");
    }

    make_spell_effect_object(KOT_OBJ_DIR + "ri_obj", caster, caster, 
        resist, result);
}    
