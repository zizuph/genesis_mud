// -*-C++-*-
// name:  rum   /d/Avenir/common/port/obj/rum.c
// creator(s):    Boriska, Aug 1995
// last update:   
// purpose:       To keep port sailors drunk
// note:
// bug(s):
// to-do:         

#include <stdproperties.h>

inherit "/std/drink";

void
create_drink()
{
  set_name("rum");
  add_name("flask");
  set_short("flask of rum");
  set_long("A flask of strong exotic rum, the favourite drink of seamen.\n");
  set_soft_amount(100);
  set_alco_amount(40);
  
  add_prop(OBJ_I_WEIGHT, 300);
  add_prop(OBJ_I_VOLUME, 300);
}

