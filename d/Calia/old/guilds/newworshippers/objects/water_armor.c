/*
  Water (ice) armour for the Worshippers. Comes as a result of a player
  sacrificing his elemental to become an armour.

  Coded by Bishop of Calia, 04/07/03.

 */

#pragma strict_rypes

inherit "/std/armour";
inherit "/d/Genesis/magic/spell_effect_object";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

void 
create_armour()
{
    set_name("wor_elem_arm");
    set_short("wor_elem_arm");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
    add_prop(MAGIC_AM_MAGIC,({20,"conjuration"}));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); 
    add_prop(OBJ_S_WIZINFO, "This is an armour that is summoned by" +
        " a member of the Elemental Worshippers of Calia. They get" +
        " it by sacrificing a summoned water elemental. Inquire with" +
        " guildmaster if you need access to the code.\n"); 
        
    set_ac(0);
    set_at(A_MAGIC);
    set_af(this_object());

    /*      slash, impale, bludgeon */
    set_am(({ 2, 0, 2 }));

    set_shield_slot( ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS}) );

}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if (dest == spell_caster)
    {
        set_this_player(spell_caster);
        wear_me();
        set_this_player(this_player());
    }
}

public int
start()
{

    set_spell_effect_desc("ice armor");
    
    spell_target->add_subloc("_wor_water_armor", this_object());
    
    set_ac(min(22 + random(spell_caster->query_stat(SS_LAYMAN))/8, 32));
    
    if (spell_caster->query_wiz_level())
    {
        spell_caster->catch_tell("Shield AC is: " + this_object()->query_ac()
            + ".\n");
    } 

    set_alarm(600.0, 0.0, &dispel_spell_effect(spell_caster));

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("The solid ice shield "+
        "melts, leaving no trace behind save a small puddle.\n");
    tell_room(environment(spell_target),"The solid ice shield "+
        "surrounding "+ QNAME(spell_target)+" melts, "+
        "leaving no trace behind save a small puddle.\n",({ spell_target }));

    remove_me();
    remove_spell_effect_object();

    return 1;
}

public string
show_subloc(string subloc, object me, object observer)
{
    if (subloc != "_wor_water_armor")
        return me->show_subloc(subloc, me, observer);

    if ((me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) || query_worn() != me))
            return "";

    return "A solid ice shield "+
        "protects " + ( observer == me ? "you" :
        me->query_objective() ) + ".\n";
}

/*
 * Function name: got_hit
 * Description:   Notes that the defender has been hit. It can be used
 *                to reduce the ac for this hitlocation for each hit.
 *                
 *                The ice armor is powerful, but brittle, and is reduced
 *                in effectiveness as it suffers hits.
 * 
 *
 *
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
    int frequency;
    
    if (spell_caster->query_stat(SS_LAYMAN) < 45)
    {
        frequency = 3; // 33% chance of shield diminishing after hit.
    }
    else if (spell_caster->query_stat(SS_LAYMAN) < 90)
    {
        frequency = 4; // 25% chance of shield diminishing after hit.
    }
    else
    {
        frequency = 5; // 20% chance of shield diminishing after hit.
    }

    if (dam > 0 && !random(frequency))
    {
        if (this_object()->query_ac() < 6)
        {
            dispel_spell_effect(spell_caster);
        }
        else
        {
            set_ac(this_object()->query_ac() - 1);
            spell_caster->catch_tell("Shards fly as your ice shield is hit.\n");
            spell_caster->tell_watcher("Shards fly as " + 
                LANG_POSS(QTNAME(spell_caster)) + " ice shield is hit.\n");
            if (spell_caster->query_wiz_level())
            {
                spell_caster->catch_tell("Ice shield AC is now " + 
                    this_object()->query_ac() + ".\n");
            }               
        }
    }

    ::got_hit(hid, ph, att, dt, dam);
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
