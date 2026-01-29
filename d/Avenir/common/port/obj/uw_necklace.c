 // file name:    ~Avenir/common/port/obj/uw_necklace.c
 // creator(s):    Glinda june -95
 // last update:
 // purpose:       One of the treasures that can be found in the wreck
 // note:
 // bug(s):
 // to-do:

inherit "/std/armour";
#include "/d/Avenir/common/common.h"
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
  set_short("ruby necklace");
  set_name("necklace");
  set_adj(({"red","ruby"}));
  set_long ("A golden necklace with a large ornament of rubies. It looks "
            + "quite valuable.\n");

  set_ac(1);
  set_am(({ 0, 0, 0}));
  set_at (A_NECK);
  set_likely_break(5);

  add_prop( OBJ_I_VALUE, 2100);
  add_prop( OBJ_I_WEIGHT, 300);
  add_prop( OBJ_I_VOLUME, 100);
}

