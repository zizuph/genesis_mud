/* 
 * 2016-02-04 - Cotillion
 * - Cleared set_exp_factor, well armoured for sure, but also high mentals
 */
#include <const.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>

inherit (KNPC + "guard_base");

#define WEP1    (KOBJ + "weapon/sword")
#define WEP2    (KOBJ + "weapon/mace")
#define WEP3    (KOBJ + "weapon/halberd")
#define ARM1    (KOBJ + "armour/chainmail")
#define ARM2    (KOBJ + "armour/winged_helmet")
#define ARM3    (KOBJ + "armour/gauntlets")
#define ARM4    (KOBJ + "armour/b_robe")
#define WEP_SKILL 60 + random(30)

string *gAdj1 = ({"alert","vigilant","wary","watchful","cautious",
                      "careful","prepared"});
string *gAdj2 = ({"black-bearded","young","scarred","noble","muscular",
                      "barrel-chested","blue-eyed"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_guard()
{
    add_name("militiaman");
    add_pname("militiamen");
    
    set_adj(ONE_OF(gAdj1));
    add_adj(ONE_OF(gAdj2));
    set_short(implode(query_adjs()," ") + " militiaman");
    set_race_name("human");
    set_gender(G_MALE);
    set_long("Before you stands one of the militiamen " +
        "of Kalaman. During times of peace, these soldiers enforce " +
        "the law of the city, but during war times, such as now, " +
        "their place is to protect the city and the surrounding " +
        "lands.\n");
    
    set_stats(({ 90 + random(30),
                 90 + random(30),
                120 + random(30),
                110 + random(30),
                110 + random(30),
                 70 + random(20) }));
    
    set_alignment(600);
    set_knight_prestige(-3);
    add_prop(CONT_I_HEIGHT, 180 + random(20));
    add_prop(CONT_I_WEIGHT, 60000 + random(10000));
    set_skill(SS_WEP_SWORD, WEP_SKILL);
    set_skill(SS_WEP_CLUB, WEP_SKILL);
    set_skill(SS_PARRY, 40 + random(30));
    set_skill(SS_DEFENCE, 40 + random(30));
    set_skill(SS_BLIND_COMBAT, 60 + random(30));
    set_skill(SS_AWARENESS, 50 + random(25));
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_act_time(25);
    add_act("assist guard");
    add_act("say The citizens are getting restless. " +
      "They fear an attack any day now.");
    add_act("say Lord Calof is a wise leader. I hope he " +
      "is able to bring Kalaman through these troubled " +
      "times.");
    add_act("emote stares at you appraisingly.");
    add_act("say Reports say the red dragonarmy is getting closer.");

    /* One of 2 weapons and some armours */    
    equip(({
        ({ WEP1, WEP2 })[random(2)],
            ARM1, ARM2, ARM3, ARM4 }));
    
}


