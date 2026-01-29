/*
 * Base weapon class for samorgan stuff
 * Tapakah, 04/2021
 */

#pragma no_clone
#pragma strict_types

#include <wa_types.h>      /* contains weapon/armour related definitions */
#include <stdproperties.h> /* contains standard properties */
#include <formulas.h>      /* contains various formulae */

#include "../defs.h"

inherit "/std/weapon";

#define WEAPON_CLASS 15
#define LEVEL_GRADE  4

void
configure_samorgan_guard_weapon (int level)
{
  int weapon_class = WEAPON_CLASS + level*LEVEL_GRADE;
  set_hit(weapon_class); set_pen(weapon_class);
  set_hands(W_ANYH);
  set_dt(W_SLASH | W_IMPALE);
  string w_type = query_name();
  string x_long;
  
  switch (w_type) {
  case "dagger":
  case "knife":
    set_wt(W_KNIFE);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 150);
    x_long = "It has a green emblem on the hilt.\n";
    break;
  case "spear":
    set_wt(W_POLEARM);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 700);
    break;
  case "partisan":
  case "halberd":
    set_wt(W_POLEARM);
    weapon_class += 10;
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 1500);
    set_hands(W_BOTH);
    set_wt(W_SLASH|W_IMPALE);
    break;
  case "sword":
    set_wt(W_SWORD);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 800);
    x_long = "It has a green emblem on the crossguard.\n";
    break;
 default:
    break;
  }    
    
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(weapon_class, weapon_class));
  if (level > 3) {
    set_long(query_long() + x_long);
    add_item("emblem",
             "The emblem depicts a conifer tree that could be a fir or a spruce.\n");
  }
}
