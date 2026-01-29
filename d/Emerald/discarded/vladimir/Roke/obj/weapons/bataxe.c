inherit "/std/weapon";
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>


create_weapon()
{
   set_name("two handed waraxe");
   add_name(({"waraxe","axe"}));
   set_short("ornate two handed waraxe");
   set_long("This axe is huge to say the least. It has  "+
            "ornate carvings of war all over the handle. "+
            "You feel as though with a good swipe it would "+
            "probably cut most people to shreds.\n");

   add_adj("two handed");

   set_default_weapon(35, 40, W_AXE, W_SLASH, W_BOTH, 0);
set_wf(TO);
   add_prop(OBJ_I_WEIGHT, 9100);
   add_prop(OBJ_I_VOLUME, 1600);
   add_prop(OBJ_I_VALUE, 700);
}




mixed
wield(object what)
{
   if (this_player()->query_skill(SS_WEP_AXE) > 50)
   if (TP->query_base_stat(SS_STR) > 75)
   if (TP->query_base_stat(SS_CON) > 60)
      {
      write("You wield the "+ TO->query_short() +" with blood lust "+
            "gleaming in your eyes.\n");
      say(QCTNAME(TP)+"'s eyes begin to shine, blood lust "+
                      "is obviously present.\n");   
   return 0;
   }
   TP->command("grumble");
   TP->add_fatigue(-random(75)-5);
   return "You feebly attempt to wield the "+ TO->query_short() +", "+
          "but you are too much of a weakling.\n";
   
}

mixed
unwield(object what)
{
   write("A snickering can be heard from somewhere.\n");
      return 0;

}

