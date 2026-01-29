
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_armour()
{
  set_name("cloak");
  add_name("robe");
  set_pname("cloaks");
  add_pname("robes");
  set_short("decorative red cloak");
  set_pshort("decorative red cloaks");
  set_adj("decorative");
  set_adj("red");
  set_long("This is a bright and decorative piece of clothing. It is red of\n"+
    "colour, with elaborate golden patterns on the edges.\n");
  set_default_armour(3, A_ROBE, (({ 0, 0, 1})), 0);
  add_prop(OBJ_I_WEIGHT, 360);   /* 360 gram */
  add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3)+random(20));
}
