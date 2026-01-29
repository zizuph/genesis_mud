/*
  This is a testing spell object, used to test the new
  Worshipper spells as we code them.
  
  Bishop of Calia, June 2003.

*/

inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting.c";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <options.h>
#include <language.h>
#include <filter_funs.h>
#include <macros.h>
#include "defs.h"


void
create_object()
{
    if (!IS_CLONE)
    {
        return;
    }

    set_name("wand");
    add_name("worshipper_test_wand");
    set_short("cool ivory wand");
    
    set_long("This ivory wand feels cool in your hand, and is surprisingly" +
        " light. Since you have it, you must be a wizard, therefore further" +
        " description seems pointless. <wandhelp> should give you a list" +
        " of the spells the wand can currently help you cast.\n");
        
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL,1);
    
    add_spell("/d/Calia/newworshippers/spells/t_anemos.c");
    add_spell("/d/Calia/newworshippers/spells/t_floga.c");
    add_spell("/d/Calia/newworshippers/spells/t_aleipso.c");
    add_spell("/d/Calia/newworshippers/spells/t_evimero.c");
    add_spell("/d/Calia/newworshippers/spells/t_apodosi.c");
    add_spell("/d/Calia/newworshippers/spells/t_dynami.c");
    add_spell("/d/Calia/newworshippers/spells/t_psotia.c");
    add_spell("/d/Calia/newworshippers/spells/t_choma.c");
    add_spell("/d/Calia/newworshippers/spells/t_kataraktas.c");
    add_spell("/d/Calia/newworshippers/spells/t_stous.c");
    add_spell("/d/Calia/newworshippers/spells/t_pagos.c");
}

int
wandhelp()
{
    environment(this_object())->catch_tell("The spells currently in the" +
        " wand are: \n" +
        " Anemos - A basic tell line to other guild members. \n" +
        " Floga - A fire bolt spell for Pyros worshippers. \n" +
        " Aleipso - A healing spell for Diabrecho worshippers. \n" +
        " Evimero - A haste spell for Aeria worshippers. \n" +
        " Dynami - A stat boost spell for Gu worshippers. \n" +
        " Apodosi - A teleport spell, sends you to the Worshipper temple.\n" +
        " Psotia - Summon a fire elemental.\n" +
        " Choma - Summon an earth elemental.\n" +
        " Kataraktas - Summon a water elemental.\n" +
        " Stous - Summon an air elemental.\n" +
        "\n");
    return 1;
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

/*
This part doesn't work for some raisin.

public void
remove_object()
{
    ::remove_object();
    cleanup_spells();
}
*/

void
init()
{
    ::init();
    add_action(wandhelp, "wandhelp");
}