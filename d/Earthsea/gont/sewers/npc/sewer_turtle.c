/*
 * /d/Earthsea/gont/sewers/liv/sewer_turtle.c
 *
 * Animal npc that has herbs as leftovers.
 * 
 * July 2021, Aeg
 */
#pragma strict_types

#include "../defs.h"
#include <macros.h>         /* General purpose */
#include <stdproperties.h>  /* References */
#include <ss_types.h>       /* Skills */
#include <wa_types.h>       /* Attack+Hitloc */
#include <cmdparse.h>       /* actions */ 
 
inherit SEWER_NPC_DIR + "sewer_animal_base";
 
/* prototypes */
public void     create_animal();

/* 
 * Function name:       create_machine
 * Description  :       creates NPC with machine settings 
 */
public void
create_animal()
{
    
    seteuid(getuid());
    int x,y;
    string *phys, *ment;
    
    phys    = ({"filthy", "shiny", "aged",
                "large", "bulky", "ancient"});
    ment   = ({"intelligent", "wheezing", "dense",
                "slow-moving", "skittish", "curious"});
                
    x = random(sizeof(phys));
    y = random(sizeof(ment));
    set_short(phys[x] + " " + ment[y] + " turtle");
    set_adj(phys[x]);
    set_adj(ment[y]);
    
    
    set_name("turtle");
    set_adj( ({"dark-green", "sewer"}) );
    set_long("This is a common turtle that can be found foraging for "
           + "food in the sewers. It differs from its surface relatives "
           + "in that it is not accustomed to daylight and is happy to "
           + "live in the dark. It is not a hulking beast, nor is it a "
           + "defenseless one. If ignored, it should not be feared.\n");


    /* stats */
    set_base_stat(SS_STR, 140 + random(20));
    set_base_stat(SS_DEX, 100 + random(10));
    set_base_stat(SS_CON, 130 + random(10));
    set_base_stat(SS_INT, 90 + random(10));
    set_base_stat(SS_WIS, 100 + random(10));
    set_base_stat(SS_DIS, 100 + random(10));    
    set_hp(20000); /* Heal it */    
    
    /* skills */
    set_skill(SS_DEFENCE,       75);
    set_skill(SS_AWARENESS,     15);
    set_skill(SS_PARRY,         30);
    set_skill(SS_BLIND_COMBAT,  50);
    
    /* Combat attacks:  ID  HIT     PEN     DMG TYPE    %USE    DESCRIPTION */
    set_attack_unarmed( 0,   5,      5,     W_SLASH,    10,     "right claw");
    set_attack_unarmed( 1,   5,      5,     W_SLASH,    10,     "left claw");
    set_attack_unarmed( 2,  25,     25,     W_BLUDGEON, 30,     "shell");
    set_attack_unarmed( 3,  15,     30,     W_IMPALE,   50,     "beak");

    /* Hit Locations:   ID  AC(IMP  SLA  BLU ),     %HIT    DESCRIPTION  */
    set_hitloc_unarmed( 0,  ({ 10,  10,  10 }),     40,     "body");
    set_hitloc_unarmed( 1,  ({  1,   1,   1 }),     10,     "head");
    set_hitloc_unarmed( 2,  ({  1,   1,   1 }),     20,     "right forearm");
    set_hitloc_unarmed( 3,  ({  1,   1,   1 }),     20,     "left forearm");
    set_hitloc_unarmed( 4,  ({  1,   1,   1 }),     10,     "tail");
    
    add_prop(CONT_I_WEIGHT, 1000);
    
    /* Machine leftovers */
    add_leftover("/d/Earthsea/herbs/herb_files/slime_mold", "mold",
                 random(2), 0, 1, 0, 0);
    add_leftover("/d/Krynn/common/herbs/greenslime", "alga", random(2), 0, 1, 0, 0);
    add_leftover(SEWER_ARM_DIR + "turtle_shell", "shell", 1, 0, 1, 0, 0);
        
    /* Actions */
    set_act_time(5); /* action every 5 'beats' */
    add_act("emote extends its head and looks in your direction.");
    add_act("emote retracts its head into its shell, but pokes "
            + "back out a moment later.");
    add_act("emote forages for some food.");
    add_act("emote splashes loudly in the water.");
    add_act("emote freezes in place and focuses its attention upstream.");
    
    
    /* Combat Actions */
    set_cact_time(2); /* combat action every 2 'beats' */
    add_cact("emote hisses at you!");
          
       
} /* create animal */

          