/*
 *      /d/Gondor/common/npc/whorc.c
 *
 *      Modified to Gondor's monster by Fysix, Feb 1997
 */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_gondor_monster()
{
    set_race_name("orc"); 
    set_adj("ugly");
    set_long("The hideous orc is wearing a chainmail, " +
     "on which you can see a crest -\n" +
     "a white hand - the symbol of Saruman!\n");

    default_config_npc(22 + random(6));
    set_base_stat(SS_STR,35+random(10));
    set_base_stat(SS_DIS,70+random(10));
    set_base_stat(SS_DEX, 35+random(10));
    set_base_stat(SS_CON,35+random(10));
    set_alignment(-100);
    set_aggressive(1);

    set_skill(SS_WEP_CLUB, random(15)+30);
    set_skill(SS_WEP_SWORD, 30+random(15));
    set_skill(SS_PARRY, random(15)+30);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DEFENCE, random(10)+30);

    add_prop(CONT_I_HEIGHT, 1500);
    add_prop(CONT_I_WEIGHT, 45000);
    add_prop(CONT_I_VOLUME, 800);

    add_cchat("Sharkey will soon rule!");
    add_cchat("The White Hand is going to dominate the world!");
    add_cchat("We will feed on your dead and molested body tonight!");

    // Give the orc some equipment
    set_equipment( ({ WEP_DIR + "orcscim", ARM_DIR + "orcmail",
                      ARM_DIR + "whshield"}));
}

// solemnian prestige
public int query_knight_prestige() {return 500;}

