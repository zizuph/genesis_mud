inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/d/Gondor/elessar/lib/evilkill.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"

create_monster()
{
    if (!IS_CLONE)
	return;
    set_name("hill-troll");
    add_name("troll");
    set_race_name("troll"); 
    set_adj("nasty");
    set_long("It is a very ugly and nasty looking troll.\n");
    default_config_npc(52);
    set_base_stat(SS_CON, 165);
    set_base_stat(SS_DIS, 200);
    set_base_stat(SS_STR,159);
    set_base_stat(SS_DEX,120);
    set_hp(25000);
    set_aggressive(1);
    set_alignment(-400);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_PARRY,57);
    set_skill(SS_BLIND_COMBAT,94);
    set_skill(SS_DEFENCE,59);
    set_skill(SS_AWARENESS,49);
    add_prop(LIVE_I_SEE_DARK,4);
    add_prop(CONT_I_HEIGHT,360);
    add_prop(CONT_I_WEIGHT,450000);
    add_prop(CONT_I_VOLUME,420000);
    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me","say Ok, come on you bastards!"}));
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
