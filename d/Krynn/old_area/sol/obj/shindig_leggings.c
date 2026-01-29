inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
   set_name("leggings");
   set_ac(10);
   set_at(A_LEGS);
   set_short("dark green leggings");
   add_adj(({"dark","green"}));
   set_long("These pair of dark green leggings are apparently "+
      "of good quality. Bright golden decorations adorn "+
      "the fabric. They are also quite small, probably "+
      "worn by a kender or gnome.\n");
   add_prop(OBJ_I_VOLUME, 4750);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_LEGS));
   add_prop(OBJ_I_VALUE, 400);
}

