inherit "/std/weapon.c";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include "/d/Terel/common/terel_std_rec.h"

create_weapon()
{
   set_name("sword");
    set_short("blue sword");
   set_adj("blue");
   set_long("A blue sword of good quality.\n");

   set_hit(25);
   set_pen(24);
   set_wt(W_SWORD);
   set_dt(W_IMPALE | W_SLASH);
}
