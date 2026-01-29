inherit "/std/monster";
inherit "/d/Gondor/common/lib/logkill";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("hill-troll");
    add_name("troll");
    set_race_name("troll"); 
    set_adj("ugly");
    set_adj("large");
    set_gender(G_MALE);
    set_long("It is a very ugly and nasty lookin' troll.\n");
    default_config_npc(60);
    set_base_stat(SS_CON, 110);
    set_base_stat(SS_STR, 114);
    set_base_stat(SS_DIS, 115);
    set_base_stat(SS_DEX, 100);
    set_random_move(12);
    set_aggressive(1);
    set_alignment(-350 - random(100));
    set_skill(SS_WEP_CLUB, 88);
    set_skill(SS_DEFENCE, 69);
    set_skill(SS_PARRY, 77);
    set_skill(SS_BLIND_COMBAT, 94);
    set_skill(SS_AWARENESS, 48);
    add_prop(LIVE_I_SEE_DARK, 4);
    add_prop(CONT_I_HEIGHT, 350);
    add_prop(CONT_I_VOLUME, 440000);
    add_prop(CONT_I_WEIGHT, 478000);
    set_all_hitloc_unarmed(20);
    seq_new("do_things");
    seq_addfirst("do_things",
     ({"@@arm_me","say I will crush you with my club, and eat your brains!"}));
}

void
arm_me()
{
    object wep, arm;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    FIX_EUID

    wep = clone_object(WEP_DIR + "trollhammer");
    wep->move(TO);
    command("wield hammer");

    arm = clone_object(ARM_DIR + "trollcape");
    arm->move(TO);
    command("wear cape");
}

/* Solamnian prestige */
query_knight_prestige() {return (450);}

