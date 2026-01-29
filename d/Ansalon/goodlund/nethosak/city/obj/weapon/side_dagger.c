/*
 *
 * glain
 *
 * These daggers are a common side weapon among the minotaurs in
 * case their weapon of choice breaks, disarmed, etc.  Most
 * minotaurs carry one tucked into their belt. 
 *
 */
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

void create_weapon()
{
   set_name("dagger");
   set_adj("long");
   add_adj("slim");
   set_long("This dagger is almost long enough to be a short sword, " +
      "but for minotaurs makes a great side weapon that is easy " +
      "to conceal.  It is not the greatest craftsmanship but it " +
      "gets the job done.\n");
   set_short("long slim dagger");
   set_default_weapon(16,16, W_KNIFE, W_SLASH, W_ANYH);

   add_prop(OBJ_I_VOLUME, 1200);
   add_prop(OBJ_I_WEIGHT, 1000);
}