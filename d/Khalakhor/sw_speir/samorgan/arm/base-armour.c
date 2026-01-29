/*
 * Base armour class for samorgan stuff
 * Tapakah, 04-05/2021
 */

#pragma no_clone
#pragma strict_types

#include <wa_types.h>      /* contains weapon/armour related definitions */
#include <stdproperties.h> /* contains standard properties */
#include <formulas.h>      /* contains various formulae */

#include "../defs.h"

inherit "/std/armour";

#define ARMOUR_CLASS 15
#define LEVEL_GRADE  4

varargs void
configure_samorgan_armour (int level=1)
{
  int armour_class = ARMOUR_CLASS + level*LEVEL_GRADE;
  set_ac(armour_class);
  set_am( ({ -1, 2, -1 }) );
  string a_type = query_name();
  string x_long;
  
  switch (a_type) {
  case "chainmail":
  case "mail":
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 2000);
    x_long = "It has a green emblem over the chest.\n";
    break;
  case "helmet":
  case "helm":
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 700);
    x_long = "It has a green emblem on the forehead.\n";
    break;
  case "coif":
    set_at(A_HEAD|A_NECK|A_CHEST);
    set_ac(15);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VOLUME, 1200);
    x_long = "It has a green emblem on the forehead.\n";
    break;
  case "shield":
    set_at(A_SHIELD);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 1500);
    x_long = "It has a green emblem in the center.\n";
    break;
  case "leggings":
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 1400);
    x_long = "It has a green emblem over the shinpads.\n";
    break;
  default:
    break;
  }    
    
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(armour_class));
  if (level > SM_SERGEANT_LEVEL) {
    set_long(query_long() + x_long);
    add_item("emblem",
             "The emblem depicts a conifer tree that could be a fir or a spruce.\n");
  }
}
