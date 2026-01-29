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
   set_name("peace maker");
   add_name("maker");
   set_pname("peace makers");
   add_name("dagger");
   set_adj("vicious");
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
        ob[i]->catch_msg(QCTNAME(enemy)+" is smacked by someone.\n");
    }
}


int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
int phit, int dam)
{
  object me = TP;

   {
    enemy->heal_hp(-dam);

      if(enemy->query_hp()<=0)
     {
   enemy->do_die(me);
      me->catch_msg("You deftly slice into your opponents throat."+
        "the peace maker shimers slightly as it slices through "+
        ""+QTNAME(enemy)+"'s neck. Blood spills everywhere.\n");
      tell_watcher(QCTNAME(me)+" deftly slices into "+ QTNAME(enemy) +"'s "+
        "neck. The peace maker shimers slightly as it comes out the back "+
        "of "+QTNAME(enemy)+"'s neck.\n");
      return 1;
     }

    if(phurt == -1)
     {
     me->catch_msg("You dart forward with linding speed, just "+
      "missing "+QTNAME(enemy)+".\n");
     enemy->catch_msg(QCTNAME(me)+"'s vicious midnight-black peace maker "+
       "narrowly misses you.\n");
     tell_watcher(QCTNAME(me)+"'s vicious midnight-black peace maker just "+
       "glides past "+QTNAME(enemy)+".\n");
     }

    switch (phurt)
     {

  case 0..4:
    me->catch_msg("You catch "+QTNAME(enemy)+" off guard as you violently "+
     "stab "+QTNAME(enemy)+" with your peace maker.\n");
    enemy->catch_msg(QCTNAME(me)+" stabs you while you were not looking. "+
      "You notice "+me->query_possessive()+" peace maker grows a deeper "+
      "color of black.\n");
    tell_watcher(QCTNAME(me)+" stabs "+ QTNAME(enemy) +" violently "+
     "with "+me->query_possessive()+" vicious midnight-black peace maker.\n");
    break;

  case 5..9:
    me->catch_msg("You whip your wrist around and catch "+QTNAME(enemy)+" on "+
      "on the side of "+enemy->query_possessive()+" face.\n");
    enemy->catch_msg(QCTNAME(me)+" whips "+ me->query_possessive() +" wrist "+
      "around and savagely cuts your face.\n");
    tell_watcher(QCTNAME(me)+ " whips "+ me->query_possessive() +" wrist "+
      "around and savagely cuts "+QTNAME(enemy)+".\n");
    break;

  case 10..19:
    me->catch_msg("You darkness engulf your arm as you nearly impale "+
      ""+QTNAME(enemy)+" on you peace maker.\n");
    enemy->catch_msg("You have an intense feeling of fear gripping you. "+
     ""+QTNAME(me)+" nearly impales you, you begin to get woozy "+
      "from the loss of blood.\n");
    tell_watcher("You notice darkness around "+QCTNAME(me)+"'s arm as "+
      ""+ me->query_possessive() +" nearly impales "+QTNAME(enemy)+".\n");
    break;

  case 20..29:
    me->catch_msg("Your peace maker seems to guide itself "+
      "towards "+QTNAME(enemy)+"'s body and cut it cruelly.\n");
    tell_watcher(QCTNAME(me)+"'s peace maker strikes with amazing "+
      "speed and accuracy as it solidly strikes "+QTNAME(enemy)+"'s "+
      "body.\n");
    enemy->catch_msg(QCTNAME(me)+"'s peace maker strikes your body "+
      "before you could even react. Blood ensues.\n");
    break;

  case 30..49:
    me->catch_msg("You reach through "+ QTNAME(enemy) +"'s guard "+
      "and catch "+ enemy->query_objective() +" squarely in the "+
      "abdomen. "+QTNAME(enemy)+"'s intestins look ready to fall out\n");
   enemy->catch_msg(QCTNAME(me)+" reaches through your guard and "+
      "wickedly cuts into your abdomen.\n");
    tell_watcher(QCTNAME(me)+" reaches through "+QTNAME(enemy)+"'s guard "+
      "with speed and power equal to none other. "+QTNAME(enemy)+"'s "+
      "intestines look ready to fall out.\n");
    break;

  case 50..69:
    me->catch_msg("You begin to lose control of your peace maker "+
                  "as it nails "+QTNAME(enemy)+", embeding "+
                  "itself deeply into "+ enemy->query_possessive() +" leg.\n");
    enemy->catch_msg(QCTNAME(me)+" nails you in the leg, you "+
                   "can feel the peace maker embedding itself "+
                   "deeper and deeper into your leg.\n");
    tell_watcher(QCTNAME(me)+" nails "+QTNAME(enemy)+" deeply in the leg.\n");
    break;

  case 70..89:
    me->catch_msg(QTNAME(enemy)+" is bleeding profusely from "+
      "the head, as you catch "+ enemy->query_objective() +" squarely "+
      "in te head.\n");
    enemy->catch_msg("You feel as though an artery has been "+
    "opened in your head after "+QTNAME(me)+" catches you "+
      "squarely on the side of your head.\n");
    tell_watcher(QTNAME(enemy)+" is bleeding terribly from "+
   "the head after "+ QTNAME(me) +" catches "+ QTNAME(enemy) +" squarely "+
      "on the head.\n");
    break;

  default:
    me->catch_msg("You stab "+QTNAME(enemy)+" maliciously clearly "+
      "attempting to mutilate "+ enemy->query_objective() +".\n");
    enemy->catch_msg(QCTNAME(me)+" cuts you maliciously in a "+
          "clear attempt to mutilate you.\n");
    tell_watcher(QCTNAME(me)+" maliciously attempts to "+
             "mutilate "+ QTNAME(enemy) +".\n");
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
   if (this_player()->query_skill(SS_WEP_KNIFE) > 70)
   if (TP->query_base_stat(SS_DIS) > 80)
   if (TP->query_base_stat(SS_DEX) > 80)
  {
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
}

mixed
unwield(object what)
{
   return 0;
}



query_recover()
{
   return MASTER+":"+query_wep_recover();
}
init_recover(arg)
{
   init_wep_recover(arg);
}


