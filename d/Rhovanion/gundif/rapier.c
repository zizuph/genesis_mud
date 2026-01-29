inherit "/std/weapon";
 
 
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <filter_funs.h>
 
#include "/d/Rhovanion/defs.h"
 
#define RAP_HIT 41
#define RAP_PEN 58
#define RAP_MIN_SKILL 71
#define RAP_MIN_DEX 100
 
string query_longd()
{
    if(TP->query_skill(SS_WEP_SWORD)<(RAP_MIN_SKILL))
     if((TP->query_base_stat(SS_DEX))<RAP_MIN_DEX)
     {
         return "This is a slim and long rapier made of blue-grey "+
                "steel. You don't feel proficient enough to use "+
                "it properly.\n";
     }
    return "This slim rapier has got no sharp edges, but it has "+
           "an extremely sharp end; you feel that there will not "+
           "be many armours, which would be inpenetrable for this "+
           "weapon.\n";
 
}
 
void
create_weapon()
{
    set_name("rapier");
    add_name("sword");
    add_name("_pinpoint_");
    set_adj(({"slim","steel","long","blue-grey"}));
    set_short("slim steel rapier");
    set_long("@@query_longd");
 
    set_default_weapon(RAP_HIT,RAP_PEN,W_SWORD,W_IMPALE,W_ANYH,0);
    set_likely_corr(1);
    set_likely_dull(1);
    set_likely_break(3);
 
    add_prop(OBJ_I_WEIGHT,1200+random(100));
    add_prop(OBJ_I_VOLUME,1000+random(100));
    add_prop(OBJ_I_VALUE,2200+random(1000));
    set_wf(TO);
}
 
int wield()
{
  if ((TP->query_skill(SS_WEP_SWORD) < RAP_MIN_SKILL ) ||
   (TP->query_base_stat(SS_DEX) < RAP_MIN_DEX ))
  {
    set_alarm(1.0,0.0,"rapier_remove");
    TP->catch_msg("You wield the "+short()+". However, this type "+
           "of weapon is too confusing for you, and with a sigh "+
           "you unwield it again.\n");
  }
  else
  {
    write("You slip your hand in the hand guard of the "+short()+
          " and sweep it through the air with a whistling sound.\n");
    say("The air whistles as "+QCTNAME(TP)+" wields the "+short()+
        " and sweeps it through the air!\n");
  }
  return 0;
}
 
int unwield()
{
 
   if (wielder)
   {
    TP->catch_msg("You release your grip upon the "+short()+".\n");
    say(QCTNAME(wielder)+" unwields the "+short()+".\n");
    return 0;
   }
   return -1;
}
 
int rapier_remove()
{
    TP->command("unwield _pinpoint_");
    return 1;
}
 
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;
 
    me = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
 
 
