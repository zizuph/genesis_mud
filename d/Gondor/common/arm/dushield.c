/* Shield of the Rohirrim */
#include "/sys/stdproperties.h"
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour()
{
  set_name("shield");
  set_pname("shields");
  set_short("painted steel shield");
  set_pshort("painted steel shields");
  set_adj("dunlending");
  add_adj("painted");
  add_adj("brown");
  add_adj("steel");
  set_long("This is a shield of steel, painted brown.\n");
  set_default_armour(30,A_SHIELD,({ -1,-1,2}),0);
}
