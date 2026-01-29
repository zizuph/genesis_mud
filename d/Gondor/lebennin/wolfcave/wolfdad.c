/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/std/creature";
inherit "std/combat/unarmed";
inherit "std/act/attack";
inherit "std/act/action";

#include <ss_types.h>
#include <filter_funs.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/common/lib/logkill.c"
#include "/d/Gondor/defs.h"

#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

int r;

create_creature() {
    set_name("wolf");
    add_name("_wolf_dad");
    set_race_name("wolf");
    set_adj(({"lanky","grey"}));
    set_long(BSN("A lanky, grey adult wolf with sharp teeth and scarred flanks."));
    set_pname("wolves");
    set_pshort("wolves");
    r=random(6);
    set_stats(({19+2*r,19+r,21+r,16-r,18-r,35+3*r}));
    set_hp(1000);
    set_alignment(-150-random(100));
    set_aggressive(1);
    set_skill(SS_DEFENCE,21+r);
    set_skill(SS_BLIND_COMBAT,14+random(5));
    set_skill(SS_AWARENESS,30+r);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_SEE_DARK,2);
    add_prop(CONT_I_WEIGHT,45000);
    add_prop(CONT_I_HEIGHT,75);
    add_prop(CONT_I_VOLUME,30567);

    set_attack_unarmed(A_BITE,15+random(6),15+random(6),W_IMPALE,40,"teeth");
    set_attack_unarmed(A_LCLAW,11+random(5),11+random(5),W_SLASH,30,"left paw");
    set_attack_unarmed(A_RCLAW,11+random(5),11+random(5),W_SLASH,30,"right paw");

    set_hitloc_unarmed(H_HEAD,({19,18,20,0}),25,"head");
    set_hitloc_unarmed(H_BODY,({20,21,17,0}),50,"body");
    set_hitloc_unarmed(H_LEGS,({24,18,20,0}),25,"legs");
    set_act_time(10+random(12));
    add_act("growl");
    add_act("sniff");
    add_act("emote howls eerily.");
    set_cact_time(10+random(5));
    add_cact("snarl all");
    add_cact("jump");
    add_cact("emote whines pitifully.");
    add_cact("groan");    
}
