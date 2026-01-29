 // file name:    ~Avenir/common/port/obj/uw_dagger.c
 // creator(s):    Glinda june -95
 // last update:
 // purpose:       One of the treasures that can be found in the wreck
 // note:
 // bug(s):
 // to-do:

inherit "/d/Avenir/inherit/weapon";
#include "/d/Avenir/common/common.h"
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
  set_short("ornate dagger");
  set_name("dagger");
  set_adj(({"ornate","golden"}));
  set_long ("A golden dagger which has been ornamneted with jewels. It " +
            "looks very valuable.\n");

  set_hit( 5);
  set_pen( 9);
  set_wt( W_KNIFE);
  set_dt( W_SLASH | W_IMPALE );
  set_hands( W_ANYH);
  set_likely_break( 5);

  add_prop( OBJ_I_VALUE, 2000);
  add_prop( OBJ_I_WEIGHT, 1200);
  add_prop( OBJ_I_VOLUME, 400);
}

