 // file name:     /d/Avenir/common/bazaar/Obj/food/mollusk.c
 // creator(s):    Glinda, May , 1995
 // last update:
 // purpose:       A nice little boot to catch with your
 // note:
 // bug(s):
 // to-do:

inherit "/std/armour.c";

#include "/d/Avenir/common/common.h"

public void
create_armour()
{
   set_name("boot");
   set_adj("soaking");
   add_adj(({"wet","old"}));
   set_short("soaking wet boot");
   set_long("This boot looks like it has been lying in water for ages. " + 
            "You can't help but wondering what happened to the other one.\n");
   set_at(A_FEET);
   set_ac(-1);
   add_prop(OBJ_I_VALUE,11);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,2465);
}

