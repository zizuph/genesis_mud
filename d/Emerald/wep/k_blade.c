inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include "default.h"

void
create_weapon()
{
   set_name("blade");
   add_name("dramlins blade");
   set_short("dramlins blade");
   set_long("@@desc");
   add_item("surface","The surface appears black and impenentrable, yet "+
        "it seems to draw you ever closer.\n");
   set_adj("unlife");
   
   set_default_weapon(29, 31, W_KNIFE, W_SLASH | W_IMPALE,  
      W_LEFT,  this_object());
   add_prop(OBJ_I_WEIGHT, 3163); 
   add_prop(OBJ_I_VOLUME,  1981); 
}

string
desc()
{
   return break_string("This blade looks lovely, decorated with ornate "+
        "runes, intertwined with roses and leaves. You feel as if the "+
        "grip were made especially for you.\n", 76);
}

int
wield(object wep)
{
   if(this_player()->query_skill(SS_WEP_KNIFE) < 50)
   {
      write("You feel as if your hands are too slippery.\n");
      return -1;
   }
   return 0;
}

void
init()
{
   ::init();
   add_action("do_flip","flip");
}

int
do_flip()
{
  if((TP->query_stat(SS_DEX)-20+random(40)) > TP->query_stat(SS_DEX)) {
    write("You throw the blade up in the air and catch it perfectly.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" throws the blade up in the air and "+
        "catches it perfectly.\n", TP);
    return 1;
  }
  write("You throw the blade up in the air, and manage to impale yourself "+
        "catching it.\n");
  say(QCTNAME(TP)+" throws the blade up in the air and "+
        "manages to impale "+POS(TP)+"self on it.\n", TP);
  return 1;
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

int
try_hit(object ob) 
{
   return 1; 
}

/* Filter the people without see_blood, so they dont see the special hits 
*/
static void
tell_watcher(string str, object enemy)
{
    object me, *ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}

/* After we tried to hit something this function is called with the result. 
*/
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    object blind;
    string *place, *how;
    int ran;

    place = ({"shoulder","ribs","neck","thigh","stomach","chest","back"})[random(7)];
    how = ({"nastily","hard","thunderingly","sickeningly"})[random(4)];

    if (dam > 0 && dam < 80)
    {
        query_wielded()->catch_msg("Dramlins blade almost jumps out of your "+
           "hand as it strikes near to "+QTNAME(enemy)+"'s head.\n");
        enemy->catch_msg("Dramlins blade snatches at the air where your "+
           "head was a few seconds ago.\n");
        tell_watcher(QCTNAME(query_wielded())+"'s blade pokes the air where "+
           QTNAME(enemy)+"'s head was.\n", enemy);
    }
    if (dam >= 80 && dam < 200)
    {
        query_wielded()->catch_msg("You duck under "+QTNAME(enemy)+"'s "+
           "guard and scratch "+QTNAME(enemy)+"'s ribs.\n");
        enemy->catch_msg(QCTNAME(query_wielded())+" jumps under your "+
           "guard and scratches your ribs with "+POS(query_wielded())+
           " blade.\n");
        tell_watcher(QCTNAME(query_wielded())+"'s jumps in under "+
           QTNAME(enemy)+"'s guard and scratches "+POS(enemy)+" ribs "+
           "badly.\n",enemy);
    }
    if(dam >= 200)
    {
        query_wielded()->catch_msg("You swing round and catch "+QTNAME(enemy)+
           " hard in the "+place+".\n");
        enemy->catch_msg(QCTNAME(query_wielded())+" catches you "+how+" in "+
           "the "+place+".\nYou feel stunned.\n");
        tell_watcher(QCTNAME(query_wielded())+" swings round and catches "+
           QTNAME(enemy)+" "+how+" in the "+place+".\n", enemy);
    }
    return 0;
}
