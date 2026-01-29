/*
 *  Food for your pet.
 *                          Tricky, 13-6-92
 */

inherit "/std/object";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_object()
{
   set_name(({"meal","doggy-meal","dogmeal"}));
   set_pname(({"meals","doggy-meals","dogmeals"}));
   set_short("doggy-meal");
   set_pshort("doggy-meals");
   set_long(break_string(
      "The doggy-meal doesn't look too edible to you, but pets seem to "
    + "love it. Who are you to question their judgement?\n", 70));

   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 700);
   add_prop(OBJ_I_VOLUME, 700);
}
