inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("soup");
    set_adj("chilled");
    set_short("bowl of chilled soup");
    set_pshort("bowls of chilled soup");
    set_long("Chilled soup, rather popular in the " +
      "stifling hot city of Sanction.\n");
    set_amount(212);
}
