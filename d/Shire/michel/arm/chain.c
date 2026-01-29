/* This is a small item needed to complete the pond quest */
/* Is to be found by searching in the bottom of the pond  */
 
inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
 
create_armour()
{
  set_name("_elegant_chain_");
  add_name("chain");
  set_short("elegant silver chain");
  set_long("This is a small silver piece of ancient jewelry.\n" +
  "It does not contain much of the precious metals but \n"+
  "is crafted with unbelievable mastership. \n" +
  "The Ancient Dwarves made this many centuries ago.\n");
  add_adj(({"elegant","dwarvish","silver","ancient","small"}));
  add_prop(OBJ_I_VALUE,100 + random(100));
  add_prop(OBJ_I_WEIGHT,650);
  add_prop(OBJ_I_VOLUME,99);
  set_ac(1);
  set_at(A_NECK);
}
