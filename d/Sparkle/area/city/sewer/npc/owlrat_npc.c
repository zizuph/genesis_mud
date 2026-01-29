/*
 * /d/Sparkle/area/city/sewer/npc/owlrat_npc.c
 * owlrat_npc standard file
 * Aeg: 11 FEB 2009
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
#include <macros.h>             /* General purpose              */
#include <cmdparse.h>           /* Actions                      */
#include <money.h>              /* Money                        */


/* Prototypes */
public void     create_owlrat();
public void     create_monster();

/*
 * Function name:       create_owlrat
 * Description  :       dummy routine for inheriting files
 */
public void
create_owlrat()
{
} /* create_owlrat */

/* 
 * Function name:       create_monster()
 * Description  :       sets up some standard things for all owlrats. 
 */
public void
create_monster()
{
    set_race_name("owlrat");
    
    seteuid(getuid());
    int x,y;
    string *eyes, *feathers;
    
    eyes     = ({"wise-eyed", "sharp-eyed", "dark-eyed", "bright-eyed",
                 "brown-eyed", "white-eyed", "yellow-eyed", "green-eyed",
                 "grey-eyed", "distant-eyed", "shifty-eyed", "wide-eyed",
                 "deep-eyed", "cloudy-eyed"});
    feathers = ({"thick-feathered", "thin-feathered", "brown-feathered", 
                 "grey-feathered", "white-feathered", "black-feathered",
                 "tan-feathered"});
                
    x = random(sizeof(eyes));
    y = random(sizeof(feathers));
    set_short(eyes[x] + " " + feathers[y] + " owlrat");
    set_adj(eyes[x]);
    set_adj(feathers[y]);
   
    /* skills */
    set_skill(SS_DEFENCE,       40+random(10));
    set_skill(SS_UNARM_COMBAT,  40+random(10));
    set_skill(SS_AWARENESS,     50+random(12));
      
    set_gender(G_NEUTER);      
    set_alignment(0);
       
    add_prop(LIVE_I_IS, 1);   
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);     /* Fleeing npcs piss people off  */
    add_prop(LIVE_I_SEE_DARK, 3);       /* Owlrats can see               */

    /* Chatter */
    set_chat_time(25); /* chatter */
    add_chat("Hoo!");
    add_chat("Hoot-Whoooo");
    
    /* Actions */
    set_act_time(35); /* action */
    add_act("emote looks directly at you and says, 'Hoo?'");
    add_act("emote ruffles it's feathers.");
    add_act("emote rotates it's head in a full circle!");
    add_act("emote scurries around.");
    add_act("emote stares blankly as drool seeps from it's beak.");
    add_act("emote hoots softly.");
    
        /* Combat Actions */
    set_cact_time(20); /* combat action */
    add_cact("shout HOO! HOOOOOOOOOO!");
    add_cact("emote pecks at your face!");
    
    create_owlrat();
    
    /* Leftovers add and remove */
    remove_leftover("nose");
    remove_leftover("kneecap");
    remove_leftover("scalp");
    remove_leftover("ear");
    remove_leftover("toe");
    remove_leftover("finger");
    remove_leftover("jaw");
    add_leftover(SEWER_OBJ_DIR + "owlrat_beak", "beak",    random(1), 0, 1, 0, 0);
             
             
    /* Combat attacks:  ID  HIT     PEN     DMG TYPE    %USE    DESCRIPTION */
    set_attack_unarmed( 0,  10,     10,     W_SLASH,     5,     "right wing");
    set_attack_unarmed( 1,  10,     10,     W_SLASH,     5,     "left wing");
    set_attack_unarmed( 2,  15,     15,     W_IMPALE,    40,    "beak");
    set_attack_unarmed( 3,  15,     15,     W_BLUDGEON,  50,    "tail");

    /* Hit Locations:   ID  AC(IMP  SLA  BLU ),     %HIT    DESCRIPTION  */
    set_hitloc_unarmed( 0,  ({  8,  10,  10 }),     45,     "breast");
    set_hitloc_unarmed( 1,  ({  8,  10,  10 }),     15,     "right wing");
    set_hitloc_unarmed( 2,  ({  8,  10,  10 }),     15,     "left wing");
    set_hitloc_unarmed( 3,  ({  8,  10,  10 }),     20,     "head");
    
} /* Create Monster */