inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by korat */
create_monster()
{
   ::create_monster();
   set_name("ghoul");
   set_race_name("ghoul");
   set_adj("revolting");
   add_adj("human");
   set_long("The moaning, animated remains of a human graverobber "+
      "that once in time stepped in here and met his faith for both "+
      "life and death. An almost overwhelming smell of rotten flesh "+
      "and decay readiates from this being, making you want to run "+
      "away.\n");
   set_stats(({75,80,60,1,1,120}));
   set_knight_prestige(250);
   set_aggressive(1);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,25);
   set_skill(SS_AWARENESS,100);
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(LIVE_I_UNDEAD,20);
   add_prop(CONT_I_WEIGHT,100000);
   add_prop(CONT_I_VOLUME,100000);
   set_act_time(6);
   add_act("moan");
   add_act("groan");
   set_cact_time(6);
   add_cact("moan");
   add_cact("groan");
   add_leftover(CPASS(dwarf/obj/ghoul_heart), "heart",1,"",1,1);
}

tell_watcher(string str, object enemy)
{
   object me, *ob;
   int i;
   me = this_object();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i=0;i<sizeof(ob);i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string direction;
   int i;
   me = this_object();
   if (random(3)>0)
      {
      switch (random(5))
      {
         case 0: command("groan"); break;
         case 1: command("emote stares at you with a look of death."); break;
         case 2: command("emote groans: Joooin meee, joooin meee."); break;
         case 3: command("emote opens its mouth. A smell of decay and death "+
            "reaches you."); break;
         default: command("moan"); break;
       }
      return 1;
   }
   hitresult = enemy->hit_me(50 + random(100), MAGIC_DT, me, -1);
   if (hitresult[0]>0)
      {
      me->catch_msg("You touch your enemy with your decaying fingers.\n");
      enemy->catch_msg(QCTNAME(me)+" touches you with its decaying "+
         "fingers. A deadly chill runs through your body!\n");
      tell_watcher(QCTNAME(me)+" touches "+QTNAME(enemy)+" with its "+
         "decaying fingers. "+QCTNAME(enemy)+" pales visibly.\n",enemy);
      if (enemy->query_hp()<=0)
         {
         enemy->catch_msg("The touch seems to draw out the rest of your "+
            "life-energy.\n");
         tell_watcher(QCTNAME(enemy)+" starts to shake as the rest of "+
            enemy->query_possessive()+" energy of life is drawn out of "+
            "the body.\n",enemy);
         enemy->do_die(me);
         return 1;
       }
   }
   else
      {
      me->catch_msg("You tried to touch your enemy but missed.\n");
      enemy->catch_msg(QCTNAME(me)+" tries to touch you with its "+
         "decaying fingers but misses.\n");
      tell_watcher(QCTNAME(me)+" tries to touch "+QTNAME(enemy)+
         " but misses.\n",enemy);
      return 1;
   }
   return 1;
}
