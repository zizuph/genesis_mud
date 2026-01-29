inherit "/std/creature";
inherit "std/combat/unarmed";
inherit "std/act/action";
inherit "std/act/domove";
#include <ss_types.h>
#include <filter_funs.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

int r;

create_creature() {
    set_name("wolf cub");
    add_name("cub");
    set_race_name("wolf");
    set_adj(({"fuzzy","grey"}));
    set_long(BSN("A fuzzy, grey wolf cub with sharp teeth and bright eyes."));
    set_pname("wolf cubs");
    set_pshort("cubs");
    r=random(3);
    set_stats(({8+r,7+r,6+r,7-r,8-r,7+2*r}));
    set_hp(1000);
    set_random_move(25);
    set_restrain_path(({LEB_DIR + "wolfcave/cave"}));
    set_monster_home(({LEB_DIR + "wolfcave/cave4"}));
    set_alignment(-50-random(51));
    set_skill(SS_DEFENCE,10+r);
    set_skill(SS_BLIND_COMBAT,10+random(5));
    set_skill(SS_AWARENESS,10+r);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_WEIGHT,15000);
    add_prop(CONT_I_HEIGHT,50);
    add_prop(CONT_I_VOLUME,10000);

    set_attack_unarmed(A_BITE,9+random(3),9+random(3),W_IMPALE,40,"teeth");
    set_attack_unarmed(A_LCLAW,6+random(5),6+random(5),W_SLASH,30,"left paw");
    set_attack_unarmed(A_RCLAW,6+random(5),6+random(5),W_SLASH,30,"right paw");

    set_hitloc_unarmed(H_HEAD,({10,10,10,0}),25,"head");
    set_hitloc_unarmed(H_BODY,({10,10,10,0}),50,"body");
    set_hitloc_unarmed(H_LEGS,({10,10,10,0}),25,"legs");
    set_act_time(10+random(12));
    add_act("growl");
    add_act("emote rolls about playfully on the floor.");
    add_act("sniff");
    set_cact_time(10+random(5));
    add_cact("snarl all");
    add_cact("emote bites your ankle.");
    add_cact("jump");
}
