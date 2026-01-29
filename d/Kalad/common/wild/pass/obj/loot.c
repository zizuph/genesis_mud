inherit "/std/object.c";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
/* by Antharanos */
void
create_object()
{
   ::create_object();
   set_name("large pile of loot");
   add_name("large pile");
   add_name("pile");
   add_name("loot");
   set_short("large pile of loot");
   set_long("A very valuable collection of precious items! Besides the "+
      "huge piles of coins, there are several golden chalices, a silver "+
      "goblet and even a priceless emerald.\n");
   add_item(({"golden chalices","chalices","silver goblet","goblet","priceless emerald","emerald"}),
      "It looks expensive!\n");
   add_prop(OBJ_I_VALUE,200000);
   add_prop(OBJ_I_VOLUME,15000);
   add_prop(OBJ_I_WEIGHT,15000);
   add_prop(OBJ_M_NO_SELL,"You can't sell this! It's stolen loot!\n");
}
