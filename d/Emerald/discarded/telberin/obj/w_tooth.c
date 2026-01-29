inherit "/std/object";

#include "default.h"

void
create_object()
{
   set_short("wyvern's tooth");
   set_name("tooth");
   set_pname("theeth");
   add_name("_telberin_quest_tooth_");
   set_adj("wyvern's");
   add_prop(OBJ_I_WEIGHT, 56);
   add_prop(OBJ_I_VOLUME, 104);
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(OBJ_I_VALUE, 98);
   set_long("This tooth is from a wyvern, it's etched surfaces showing where" +
            " it has eaten armour and weapons.\n");
}

