/*
 * /d/Sparkle/area/city/sewer/npc/gremlin_npc.c
 * gremlin_npc standard file
 * Aeg: 06 FEB 2009
 */
 
#pragma strict_types
#include "defs.h"

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/domove";

#include <filter_funs.h>        /* for FILTER_LIVE              */
#include <ss_types.h>           /* for SS_DEFENCE, etc          */
#include <stdproperties.h>      /* for NPC_I_NO_LOOKS, etc      */
#include <wa_types.h>           /* for W_IMPALE, etc            */
#include <macros.h>             /* General purpose              */
#include <cmdparse.h>           /* Actions                      */
#include <money.h>              /* Money                        */


/* Prototypes */
public void     create_gremlin();
public void     create_monster();

/*
 * Function name:       create_gremlin
 * Description  :       dummy routine for inheriting files
 */
public void
create_gremlin()
{
} /* create_gremlin */

/* 
 * Function name:       create_monster()
 * Description  :       sets up some standard things for all gremlins. 
 */
public void
create_monster()
{
    set_race_name("gremlin");
    
    seteuid(getuid());
    int x,y;
    string *phys, *ment;
    
    phys    = ({"green-skinned", "bright-eyed", "white-haired", "slimy",  
                "dark-skinned", "slimy-skinned", "olive-skinned", 
                "scaly-skinned", "deep-eyed", "sharp-toothed", 
                "yellow-haired", "grey-haired", "black-haired", 
                "brown-skinned", "big-eared", "pointy-eared", "floppy-eared",
                "small", "average-sized", "muscular", "lanky", "lean",
                "red-eyed", "yellow-eyed", "scarred"});
    ment    = ({"smelly", "malodorous", "foul", "foul-smelling", "rank", 
                "stinking", "putrid", "strong", "mephitic", "noisome",
                "baneful", "feral", "wild", "savage", "intelligent", 
                "clever", "bright", "tricky", "sneaky", "furtive",
                "mischevious", "bothersome", "vexatious", "troublesome",
                "annoying", "disturbing", "tiresome", "irksome"});
                
    x = random(sizeof(phys));
    y = random(sizeof(ment));
    set_short(phys[x] + " " + ment[y] + " gremlin");
    set_adj(phys[x]);
    set_adj(ment[y]);
   
    /* skills */
    set_skill(SS_DEFENCE,       50+random(10));
    set_skill(SS_UNARM_COMBAT,  30+random(10));
    set_skill(SS_WEP_KNIFE,     60+random(20));
    set_skill(SS_WEP_AXE,       20+random(20));
    set_skill(SS_WEP_POLEARM,   20+random(20));
    set_skill(SS_WEP_SWORD,     40+random(10));
    set_skill(SS_WEP_CLUB,      50+random(10));
    set_skill(SS_AWARENESS,     50+random(12));
    set_skill(SS_PARRY,         50+random(10));
    
    set_alignment(0);
       
    add_prop(LIVE_I_IS, 1);   
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);     /* Fleeing nps piss people off   */
    add_prop(LIVE_I_SEE_DARK, 3);       /* Gremlins are darklings        */
    add_prop(MAGIC_I_BREATH_WATER, 1);  /* Gremlins spawn in the water   */
    add_prop(MAGIC_I_RES_ACID, 1);      /* Gremlins are immune to acid   */
    add_prop(MAGIC_I_RES_POISON, 1);    /* Gremlins are immune to poison */
    add_prop(NPC_I_NO_UNARMED, 1);      /* We don't want fistfighters    */
    
    
    create_gremlin();
             
} /* Create Monster */