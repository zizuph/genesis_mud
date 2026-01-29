inherit "/std/food";

#include <stdproperties.h>

create_food()
{
    set_amount(100);
    set_name("gingerbread");
    set_short("yummy gingerbread");
    set_adj("yummy");
    set_long("This gingerbread looks really yummy. What a luck you've been\n" +
      "nice this year.\n");
}
