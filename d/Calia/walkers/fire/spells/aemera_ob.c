
/* Aemera Object

   Conjured by the Aemera spell of the Firewalkers.

   Coded by Jaacar 
   Parts taken from the wolfhelm coded by Maniac

   Light level modified by Bishop, June 12th 1999.

*/

#pragma strict_types

inherit "/d/Genesis/magic/spell_effect_object";
inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"
#include FIRE_HEADER

string aemera_a;
varargs public int dispel_spell_effect(object dispeller);

void
set_aemera_a()
{
    aemera_a = "luminous";
    set_adj(aemera_a);
}

void
init()
{
    ::init();
    wear_me();
}

public int
start()
{
    set_spell_effect_desc("aemera");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    set_this_player(spell_target);
    wear_me();  // We needed to set_this_player for this...

    spell_target->add_subloc(AEMERA_OBJ, this_object());
    set_alarm(480.0, 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_msg("The light surrounding you fades away "+
        "into nothingness.\n");
    tell_room(environment(spell_target),"The light surrounding "+
        QCTNAME(spell_target)+" fades away into nothingness.\n",
        ({spell_target}));

    spell_target->remove_shadow(AEMERA_SHADOW);
    remove_spell_effect_object();

    return 1;
}

void 
create_armour()
{
    set_name("daylight_obj");
    add_name(AEMERA_OBJ);
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_I_LIGHT,5);

    set_ac(0);
    set_at(A_MAGIC);
    set_af(this_object());

    set_shield_slot( ({ A_BODY }) );
}

public string
show_subloc(string subloc, object me, object observer)
{
    if((me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
        (subloc != AEMERA_OBJ) || query_worn() != me)
            return "";

    return (observer == me ? "You seem": capitalize(me->query_pronoun()+
        " seems"))+" to be fashioned out of pure light.\n";
}

public mixed
wear(object obj)
{
    object s;
    seteuid(getuid());
    s = clone_object(AEMERA_SHADOW);
    s->shadow_me(TP);
    return 1;
}

public mixed
remove(object obj)
{
    return 1;
}

int
query_recover()
{
    return 0;
}

void 
set_likely_break(int i)
{
    i=0;
    ::set_likely_break(i);
}

int 
set_condition(int i)
{
    i=0;
    ::set_condition(i);
}

varargs void
remove_broken(int silent = 0)
{
    return;
}
