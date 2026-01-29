#include <stdproperties.h>
#include "../stddefs.h"

#pragma save_binary

inherit "/std/food";
inherit STRINGLIB;


create_food()
{
  set_name(({"fruit", "apple"}));
  set_adj(({"unripe", "small"}));
  set_long(WRAP("It is a small, unripe apple, sour and unappealing.\n"));

  add_prop(OBJ_I_WEIGHT, 100); 
  add_prop(OBJ_I_VOLUME, 120);
  add_prop(OBJ_I_VALUE, 0);
  set_amount(0);
}
