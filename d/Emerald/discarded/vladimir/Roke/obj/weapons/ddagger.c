/* This weapon is styled after Aridor's Draconian Claymore, and  */
/* modified to adjust to a dagger Vladimir 8-18-94 */
   inherit "/std/weapon";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"




create_weapon()
{
   set_name("peace maker");
   add_name("maker");
  set_pname("peace makers");
   add_name("dagger");
   set_adj("viscious");
   add_adj("midnight-black");
   set_long("@@my_long");
   set_default_weapon(36, 38, W_KNIFE, W_SLASH | W_IMPALE, W_RIGHT);

   set_wf(TO);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_S_WIZINFO,"This is a very potent dagger. It is very light "+
      "and strong. It has magic in that allows it a high hit and "+
      "penetration. It was made especially for the town marshal to "+
      "keep the town in order.\n");

   add_prop(MAGIC_AM_ID_INFO,({"This weapon is magical and potent\n", 5,
            "You feel a strong will emanating from " +
            "the dagger that you must overcome.\n", 25,
            "The weapon's balance is subject to the magic, "+
            "allowing better wieldability and very high hit rate.\n", 51}));
   add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
   add_prop(OBJ_I_VOLUME, 2500);
   add_prop(OBJ_I_WEIGHT, 3900);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(36,38) + 1200);
}

string
query_recover()

{
   return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
   init_wep_recover(arg);
}


my_long()
{
   return "This dagger is long and viscious. The blade is midnight black. "+
   "The hilt is made from soft leather that is died green wrapped "+
   "around metal. On the very bottom of the weapon is a symbol of two "+
   "crossed axes over a map of the world.\n";


}




mixed
wield(object what)
{
   if (this_player()->query_skill(SS_WEP_KNIFE) > 80)
   if (TP->query_base_stat(SS_DIS) > 80)
   if (TP->query_base_stat(SS_DEX) > 80)
      {
      write("You feel a slight tinge of fear as you grip this magnificent "+
         "weapon. You manage to overcome it and take hold of it's power.\n");
      return 0;
   }
   TP->add_mana(-random(50)-10);
   return "As you try to take hold of the dagger, an overpowering feel " +
   "of terror rips through your mind and body. You are unable to wield "+
   "the dagger.\n";
}

mixed
unwield(object what)
{
   return 0;
}

 

