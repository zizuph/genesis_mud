inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/sys/formulas.h"


void
create_weapon()
{
   set_name("sword");
   add_name(({"shadesword","shade sword"}));
   set_short("shadesword");
   set_long("This sword is a favorite of the Shades.\n");
   set_default_weapon(31, 27, W_SWORD, W_SLASH | W_IMPALE, W_ANYH, 0);
   
   add_prop(OBJ_I_WEIGHT, 3000);
   add_prop(OBJ_I_VOLUME,  500);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(31, 27) + random(200) - 100);
   
}
