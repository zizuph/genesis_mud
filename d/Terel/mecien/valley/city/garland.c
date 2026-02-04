inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

create_armour(){
   
   set_name("garland");
   set_adj("evergreen");
   add_name("evergreen_garland");
   set_short("evergreen garland");
  set_at(A_HEAD);
   set_ac(3);
   add_prop("mystic_armour", 1);
   set_long("It is a beautiful garland of evergreen leaves.\n");
   add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment"}));
}

