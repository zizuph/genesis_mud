/*
 *	/d/Gondor/rohan/edoras/npc/edoras_officer.c
 *
 *	Olorin, July 1995
 *  Modification log:
 *    Alto, 19-Mar-02, commented out and replaced ARM_ARRAY3 because
 *    npc was cloning and wearing two surcoats. This could
 *    probably be done better by creating an alternative
 *    set of greaves of less value to place in the array.
 */
inherit "/d/Gondor/rohan/edoras/npc/edoras_soldier";

#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({EDORAS_DIR + "obj/guardsword", WEP_DIR + "rospear", EDORAS_DIR + "obj/rosword"})
#define WEP_ARRAY2 ({EDORAS_DIR + "obj/roshield" })
#define ARM_ARRAY1 ({EDORAS_DIR + "obj/rohelm"})
#define ARM_ARRAY2 ({EDORAS_DIR + "obj/corslet"})
// #define ARM_ARRAY3 ({EDORAS_DIR + "obj/roh_surcoat", EDORAS_DIR + "obj/rogreaves"})
#define ARM_ARRAY3 ({EDORAS_DIR + "obj/rogreaves"})

void
set_arm_arrays()
{
    ::set_arm_arrays();

    wep1 = WEP_ARRAY1;
    wep2 = WEP_ARRAY2;
    arm1 = ARM_ARRAY1;
    arm2 = ARM_ARRAY2;
    arm3 = ARM_ARRAY3;
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
      + " officer of the King's Eored. His stance reveals "
      + "experience from years of service as a warrior. "
      + "Experienced and skilled as he is, he is a terrifying "
      + "opponent in battle."));
    
    default_config_npc(115 + (rnd1 + rnd2) / 2);
    set_base_stat(SS_DIS, 130 + rnd2);
    set_alignment(650 + rnd1 * 10);
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

