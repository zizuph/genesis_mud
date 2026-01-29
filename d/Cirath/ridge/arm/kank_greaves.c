 /* Derryn's greaves.
 code (c) 1998 Damian Horton */

#pragma strict_types
#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include "defs.h"
#include "/sys/formulas.h"

void create_armour()
{
  set_name("greaves");
  set_short("kank greaves");
  set_long("These greaves are fashioned from strips of black kank carapace "+
           ". Thus, they supply quite reasonable protection to ones "+
           "legs.\n");
  set_adj("kank");

  set_ac(16);
  set_am(({-1,-1,2})); 
  set_at(A_LEGS);

  add_prop(OBJ_I_WEIGHT, 2700);
  add_prop(OBJ_I_VOLUME, 2300);
  add_prop(OBJ_I_VALUE,(F_VALUE_ARMOUR(16)/2)-random(100));
}
