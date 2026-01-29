inherit "/std/object";

#include <stdproperties.h>

void create_object()
{
  set_short("shiny brooch");
  set_name("brooch");
  set_adj("shiny");
  set_long("This is a small, shiny brooch, which cannot be worn, but" +
           " only carried on the person.  There is small engraving on it.\n");
  add_item("engraving", "It reads:\nTo the officer Muhrdaal for" +
                        " spreading the glory of Easterlings.\n");
  add_prop(OBJ_I_VALUE, 120);
}
