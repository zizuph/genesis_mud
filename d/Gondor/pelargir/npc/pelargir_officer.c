/*
 *	/d/Gondor/pelargir/npc/pelargir_officer.c
 *
 *	Olorin, July 1995
 */
inherit "/d/Gondor/pelargir/npc/pelargir_soldier";

#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({WEP_DIR + "dlongsword", WEP_DIR + "hhalberd", WEP_DIR + "gbattleaxe"})
#define WEP_ARRAY2 ({ARM_DIR + "pel_shield" })
#define ARM_ARRAY1 ({ARM_DIR + "ghelmet"})
#define ARM_ARRAY2 ({ARM_DIR + "schainmail"})

void
set_arm_arrays()
{
    ::set_arm_arrays();

    wep1 = WEP_ARRAY1;
    wep2 = WEP_ARRAY2;
    arm1 = ARM_ARRAY1;
    arm2 = ARM_ARRAY2;
}

void
create_guard()
{
    int     rnd1 = random(31),
            rnd2 = random(31);

    set_short("stern officer");
    set_pshort("officers");
    set_name("officer");
    set_pname("officers");
    set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," ")))
      + " officer of the Pelargir garrison. He is probably from Lebennin "
      + "or Belfalas, the provinces closest to Pelargir. His proud "
      + "stance makes him look like he is the veteran of many battles. "
      + "Experienced and skilled as he is, he is a terrifying opponent "
      + "in combat."));
    
    default_config_npc(85 + (rnd1 + rnd2) / 2);
    set_base_stat(SS_DIS, 100 + rnd2);
    set_alignment(350 + rnd1 * 10);
    set_skill(SS_WEP_SWORD,   75 + rnd1);
    set_skill(SS_WEP_POLEARM, 75 + rnd2);
    set_skill(SS_WEP_CLUB,    75 + rnd1);
    set_skill(SS_WEP_AXE,     75 + rnd2);
    set_skill(SS_WEP_KNIFE,   75 + rnd1);
    set_skill(SS_PARRY,       75 + rnd2);
    set_skill(SS_DEFENCE,     75 + rnd1);
    add_prop(CONT_I_HEIGHT, 170 + rnd1);
    add_prop(CONT_I_WEIGHT, 85000 + rnd1 * 500);
    add_prop(CONT_I_VOLUME, 80000 + rnd1 * 500);    
}

