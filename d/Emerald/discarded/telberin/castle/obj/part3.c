inherit "/std/object";

#include "default.h"

void
create_object()
{
   set_short("collection of pages");
   set_long("These pages are the end of a small book, the writing very "+
      "ornate and caligraphised.\n");
   set_name("pages");
	add_name("collection");
   add_name("_quest_book_part_3_");
   add_prop(OBJ_I_VOLUME, 23);
   add_prop(OBJ_I_WEIGHT, 24);
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(OBJ_I_VALUE, 37);
}