public mixed did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int
phit,int dam)
{
  object wielder = query_wielded();
  switch(phurt)
  {
    case -1:
      query_wielded()->catch_msg("You swing the "+short()+" harmlessly "+
        "through the air.\n");
      enemy->catch_msg(QCTNAME(query_wielded())+" swings the "+short()+
        " harmlessly through the space near you.\n");
      tell_watcher(QCTNAME(query_wielded())+" swings the "+short()+
        " at "+QTNAME(enemy)+", but misses.\n",enemy);
      break;
    case 0:
      query_wielded()->catch_msg("You narrowly miss "+QTNAME(enemy)+
        " with the "+short()+".\n");
      enemy->catch_msg(QCTNAME(query_wielded())+" narrowly misses you "+
        "with the "+short()+".\n");
      tell_watcher(QCTNAME(query_wielded())+" swings the "+short()+
        " at "+QTNAME(enemy)+" and narrowly misses.\n",enemy);
      break;
    case 1..5:
      query_wielded()->catch_msg("You tear a shallow wound into the "+
        hdesc+" of the "+enemy->query_race_name()+" with "+
        "the "+short()+".\n");
      enemy->catch_msg("You feel a fresh wound open on your "+hdesc+
        " as the "+short()+" tears into you.\n");
      tell_watcher(QCTNAME(query_wielded())+" tears a shallow wound "+
        "into the "+hdesc+" of "+QTNAME(enemy)+" with the "+short()+
        ".\n",enemy);
      break;
    case 6..10:
      query_wielded()->catch_msg("You tear small chunks of flesh out "+
        "of the "+hdesc+" of the "+enemy->query_race_name()+
        " with the "+short()+".\n");
      enemy->catch_msg("You lose small chucks of flesh as the "+short()+
        " tears into your "+hdesc+".\n");
      tell_watcher(QCTNAME(query_wielded())+" tears small chunks of "+
        "flesh out of the "+hdesc+" of "+QTNAME(enemy)+" with the "+
        short()+".\n",enemy);
      break;
    case 11..20:
      query_wielded()->catch_msg("Your "+short()+" rips into the "+hdesc+
        " of "+QTNAME(enemy)+", shredding flesh as it goes.\n");
      enemy->catch_msg("The flesh of your "+hdesc+" is shredded as the "+
        short()+" rips into it.\n");
      tell_watcher(QCTNAME(query_wielded())+" shreds the flesh on "+
        "the "+hdesc+" of "+QTNAME(enemy)+" with "+
        HIS_HER(query_wielded())+" "+short()+".\n",enemy);
      break;
    case 21..40:
      query_wielded()->catch_msg("Your "+short()+" tears a deep wound "+
        "into the "+hdesc+" of the "+enemy->query_race_name()+".\n");
      enemy->catch_msg(QCTNAME(query_wielded())+" tears a deep "+
        "wound into your "+hdesc+" with "+HIS_HER(query_wielded())+
        " "+short()+".\n");
      tell_watcher(QCTNAME(query_wielded())+" tears a deep wound into "+
        "the "+hdesc+" of "+QTNAME(enemy)+" with the "+short()+
        ".\n",enemy);
      break;
    case 41..60:
      query_wielded()->catch_msg("Your "+short()+" tears large "+
        "chunks of flesh from the "+hdesc+" of the "+
        enemy->query_race_name()+".\n");
      enemy->catch_msg(QCTNAME(query_wielded())+" tears large chunks of "+
        "flesh from your "+hdesc+" with "+HIS_HER(query_wielded())+
        " "+short()+".\n");
      tell_watcher(QCTNAME(query_wielded())+" tears large chunks of "+
        "flesh from the "+hdesc+" of "+QTNAME(enemy)+" with the "+
        short()+".\n",enemy);
      break;
    case 61..80:
      query_wielded()->catch_msg("Your "+short()+" leaves nothing but "+
        "ribbons of flesh hanging from the "+hdesc+" of "+
        "the "+enemy->query_race_name()+".\n");
      enemy->catch_msg(QCTNAME(query_wielded())+" reduces the "+
        "flesh of your "+hdesc+" to mere ribbons with "+
        HIS_HER(query_wielded())+" "+short()+".\n");
      tell_watcher(QCTNAME(query_wielded())+" reduces the flesh "+
        "of the "+hdesc+" of "+QTNAME(enemy)+" to ribbons with the "+
        short()+".\n",enemy);
      break;
    case 81..90:
      query_wielded()->catch_msg("Your "+short()+" almost tore "+
        "through the "+hdesc+" of the "+enemy->query_race_name()+".\n");
      enemy->catch_msg("The "+short()+" almost tore right through "+
        "your "+hdesc+".\n");
 
      tell_watcher("The "+short()+" wielded by "+QTNAME(query_wielded())+
        " almost tore through the "+hdesc+" of "+QTNAME(enemy)+
        ".\n",enemy);
      break;
    default:
      query_wielded()->catch_msg("Shards of bone fly everywhere as "+
       "your "+short()+" completely destroys the "+hdesc+" of the "+
        enemy->query_race_name()+".\n");
      enemy->catch_msg("Your "+hdesc+" shatters when the "+short()+
        " bites into it, sending splinters of bone flying everywhere.\n");
      tell_watcher("You duck to avoid shards of bone as the "+short()+
        " wielded by "+QTNAME(query_wielded())+" completely shatters "+
        "the "+hdesc+" of "+QTNAME(enemy)+".\n",enemy);
      if(enemy->query_hp() <= 0)
      {
      if(enemy->query_average_stat() < wielder->query_average_stat()-30)
        set_alarm(1.0,0.0,"easy_win");
      if(enemy->query_average_stat() > wielder->query_average_stat()-29
      && enemy->query_average_stat() < wielder->query_average_stat()+29)
        set_alarm(1.0,0.0,"avg_win");
      if(enemy->query_average_stat() > wielder->query_average_stat()-30)
        set_alarm(1.0,0.0,"hard_win");
      }
      break;
  }
