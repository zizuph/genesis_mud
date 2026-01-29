/* 
 * /d/Kalad/common/wild/pass/npc/lily_knight.c
 * Purpose    : A knight of Thanar
 * Located    : /d/Kalad/common/wild/pass/desert/camp/c33
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("marselius");
   add_name("knight");
   add_name("master");
   set_race_name("human");
   set_adj("strong");
   add_adj("alert");
   set_long("An impressive-looking individual whose eyes are carefully "+
      "scanning his surroundings. With his dark hair and eyes, he almost "+
      "looks like one of the Bedellin, except that there seems to be an "+
      "uncanny glint of malice in his gaze.\n");
   set_stats(({125,105,125,85,85,125}));
   set_alignment(-1000);
   set_skill(SS_WEP_SWORD,90);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_BLIND_COMBAT,50);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,90);
   set_skill(SS_AWARENESS,50);
   set_title("the Black Lily Knight Of Thanar");
   set_act_time(6);
   add_act("emote carefully appraises you as an opponent.");
   add_act(({"say We Knights despise the lesser races.","emote spits on the ground in disgust at the thought of gnomes and hobbits."}));
   add_act("chuckle evil");
   add_act("say Thanar watch over you, stranger.");
   set_cact_time(3);
   add_cact("say I promise you a slow and painful death.");
   add_cact("say Fool! You shall die for attacking me!");
   add_cact("say Your death shall please the might Thanar!!");
   add_cact("laugh evil all");
   add_speak("With the help of the Bedellin nomads, the conquest of Kabal "+
      "will be like taking money from a beggar! However, there is still "+
      "that meddlesome witch, Duthrala. Perhaps if she were to ... let's "+
      "say ... suddenly disappear, then perhaps I could return the favor.\n");
   set_default_answer("The lily knight says: Quit wasting my time with "+
      "your inane questions!\n");
   add_ask(({"witch","duthrala","favor"}),"I'm very "+
      "pleased that you are interested in my offer. All I require from you "+
      "is the death of the Bedellin witch. Of course you'll have to bring "+
      "me her robe to prove her death. But once that is done, I shall give "+
      "you your just reward!\n");
   add_ask(({"quests","quest","tasks","task"}),
      "The knight just laughs at you.\n");
   add_ask(({"ruined tower","tower","ruins","ruin"}),
      "Hmm, how did you find out about that? Very "+
      "well, now that you know of it, you might as well hear the rest of "+
      "the story. It was once a great stronghold of magic for the Order of "+
      "Thanar, but has since fallen into ruins. It is rumoured to be "+
      "located somewhere among the dunes. However, noone that has entered "+
      "it has ever left, for it is rumoured to be inhabited by undead.\n");
   add_ask(({"thanar","t'har"}),
      "Hahahahaha!! They are one and the same! These "+
      "foolish savages don't realize that they worship but one aspect of "+
      "the almighty Thanar!\n");
   set_knight_prestige(1000);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   trig_new("%w 'gives' 'you' 'a' 'frost' 'white' %s","react_give");
}
void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/wild/pass/arm/bed_ekeff");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/wild/pass/arm/bed_erobe");
   arm -> move(TO);
   arm = clone_object(CVAN(obj/npc_symbol));
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/caravan/wep/lksword");
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(6))->move(TO,1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("say For the glory of Thanar!!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   me = TO;
   if (random(5))
      return 0;
   hitresult = enemy->hit_me(300 + random(300), W_BLUDGEON, me, -1);
   how = " without effect";
   if (hitresult[0] > 0)
      how == "";
   if (hitresult[0] > 10)
      how = " hard";
   if (hitresult[0] > 20)
      how = " very hard";
   if (hitresult[0] > 30)
      how = " extremely hard";
   if (hitresult[0] > 40)
      how = " tremendously hard";
   me -> catch_msg("You bodyslam your opponent!\n"+
      capitalize(enemy->query_pronoun())+" is bodyslammed"+
      how + ".\n");
   enemy -> catch_msg(QCTNAME(me) + " bodyslams you!\n"+
      "You are bodyslammed" + how + ".\n");
   tell_watcher(QCTNAME(me) + " bodyslams " + QTNAME(enemy) + "!\n"+
      capitalize(enemy->query_pronoun()) + " is bodyslammed"+
      how + ".\n", enemy);
   if (enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}
int
react_give(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_give",who);
      return 1;
   }
}
void
return_give(string who)
{
   object obj;
   int ran;
   if(obj = present(who,environment())){
      command("say This is what you deserve!!!");
      command("laugh " + (obj->query_real_name()));
      command("kill " + (obj->query_real_name()));
   }
}