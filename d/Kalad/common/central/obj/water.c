inherit "/std/drink";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Korat */
void
create_drink()
{
   set_name("water");
   set_adj("litre");
   set_short("litre of water");
   set_long("This water looks fairly fresh.\n");
   set_soft_amount(1000);
   set_alco_amount(0);
   set_drink_msg("It tastes very refreshing.\n");
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_VALUE, 5);
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(OBJ_I_NO_GET,"You can carry water in a container, but not pick it up with your bare hands!\n");
   add_prop("_korat_quest_water",1);
}
