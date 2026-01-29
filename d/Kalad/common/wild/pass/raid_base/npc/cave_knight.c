inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "../defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include <wa_types.h>
#include <macros.h>

#define OBJ CARAVAN + "obj/"
#define ARM CARAVAN + "arm/"
#define WEP CARAVAN + "wep/"
#define TO this_object()
#define TP this_player()

public void
create_kalad_monster()
{
    set_default_answer("say What are you jabbering " +
        "about?? All we care about are those damn goblins!\n", 1);
    add_ask(({"knights", "thanar knights", "holy order of thanar", "thanarians"}),
      "We shall force all of Kalad under the rule of Lord Thanar, greatest "+
      "of the gods!\n");
    add_ask(({"war"}),
      "Ahh, it shall be glorious. All the barbaric demihumans shall be "+
      "cleansed from this city.\n");
    set_name("thrakkan");
    add_name("knight");
    set_race_name("human");
    set_adj("fearsome");
    add_adj("commanding");
    set_long("An aura of complete confidence radiates from this man. His "+
      "regal looks cannot hide the seething anger and cruel nature of his "+
      "black-hearted soul. From his eyes can be seen but one thing...death.\n");
    set_stats(({150, 150, 150, 100, 100, 150}));
    set_alignment(-1000);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_title("the Raid Commander of Thanar");
    set_act_time(3);
    add_act("ponder");
    add_act("emote gazes at a map of Kalad.");
    add_act("think the death and destruction soon to come");
    add_act("grin dem");
    add_act("swing");
    add_act("say It is the destiny of the human race to conquer the "+
      "lesser races of elves, dwarves, gnomes, hobbits and goblins.");
    set_cact_time(2);
    add_act("say We'll get those stupid red goblins!");
    add_cact("say Now, someone to test my battle prowess against!");
    add_cact("laugh loud");
    add_cact("say Such a pitiful fighter you are! I surpassed such "+
      "pitiful fighting when I was but a boy of twelve summers!!");
    add_cact("say You're almost too pitiful to kill!");
    add_cact("thanaraidme");
    add_speak("The coming war will result in the total expulsion of "+
      "demihumans from Kabal!\n");
    set_knight_prestige(1000);
    MONEY_MAKE_PC(random(3))->move(TO, 1);
    MONEY_MAKE_GC(random(10))->move(TO, 1);
    add_leftover(RAID + "obj/thanar_head", "head", 1, 0, 0, 1);
    add_ask(({ "goblin", "goblins", "fang", "fangs", "red fang", "red fangs" }),
        "say The Red Fang! The have gotten in our way " +
        "for the last time. We are going to go in that cave and paint the " +
        "walls red - with their blood! If only we could get that stupid " +
        "scout out of the way.\n", 1);
    add_ask("scout", "say Every time we get " +
        "close to the cave, that stupid hunchbacked goblin warns them " +
        "before we get to the door! Bring me his damned head!!\n", 1);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));
    arm = clone_object(ARM + "mkhelm");
    arm->move(TO);
    arm = clone_object(ARM + "mkplate");
    arm->move(TO);
    arm = clone_object(ARM + "mkgaunt");
    arm->move(TO);
    arm = clone_object(ARM + "mkgreav");
    arm->move(TO);
    arm = clone_object(ARM + "mkcloak");
    arm->move(TO);
    arm = clone_object(ARM + "ktmed");
    arm->move(TO);
    arm = clone_object(OBJ + "npc_symbol");
    arm->move(TO);
    command("wear all");
    wep = clone_object(WEP + "lksword");
    wep->move(TO);
    command("wield all");
}

public int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;

    me = TO;
    if (random(5))
	return 0;

    hitresult = enemy->hit_me(350 + random(350), W_BLUDGEON, me, -1);
    how = " without effect";
    if (hitresult[0] > 0)
	how == "";
    if (hitresult[0] > 10)
	how = " hard";
    if (hitresult[0] > 20)
	how = " very hard";
    if (hitresult[0] > 30)
	how = " extremely hard";
    if (hitresult[0] > 35)
	how = " with such force, the sound of bones and internal organs exploding can be heard";
    me->catch_msg("You bodyslam your opponent!\n"+
      capitalize(enemy->query_pronoun())+" is bodyslammed"+
      how + ".\n");
    enemy->catch_msg(QCTNAME(me) + " bodyslams you!\n"+
      "You are bodyslammed" + how + ".\n");
    tell_watcher(QCTNAME(me) + " bodyslams " + QTNAME(enemy) + "!\n"+
      capitalize(enemy->query_pronoun()) + " is bodyslammed"+
      how + ".\n", enemy);
    if (enemy->query_hp() <= 0)
	enemy->do_die(me);
    return 1;
}

public void
help_friend(object ob)
{
    if(ob && !query_attack() && present(ob, environment()))
    {
	command("say May Thanar have mercy on your soul...");
	command("grin mer");
	command("kill " + OB_NAME(ob));
    }
}

public void
reject(object ob, object from)
{
   command("say I don't want this!");
   command("drop " + ob->query_name());
}

public void
reward_head(object ob, object from)
{
   object pendant;

   if(!present(from, environment()))
   {
      command("shrug");
      command("eat head");
      return;
   }

   if(present(RAID_GOBLIN_REWARD, from))
   {
      command("snarl " + from->query_real_name());
      command("say Goblin scum! Die!!");
      command("kill " + from->query_real_name());
      command("eat head");
      return;
   }

   if(present(RAID_HUMAN_REWARD, from))
   {
      command("say So he came back from the dead eh?? Well good on you " +
         "for fixing that little problem!");
      command("cackle");
      command("eat head");
      return;
   }

   command("cackle hyst");
   command("shout Take that, brother!! The scout is dead, and soon the caves " +
      "will be ours!");
   command("emote grabs the skull and rips a bloody fang out of its mouth.");
   command("emote fetches a small chain from his pocket and ties the fang " +
      "to it.");

   pendant = clone_object(RAID + "obj/thanar_necklace");
   pendant->remove_prop(OBJ_M_NO_DROP);
   pendant->move(this_object(), 1);

   command("give pendant to " + from->query_real_name());
   command("eat head");

   pendant->add_prop(OBJ_M_NO_DROP, 1);

   SCROLLING_LOG(LOG + "trinkets",
      capitalize(from->query_real_name()) + " received the Thanar trinket"
   );
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if(!from)
      return;

   if(ob && ob->query_prop(RAID_GOBLIN_LEFTOVER))
   {
      set_alarm(1.0, 0.0, &reward_head(ob, from));
      return;
   }

   if(ob->query_coin_type())
   {
      set_alarm(1.0, 0.0, &command("say For moi? Ha - thanks!"));
      return;
   }

   set_alarm(1.0, 0.0, &reject(ob, from));
}
