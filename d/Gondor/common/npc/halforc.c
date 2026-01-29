/* 
 *	/d/Gondor/justus/monster/halforc.c
 *
 *	Note that the word 'halforc' is not used in the descriptions.
 *	Players may figure that out for themselves, however.
 *	This file is derived from /d/Gondor/elessar/elessar/npc/whorc.c
 *	However these spies use Rohirrim army equipment!
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Gondor/common/lib/logkill.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_monster()
{
    set_name("man");
    set_pname("men");
    set_pshort("men");
    set_race_name("human"); 
    set_adj("squint-eyed");
    set_long(BS("This man has strange looks for a human. Most noticeably, "+
      "he is somewhat squint-eyed.\n"));

    default_config_npc(25 + random(6));
    set_base_stat(SS_DEX, 30 + random(11));
    set_base_stat(SS_CON, 30 + random(11));

    set_alignment(-200);
    set_aggressive(1);

    set_skill(SS_WEP_CLUB,  30 + random(16));
    set_skill(SS_WEP_SWORD, 30 + random(16));
    set_skill(SS_PARRY,     10 + random(11));
    set_skill(SS_DEFENCE,   10 + random(11));
    set_skill(SS_BLIND_COMBAT, 25);

    add_prop(LIVE_I_SEE_DARK,1);
    add_prop(CONT_I_HEIGHT,  1500);
    add_prop(CONT_I_WEIGHT, 45000);
    add_prop(CONT_I_VOLUME, 45000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_chat_time(10 + random(6));
    add_chat("Our plan seems to have worked!");
    add_chat("Tell the Rangers that everything is fine here.");
    add_chat("Nice to meet you!");
    set_cchat_time(3 + random(6));
    add_cchat("Ah! He is carrying some nice stuff...");
    add_cchat("You might as well commit suicide.");
    add_cchat("In a moment me be getting very glad, "+
	      "dancing around your corpse!");
    add_cchat("How comes that angry look onto your face?");

}

public void
arm_me()
{
    FIX_EUID;

    if (!random(3)) 
	clone_object(WEP_DIR + "orcclub")->move(TO);
    else 
	clone_object(WEP_DIR + "rosword")->move(TO);
    command("wield all");

    clone_object(ARM_DIR + "studlarm")->move(TO);

    if (random(2))
	clone_object(ARM_DIR + "roshield")->move(TO);
    if (random(2))
	clone_object(ARM_DIR + "rohelm")->move(TO);
    command("wear all");
}

/* For the solemnians */
public int query_knight_prestige() { return 250; }
