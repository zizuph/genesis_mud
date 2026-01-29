inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/evilkill.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"

create_monster()
{
    if (!IS_CLONE)
	return;
    set_name("hill-troll");
    add_name("troll");
    set_race_name("troll"); 
    set_adj("ugly");
    set_adj("large");
    set_gender(0);
    set_long("It is a very ugly and nasty lookin' troll.\n");

    default_config_npc(60);
    set_base_stat(SS_CON, 150);
    set_base_stat(SS_STR,154);
    set_base_stat(SS_DIS,175);
    set_base_stat(SS_DEX,120);
    set_hp(15000);
    set_random_move(12);
    set_aggressive(1);
    set_alignment(-400);
    set_skill(SS_WEP_CLUB,88);
    set_skill(SS_PARRY,77);
    set_skill(SS_BLIND_COMBAT,94);
    set_skill(SS_DEFENCE,69);
    set_skill(SS_AWARENESS,48);
    add_prop(LIVE_I_SEE_DARK,4);
   add_prop(CONT_I_HEIGHT,3500);
   add_prop(CONT_I_VOLUME,440000);
   add_prop(CONT_I_WEIGHT,478000);
    set_alignment(-200 + random(100));
    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me","say I will crush you with my club, and eat your brains!"}));
}

arm_me()
{
    object wep, arm;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(this_object()));

    wep = clone_object("/d/Gondor/common/wep/trollhammer");
    wep->move(this_object());
    command("wield hammer");

    arm = clone_object("/d/Gondor/common/arm/trollcape");
    arm->move(this_object());
    command("wear cape");
}

/* Solamnian prestige */
query_knight_prestige() {return (250);}
