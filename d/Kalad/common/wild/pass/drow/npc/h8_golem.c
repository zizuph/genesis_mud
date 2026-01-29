inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
int heal;
create_monster()
{
   int i;
   set_name("golem");
   add_name("statue");
   set_short("obsidian statue");
   set_race_name("golem");
   set_adj("obsidian");
   set_gender(G_NEUTER);
   set_long("A towering suit of obsidian plate armour. It stands nearly eight "+
      "feet in height and though the armour is very ornate, it still appears "+
      "to be of near mint condition. The statue must weigh an incredible "+
      "amount. You cannot be sure, but it appears as if a faint green glow "+
      "is emanating from beneath its helm.\n");
   for (i = 0; i < 3; i++)
   set_base_stat(i, 75 + random(50));
   set_base_stat(3, 25);
   set_base_stat(4, 25);
   set_base_stat(5, 100);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_AWARENESS,100);
   set_skill(SS_SPELLCRAFT,60);
   set_knight_prestige(1000);
   set_attack_unarmed(0, 45, 45, W_BLUDGEON, 30, "right obsidian gauntlet");
   set_attack_unarmed(1, 45, 45, W_BLUDGEON, 30, "left obsidian gauntlet");
   set_attack_unarmed(2, 40, 40, W_BLUDGEON, 20, "right obsidian boot");
   set_attack_unarmed(3, 40, 40, W_BLUDGEON, 20, "left obsidian boot");
   set_hitloc_unarmed(1, 70, 15, "obsidian helmet");
   set_hitloc_unarmed(2, 65, 10, "right obsidian gauntlet");
   set_hitloc_unarmed(3, 65, 10, "left obsidian gauntlet");
   set_hitloc_unarmed(4, 95, 45, "obsidian plate armour");
   set_hitloc_unarmed(5, 85, 20, "obsidian greaves");
   add_prop(LIVE_I_SEE_DARK, 1000);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(CONT_I_WEIGHT,2000000);
   add_prop(CONT_I_VOLUME,2000000);
   add_prop(LIVE_I_NO_CORPSE,1);
   trig_new("%w 'leaves' 'the' 'ranks' %s","react_attack");
}
int 
react_attack(string who)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(1.0,0.0,"return_attack",who);
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
      command("emote animates and moves to the attack!");
      command("kill " + (obj->query_real_name()));
   }
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
   me = TO;
   attacktype = random(5);
   if (attacktype == 1)
      {
      ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });
      
      for (i = 0; i < sizeof(ob); i++)
      {
         penet = 400 + random(200);
         penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_ACID) / 50;
         hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);
         
         how = "not harmed";
         if (hitresult[0] > 0)                  
            how == "barely burned";
         if (hitresult[0] > 10)
            how = "slightly burned";
         if (hitresult[0] > 20)
            how = "burned quite badly";
         if (hitresult[0] > 40)
            how = "burned very badly";
         if (hitresult[0] > 60)
            how = "utterly devastated";
         ob[i]->catch_msg("The obsidian golem opens its mouth and without warning "+
            "an acidic cloud emerges and blankets the room!\n");
         ob[i]->catch_msg("You were " + how + " by the obsidian golem's acidic cloud!\n");
         tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the obsidian golem's acidic cloud!\n", ob[i]);
         
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
      write("The obsidian golem suddenly attracts the bits and pieces "+
         "of itself chipped away during battle!\n");
      say("The obsidian golem suddenly attracts the bits and pieces "+
         "of itself chipped away during battle!\n");
      me->heal_hp(1000);
      return 1;
   }
   
   return 0;
}
do_die(object killer)
{
   object corpse;
   if (query_hp() > 0) return;
   
   corpse = clone_object(CPASS(drow/obj/rubble));
   corpse->move(environment(TO));
   
   ::do_die(killer);
}
