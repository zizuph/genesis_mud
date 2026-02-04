
inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

public void
create_weapon ()
{
  set_name("sword");
  set_short("typical sword");
  add_adj(({"typical" }));
  set_long("This is a standard 40/40 sword for testing.\n");
  set_hit (40);
  set_pen (40);
  set_dt (W_IMPALE | W_SLASH);
  add_prop (OBJ_I_WEIGHT, 10000);
  add_prop (OBJ_I_VOLUME, 10000);

}

int
set_dull(int du)
{

    return 1;
}

