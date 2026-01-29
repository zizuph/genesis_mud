inherit "/std/weapon";
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/d/Shire/defs.h" 
 
create_weapon()
{
  set_name("stalagmite");
  set_pname("stalagmites");
  set_adj(({ "stone", "heavy" }));
  set_short("heavy stalagmite");
  set_long("This is a large stalagmite formed on the floors "+
     "of many a dark cave. Wide and rounded towards it base, "+
     "it tapers to a narrow tip some ten feet away. Apparently "+
     "it has been snapped off at its base by something inhumanly "+
     "strong.\n");
 
  set_hit(25);
  set_pen(55);
  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);
  set_hands(W_BOTH);
 
  add_prop(OBJ_I_WEIGHT, 250000);
  add_prop(OBJ_I_VOLUME, 200000);
  add_prop(OBJ_I_VALUE, 0);
}
