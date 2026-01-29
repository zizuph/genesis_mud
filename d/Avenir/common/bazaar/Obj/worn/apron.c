 //  Glinda May -95.
 //  Armour for the cook

inherit "/d/Avenir/inherit/cloth_arm";

#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Avenir/common/common.h"

void
create_armour ()
{
  set_name("apron");
  set_short("filthy apron");
  add_adj(({"filthy", "cloth"}));
  set_long ("This apron is so filthy you can barely stand to " +
            "touch it, much less wipe your forehead or your hands " +
            "with it.\n");
  set_ac (2);
  set_am(({ 0, 0, 0}));
  set_at (A_WAIST);
   add_prop(OBJ_I_VOLUME,850);
   add_prop(OBJ_I_WEIGHT,530);
   add_prop(OBJ_I_VALUE,23);
}

init()
{
   add_action("wipe_me","wipe");
   ::init();
}

wipe_me(string str)
{
   NF("Wipe what?\n");
   if( str=="forehead with apron" || str=="forehead")
   {
      write("You wipe your forehead with the filthy apron. Eeew!\n");
      say(QCTNAME(TP) + " wipes " + TP->query_possessive() +
          " forehead with " + TP->query_possessive() + " filthy apron.\n");
      return 1;
   }
   if( str== "hands on apron" || str=="hands")
   {
      write("You wipe your hands on the filthy apron. Much to your " +
            "surprise they don't seem any cleaner than before.\n");
      say(QCTNAME(TP) + " wipes " + TP->query_possessive() +
          " hands on " + TP->query_possessive() + " filthy apron.\n");
      return 1;
   }
   return 0;
}
