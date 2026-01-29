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
   add_name("serated blade");
   set_short("serated blade");
   set_long("@@desc");
   add_item("surface","The surface appears black and impenentrable, yet "+
        "it seems to draw you ever closer.\n");
   set_adj("serated");
   
   set_default_weapon(26, 33, W_KNIFE, W_SLASH | W_IMPALE,  
      W_LEFT,  this_object());
   add_prop(OBJ_I_WEIGHT, 3794); 
   add_prop(OBJ_I_VOLUME,  2989); 
}

string
desc()
{
   return "A long serated blade with lovely runes etched on the surface "+
	"and a sharp edge, signifies the tender loving care that went "+
	"into this weapon of death.\n";
}

int
wield(object wep)
{
   if(this_player()->query_skill(SS_WEP_KNIFE) < 60)
   {
      write("You aren't skilled enough to wield such a weapon.\n");
      return -1;
   }
   return 0;
}

void
init()
{
   ::init();
   add_action("do_grate","grate");
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
    how = ({"nasty","devastating","disgusting","sickening"})[random(4)];

    if (phurt == -1)
    {
        query_wielded()->catch_msg("You whirl round and reach out with "+
	   "the serated blade and just miss "+QTNAME(enemy)+" by a "+
	   "whisker.\n");
        enemy->catch_msg(QCTNAME(query_wielded())+" whirls around and "+
	   "reaches out with "+POS(TP)+" blade and just misses you by "+
	   "a whisker.\n");
        tell_watcher(QCTNAME(query_wielded())+" whirls around viciously "+
	   "and reaches out with "+POS(TP)+" and just misses "+QTNAME(enemy)+
	   " by a whisker.\n", enemy);
    }
    if (phurt == 0)
    {
        query_wielded()->catch_msg("You are too quick for "+QTNAME(enemy)+
	   " and manage to scratch "+enemy->query_objective()+" in the "+
	   place+".\n");
        enemy->catch_msg(QCTNAME(query_wielded())+" is just too quick for "+
	   "you and manages to scratch you nastily in the "+place+".\n");
        tell_watcher(QCTNAME(query_wielded())+" is too quick for "+
	   QTNAME(enemy)+" and manages to scratch "+enemy->query_objective()+
	   " in the "+place+".\n",enemy);
    }
    else
    {
        query_wielded()->catch_msg("You kneel and plunge your blade "+
	   "upwards into "+QTNAME(enemy)+"'s "+place+". It is a "+how+" "+
	   "sound.\n");
        enemy->catch_msg(QCTNAME(query_wielded())+" kneels under your "+
	   "guard and plunges upwards into your "+place+" with "+POS(TP)+
	   "blade. It is a "+how+" sound.\n");
        tell_watcher(QCTNAME(query_wielded())+" kneels under "+QTNAME(enemy)+
	   "'s guard and plunges upwards with "+POS(TP)+"blade. It is a "+
	   how+" sound.\n", enemy);
    }
    return 0;
}
