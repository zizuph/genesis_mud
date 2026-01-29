/* hgiant.c: Generic Half-giant guard. Serpine, 12/23/96. */
 
inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include "defs.h"
 
#define GDESC ({"ugly","dull","angry","tired","ambitious"})[random(5)]
 
void
create_monster()
{
   ::create_monster();
   set_name("guard");
   add_name("giant");
   set_race_name("half-giant");
    add_prop (LIVE_I_NEVERKNOWN, 1);
   set_adj(GDESC);
   add_adj("towering");
    set_gender(random(2));
   set_long("This is an enormous creature, standing over 10 feet tall "
        +"and probably a ton in weight. It is a simple guard, and lacks "
        +"the brainpower for complex thinking.\n");
   set_stats(({110,50,90,5,5,90}));
   set_skill(SS_DEFENCE, 90);
   set_skill(SS_WEP_CLUB, 90);
   set_skill(SS_PARRY, 40);
   set_assist_cry("I must defend!");
   set_default_answer("Umm...Dunno.\n");
   set_act_time(6);
   add_act("grin");
   add_act("emote flexes powerful muscles.");
   add_act("sigh");
   add_act("emote leans on a club.");
   set_cact_time(3);
   add_cact("chuckle");
   add_cact("poke all eye");
   add_act("say I get bored standing here all day.");
   add_act("say I get paid well for this job.");
   add_act("say Don't try anything funny, or I'll squash you.");
   add_cact("say You are a pitiful fool.");
   add_cact("say Why do you even try?");
   add_cact("say I like to destroy puny fools like you.");
}
 
void
arm_me()
{
   object wep;
   seteuid(getuid(this_object()));
   clone_object(TYR_WEP+"club_hge.c")->move(TO);
   clone_object(TYR_ARM+"body_hid.c")->move(TO);
   clone_object(TYR_ARM+"head_hid.c")->move(TO);
   clone_object(TYR_ARM+"legs_hid.c")->move(TO);
   command("wield all");
   command("wear all");
}

 
 
/* ****************** Ground-Sweep ************************* */
 
int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    int bonk;
 
    me=this_object();
 
    if(random(4)) return 0;
 
    hitresult = enemy->hit_me(150 + random(150), W_BLUDGEON, me, -1);
    how = "puzzled by such a useless attack";
    bonk = 0;
    if (hitresult[0] > 0)  { how = "pushed back"; bonk = 10; }
    if (hitresult[0] > 15) { how = "knocked back"; bonk = 20;  }
    if (hitresult[0] > 30) { how = "knocked over"; bonk = 30; }
    if (hitresult[0] > 50) { how = "thrown several feet"; bonk = 40; }
    if (hitresult[0] > 75) { how = "thrown several yards"; bonk = 50; }
 
    enemy->catch_msg(QCTNAME(me) + " ground sweeps you with "+
                     HIS_HER(me) + " huge club.\n");
    enemy->catch_msg("You are " + how + ".\n");
 
    tell_watcher(QCTNAME(me)+" ground sweeps "+QCTNAME(enemy)+
                 " with " + HIS_HER(me) + " huge club.\n"+
                 QCTNAME(enemy)+" is "+how+".\n",
                 me, enemy);
    if (bonk>0) { enemy->add_attack_delay(bonk, 1); }
 
    if(enemy->query_hp() <= 0) enemy->do_die(me);
 
    return 1;
}
