inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/evilkill.h"
#include "/sys/ss_types.h"

create_monster()
{
    if (!IS_CLONE)
	return;
    set_name("hill-troll");
    add_name("troll");
    set_race_name("troll"); 
    set_adj("nasty");
    set_long("It is a very ugly and nasty lookin' troll.\n");
    set_gender(0);
    default_config_npc(39);
    set_base_stat(SS_CON, 192);
    set_base_stat(SS_STR,185);
    set_base_stat(SS_DEX,110);
    set_base_stat(SS_DIS,170);
    set_hp(19000);
    set_aggressive(1);
    set_skill(SS_WEP_CLUB,93);
    set_skill(SS_PARRY,52);
    set_skill(SS_BLIND_COMBAT,67);
    set_skill(SS_DEFENCE,54);
    set_skill(SS_AWARENESS,44);
    add_prop(LIVE_I_SEE_DARK,4);
    add_prop(CONT_I_WEIGHT,1467000);
    add_prop(CONT_I_VOLUME,378000);
    add_prop(CONT_I_HEIGHT,350);
    set_alignment(-200 + random(100));
    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me","say I will eat you as supper tonight, idiot!","say Put that fire out!","extinguish fire"}));
}

arm_me()
{
    object wep, arm;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(this_object()));

    wep = clone_object("/d/Gondor/common/wep/trollclub");
    wep->move(this_object());
    command("wield club");

    arm = clone_object("/d/Gondor/common/arm/trollcape");
    arm->move(this_object());
    command("wear cape");
}

/* Solamnian prestige */
query_knight_prestige() {return (250);}
