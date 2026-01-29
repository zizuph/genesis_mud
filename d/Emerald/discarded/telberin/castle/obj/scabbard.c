inherit "/std/object";

#include "default.h"

void
create_object()
{
   set_short("scabbard");
   set_long("This red velvet covered scabbard is beautiful, and the sword " +
            "that must go with it must also be amazingly special.\n");
   set_name("scabbard");
   add_name("_mylos_quest_scabbard_");
   
   add_prop(OBJ_I_WEIGHT, 351);
   add_prop(OBJ_I_VOLUME, 212);
   add_prop(OBJ_I_VALUE, 101);
   add_prop(OBJ_M_NO_BUY, 1);
}
