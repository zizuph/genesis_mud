/*
 *    A warg skin
 *    (modified from Rohan wolf skin)
 */
#pragma strict_types

inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

void
create_armour() 
{
  set_name("warg skin");
  add_name("skin");
  add_name("wargskin");
  add_name("fur");
  add_name("warg fur");
  set_short("furry warg skin");
  set_pshort("warg skins");
  set_long("The skin of a warg from Isengard.\n");
  set_adj(({"furry","warg's", "warg"}));
  set_ac(20);
  set_at(A_BODY);
  set_am(({-2,2,1}));
  add_prop(OBJ_I_WEIGHT,(800+(random(600))));
  add_prop(OBJ_I_VOLUME,(600+(random(600))));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(9)+random(40)-50);
  add_prop(OBJ_M_NO_STEAL, 1);
}

