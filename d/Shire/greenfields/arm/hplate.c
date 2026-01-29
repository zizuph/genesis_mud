//  Mod:  Added /std/keep to this armour -Igneous

inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

object wearer;

create_armour()
{
   set_name("breastplate");
   set_adj(({"lacquered","steel"}));
   set_short("lacquered steel breastplate");
   set_long("The "+short()+" seems as much a piece of art as a "+
      "piece of armour. Formed of two halves that buckle together "+
      "to encase the entire torso in sturdy steel, the armour "+
      "also sports elaborate decorations. Flowing down from the "+
      "shoulders and meandering across both the front and the back of "+
      short()+" is a wide, painted ribbon of darkest blue edged "+
      "in gold and silver that crosses over the wearer's heart and "+
      "spine. The "+short()+" was obviously crafted for a human lord.\n");
   set_default_armour(40,A_TORSO,({1,1,-2}),0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(40,A_TORSO) + 550);
   add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(40) + random(101));
   add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


public int wear()
{
   wearer = this_player();
   WRITEN("You encase yourself in the "+short()+" by buckling the "+
      "two halves together around you.");
   SAY(" buckles on the "+short()+".");
   return 1;
}


public int remove()
{
   WRITEN("You unbuckle the two halves of the "+short()+" and let them "+
      "fall away from your body.");
   say(QCTNAME(wearer)+" unbuckles the "+short()+".\n");
   return 1;
}

string
query_recover()
{
   return MASTER + ":" + query_arm_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
   init_arm_recover(arg);
   
   init_keep_recover(arg);
}
