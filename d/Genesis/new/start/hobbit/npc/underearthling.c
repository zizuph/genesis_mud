/*
 * File         : /d/Genesis/start/hobbit/npc/underearthling.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1999, Joakim Larsson
 * Date         : 3/25/1999
 * Related Files: 
 * Purpose      : 
 *     The undereartlings are a small creature humanoid race that has
 *    been raised and totally controlled by Dorm, the evil wizard.
 *    Undereartlings are about 70 cm in length and has a hairy
 *    tail-less but rat-like body and pointy teeth. They usually live
 *    in big hords below ground. Dorm control their minds and used them
 *    for massive attacks during the great wars and they were once
 *    allied with the older hobits on the village when these where paid
 *    warriors. Now when the hobbits has turned away from Dorm these
 *    underearthlings keeps him updated on how the village develops.
 * Todo         : 
 * 
 */

/* directives */
#pragma strict_types
/* inherits */
inherit "/std/monster";
inherit "/std/act/action";

/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <ss_types.h> 
#include "../hobbit.h"
/* defines */

/* prototypes */
void npc_actions();
void npc_default_answer();
void equip_me();

/* globals */
int     Status;

/*
 * Function name:       create_monster
 * Description  :       set up the npc
 */
void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("sluggo");
    set_adj(({ "hairy", "peering"}));
    set_race_name("underearthling");
    set_gender(G_MALE);
    set_long(
        "This is a sneaking creature sent out by Dorm, the mighty evil " +
        "wizard, to keep an eye on the hobbit village.\n");
    add_prop(CONT_I_HEIGHT, 70);
    add_prop(CONT_I_WEIGHT, 20000);
    add_prop(NPC_I_NO_LOOKS, 1);
    
    set_default_answer(npc_default_answer);
    
    set_stats(({8, 10, 7, 8, 7, 8}));
    set_alignment(-50);
    set_hp(query_max_hp());
    add_act("@@npc_actions@@");
    set_act_time(6);
    equip_me();
    
    add_name("creature");
    
}
/*
 * Function name: npc_actions()
 * Description  :  Handles NPC actions
 */
string
npc_actions()
{
    return "";
}

/*
 * Function name: npc_default_answer()
 * Description  : Handles the default answer for unknown questions.
 */
string
npc_default_answer()
{
    command("say I am not afraid and will tell you nothing.");
    return "";
}
 
/*
 * Function name: equip_me()
 * Description  : create cloths and equipments and wear it.
 */
void
equip_me()
{
    object clone;
    
    seteuid(getuid(TO));
    
    // Make some basic clothes
    clone = clone_object(EX_OBJ + "linnen_pants");
    clone->set_long("A pair of black linnen pants.\n");
    clone->move(TO);
    clone = clone_object(EX_OBJ + "linnen_shirt");
    clone->set_long("A black linnen shirt.\n");
    clone->move(TO);
    
    // Make some armour featured clothes
    clone = clone_object(EX_ARM + "leather_vest");
    clone->set_long("A black leather vest.\n");
    clone->move(TO);
    clone = clone_object(EX_ARM + "leather_boots");
    clone->set_long("A pair of well used leather boots.\n");
    clone->move(TO);
    
    // Put it on!
    command("wear all");
}

/* EOF */
