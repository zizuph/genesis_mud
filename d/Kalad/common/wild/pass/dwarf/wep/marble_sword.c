inherit "/d/Kalad/std/weapon.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by korat */
create_weapon()
{
   ::create_weapon();
   set_name("longsword");
   add_name("sword");
   set_adj("marble");
   set_short("marble longsword");
   set_pshort("marble longswords");
   set_long("This sword of marble shines so much that you can "+
      "use it as a mirror. Its polished, sharp surface contains "+
      "a wide range of colours and variegations. A work of art.\n");
   set_hit(35);
   set_pen(40);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   add_prop(OBJ_I_VALUE,2000);
   add_prop(OBJ_I_WEIGHT, 12000);
   add_prop(OBJ_I_VOLUME, 6000);

   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(OBJ_S_WIZINFO,
      "This sword is enchanted, giving it better hit and pen.\n");
   add_prop(MAGIC_AM_ID_INFO,
      ({"The sword is magical.\n",5,
      "The sword has been enchanted to hit and penetrate better.\n",40}));
   add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
}

unwield(object what)
{
   if((E(TO)->id("statue")) && (E(TO)->query_hp() > 0))
      {
      tell_room(E(E(TO)), "The long marble sword seems to "+
         "be a part of the statue. It refuses to unwield.\n", E(TO));
      return "The sword cannot be unwielded!";
   }
   return 0;
}



/*
* Function name: tell_watcher
* Description:   Send the string from the fight to people that want them
* Arguments:     The string to send
* This function is copied from Magebane (jagged scimitar) by Mercade.
*/

static void
tell_watcher(string str, object enemy)
{
   object me,*ob;
   int i;
   
   me = query_wielded();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
   if(ob[i]->query_option(OPT_BLOOD))
      ob[i]->catch_msg(str);
}


public mixed did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
   string mine_msg;
   string your_msg;
   string other_msg;
   object wielder = query_wielded();
   
   /* Change the combat messages */
   switch(phurt)
   {
      case -2..25:
      break;
      default:
      mine_msg="The marble longsword bites deeply into "+QTNAME(enemy)+
         "'s flesh.\n";
      your_msg="The marble longsword bites deeply into your flesh.\n";
      other_msg="The marble longsword of "+QTNAME(wielder)+" bites "+
         "deeply into "+QTNAME(enemy)+"'s flesh.\n";
      wielder->catch_msg(mine_msg);
      enemy->catch_msg(your_msg);
      tell_watcher(other_msg,enemy);
      break;
   }
   return 0;
}


