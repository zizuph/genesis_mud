
 /* 

    This is base file that provides a revised set of attack descriptions
    based on damage types. It's a possible way of improving the cbase. 

                     Created by Maniac 11/10/96

                  Copyright (C) Miguel Leith 1996. 

 */ 

#pragma save_binary
#pragma strict_types

#include <language.h> 
#include <wa_types.h> 
#include <macros.h> 

#define ATT_FORM 0
#define ONL_FORM 1 
#define ING_FORM 2
#define VB_PREP 3

/* 
   damage adverbs, from weakest to strongest. These are the common
   elements of attack descriptions for all damage types. A common 
   dsecriptive element allows players a means of differentiating the 
   damage levels consistently
 */ 
static mixed dam_adv = 
       ({ "completely", /* for misses */ 
          "weakly", 
          "lightly", 
          "slightly", 
          "accurately", 
          "powerfully",  
          "forcefully",
          "severely", 
          "devastatingly" }); 

/* slash damage verbs, weakest to strongest */ 
static mixed slash_dam_vb = 
       ({ ({ "miss", "misses", "missing" }), 
          ({ "tickle", "tickles", "tickling" }), 
          ({ "graze", "grazes", "grazing" }),  
          ({ "cut", "cuts", "cutting" }), 
          ({ "gash", "gashes", "gashing" }), 
          ({ "slash", "slashes", "slashing" }),
          ({ "rip", "rips", "ripping" }),
          ({ "carve", "carves", "carving" }),  
          ({ "cleave", "cleave", "cleaves" }) }); 

/* slash move verbs and their prepositions if they are phrasal verbs */ 
static mixed slash_move_vb = 
       ({ ({ "sweep", "sweeps", "sweeping", "across" }), 
          ({ "arc", "arcs", "arcing", "towards" }),  
          ({ "curve", "curves", "curving", "towards" }), 
          ({ "draw", "draws", "drawing", "across" }),  
          ({ "glide", "glides", "gliding", "across" }),  
          ({ "swing", "swings", "swinging", "at" }) }); 

/* impale damage verbs, weakest to strongest */ 
static mixed impale_dam_vb =
          ({ ({ "miss", "misses", "missing" }), 
             ({ "poke", "pokes", "poking" }), 
             ({ "spike", "spikes", "spiking" }), 
             ({ "stab", "stabs", "stabbing" }), 
             ({ "puncture", "punctures", "puncturing" }),  
             ({ "pierce", "pierces", "piercing" }),  
             ({ "impale", "impales", "impaling" }), 
             ({ "gore", "gores", "goring" }),
             ({ "skewer", "skewers", "skewering" }) }); 

/* impale move verbs and their prepositions */ 
static mixed impale_move_vb = 
          ({ ({ "drive", "drives", "driving", "at" }),   
             ({ "lunge", "lunges", "lunging", "at" }), 
             ({ "thrust", "thrusts", "thrusting", "at" }), 
             ({ "ram", "rams", "ramming", "at" }),  
             ({ "push", "pushes", "pushing", "at" }),
             ({ "propel", "propels", "propelling", "towards" }) }); 

/* bludgeon damage verbs, weakest to strongest */ 
static mixed bludg_dam_vb = 
          ({ ({ "miss", "misses", "missing" }), 
             ({ "tap", "taps", "tapping" }), 
             ({ "cuff", "cuffs", "cuffing" }),   
             ({ "thump", "thumps", "thumping" }), 
             ({ "strike", "strikes", "striking" }),  
             ({ "batter", "batters", "battering" }), 
             ({ "hammer", "hammers", "hammering" }),  
             ({ "smash", "smashes", "smashing" }),   
             ({ "crush", "crushes", "crushing" }) }); 

/* bludgeon move verbs and their prepositions  */ 
static mixed bludg_move_vb = 
       ({ ({ "swing", "swings", "swinging", "at" }), 
          ({ "arc", "arcs", "arcing", "towards" }), 
          ({ "swerve", "swerves", "swerving", "towards" }), 
          ({ "hook", "hooks", "hooking", "across" }),
          ({ "launch", "launches", "launching", "at" }),  
          ({ "aim", "aims", "aiming", "at" }) }); 



int
damage_element(int pdam)
{
    if (pdam < 0)  
       return 0; 
    else if (pdam == 0)
       return 1;
    else if (pdam < 4) 
       return 2;
    else if (pdam < 8) 
       return 3; 
    else if (pdam < 12) 
       return 4; 
    else if (pdam < 16) 
       return 5; 
    else if (pdam < 25) 
       return 6; 
    else if (pdam < 50) 
       return 7; 
    else 
       return 8; 
}



/* 
   The remaining functions in this file provide attack descriptions 
   for a particular move in combat. You pass to any of these functions 
   the attacker, his enemy, the hit type (e.g. W_BLUDGEON),  
   the percentage of damage, the hit part (e.g. "head"), and the 
   weapon short (e.g, "sword of light"). 

   The functions return an array of three strings, where the first is 
   the string that the attacker sees, the second is the string that  
   the enemy sees, the third is the string that onlookers see. 
   The appropriate functions to use are catch_msg, catch_msg and 
   tell_watcher respectively. 
 */ 

string * 
attack_desc_template_one(object attacker, object enemy, 
                         int hit_type, int pdam, string hit_part, 
                         string weapon_desc) 
{
    mixed dam_vb, move_vb; 
    string da; 
    int ds, ms, de, me; 

    switch (hit_type) { 
        case W_SLASH : 
                  dam_vb = slash_dam_vb; 
                  move_vb = slash_move_vb; 
                  break;
        case W_IMPALE : 
                  dam_vb = impale_dam_vb; 
                  move_vb = impale_move_vb; 
                  break;
        default : 
                  dam_vb = bludg_dam_vb;  
                  move_vb = bludg_move_vb; 
                  break;
    } 

    ds = sizeof(dam_vb); 
    ms = sizeof(move_vb); 

    me = random(ms); 
    move_vb = move_vb[me]; 

    de = damage_element(pdam); 
    dam_vb = dam_vb[de]; 

    da = dam_adv[de]; 

    return ({ 
             ("You " + move_vb[ATT_FORM] + " your " + weapon_desc +  
              " " + move_vb[VB_PREP] + " " + 
              enemy->query_the_name(attacker) + " and " +  
              dam_vb[ATT_FORM] + " " + enemy->query_possessive() + 
              " " + hit_part + " " + da + ".\n"),  

             (attacker->query_The_name(enemy) + " " +  move_vb[ONL_FORM] + 
              " " + attacker->query_possessive() + " " + weapon_desc + 
              " " + move_vb[VB_PREP] + " you and " + dam_vb[ONL_FORM] + 
              " your " + hit_part + " " + da + ".\n"), 

              (QCTNAME(attacker) + " " + move_vb[ONL_FORM] + " " + 
               attacker->query_possessive() + " " + weapon_desc + 
               " " + move_vb[VB_PREP] + " " + QTNAME(enemy) + " and " + 
               dam_vb[ONL_FORM] + " " + enemy->query_possessive() + " " + 
               hit_part + " " + da + ".\n") 
           });  
}


