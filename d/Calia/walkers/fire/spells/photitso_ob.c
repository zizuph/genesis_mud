
/* Photitso Object

   Conjured by the Photitso spell of the Firewalkers.

   Coded by Jaacar 
   Description modified by Bishop, 9th april 1999.
*/

#pragma strict_types

inherit "/d/Genesis/magic/spell_effect_object";
inherit "/std/object";

#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"
#include FIRE_HEADER

varargs public int dispel_spell_effect(object dispeller);
public void remove_spell_effect_object();

public int
start()
{
    set_spell_effect_desc("light");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    spell_target->add_subloc(PHOTITSO_OBJ, this_object());
    set_alarm(300.0, 0.0, dispel_spell_effect);

    return 1;
}

public void
remove_spell_effect_object()
{
    spell_target->remove_magic_effect(this_object());
    remove_object();
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_msg("The flame over your hand fades away.\n");
    tell_room(environment(spell_target),"The flame over "+
        QCTNAME(spell_target)+"'s hand fades away.\n",
        ({spell_target}));

    environment(this_object())->update_light();
    remove_spell_effect_object();

    return 1;
}

void 
create_object()
{
    set_name("light_obj");
    add_name(PHOTITSO_OBJ);
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_LIGHT,1);

}

public string
show_subloc(string subloc, object me, object observer)
{
    if((me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
        (subloc != PHOTITSO_OBJ))
            return "";

    return "A steady heatless flame"+
        " burns in the air over " + ( observer == me ? "your" :
        me->query_possessive() ) +" hand.\n";
}

