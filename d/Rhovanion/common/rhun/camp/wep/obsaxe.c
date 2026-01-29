 
inherit "/std/weapon";
 
#include "/sys/ss_types.h"
#include <stdproperties.h>
#include "/sys/wa_types.h"
#include <macros.h>
#include <filter_funs.h>
#include <formulas.h>
 
void
create_weapon()
{
    set_name("axe");
    set_adj("obsidian");
    set_adj("ancient");
    set_short("ancient obsidian axe");
    set_long("You wonder who and when made this axe, "+
        "but you don't see any signs which can help "+
        "to find it out.\n"+
        "This is a very unusual two-bladed obsidian axe. "+
        "You feel as power flows through your body when "+
        "you touch it. As your fingers firmly grip the "+
        "handle you feel that you can stand toe-to-toe "+
        "with everyone!\n");
 
 
    set_pen(40);
    set_hit(45);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_RIGHT);
 
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); /* it is magic */
    add_prop(MAGIC_AM_MAGIC,({ 33, "enchantment" }));
}
 
static void
tell_watcher(string str, object me, object enemy)
{
    object *ob;
    int i;
 
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
 
int
try_hit(object enemy)
{
  int skill, stat, skill_e, stat_e, pen, perf, pdam;
  mixed *hitresult;
  object me;
  string text, ptext, ptext2, ptexta;
 
  me = query_wielded();
  skill = me->query_skill(SS_WEP_AXE);
  stat = me->query_stat(SS_STR);
  skill_e = enemy->query_skill(SS_DEFENCE);
  stat_e = enemy->query_stat(SS_DEX);
 
 
  if ((random(60) < (skill/2)) &&
      (((random(skill+stat)*3)/2) > random(skill_e+stat_e)))
  {
    int lev;
    pen = F_PENMOD(45+random(stat/3), skill);
    hitresult = enemy->hit_me(pen,W_IMPALE|W_SLASH, me, -1);
    perf = hitresult[2] * 100 / pen;
    pdam = hitresult[0];
 
    lev = 0;
    ptext = "tickles";
    ptext2 = ".";
    if (perf > 20)
     {
      ptext = "hits";
      ptext2 = " hard.";
     }
    if (perf > 45)
     {
      ptext = "bonked";
      ptext2 = " seriously.";
     }
    if (perf > 65)
     {
      ptext = "smashes";
      ptext2 = " with a mighty blow!";
     }
    if (perf > 90)
     {
      ptext = "massacres";
      ptext2 = " to small fragments!";
     }
 
    text = "unharmed";
    if (pdam > 0)
      text = "tickled";
    if (pdam > 2)
      text = "grazed";
    if (pdam > 5)
      text = "sligtly hurt";
    if (pdam > 10)
      text = "hurt";
    if (pdam > 17)
      text = "rather hurt";
    if (pdam > 30)
      text = "very hurt";
    if (pdam > 45)
      text = "smashed";
    if (pdam > 70)
      text = "crushed";
    if (pdam > 90)
      text = "seeing death comming";
 
    if( perf > 75 )
    {
       me->catch_msg("You laugh demonically, as you feel "+
                        "your axe beats deep into your enemy.\n");
       tell_watcher( QTNAME(me)+" laughs"+
                     " demonically, as his axe beats deep into "+
                     QTNAME(enemy)+"!\n",me,enemy );
       enemy->catch_msg( QTNAME(me)+" laughs demonically, as his axe "+
                     "beats deep into your body!\n" );
    }
    me->catch_msg("Your obsidan axe "+ptext+" "+QTNAME(enemy)+
                  ptext2+"\n"+
                  capitalize(enemy->query_pronoun())+" seems "+
                  "to be "+text+".\n");
    enemy->catch_msg("The obsidan axe wielded by "+QTNAME(me)+" "+
                  ptext+" you"+ptext2+"\n"+
                  "You feel "+text+".\n");
    tell_watcher("The obsidan axe wielded by "+QTNAME(me)+" "+
                  ptext+" "+QTNAME(enemy)+ptext2+"\n"+
                  QTNAME(enemy)+" seems "+
                  "to be "+text+".\n",me,enemy);
    if (enemy->query_hp() <= 0)
    {
      enemy->do_die(me);
      return 0;
    }
     return 0;
  }
  return 1;
}
