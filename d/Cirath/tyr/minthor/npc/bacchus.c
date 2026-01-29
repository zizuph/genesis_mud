inherit "/d/Cirath/std/monster";
#include "/d/Cirath/common/defs.h"
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include <wa_types.h>

create_monster()
{
   set_name("bacchus");
   set_title(" the Master Hunter of the Minthor House");
   set_race_name("human");
   set_adj("lean");
   add_adj("agitated");
   set_gender(0);
   set_short("lean agitated human");
   set_long("This is the Master Hunter of the Minthor Clan.  He is the  "
        +"eldest son of the family, but has no intentions of leaving his "
        +"palatial home unless necessary.  He stand roughly six and a "
        +"half feet tall and seems to be well muscled.  He does not look "
        +"happy to see you.\n");
   set_alignment(-50);
   set_stats(({125,160,120,100,100,120}));
   set_skill(SS_WEP_CLUB,70);
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,90);
   set_skill(SS_WEP_SWORD,70);
   set_skill(SS_2H_COMBAT,70);
   set_act_time(3);
   add_act("say Get out of my room!");
   add_act("say You really should leave before this gets nasty.");
   add_act("say I was busy here, I would have preferred no interuptions.");
   add_act("emote grins wolfishly");
   set_cact_time(6);
   add_cact("say That was the stupidest thing you could have done.");
   add_cact("say I will have you drawn and quartered in the market square "
        +"for this!");
   add_cact("emote throws back his head and roars with laughter.");
   add_prop(LIVE_I_NEVERKNOWN,1);

}

void
arm_me()
{
   clone_object(TZ_MINTHOR + "wep/b_club")->move(TO);
   clone_object(TZ_MINTHOR + "wep/b_sword")->move(TO);
   command("wield all");
   clone_object(TZ_MINTHOR + "arm/b_plate")->move(TO);
   clone_object(TZ_MINTHOR + "arm/b_helm2")->move(TO);
   clone_object(TZ_MINTHOR + "arm/b_cloak")->move(TO);
   command("wear all");
   MONEY_MAKE_GC(random(50))->move(this_object(),1);
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me=this_object();

   if(random(10)) return 0;

   hitresult = enemy->hit_me(250 + random(150), W_SLASH, me, -1);
    how = "untouched";
    if (hitresult[0] > 0) how = "barely scraped";
    if (hitresult[0] > 15) how = "slightly wounded";
    if (hitresult[0] > 30) how = "wounded";
    if (hitresult[0] > 50) how = "sliced dangerously";
    if (hitresult[0] > 75) how = "mortally wounded";

    enemy->catch_msg(QCTNAME(me) + " lashes out at you with "+
                     HIS_HER(me) + " razor-reed sword.\n");
    enemy->catch_msg("You feel " + how + ".\n");

    tell_watcher(QCTNAME(me)+" lashes out at "+QCTNAME(enemy)+
                 " with " + HIS_HER(me) + " razor-reed sword.\n",
                 me, enemy);

    if(enemy->query_hp() <= 0) enemy->do_die(me);

    return 1;
}


