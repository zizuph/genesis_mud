/* 
 * /d/Kalad/common/wild/pass/npc/bed_witch.c
 * Purpose    : Npc that gives cluse to ogre caves
 * Located    : /d/Kalad/common/wild/pass/desert/camp/c30
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

/* by Antharanos */
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
object bedwitch;
int heal;
void
create_monster()
{
   int i;
   set_name("duthrala");
   add_name("witch");
   set_race_name("human");
   set_adj("mysterious");
   add_adj("bedellin");
   set_short("bedellin witch");
   set_long("A strangely odd sight, this woman unlike nearly all other "+
      "Bedellin women is not masked and in fact, has her entire face clearly "+
      "within view. Her strong, fierce features give you cause for respect, "+
      "and even fear. For her to be as she is, in such a society, she must "+
      "truly be a person of incredible importance, in one fashion or the "+
      "other.\n");
   
   for(i = 0; i < 3; i++)
   set_base_stat(i, 90 + random(30));
   set_base_stat(3, 133);
   set_base_stat(4, 125);
   set_base_stat(5, 100);
   set_gender(G_FEMALE);
   
   set_skill(SS_UNARM_COMBAT,60);
   set_skill(SS_WEP_KNIFE,100);
   set_skill(SS_DEFENCE,70);
   set_skill(SS_BLIND_COMBAT,70);
   set_skill(SS_AWARENESS,80);
   set_alignment(900);
   set_knight_prestige(-5);
   set_act_time(3);
   add_act("say Only my magical prowess keeps the tribe from the brink of destruction.");
   add_act("smile conf");
   add_act("say As an ulugarr, you could help me and noone here would think otherwise.");
   add_act("say We could be of mutual benefit to one another.");
   add_act("smirk");
   set_cact_time(3);
   add_cact("emote screams in outrage.");
   add_cact("say You fool!!");
   add_cact("emote snarls with pure rage.");
   add_cact("say T'har will devour you for this!");
   add_cact("say Mat da'if berrani!");
   add_speak("I am in need of an item of great power, I however, cannot "+
      "leave this tent. Our illustrious sheik has forbidden me from leaving, for "+
      "he believes that I must stay here, in case things take a turn for "+
      "the worse. I can help you in times to come, but first you must "+
      "retrieve my spell book from the sheik's tent. Otherwise, we have "+
      "nothing to speak about.\n");
   add_ask(({"item of great power","great power","item"}),
      "You must recover my spell book. All I know is that the sheik took "+
      "it away from me and secreted it somewhere within the camp.\n");
   add_ask(({"sheik"}),
      "His name is Musalim.\n");
   add_ask(({"spell book"}),
      "It is an item of great power.\n");
   set_default_answer("I will not answer foolish questions.\n");
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   set_title("the Witch of the Iriphawa tribe");
   trig_new("%w 'snarls' %s","react_pain");
   trig_new("%w 'kicks' 'you' %s","react_pain");
   trig_new("%w 'attacks' %s","react_pain");
   trig_new("%w 'gives' 'you' 'a' 'brown' 'spell' 'book.\n' %s","react_leave");
}
int
react_pain(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_pain",who);
      return 1;
   }
}
void
return_pain(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("snarl " + (obj->query_real_name()));
      command("wield all");
      command("kill " + (obj->query_real_name()));
   }
}
int
react_leave(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_leave",who);
      return 1;
   }
}
void
return_leave(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("gasp");
      command("open spell book");
      command("read spell book");
      command("say Thank you very much for the return of my spell book.");
      command("bow " + (obj->query_real_name()));
      command("say Now, to fulfill my end of the bargain.");
      command("say Journey to the lair of the stone giants, within the "+
         "Desertrise mountains. Once there, rub the great red orb in their "+
         "lair. That shall give you many helpful clues in a very important "+
         "task.\n");
      command("wave .");
      command("emote leaves the tent.");
      if(bedwitch = present("duthrala", environment(TP)))
         {
         bedwitch -> remove_object();
      }
   }
}
void
arm_me()
{
   object it;
   seteuid(getuid(TO));
   it = clone_object("/d/Kalad/common/wild/pass/arm/bed_w_robe");
   it -> move(TO);
   command("wear all");
   it = clone_object("/d/Kalad/common/wild/pass/wep/bed_edag");
   it -> move(TO);
   MONEY_MAKE_PC(random(3))->move(TO,1);
}
tell_watcher(string str, object enemy)
{
   object me,*ob;
   int i;
   
   me = this_object();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}
int
special_attack(object enemy)
{
   
   int attacktype, i, penet;
   mixed* hitresult;
   string how;
   object me, *ob;
   me = this_object();
   
   attacktype = random(5);
   if (attacktype == 1)
      {
      
      ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });
      
      for (i = 0; i < sizeof(ob); i++)
      {
         penet = 600 + random(400);
         penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_FIRE) / 50;
         hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);
         
         how = "not harmed";
         if (hitresult[0] > 0)                  
            how == "barely scratched";
         if (hitresult[0] > 10)
            how = "slightly scratched";
         if (hitresult[0] > 20)
            how = "scratched quite badly";
         if (hitresult[0] > 40)
            how = "scratched very badly";
         if (hitresult[0] > 60)
            how = "utterly devastated";
         
         ob[i]->catch_msg("You see the bedellin witch move her body in "+
            "a strange rythmic motion and without warning a searing wall of sand "+
            "rushes towards you!\n");
         ob[i]->catch_msg("You were " + how + " by the wall of sand!\n");
         tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the wall of sand!\n", ob[i]);
         
         if (ob[i]->query_hp() <= 0)
            ob[i]->do_die(me);
       }
      return 1;
      return 1;}
   
   if (attacktype == 2)
      {
      if (heal == 5)
         {
         return 0;
       }
      heal += 1;
      write("The bedellin witch closes her eyes and looks concentrated.\n");
      say("The bedellin witch closes her eyes and looks concentrated.\n");
      me->heal_hp(1000);
      return 1;
      return 1;}
   return 0;
}