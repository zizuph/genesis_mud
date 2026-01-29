inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_short("plate of smoked meat");
set_pshort("plates of smoked meat");
    set_name("plate");
    set_pname("plates");
    add_name("meat");
    add_pname("meats");
    set_adj("smoked");
    set_long("A large plate of smoked meat.\n");
    set_amount(320);
}
