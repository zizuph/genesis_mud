#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"

#define SHIMMERING_SUBLOC "shimmering_subloc"

inherit "/std/armour";
int worn, shimm = 0;

create_armour()
{
   set_name("cape");
   add_name("cloak");
   add_adj(({"shimmering","silver","full"}));
   set_short("shimmering silver cape");
   set_long("This cape shimmers with silver light, swirling and "+
      "dancing around you, making you literally glow.\n");
   set_at(A_ROBE);
   set_ac(10);
   add_prop(OBJ_I_VOLUME, 500);
   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VALUE, 10000);
   set_af(TO);
   seteuid(getuid(TO));
   worn = 0;
}

init()
{
   set_alarm(3.0, 0.0, "wear_cape");
   add_action("shimmer", "shimmer");
   ::init();
}

int
shimmer(string str)
{
   
   if (worn != 1)
   {
      NF("What ?\n");
      return 0;
   }

   if (str != "on" && str != "off")
      {
      if (shimm == 0)
         write("Your cloak is not shimmering.\n");
      else if (shimm == 1)
         write("Your cloak is shimmering.\n");
      return 1;
   }
   
   if (!str)
      {
      NF("Shimmer on or off?\n");
      return 0;
   }
   
   if (str == "on" && shimm == 0)
      {
      write("Your cape swirls around you, casting beams of silver light "+
         "in every direction. You feel invincible as the light pours "+
         "over your body!\n");
      say(QCTNAME(TP)+"'s cape swirls around "+POSSESSIVE(TP)+" body, "+
         "casting beams of silver light in every direction.\n");
      TP->add_subloc(SHIMMERING_SUBLOC, TO);
      TP->add_prop(OBJ_M_NO_ATTACK, "You try to attack, but the shimmering "+
         "globe of silver light prevents you from getting near, and your "+
         "attack fails.\n");
      shimm = 1;
      return 1;
   }
   else if (str == "on" && shimm == 1)
      {
      write("Your cape is already shimmering.\n");
      return 1;
   }
   else if (str == "off" && shimm == 1)
      {
      write("Your cape slowly stops swirling, falling gently around your "+
         "body again as the silver globe fades.\n");
      say(QCTNAME(TP)+"'s cape slowly stops swirling, and falls gently "+
         "around "+POSSESSIVE(TP)+" body as the silver globe fades.\n");
      TP->remove_subloc(SHIMMERING_SUBLOC);
      TP->remove_prop(OBJ_M_NO_ATTACK);
      shimm = 0;
      return 1;
   }
   else if (str == "off" && shimm == 0)
      {
      write("Your cape is not shimmering.\n");
      return 1;
   }
   
   return 0;
}

void
wear_cape()
{
   set_alarm(7.0, 0.0, "shimmer1");
   TP->command("$wear cape");
}

void
shimmer1()
{
   TP->command("$shimmer on");
}

mixed
wear(object what)
{
   if (what == TO)
      {
      write("You wrap the shimmering silver cape around your body.\n");
      say(QCTNAME(TP)+" wraps the shimmering silver cape around "+
         POSSESSIVE(TP)+" body, basking in it's silver glow.\n");
      worn = 1;
      return 1;
   }
   
   return 0;
}

mixed
remove(object what)
{
   if (what == TO)
      {
      if (shimm == 1)
         TP->command("$shimmer off");

      wearer->catch_msg("You remove the shimmering silver cape.\n");
      say(QCTNAME(TP) + " removes "+POSSESSIVE(TP)+" shimmering "+
         "silver cape.\n");
      worn = 0;
      return 1;
   }
   
   return 0;
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
   
   string str;
   
   if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   
   if(for_obj == carrier)
      str = "A dazzling globe of pure silver light surrounds you.\n";
   else
      str = "A dazzling globe of pure silver light surrounds "+OBJECTIVE(carrier)+".\n";
   
   return str;
}



string
query_auto_load()
{
   return MASTER_OB(this_object()) + ":";
}
