inherit "/std/weapon";
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/d/Shire/defs.h"

create_weapon()
{
  set_name("spear");
  set_pname("spears");
  set_short("black-shafted mithril-headed spear");
  set_adj(({ "black", "black-shafted", "mithril", 
            "mithril-headed", "magic" }));

  set_long("This heavy spear has a thick, black, wooden shaft seven "+
     "feet in length. The slender, glittering, diamond-shapped head "+
     "of the spear extends another foot beyond that. Runes are "+
     "carved into the spear in two rows, one on each side of the "+
     "shaft. A distinct, pulsating warmth can be felt emanating "+
     "from this weapon at close range. You judge by the sheer "+
     "size and wieght of this spear that it is a difficult "+
     "weapon to use effectively.\n");

  set_hit(30);
  set_pen(58);
  set_wt(W_POLEARM);
  set_dt(W_IMPALE);
  set_hands(W_BOTH);
  set_wf(this_object());
 
  add_prop(OBJ_I_WEIGHT, 10000);
  add_prop(OBJ_I_VOLUME, 5000); 
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20, 20));
}

mixed
wield(object ob)
{
  if (TP->query_stat(SS_INT) < 140)
  {
    TO->move(ENV(TP));
    return "You fail to comprehend how this silly stick "+
           "can be used as an effective weapon and cast it "+
           "aside.\n";
  }
 
  else if (TP->query_skill(SS_WEP_POLEARM) < 70)
  {
    return "The "+ short() +" feels uncomfotable in your hands and "+
           "you decide to choose a different weapon.\n";
  }
 
  else if (TP->query_stat(SS_STR) < 150)
  {
    return "You struggle to carry the "+ short() +" and decide "+
           "it's too heavy for you to use.\n";
  }
 
  else
  {
    write("You firmly grasp the "+ short() +".\n");
    say(QCTNAME(TP) + " readies his "+ short() +" for combat.\n");
    return 1;
  }
}

mixed
unwield(object ob)
{
  write("You relax your grip on the "+ short() +".\n");
  say(QCTNAME(TP) + " loosens his grip on his "+ short() +".\n");
  return 1;
}
 
static void
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
 
void
try_thrust(object enemy, int dam)
{
  object wielder = query_wielded();
  int MY_STAT = TP->query_stat(SS_INT);
  int ENEMY_SKILL = enemy->query_skill(SS_DEFENSE); 
 
  if ((random(MY_STAT) + dam) > random(3*ENEMY_SKILL))
  {
    wielder->catch_msg("You notice a slight lapse in your "+
                       "opponents' defense and strike quickly!\n");
    enemy->catch_msg("The "+short()+" strikes you [how].\n");
    enemy->catch_msg("It does "+dam+" points of damage.\n");
    enemy->heal_hp(-dam);
  }
}
  
public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
  object wielder = query_wielded();

  switch(phurt)
  {
    case -1:
    case -2:
      query_wielded()->catch_msg("You wildly lunge with your "+short()+" and"+
        "miss everything.\n");
      enemy->catch_msg(QCTNAME(query_wielded())+" wildly lunges with "+
        HIS_HER(query_wielded())+" "+short()+" and misses you.\n"); 
      tell_watcher(QCTNAME(query_wielded())+" wildly lunges with "+
        HIS_HER(query_wielded())+" "+short()+" and misses "+
        "everything\n", enemy);
      break;
    case 0:   
      query_wielded()->catch_msg("You harmlessly jab your "+short()+
        " through the air.\n");
      enemy->catch_msg(QCTNAME(query_wielded())+" harmlessly jabs "+
        "the air next to you with "+HIS_HER(query_wielded())+" "+short()+".\n");     
      tell_watcher(QCTNAME(query_wielded())+" harmlessly jabs "+
        HIS_HER(query_wielded())+" "+short()+" through the air.\n",enemy);
      break;
    default:
      query_wielded()->catch_msg("Your "+short()+" pierces a hole "+
        "through the "+hdesc+" of your enemy.\n");
      enemy->catch_msg(QCTNAME(query_wielded())+" impales your "+hdesc+
        "with "+HIS_HER(query_wielded())+" "+short()+".\n");
      tell_watcher(QCTNAME(query_wielded())+" watcher message.\n",enemy);
      break;
  }
  try_thrust(enemy, dam/2);
}
