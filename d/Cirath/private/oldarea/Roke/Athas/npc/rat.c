inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";	/* random move and follow */

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <const.h>
#include "/d/Roke/common/defs.h"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD 0
#define H_BODY 1

create_creature() {

    if (!IS_CLONE)
	return;
    set_name("rat");
    set_race_name("rat"); 
    set_adj("gray");
    add_adj("hairy");

	set_long(BSS("This rat seems HUGE, but that could be an "+
		"illusion since you crawl.\n"));

    set_gender(G_NEUTER);
    set_random_move(40);
	set_stats(({ 7, 12, 8, 2, 3, 16}));
    set_hp(100);


    add_prop(CONT_I_WEIGHT, 4000);
    add_prop(CONT_I_VOLUME, 3700);

    add_prop(OBJ_I_NO_INS, 1);

    set_attack_unarmed(A_BITE,   8, 10, W_IMPALE, 80, "jaws");
    set_attack_unarmed(A_LCLAW, 15,  6, W_SLASH,  10, "left paw");
    set_attack_unarmed(A_RCLAW, 15,  6, W_SLASH,  10, "right paw");

    set_hitloc_unarmed(H_HEAD, ({ 10, 14,  6,   5 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  5,  8, 16,   0 }), 80, "body");

}
