inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
set_soft_amount(100);
set_alco_amount(0);
set_name("water");
set_pname("waters");
add_name("cup");
add_pname("cups");
set_adj(({"candy","flavored","candy flavored"}));
set_short("cup of candy flavored water");
set_pshort("cups of candy flavored water");
set_long("A small glass of the candy flavored  water, "+
"popular among the kender in Kendermore.\n");
add_prop(OBJ_I_WEIGHT, 100);
add_prop(OBJ_I_VOLUME, 100);
}
