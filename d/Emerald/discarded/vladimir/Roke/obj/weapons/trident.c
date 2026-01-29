inherit "/std/weapon";

#include <filter_funs.h>
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
   set_name("trident");
   add_name("trident_for_sharkquest");
   set_short("gigantic trident");
   set_long("This is the largest weapon you have EVER seen in"+
      " your life. You could easily skewer a horse with it. The"+
      " three sharp prongs on the end are crafted out of the"+
      " finest platinum and are glowing white hot.\n"); 
   set_adj("gigantic");
   set_hit(35);
   set_pen(54);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   set_hands(W_BOTH);
   set_wf(TO);
   
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,54) + 2000);
   add_prop(OBJ_I_WEIGHT, 28000);
   add_prop(OBJ_I_VOLUME, 8000);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_MAGIC,({46, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO,({"It is enchanted to only allow "+
            "a certain quality of person to wield it.",10,
            "The user must have great strength and skill to wield it. "+
            "It is also especially effective against a certain type "+
            "of foe.",25,
            "The user must have the strength of a titanic hero and the "+
            "skill of a master journeyman to wield this "+
            "magnificent weapon of human slaying.",50}));
   add_prop(OBJ_S_WIZINFO,({"The user must have a 120 str and a 50"+
            " polearm to wield. It does 2 times damage to humans. "+
            "It is found on the monster: /d/Roke/Athas/npc/gladiator.c"}));
}

varargs void
tell_watcher(string str, object enemy, mixed arr)
{
   object *ob;
   int i;
   object me = TP;
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({me});
   ob -= ({enemy});
   
   if (arr)
      {
      if (pointerp(arr))
         ob -= arr;
      else
         ob -= ({arr});
   }
   
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->query_see_blood() && CAN_SEE_IN_ROOM(ob[i]))
      {
      if (CAN_SEE(ob[i], me))
         ob[i]->catch_msg(str);
      else
         ob[i]->catch_msg(QCTNAME(enemy)+" is hit by someone.\n");
   }
}


