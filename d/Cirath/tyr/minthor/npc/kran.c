inherit "/std/monster";
#include "../defs.h"
#include <wa_types.h>
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/athas/gladiator/guruquest.h"
#include "/d/Cirath/common/introfnc.h"

mixed attackers;
int more_aid;

void
create_monster ()
{
    set_living_name("kranj'k");
    set_name("kranj'k");
    set_title("Master Warrior of Athas");
    set_race_name("human");
    set_adj("lean");
    add_adj("disciplined");
    set_long("A powerful warrior once in the service of Kalak, Kranj'k "
   +"is now a warrior for hire, selling out his fighting skills to anyone "
   +"with a big purse. Legend has it, that he trained Lyden, and was the "
   +"first gladiator to escape from the slave pits. Why he was spared is "
   +"a mystery.\n");
   set_stats(({ 170, 185, 200, 130, 130, 140}));
    set_all_hitloc_unarmed(50);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_alignment(0);

    set_act_time(3);
    add_act("emote casually catches a small bug in his mouth.");
    add_act("emote stretches his long limbs.");
    add_act("roar");
    add_act("shout I am the greatest warrior in the world!");
    add_act("say I trained Lyden, and you thought he was tough.");
    add_act("say You should not be here, leave or i will kill you.");
    add_act("say I won't waste the water killing you.");
    set_cact_time(3);
    add_cact("say You fools never learn.");
    add_cact("say I have killed worms tougher than you!");
    add_cact("say That kind of tickles, do it again.");
    add_cact("emote sticks his finger into your eye.");
    add_cact("emote smiles grimly.");
    call_out("arm_me",1);
}

void
arm_me()
{
     clone_object("/d/Cirath/tyr/minthor/wep/rkaxe")->move(TO);
    clone_object("/d/Cirath/tyr/arm/l_greave")->move(TO);
    clone_object("/d/Cirath/tyr/arm/l_vhelm")->move(TO);
    clone_object("/d/Cirath/tyr/arm/l_gaunt")->move(TO);
    clone_object("/d/Cirath/tyr/arm/l_shirt")->move(TO);
    command("wield all");
    command("wear all");
}

/*
void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if (!pointerp(attackers)) attackers = ({});
    if (member_array(ob,attackers) == -1) attackers += ({ob});
}
*/

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me=this_object();

    if(random(12)) return 0;

    hitresult = enemy->hit_me(300 + random(200), W_BLUDGEON, me, -1);
    how = "untouched";
    if (hitresult[0] > 0) how = "barely touched";
    if (hitresult[0] > 15) how = "a little bruised";
    if (hitresult[0] > 30) how = "hurt";
    if (hitresult[0] > 50) how = "incredibly hurt";
    if (hitresult[0] > 75) how = "numb all over";

    enemy->catch_msg(QCTNAME(me) + " strikes you with "+
                     HIS_HER(me) + " forearm smash.\n");
    enemy->catch_msg("You feel " + how + ".\n");

    tell_watcher(QCTNAME(me)+" strikes "+QCTNAME(enemy)+
                 " with " + HIS_HER(me) + " forearm smash.\n",
                 me, enemy);

    if(enemy->query_hp() <= 0) enemy->do_die(me);

    return 1;
}

void
bring_aid(object enemy)
{
    object trops;
    int i;

    seteuid(getuid());
    for (i = 0; i < 3; i++)
    {
        trops = clone_object(TZ_MINTHOR + "npc/guard");
        trops->move_living("xxx", ENV(TO));
        trops->command("$kill " + OB_NAME(enemy));
    }
    enemy->attack_object(trops);

    command("say Run while you can");
}

int
special_att(object enemy)
{
    if (query_hp() < 900 && more_aid == 0)
    {
        command("shout Guards!  Guards!  Intruders in the house!  Assist me!");
        tell_room(ENV(TO),"Cries of alarm echo through the house.\n");
        set_alarm(10.0, 0.0, &bring_aid(enemy));
        more_aid = 1;
    }


    return ::special_attack(enemy);
}


void
attacked_by(object ob)
{
    object guard;

    ::attacked_by(ob);
    guard = present("guard", ENV(TO));
    if (guard)
    {
        command("say Kill the intruder!");
        set_alarm(3.0, 0.0, "guard_attack", ob, guard);
    }
    else
    {
        command("say Now its just you and me.  Taste my blade!");
    }
}


void
guard_attack(object enemy, object guard)
{
    if (objectp(guard) && ENV(enemy) == ENV(TO))
    {
        guard->command("emote moves in front of you, " +
          "forcing you to attack him.");
        enemy->attack_object(guard);
    }
}


