
inherit "/d/Genesis/magic/spell_effect_object";
inherit "/std/object";

#include <stdproperties.h>

varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
    set_spell_effect_desc("nuchta");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    set_alarm(180.0, 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    tell_room(environment(this_object()),"The room becomes light again.\n");
    remove_object();
    environment(this_object())->update_light();
    return 1;
}

void
create_object()
{
    set_name("nuchta_obj");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_LIGHT, -1);
}
