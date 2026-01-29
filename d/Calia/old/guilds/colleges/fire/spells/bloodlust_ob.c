/*
  This is the spell object for the bloodlust spell the Fire College
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

int defence, parry, polearm, speed;

void 
create_object()
{
    set_name("_bloodlust_ob_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}

void
angry_emotes()
{
    string *angry_em = ({"roar", "roar violently", "growl", "growl furiously",
        "explode", "fume", "steam", "scream"});
        
    spell_caster->command(angry_em[random(sizeof(angry_em))]);
    
    set_alarm(itof(10 + random(40)), 0.0, &angry_emotes());
}

public int
start()
{
    int stat = find_controlling_stat("fire", spell_caster);
  
    defence = spell_caster->query_skill(SS_DEFENCE);
    parry = spell_caster->query_skill(SS_PARRY);
    polearm = spell_caster->query_skill(SS_ELEMENT_FIRE) - 
        spell_caster->query_skill(SS_WEP_POLEARM);
    speed = min(50 + (random(stat) + random(stat))/2, 150);
    
    spell_caster->set_skill(SS_DEFENCE, 0);
    spell_caster->set_skill(SS_PARRY, 0);
    spell_caster->set_skill(SS_WEP_POLEARM, 
        spell_caster->query_skill(SS_ELEMENT_FIRE));
    spell_caster->add_prop(LIVE_I_QUICKNESS, 
        spell_caster->query_prop(LIVE_I_QUICKNESS) + speed);
        
        
    spell_caster->catch_tell("As you complete the enchantment, the" +
        " world begins to take on a red tint. The part of you that" +
        " you draw upon to use fire magic, but keep under taut" +
        " control, becomes dominant. Burning with rage, you stop" +
        " caring about anything not related to the destruction of" +
        " your enemies.\n");
        
    tell_room(environment(spell_caster), "As " + QTNAME(spell_caster) +
        " completes the spell, " + spell_caster->query_pronoun() + 
        " appears to grow increasingly angry!\n", spell_caster);
    
    set_alarm(itof(speed * 6), 0.0, &dispel_spell_effect());
    set_alarm(itof(10 + random(40)), 0.0, &angry_emotes());

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_caster->set_skill(SS_DEFENCE, 
        spell_caster->query_skill(SS_DEFENCE) + defence);
    spell_caster->set_skill(SS_PARRY, 
        spell_caster->query_skill(SS_PARRY) + parry);
    spell_caster->set_skill(SS_WEP_POLEARM, 
        spell_caster->query_skill(SS_WEP_POLEARM) - polearm);
    spell_caster->add_prop(LIVE_I_QUICKNESS, 
        spell_caster->query_prop(LIVE_I_QUICKNESS) - speed);
    
    spell_caster->catch_tell("The murderous rage begins to" +
        " subside, your normal, rational self returning.\n");
    tell_room(environment(spell_caster), QCTNAME(spell_caster) +
        " seems to calm down.\n", spell_caster);    
    
    
    remove_spell_effect_object();

    return 1;
}