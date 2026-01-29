#include <stdproperties.h>

#pragma save_binary

inherit "/d/Dville/caution/elf/obj/depository";


create_container() {
  set_name("piggy bank");
  set_pname("piggy banks");

  set_short("piggy bank");
  set_pshort("piggy banks");

  set_long("It is a piggy bank, containing @@cont@@ cc.\n");

  add_prop(CONT_I_WEIGHT, 10);
  add_prop(CONT_I_VOLUME, 10);
  add_prop(CONT_I_TRANSP, 0);
  add_prop(CONT_I_CLOSED, 0);
  add_prop(CONT_I_MAX_WEIGHT, 1000);
  add_prop(CONT_I_MAX_VOLUME, 1000);
}


string cont()
{
  return ""+balance(this_player());
}