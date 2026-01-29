inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
   set_name("club");
   set_adj("big");
   add_adj("steel"); 
   set_short("big steel club");   set_long("This is a big steel club about 4 feet long, " +
      "often seen in the hands of ogres that live in the nearby " +
      "land of Kern. Although not very well balanced, you would " +
      "say if it hit someone, it would certainly hurt. \n");
   set_default_weapon(20,30,W_CLUB,W_BLUDGEON,W_ANYH);
   add_prop(OBJ_I_VOLUME, 6000);
   add_prop(OBJ_I_WEIGHT, 6000);
}

