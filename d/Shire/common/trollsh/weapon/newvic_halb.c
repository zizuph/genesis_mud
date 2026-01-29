/*
 *	Removed the tellem and replaced them.
 *      Igneous Sept, 12/96
 */

inherit "/std/weapon";

#include <filter_funs.h>
#include <options.h>
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>

void
create_weapon()
{
   set_name("halberd");
   set_short("cruel black halberd");
   set_pshort("cruel black halberds");
   set_adj(({"cruel","troll","black"}));
   set_long("This is a nasty wicked polearm, made by the trolls of the "
      +"trollshaws. It has a long shaft made by black steel. The "
      +"shaft is almost 4 feet long and has one axe head and "
      +"one spear head. The weapon itself is heavy and the blades "
      +"on it are very sharp. On the back you can see a large hook "
      +"connected to it.\n");
   set_hit(34);
   set_pen(40);
   set_wf(TO);
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE | W_BLUDGEON);
   add_item(({"head","heads"}),
      "The halberd has two heads, one axe and one spear head. "
      +"It looks vicious, both blades are as sharp as they can be and "
      +"the halberd looks like it could cut through anything.\n");
   add_item("hook","The hook is sharp and has rusty edges.\n");
   
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(29, W_POLEARM));
   add_prop(OBJ_I_VOLUME, 14000);
   add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(26,39) + random(140));
   
}

int
query_usable(object who)
{
   return (who->query_skill(SS_WEP_POLEARM)>55 ||
      STR(who) > 70);
}

int
query_hands()
{
   if(!TP)
      return W_BOTH;
   else if(STR(TP) > 120)
      {
      set_hit(34);
      set_pen(40);
      return W_BOTH;
   }
   else
      return W_BOTH;
}

int
wield(object to)
{   
   if(!query_usable(TP))
      {
      write("You desperatly try to wield the halberd, but you realize that "+
         "you are too weak.\n");
      say(QCTNAME(TP)+" tries to wield the halberd, but is not "+
         "strong enough.\n");
      return -1;
   }
   else 
      write("You skillfully wield the halberd "+
      (query_hands()==W_BOTH? "twohanded.\n" : "single handed.\n"));
   return 1;
}

int 
unwield()
{
   return 0;
}

/*
 *  Ruthlessly stolen from /std/combat/cbase
 */
varargs void
tell_watcher(string str, object enemy, mixed arr)
{
   object me = query_wielded();
   object *ob;
   int i, size;
   
   ob = all_inventory(environment(me)) - ({ me, enemy });
   
   if (arr)
      {
      if (pointerp(arr))
         ob -= arr;
      else
         ob -= ({ arr });
   }
   
   /* We only display combat messages to interactive players. */
   ob = FILTER_PLAYERS(ob);
   
   i = -1;
   size = sizeof(ob);
   while(++i < size)
   {
      if (!ob[i]->query_option(OPT_BLOOD) && CAN_SEE_IN_ROOM(ob[i]))
         {
         if (CAN_SEE(ob[i], me))
            ob[i]->catch_msg(str);
         else
            tell_object(ob[i], enemy->query_The_name(ob[i]) +
            " is hit by someone.\n");
         }
   }
}

