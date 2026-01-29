
 /* 

    This is base file that provides a revised set of attack descriptions 
    based on damage types. It was coded as a possible way of improving 
    the cbase but is only used for special attacks in Calia. 

                     Created by Maniac 11/10/96

                  Copyright (C) Miguel Leith 1996. 

   Function "damage_element" revised to be in line with cbase measures 
   of damage, Maniac, 25/5/01 

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
       ({ "", /* for misses */ 
          " weakly", 
          " lightly", 
          "", 
          " accurately", 
          " powerfully",  
          " forcefully",
          " severely", 
          " devastatingly" }); 

/* slash damage verbs, weakest to strongest */ 
static mixed slash_dam_vb = 
       ({ ({ "miss", "misses", "missing" }), 
          ({ "tickle", "tickles", "tickling" }), 
          ({ "graze", "grazes", "grazing" }), 
          ({ "cut", "cuts", "cutting" }), 
          ({ "gash", "gashes", "gashing" }), 
          ({ "slash", "slashes", "slashing" }), 
          ({ "rip", "rips", "ripping" }), 
          ({ "hew", "hews", "hewing" }), 
          ({ "cleave", "cleaves", "cleaving" }) }); 

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
             ({ "force", "forces", "forcing", "at" }) }); 

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
          ({ "jab", "jabs", "jabbing", "at" }) }); 

static string conj; 


/* 
 * Function:     damage_element 
 * Description:  Given the percentage of damage of a hit, 
 *               returns the appropriate index for one of 
 *               the damage description arrays. 
 */ 
int
damage_element(int pdam)
{
    if (pdam < 0)
        return 0; 

    switch (pdam) { 
        case 0..2 : 
            return 1; 
            break; 
        case 3..5 : 
            return 2; 
            break; 
        case 6..9 : 
            return 3; 
            break; 
        case 10..19 : 
            return 4; 
            break; 
        case 20..29 : 
            return 5; 
            break; 
        case 30..49 : 
            return 6; 
            break; 
        case 50..79 : 
            return 7; 
            break; 
        default : 
            return 8; 
            break; 
    } 
}



/* 
   The remaining functions in this file provide attack descriptions 
   for a particular move in combat. You pass to any of these functions 
   the attacker, his enemy, the hit type (e.g. W_BLUDGEON), 
   the percentage of damage, the hit part (e.g. "head"), and the 
   weapon short (e.g, "sword of light"). The optional inner_clause 
   argument should contain three strings to be inserted after the 
   initial subject pronoun of the sentence in first, second and 
   third person respectively. The optional new_adverbs argument 
   can replace the default adverbs (should contain nine elements
   in order from weakest hit to strongest). The optional second_ing 
   argument being true indicates that the final clause should be 
   in "ing" form e.g. "accurately cutting his legs."

   The functions return an array of three strings, where the first 
   is the string that the attacker sees, the second is the string 
   that the enemy sees, the third is the string that onlookers see. 
   The appropriate functions to use are catch_msg, catch_msg and 
   tell_watcher respectively. 
 */ 

varargs string * 
attack_desc_template_one(object attacker, object enemy, 
                         int hit_type, int pdam, string hit_part, 
                         string weapon_desc, string *inner_clause, 
                         string *new_adverbs, int second_ing) 
{
    string dam_vb, move_vb, da; 
    int de; 

    if (!(de = damage_element(pdam))) 
        conj = " but "; 
    else 
    { 
        if (second_ing) 
            conj = ", "; 
        else 
            conj = " and "; 
    } 

    switch (hit_type) 
    { 
        case W_SLASH : 
             dam_vb = slash_dam_vb[de]; 
             move_vb = slash_move_vb[random(sizeof(slash_move_vb))]; 
             break; 
        case W_IMPALE : 
             dam_vb = impale_dam_vb[de]; 
             move_vb = impale_move_vb[random(sizeof(impale_move_vb))]; 
             break; 
        default : 
             dam_vb = bludg_dam_vb[de]; 
             move_vb = bludg_move_vb[random(sizeof(bludg_move_vb))]; 
             break; 
    } 

    if (pointerp(new_adverbs) && sizeof(new_adverbs)) 
        da = new_adverbs[de]; 
    else 
        da = dam_adv[de]; 

    return ({ 
             ("You" + (((sizeof(inner_clause) > 0) && 
                          stringp(inner_clause[0])) ? 
                         inner_clause[0] : " ") + 
              move_vb[ATT_FORM] + " your " + weapon_desc + 
              " " + move_vb[VB_PREP] + " " + 
              enemy->query_the_name(attacker) + conj + 
              (second_ing ? dam_vb[ING_FORM] : dam_vb[ATT_FORM]) + 
              " " + enemy->query_possessive() + 
              " " + hit_part + da + ".\n"), 

             (attacker->query_The_name(enemy) + 
              (((sizeof(inner_clause) > 1) && stringp(inner_clause[1])) ? 
                       inner_clause[1] : " ") + 
              move_vb[ONL_FORM] + 
              " " + attacker->query_possessive() + " " + weapon_desc + 
              " " + move_vb[VB_PREP] + " you" + conj + 
              (second_ing ? dam_vb[ING_FORM] : dam_vb[ONL_FORM]) + 
              " your " + hit_part + da + ".\n"), 

              (QCTNAME(attacker) + 
              (((sizeof(inner_clause) > 2) && stringp(inner_clause[2])) ? 
                        inner_clause[2] : " ") + 
               move_vb[ONL_FORM] + " " + 
               attacker->query_possessive() + " " + weapon_desc + 
               " " + move_vb[VB_PREP] + " " + QTNAME(enemy) + conj + 
               (second_ing ? dam_vb[ING_FORM] : dam_vb[ONL_FORM]) + 
               " " + enemy->query_possessive() + " " + 
               hit_part + da + ".\n") 
           }); 
}

