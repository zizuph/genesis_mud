// -*-C++-*-
// name:  rum   /d/Avenir/common/ships/sparkle/rum.c
// creator(s):    Boriska, Mar 26 1995
// last update:   
// purpose:       To be placed in chest in the Sparkle-Avenir ship
// note:
// bug(s):
// to-do:         

#include <stdproperties.h>

#pragma save_binary

inherit "/std/drink";

void
create_drink()
{
  set_name("rum");
  add_name("bottle");
  set_short("bottle of rum");
  set_long("A bottle of strong exotic rum, covered with dust and cobwebs.\n");
  set_soft_amount(200);
  set_alco_amount(100);
  
  add_prop(OBJ_I_WEIGHT, 500);
  add_prop(OBJ_I_VOLUME, 500);
}
