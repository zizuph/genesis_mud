/* gresolle 921113 */
inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
  set_soft_amount(100); /* a pint */
  set_alco_amount(100);
  set_long("This is a pint of the world famous Roke beer, the most\n"+
           "refreshing and relaxing beer ever made.\n");
  set_name("beer");
  set_adj("smelly");
  set_short("orc beer");
  set_pshort("orc beers");
  add_name("orcbeer");

  add_prop(OBJ_I_WEIGHT,600);
  add_prop(OBJ_I_VOLUME,600);

}



