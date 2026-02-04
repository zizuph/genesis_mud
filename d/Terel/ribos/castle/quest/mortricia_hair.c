inherit "/std/weapon.c";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon()
{
   set_name("hair");
   set_short("lock of Mortricia's hair");
   set_long(break_string(
   "A 3 foot long lock of Mortricia's hair.  It shines, sparkles, " +
   "and is as strong as steel.  In fact, it could even be used, " +
   "possibly, as a sword.\n", 70));

   set_hit(3);
   set_pen(3);
   set_wt(W_SWORD);
   set_dt(W_IMPALE | W_SLASH);

}
