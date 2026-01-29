/*
 *  thornlin/npc/wolf-dog.c
 *  by Boromir, June 1995
 *
 *  Modified from /d/Gondor/common/npc/wolf.c
 *   by Olorin              Feb 1993
 *
 */
#include "/d/Gondor/defs.h"
inherit NPC_DIR + "wolf";

#include <ss_types.h>

#define JUMP_RATE	25
#define JUMP_PEN	50

void
create_wolf()
{
    set_name("wolf dog");
    set_race_name("wolf dog");
    set_living_name("draughuan");
    add_name(({"dog", "wolf"}));
    add_adj(({"huge", "ugly", }));
    set_long(BSN("This is a huge and ugly dog, or rather something "+
	"between a dog and a wolf. Its skin looks more wolf-like "+
	"than dog-like but it acts like a dog. It looks like it is a "+
	"tough fighter and you would probably not want to mess with "+ 
	"it or its master."));
    set_stats(({50+random(30), 40+random(20), 30+random(20), 20, 20, 75}));
    set_alignment(-200+random(50));

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_SWIM, 80);

    set_jump_rate(JUMP_RATE);
    set_jump_pen(JUMP_PEN);
}

