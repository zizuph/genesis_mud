inherit "/std/weapon";
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>


void
create_weapon()

{
   set_name("longsword");
   add_name("sword");
   set_short("green steel longsword");
   set_long("This is a longsword made from green steel. "+
               "It has an emblem on each side of the blade of "+
             "two crossed axes over a map of the world.\n");
   set_adj(({"green", "steel"}));


   set_hit(35);
   set_pen(35);
   set_wf(TO);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_WEIGHT, 3500);
   add_prop(OBJ_I_VOLUME, 2000);
   add_prop(OBJ_I_VALUE, 800);
   set_hands(W_ANYH);
}




mixed
wield(object what)
{
   if (this_player()->query_skill(SS_WEP_SWORD) > 40)
   if (TP->query_base_stat(SS_WIS) > 50)
   if (TP->query_base_stat(SS_DEX) > 50)
      {
      write("You feel confident as you wield the "+ TO->query_short() +".\n");
      say(QCTNAME(TP)+"'s face narrows, thoughts obviously racing "+
            "through "+ TP->query_possessive() +" mind.\n");   
   return 0;
   }
   TP->add_hp(-random(30)-5);
   return "You attempt to wield the "+ TO->query_short() +", but "+
          "feel as though you are unworthy to wield a sword such "+
          "as this.\n";
   
}

mixed
unwield(object what)
{
      return 0;

}

