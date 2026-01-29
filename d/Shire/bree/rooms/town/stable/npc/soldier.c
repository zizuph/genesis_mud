/*
 *	/d/Gondor/morgul/npc/ithil_soldier.c
 *
 *	Olorin, July 1993
 *	General revision: Olorin, February 1996
 */
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_monster.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/waraxe", MORGUL_DIR + "obj/battleaxe", \
                     MORGUL_DIR + "obj/orcmace", MORGUL_DIR + "obj/stabsword"})
#define WEP_ARRAY2 ({MORGUL_DIR + "obj/maingauche", MORGUL_DIR + "obj/shield"})
#define ARM_ARRAY1 ({MORGUL_DIR + "obj/ithil_cloak"})
#define ARM_ARRAY3 ({MORGUL_DIR + "obj/blackcap"})

public void
create_ithil_soldier()
{
}

nomask void
create_ithil_monster()
{
    int rnd = random(26);
    set_name("orc");
    add_name("soldier");
    set_pname("orcs");
    set_short("orc soldier");
    set_pshort("orc soldiers");
    set_race_name("orc");
    set_adj(alignlook());
    set_adj("black-skinned");
    set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," ")))
      + " orc soldier with short crooked legs and long arms that hang "
      + "almost to the ground. He belongs to one of the smaller orc "
      + "races, but he is very broad and looks to be rather strong."));

    default_config_npc(55 + rnd / 2);
    set_base_stat(SS_INT, 25 + rnd / 2);
    set_base_stat(SS_WIS, 25 + rnd / 2);
    set_base_stat(SS_DIS, 75 + rnd / 5);

    set_alignment(-300-rnd*12);
    set_skill(SS_WEP_SWORD,   55 + rnd);
    set_skill(SS_WEP_POLEARM, 55 + rnd);
    set_skill(SS_WEP_CLUB,    55 + rnd);
    set_skill(SS_WEP_KNIFE,   55 + rnd);
    set_skill(SS_WEP_AXE,     55 + rnd);
    set_skill(SS_PARRY,       55 + rnd);
    set_skill(SS_DEFENCE,     55 + rnd);
    set_skill(SS_2H_COMBAT,   55 + rnd);
    add_prop(CONT_I_HEIGHT,   145 + rnd);
    add_prop(CONT_I_WEIGHT, 80000 + rnd*800);
    add_prop(CONT_I_VOLUME, 75000 + rnd*800);
    add_prop(LIVE_I_SEE_DARK, 4);

    set_chat_time(10);
    add_chat("Don't even think about it!");
    add_chat("You won't get the horse!");
    add_chat("I'm so hungry I could eat this horse.");

    set_cchat_time(5 + random(10));
    add_cchat("Hurry, we must deliver this horse!");
    add_cchat("I'll eat this horse before I let you have it!");
    add_cchat("We got the horse, its ours!");

    set_act_time(15 + random(15));
    add_act("shout Don't let them get the horse!");
    add_act("get all from corpse");
    add_act("swear");
    add_act("kick horse");
    add_act("emote punches the horse in the face.");
    add_act("emote pulls roughly on the reigns.");

    set_cact_time(2);
    add_cact("@@emote_enemy|kick");
    add_cact("@@emote_enemy|spit");
    add_cact("kick horse.");
    add_cact("@@say_enemy|We will feast on your rotting corpse, stinking |");
    add_cact("@@say_enemy|This | won't get away with our prize!");
    create_ithil_soldier();
}

static void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Wep2 = WEP_ARRAY2;
    Arm1 = ARM_ARRAY1;
    Arm3 = ARM_ARRAY3;
}

