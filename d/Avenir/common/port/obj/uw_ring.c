 // file name:    ~Avenir/common/port/obj/uw_ring.c
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
  set_short("diamond ring");
  set_name("ring");
  set_adj(({"diamond"}));
  set_long ("A golden ring with a huge diamond embedded. It looks quite "
          + "valuable.\n");

  set_ac(1);
  set_am(({ 0, 0, 0}));
  set_at (A_ANY_FINGER);
  set_likely_break(5);

  add_prop( OBJ_I_VALUE, 2000);
  add_prop( OBJ_I_WEIGHT, 300);
  add_prop( OBJ_I_VOLUME, 100);
}
