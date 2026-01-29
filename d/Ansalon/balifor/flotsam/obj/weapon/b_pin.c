inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("pin");
    set_adj("belaying");
    set_short("belaying pin");
    set_long("This metal belaying pin is usually used on ships " +
      "to fasten ropes down with, but can be used as a clubbing " +
      "weapon if the need arises. \n");
    set_default_weapon(18,12,W_CLUB,W_BLUDGEON,W_ANYH);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 1500);
}
