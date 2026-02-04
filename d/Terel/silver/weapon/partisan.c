/*
  
  by Udana, /2006
*/

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume, 1.0 is for steel.*/
#define WEIGHT_MOD 1.2
/* used to calculate value */
#define VALUE_MOD 1.0
#define HIT 25
#define PEN 38


create_weapon()
{
  set_name("partisan");
  add_name("polearm");
  set_adj("long");
  set_short("long partisan");   
  set_long("A long wooden spear with small axes added at both sides of its head. This rather unhandy "+
    "weapon is almost out of use, yet some guards and soldiers still prefers is over standard spears. "+
    "It takes more skill to use, but it offers more damage.\n");
  set_default_weapon(HIT, PEN, W_POLEARM, W_IMPALE | W_SLASH, W_BOTH);
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_WEAPON(HIT, PEN)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM)) * WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));

  add_item(({"axes", "head"}), "Two small axes has been added to both sides of the head of this weapon, it's "+
    "it's probably possible to use them to chop your enemies, but it wouldn't be very easy.\n");
}
