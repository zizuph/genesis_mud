inherit "/std/drink";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Korat */
void
create_drink()
{
   set_name("coffee");
   set_adj("litre");
   set_short("litre of coffee");
   set_long("This coffee smells wonderful!\n");
   set_soft_amount(1000);
   set_alco_amount(0);
   set_drink_msg("It tastes very refreshing.\n");
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_VALUE, 5);
   add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_GET,"You want to hold some hot coffee in your hands? "+
      "No, it must stay in a container.\n");
   add_prop("_korat_quest_coffee",1);
}
