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
    set_name("uruk");
    add_name("uruk-hai");
    set_race_name("uruk-hai"); 
    set_adj("menacing");
    set_long("It is a very ugly and menacing uruk-hai commander.\n");
    default_config_npc(43+random(6));
    set_base_stat(SS_DEX, 45);
    set_base_stat(SS_CON,45);
    set_hp(10000);
    set_aggressive(1);
    set_attack_chance(33);
    set_skill(SS_WEP_CLUB,random(35)+35);
    set_skill(SS_WEP_SWORD,35+random(35));
    set_skill(SS_PARRY,random(30)+30);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_DEFENCE,random(30)+30);
    add_prop(CONT_I_HEIGHT,150);
    add_prop(CONT_I_WEIGHT,65000);
    add_prop(CONT_I_VOLUME,1200);
add_cchat("Sauron will soon rule!");
add_cchat("The Red Eye is going to dominate the world!");
add_cchat("We will feed on your dead and molested body tonight!");
  add_cchat("I am a fighting Uruk-Hai! Men of Gondor don't scare me!");
    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me","say Die like the screaming pig you are!"}));
}

arm_me()
{
    object wep, arm, arm2;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(this_object()));

    wep = clone_object("/d/Gondor/elessar/obj/wep/uruksword");
    wep->move(this_object());
    command("wield sword");

    arm = clone_object("/d/Gondor/elessar/obj/arm/orcmail");
    arm->move(this_object());
    command("wear mail");
    arm2 = clone_object("/d/Gondor/elessar/obj/arm/rehelm");
    arm2->move(this_object());
    command("wear helm");
}

