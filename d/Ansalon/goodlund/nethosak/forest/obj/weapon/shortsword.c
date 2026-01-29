#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <options.h>
#include <filter_funs.h>

void
create_weapon()
{
   set_name("shortsword");
   add_name("sword");
   add_name("blade");
   set_adj("twin-bladed");
   set_long("The strange shortsword has been made out of tempered "+
            "steel making it extremely durable and hard. Two thin "+
            "identical blades have been attached to the the beautiful "+
            "carved wooden handle. The sword seems to be extremely "+
            "light compared to other swords.\n");

   set_short("twin-bladed shortsword");
   set_default_weapon(35,35, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
   set_likely_dull(0);

   if (random(2)==0)
   {
      add_prop(OBJ_I_VOLUME, 3100);
      add_prop(OBJ_I_WEIGHT, 3500);
   }
   else 
   {
      add_prop(OBJ_I_VOLUME, 5100);
      add_prop(OBJ_I_WEIGHT, 5500);
   }   
}

