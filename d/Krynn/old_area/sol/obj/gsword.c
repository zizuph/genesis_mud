/* The sword used by Grum and Hepp
 * Teth, April 25, 1996
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>

create_weapon()
{
   set_name(({"longsword", "sword"}));
   set_short("tempered longsword");
   set_adj("tempered");
   set_pshort("tempered longswords");
   set_long("This longsword has been tempered to reduce wear and tear. " +
            "It appears to be useful for both stabbing and slashing " + 
            "opponents. It has a plain hilt and pommel.\n");
   set_default_weapon(29, 24, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
   add_prop(OBJ_I_VOLUME, 1800);
   add_prop(OBJ_I_WEIGHT, 5500);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(29,24));
}


