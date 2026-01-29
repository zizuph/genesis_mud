/* Berry juice for Kendermore, Gwyneth, May 1999 */

inherit "/std/drink";
#include <stdproperties.h>

void
create_drink()
{
set_soft_amount(75);
set_alco_amount(0);
set_name("juice");
add_name("_kendermore_berry_juice");
set_pname("juices");
add_name("glass");
add_pname("glasses");
set_adj("berry");
add_adj("fresh");
set_short("glass of fresh berry juice");
set_pshort("glasses of fresh berry juice");
set_long("A small glass of freshly squeezed berry juice. \n");
add_prop(OBJ_I_WEIGHT, 30);
add_prop(OBJ_I_VOLUME, 30);
}
