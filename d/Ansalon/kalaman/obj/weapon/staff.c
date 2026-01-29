inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("staff");
    add_name("weapon");
    set_pname("staffs");
    add_pname("weapons");
    set_short("staff of office");
    set_pshort("staffs of office");
    set_long("This long, thick wooden staff, painted black, " +
      "is that carried by the chamberlain of Kalaman.\n");
    set_default_weapon(30,20,W_POLEARM, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 3000);
}