public mixed
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
   object tp;
   string matter;
   
   tp = query_wielded();
   if(!query_usable(tp))
      {   
      write("You can not use this weapon properly.\n"); 
      return 0;
   }
   
   if (phurt == -1 || phurt == -2)
      {
      tp->catch_msg("You swing your "+short()+" punching nothing but "+
         "thin air.\n");
      enemy->catch_msg(QCTNAME(tp)+" swings "+HIS_HER(tp)+" "+short()+" at "+
         "you, punching nothing but thin air.\n");
      tell_watcher(QCTNAME(tp)+" swings "+HIS_HER(tp)+" "+short()+
         " punching nothing but thin air.\n",enemy);
      return 1;
   }
   else if (phurt == 0)
      {
      tp->catch_msg("You swing your "+short()+" dangerously close "+
         "to "+QTNAME(enemy)+"'s "+hdesc+".\n");
      enemy->catch_msg(QCTNAME(tp)+" swings "+HIS_HER(tp)+" "+short()+
         " dangerously close to your "+hdesc+".\n");
      tell_watcher(QCTNAME(tp)+" swings "+HIS_HER(tp)+" "+short()+
         " dangerously close to "+QTNAME(tp)+"'s "+hdesc+".\n",enemy);
      return 1;
   }    
   else if(phurt < 5)
      {
      tp->catch_msg("You nicely touch "+QTNAME(enemy)+"'s "+hdesc+
         " with your "+short()+".\n");
      enemy->catch_msg(QCTNAME(tp)+" nicely touches your "+hdesc+" with "+
         HIS_HER(tp)+" "+short()+".\n");
      tell_watcher(QCTNAME(tp)+" nicely touches "+QTNAME(enemy)+"'s "+
         hdesc+" with "+HIS_HER(tp)+" "+short()+".\n",enemy);
      return 1;
   }
   else if(phurt <10)
      {
      tp->catch_msg("You cut "+QTNAME(enemy)+"'s "+hdesc+" with your "+
         short()+".\n");
      enemy->catch_msg(QCTNAME(tp)+" cut your "+hdesc+" with "+HIS_HER(tp)+
         " "+short()+".\n");
      tell_watcher(QCTNAME(tp)+" cut "+QTNAME(enemy)+"'s "+hdesc+
         " with "+HIS_HER(tp)+" "+short()+".\n",enemy);
      return 1;
   }
   else if(phurt<25)
      {
      tp->catch_msg("You make a nice flesh wound on "+QTNAME(enemy)+
         "'s "+hdesc+" with your "+short()+".\n");
      enemy->catch_msg(QCTNAME(tp)+" makes a nice flesh wound on your "+
         hdesc+" with "+HIS_HER(tp)+" "+short()+".\n");
      tell_watcher(QCTNAME(tp)+" makes a nice flesh wound on "+QTNAME(enemy)+
         "'s "+hdesc+" with "+HIS_HER(tp)+" "+short()+".\n",enemy);
      return 1;
   }   
   else if(phurt<50)
      {
      tp->catch_msg("Your "+short()+" hits "+QTNAME(enemy)+" hard in the "+
         hdesc+".\n");
      enemy->catch_msg(QCTNAME(tp)+"'s "+short()+" hits you hard in "+
         "the "+hdesc+".\n");
      tell_watcher(QCTNAME(tp)+"'s "+short()+" hits "+QTNAME(enemy)+
         " hard in the "+hdesc+".\n",enemy);
      return 1;
   }
   else if(phurt<75)
      {
      tp->catch_msg("You schmack your "+short()+" into "+QTNAME(enemy)+
         "'s "+hdesc+" with a breathtaking hit.\n");
      enemy->catch_msg(QCTNAME(tp)+" schmacks "+HIS_HER(tp)+" "+short()+
         " into your "+hdesc+" with a breathtaking hit.\n");
      tell_watcher(QCTNAME(tp)+" schmacks "+HIS_HER(tp)+" "+short()+
         "into "+QTNAME(enemy)+"'s "+hdesc+" with a breathtaking "+
         "hit.\n",enemy);
      return 1;
   }
   
   
   if (enemy->query_hp() <= 0)
      {
      switch (hdesc)
      {
         case "head":
         matter = "brains";
         break;
         case "body":
         matter = "guts";
         break;
         default:
         matter = "blood";
         break;
       }
      tp->catch_msg("You swing your "+short()+" into "+QTNAME(enemy)+
         "'s "+hdesc+" with a powerful strike!\n"+CAP(matter)+" splashes "+
         "right onto your face!!\n"+QCTNAME(enemy)+" is cast several feet "+
         "in the air by your massacring hit!!!\n"+CAP(matter)+" pour out "+
         HIS_HER(enemy)+" "+hdesc+" as "+HE_SHE(enemy)+" falls flat to "+
         "the ground.\n");
      tp->command("cackle");   
      
      enemy->catch_msg(QCTNAME(tp)+" swings "+HIS_HER(tp)+" "+short()+
         " right into your "+hdesc+" with a powerful strike!\nYou silently "+
         "watch "+matter+" from your "+hdesc+" splash right onto "+HIS_HER(tp)+
         "face.\nYou are cast several feet up in the air by the massacrating "+
         "hit!\n"+CAP(matter)+" pour out from your "+hdesc+" as you "+
         "fall flat on the ground.\n");
      enemy->command("scream");
      
      tell_watcher(QCTNAME(tp)+" swings "+HIS_HER(tp)+" "+short()+
         " powerfully into "+QCTNAME(enemy)+" "+hdesc+"!\n"+
         CAP(matter)+" splashes right onto "+QCTNAME(tp)+"'s face.\n"+
         QCTNAME(enemy)+" is cast several feet up in the air by "+
         QTNAME(tp)+"'s s massacring strike!\n"+
         CAP(matter)+" pour out from "+QTNAME(enemy)+" "+hdesc+
         " as "+HE_SHE(enemy)+" falls flat to the ground!\n",enemy);
      enemy->do_die(tp);
      return 1;
   }
   
}
