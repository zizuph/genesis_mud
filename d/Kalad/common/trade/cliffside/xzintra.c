/**********************************************************************
 * - xzintra.c                                                      - *
 * - Bug fix. With new uptimes of 30 days Penance should give out   - *
 * - quest more often and not fade out.                             - *
 * - Updated by Damaris@Genesis 11/2004                             - *
 **********************************************************************/
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
int locket;
string long;
object assassin;
void
create_monster()
{
   ::create_monster();
   set_name("penance");
   set_living_name("penance");
   set_title("the Shrouded Assassin of the Zintra");
   set_race_name("human");
   set_long("This old human looks as though his ancient eyes "+
      "have seen much.\n");
  // set_short("old human");
   add_adj("old");
   set_stats(({ 170, 250, 170, 75, 50, 100}));
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_WEP_KNIFE, 100);
   set_skill(SS_PARRY, 100);
   add_speak("A guardsman of the city took a locket from me. I want it back.\n");
   add_act("emote grins evilly.");
   add_act("emote smiles like an old fool.");
   set_act_time(5);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   seteuid(geteuid(this_object()));
   
   clone_object("/d/Kalad/common/trade/cliffside/obj/p2dagger")->move(TO);
   clone_object("/d/Kalad/common/trade/cliffside/obj/pdagger")->move(TO);
   clone_object("/d/Kalad/common/trade/cliffside/obj/zmail")->move(TO);
   clone_object("/d/Kalad/common/trade/cliffside/obj/zcloak")->move(TO);
   clone_object("/d/Kalad/common/trade/cliffside/obj/zboots")->move(TO);
   
   command("wear all");
   command("wield all");
   seteuid(getuid(TO));
   
}
int
special_attack(object enemy)
{
   object me;
   object dagger;
   mixed* hitresult;
   string how;
   me = this_object();
   if(random(3))
      return 0;
   dagger = present("_penance_dagger1");
   if (!dagger || !dagger->query_wielded())
   {
       dagger = present("_penance_dagger2");
       if (!dagger || !dagger->query_wielded())
           return 0;
   }
   hitresult = enemy->hit_me(550 + random(1000), W_IMPALE, me, -1);
   how = " but did no damage";
   if(hitresult[0] > 0)
      how == "";
   if(hitresult[0] > 5)
      how = " barely parting the flesh";
   if(hitresult[0] > 10)
      how = " drawing blood";
   if(hitresult[0] > 15)
      how = " sending blood flying through the air";
   if(hitresult[0] > 20)
      how = " piercing flesh, bone, and tendon";
   me-> catch_msg("You thrust your daggerinto your enemy's knee!\n" +
      capitalize(enemy->query_pronoun()) + "is stabbed in the knee" + 
      how + ".\n");
   enemy-> catch_msg(QCTNAME(me) + " thrusts his dagger into your knee!\n" +
      "You are stabbed in the knee" + how + ".\n");
   tell_watcher(QCTNAME(me) + " thrusts his dagger into " + QCTNAME(enemy) + "!\n",enemy);
   if(enemy->query_hp() <=0)
      enemy->do_die(me);
   return 1;
}
public void
locket_return()
{
   locket = 1;
}
public void
enter_inv(object ob, object from)
{
   if (MASTER_OB(ob) != "/d/Kalad/common/trade/cliffside/obj/locket")
      {
      ::enter_inv(ob, from);
      set_alarm(2.0,0.0,"drop_the_object",ob);
      return;
   }
   if (!interactive(from))
      return;
   else
      set_this_player(from);
   if (from->test_bit("Kalad", 0, 9))
      {
      write(query_The_name(from) + " thanks you.\n");
      TP->catch_msg("You don't feel more experienced.\n");
   }
   else {
      write("The old human thanks you gratefully.\n");
      TP->catch_msg("You feel more experienced.\n");
      TP->add_exp(1500);
      TP->set_bit(0,9);
   }

}