int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
   int phit, int dam)
{
   object me = TP;
   
   if(enemy->query_race_name() != "human") return 0;
   {
      enemy->heal_hp(-dam);
      
      if(enemy->query_hp()<=0)
         {
         enemy->do_die();
         me->catch_msg("You bulldoze a new body cavity right into the "+
            "center of "+QTNAME(enemy)+" with your Allmighty Trident of "+
            "Absolute Power and Dominance Over The World.\n");
         tell_watcher(QCTNAME(me)+" bulldozes a new body cavity right "+
            "into the center of "+QTNAME(enemy)+" with "+
            me->query_possessive()+" allmighty trident.\n");
         return 1;
      }
      
      if(phurt == -1)
         {
         me->catch_msg("Your gigantic trident crackles in the air, just "+
            "barely missing "+QTNAME(enemy)+".\n");
         enemy->catch_msg(QCTNAME(me)+"'s gigantic trident crackles in "+
            "the air as you barely manage to escape his blow.\n");
         tell_watcher(QCTNAME(me)+"'s gigantic trident crackles in the "+
            "air just as it misses "+QTNAME(enemy)+".\n");
      }
      
      switch (phurt)
      {
         
         case 0..4:
         me->catch_msg("You score a searing flesh wound on "+
            QTNAME(enemy)+" with your gigantic trident.\n");
         enemy->catch_msg(QTNAME(me)+"scores a searing flesh wound on you "+
            "with "+me->query_possessive()+" gigantic trident.\n");
         tell_watcher(QTNAME(me)+" scores a searing flesh wound on "+
            QTNAME(enemy)+" with "+me->query_possessive()+" gigantic "+
            "trident.\n");
         break;
         
         case 5..9:
         me->catch_msg("You cut a nasty slit in "+QTNAME(enemy)+"'s side "+
            "with "+me->query_possessive()+" gigantic trident.\n");
         enemy->catch_msg(QCTNAME(me)+" cuts a painfil slit in your side "+
            "with "+me->query_possessive()+" gigantic trident.\n");
         tell_watcher(QCTNAME(me)+ "cuts a small slit in "+QTNAME(enemy)+
            "'s side with "+me->query_possessive()+" gigantic trident.\n");
         break;
         
         case 10..19:
         me->catch_msg("You hear the prongs of your glowing trident "+
            "vibrate rapidly as they cut deeply into "+QTNAME(enemy)+".\n");
         enemy->catch_msg("You feel the prongs of "+QTNAME(me)+"'s "+
            "horrible trident vibrate rapidly as they cut deeply into you.\n");
         tell_watcher("You hear the prongs of "+QTNAME(me)+"'s glowing "+
            "trident vibrate rapidly as they cut deeply into "+
            QTNAME(enemy)+".\n");
         break;
         
         case 20..29:
         me->catch_msg("Your vibrating trident screams with delight as it "+
            "tears a burning gash on "+QTNAME(enemy)+"'s forehead.\n");
         tell_watcher(QTNAME(me)+"'s vibrating trident screams with "+
            "delight as it tears a burning gash on "+QTNAME(enemy)+"'s "+
            "forehead.\n");
         enemy->catch_msg(QCTNAME(me)+"'s wicked trident screams a sour "+
            "note of delight as it tears a burning gash on your forehead.\n");
         break;
         
         case 30..49:
         me->catch_msg("Your white hot trident comes to life and burrows "+
            "far within "+QTNAME(enemy)+"'s body.\n");
         enemy->catch_msg(QCTNAME(me)+"'s nasty trident comes to life and "+
            "burrows far within your body.\n");
         tell_watcher(QCTNAME(me)+"'s white hot trident comes to life and "+
            "burrows far within "+QTNAME(enemy)+"'s body.\n");
         break;
         
         case 50..69:
         me->catch_msg("You adeptly thrust your wonderful trident through "+
            QTNAME(enemy)+"'s flesh like a hot knife through butter.\n");
         enemy->catch_msg(QCTNAME(me)+" adeptly thrusts "+
            me->query_possessive()+" wretched trident through your flesh like "+
            "a hot knife through butter.\n");
         tell_watcher(QCTNAME(me)+" adeptly thrusts "+me->query_possessive()+
            " wonderful trident through "+QTNAME(enemy)+"'s flesh like a "+
            "hot knife through butter.\n");
         break;
         
         case 70..89:
         me->catch_msg(QCTNAME(enemy)+" cries out in anguish as your "+
            "favourite trident is rammed through his body very hard.\n");
         enemy->catch_msg("You scream out in anguish as "+QTNAME(me)+
            "'s despicable trident is rammed through your body very "+
            "hard.\n");
         tell_watcher(QCTNAME(enemy)+"cries out in anguish as "+
            QTNAME(me)+"'s favourite trident is rammed through "+
            QTNAME(enemy)+"'s body quite hard.\n");
         break;
         
         default:
         me->catch_msg("You lovingly skewer "+QTNAME(enemy)+" on the "+
            "end of your absolutely glorious trident.\n");
         enemy->catch_msg(QCTNAME(me)+" heartlessly skewers you on the "+
            "end of "+me->query_possessive()+" stupid, scum-sucking, trashy "+
            "boot-licking, piece of garbage, no good, pain-in-the-butt "+
            "trident.\n");
         tell_watcher(QCTNAME(me)+" heartlessly skewers "+QTNAME(enemy)+
            " on the end of "+me->query_possessive()+" ever-so-handy "+
            "trident.\n");
         break; 
      }
   }
   return 0;
}

mixed
wield(object ob)
{
   if(ob!=TO)
      return 0;
   
   if(TP->query_alignment() < 750 && TP->query_alignment() > -750)
      if(TP->query_base_stat(SS_STR)>119)
      if(TP->query_skill(SS_WEP_POLEARM)>49)
      {
      write("You easily wield the huge weapon.\n");
      return 0;
   }
   
   TP->heal_hp(-random(50)-20);
   return"The trident becomes hot and burns your hands!\n";
}


query_recover()
{
   return MASTER+":"+query_wep_recover();
}
init_recover(arg)
{
   init_wep_recover(arg);
}
