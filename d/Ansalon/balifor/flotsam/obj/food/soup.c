inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("soup");
    set_adj("warm");
    set_short("bowl of warm soup");
    set_pshort("bowls of warm soup");
    set_long("Although warm, this soup does not smell " +
      "very good. \n");
    set_amount(212);
}
