inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>
#include "/d/Gondor/defs.h"

create_armour() {
  set_name(({"tunic", "black tunic", "black chain tunic", "chain tunic"}));
  set_short("black tunic");
  set_pshort("black tunics");
  set_long(BSN("This is a black tunic made of fine chain mesh. It is light " +
             "and will provide rather good protection despite its appearance"));
  set_default_armour(25,A_BODY,({1, 1, -2}), 0);
  add_prop(OBJ_I_WEIGHT,4000);
  add_prop(OBJ_I_VOLUME,900);
  add_prop(OBJ_I_VALUE,750);
}
