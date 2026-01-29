inherit "/std/object";

#include "default.h"

void
create_object()
{
   set_short("collection of pages");
   set_long("This collection of pages seems to be the start of a small "+
      "book. The writing is\nextremely ornate and caligraphised.\n");
   set_name("pages");
   add_name("collection");
   add_name("_quest_book_part_1_");
   add_prop(OBJ_I_VOLUME, 23);
   add_prop(OBJ_I_WEIGHT, 24);
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(OBJ_I_VALUE, 37);
}
