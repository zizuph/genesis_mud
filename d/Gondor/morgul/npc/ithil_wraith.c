/*
 *	/d/Gondor/morgul/npc/ithil_wraith.c
 *
 *	Olorin, August 1993
 *	Modified by Elessar, Feb 94.
 *	- now defined as Undead by the property LIVE_I_UNDEAD.
 *	- also given a nasty black mace in its weapon-array: wraith_mace.c
 *	which is a mace of slaying elves and humans - truly evil ;-)
 *	General revision: Olorin, February 1996
 *      5-5-2000 Stern, adapted to use unique_platemail to reduce
 *                      number of magical armours.
 */
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_monster.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/mattock", MORGUL_DIR + "obj/wraith_mace", MORGUL_DIR + "obj/halberd"})
#define ARM_ARRAY1 ({MORGUL_DIR + "obj/platehelm"})
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/platemail_unique"})
#define ARM_ARRAY3 ({MORGUL_DIR + "obj/blackcloak"})

public void
create_ithil_wraith()
{
}

nomask void
create_ithil_monster()
{
    int     rnd = random(16);

    set_name(({"captain", "shape", "undead", "wraith"}));
    set_pname("wraiths");
    set_race_name("human"); 
    add_adj(({"dark", "tall", "terrible", "undead"}));
    set_short("dark wraith");
    set_pshort("dark wraiths");
    set_long("A dark towering shape with eyes glowing like coal. "
      + "He is one of the servants of the Dark Lord, ages ago a mighty "
      + "warrior, but now he is undead, not a living man anymore, but "
      + "not one of the mighty nazgul.\n");
    
    default_config_npc(150 + rnd);
    set_base_stat(SS_INT, 160 + rnd);
    
    set_alignment(-500-rnd*10);
    set_skill(SS_WEP_POLEARM, 95 + rnd);
    set_skill(SS_WEP_AXE,     95 + rnd);
    set_skill(SS_WEP_CLUB,    95 + rnd);
    set_skill(SS_PARRY,       95 + rnd);
    set_skill(SS_DEFENCE,     95 + rnd);
    add_prop(CONT_I_HEIGHT,   195 + rnd);
    add_prop(CONT_I_WEIGHT, 65000 + rnd * 200);
    add_prop(CONT_I_VOLUME, 60000 + rnd * 200);    
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD,   50);
    add_prop("_ranger_i_not_brawl", 1);

    set_chat_time(15 + random(15));
    add_chat("Lugburz wants it, you will do it!");

    set_cchat_time(5 + random(10));
    add_cact("You little land-rat!");
    add_cact("Dirty spy, take this!");

    set_act_time(15 + random(15));	

    set_cact_time(2 + random(2));
    add_cact("hiss"); 
    add_cact("growl"); 
    add_cact("@@emote_enemy|snarl"); 

    create_ithil_wraith();
}

public string
query_nonmet_name()
{
    return implode(({query_adjs()[0], query_adjs()[1]})," ")
      + " "  + query_real_name();
}

static void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Arm1 = ARM_ARRAY1;
    Arm2 = ARM_ARRAY2;
    Arm3 = ARM_ARRAY3;

    set_all_hitloc_unarmed(20);
}