public mixed did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit
,int dam)
{
  object wielder;
 
  wielder= query_wielded();
 
  if(phurt == -1)
  {
    wielder->catch_msg("You sweep the "+short()+" through the air.\n");
    enemy->catch_msg(QCTNAME(wielder)+" swings the "+short()+
                     " harmlessly through the air near you.\n");
    tell_watcher(QCTNAME(wielder)+" sweeps the "+short()+
      " at "+QTNAME(enemy)+", but misses.\n",enemy);
  }
  else if(phurt == 0)
  {
    wielder->catch_msg("You almost manage to pierce "+
    QTNAME(enemy)+" with the "+short()+".\n");
    enemy->catch_msg(QCTNAME(wielder)+" narrowly misses you "+
      "with the "+short()+".\n");
    tell_watcher(QCTNAME(wielder)+" sweeps the "+short()+
      " at "+QTNAME(enemy)+" but narrowly misses.\n",enemy);
  }
  else if(phurt<5)
  {
    wielder->catch_msg("You scratch the "+
      hdesc+" of "+QTNAME(enemy)+" with your "+short()+".\n");
    enemy->catch_msg(QCTNAME(wielder)+" manages to scratch "+
      " your "+hdesc+" with the "+short()+".\n");
    tell_watcher(QCTNAME(wielder)+" scratches "+
      "the "+hdesc+" of "+QTNAME(enemy)+" with the "+short()+
      ".\n",enemy);
  }
  else if(phurt<10)
  {
    wielder->catch_msg("You prick the "+
      hdesc+" of "+QCTNAME(enemy)+" with the "+short()+".\n");
    enemy->catch_msg("A small drop of blood appears as the "+short()+
      " pricks your "+hdesc+".\n");
    tell_watcher(QCTNAME(wielder)+" pricks the "+
      hdesc+" of "+QTNAME(enemy)+" with the "+
      short()+".\n",enemy);
  }
  else if(phurt<20)
  {
    wielder->catch_msg("Your "+short()+" punctures "+
      "the "+hdesc+" of "+QTNAME(enemy)+", causing a trail "+
      "of blood to appear on it.\n");
    enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+
      " punctures your "+hdesc+", starting a narrow blood trail.\n");
    tell_watcher(QCTNAME(wielder)+"'s "+short()+" punctures "+
      "the "+hdesc+" of "+QTNAME(enemy)+". A small trail of blood "+
      "runs down it.\n",enemy);
  }
  else if(phurt<40)
  {
    wielder->catch_msg("Your "+short()+" pierces into the "+
    hdesc+" of "+QTNAME(enemy)+", tearing a nasty looking wound.\n");
    enemy->catch_msg("Your "+hdesc+" starts bleeding as the "+
      short()+" of "+QTNAME(wielder)+" pierces it.\n");
    tell_watcher(QCTNAME(wielder)+" pierces the "+
      hdesc+" of "+QTNAME(enemy)+" with "+HIS(wielder)+" "+
      short()+" causing a nasty looking wound to open.\n",enemy);
  }
  else if(phurt<60)
  {
    wielder->catch_msg("The blood pours out heavily of the "+
      hdesc+" of "+QTNAME(enemy)+" as the end of your "+short()+
      " impales it.\n");
    enemy->catch_msg(QCTNAME(wielder)+" impales "+
      " your "+hdesc+" with the end of "+HIS(wielder)+
      " "+short()+" causing blood to pour out heavily.\n");
    tell_watcher(QCTNAME(wielder)+" impales "+
      "the "+hdesc+" of "+QTNAME(enemy)+" with the sharp end of the "+
      short()+" causing blood to pour out heavily.\n",enemy);
  }
  else if(phurt<80)
  {
    wielder->catch_msg("Your "+short()+" dives deep into "+
      " the "+hdesc+" of "+QTNAME(enemy)+", causing a fountain of "+
      "blood to splash everything in surroundings.\n");
    enemy->catch_msg(QCTNAME(wielder)+" dives deep "+
      "into your "+hdesc+" with "+HIS(wielder)+" "+short()+
      ". Fountains of blood from your wound splashes the "+
      "surroundings.\n");
    tell_watcher(QCTNAME(wielder)+" dives deep "+
      "into the "+hdesc+" of "+QTNAME(enemy)+" with the "+
      short()+", causing a fountain of blood to splash the "+
      "surroundings.\n",enemy);
  }
  else
  {
    wielder->catch_msg("You pierce completely through the "+
     hdesc+" of "+QTNAME(enemy)+" with a powerful thrust of "+
     "your "+short()+", making "+HIM(enemy)+
     " gasp in pain.\n");
    enemy->catch_msg("You gasp in pain, as "+
     QCTNAME(wielder)+"completlely pierces your "+hdesc+" with "+
     "a powerful thrust of "+HIS(wielder)+" "+short()+".\n");
    tell_watcher(QCTNAME(enemy)+" gasps in pain, as "+
     QTNAME(wielder)+" pierces completely through the "+hdesc+
     " of "+
     QTNAME(enemy)+" with a powerful strike of "+HIS(wielder)+
     " "+short()+".\n",enemy);
  }
  return 1;
}
 
query_recover()  { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
