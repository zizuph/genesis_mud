/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/common/lib/logkill.c"
#include "/d/Gondor/defs.h"

create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("hill-troll");
    add_name("troll");
    set_race_name("troll"); 
    set_adj("nasty");
    set_long("It is a very ugly and nasty lookin' troll.\n");
    set_gender(G_MALE);
    default_config_npc(39);
    set_base_stat(SS_CON, 122);
    set_base_stat(SS_STR, 125);
    set_base_stat(SS_DEX, 90);
    set_base_stat(SS_DIS, 110);
    set_aggressive(1);
    set_skill(SS_WEP_CLUB, 93);
    set_skill(SS_PARRY, 52);
    set_skill(SS_BLIND_COMBAT, 67);
    set_skill(SS_DEFENCE, 54);
    set_skill(SS_AWARENESS, 44);
    add_prop(LIVE_I_SEE_DARK, 4);
    add_prop(CONT_I_WEIGHT, 1467000);
    add_prop(CONT_I_VOLUME, 378000);
    add_prop(CONT_I_HEIGHT, 350);
    set_all_hitloc_unarmed(23);
    set_alignment(-350 - random(100));
    seq_new("do_things");
    seq_addfirst("do_things",
        ({"@@arm_me","say I will eat you as supper tonight, idiot!",
          "say Put that fire out!","extinguish fire"}));
}

arm_me()
{
    object wep, arm;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    FIX_EUID

    wep = clone_object(WEP_DIR + "trollclub");
    wep->move(TO);
    command("wield club");

    arm = clone_object(ARM_DIR + "trollcape");
    arm->move(TO);
    command("wear cape");
}

/* Solamnian prestige */
query_knight_prestige() {return (450);}
