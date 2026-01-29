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
   set_adj("stone");
   set_long("It is a statue of a dwarf, made of limestone. @@fighting@@\n");
   set_stats(({75,80,60,1,1,120}));
   set_gender(G_NEUTER);
   set_knight_prestige(0);
   set_aggressive(0);
   set_skill(SS_LANGUAGE,25);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,35);
   set_skill(SS_UNARM_COMBAT, 100);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_NO_CORPSE,1);
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(LIVE_I_UNDEAD,20);
   add_prop(CONT_I_WEIGHT,100000);
   add_prop(CONT_I_VOLUME,60000);
   set_attack_unarmed(A_RCLAW, 30, 30, W_BLUDGEON, 50, "right stone fist");
   set_attack_unarmed(A_LCLAW, 30, 30, W_BLUDGEON, 50, "left stone fist");
   set_all_hitloc_unarmed(({40,40,10}));
}

fighting()
{
   if(TO->query_attack())
      return "It is alive and fighting!";
   return "It stands next to one of the eastern exits.";
}


int
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("kill " + lower_case(ob->query_real_name()));
   }
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
         wep-> set_dull(wep->query_dull()+1);
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
