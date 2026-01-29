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
    set_name("orc");
    add_name("orc");
    set_race_name("orc"); 
    set_adj("ugly");
    set_long("The hideous orc is wearing a chainmail, on which you can see a crest -\n"+
"a white hand - the symbol of Saruman!\n");
    default_config_npc(22+random(6));
    set_base_stat(SS_STR,35+random(10));
    set_base_stat(SS_DIS,70+random(10));
    set_base_stat(SS_DEX, 35+random(10));
    set_base_stat(SS_CON,35+random(10));
    set_hp(1500);
    set_aggressive(1);
    set_skill(SS_WEP_CLUB,random(15)+30);
    set_skill(SS_WEP_SWORD,30+random(15));
    set_skill(SS_PARRY,random(15)+30);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_DEFENCE,random(10)+30);
    add_prop(CONT_I_HEIGHT,1500);
    add_prop(CONT_I_WEIGHT,45000);
    add_prop(CONT_I_VOLUME,800);
add_cchat("Sharkey will soon rule!");
add_cchat("The White Hand is going to dominate the world!");
add_cchat("We will feed on your dead and molested body tonight!");
    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me","say Die like the screaming pig you are!"}));
}

arm_me()
{
    object wep, arm;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(this_object()));

    wep = clone_object("/d/Gondor/elessar/obj/wep/orcscim");
    wep->move(this_object());
    command("wield scimitar");

    arm = clone_object("/d/Gondor/elessar/obj/arm/orcmail");
    arm->move(this_object());
    command("wear mail");
  arm = clone_object("/d/Gondor/elessar/obj/arm/whshield");
  arm->move(this_object());
  command("wear shield");
}

