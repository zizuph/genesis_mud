
/* Ochetos (Armour of Air) Armour

   Conjured by the Ochetos spell of the Windwalkers.

   Coded by Jaacar 

*/

#pragma strict_types

inherit "/std/armour";
inherit "/d/Genesis/magic/spell_effect_object";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include WIND_HEADER

varargs public int dispel_spell_effect(object dispeller);

void 
create_armour()
{
    set_name("wind_arm");
    add_name(OCHETOS_OBJ);
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); 

    set_ac(30);
    set_at(A_MAGIC);
    set_af(this_object());

    set_shield_slot( ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS}) );

}

void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);
    wear_me();
}

public int
start()
{
    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    spell_target->add_subloc(OCHETOS_OBJ, this_object());
    set_alarm(600.0, 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("The shimmering shield of air disappears!\n");
    tell_room(environment(spell_target),"The shimmering shield of air surrounding "+
        QNAME(spell_target)+" vanishes.\n",({ spell_target }));

    remove_me();
    remove_spell_effect_object();

    return 1;
}

public string
show_subloc(string subloc, object me, object observer)
{
    if((me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
        (subloc != OCHETOS_OBJ) || query_worn() != me)
            return "";

    return "A shimmering shield of air "+
        "surrounds " + ( observer == me ? "you" :
        me->query_objective() ) + ".\n";
}

/*
 * Function name: got_hit
 * Description:   Notes that the defender has been hit. It can be used
 *                to reduce the ac for this hitlocation for each hit.
 * Arguments:     hid:   The hitloc id, ie the bodypart hit.
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage done to us in hit points
 */
varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    if(dam <= 0)
        return 0;


    spell_target->catch_msg("The shimmering shield of air " +
        "shifts around you.\n");
    tell_room(environment(query_worn()),"The shimmering shield of air surrounding "+
        QNAME(spell_target)+" shifts.\n",({ spell_target }));

    return ::got_hit(hid, ph, att, dt, dam);
}

/*
 * called from the set_at - we want to be able to wear
 * the armour without printing messages
 */
public mixed
wear(object obj)
{
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
