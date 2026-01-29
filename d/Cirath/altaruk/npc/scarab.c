/*
 * scarab : Athasian sand scarab. Tiny little bug(ger).
 *
 * Azazel 2002
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

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1


string *randadj1;


void
create_creature()
{
    randadj1 = ({ "onyx", "emerald", "gold" });

    if (!random(5))
    add_leftover("/std/leftover", "shell", 1, 0, 1, 1);
    if (!random(5))
    add_leftover("/std/leftover", "leg", random(5) + 1, 0, 0, 0);

    set_name("scarab");
    set_race_name("scarab");
    set_adj(randadj1[random(sizeof(randadj1))]);
    add_adj("sand");
    set_long("This is a sand scarab. Its tiny, but" +
        " too big for you to just step on to kill." +
        " Some say thay are good luck.");
   
    add_prop(LIVE_I_NEVERKNOWN,1);
   
    set_stats(({ 5, 15, 10, 3, 3, 20 }));
    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_DEFENCE, 10);
    
    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 100, "incisors");

    set_hitloc_unarmed(H_HEAD, ({ 1, 5, 1,}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 1, 5, 1,}), 80, "body");
 
    set_act_time(12);
    add_act("jump");
    add_act("emote makes a clicking sound.");
    add_act("emote quickly burrows into the sand.");
    add_act("emote gives off a lot of clicking sounds.");
    set_cact_time(6);
    add_cact("emote tries to crawl under your skin.");
    add_cact("emote tries to get into your clothes.");
}
