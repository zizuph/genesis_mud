inherit "/std/scroll";

#include <stdproperties.h>
#include "defs.h"

void
create_scroll()
{
  set_name("book");
  set_adj("leather-bound");
  add_adj("old");
  set_long("This is a old book with a cover made of black leather.\n"+
           "It looks like it have been read quite many times. It's\n"+
           "pages are made of the finest paper and you have to be \n"+
           "very careful reading it.\n");

  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME, 1000);

  set_file(BARB + "barb_book.txt");
}

