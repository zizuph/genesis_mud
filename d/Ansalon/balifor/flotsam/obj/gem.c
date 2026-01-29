/*
gem.c
-----

Coded ........: 95/05/09
By ...........: Jeremiah

Latest update : 95/05/09
By ...........: Jeremiah


*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"


void
create_object()
{
   set_name("gem");
   set_short("red gem");
   set_long("This small red gem is most magnificent! As you turn " +
      "it in your hand, the light of the sun sparkles through it, casting " +
      "a fiery blood-red light. You gather this gem would be worth a bit " +
      "at the markets.\n");
   
   add_prop(OBJ_I_VALUE, 30);
   add_prop(OBJ_I_WEIGHT,20);
   add_prop(OBJ_I_VOLUME,20);
   add_prop(OBJ_I_VALUE, 3500);
}
