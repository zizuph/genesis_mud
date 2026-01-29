/*
 *  Palmer December 2002 snarfed from:
 *	/d/Gondor/morgul/npc/ithil_uruk.c
 *
 *	Olorin, July 1993
 *	General revision: Olorin, Feb 1996
 */
#pragma strict_types

inherit "/d/Shire/bree/rooms/town/stable/npc/soldier.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "uruk_defs.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/mattock", MORGUL_DIR + "obj/halberd", MORGUL_DIR + "obj/mornstar"})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/chainmail"})

public void
create_ithil_uruk()
{
}

nomask void
create_ithil_soldier()
{
    int rnd = random(41);
    set_short("black orc");
    set_pshort("black orcs");
    set_name("orc");
    set_pname("orcss");
    set_adj(({"filthy", "angry"}));
    // remove_adj("black-skinned");
    set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," ")))
    + " orc, one of the uruk-hai, with crooked legs and long arms "
    + "that hang almost to the ground. He looks much stronger and "
    + "meaner than other orcs of lesser breeds."));

    default_config_npc(85 + rnd / 2);
    set_base_stat(SS_INT, 65 + rnd);
    set_base_stat(SS_WIS, 65 + rnd);

    set_alignment(-350-rnd*10);

    set_skill(SS_WEP_SWORD,   75 + rnd);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_CLUB,    75 + rnd);
    set_skill(SS_WEP_AXE,     75 + rnd);
    set_skill(SS_WEP_KNIFE,   75 + rnd);
    set_skill(SS_PARRY,       75 + rnd);
    set_skill(SS_DEFENCE,     75 + rnd);
    add_prop(CONT_I_HEIGHT,   170 + rnd);
    add_prop(CONT_I_WEIGHT, 85000 + rnd * 500);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_VOLUME, 80000 + rnd * 500);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_DONT_CLING, 1);
    create_ithil_uruk();

    reset_monster();
}


// This is to keep the guy from chasing people
public void
start_follow(object ob)
{
    // Null
}

public void
do_die(object killer)
{
    killer->add_prop("_i_killed_uruk", 1);
    ::do_die(killer);
}


static void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Wep2 = WEP_ARRAY2;
    Arm2 = ARM_ARRAY2;

    set_all_hitloc_unarmed(20);
}

