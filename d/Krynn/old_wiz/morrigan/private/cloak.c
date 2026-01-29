#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <stdproperties.h>

#define CLOAK_SHADOW "/d/Krynn/morrigan/private/cloak_shadow"
#define CLOAK_SUBLOC "concealed_by_cloak_subloc"

inherit "/std/armour";

int hooded = 0;
int worn = 0;

create_armour()
{
   set_name("cloak");
   add_name("shadow_cloak");
   add_adj("black");
   add_adj("midnight");
   set_short("midnight black cloak");
   set_long("This is a midnight black cloak made of a strange material "+
      "that you cannot identify. It is very thin and light weight, but "+
      "very resilient. The cloak itself is long and flowing, covering "+
      "everything but the owner's feet and hands. The edges of the cloak, "+
      "and hood, are decorated with silver runes.\n");
   add_item("runes", "The runes make no sense to you, but you get a vague "+
      "impression that they are magical in some way.\n");
   set_at(A_ROBE);
   set_ac(5);
   set_af(TO);
   seteuid(getuid(TO));
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VALUE, 1000);
}

mixed
wear(object what)
{
   if (what == TO)
      {
      write("You wrap the midnight black cloak around your body.\n");
      say(QCTNAME(TP)+" wraps the midnight black cloak around "+POSSESSIVE(TP)+
         " body.\n");
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
      if (hooded == 1)
         {
         hooded = 0;
         TP->remove_prop(LIVE_I_NEVERKNOWN);
         TP->remove_subloc(CLOAK_SUBLOC);
         TP->remove_shadow(CLOAK_SHADOW);
       }
      
      wearer->catch_msg("You remove the midnight black cloak.\n");
      say(QCTNAME(TP) + " removes "+POSSESSIVE(TP)+" midnight black "+
         "cloak.\n");
      worn = 0;
      return 1;
   }
   return 0;
}

init()
{
   add_action("raise_hood", "raise");
   add_action("lower_hood", "lower");
   ::init();
}

int
raise_hood(string str)
{
   NF("Raise what?\n");
   if (!str)
      return 0;
   
   if (str != "hood")
      return 0;
   
   NF("You can only raise the hood if you wear the cloak first.\n");
   if (worn != 1)
      return 0;
   
   NF("Your hood is already raised.\n");
   if (hooded == 1)
      return 0;
   
   hooded = 1;
   TP->add_subloc(CLOAK_SUBLOC, TO);
   
   write("Shadows fall across your face as you pull the hood of your "+
      "midnight black cloak over your head.\n");
   say(QCTNAME(TP)+"'s face vanishes into the darkness of "+POSSESSIVE(TP)+
      " cloak as "+PRONOUN(TP)+" pulls the hood over "+POSSESSIVE(TP)+
      " head.\n");
   
   TP->add_prop(LIVE_I_NEVERKNOWN, 1);
   clone_object(CLOAK_SHADOW)->shadow_me(TP);
   return 1;
}

int
lower_hood(string str)
{
   NF("Lower what?\n");
   if (!str)
      return 0;
   
   if (str != "hood")
      return 0;
   
   NF("But you are not wearing the midnight black cloak.\n");
   if (worn != 1)
      return 0;
   
   NF("Your hood is already lowered.\n");
   if (hooded == 0)
      return 0;
   
   hooded = 0;
   TP->remove_subloc(CLOAK_SUBLOC);
   
   write("The shadows surrounding your face vanish as you lower the hood "+
      "of your midnight black cloak.\n");
   say(QCTNAME(TP)+"'s face emerges from the shadows of "+POSSESSIVE(TP)+
      " midnight black cloak as "+PRONOUN(TP)+" lowers "+POSSESSIVE(TP)+
      " hood.\n");
   
   TP->remove_prop(LIVE_I_NEVERKNOWN);
   TP->remove_shadow(CLOAK_SHADOW);
   return 1;
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
   
   string str;
   
   if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   
   if(for_obj == carrier)
      str = "Your face is concealed beneath the darkness of your hooded "+
   "midnight black cloak.\n";
   else
      str = OBJECTIVE(carrier)+" face is concealed beneath the darkness "+
   "of "+POSSESSIVE(carrier)+" hooded midnight black cloak.\n";
   
   return str;
}
