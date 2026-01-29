
/*
 * fos_obj.c
 *
 * This is the spell object for the fos (Light) spell for 
 * the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, July 31st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER

void 
create_object()
{
    set_name("_fos_object_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_S_WIZINFO, "This is a spell object created by the "+
        "fos spell of the Spirit Circle of Psuchae.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_LIGHT,2);
}


public int
start()
{
    int gstat, spirit, spellcraft, divination, time;

    gstat = spell_target->query_stat(SS_OCCUP);
    spirit = spell_target->query_skill(SS_ELEMENT_SPIRIT);
    spellcraft = spell_target->query_skill(SS_SPELLCRAFT);
    divination = spell_target->query_skill(SS_FORM_DIVINATION);

    time = MIN(600,(gstat + spirit + spellcraft + divination + random(200)));
    
    set_spell_effect_desc("light");

    spell_target->add_subloc("_fos_object_subloc", TO);
    set_alarm(itof(time), 0.0, &dispel_spell_effect(TO));

    return 1;
}

public string
show_subloc(string subloc, object me, object observer)
{
  if((me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
     (subloc != "_fos_object_subloc"))
    return "";

  return "A bright halo sits above " + ( observer == me ? "your" :
      me->query_possessive() ) + " head.\n";
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("Your halo disappears.\n");
    say("The halo above "+QTNAME(spell_target)+" disappears.\n");

    TO->add_prop(OBJ_I_LIGHT,0);
    environment(TO)->upate_light(1);
    remove_spell_effect_object();
    return 1;
}