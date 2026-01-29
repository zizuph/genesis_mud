#pragma save_binary

inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

void create_weapon()
{
  set_name("cutlass");
    set_adj(({"light","sharp"}));
  set_short("sharp light cutlass");
  set_long("This cutlass has a narrower, lighter blade than usual, "+
    "but as a result feels much more maneuverable. The blade gleams "+
    "brightly with even the slightest light, giving testiment to the "+
    "loving care the steel has been shown by its owner. A silvery wire "+
    "braid provides an excellent grip to the otherwise unadorned "+
     "hilt.\n");
  set_default_weapon(20,17,W_SWORD,W_SLASH,W_ANYH,0);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(20,17)+random(91));
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(17,W_SWORD)-500-random(16));
  add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
}
