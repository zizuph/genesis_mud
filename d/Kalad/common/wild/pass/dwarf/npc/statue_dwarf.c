inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
#include <ss_types.h>
#define A_LCLAW 1
#define A_RCLAW 2
#define H_BODY 0
/* by korat */
create_monster()
{
   ::create_monster();
   set_name("statue");
   set_race_name("statue");
   set_adj("large");
   add_adj("marble");
   set_long("It is a statue of pure marble that almost reaches the roof. "+
      "A mighty work of art! @@attacking@@\n");
   set_stats(({160,160,160,50,50,160}));
   set_gender(G_NEUTER);
   set_knight_prestige(0);
   set_aggressive(0);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_AWARENESS,100);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(LIVE_I_UNDEAD,20);
   add_prop(CONT_I_WEIGHT, 2000000);
   add_prop(CONT_I_VOLUME,60000);
   add_prop(LIVE_I_NO_CORPSE,1);
   set_all_hitloc_unarmed(({80,80,40}));
   set_attack_unarmed(A_RCLAW, 80, 80, W_SLASH, 100, "marble longsword");
}

string
attacking()
{
   if(TO->query_attack())
      return "It is alive and fighting!";
   return "It stands in front of the eastern exit as if protecting it.";
}

int
special_attack(object enemy)
{
   object me, co;
   object plex;
   string msg;
   mixed* hitresult;
   int i;
   int stun;
   object *ob;

   me = this_object();
   co = enemy->query_combat_object();

   if (random(5)>0)
      {
      return 0;
   }
   me->catch_msg("You call for a blanket of fright.\n");
   hitresult = enemy->hit_me(200 + random(400), MAGIC_DT, me, -1);
   enemy->catch_msg(QCTNAME(me)+" lifts its arms up in the air. "+
      "A sudden darkness penetrates your mind ... \n");
   tell_watcher(QCTNAME(me)+" lifts its arms up in the air, while "+
      "staring intensely at "+QTNAME(enemy)+".\n",enemy);

   switch (random(6))
   {
      case 0: msg="You suddenly feel your skin starting to melt!\n"; break;
      case 1: msg="A terrifying flame envelopes you. The smell of "+
      "your flesh burning is horrifying!\n"; break;
      case 2: msg="The statue turns in front of your eyes into "+
      "a fleshless image of ... yourself!\n"; break;
      case 3: msg="You feel yourself slowly getting heavier and heavier, "+
      "and soon you stand motionless.\n"; break;
      case 4: msg="Your arms turns into two vicious snakes with salvia "+
      "dripping from their fangs. They attack you!\n"; break;
      case 5: msg="A bottomless pit opens in front of you ... you "+
      "start to fall!\n"; break;
      default: break;
   }

   switch (hitresult[0])
   {
      case 0..4:
      enemy->catch_msg("You manage to fight the frightening pictures "+
         "off.\n");
      break;
      case 5..100:
      enemy->catch_msg(msg);
      enemy->command("scream");
      co->cb_add_panic(hitresult[0]*20);
      break;
      default: break;
   }
   if (hitresult[0]>4)
      {
      ob = all_inventory(enemy);
      stun = 0;
      for (i=0;i<sizeof(ob);i++)
      if (ob[i]->query_name()=="stun") stun=1;
      if(!stun && random(enemy->query_base_stat(SS_DIS))<100)
         {
         plex = clone_object(CPASS(dwarf/obj/stun_object));
         plex->set_remove_time(random(30)+30);
         plex->move(enemy);
         enemy->catch_msg("It was just a ima...NO!! Its real! "+
            "Your body freezes up in pure fright!\n");
       }
      else
         {
         enemy->catch_msg("The horrifying image fades slowly away, "+
            "leaving you wondering if it really happened or not ...\n");
       }
   }
   if (enemy->query_hp()<=0)
      {
      enemy->catch_msg("The image scares you until your body cannot "+
         "manage it anymore. You die in horrifying pains...\n");
      tell_watcher(QCTNAME(enemy)+"'s eyes are wide open in "+
         "utter fright!\n",enemy);
      enemy->do_die(me);
      return 1;
   }
   return 1;
}

void
cr_got_hit(int hid, int ph, object att, int dt, int dam)
{
   object wep;
   string str, str2;
   int type = 0;
   if(ph<1) return;
   switch(dt)
   {
      case W_LEFT: wep = att->query_weapon(W_LEFT); break;
      case W_RIGHT: wep = att->query_weapon(W_RIGHT); break;
      case W_BOTH: wep = att->query_weapon(W_BOTH); break;
      default: break;
   }
   type=W_BLUDGEON;
   if(objectp(wep))
      type = wep->query_dt();
   if(type == W_SLASH || type == W_IMPALE || type == (W_SLASH | W_IMPALE))
      {
      if(!objectp(wep)) return;
      if(!wep->query_prop(OBJ_I_IS_MAGIC_WEAPON))
         wep -> set_dull(wep->query_dull()+1);
      att->catch_msg("Your "+wep->query_short()+" hits the statue "+
         "with a loud 'tooinggg'.\n");
      tell_room(E(TO),QCTNAME(att)+"'s "+wep->query_short()+
         " hits the statue"+
         " with a loud 'tooing'.\n",att);
      return;
   }
   if(type == W_BLUDGEON || type == (W_BLUDGEON | W_SLASH) ||
         type ==  (W_BLUDGEON | W_IMPALE))
   {
      if(ph<1) return;
      switch (ph)
      {
         case 1..4:
         str = "Your attack almost bounces off the statue.\n";
         str2 = "The attack of "+QTNAME(att)+" almost bounches off the statue.\n";
         break;
         case 5..9:
         str = "Small cracks starts to show on the statue.\n";
         str2 = "Small cracks starts to show on the statue.\n";
         break;
         case 10..15:
         str = "Pieces of rock are hit loose from your blow.\n";
         str2 = "Pieces of rock are hit loose from "+QTNAME(att)+"'s blow.\n";
         break;
         case 16..20:
         str = "Chunks of rock falls on the floor from your "+
         "excellent blow.\n";
         str2 = "Chunks of rock falls on the floor from "+QTNAME(att)+"'s blow.\n";
         break;
         case 21..30:
         str = "A loud crash echoes in the temple as you hit the statue.\n";
         str2 = "A load crash echoes in the temple as "+QTNAME(att)+
         " hits the statue.\n";
         break;
         default:
         str = "The statue almost crumbles from your crushing hit.\n";
         str2 = "The statue almost crumbles from "+QTNAME(att)+
         "'s hit.\n";
         break;
      }
      att->catch_msg(str);
      tell_room(E(TO),str2,att);
      return;
   }
   return;
}

do_die(object killer)
{
   if (TO->query_hp()>0) return;
   tell_room(E(TO),"The statue shatters into hundreds of small pieces, as "+
      QTNAME(killer)+" crushed it with with an excellent hit.\n",killer);
   killer->catch_msg("The statue shatters into hundreds of small pieces, as "+
      "you crushed it with an excellent hit.\n");
   ::do_die(killer);
}
