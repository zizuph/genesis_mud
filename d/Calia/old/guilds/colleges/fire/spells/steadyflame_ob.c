/*
  This is the spell object for the light spell the Fire College
  uses. 

  Coded by Bishop of Calia, June 2003.

 */
 
#pragma strict_types

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/d/Calia/guilds/colleges/specials/common_functions";
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"

string adj = "fluttering";

void 
create_object()
{
    set_name("_steadyflame_ob_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_LIGHT, 2);
}


public string
show_subloc(string subloc, object me, object observer)
{
    if((me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
        (subloc != "_steadyflame_ob_"))
            return "";

    return "A " + adj + " heatless flame"+
        " burns in the air over " + ( observer == me ? "your" :
        me->query_possessive() ) +" right shoulder.\n";
}

public int
start()
{
    int stat = find_controlling_stat("fire", spell_caster);
    string *descs = ({"fluttering", "flickering", "pulsating", 
        "steady", "powerful"});
    
    adj = descs[min(stat/40, 4)];
    //Duration 5-30 minutes:
    stat = min(300 + (random(stat) + random(stat))*5, 1800);

    set_spell_effect_desc("light");
    
    spell_caster->catch_tell("A " + adj + " heatless flame springs" +
        " into being over your right shoulder, lighting your" +
        " path.\n");
    say("A " + adj + " heatless flame springs into being over " +
        LANG_POSS(QTNAME(spell_caster)) + " right shoulder.\n",
        spell_caster);        
    spell_target->add_subloc("_steadyflame_ob_", TO);        
    
    set_alarm(itof(stat), 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_caster->catch_tell("The " + adj + " flame over your right"+
        " shoulder winks out.\n");
    say("The " + adj + " heatless flame over " +
        LANG_POSS(QTNAME(spell_caster)) + " right shoulder winks" +
        " out.\n", spell_caster);          
    
    remove_spell_effect_object();

    return 1;
}