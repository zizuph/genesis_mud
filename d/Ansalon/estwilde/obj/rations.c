inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("rations");
    add_name("pack");
    add_name("ration");
    add_pname("packs");
    set_adj("iron");
    set_short("pack of iron rations");
    set_pshort("packs of iron rations");
    set_long("This small pack of mostly dried meat is used " +
      "as a reliable travelling food. While not particularly " +
      "tasty, it is reasonably filling.\n");
    set_amount(212);
}
