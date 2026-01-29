#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <state_desc.h>
#include <composite.h>
#include <cmdparse.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/armour";
int worn;

create_armour()
{
   set_name("helm");
   add_name("helmet");
   add_adj(({"platinum","winged"}));
   set_short("winged platinum helm");
   set_long("The platinum metal from whence this helm was forged "+
      "gleams with an inner light. Two beautifully crafted wings "+
      "sprout from the sides, made of the same pure platinum. The "+
      "helm is exquisite beyond belief, you feel it is blessed in "+
      "some way.\n");
   set_at(A_HEAD);
   set_ac(35);
   add_prop(OBJ_I_VOLUME, 2000);
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VALUE, 10000);
   add_prop(OBJ_I_LIGHT, 1);
   set_af(TO);
   seteuid(getuid(TO));
   worn = 0;
}

init()
{
   ::init();
   set_alarm(4.0, 0.0, "wear_helm");
   /* add_action("do_gleam", "gleam"); */
   add_action("do_say", "'");
   add_action("do_say", "say");
}

void
wear_helm()
{
   TP->command("$wear helm");
}

/*
do_gleam(string str)
{
   object *oblist;
   
   if (worn == 0)
      {
      NF("You must wear the helm to do this.\n");
      return 0;
   }
   
   if (!str)
      {
      write("You narrow your eyes from behind your helm.\n");
      say("Two pinpricks of light gleam like smoldering coals from "+
         "behind the visor of "+QTNAME(TP)+"'s winged platinum helm.");
      return 1;
   }
   
   oblist = parse_this(str, "[at] [the] %l");
   oblist -= ({ this_player });
   
   if ((!strlen(str)) || (!sizeof(oblist)))
      {
      notify_fail("Gleam at whom?\n");
      return 0;
   }
   
   if (sizeof(oblist) == 1)
      str = (string)oblist[0]->query_objective();
   else
      str = "them";
   
   actor("From behind your helm, you narrow your eyes at", oblist, ".");
   targetbb(" regards you sternly, and two pinpricks of light from behind "+
      "the visor of "+POSSESSIVE(TP)+" winged platinum helm bore into you, "+
      "leaving you unnerved", oblist);
   all2actbb(" regards", oblist, " sternly, the two pinpricks of light "+
      "behind the visor of "+POSSESSIVE(TP)+" boring into "+str+" and "+
      "leaving "+str+" unnerved.");
   return 1;
}
*/

do_say(string s)
{
   
   if (worn == 0)
      {
      notify_fail("You must wear the helm to do this.\n");
      return 0;
   }
   
   if (!s)
      {
      notify_fail("Say what?\n");
      return 0;
   }
   
   if (TP->query_option(OPT_ECHO) == 1)
      write("Your voice sounds cool as you speak through the "+
      "helm, `" + s + "'\n");
   if (TP->query_option(OPT_ECHO) == 0)
      write("Ok.\n");
   say("A cool voice rings from beneath "+QTNAME(TP)+"'s helm, `"+
      s+"'\n");
   return 1;
}

mixed
wear(object what)
{
   if (what == TO)
      {
      say("The platinum of "+QTNAME(TP)+"'s helm gleams with inner light "+
         "as "+PRONOUN(TP)+" wears it.\n");
      write("You feel magical warmth sweep over your body as you wear the "+
         "winged platinum helm.\n");
      TP->set_skill(110, (TP->query_skill(110) + 25));
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
      wearer->catch_msg("You slide the platinum helm off and tuck it "+
         "under your arm, feeling its warmth slowly withdraw from you.\n");
      say(QCTNAME(TP) + " slides off "+POSSESSIVE(TP)+" helm and tucks "+
         "it under "+POSSESSIVE(TP)+" arm. The platinum's gleam dies "+
         "down.\n");
      TP->set_skill(110, (TP->query_skill(110) - 25));
      worn = 0;
      return 1;
   }
   
   return 0;
}

string
query_auto_load()
{
   return MASTER_OB(this_object()) + ":";
}
