inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name(({"salad", "plate"}));
    set_adj("seaweed");
    set_short("plate of seaweed salad");
    set_pshort("plates of seaweed salads");
    set_long("Uuurgh. It would be best not to explore what " +
      "exactly is in this salad. From the smell of it you " +
      "would need to be a gully dwarf, or very hungry, to " +
      "enjoy a meal of this. \n");
    set_amount(150);
}
