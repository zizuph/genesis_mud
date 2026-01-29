/*
 * Erdlu : Athasian beast. This one is wild.
 */
#pragma strict_types

#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_BOTH 3

#define H_HEAD 0
#define H_NECK 1
#define H_BODY 2
#define H_R_LEG 3
#define H_L_LEG 4

string *randadj1, *randadj2;

void
create_creature()
{
	
    randadj1 = ({ "red-scaled", "red-scaled", "gray-scaled" });
    randadj2 = ({ "hungry", "wild", "visious", "crazed" });

    if (!random(5))
        add_leftover("/d/Cirath/altaruk/npc/leftover/beak", "beak", random(2), 0, 1, 1);
    if (!random(5))
        add_leftover("/d/Cirath/altaruk/npc/leftover/claw", "claw", random(2), 0, 1, 1);
    if (!random(5))
        add_leftover("/std/leftover", "skull", 1, 0, 1, 1);
    if (!random(5))
        add_leftover("/std/leftover", "scale", random(5) + 1, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "heart", 1, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "eye", 2, 0, 0, 0);
    if (!random(5))
        add_leftover("/std/leftover", "kidney", 2, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "intestine", 2, 0, 0, 1);
        
    set_name("erdlu");
    set_race_name("erdlu");
    set_adj(randadj1[random(sizeof(randadj1))]);
    add_adj(randadj2[random(sizeof(randadj2))]);
    set_long("This is an Erdlu. A flightless, featherless birds" +
        " covered with flaky gray-to-red scales.They have" +
        " powerful, lanky legs ending in four-toed feet with" +
        " razor-sharp claws, and can run at great speeds over" +
        " short distances. ");
    
    add_prop(LIVE_I_NEVERKNOWN,1);
    
    set_aggressive(1);
    set_stats(({ 140, 100, 140, 30, 30, 120 }));

    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 70);
    
    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 20, "beak");
    set_attack_unarmed(A_LCLAW, 30, 20, W_SLASH,  35, "left foot");
    set_attack_unarmed(A_RCLAW, 30, 20, W_SLASH,  35, "right foot");
    set_attack_unarmed(A_BOTH, 40, 30, W_BLUDGEON,  10, "feet");

    set_hitloc_unarmed(H_HEAD, ({ 15, 20, 5,}), 10, "head");
    set_hitloc_unarmed(H_NECK, ({ 10, 15, 15,}), 10, "neck");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 15,}), 60, "body");
    set_hitloc_unarmed(H_R_LEG, ({ 15, 15, 10,}), 15, "right leg");
    set_hitloc_unarmed(H_L_LEG, ({ 15, 15, 10,}), 15, "left leg");

   set_act_time(12);
   add_act("yawn.");
   add_act("emote tosses its head around and snorts.");
   add_act("emote snorts");
   add_act("emote rises a clawed foot and stomps it into the sand.");
   add_act("emote tilts its head and gives off a clicking sound.");
   set_cact_time(6);
   add_cact("scream");
   add_cact("scream");
   add_cact("emote shrieks!");
   add_cact("emote throws its head about and screams out loud!");
}
