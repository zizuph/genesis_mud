/* lyden.c: Lyden, Huge Gladiator. Revised by Serpine, 11/24/95. */
 
#pragma strict_types
 
inherit "/std/monster";
#include <wa_types.h>
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/athas/gladiator/guruquest.h"
#include "/d/Cirath/common/introfnc.h"
 
mixed attackers;
 
void
create_monster ()
{
    set_living_name("lyden");
    set_name("lyden");
    set_title("Independent Gladiator of World Renown");
    set_race_name("human");
    set_adj("gargantuan");
    add_adj("tanned");
    set_long("Once a slave in Tyr, the awesome power of this gladiator "
            +"won both fame and his freedom. But true freedom escaped "
            +"him, for he was still chained to his lust for blood. His "
            +"life has become an endless string of battles, a search for "
            +"what few worthy opponents he can find.\n"
            +"A chain runs from each of his ears to a ring in his nose.\n"
            +"He has the brutal scars of a Gladiator.\n");
   
    set_stats(({ 200, 170, 170, 75, 75, 200}));
    set_all_hitloc_unarmed(50);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_alignment(0);
   
    set_act_time(3);
    add_act("emote laughs harshly at your puny body.");
    add_act("emote breaks a cinder block over his head.");
    add_act("spit");
    add_act("emote stomps on the ground, shaking the earth.");
    add_act("shout I am the greatest warrior in the world!");
    add_act("say No one can defeat me!");
    add_act("say I challenge anyone to a fair fight!...\n"
           +"Hell! I challenge anyone to an unfair fight!");
    add_act("say Are you even brave enough to attack, small one?");
 
    set_cact_time(3);
    add_cact("say I will do away with you quickly, flea!");
    add_cact("say Why persist? You have no chance of defeating me!");
    add_cact("say Is that the best you can do?");
    add_cact("emote works himself into a wild battlerage.");
    add_cact("emote breaks into a sweat as his breathing becomes heavier.");
 
   
}
 
void
arm_me()
{
    clone_object("/d/Cirath/athas/a_tyr/objects/l_triden")->move(TO);
    clone_object("/d/Cirath/athas/a_tyr/objects/l_greave")->move(TO);
    clone_object("/d/Cirath/athas/a_tyr/objects/l_vhelm")->move(TO);
    clone_object("/d/Cirath/athas/a_tyr/objects/l_gaunt")->move(TO);
    clone_object("/d/Cirath/athas/o_armours/body_scl")->move(TO);
    command("wield all");
    command("wear all");
}
 
void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if (!pointerp(attackers)) attackers = ({});
    if (member_array(ob,attackers) == -1) attackers += ({ob});
}
 
void
do_die(object killer)
{
    object cuir;
   
    if (query_hp() > 0) return;
   
    if (sizeof(attackers) <= 1)
    if (cuir = present(CUIR_ID,killer))
    {
        cuir->report_kill(LYDEN);
    }
    ::do_die(killer);
}
 
/* **************** LYDEN CHARGES! ******************** */
int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
 
    me=this_object();
 
    if(random(8)) return 0;
 
    hitresult = enemy->hit_me(200 + random(200), W_BLUDGEON, me, -1);
    how = "amazed by such a feeble attack";
    if (hitresult[0] > 0) how = "dazed";
    if (hitresult[0] > 15) how = "injured";
    if (hitresult[0] > 30) how = "hurt";
    if (hitresult[0] > 50) how = "severely hurt";
    if (hitresult[0] > 75) how = "on the verge of collapse";
 
    enemy->catch_msg(QCTNAME(me) + " strikes you with "+
                     HIS_HER(me) + " leaping charge.\n");
    enemy->catch_msg("You feel " + how + ".\n");
 
    tell_watcher(QCTNAME(me)+" strikes "+QCTNAME(enemy)+
                 " with " + HIS_HER(me) + " leaping charge.\n",
                 me, enemy);
 
    if(enemy->query_hp() <= 0) enemy->do_die(me);
 
    return 1;
}
