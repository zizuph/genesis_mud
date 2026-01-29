inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
 
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "defs.h"
 
#define A_FHOOVES 0
#define A_RHOOVES 1
#define A_TEETH   2
 
#define H_HEAD 0
#define H_BODY 1
 
void
create_creature()
{
    set_name(({"the sheep","sheep"}));
    set_short("sheep");
    set_pshort("sheep");
    set_race_name("sheep");
    set_adj(({"small","white"}));
    set_long(BS(
        "A common sheep, covered in white wool with a black face " +
        "and hooves, he is the image of innocence and defenselessness.\n"));
 
    set_stats(({ 10, 10, 10, 10, 10, 10}));
 
    /* ask for help from team members, but don't help if they are attacked */
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
    add_prop(ATTACK_PASSIVE,1);   /* won't attack friend's attacker */
    set_hp(3000);
 
    set_skill(SS_DEFENCE, 10);
 
    set_attack_unarmed(A_FHOOVES, 10, 10, W_BLUDGEON, 10, "front hooves");
    set_attack_unarmed(A_RHOOVES, 10, 10, W_BLUDGEON, 10, "rear hooves");
    set_attack_unarmed(A_TEETH,   10, 10, W_SLASH,    10, "teeth");
 
    set_hitloc_unarmed(H_HEAD, ({10, 10, 10, 10 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({10, 10, 10, 10 }), 80, "body");
 
    set_act_time(10);
    set_alignment(300);
    add_act("emote chews on a wad of grass.");
    add_act("emote baaaa's noisily.");
    add_act("emote baaaa's noisily.");
    add_act("emote rolls his eyes.");
    add_act("emote nudges you with his nose.");
    add_act("north");
    add_act("south");
    add_act("east");
    add_act("west");
 
}
 
