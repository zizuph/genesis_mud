/* This file is /d/Gondor/morgul/npc/ithil_guard.c     */
/*                                                     */
/* Olorin, July 1993                                   */
/*      Modified 11-4-2009 by Eowul, Updated stats */

#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_man.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/halberd", MORGUL_DIR + "obj/spear" })
#define ARM_ARRAY1 ({MORGUL_DIR + "obj/blackcap"})
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/chainmail"})
#define ARM_ARRAY3 ({MORGUL_DIR + "obj/ithil_cloak"})

public void
create_ithil_guard()
{
}

nomask void
create_ithil_man()
{
    int     rnd = random(31);
 
    set_short("swarthy guard");
    set_pshort("swarthy guards");
    set_name("guard");
    add_pname("guards");
    set_long(CAP(LANG_ADDART(implode(query_adjs()," ")))
      + " man from Harad or Khand in the south, with a face like a "
      + "skull and burning eyes. He is a soldier in the Morgul Army, "
      + "on duty as a guard.\n");

    default_config_npc(110 + rnd);
    set_skill(SS_WEP_SWORD,    65 + rnd);
    set_skill(SS_WEP_POLEARM,  70 + rnd / 2);
    set_skill(SS_PARRY,        70 + rnd / 2);
    set_skill(SS_DEFENCE,      70 + rnd / 2);
    add_prop(CONT_I_HEIGHT,   180 + rnd/  2);
    add_prop(CONT_I_WEIGHT, 75000 + rnd * 500);
    add_prop(CONT_I_VOLUME, 70000 + rnd * 500);    

    set_chat_time(25+random(15));
    add_chat("I hate this guard duty!");
    add_chat("Guarding day and night, but never does anything happen!");
    add_chat("I want to go down to Ithilien, too! There's the action!");

    set_cchat_time(5+random(10));
    set_act_time(15+random(15));	
    set_cact_time(2+random(2));
}

static void
set_arm_arrays()
{
    ::set_arm_arrays();

    Wep1 = WEP_ARRAY1;
    Arm1 = ARM_ARRAY1;
    Arm2 = ARM_ARRAY2;
    Arm3 = ARM_ARRAY3;
}

