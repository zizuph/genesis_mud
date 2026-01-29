/*
 *	/d/Gondor/morgul/npc/ithil_officer.c
 *
 *	Olorin, July 1993
 *	General revision: Olorin, February 1996
 *      Modified 4-5-2000 by Stern, to load matted platemails instead of
 *                                  black ones.
 *      Modified 11-4-2009 by Eowul, Updated stats
 */
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_man.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/mattock", MORGUL_DIR + "obj/halberd", MORGUL_DIR + "obj/mornstar"})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/normalplate"})

public void
create_ithil_officer()
{
}

nomask void
create_ithil_man()
{
    int     rnd = random(41);
 
    set_short("officer");
    set_pshort("officers");
    set_name("officer");
    set_pname("officers");
    set_long(CAP(LANG_ADDART(implode(query_adjs()," ")))
      + " officer of the Morgul Army. He is from Harad or Khand in the "
      + "south, and looks like he is the veteran of many campaigns. "
      + "Experienced and skilled as he is, he is a terrifying opponent "
      + "in combat.\n");
    
    default_config_npc(110 + rnd);
    set_base_stat(SS_DEX,   150  +  rnd);
    set_alignment(-350-rnd*10);
    set_skill(SS_WEP_SWORD,    75 + rnd);
    set_skill(SS_WEP_POLEARM,  75 + rnd);
    set_skill(SS_WEP_CLUB,     75 + rnd);
    set_skill(SS_WEP_AXE,      75 + rnd);
    set_skill(SS_WEP_KNIFE,    75 + rnd);
    set_skill(SS_PARRY,        75 + rnd);
    set_skill(SS_DEFENCE,      75 + rnd);
    set_skill(SS_BLIND_COMBAT, 85 + rnd);
    add_prop(CONT_I_HEIGHT,   170 + rnd);
    add_prop(CONT_I_WEIGHT, 85000 + rnd*500);
    add_prop(CONT_I_VOLUME, 80000 + rnd*500);    

    create_ithil_officer();
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

void
upgrade_monster(int stat)
{
    int     xs = stat  +  10;

    if (query_stat(SS_STR) < xs)
        set_base_stat(SS_STR, xs);

    xs = stat + 30;
    if (query_stat(SS_DEX) < xs)
        set_base_stat(SS_DEX, xs);
    if (query_stat(SS_CON) < xs)
        set_base_stat(SS_CON, xs);
    xs = stat - 20;
    if (query_stat(SS_INT) < xs)
        set_base_stat(SS_INT, xs);
    if (query_stat(SS_DIS) < xs)
        set_base_stat(SS_DIS, xs);
    xs = stat - 30;
    if (query_stat(SS_WIS) < xs)
        set_base_stat(SS_WIS, xs);
        
    set_hp(query_max_hp());
}

