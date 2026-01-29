// Navarre October 5 2008: Increasing the stats on the elite guards slightly.
//                         They are pretty much useless currently, so let's
//                         make them slightly better.
//
// Was       :     set_stats(({80 + random(40),
//                             70 + random(25),
//                             80 + random(25),
//                             70,70, 120 }));


#include <const.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>

inherit (KNPC + "guard_base");

#define WEP3 KOBJ + "weapon/halberd"
#define WEP2 KOBJ + "weapon/claymore"
#define ARM1 KOBJ + "armour/platemail"
#define ARM2 KOBJ + "armour/winged_helmet"
#define ARM3 KOBJ + "armour/gauntlets"
#define ARM4 KOBJ + "armour/g_robe"
#define ARM5 KOBJ + "armour/leggings"

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
    set_name("guard");
    add_name("militiaman");
    set_adj(ONE_OF(gAdj1));
    add_adj("elite");
    set_short(implode(query_adjs()," ") + " guard");
    set_race_name("human");
    set_gender(G_MALE);
    set_long("This is one of the elite guards of Kalaman. " +
      "Being one of the most skilled, brave, and loyal " +
      "members of the local military, they are usually " +
      "shown a great deal of respect.\n");

    set_stats(({130 + random(40),
                110 + random(25),
                150 + random(25),
                110 + random(25),
                110 + random(25),
                120 + random(20)}));

    set_alignment(600);
    set_knight_prestige(-3);
    
    add_prop(CONT_I_HEIGHT, 180 + random(40));
    add_prop(CONT_I_WEIGHT,70000 + random(10000));
    set_skill(SS_WEP_POLEARM, 75 + random(20));
    set_skill(SS_WEP_SWORD, 75 + random(20));
    set_skill(SS_PARRY, 50 + random(40));
    set_skill(SS_DEFENCE, 70 + random(15));
    set_skill(SS_BLIND_COMBAT, 70 + random(30));
    set_skill(SS_AWARENESS, 60 + random(15));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    // Well Armoured
    set_exp_factor(130);

    set_act_time(25);
    add_act("assist guard");
    add_act("assist calof");
    add_act("assist calof");
    add_act("emote looks around confidently.");
    add_act("say Lord Calof is a wise leader. I hope he " +
      "is able to bring Kalaman through these troubled " +
      "times.");
    add_act("emote stares at you appraisingly.");
    add_act("say Reports say the red dragonarmy is getting closer.");
    
    equip(({
        ({ WEP2, WEP3 })[random(2)],
            ARM1, ARM2, ARM3, ARM4, ARM5 }));
}
