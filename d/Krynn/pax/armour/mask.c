#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/armour";
int worn;

create_armour()
{
   set_name("helmet");
   add_name("helm");
   add_name("mask");
   add_adj(({"hideous","horned"}));
   set_short("hideous horned dragonhelm");
   add_name("dragonhelm");
   set_long("This mask is carved to resemble the visage of a dragon. Horns "+
      "adorn the mask, which is black with gold trim. This superb "+
      "mask clearly belonged to someone of great importance, and you "+
      "feel certain the mask is magically blessed by the Dark Queen.\n");
   set_at(A_HEAD);
   set_ac(35);
   add_prop(OBJ_I_VOLUME, 5000);
   add_prop(OBJ_I_WEIGHT, 5000);
   set_af(TO);
   seteuid(getuid(TO));
   worn = 0;
}

init()
{
   ::init();
   add_action("do_say", "'");
   add_action("do_say", "say");
}

do_say(string s)
{
   
   if (worn == 0)
      {
      notify_fail("You must wear the mask to do this.\n");
      return 0;
   }
   
   if (!s)
      {
      notify_fail("Say what?\n");
      return 0;
   }
   
   if (TP->query_option(OPT_ECHO) == 1)
      write("Your voice sounds cold and harsh as you speak through the mask, `"+
      s+"'\n");
   if (TP->query_option(OPT_ECHO) == 0)
      write("Ok.\n");
   
   say("A cold voice thunders from beneath "+QTNAME(TP)+"'s mask, `"+
      s+"'\n");
   return 1;
}

mixed
wear(object what)
{
   say(QCTNAME(TP)+" solemnly pulls the hideous horned dragonhelm over "+
      POSSESSIVE(TP)+" face, concealing "+POSSESSIVE(TP)+" features.\n");
   write("You solemnly pull the hideous horned dragonhelm over your face.\n");
   worn = 1;
   return 1;
}

mixed
remove(object what)
{
   wearer->catch_msg("You pull the dragonhelm off, revealing your features again.\n");
   say(QCTNAME(TP) + " pulls off the horned dragonhelm, revealing "+
      POSSESSIVE(TP)+" features again.\n");
   worn = 0;
   return 1;
}
