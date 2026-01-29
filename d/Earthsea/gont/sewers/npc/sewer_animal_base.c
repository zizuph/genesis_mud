/*
 * sewer_animal_base npc standard file
 * 
 *  MAR 2021, Aeg
 */
 
#pragma strict_types
#include "../defs.h"

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";

#include <filter_funs.h>        /* for FILTER_LIVE              */
#include <ss_types.h>           /* for SS_DEFENCE, etc          */
#include <stdproperties.h>      /* for NPC_I_NO_LOOKS, etc      */
#include <wa_types.h>           /* for W_IMPALE, etc            */
#include <macros.h>             /* General purpose */
#include <cmdparse.h>           /* actions */


/* Prototypes */
public void     create_animal();
public void     create_monster();

/*
 * Function name:       create_animal
 * Description  :       dummy routine for inheriting files
 */
public void
create_animal()
{
} /* create_animal */

/* 
 * Function name:       create_monster()
 * Description  :       sets up some standard things for all gont animals. 
 */
public void
create_monster()
{
    seteuid(getuid());
    set_race_name("animal");
    set_gender(G_NEUTER);
   
    /* skills */
    set_skill(SS_DEFENCE,       30+random(10));
    set_skill(SS_UNARM_COMBAT,  30+random(10));
    set_skill(SS_AWARENESS,     50+random(10));
    set_skill(SS_PARRY,         50+random(10));
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");

       
    /* Need to remove some leftovers */
    remove_leftover("nose"); 
    remove_leftover("tooth"); 
    remove_leftover("kneecap"); 
/*    remove_leftover("intestine"); */
    remove_leftover("nail"); 
/*    remove_leftover("skull"); */
    remove_leftover("thighbone");
/*    remove_leftover("eye"); */
/*    remove_leftover("heart"); */
    remove_leftover("scalp");
/*    remove_leftover("rib"); */
/*    remove_leftover("kidney"); */
    remove_leftover("ear");
/*    remove_leftover("meat"); */
    remove_leftover("toe");
    remove_leftover("finger");
    remove_leftover("jaw");
    
    create_animal();
             
} /* Create Monster */
    
