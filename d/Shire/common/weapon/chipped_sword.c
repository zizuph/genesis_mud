/* this is a test modify of the supersword */

inherit "/std/weapon";

#include <macros.h>
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon()
{
  set_name(({"sword","chipped sword"}));
  set_pname("swords");
  set_short("chipped sword");
  set_pshort("chipped swords");
  set_long("This sword is very old and seems to have taken many life.\n");

  set_default_weapon( /* See /sys/wa_types.h for maxima */
    30,
    30,
    W_SWORD,                /* weapon type       */
    W_IMPALE | W_SLASH,     /* damage type       */
    W_NONE,                 /* nr of hands       */
    0
  );           /* object that defines wield and unwield functions */

  add_prop(OBJ_I_WEIGHT, 8000);
  add_prop(OBJ_I_VOLUME, 6000);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(80, 80));
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
