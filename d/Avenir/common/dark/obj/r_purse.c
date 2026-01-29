// Rogue's purse, for dark/mon/rogue
// Made by Boriska, Feb 1995

inherit "/std/receptacle";

#include <stdproperties.h>

void
create_receptacle ()
{
  set_name ("purse");
  set_short("once-fat purse");
  set_pshort("once-fat purses");
  add_adj("once-fat");
  set_long("This worn purse had seen better days and lots of money.\n");
  add_prop (CONT_I_WEIGHT, 100);
  add_prop (CONT_I_VOLUME, 100);
  add_prop (OBJ_I_VALUE,  50);
  add_prop (CONT_I_MAX_WEIGHT, 2000);
  add_prop (CONT_I_MAX_VOLUME, 2000);
}

