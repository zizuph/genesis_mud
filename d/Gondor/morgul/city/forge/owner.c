#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_monster.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_ithil_monster() 
{
    add_name(({"shopkeeper","owner","shopowner",}));
    set_race_name("orc");
    set_adj(({"angry","dark-skinned"}));

    default_config_npc(62);
    set_base_stat(SS_CON,95);
    set_base_stat(SS_STR,95);
    set_skill(SS_WEP_SWORD, random(10)+90);
    set_skill(SS_AWARENESS, random(10)+90);
    set_skill(SS_DEFENCE, random(10)+90);
    set_skill(SS_PARRY, random(10)+90);
    set_skill(SS_TRADING, random(10)+90);
    set_alignment(-100-random(200));
    set_chat_time(12);
	add_chat("Me got supplies. You got money?");
	add_chat("What do you want?");
    add_cchat("Get out of here, you stinking thief!");
    add_cchat("I'll eat your corpse really soon now!");
    add_cchat("Come here, you orcs! Fresh meat!");

    set_pick_up(0);
}

public void
arm_me()
{
    FIX_EUID
    clone_object(MORGUL_DIR + "obj/ithilsword")->move(TO);
    command("wield sword");
    clone_object(MORGUL_DIR + "obj/ltunic")->move(TO);
    command("wear armour");
}

/* solamnian prestige */
public int query_knight_prestige() { return -3; }

