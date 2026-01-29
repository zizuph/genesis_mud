/*
 * This is very bad coding style!
 * Use the standard rat and configure it!
 */
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
#include "/d/Gondor/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include "/d/Gondor/common/lib/logkill.c"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

void
create_creature() 
{
    if(!IS_CLONE)
        return;
    set_name("rat");
    set_race_name("rat");
    set_adj("large");
    set_adj("black");
    set_long(BSN("This rat is big! Nothing like the little ones found out near"+
            " the harlond. This rat looks like it could eat a whole hobbit "+ 
            "and then come back for a dwarf!"));
    set_gender(2);
    set_stats(({ 40, 40, 40, 10, 10, 40}));
    REFRESH;
    set_skill(SS_SWIM, 95);
    set_skill(SS_DEFENCE,80);
    set_skill(SS_AWARENESS,80);
    set_alignment(-50-random(100));
     
    add_prop(LIVE_I_SEE_DARK,4);

    set_attack_unarmed(A_BITE, 40, 40, W_IMPALE, 80, "jaws");
    set_attack_unarmed(A_LCLAW, 30, 30, W_SLASH, 10, "left claw");
    set_attack_unarmed(A_RCLAW, 30, 30, W_SLASH, 10, "right claw");

    set_hitloc_unarmed(H_HEAD, ({40, 40, 40, 0}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({35, 35, 35, 0}), 80, "body");

}

query_knight_prestige() {return 36;}

