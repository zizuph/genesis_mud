inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>
#include "/d/Gondor/defs.h"

create_armour() {
  set_name(({"trousers","black trousers","blacktrousers"}));
  set_short("pair of black trousers");
  set_pshort("pairs of leather trousers");
  set_long(BSN("These trousers are made of a fine black chain mesh. They are " +
       "normally worn by members of the Shades."));
  set_default_armour(25, A_LEGS, ({ 1, 1, -2 }), 0);
  add_prop(OBJ_I_WEIGHT,1500);
  add_prop(OBJ_I_VOLUME,700);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)+random(10)-5);
 }
