inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Antharanos */
#define QUEST_NAME "claddathquest"
int heal;
int entrails;
string long;
object matron;
void
create_monster()
{
   set_name("lualyrr");
   add_name("priestess");
   add_name("matron");
   set_race_name("drow");
   set_adj("vibrant");
   add_adj("energetic");
   set_long("The very vision of drow beauty and grace is before your "+
      "eyes. Tall and possessing a natural dexterity common to all drow, "+
      "her graceful movements are comparable to those of a feline predator "+
      "stalking her unsuspecting prey.\n");
   set_gender(G_FEMALE);
   set_all_hitloc_unarmed(25); /* A permanent protective ac spell */
   set_stats(({140,200,140,25,25,100}));
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_WEP_CLUB,100);
   set_skill(SS_WEP_AXE,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_AWARENESS,90);
   set_skill(SS_SPELLCRAFT,90);
   set_skill(SS_HIDE,50);
   set_skill(SS_SNEAK,50);
   set_alignment(-1100);
   set_knight_prestige(1100);
   set_act_time(3);
   add_act("smirk");
   add_act("grin menacingly all");
   add_act("cackle dem");
   add_act("snarl all");
   add_act("hide");
   add_act("say Wael!");
   set_cact_time(3);
   add_cact("wield spiked adamantine mace");
   add_cact("wield triple-bladed adamantine axe");
   add_cact("grin mer all");
   set_title("Claddath, the Matron Mother of House Claddath, Seventh House of Undraeth");
   add_speak("I shall offer you a deal stranger...I for one believe that the city "+
      "of Undraeth should be open to non-drow. However, there are those "+
      "in the city that are rather conservative...for example the drow of "+
      "House Kilsek. Perhaps if someone were to teach them a lesson, "+
      "the other houses would see how closing off the city would only be "+
      "of detriment to us?\n");
   set_default_answer("Stupid questions will lead you nowhere!\n");
   add_ask("lesson","All you must do is slay one of the yochlol within "+
      "the compound of House Kilsek. Then remove its heart and bring it back "+
      "to me.\n");
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   trig_new("%w 'starts' 'to' 'search' %s","react_attack");
   set_alarm(1.0,0.0,"arm_me");
}
entrails_return()
{
   entrails = 1;
}
public void
enter_inv(object ob, object from)
{
   if(MASTER_OB(ob) != "/d/Kalad/common/wild/pass/drow/obj/yochlol_heart")
      {
      ::enter_inv(ob, from);
      set_alarm(2.0,0.0,"drop_the_object",ob);
      return;
   }
   if(!interactive(from))
      return;
   else
      set_this_player(from);
   if(from->test_bit("Kalad",0,19))
      {
      write(query_The_name(from) + " grins demonically.\n");
      TP->catch_msg("You do not feel more experienced.\n");
   }
   else
      {
      command("grin dem");
      command("say Well done...FOOL!");
      TP->catch_msg("You feel more experienced.\n");
      TP->add_exp(7500);
      TP->set_bit(0,19);
      seteuid(getuid(TO));
      log_file(QUEST_NAME, extract(ctime(time()),4,15)+ " " +
         capitalize(TP->query_real_name()) + " rewarded with 7500 xp, "+
         "<"+TP->query_average_stat()+"> average stats.\n");
   }
   ::enter_inv(ob,from);
   set_alarm(2.0,0.0,"remove_the_object",ob);
}
void
remove_the_object(object ob)
{
   command("laugh dem");
   command("say Death to you for slaying a servant of Lolth!");
   command("exa thesummoningspellforthedrowkillers");
   command("emote vanishes into a black, choking fog.");
   if(matron = present("lualyrr",environment(TP)));
   {
      matron -> remove_object();
   }
}
void
init_living()
{
    ::init_living();
    if(interactive(TP))
        set_alarm(3.0,0.0,&command("grin "+TP->query_name()));
}

int
react_attack(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_attack",who);
      return 1;
   }
}
void
return_attack(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("say Iblith!");
      command("kill " + (obj->query_real_name()));
   }
}
void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object(CPASS(arm/piwafwi));
   arm -> move(TO);
   arm = clone_object(CPASS(arm/dw_boots));
   arm -> move(TO);
   command("wear all");
   wep = clone_object(CPASS(wep/dw_mace));
   wep -> move(TO);
   wep = clone_object(CPASS(drow/wep/h7_p1_mace));
   wep -> move(TO);
   command("grin dem");
   arm = clone_object(CPASS(drow/obj/h7_insignia));
   arm -> move(TO);
   MONEY_MAKE_PC(random(2))->move(TO,1);
   MONEY_MAKE_GC(random(10))->move(TO,1);
}
tell_watcher(string str, object enemy)
{
   object me,*ob;
   int i;
   
   me = TO;
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
   me = TO;
   
   attacktype = random(5);
   if (attacktype == 1)
      {
      
      ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });
      
      for (i = 0; i < sizeof(ob); i++)
      {
         penet = 500 + random(400);
         penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_COLD) / 50;
         hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);
         
         how = "not harmed";
         if (hitresult[0] > 0)                  
            how == "barely frozen";
         if (hitresult[0] > 10)
            how = "slightly frozen";
         if (hitresult[0] > 20)
            how = "frozen quite badly";
         if (hitresult[0] > 40)
            how = "frozen very badly";
         if (hitresult[0] > 60)
            how = "utterly frozen";
         
         ob[i]->catch_msg("You hear a rhythmic chanting and then a deadly eruption "+
            "of deathly cold shoots forth from the matron mother's hands at you!\n");
         ob[i]->catch_msg("You were " + how + " by the unnatural cold!\n");
         tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the unnatural cold!\n", ob[i]);
         
         if (ob[i]->query_hp() <= 0)
            ob[i]->do_die(me);
       }
      return 1;
   }
   
   if (attacktype == 2)
      {
      if (heal == 5)
         {
         return 0;
       }
      heal += 1;
      write("The matron mother chants a prayer to Lolth.\n"+
         "She is surrounded in a brilliance of red and now looks much better!\n");
      say("The matron mother chants a prayer to Lolth.\n"+
         "She is surrounded in a brilliance of red and now looks much better!\n");
      me->heal_hp(900);
      return 1;
   }
   return 0;
}