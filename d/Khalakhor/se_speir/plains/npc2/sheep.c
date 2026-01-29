//
// sheep - a sheep in the pasture on the plain
//
// Zima   May 18, 1998
//
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
 
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
 
#define A_FHOOVES 0
#define A_RHOOVES 1
#define A_TEETH   2
 
#define H_HEAD 0
#define H_BODY 1
 
string color="black";
string query_color() { return color; }

void create_creature() {
    set_name("sheep");
    if (random(5)) color="white";
    set_short(color+" sheep");
    set_pshort(color+" sheep");
    set_race_name("sheep");
    set_adj(({"small",color}));
    set_long(
        "A common sheep, covered in "+color+" wool with a black face " +
        "and hooves. He is munching on the grass of the plains and "+
        "baaaa-ing innocently.\n");
 
    set_stats(({ 10, 10, 10, 10, 10, 10}));
    set_skill(SS_DEFENCE, 10);
 
    set_attack_unarmed(A_FHOOVES, 10, 10, W_BLUDGEON, 10, "front hooves");
    set_attack_unarmed(A_RHOOVES, 10, 10, W_BLUDGEON, 10, "rear hooves");
    set_attack_unarmed(A_TEETH,   10, 10, W_SLASH,    10, "teeth");
 
    set_hitloc_unarmed(H_HEAD, ({10, 10, 10, 10 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({10, 10, 10, 10 }), 80, "body");
 
    set_random_move(30);
    set_act_time(10);
    add_act("emote chews on a wad of grass.");
    add_act("emote baaaa's noisily.");
    add_act("emote baaaa's noisily.");
    add_act("emote rolls his eyes.");
    add_act("emote nudges you with his nose.");
    add_act("emote paws the ground with his front hooves.");
    add_act("emote jumps nervously and baaaa's.");
 
}
