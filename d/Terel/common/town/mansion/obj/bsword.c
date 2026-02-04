inherit "/std/weapon.c";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon()
{
   set_name("sword");
   set_adj("black");
    set_short("black sword");
   set_long("This black sword is vile and evil.  It emanates a " +
   "dark and \nmysterious vibration.\n");

   set_hit(30);
   set_pen(24);
   set_wt(W_SWORD);
   set_dt(W_IMPALE | W_SLASH);

/*   add_prop(OBJ_I_VALUE, comp_value(50)); */
}
