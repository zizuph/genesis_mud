/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"
#include "/d/Gondor/common/lib/logkill.c"

#define WEP1 ROH_DIR + "horn/obj/long_sword"
#define ARM1 ROH_DIR + "edoras/obj/roshield"
#define ARM2 ROH_DIR + "horn/obj/b_coat_mail"
#define ARM3 ROH_DIR + "edoras/obj/rohelm"
#define ARM4 ROH_DIR + "horn/obj/mail_leggings"

create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("erkenbrand");
    add_name("man");
    set_race_name("human");
    set_adj(({"tall","Rohirrim"}));
    set_long(BSN("The Rohirrim is tall and long-limbed, with long "+
    "flaxen braids; his face is stern and keen. He looks "+
    "like a true leader."));
    set_title("Marshal of Westfold");
    set_base_stat(SS_CON,random(10)+85);
    set_base_stat(SS_DEX,random(10)+80);
    set_base_stat(SS_STR,random(10)+80);
    set_base_stat(SS_INT,random(5)+70);
    set_base_stat(SS_WIS,random(5)+80);
    set_base_stat(SS_DIS,random(5)+85);
    set_alignment(450+random(250));
    set_skill(SS_AWARENESS,50);
    set_skill(SS_ANI_HANDL,55);
    set_skill(SS_WEP_SWORD, random(5)+80);
    set_skill(SS_WEP_POLEARM, random(5)+80);
    set_skill(SS_DEFENCE,85);
    set_skill(SS_PARRY,80);
    add_prop(CONT_I_HEIGHT,190); 
    add_prop(CONT_I_WEIGHT,70000);
    add_prop(CONT_I_VOLUME,70000);

    set_cchat_time(20);
    add_cchat("Intruder! Alert!");

}

arm_me()
{
    object wep, arm;

    FIX_EUID

    wep = clone_object(WEP1);
    wep->move(TO);
    arm = clone_object(ARM1);
    arm->move(TO);
    arm = clone_object(ARM2);
    arm->move(TO);
    arm = clone_object(ARM3);
    arm->move(TO);
    arm = clone_object(ARM4);
    arm->move(TO);
    command("wield all");
    command("wear all");
}

/* Solamnian knight prestige */
query_knight_prestige() {return (-10);}
